#ifndef SELECTOR_KEYPAD_H_
#define SELECTOR_KEYPAD_H_

#include "stdint.h"
#include "stdbool.h"

typedef void (* init_hardware)(void);                    //set by user
typedef void (*set_row_as_input_fn)(uint8_t row);        //set by user
typedef void (*set_row_as_output_low_fn)(uint8_t row);   //set by user
typedef uint8_t (*get_column_value_fn)(uint8_t column);  //set by user

typedef struct {
    uint8_t rows;
    uint8_t columns;
    init_hardware init;
    set_row_as_input_fn set_row_as_input;
    set_row_as_output_low_fn set_row_as_output_low;
    get_column_value_fn get_column_value;
} keypad_t;

void init_keypad(keypad_t* keypad);
uint16_t scan_keypad(keypad_t* keypad);

#endif /* SELECTOR_KEYPAD_H_ */