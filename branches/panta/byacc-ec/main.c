#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#include "defs.h"

char dflag;
char lflag;
char rflag;
char tflag;
char vflag;
/* The version number is also stored in skeleton.c.  */
char *yaccversion = "Berkeley Yacc / elastiC";
char emitident;

char *file_prefix = NULL;
char *myname = "yacc";
char *temp_form = "yacc.XXXXXXX";

int lineno;
int outline;

int explicit_file_name;

char *action_file_name;
char *code_file_name;
char *defines_file_name;
char *input_file_name = "";
char *output_file_name;
char *text_file_name;
char *union_file_name;
char *verbose_file_name;

FILE *action_file;						   /*  a temp file, used to save actions associated    */
			/*  with rules until the parser is written      */
FILE *code_file;						   /*  y.code.c (used when the -r option is specified) */
FILE *defines_file;						   /*  y.tab.h                     */
FILE *input_file;						   /*  the input file                  */
FILE *output_file;						   /*  y.tab.c                     */
FILE *text_file;						   /*  a temp file, used to save text until all        */
			/*  symbols have been defined               */
FILE *union_file;						   /*  a temp file, used to save the union         */
			/*  definition until all symbol have been       */
			/*  defined                     */
FILE *verbose_file;						   /*  y.output                        */

int nitems;
int nrules;
int nsyms;
int ntokens;
int nvars;

int start_symbol;
char **symbol_name;
short *symbol_value;
short *symbol_prec;
char *symbol_assoc;

short *ritem;
short *rlhs;
short *rrhs;
short *rprec;
char *rassoc;
short **derives;
char *nullable;

/* elastiC variables */
int   ec_flag = 0;
char *ec_class_name   = NULL;
char *ec_package_name = NULL;
char *ec_extends_name = NULL;

void done(int k)
{
	if (action_file)
	{
		fclose(action_file);
		unlink(action_file_name);
	}
	if (text_file)
	{
		fclose(text_file);
		unlink(text_file_name);
	}
	if (union_file)
	{
		fclose(union_file);
		unlink(union_file_name);
	}
	exit(k);
}


RETSIGTYPE onintr(int num)
{
	done(EXIT_FAILURE);
}

void set_signals(void)
{
#ifdef SIGINT
	if (signal(SIGINT, SIG_IGN) != SIG_IGN)
		signal(SIGINT, onintr);
#endif
#ifdef SIGTERM
	if (signal(SIGTERM, SIG_IGN) != SIG_IGN)
		signal(SIGTERM, onintr);
#endif
#ifdef SIGHUP
	if (signal(SIGHUP, SIG_IGN) != SIG_IGN)
		signal(SIGHUP, onintr);
#endif
}

void usage(void)
{
	fprintf(stderr, "usage: %s [-dlrtvV] [-Q[y|n]] [-E[option]] [-b file_prefix] [-o outputfile] filename\n", myname);
	fprintf(stderr, "  where -E[option] is intended for elastiC parser generation:\n");
	fprintf(stderr, "   -E                     - generate an elastiC parser\n");
	fprintf(stderr, "   -Eclass=className      - the elastiC parser class name\n");
	fprintf(stderr, "   -Epackage=packageName  - the elastiC parser package name\n");
	fprintf(stderr, "   -Eextends=extendName   - the elastiC parser base class name\n");

	exit(EXIT_FAILURE);
}

void getargs_elastic(char *option)
{
	int len;

	ec_flag = 1;

	if (!option || !(*option))
		return;

	len = strlen(option);
	if (strncmp("class=", option, 6) == 0 && len > 6)
		ec_class_name = &(option[6]);
	else if (strncmp("package=", option, 8) == 0 && len > 8)
		ec_package_name = &(option[8]);
	else if (strncmp("extends=", option, 8) == 0 && len > 8)
		ec_extends_name = &(option[8]);
}

void byacc_getargs(int argc, char *argv[])
{
	int i;
	char *s;

	/* set elastiC defaults */
	ec_flag = 0;
	ec_class_name   = "Parser";
	ec_package_name = "Parser";
	ec_extends_name = "basic.Object";

	if (argc > 0)
		myname = argv[0];
	for (i = 1; i < argc; ++i)
	{
		s = argv[i];
		if (*s != '-')
			break;
		switch (*++s)
		{
		case '\0':
			input_file = stdin;
			if (i + 1 < argc)
				usage();
			return;

		case '-':
			++i;
			goto no_more_options;

		case 'b':
			if (*++s)
				file_prefix = s;
			else if (++i < argc)
				file_prefix = argv[i];
			else
				usage();
			continue;

		case 'o':
			if (*++s)
				output_file_name = s;
			else if (++i < argc)
				output_file_name = argv[i];
			else
				usage();
			explicit_file_name = 1;
			continue;

		case 'd':
			dflag = 1;
			break;

		case 'l':
			lflag = 1;
			break;

		case 'r':
			rflag = 1;
			break;

		case 't':
			tflag = 1;
			break;

		case 'v':
			vflag = 1;
			break;

		case 'V':
			fprintf(stderr, "%s: %s\n", myname, yaccversion);
			break;

		case 'Q':
			switch (*++s)
			{
			case 'y':
				emitident = 1;
				break;
			case 'n':
				emitident = 0;
				break;
			default:
				usage();
			}
			break;

		case 'E':
			ec_flag = 1;
			getargs_elastic(&(s[1]));
			continue;

		default:
			usage();
		}

		for (;;)
		{
			switch (*++s)
			{
			case '\0':
				goto end_of_option;

			case 'd':
				dflag = 1;
				break;

			case 'l':
				lflag = 1;
				break;

			case 'r':
				rflag = 1;
				break;

			case 't':
				tflag = 1;
				break;

			case 'v':
				vflag = 1;
				break;

			case 'V':
				fprintf(stderr, "%s: %s\n", myname, yaccversion);
				break;

			case 'E':
				ec_flag = 1;
				break;

			default:
				usage();
			}
		}
	  end_of_option:;
	}

  no_more_options:;
	if (i + 1 != argc)
		usage();
	input_file_name = argv[i];
}


