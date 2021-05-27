# Generic drivers
## What are generic drivers?
Software that allow us to control different devices (like keypads, lcd16x2 or hc50) using any base architecture(like avr, pic or arm).
## How to use them?
Just add them to your project(like any other standard library) and implement the base firmware that each one require. Take
next picture as a reference.

<img src="assets/implementation.png" width="50%"> </img>

## How they work? 
* Take "selector_keypad" as example.
* Any generic driver allow us to create generic objects:
```c
keypad_t my_generic_object;
```
* But they are incomplete, their function attributes(4 in this case) are not defined :
```c

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
```
* So the programmer should complete function attributes listed above to be able to use the keypad api:
```c
void init_keypad(keypad_t* keypad);
uint16_t scan_keypad(keypad_t* keypad);
``` 
* First attribute: "init_hardware init". Is a function that return "void" and receive "void" as a parameter.
```c
void my_keypad_init(){

}
``` 






