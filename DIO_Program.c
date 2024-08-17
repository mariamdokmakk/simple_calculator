#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "DIO_Private.h"

void DIO_SetPinDir(u8 port, u8 pin, u8 dir)
{
    if(dir == Input)
    {
        if (port == Port_A)
            CLR_BIT(DDRA, pin);
        else if (port == Port_B)
            CLR_BIT(DDRB, pin);
        else if (port == Port_C)
            CLR_BIT(DDRC, pin);
        else if (port == Port_D)
            CLR_BIT(DDRD, pin);
    }

    else if(dir == Output)
    {
        if (port == Port_A)
            SET_BIT(DDRA, pin);
        else if (port == Port_B)
            SET_BIT(DDRB, pin);
        else if (port == Port_C)
            SET_BIT(DDRC, pin);
        else if (port == Port_D)
            SET_BIT(DDRD, pin);
    }
}

void DIO_SetPinValue(u8 port, u8 pin, u8 value)
{
    if (value == Low)
    {
        if (port == Port_A)
            CLR_BIT(PORTA, pin);
        else if (port == Port_B)
            CLR_BIT(PORTB, pin);
        else if (port == Port_C)
            CLR_BIT(PORTC, pin);
        else if (port == Port_D)
            CLR_BIT(PORTD, pin);
    }

    else if (value == High)
    {
        if (port == Port_A)
            SET_BIT(PORTA, pin);
        else if (port == Port_B)
            SET_BIT(PORTB, pin);
        else if (port == Port_C)
            SET_BIT(PORTC, pin);
        else if (port == Port_D)
            SET_BIT(PORTD, pin);
    }
}

void DIO_GetPinValue(u8 port, u8 pin, u8* value)
{
	switch (port)
	    {
	    case Port_A:
	        *value = GET_BIT(PINA, pin);
	        break;

	    case Port_B:
	        *value = GET_BIT(PINB, pin);
	        break;

	    case Port_C:
	        *value = GET_BIT(PINC, pin);
	        break;

	    case Port_D:
	        *value = GET_BIT(PIND, pin);
	        break;
	    }

}

void DIO_SetPortDir(u8 port, u8 dir)
{
    if (dir == Input)
    {
        if(port == Port_A)
            DDRA = 0x00;
        else if (port == Port_B)
            DDRB = 0x00;
        else if (port == Port_C)
            DDRC = 0x00;
        else if (port == Port_D)
            DDRD = 0x00;
    }

    if (dir == Output)
    {
        if (port == Port_A)
            DDRA = 0xff;
        else if (port == Port_B)
            DDRB = 0xff;
        else if (port == Port_C)
            DDRC = 0xff;
        else if (port == Port_D)
            DDRD = 0xff;
    }
}

void DIO_SetPortValue(u8 port, u8 value)
{
    if (port == Port_A)
        PORTA = value;
    else if (port == Port_B)
        PORTB = value;
    else if (port == Port_C)
        PORTC = value;
    else if (port == Port_D)
        PORTD = value;
}

void DIO_GetPortValue(u8 port, u8 *value)
{
    if (port == Port_A)
        *value = PINA;
    else if (port == Port_B)
        *value = PINB;
    else if (port == Port_C)
        *value = PINC;
    else if (port == Port_D)
        *value = PIND;
}
