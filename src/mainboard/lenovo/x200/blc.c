/* SPDX-License-Identifier: GPL-2.0-only */

#include <stdint.h>
#include <commonlib/helpers.h>
#include <console/console.h>
#include <northbridge/intel/gm45/gm45.h>
#include <device/pci.h>
#include <drivers/intel/gma/opregion.h>

static const struct blc_pwm_t blc_entries[] = {
	/* corrected to 320MHz CDClk, vendor set 753; works fine at both: */
	{"LTD121EQ3B", 447},
	{"LTD121EWVB", 165},
	{"LTD133EQ1B", 264},  /* Found on an X301 */
	{"B121EW03 V6 ", 165},
	/* datasheets: between 100 and 20k, typical 200 */
	/* TESTED: works best at 400 */
	{"B121EW09 V3 ", 400},
	{"HV121WX4-120", 110}, /* Aftermarket AFFS lcd, works well at low pwm */
	{"LTN121AT03001", 110},
	{"LTN121AT07L02", 750}, /* Its part name is LTN121AT07-L02 */
	{"LTN121AP03001", 750},
	/* TODO: untested panels found on thinkwiki */
	/* Generally CCFL runs best at lower PWM */
	/* {"B121EW09 V2 ", 450}, */
	/* {"N121IB-L05", 450}, */
	{"LP121WX3-TLC1", 400}, /* TESTED to work best at this value */
	/* {"LP121WX3-TLA1" 450}, */
	/* {"B121EW03 V3 " 110}, */
	/* {"LTN121AP02001" 110}, */
};

int get_blc_values(const struct blc_pwm_t **entries)
{
	*entries = blc_entries;
	return ARRAY_SIZE(blc_entries);
}

const char *mainboard_vbt_filename(void)
{
	struct device *gma = pcidev_path_on_root(PCI_DEVFN(0x2, 0));
	u16 pwm_freq = gma ? get_blc_pwm_freq_value(gm45_get_lvds_edid_str(gma)) : 0;

	if (pwm_freq == 0) {
		printk(BIOS_DEBUG,
		       "GMA: Display backlight type not found, assuming LED\n");
		return "data_led.vbt";
	} else if (pwm_freq > 200) {
		printk(BIOS_DEBUG, "GMA: Using LED backlight VBT\n");
		return "data_led.vbt";
	} else {
		printk(BIOS_DEBUG, "GMA: Using CCFL backlight VBT\n");
		return "data_ccfl.vbt";
	}
}
