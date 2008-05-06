SUBDIRS		= src cluttermm-gtk

EXTRA_DIST	= README					\
		  cluttermm-gtk-config.h.in cluttermm-gtk.h	\
		  cluttermm-gtk.pc.in

cluttermm_includedir		= $(includedir)/cluttermm-gtk-$(API_VER)
cluttermm_include_HEADERS	= cluttermm-gtk.h

cluttermm_configdir		= $(libdir)/cluttermm-gtk-$(API_VER)/include
cluttermm_config_DATA	= cluttermm-gtk-config.h

pkgconfigdir		= $(libdir)/pkgconfig
pkgconfig_DATA		= cluttermm-gtk-$(API_VER).pc
DISTCLEANFILES = $(pkgconfig_DATA)


