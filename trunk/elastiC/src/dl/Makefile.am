# ==========================================================================
# Makefile.am
# ==========================================================================
# Automake makefile template for elastiC.
# --------------------------------------------------------------------------
#   AUTHOR:  Marco Pantaleoni         E-mail: panta@elasticworld.org
#
#   Created: 15 Nov 1999
#
#   $Id$
# --------------------------------------------------------------------------
#    Copyright (C) 1999-2001 Marco Pantaleoni. All rights reserved.
#
#  The contents of this file are subject to the elastiC License version 1.0
#  (the "elastiC License"); you may not use this file except in compliance
#  with the elastiC License. You may obtain a copy of the elastiC License at
#  http://www.elasticworld.org/LICENSE
#
#  IN NO EVENT SHALL THE AUTHOR OR DISTRIBUTORS BE LIABLE TO ANY PARTY
#  FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES
#  ARISING OUT OF THE USE OF THIS SOFTWARE, ITS DOCUMENTATION, OR ANY
#  DERIVATIVES THEREOF, EVEN IF THE AUTHOR HAS BEEN ADVISED OF THE
#  POSSIBILITY OF SUCH DAMAGE.
#
#  THE AUTHOR AND DISTRIBUTORS SPECIFICALLY DISCLAIM ANY WARRANTIES,
#  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT.  THIS SOFTWARE
#  IS PROVIDED ON AN "AS IS" BASIS, AND THE AUTHOR AND DISTRIBUTORS HAVE
#  NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR
#  MODIFICATIONS.
#
#  See the elastiC License for the specific language governing rights and
#  limitations under the elastiC License.
# ==========================================================================

# Directory where sources are, from where we are.
srcdir = @srcdir@
VPATH = @srcdir@

EXTRA_DIST = dl-ltdl.c dl-dl.c dl-no.c dl-win32.c
noinst_LTLIBRARIES = libdl.la

CFLAGS = $(CORE_CFLAGS)

if DLBACKEND_DL
DL_SRCS = dl-dl.c
else
DL_SRCS =
endif
if DLBACKEND_LTDL
LTDL_SRCS = dl-ltdl.c
else
LTDL_SRCS =
endif
if DLBACKEND_NO
NO_SRCS = dl-no.c
else
NO_SRCS =
endif
if DLBACKEND_WIN32
WIN32_SRCS = dl-win32.c
else
WIN32_SRCS =
endif

# Chose your version here !
static_sources = \
	$(DL_SRCS)	\
	$(LTDL_SRCS)	\
	$(NO_SRCS)	\
	$(WIN32_SRCS)
#static_sources = \
#	dl-no.c

libdl_la_SOURCES = \
	$(static_sources)

INCLUDES = -I$(top_srcdir) -I$(top_srcdir)/src $(INCLTDL)