char *allocate(unsigned int n)
{
	char *p;

	p = NULL;
	if (n)
	{
		p = CALLOC(1, n);
		if (!p)
			no_space();
	}
	return (p);
}

void create_file_names(void)
{
	int i,
	    len;
	char *tmpdir;

	tmpdir = getenv("TMPDIR");
#ifdef __WIN32__
	if (tmpdir == 0)
		tmpdir = ".";
#else
	if (tmpdir == 0)
		tmpdir = "/tmp";
#endif

	len = strlen(tmpdir);
	i = len + 13;
	if (len && tmpdir[len - 1] != '/')
		++i;

	action_file_name = MALLOC(i);
	if (action_file_name == 0)
		no_space();
	text_file_name = MALLOC(i);
	if (text_file_name == 0)
		no_space();
	union_file_name = MALLOC(i);
	if (union_file_name == 0)
		no_space();

	strcpy(action_file_name, tmpdir);
	strcpy(text_file_name, tmpdir);
	strcpy(union_file_name, tmpdir);

	if (len && tmpdir[len - 1] != '/')
	{
		action_file_name[len] = '/';
		text_file_name[len] = '/';
		union_file_name[len] = '/';
		++len;
	}

	strcpy(action_file_name + len, temp_form);
	strcpy(text_file_name + len, temp_form);
	strcpy(union_file_name + len, temp_form);

	action_file_name[len + 5] = 'a';
	text_file_name[len + 5] = 't';
	union_file_name[len + 5] = 'u';

	mktemp(action_file_name);
	mktemp(text_file_name);
	mktemp(union_file_name);

	if (ec_flag)
	{
		if (! file_prefix)
			file_prefix = ec_class_name;
	} else
	{
		if (! file_prefix)
			file_prefix = "y";
	}

	if (ec_flag)
	{
		len = strlen(file_prefix);

		if (!output_file_name)
		{
			output_file_name = MALLOC(len + strlen(EC_OUTPUT_SUFFIX) + 1);
			if (output_file_name == 0)
				no_space();
			strcpy(output_file_name, file_prefix);
			strcpy(output_file_name + len, EC_OUTPUT_SUFFIX);
		}
	} else
	{
		len = strlen(file_prefix);

		if (!output_file_name)
		{
			output_file_name = MALLOC(len + strlen(OUTPUT_SUFFIX) + 1);
			if (output_file_name == 0)
				no_space();
			strcpy(output_file_name, file_prefix);
			strcpy(output_file_name + len, OUTPUT_SUFFIX);
		}
	}

	if (rflag)
	{
		code_file_name = MALLOC(len + 8);
		if (code_file_name == 0)
			no_space();
		strcpy(code_file_name, file_prefix);
		strcpy(code_file_name + len, CODE_SUFFIX);
	} else
		code_file_name = output_file_name;

	if (dflag)
	{
		if (explicit_file_name)
		{
			defines_file_name = MALLOC(strlen(output_file_name));
			if (defines_file_name == 0)
				no_space();
			strcpy(defines_file_name, output_file_name);
			if (!strcmp(output_file_name + (strlen(output_file_name) - 2), ".c"))
				defines_file_name[strlen(output_file_name) - 1] = 'h';
		} else
		{
			defines_file_name = MALLOC(len + 7);
			if (defines_file_name == 0)
				no_space();
			strcpy(defines_file_name, file_prefix);
			strcpy(defines_file_name + len, DEFINES_SUFFIX);
		}
	}

	if (vflag)
	{
		verbose_file_name = MALLOC(len + 8);
		if (verbose_file_name == 0)
			no_space();
		strcpy(verbose_file_name, file_prefix);
		strcpy(verbose_file_name + len, VERBOSE_SUFFIX);
	}
}

void open_files(void)
{
	create_file_names();

	if (input_file == 0)
	{
		input_file = fopen(input_file_name, "r");
		if (input_file == 0)
			open_error(input_file_name);
	}

	action_file = fopen(action_file_name, "w");
	if (action_file == 0)
		open_error(action_file_name);

	text_file = fopen(text_file_name, "w");
	if (text_file == 0)
		open_error(text_file_name);

	if (vflag)
	{
		verbose_file = fopen(verbose_file_name, "w");
		if (verbose_file == 0)
			open_error(verbose_file_name);
	}

	if (dflag)
	{
		defines_file = fopen(defines_file_name, "w");
		if (defines_file == 0)
			open_error(defines_file_name);
		union_file = fopen(union_file_name, "w");
		if (union_file == 0)
			open_error(union_file_name);
	}

	output_file = fopen(output_file_name, "w");
	if (output_file == 0)
		open_error(output_file_name);
	if (emitident)
		fprintf(output_file, "#ident \"%s: %s\"\n", myname, yaccversion);

	if (rflag)
	{
		code_file = fopen(code_file_name, "w");
		if (code_file == 0)
			open_error(code_file_name);
	} else
		code_file = output_file;
}


int main(int argc, char *argv[])
{
	set_signals();
	byacc_getargs(argc, argv);
	open_files();
	reader();
	lr0();
	lalr();
	make_parser();
	verbose();
	output();
	done(EXIT_SUCCESS);

	/*NOTREACHED*/
	exit(EXIT_SUCCESS);
}
