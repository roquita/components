#ifndef EXPANDER_PCF8574_H_
#define EXPANDER_PCF8574_H_

/*
_gpio_mode_map: is a 8 bit(1 bit for each gpio) variable containing gpio mode of each gpio. "1" if input and "0" if output.
At power up, all gpio are in input mode, so only output_map is required at config. User no needs to set its value, is set by
mcu at run time.

output_map: is a 8 bit(1 bit for each gpio) variable containing a confirmation for output mode for each gpio. "1" if you want
that gpio like output and "0" the oposite. Needs to be set by user in code.
ex: output_map as "0b 0000 1111 0000 0001" means p00,p10,p11,p12,p13 like outputs and the rest by default like inputs.
ex equivalent of previous in code:
output_map = (P00 | P10 | P11 | P12 | P13 );

Pxy : means  Port x - Gpio y

Note: Remember that gpio mode is handled in software side, not by hardware.
Note: Analice gpio architecture to understant why it is called quasibidirectional. PCF8575 isnt push-pull nor open-drain.
Note: Take care about hardware design, this may affect status of gpio.
*/

#include "stdint.h"
#include "stdbool.h"

#define DEBUG_ENABLED false
#define P0_OUTPUT (P00 | P01 | P02 | P03 | P04 | P05 | P06 | P07)

typedef enum
{
	P00 = 1 << 0,
	P01 = 1 << 1,
	P02 = 1 << 2,
	P03 = 1 << 3,
	P04 = 1 << 4,
	P05 = 1 << 5,
	P06 = 1 << 6,
	P07 = 1 << 7,
} pcf8574_gpio_num_t;

typedef bool (*is_present_fn)(void);
typedef int (*i2c_read_fn)(uint8_t* port);
typedef int (*i2c_write_fn)(uint8_t port);

typedef struct
{
	is_present_fn is_present; //defined by user
	i2c_read_fn i2c_read; //defined by user
	i2c_write_fn i2c_write; //defined by user
	uint8_t output_map; // remember by default all gpios are input //defined by user
	uint8_t gpio_mode_map; // used in run-time, not defined by user
} pcf8574_t;

void pcf8574_init(pcf8574_t *pcf8574);
void pcf8574_gpio_set_level(pcf8574_t *pcf8574, pcf8574_gpio_num_t n, int level);
void pcf8574_gpio_toogle_level(pcf8574_t *pcf8574, pcf8574_gpio_num_t n);
int pcf8574_gpio_get_level(pcf8574_t *pcf8574, pcf8574_gpio_num_t n);
uint8_t pcf8574_print_gpios_status(pcf8574_t *pcf8574);

#endif /* EXPANDER_PCF8574_H_ */