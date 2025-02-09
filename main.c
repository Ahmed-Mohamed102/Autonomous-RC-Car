/*
 * main.c
 *
 *  Created on: Sep 25, 2024
 *      Author: ahmed
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "GI_interface.h"
#include "TIMER0_interface.h"
#include "TIMER1_interface.h"
#include "TIMER2_interface.h"
#include "ANALOG_interface.h"
#include "UART_interface.h"
#include "TWI_interface.h"
#include "US_interface.h"
#include "SERVO_interface.h"
#include "CLCD_interface.h"
#include "EEPROM_interface.h"
#include <util/delay.h>

#define BLUETOOTH     1
#define ULTRASONIC    0

void SWITCH(void);

// Directions Flag
u8 ForwardFlag=0;
u8 CaseFlag=0;
u8 Local_u8Controler='f';
u8 WDTFLAG=0;
u8 SPEEDCARRIER=0;
u8 OBSTECLSNUM=0;
u8 SPEEDCARRIER_B=0;

f64 Global_f64ForwardTime=0;
f64 Global_f64RightTime=0;
f64 Global_f64LeftTime=0;

f32 Global_f32ForwardDistance=0;
f32 Global_f32RightDistance=0;
f32 Global_f32LeftDistance=0;
f32 Global_f32LastForwardDistance=0;
void Display(void)
{
	CLCD_voidClearDisplay();
	switch(CaseFlag)
	{
	case BLUETOOTH:
	{
		CLCD_voidSendString("BLUETOOTH");
		break;
	}
	case ULTRASONIC:
	{
		CLCD_voidSendString("ULTRASONIC");
		break;
	}
	}
	CLCD_voidSetPosition(0,11);
	CLCD_voidSendString("SP:");
	if(CaseFlag==BLUETOOTH)
	{
		CLCD_voidSendNum(SPEEDCARRIER_B);
	}
	else
	{
	CLCD_voidSendNum(SPEEDCARRIER);
	}
	CLCD_voidSetPosition(1,0);
	CLCD_voidSendString("OBS:");
	CLCD_voidSendNum(OBSTECLSNUM);
}
void Forward(void)
{
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_LOW);
	ANALOG_voidSendSignal(PORT_u8B,PIN_7,10);
	SPEEDCARRIER=10;
	EEPROM_voidWriteDataByte(DEVICE1,10,SPEEDCARRIER);
	ForwardFlag = 1;
	Display();
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_LOW);

}
void Forward_BLUE(void)
{
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_LOW);
}
void Stop(void)
{
	DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_LOW);
	//ForwardFlag=0;
	ForwardFlag=0;
	SPEEDCARRIER=0;
	EEPROM_voidWriteDataByte(DEVICE1,20,SPEEDCARRIER);
	Display();
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_LOW);

}
void Stop_BLUE(void)
{
	DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_LOW);

}
void Back(void)
{
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_LOW);
	ANALOG_voidSendSignal(PORT_u8B,PIN_7,8);
	SPEEDCARRIER=8;
	EEPROM_voidWriteDataByte(DEVICE1,30,SPEEDCARRIER);
	Display();
	Global_f32LastForwardDistance=Global_f32ForwardDistance;
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_HIGH);
	while(Global_f32ForwardDistance < Global_f32LastForwardDistance+3)
	{
		US_voidGetDistance(PORT_u8B,PIN_1,&Global_f64ForwardTime);
		Global_f32ForwardDistance=0.0175*Global_f64ForwardTime;
	}
}
void Back_BLUE(void)
{
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_HIGH);

	DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_HIGH);
}
void Right(void)
{
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_HIGH);
	ANALOG_voidSendSignal(PORT_u8B,PIN_7,7);
	SPEEDCARRIER=7;
	EEPROM_voidWriteDataByte(DEVICE1,40,SPEEDCARRIER);
	Display();
	DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_LOW);

	while(Global_f32ForwardDistance < 10 )
	{
		US_voidGetDistance(PORT_u8B,PIN_1,&Global_f64ForwardTime);
		Global_f32ForwardDistance=0.0175*Global_f64ForwardTime;
	}
	Stop();
	SERVO_voidMoveToAngle(135);
	_delay_ms(500);
	US_voidGetDistance(PORT_u8B,PIN_1,&Global_f64RightTime);
	Global_f32RightDistance=0.0175*Global_f64RightTime;
	if (Global_f32RightDistance < 10)
	{
		Display();
		DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_HIGH);
		DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_HIGH);
		DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_LOW);
		DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_LOW);
		DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_LOW);
		while(Global_f32RightDistance < 10 )
		{
			US_voidGetDistance(PORT_u8B,PIN_1,&Global_f64RightTime);
			Global_f32RightDistance=0.0175*Global_f64RightTime;
		}
	}
	SERVO_voidMoveToAngle(90);
}
void Right_BLUE(void)
{
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_LOW);
}
void Left(void)
{
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_HIGH);
	ANALOG_voidSendSignal(PORT_u8B,PIN_7,7);
	SPEEDCARRIER=7;
	EEPROM_voidWriteDataByte(DEVICE1,50,SPEEDCARRIER);
	Display();
	DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_LOW);
	while(Global_f32ForwardDistance < 10 )
	{
		US_voidGetDistance(PORT_u8B,PIN_1,&Global_f64ForwardTime);
		Global_f32ForwardDistance=0.0175*Global_f64ForwardTime;
	}
	Stop();
	SERVO_voidMoveToAngle(45);
	_delay_ms(500);
	US_voidGetDistance(PORT_u8B,PIN_1,&Global_f64LeftTime);
	Global_f32LeftDistance=0.0175*Global_f64LeftTime;
	if (Global_f32LeftDistance < 10)
	{
		Display();
		DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_HIGH);
		DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_LOW);
		DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_LOW);
		DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_HIGH);
		DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_LOW);
		while(Global_f32LeftDistance < 10 )
		{
			US_voidGetDistance(PORT_u8B,PIN_1,&Global_f64LeftTime);
			Global_f32LeftDistance=0.0175*Global_f64LeftTime;
		}
	}
	SERVO_voidMoveToAngle(90);
}
void Left_BLUE(void)
{
	DIO_voidSetPinValue(PORT_u8D,PIN_7,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_6,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8C,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8D,PIN_4,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_HIGH);
	DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_LOW);
}
void BLUETOOTHMODE(void)
{
	ANALOG_voidSendSignal(PORT_u8B,PIN_7,SPEEDCARRIER_B);
	while (1)
	{
		Display();
		UART_u8RecieveDataSynch(&Local_u8Controler);
		if(Local_u8Controler-'0' <= 9)
		{
			SPEEDCARRIER_B=2*(Local_u8Controler-'0');
			ANALOG_voidSendSignal(PORT_u8B,PIN_7,SPEEDCARRIER_B);
		    EEPROM_voidWriteDataByte(DEVICE1,60,SPEEDCARRIER_B);
		}
		switch(Local_u8Controler)
		{
		case 'w':
		{
			Forward_BLUE();
			Local_u8Controler='f';
			break;
		}
		case 'd':
		{
			Right_BLUE();
			Local_u8Controler='f';
			break;
		}
		case 's':
		{
			Back_BLUE();
			Local_u8Controler='f';
			break;
		}
		case 'a':
		{
			Left_BLUE();
			Local_u8Controler='f';
			break;
		}
		default :
		{
			Stop_BLUE();
			Local_u8Controler='f';
			break;
		}
		}


	}
}
void ULTRASONICMODE(void)
{
	while (1)
	{
		US_voidGetDistance(PORT_u8B,PIN_1,&Global_f64ForwardTime);
		Global_f32ForwardDistance=0.0175*Global_f64ForwardTime;
		if(Global_f32ForwardDistance > 6)
		{
			if(ForwardFlag != 1)
			{
				Forward();
			}
		}
		else if(Global_f32ForwardDistance <= 6)
		{
			OBSTECLSNUM++;
			EEPROM_voidWriteDataByte(DEVICE1,0,OBSTECLSNUM);
			label1:
			Stop();
			SERVO_voidMoveToAngle(0);
			_delay_ms(500);
			US_voidGetDistance(PORT_u8B,PIN_1,&Global_f64RightTime);
			Global_f32RightDistance=0.0175*Global_f64RightTime;
			SERVO_voidMoveToAngle(180);
			_delay_ms(500);
			US_voidGetDistance(PORT_u8B,PIN_1,&Global_f64LeftTime);
			Global_f32LeftDistance=0.0175*Global_f64LeftTime;
			SERVO_voidMoveToAngle(90);
			_delay_ms(500);
			if(Global_f32RightDistance < 8 && Global_f32LeftDistance <8)
			{
				Back();
				goto label1;
			}
			else if(Global_f32RightDistance >= Global_f32LeftDistance)
			{
				Right();
			}
			else if(Global_f32RightDistance < Global_f32LeftDistance)
			{
				Left();
			}
		}

	}

}
void SWITCH(void)
{
	switch(CaseFlag)
	{
	case BLUETOOTH :
	{
		CaseFlag = ULTRASONIC;
		ULTRASONICMODE();
		break;
	}
	case ULTRASONIC :
	{
		CaseFlag = BLUETOOTH;
		BLUETOOTHMODE();
		break;
	}
	}
}

void main(void)
{
	// FOR SWITCH MODE
	DIO_voidSetPinDirection(PORT_u8B,PIN_0,PIN_IN);
	DIO_voidSetPinValue(PORT_u8B,PIN_0,PIN_HIGH);
	// FOR MOTOR DRIVER
	DIO_voidSetPinDirection(PORT_u8B,PIN_3,PIN_OUT);
	DIO_voidSetPinDirection(PORT_u8B,PIN_4,PIN_OUT);
	DIO_voidSetPinDirection(PORT_u8B,PIN_5,PIN_OUT);
	DIO_voidSetPinDirection(PORT_u8B,PIN_6,PIN_OUT);
	DIO_voidSetPinDirection(PORT_u8B,PIN_7,PIN_OUT);
	// FOR US
	DIO_voidSetPinDirection(PORT_u8D,PIN_2,PIN_IN);
	DIO_voidSetPinDirection(PORT_u8B,PIN_1,PIN_OUT); // TRIG
	// FOR SERVO
	SERVO_voidInit();
	SERVO_voidMoveToAngle(90);
	DIO_voidSetPinValue(PORT_u8B,PIN_3,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_4,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_5,PIN_LOW);
	DIO_voidSetPinValue(PORT_u8B,PIN_6,PIN_LOW);
	US_voidGetDistance(PORT_u8B,PIN_1,&Global_f64ForwardTime);
	Global_f32ForwardDistance=0.0175*Global_f64ForwardTime;
	// for switch
	DIO_voidSetPinDirection(PORT_u8D,PIN_3,PIN_IN);
	DIO_voidSetPinValue(PORT_u8D,PIN_3,PIN_HIGH);
	GI_voidEnable();
	EXTI_voidEnableDisable(INT_1,Enabled);
	EXTI_voidSetSenseCtrl(INT_1,falling_edge);
	EXTI_voidSetCallBack(INT_1,SWITCH);
	UART_voidInit();
	// for blue module
	DIO_voidSetPinDirection(PORT_u8D,PIN_0,PIN_IN);
	DIO_voidSetPinDirection(PORT_u8D,PIN_1,PIN_OUT);
	//for leds
	DIO_voidSetPinDirection(PORT_u8D,PIN_7,PIN_OUT);
	DIO_voidSetPinDirection(PORT_u8D,PIN_6,PIN_OUT);
	DIO_voidSetPinDirection(PORT_u8D,PIN_4,PIN_OUT);
	DIO_voidSetPinDirection(PORT_u8C,PIN_3,PIN_OUT);
	DIO_voidSetPinDirection(PORT_u8C,PIN_4,PIN_OUT);
	// FOR CLCD
	DIO_voidSetPortDirection(PORT_u8A,PORT_OUT);
	DIO_voidSetPinDirection(PORT_u8C,PIN_7,PIN_OUT);
	DIO_voidSetPinDirection(PORT_u8C,PIN_6,PIN_OUT);
	DIO_voidSetPinDirection(PORT_u8C,PIN_5,PIN_OUT);
	CLCD_voidInit();
	// EEPROM
	TWI_voidMasterInit(0);
	DIO_voidSetPinDirection(PORT_u8C,PIN_0,PIN_OUT);
	DIO_voidSetPinDirection(PORT_u8C,PIN_1,PIN_OUT);
	SPEEDCARRIER_B=EEPROM_u8ReadDataByte(DEVICE1,60);
	OBSTECLSNUM=EEPROM_u8ReadDataByte(DEVICE1,0);
	while(1)
	{
		ULTRASONICMODE();
	}
}




