 /******************************************************************************
 * main.c
 *
 *
 *      Author: maria
 */
 /*******************************************************************************/
#include "keypad.h"
#include "DIO_Interface.h"
#include <util/delay.h>

/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/

#ifndef STANDARD_KEYPAD

#if (KEYPAD_NUM_COLS == 3)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x3 keypad
 */
static u8 KEYPAD_4x3_adjustKeyNumber(u8 button_number);
#elif (KEYPAD_NUM_COLS == 4)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x4 keypad
 */
static u8 KEYPAD_4x4_adjustKeyNumber(u8 button_number);
#endif

#endif /* STANDARD_KEYPAD */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

u8 KEYPAD_getPressedKey(void)
{
	u8 col,row;
	DIO_SetPinDir(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID, Input);
	DIO_SetPinDir(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+1, Input);
	DIO_SetPinDir(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+2, Input);
	DIO_SetPinDir(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+3, Input);

	DIO_SetPinDir(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID, Input);
	DIO_SetPinDir(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+1, Input);
	DIO_SetPinDir(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+2, Input);
	DIO_SetPinValue(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID, High);
		DIO_SetPinValue(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+1, High);
		DIO_SetPinValue(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+2,High);
#if(KEYPAD_NUM_COLS == 4)
	DIO_SetPinDir(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+3, Input);
	DIO_SetPinValue(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+3,High);
#endif
	while(1)
	{
		for(row=0 ; row<KEYPAD_NUM_ROWS ; row++) /* loop for rows */
		{
			/*
			 * Each time setup the direction for all keypad port as input pins,
			 * except this row will be output pin
			 */
			DIO_SetPinDir(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,Output);
			/* Set/Clear the row output pin */
			DIO_SetPinValue(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row, KEYPAD_BUTTON_PRESSED);

			for(col=0 ; col<KEYPAD_NUM_COLS ; col++) /* loop for columns */
			{
				u8 pin_value = 0;
				DIO_GetPinValue(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+col, &pin_value);
				/* Check if the switch is pressed in this column */
				if( pin_value== KEYPAD_BUTTON_PRESSED)
				{
					#if (KEYPAD_NUM_COLS == 3)
						#ifdef STANDARD_KEYPAD
							return ((row*KEYPAD_NUM_COLS)+col+1);
						#else
							return KEYPAD_4x3_adjustKeyNumber((row*KEYPAD_NUM_COLS)+col+1);
						#endif
					#elif (KEYPAD_NUM_COLS == 4)
						#ifdef STANDARD_KEYPAD
							return ((row*KEYPAD_NUM_COLS)+col+1);
						#else
							return KEYPAD_4x4_adjustKeyNumber((row*KEYPAD_NUM_COLS)+col+1);
						#endif
					#endif
				}
			}
			DIO_SetPinDir(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,Input);
		}
	}
}

#ifndef STANDARD_KEYPAD

#if (KEYPAD_NUM_COLS == 3)
/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x3 shape
 */
static u8 KEYPAD_4x3_adjustKeyNumber(u8 button_number)
{
	u8 keypad_button = 0;
	switch(button_number)
	{
		case 10: keypad_button = '*'; // ASCII Code of *
				 break;
		case 11: keypad_button = 0;
				 break;
		case 12: keypad_button = '#'; // ASCII Code of #
				 break;
		default: keypad_button = button_number;
				break;
	}
	return keypad_button;
}

#elif (KEYPAD_NUM_COLS == 4)

/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x4 shape
 */
static u8 KEYPAD_4x4_adjustKeyNumber(u8 button_number)
{
	u8 keypad_button = 0;
	switch(button_number)
	{
		case 1: keypad_button = '7';
				break;
		case 2: keypad_button = '8';
				break;
		case 3: keypad_button = '9';
				break;
		case 4: keypad_button = '/'; // ASCII Code of %
				break;
		case 5: keypad_button = '4';
				break;
		case 6: keypad_button = '5';
				break;
		case 7: keypad_button = '6';
				break;
		case 8: keypad_button = '*'; /* ASCII Code of '*' */
				break;
		case 9: keypad_button = '1';
				break;
		case 10: keypad_button = '2';
				break;
		case 11: keypad_button = '3';
				break;
		case 12: keypad_button = '-'; /* ASCII Code of '-' */
				break;
		case 13: keypad_button = reset();
				break;
		case 14: keypad_button = '0';
				break;
		case 15: keypad_button = '='; /* ASCII Code of '=' */
				break;
		case 16: keypad_button = '+'; /* ASCII Code of '+' */
				break;
		default: keypad_button = button_number;
				break;
	}
	return keypad_button;
}

#endif

#endif /* STANDARD_KEYPAD */
