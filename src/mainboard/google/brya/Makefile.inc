bootblock-y += bootblock.c

verstage-$(CONFIG_CHROMEOS) += chromeos.c

romstage-$(CONFIG_CHROMEOS) += chromeos.c
romstage-y += romstage.c
romstage-$(CONFIG_MAINBOARD_USE_EARLY_LIBGFXINIT) += gma-mainboard.ads

ramstage-$(CONFIG_CHROMEOS) += chromeos.c
ramstage-y += mainboard.c
ramstage-y += ec.c

BASEBOARD_DIR:=$(call strip_quotes,$(CONFIG_BASEBOARD_DIR))

subdirs-y += variants/baseboard/$(BASEBOARD_DIR)
subdirs-y += variants/$(VARIANT_DIR)
subdirs-y += variants/$(VARIANT_DIR)/memory
subdirs-$(CONFIG_HAVE_SPD_IN_CBFS) += spd

CPPFLAGS_common += -I$(src)/mainboard/$(MAINBOARDDIR)/variants/baseboard/include
CPPFLAGS_common += -I$(src)/mainboard/$(MAINBOARDDIR)/variants/baseboard/$(BASEBOARD_DIR)/include
CPPFLAGS_common += -I$(src)/mainboard/$(MAINBOARDDIR)/variants/$(VARIANT_DIR)/include
