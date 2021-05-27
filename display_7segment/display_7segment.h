#ifndef DISPLAY_7SEGMENT_H_
#define DISPLAY_7SEGMENT_H_

#include <stdbool.h>
#include <stdint.h>

typedef void(*seven_sgmt_print_fn)(uint8_t byte);
typedef void(*seven_sgmt_enable_fn)();
typedef void(*seven_sgmt_disable_fn)();

typedef struct{
	seven_sgmt_print_fn print;
	seven_sgmt_enable_fn enable;
	seven_sgmt_disable_fn disable;
}seven_sgmt_t;

#define seven_sgmt_print(seven_sgmt_t,value) (seven_sgmt_t.print(value))
#define seven_sgmt_enable(seven_sgmt_t) (seven_sgmt_t.enable())
#define seven_sgmt_disable(seven_sgmt_t) (seven_sgmt_t.disable())

#endif /* DISPLAY_7SEGMENT_H_ */