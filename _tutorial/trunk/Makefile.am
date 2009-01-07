## Copyright (c) 2008  Openismus GmbH  <danielk@openismus.com>
##
## This file is part of the Cluttermm Tutorial.
##
## The Cluttermm Tutorial is free software; you can redistribute it and/or
## modify it under the terms of the GNU General Public License as published
## by the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## The Cluttermm Tutorial is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with the Cluttermm Tutorial; if not, write to the Free Software
## Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA

## This project does not use recursive make, but a single toplevel Makefile
## to build the entire tree (excluding the po subdirectory as gettext comes
## with its own build system).  Read Peter Miller's excellent paper to learn
## why recursive make invocations are both slow and error-prone:
## http://members.pcug.org.au/~millerp/rmch/recu-make-cons-harm.html

AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS  = -I m4 $(ACLOCAL_FLAGS)
DISTCHECK_CONFIGURE_FLAGS = --enable-warnings=fatal

noinst_PROGRAMS =	\
	examples/actor/example			\
	examples/actor_group/example		\
	examples/actor_transformations/example	\
	examples/behaviour/example		\
	examples/custom_actor/example		\
	examples/custom_container/example	\
	examples/effects/example		\
	examples/full_example/example		\
	examples/multiline_text_entry/example	\
	examples/score/example			\
	examples/scrolling/example		\
	examples/stage/example			\
	examples/stage_widget/example		\
	examples/timeline/example

examples_actor_example_SOURCES			= examples/actor/main.cc
examples_actor_group_example_SOURCES		= examples/actor_group/main.cc
examples_actor_transformations_example_SOURCES	= examples/actor_transformations/main.cc
examples_behaviour_example_SOURCES		= examples/behaviour/main.cc
examples_custom_actor_example_SOURCES =		\
	examples/custom_actor/main.cc		\
	examples/custom_actor/triangle_actor.cc	\
	examples/custom_actor/triangle_actor.h
examples_custom_container_example_SOURCES =	\
	examples/custom_container/examplebox.cc	\
	examples/custom_container/examplebox.h	\
	examples/custom_container/main.cc
examples_effects_example_SOURCES		= examples/effects/main.cc
examples_full_example_example_SOURCES		= examples/full_example/main.cc
examples_multiline_text_entry_example_SOURCES =		\
	examples/multiline_text_entry/main.cc		\
	examples/multiline_text_entry/multiline_entry.cc\
	examples/multiline_text_entry/multiline_entry.h
examples_score_example_SOURCES			= examples/score/main.cc
examples_scrolling_example_SOURCES =		\
	examples/scrolling/main.cc		\
	examples/scrolling/scrollingcontainer.cc\
	examples/scrolling/scrollingcontainer.h
examples_stage_example_SOURCES			= examples/stage/main.cc
examples_stage_widget_example_SOURCES		= examples/stage_widget/main.cc
examples_timeline_example_SOURCES		= examples/timeline/main.cc

AM_CPPFLAGS = $(TUTORIAL_MODULES_CFLAGS)
AM_CXXFLAGS = $(TUTORIAL_WXXFLAGS)
LDADD = $(TUTORIAL_MODULES_LIBS)

dist_pkgdata_DATA =						\
	examples/full_example/images/alexander_larsson.jpg	\
	examples/full_example/images/andreas_nilsson.jpg	\
	examples/full_example/images/bastian_nocera.jpg		\
	examples/full_example/images/christian_kellner.jpg	\
	examples/full_example/images/david_zeuthen.jpg		\
	examples/full_example/images/john_palmieri.jpg		\
	examples/full_example/images/jonathan_blandford.jpg	\
	examples/full_example/images/matthew_allum.jpg		\
	examples/full_example/images/matthias_clasen.jpg	\
	examples/full_example/images/mikael_hallendal.jpg	\
	examples/full_example/images/ryan_lortie.jpg

cluttermm_docdir = $(datadir)/doc/cluttermm-0.9/docs
tutorialdir	= $(cluttermm_docdir)/tutorial/html
figuresdir	= $(cluttermm_docdir)/tutorial/figures
iconsdir	= $(cluttermm_docdir)/tutorial/icons

