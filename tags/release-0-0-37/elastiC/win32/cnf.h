/* cnf.h.in -*-c-*- */

#ifdef _WIN32
#undef WIN32
#define WIN32
#endif

#if defined(WIN32) || defined(_WIN32)
	/* Win32 */

#if defined(MINGW32)
	/* Mingw32 */
#define EC_CCOMPILER_MINGW32

#elif defined(CYGWIN)
	/* Cygwin */
#define EC_CCOMPILER_CYGWIN

#elif defined(_MSC_VER)
	/* Microsoft Visual C++ */
#define EC_CCOMPILER_VC

#if _MSC_VER == 1200
#define EC_CCOMPILER_VC6
#endif

/* :TODO: _MSC_VER for EC_COMPILER_VC7 ??? */

#define LITTLE_ENDIAN 1234
#define BIG_ENDIAN    4321

#if defined(_M_ALPHA)
#define __alpha__
#undef  WORDS_BIGENDIAN
#define BYTE_ORDER LITTLE_ENDIAN
#elif defined(_M_IX86)
#undef  WORDS_BIGENDIAN
#define BYTE_ORDER LITTLE_ENDIAN
#elif defined(_M_MPPC)
#define  WORDS_BIGENDIAN 1
#define BYTE_ORDER BIG_ENDIAN
#elif defined(_M_MRX000)
#define  WORDS_BIGENDIAN 1
#define BYTE_ORDER BIG_ENDIAN
#elif defined(_M_PPC)
#define  WORDS_BIGENDIAN 1
#define BYTE_ORDER BIG_ENDIAN
#endif /* _M_* */

#endif /* defined(WIN32) ... defined(_MSC_VER) */

#endif /* WIN32 */

#ifdef WIN32
#define SO_SUFFIX ".dll"
#else /* ! WIN32 */
#define SO_SUFFIX ".so"
#endif

#define EC_VERSION			EC_MAKEVERSION(0, 0, 37)
#define EC_VERSION_STRING	"0.0.37"

#define EC_MAJOR_VERSION	0
#define EC_MINOR_VERSION	0
#define EC_MICRO_VERSION	37

#define EC_API_VERSION		10
#define EC_API_REVISION		0
#define EC_BINARY_AGE		1

#define CNF_PREFIX			"/home/panta/usrlocal"
#define CNF_EXECPREFIX		"${prefix}"
#define CNF_BINDIR			"${exec_prefix}/bin"
#define CNF_LIBS			"-ldl -lm "
#define CNF_CFLAGS			"-Wall -Winline -Wstrict-prototypes -Wno-protocols -D_GNU_SOURCE -I${top_builddir} -g -O0 -DEC_DEBUG"
#define CNF_CC				"gcc"

#define EC_PLATFORM_ALIGNMENT	8

/*
 * Should we use EC_API_VERSION instead of EC_VERSION in EC_DEFAULTLIBPATH ???
 * Maybe we should use:
 *  .../usr/lib/elastic:/usr/lib/elastic/native-10...
 */
#ifndef WIN32	/* UNIX */
#define EC_DEFAULTLIBPATH	"/usr/lib/elastic:/usr/lib/elastic-0.0.37:/home/panta/usrlocal/lib/elastic:/home/panta/usrlocal/lib/elastic-0.0.37"
#else		/* WIN32 */
/*
 * We are hardcoding default paths, which is *UGLY*
 * On Win32 we should really use a configuration mechanism
 * like the registry.
 */
#if defined(CYGWIN)
#define EC_DEFAULTLIBPATH	"C:\\elastic-0.0.37;C:\\elastic-0.0.37\\lib;C:\\elastic;C:\\elastic\\lib;/home/panta/usrlocal\\elastic;/home/panta/usrlocal\\elastic-0.0.37"
#else
#define EC_DEFAULTLIBPATH	"C:\\elastic-0.0.37;C:\\elastic-0.0.37\\lib;C:\\elastic;C:\\elastic\\lib"
#endif

#endif
