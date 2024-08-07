/*
 * SSD_program.c
 *
 *  Created on: Jun 30, 2024
 *      Author: wily
 */
#include "..\..\LIB\STD_TYPES.h"
#include "..\..\LIB\BIT_MATH.h"

#include "..\..\MCAL\GPIO\GPIO_interface.h"

#include "SSD_private.h"
#include "SSD_interface.h"

static u8 SSDNumbers[10] = SSD_Number_Array;

void SSD_Init(SSD_Type SSD_Configuration) {
	if (SSD_Configuration.Decoder == SSD_NO_DECODER) {
		GPIO_SetPortDirection(SSD_Configuration.DataPort, PORT_OUTPUT);
	} else if (SSD_Configuration.Decoder == SSD_DECODER) {
		switch (SSD_Configuration.NibbleType) {
		case SSD_LOW_NIBBLE:
			GPIO_SetLowNibbleDirection(SSD_Configuration.DataPort,
			L_NIBBLE_OUTPUT);
			break;
		case SSD_HIGH_NIBBLE:
			GPIO_SetHighNibbleDirection(SSD_Configuration.DataPort,
			H_NIBBLE_OUTPUT);
			break;
		}
	}
}
void SSD_Enable(SSD_Type SSD_Configuration) {
	if (SSD_Configuration.Type == SSD_COMMON_ANODE) {
		GPIO_SetPinDirection(SSD_Configuration.EnablePort,
				SSD_Configuration.EnablePin, PIN_OUTPUT);
		GPIO_SetPinValue(SSD_Configuration.EnablePort,
				SSD_Configuration.EnablePin, LOGIC_HIGH);
	} else if (SSD_Configuration.Type == SSD_COMMON_CATHODE) {
		GPIO_SetPinDirection(SSD_Configuration.EnablePort,
				SSD_Configuration.EnablePin, PIN_OUTPUT);
		GPIO_SetPinValue(SSD_Configuration.EnablePort,
				SSD_Configuration.EnablePin, LOGIC_LOW);
	}
}
void SSD_Disable(SSD_Type SSD_Configuration) {
	if (SSD_Configuration.Type == SSD_COMMON_ANODE) {
		GPIO_SetPinDirection(SSD_Configuration.EnablePort,
				SSD_Configuration.EnablePin, PIN_OUTPUT);
		GPIO_SetPinValue(SSD_Configuration.EnablePort,
				SSD_Configuration.EnablePin, LOGIC_LOW);
	} else if (SSD_Configuration.Type == SSD_COMMON_CATHODE) {
		GPIO_SetPinDirection(SSD_Configuration.EnablePort,
				SSD_Configuration.EnablePin, PIN_OUTPUT);
		GPIO_SetPinValue(SSD_Configuration.EnablePort,
				SSD_Configuration.EnablePin, LOGIC_HIGH);
	}
}
void SSD_SendNumber(SSD_Type SSD_Configuration, u8 CopyNumber) {
	if (SSD_Configuration.Decoder == SSD_NO_DECODER) {
		if (SSD_Configuration.Type == SSD_COMMON_ANODE) {
			GPIO_WritePortValue(SSD_Configuration.DataPort,
					~SSDNumbers[CopyNumber]);
		} else if (SSD_Configuration.Type == SSD_COMMON_CATHODE) {
			GPIO_WritePortValue(SSD_Configuration.DataPort,
					SSDNumbers[CopyNumber]);
		}
	} else if (SSD_Configuration.Decoder == SSD_DECODER) {
		switch (SSD_Configuration.NibbleType) {
		case SSD_LOW_NIBBLE:
			GPIO_WriteLowNibbleValue(SSD_Configuration.DataPort,CopyNumber);
			break;
		case SSD_HIGH_NIBBLE:
			GPIO_WriteHighNibbleValue(SSD_Configuration.DataPort,
			CopyNumber);
			break;
		}
	}
}

