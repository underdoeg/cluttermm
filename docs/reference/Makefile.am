
doxygen_configfile = Doxyfile

EXTRA_DIST	= README $(doxygen_configfile)


include $(top_srcdir)/docs/Makefile_web.am_fragment
web_path_reference = $(web_path_docs)reference

cluttermm-reference: $(doxygen_configfile)
	doxygen $(doxygen_configfile)

cluttermm-reference-html: cluttermm-reference

cluttermm-reference-html.tar.gz: cluttermm-reference-html
	tar -cf - $< | gzip > $@

post-html: html/index.html
	rsync $(rsync_args) -r html/ $$USER@$(web_host):$(web_path_reference)/html/

all-local: cluttermm-reference

clean-local:
	-rm -rf html
	-rm -f cluttermm-reference-html.tar.gz

