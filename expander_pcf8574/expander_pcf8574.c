#include "expander_pcf8574.h"

#define nBIT(port, bit) ((port >> bit) & 0b1)
#define PCF8574_ERR_CHECK(x)  (x)

static bool PCF8574_GPIO_MODE_MAP_CHECK(pcf8574_t *pcf8574, pcf8574_gpio_num_t n){
	if (  (pcf8574->gpio_mode_map & n) != 0)
	{
		#if DEBUG_ENABLED
		printf( "gpio:%u is in input mode. Setting new value rejected.", n);
		#endif

		return false;
	}
	return true;
}

void pcf8574_init(pcf8574_t *pcf8574)
{
	// define local variables
	uint8_t gpio_mode_map = 0xFF & ~(pcf8574->output_map);
	pcf8574->gpio_mode_map = gpio_mode_map;

	// set gpio mode
	// all outputs will be set LOW
	PCF8574_ERR_CHECK(pcf8574->i2c_write(gpio_mode_map));

	#if DEBUG_ENABLED
	// print gpio configuration
	uint8_t port0 = gpio_mode_map;
	
	printf(" ---  PCF8574 input(1)/output(0) map  ---  \n");
	printf("p07 p06 p05 p04 p03 p02 p01 p00\n");
	printf(" %d   %d   %d   %d   %d   %d   %d   %d  \n\n",
	nBIT(port0, 7), nBIT(port0, 6), nBIT(port0, 5), nBIT(port0, 4), nBIT(port0, 3), nBIT(port0, 2), nBIT(port0, 1), nBIT(port0, 0));
	#endif
}

void pcf8574_gpio_set_level(pcf8574_t *pcf8574, pcf8574_gpio_num_t n, int level)
{
	// verify n is output pin
	PCF8574_GPIO_MODE_MAP_CHECK(pcf8574, n);

	// read ports
	uint8_t status;
	PCF8574_ERR_CHECK(pcf8574->i2c_read(&status));

	// hold inputs like inputs
	status |= (pcf8574->gpio_mode_map);

	// set new value
	if (level == 1)
	{
		status |= n;
	}
	else
	{
		status &= ~n;
	}

	PCF8574_ERR_CHECK(pcf8574->i2c_write(status));
}
void pcf8574_gpio_toogle_level(pcf8574_t *pcf8574, pcf8574_gpio_num_t n)
{
	// verify n is output pin
	PCF8574_GPIO_MODE_MAP_CHECK(pcf8574, n);

	// read ports
	uint8_t status;
	PCF8574_ERR_CHECK(pcf8574->i2c_read(&status));

	// hold inputs like inputs
	status |= (pcf8574->gpio_mode_map);

	// toogle gpio level
	status ^= n;

	// write ports
	PCF8574_ERR_CHECK(pcf8574->i2c_write(status));
}
int pcf8574_gpio_get_level(pcf8574_t *pcf8574, pcf8574_gpio_num_t n)
{
	// read ports
	uint8_t status = 0xFF;
	PCF8574_ERR_CHECK(pcf8574->i2c_read(&status));

	// get bit value
	return (status & n) ? 1 : 0;
}

uint8_t pcf8574_print_gpios_status(pcf8574_t *pcf8574)
{
	uint8_t status;
	PCF8574_ERR_CHECK(pcf8574->i2c_read(&status));	
	
	#if DEBUG_ENABLED
	uint8_t port0 = status;
	
	printf(" ---  PCF8574 gpio status  ---  \n");
	printf("p10 p07 p06 p05 p04 p03 p02 p01 p00\n");
	printf(" %d   %d   %d   %d   %d   %d   %d   %d  \n\n",
	nBIT(port0, 7), nBIT(port0, 6), nBIT(port0, 5), nBIT(port0, 4), nBIT(port0, 3), nBIT(port0, 2), nBIT(port0, 1), nBIT(port0, 0));
	#endif
	
	return status;
}