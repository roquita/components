#ifndef BLUETOOTH_HC06_H_
#define BLUETOOTH_HC06_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef enum{
	HC06_READ_OK,
	HC06_READ_NO_BYTES
}hc06_read_error_t;

typedef void (*bluetooth_hc06_print_char)(char c);
typedef void (*bluetooth_hc06_echo)(void);
typedef int (*bluetooth_hc06_bytes_available)(void);
typedef hc06_read_error_t (*bluetooth_hc06_read_byte)(uint8_t* byte);
typedef void (*bluetooth_hc06_key_set_level)(int level);
typedef int (*bluetooth_hc06_state_get_level)();
typedef void (*bluetooth_hc06_delay_ms)(int ms);

typedef struct{
	bluetooth_hc06_print_char print_char;
	bluetooth_hc06_echo echo;
	bluetooth_hc06_bytes_available bytes_available;
	bluetooth_hc06_read_byte read_byte;
	bluetooth_hc06_key_set_level key_set_level;
	bluetooth_hc06_state_get_level state_get_level;
	bluetooth_hc06_delay_ms delay_ms;
}hc06_t;

void hc06_init(hc06_t*);
void hc06_print_string(hc06_t*, char* str);
void hc06_print_fmt(hc06_t*, const char* fmt, ...);
#define hc06_echo(hc06_t) (hc06_t.echo())
#define hc06_bytes_available(hc06_t) (hc06_t.bytes_available())
#define hc06_read_byte(hc06_t, p_byte) (hc06_t.read_byte(p_byte))
#define hc06_is_paired(hc06_t) (hc06_t.state_get_level() == 1)
#define hc06_software_reset(hc06_t) do \
{\
	hc06_t.key_set_level(0);\
	hc06_t.delay_ms(1);\
	hc06_t.key_set_level(1);\
	hc06_t.delay_ms(50);\
	hc06_print_string(&hc06_t,"AT+RESET\r\n");\
	hc06_t.delay_ms(50);\
	hc06_t.key_set_level(0);\
	hc06_t.delay_ms(1);\
} while (0);
#define hc06_fabric_config(hc06_t) do \
{\
	hc06_t.key_set_level(0);\
	hc06_t.delay_ms(1);\
	hc06_t.key_set_level(1);\
	hc06_t.delay_ms(50);\
	hc06_print_string(&hc06_t,"AT+ORGL\r\n");\
	hc06_t.delay_ms(50);\
	hc06_t.key_set_level(0);\
	hc06_t.delay_ms(1);\
} while (0);
#define hc06_link(hc06_t, mac) do \
{\
	hc06_t.key_set_level(0);\
	hc06_t.delay_ms(1);\
	hc06_t.key_set_level(1);\
	hc06_t.delay_ms(50);\
	hc06_print_fmt(&hc06_t,"AT+LINK=%s\r\n",mac);\
	hc06_t.delay_ms(50);\
	hc06_t.key_set_level(0);\
	hc06_t.delay_ms(1);\
} while (0);
#define hc06_unlink(hc06_t) do \
{\
	hc06_t.key_set_level(0);\
	hc06_t.delay_ms(1);\
	hc06_t.key_set_level(1);\
	hc06_t.delay_ms(50);\
	hc06_print_fmt(&hc06_t,"AT+DISC\r\n");\
	hc06_t.delay_ms(50);\
	hc06_t.key_set_level(0);\
	hc06_t.delay_ms(1);\
} while (0);
#endif /* BLUETOOTH_HC06_H_ */