/******************************************************************************

 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "STD_TYPES.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define KEYPAD_NUM_COLS                   4
#define KEYPAD_NUM_ROWS                   4

/* Keypad Port Configurations */
#define KEYPAD_ROW_PORT_ID                Port_B
#define KEYPAD_FIRST_ROW_PIN_ID           Pin0

#define KEYPAD_COL_PORT_ID                Port_B
#define KEYPAD_FIRST_COL_PIN_ID           Pin4

/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED            Low
#define KEYPAD_BUTTON_RELEASED           High

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Get the Keypad pressed button
 */
u8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
