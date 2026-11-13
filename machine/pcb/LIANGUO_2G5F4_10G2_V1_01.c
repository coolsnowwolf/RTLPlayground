#include "machine_defs.h"

/* Experimental 4+2 target, derived from the owner's 512 KiB stock dump.
 * GPIO/I2C values are recovered from code; front-panel order and the
 * RTL8372 identification still need hardware confirmation. See doc/devices/.
 */
__code const struct machine machine = {
	.machine_name = "Lianguo 2G5F4_10G2 V1.01",
	.n_sfp = 2,
	.flash_sio = 1,
	.n_10g = 0,
	.log_to_phys_port = {0, 0, 0, 6, 1, 2, 3, 4, 5},
	.phys_to_log_port = {4, 5, 6, 7, 8, 3, 0, 0, 0},
	.is_sfp = {0, 0, 0, 2, 0, 0, 0, 0, 1},
	// Assumed left slot: SDS1, ModAbs=GPIO30, RX_LOS=GPIO37.
	.sfp_port[0].pin_detect = GPIO30_ACL_BIT3_EN,
	.sfp_port[0].pin_los = GPIO37,
	.sfp_port[0].pin_tx_disable = GPIO_NA,
	.sfp_port[0].sds = 1,
	.sfp_port[0].i2c = I2CBUS(GPIO39_I2C_SDA4, GPIO40_I2C_SCL3_MDC1),
	// Assumed right slot: SDS0, ModAbs=GPIO50, RX_LOS=GPIO51.
	.sfp_port[1].pin_detect = GPIO50_I2C_SCL2_UART1_TX,
	.sfp_port[1].pin_los = GPIO51_I2C_SDA2_UART1_RX,
	.sfp_port[1].pin_tx_disable = GPIO_NA,
	.sfp_port[1].sds = 0,
	.sfp_port[1].i2c = I2CBUS(GPIO41_I2C_SDA3_MDIO1, GPIO40_I2C_SCL3_MDC1),
	.reset_pin = GPIO_NA,
	// Stock code sets mux bits 27/29, enables LED29 and disables LED27.
	// No confirmed SYS LED wiring: leave LED28 disabled in this trial build.
	.high_leds = { .mux = LED_27 | LED_29, .enable = LED_29 },
	// Stock boot code configures SET0 without changing the port-set selector.
	// Assume its hardware default is SET0 for all ports; verify on the board.
	.port_led_set = {0, 0, 0, 0, 0, 0, 0, 0, 0},
	.led_sets = {
		{
			// Reproduce 0x6548=0x0041017f and 0x6528[3:0]=0xf.
			0x000f017fUL,
			LEDS_2G5 | LEDS_LINK,
			// Stock 0x6544[15:0]=0x0044. Unused LED3 is disabled.
			LEDS_1G | LEDS_LINK,
			0,
		},
	},
	.led_mux_custom = 0,
	.mac_flash_offset = 0,
};