dist_figures_DATA =					\
	docs/tutorial/figures/actor_events.png		\
	docs/tutorial/figures/actor_group.png		\
	docs/tutorial/figures/actors.png		\
	docs/tutorial/figures/actor_transformations.png	\
	docs/tutorial/figures/alpha-func.png		\
	docs/tutorial/figures/behaviours.png		\
	docs/tutorial/figures/custom_actor.png		\
	docs/tutorial/figures/custom_container.png	\
	docs/tutorial/figures/effects.png		\
	docs/tutorial/figures/full_example.png		\
	docs/tutorial/figures/multiline_text_entry.png	\
	docs/tutorial/figures/path-alpha-func.png	\
	docs/tutorial/figures/score.png			\
	docs/tutorial/figures/scrolling.png		\
	docs/tutorial/figures/stage.png			\
	docs/tutorial/figures/stage_widget.png		\
	docs/tutorial/figures/timeline.png

dist_icons_DATA =				\
	docs/tutorial/icons/caution.png		\
	docs/tutorial/icons/home.png		\
	docs/tutorial/icons/important.png	\
	docs/tutorial/icons/next.png		\
	docs/tutorial/icons/note.png		\
	docs/tutorial/icons/prev.png		\
	docs/tutorial/icons/tip.png		\
	docs/tutorial/icons/up.png		\
	docs/tutorial/icons/warning.png

web_host	= www.openismus.com
web_path	= /home/murrayc/openismus.com/documents/cluttermm_tutorial/0.9/
web_path_docs	= $(web_path)docs/

clutter_tut_path = $(web_path_docs)tutorial

# --delete and --delete-after are causing
# "
# Invalid file index: 1768710413 (count=0) [receiver]
# rsync error: protocol incompatibility (code 2) at sender.c(156)
# "
# with sourceforge recently (May 2005). murrayc.

#rsync_args	= -vz --rsh ssh --delete --delete-after
rsync_args	= -vz --rsh ssh

DOCBOOK_PHPWEBNOTES_TRANSFORM = docs/tutorial/docbook_phpwebnotes.xsl

dist_noinst_DATA =					\
	docs/index.html					\
	docs/tutorial/README				\
	docs/tutorial/cluttermm-tut.xml			\
	docs/tutorial/cluttermm-tut-with-examples.xml	\
	$(DOCBOOK_PHPWEBNOTES_TRANSFORM)		\
	docs/tutorial/insert_example_code.pl		\
	docs/tutorial/style.css

EXTRA_DIST = docs/tutorial/html

DOCBOOK_STYLESHEET ?= http://docbook.sourceforge.net/release/xsl/current/xhtml/chunk.xsl

# Create a DocBook source file that doesn't have the examples' comments blocks:
docs/tutorial/cluttermm-tut-with-examples.xml: docs/tutorial/cluttermm-tut.xml docs/tutorial/insert_example_code.pl
	$(PERL_PATH) $(srcdir)/docs/tutorial/insert_example_code.pl $(srcdir)/examples $< >$@

# The new XML DocBook way:
XSLTPROC = xsltproc
XMLLINT = xmllint
DB2PDF = docbook2pdf

docs/tutorial/html/index.html: docs/tutorial/cluttermm-tut-with-examples.xml
	-rm -rf docs/tutorial/html
	mkdir docs/tutorial/html
	$(XSLTPROC) \
	  --param toc.section.depth 1 \
	  --stringparam html.stylesheet style.css \
	  --stringparam admon.graphics 1 \
	  --stringparam admon.graphics.path ../icons/ \
	  --stringparam admon.graphics.extension .png \
	  --stringparam chunker.output.indent yes \
	  --stringparam chunker.output.encoding UTF-8 \
	  --stringparam navig.graphics yes \
	  --stringparam navig.graphics.extension .png \
	  --stringparam navig.graphics.path ../icons/ \
	  --stringparam toc.list.type ul \
	  --stringparam use.id.as.filename 1 \
	  --xinclude --catalogs -o docs/tutorial/html/ \
	  $(DOCBOOK_STYLESHEET) $<

