#ifndef DRIVER_MAX7219_H_
#define DRIVER_MAX7219_H_

#include <stdbool.h>
#include <stdint.h>

typedef enum{
	NO_OP_REG ,DIG0_REG ,DIG1_REG,DIG2_REG ,
	DIG3_REG ,DIG4_REG ,DIG5_REG ,DIG6_REG ,
	DIG7_REG ,
	DECODE_MODE_REG ,
	INTENSITY_REG ,
	SCAN_LIMIT_REG ,
	SHUTDOWN_REG ,
	DISPLAY_TEST_REG = 0xF
}max7219_reg_t;
typedef enum {
	SHUTDOWN_MODE,ACTIVE_MODE
}max7219_power_mode_t;
typedef enum {
	NO_DECODE,
	DIGITS_0_DECODED,
	DIGITS_3210_DECODED = 0xF,
	ALL_DIGITS_DECODED = 0xFF
}max7219_decode_mode_t;
typedef enum{
	STD_0_CHAR = 0b01111110,
	STD_1_CHAR = 0b00110000,
	STD_2_CHAR = 0b01101101,
	STD_3_CHAR = 0b01111001,
	STD_4_CHAR = 0b00110011,
	STD_5_CHAR = 0b01011011,
	STD_6_CHAR = 0b01011111,
	STD_7_CHAR = 0b01110000,
	STD_8_CHAR = 0b01111111,
	STD_9_CHAR = 0b01111011,
	STD___CHAR = 0b00000001,
	STD_E_CHAR = 0b01001111,
	STD_H_CHAR = 0b00110111,
	STD_L_CHAR = 0b00001110,
	STD_P_CHAR = 0b01100111,
	STD_BLANK_CHAR = 0b00000000
}max7219_std_char_t;
typedef enum{
	BCD_0_CHAR ,BCD_1_CHAR ,BCD_2_CHAR ,BCD_3_CHAR ,
	BCD_4_CHAR ,BCD_5_CHAR ,BCD_6_CHAR ,BCD_7_CHAR ,
	BCD_8_CHAR ,BCD_9_CHAR ,BCD___CHAR ,BCD_E_CHAR ,
	BCD_H_CHAR ,BCD_L_CHAR ,BCD_P_CHAR ,BCD_BLANK_CHAR
}max7219_bcd_char_t;
typedef enum{
	DUTY_1_32, DUTY_3_32,DUTY_5_32,DUTY_7_32,DUTY_9_32,
	DUTY_11_32,DUTY_13_32,DUTY_15_32,DUTY_17_32,DUTY_19_32,
	DUTY_21_32,DUTY_23_32,DUTY_25_32,DUTY_27_32,DUTY_29_32,
	DUTY_31_32,
}max7219_intensity_t;
typedef enum{
	ENABLE_DIG_0,
	ENABLE_DIG_01,
	ENABLE_DIG_012,
	ENABLE_DIG_0123,
	ENABLE_DIG_01234,
	ENABLE_DIG_012345,
	ENABLE_DIG_0123456,
	ENABLE_DIG_01234567,
}max7219_scan_limit_t;
typedef enum{
	NORMAL_OP_MODE,TEST_OP_MODE
}max7219_operation_mode_t;

typedef void (*max7219_send_cmd)(uint8_t addr, uint8_t data);

typedef struct{
	max7219_send_cmd send_cmd;
}max7219_t;

#define max7219_set_operation_mode(max7219_t,max7219_operation_mode_t) {max7219_t.send_cmd(DISPLAY_TEST_REG, max7219_operation_mode_t);}
#define max7219_set_scan_limit(max7219_t,max7219_scan_limit_t) {max7219_t.send_cmd(SCAN_LIMIT_REG, max7219_scan_limit_t);}
#define max7219_set_intensity(max7219_t,max7219_intensity_t) {max7219_t.send_cmd(INTENSITY_REG, max7219_intensity_t);}
#define max7219_set_decode_mode(max7219_t,max7219_decode_mode_t) {max7219_t.send_cmd(DECODE_MODE_REG, max7219_decode_mode_t);}
#define max_7219_set_power_mode(max7219_t,max7219_power_mode_t) {max7219_t.send_cmd(SHUTDOWN_REG, max7219_power_mode_t);}
#define max7219_set_std_digit(max7219_t,digit_reg,max7219_std_char_t) {max7219_t.send_cmd(digit_reg, max7219_std_char_t);}
#define max7219_set_bcd_digit(max7219_t,digit_reg,max7219_bcd_char_t) {max7219_t.send_cmd(digit_reg, max7219_bcd_char_t);}

#endif /* DRIVER_MAX7219_H_ */