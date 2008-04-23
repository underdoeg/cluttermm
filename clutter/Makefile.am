SUBDIRS		= src cluttermm

EXTRA_DIST	= README					\
		  cluttermmconfig.h.in cluttermm.h	\
		  cluttermm.pc.in

cluttermm_includedir		= $(includedir)/cluttermm-$(API_VER)
cluttermm_include_HEADERS	= cluttermm.h

cluttermm_configdir		= $(libdir)/cluttermm-$(API_VER)/include
cluttermm_config_DATA	= cluttermmconfig.h

pkgconfigdir		= $(libdir)/pkgconfig
pkgconfig_DATA		= cluttermm-$(API_VER).pc

