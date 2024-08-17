#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H
#include "STD_TYPES.h"

typedef enum
{
    Pin0,
    Pin1,
    Pin2,
    Pin3,
    Pin4,
    Pin5,
    Pin6,
    Pin7
} et_pin;

typedef enum
{
    Port_A,
Port_B,
    Port_C,
    Port_D
}et_port;

typedef enum
{
    Input,
    Output
} et_dir;

typedef enum
{
    Low,
    High
} et_value;

void DIO_SetPinDir(u8 port, u8 pin, u8 dir);
void DIO_SetPinValue(u8 port, u8 pin, u8 value);
void DIO_GetPinValue(u8 port, u8 pin, u8* value);

void DIO_SetPortDir(u8 port, u8 dir);
void DIO_SetPortValue(u8 port, u8 value); 
void DIO_GetPortValue(u8 port, u8 *value);

#endif
