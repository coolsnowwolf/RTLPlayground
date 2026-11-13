#include "machine_init_defs.h"

// Preserve unrelated fields; reproduce the working reference's low LED pins.
void machine_custom_init(void) __banked
{
	reg_read_m(RTL837X_REG_LED_GLB_IO_EN);
	sfr_mask_data(0, 0xff, 0);
	sfr_mask_data(1, 0x01, 0);
	reg_write_m(RTL837X_REG_LED_GLB_IO_EN);
	reg_read_m(RTL837X_PIN_MUX_0);
	sfr_mask_data(0, 0xff, 0xff);
	sfr_mask_data(1, 0x01, 0x01);
	reg_write_m(RTL837X_PIN_MUX_0);
}
