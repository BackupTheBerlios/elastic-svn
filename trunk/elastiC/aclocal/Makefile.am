# ==========================================================================
# Makefile.am
# ==========================================================================
# Automake makefile template for elastiC.
# --------------------------------------------------------------------------
#   AUTHOR:  Marco Pantaleoni         E-mail: panta@elasticworld.org
#
#   Created: 19 Nov 1999
#
#   $Id$
# --------------------------------------------------------------------------
#    Copyright (C) 1999-2002 Marco Pantaleoni. All rights reserved.
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

EXTRA_DIST = elastic-comp elastic-clean.am elastic.am elastic.m4 elasticdir.m4

aclocaldir  = $(datadir)/aclocal
automakedir = $(datadir)/automake

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(aclocaldir)
	for p in $(srcdir)/*.m4; do \
	  $(INSTALL_DATA) $$p $(DESTDIR)$(aclocaldir)/`basename $$p`; \
	done
#	#$(mkinstalldirs) $(DESTDIR)$(automakedir)
#	#for p in $(srcdir)/*.am; do \
#	#  $(INSTALL_DATA) $$p $(DESTDIR)$(automakedir)/`basename $$p`; \
#	#done
