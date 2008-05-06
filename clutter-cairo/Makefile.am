SUBDIRS		= src cluttermm-cairo

EXTRA_DIST	= README					\
		  cluttermm-cairo-config.h.in cluttermm-cairo.h	\
		  cluttermm-cairo.pc.in

cluttermm_includedir		= $(includedir)/cluttermm-cairo-$(API_VER)
cluttermm_include_HEADERS	= cluttermm-cairo.h

cluttermm_configdir		= $(libdir)/cluttermm-cairo-$(API_VER)/include
cluttermm_config_DATA	= cluttermm-cairo-config.h

pkgconfigdir		= $(libdir)/pkgconfig
pkgconfig_DATA		= cluttermm-cairo-$(API_VER).pc
DISTCLEANFILES = $(pkgconfig_DATA)
