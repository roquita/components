#include "selector_keypad.h"

void init_keypad(keypad_t* keypad){
	keypad->init();
}
uint16_t scan_keypad(keypad_t* keypad){
	
	uint16_t result = 0xffff;
	uint8_t rows = keypad->rows;
	uint8_t columns = keypad->columns;
	
	for( uint8_t i = 0; i < rows; i++ ){
		keypad->set_row_as_output_low(i);
		
		bool key_pressed = false;
		for( uint8_t j = 0; j < columns; j++){
			key_pressed = (keypad->get_column_value(j) == 0);
			if( key_pressed){
				result = (i << 8) + j;
				break;
			}
		}
		
		keypad->set_row_as_input(i);
		
		if( key_pressed){
			break;
		}
	}
	
	return result;
}
