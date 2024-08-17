/*
 * main.c
 *
 *  Created on: Jul 8, 2024
 *      Author: maria
 */
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "DIO_Interface.h"
#include "keypad.h"

int is_digit(u8 key);
int is_operator(u8 key);
int calculate(s16 op1, s16 op2, u8 operator);
void reset(void);
void LCD_moveCursorLeft(void) {
    LCD_sendCommand(LCD_MOVE_CURSOR_LEFT);
}

 u16 op1 = 0,count_op1=0,count_op2=0, op2 = 0;
 u8 operator = 0;
 u8 last_key = '\0';
 u8 flag = 0; //flag for op1,op2
 u16 sign1 = 1, sign2 = 1; // Sign for op1 and op2
 u8 key;
 void reset(void) {
     LCD_sendCommand(LCD_CLEAR_COMMAND);
     op1 = 0;
     op2 = 0;
     operator = 0;
     last_key = '\0';
     sign1 = 1;
     sign2 = 1;
     flag=0;
     count_op1=0;count_op2=0;
     _delay_ms(200);
 }

ISR(INT0_vect) {

   reset();
}

ISR(INT1_vect) {

    if (last_key != '\0') { //when any button is pressed

if(flag==0&&count_op1>0){
    if(sign1==-1){
	   LCD_moveCursorLeft();
       LCD_displayCharacter(' '); // Overwrite with space
       LCD_moveCursorLeft();
	   sign1=1;}
    if(count_op1>0){
	   op1=op1/10;
	   LCD_moveCursorLeft();
	   LCD_displayCharacter(' '); // Overwrite with space
	   LCD_moveCursorLeft();
	   count_op1--;}

}

else if(flag==1&&count_op2>0){
	if(sign2==-1){
	   LCD_moveCursorLeft();
       LCD_displayCharacter(' '); // Overwrite with space
       LCD_moveCursorLeft();
	   sign2=1;}
	if(count_op2>0){
		op2=op2/10;
		LCD_moveCursorLeft();
		LCD_displayCharacter(' '); // Overwrite with space
		LCD_moveCursorLeft();
		count_op2--;

		}
}
else if((operator=='-'||operator=='+'||operator=='*'||operator=='/')&&count_op2==0){
	LCD_moveCursorLeft();
	LCD_displayCharacter(' '); // Overwrite with space
	LCD_moveCursorLeft();
	operator='0';
	flag=0;

}

 _delay_ms(200);
    }
}

int main(void) {

    // Initialize the LCD
    LCD_init();

    DIO_SetPinDir(Port_D, Pin2, Input);
    DIO_SetPinValue(Port_D, Pin2, High); // internal pull up resistance

    DIO_SetPinDir(Port_D, Pin3, Input);
    DIO_SetPinValue(Port_D, Pin3, High); // internal pull up resistance

    MCUCR |= (1 << ISC01); // INT0 on falling edge
    MCUCR &= ~(1 << ISC00);

    MCUCR |= (1 << ISC11); //  INT1 on falling edge
    MCUCR &= ~(1 << ISC10);

    GICR |= (1 << INT0);   // Enable INT0
    GICR |= (1 << INT1);   // Enable INT1

    sei(); // Enable global interrupts

    while (1) {
        key = KEYPAD_getPressedKey();
        if ( key != '=') {
            LCD_displayCharacter(key);

            if (is_digit(key) && flag == 0) {
                op1 = op1 * 10 + (key - '0');
                count_op1++;
                last_key = key;
            } else if (is_operator(key) && flag == 0) {
                if (key == '-' && op1 == 0) {
                    sign1 = -1;
                } else {
                    operator = key;
                    flag = 1; // Switch to entering op2

                }
                last_key = key;
            }

             else if (is_operator(key) && flag == 1 ) {
            		    if(key=='-'&&op2==0){
            		    sign2=-1; }

                        else{
                        	//Assign result in op1 to make another operation
            	        op1 = calculate(op1 * sign1, op2 * sign2, operator);
            	       // Display result
            	      LCD_sendCommand(LCD_CLEAR_COMMAND);
            	      LCD_intgerToString(op1);
            	      operator = key;
            	      //display the other operator for the operation
            	      LCD_displayCharacter(key);
            	      op2 = 0;//reset the variable for second operand
            	      sign2 = 1;
            	      last_key = key;
            	      _delay_ms(200);
            	            }
              last_key = key;
            }
            else if (is_digit(key) && flag == 1) {
                op2 = op2 * 10 + (key - '0');
                last_key = key;
                count_op2++;
            }
            _delay_ms(200);
        }

        if (key == '=') { // Calculate result when = is pressed
            if (operator != 0) {
            	if (operator == '/' && op2 == 0) {
            	                    // Handle division by zero
            	    LCD_sendCommand(LCD_CLEAR_COMMAND);
            	     LCD_displayString("Infinity");
            	      _delay_ms(500);
            	       reset();
            	                }
            	else{
            		int result = calculate(op1 * sign1, op2 * sign2, operator);

                LCD_sendCommand(LCD_CLEAR_COMMAND);
                LCD_intgerToString(result) ;// Convert result to string

                op1 = result;
                // Reset variables
                op2 = 0;
                count_op2=0;
                operator = 0;
                key='0';
                last_key = '\0';
                flag = 0;
                sign1 = 1;
                sign2 = 1;
                _delay_ms(200);}
            }
        }
    }
}

int is_digit(u8 key) {
    return key >= '0' && key <= '9';
}

int is_operator(u8 key) {
    return key == '+' || key == '-' || key == '*' || key == '/';
}

int calculate(s16 op1, s16 op2, u8 operator) {
    switch (operator) {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '/': return op1 / op2;
        case '*': return op1 * op2;
        default: return 0;
    }
}
