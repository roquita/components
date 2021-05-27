
#include "bluetooth_hc06.h"

void hc06_init(hc06_t* hc06){
	
}
void hc06_print_string(hc06_t* hc06, char* string){
	while( *string != 0){
		hc06->print_char(*string);
		string++;
	}	
};
void hc06_print_fmt(hc06_t* hc06, const char* fmt, ...){
	char buffer[100];
	
	va_list args;
	va_start(args,fmt);
	vsprintf(buffer, fmt, args);
	hc06_print_string(hc06, buffer);
	va_end(args);	
};