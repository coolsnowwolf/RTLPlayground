#define MACHINE_CHIPSET RTL8372
#include "machine_defs.h"

/* GPIO/I2C/LED settings recovered from SR-S25G2206F_NOR.bin, which the owner
 * reports working on RTL-4GT-2S+ V1.03. Front-panel order and the new image
 * still need hardware confirmation. See doc/devices/.
 */
__code const struct machine machine = {
	MACHINE_COMMON_SETTING,
	.n_sfp = 2,
	.flash_sio = 1,
	.n_10g = 0,
	.log_to_phys_port = {0, 0, 0, 6, 1, 2, 3, 4, 5},
	.phys_to_log_port = {4, 5, 6, 7, 8, 3, 0, 0, 0},
	.is_sfp = {0, 0, 0, 2, 0, 0, 0, 0, 1},
	.sfp_port[0].pin_detect = GPIO30_ACL_BIT3_EN,
	.sfp_port[0].pin_los = GPIO37,
	.sfp_port[0].pin_tx_disable = GPIO_NA,
	.sfp_port[0].sds = 1,
	.sfp_port[0].i2c = I2CBUS(GPIO39_I2C_SDA4, GPIO40_I2C_SCL3_MDC1),
	.sfp_port[1].pin_detect = GPIO50_I2C_SCL2_UART1_TX,
	.sfp_port[1].pin_los = GPIO51_I2C_SDA2_UART1_RX,
	.sfp_port[1].pin_tx_disable = GPIO_NA,
	.sfp_port[1].sds = 0,
	.sfp_port[1].i2c = I2CBUS(GPIO41_I2C_SDA3_MDIO1, GPIO40_I2C_SCL3_MDC1),
	.reset_pin = GPIO_NA,
	.high_leds = { .mux = LED_27 | LED_29, .enable = LED_29 },
	.port_led_set = {0, 0, 0, 1, 0, 0, 0, 0, 1},
	.led_sets = {
		// OEM SET0: 0x6548=0x0041017f; 0x6544[15:0]=0x0044.
		{0x000f017fUL, LEDS_2G5 | LEDS_LINK, LEDS_1G | LEDS_LINK, 0},
		// OEM SET1: 0x6540=0x0040017f; 0x653c[15:0]=0x0044.
		// 10G flag lives in 0x6528; combined extended fields are 0x001f000f.
		{0x000f017fUL, LEDS_10G | LEDS_LINK, LEDS_1G | LEDS_LINK, 0},
	},
	.led_mux_custom = 0,
	.mac_flash_offset = 0,
};

// Preserve unrelated fields; reproduce the working reference's low LED pins.
MACHINE_CUSTOM_INIT(
	reg_read_m(RTL837X_REG_LED_GLB_IO_EN);
	sfr_mask_data(0, 0xff, 0);
	sfr_mask_data(1, 0x01, 0);
	reg_write_m(RTL837X_REG_LED_GLB_IO_EN);
	reg_read_m(RTL837X_PIN_MUX_0);
	sfr_mask_data(0, 0xff, 0xff);
	sfr_mask_data(1, 0x01, 0x01);
	reg_write_m(RTL837X_PIN_MUX_0);
)