validate-original: docs/tutorial/cluttermm-tut.xml
	$(XMLLINT) --xinclude --valid --noout --catalogs $(DOCBOOK_STYLESHEET) $<

validate: docs/tutorial/cluttermm-tut-with-examples.xml
	$(XMLLINT) --xinclude --valid --noout --catalogs $(DOCBOOK_STYLESHEET) $<

post-html: docs/tutorial/html/index.html docs/tutorial/style.css docs/tutorial/pdf/programming-with-cluttermm.pdf
	rsync $(rsync_args) $(srcdir)/docs/tutorial/figures/*.png $$USER@$(web_host):$(clutter_tut_path)/figures/
	rsync $(rsync_args) $(srcdir)/docs/tutorial/icons/*.png $$USER@$(web_host):$(clutter_tut_path)/icons/
	rsync $(rsync_args) -Cr docs/tutorial/html/ $$USER@$(web_host):$(clutter_tut_path)/html/
	rsync $(rsync_args) $(srcdir)/docs/tutorial/*.css $$USER@$(web_host):$(clutter_tut_path)/html/
	rsync $(rsync_args) -Cr docs/tutorial/pdf/ $$USER@$(web_host):$(clutter_tut_path)/pdf/
	rsync $(rsync_args) -Cr $(srcdir)/examples/ --exclude '*/example' $$USER@$(web_host):$(web_path)/examples/

# PDF Generation:

# we need to produce a version with full examples with all of the XIncludes done so that it
# can processed for PDF
docs/tutorial/programming-with-cluttermm.xml: docs/tutorial/cluttermm-tut-with-examples.xml
	rm -rf docs/tutorial/html
	mkdir docs/tutorial/html
	$(XMLLINT) --xinclude --postvalid -o $@ $<

# We have to generate the pdf in a subdirectory (e.g. pdf/) because the tutorial
# specifies the path to the figures as '../figures' so if we build it in this
# directory, it won't find the images.
docs/tutorial/pdf/programming-with-cluttermm.pdf: docs/tutorial/programming-with-cluttermm.xml
	$(DB2PDF) --output docs/tutorial/pdf $<

pdf-local: docs/tutorial/pdf/programming-with-cluttermm.pdf

html-local: docs/tutorial/html/index.html

doc-clean:
	-rm -rf docs/tutorial/html docs/tutorial/html_withcomments docs/tutorial/pdf
	-rm -f docs/tutorial/cluttermm-tut-with-examples.xml

clean-local: doc-clean

doc-rebuild: doc-clean html pdf

install-tutorial: docs/tutorial/html/index.html docs/tutorial/style.css
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(tutorialdir)
	@dir='$(<D)'; for p in $$dir/*.html ; do \
	  f=`echo "$$p" | sed -e 's|^.*/||'`; \
	  echo " $(INSTALL_DATA) $$p $(DESTDIR)$(tutorialdir)/$$f"; \
	  $(INSTALL_DATA) $$p $(DESTDIR)$(tutorialdir)/$$f; \
	done
	$(INSTALL_DATA) $(srcdir)/docs/tutorial/style.css $(DESTDIR)$(tutorialdir)

uninstall-tutorial: docs/tutorial/html/index.html docs/tutorial/style.css
	@$(NORMAL_UNINSTALL)
	@dir='$(<D)'; for p in $$dir/*.html ; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " rm -f $(DESTDIR)$(tutorialdir)/$$f"; \
	  rm -f $(DESTDIR)$(tutorialdir)/$$f; \
	done
	rm -f $(DESTDIR)$(tutorialdir)/style.css
	rm -rf $(DESTDIR)$(tutorialdir)/icons

all-local: html

install-data-local: install-tutorial

uninstall-local: uninstall-tutorial

maintainer-clean-local: doc-clean

.PHONY: post-html doc-clean doc-rebuild install-tutorial uninstall-tutorial validate validate-original
