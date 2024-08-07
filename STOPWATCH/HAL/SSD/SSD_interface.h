/*
 * SSD_interface.h
 *
 *  Created on: Jun 30, 2024
 *      Author: wily
 */

#ifndef SSD_SSD_INTERFACE_H_
#define SSD_SSD_INTERFACE_H_

#define SSD_COMMON_CATHODE  0
#define SSD_COMMON_ANODE    1

#define SSD_NO_DECODER    0
#define SSD_DECODER  1

#define SSD_LOW_NIBBLE    0
#define SSD_HIGH_NIBBLE   1

typedef struct {

	u8 Type;
	u8 Decoder;
	u8 DataPort;
	u8 EnablePort;
	u8 EnablePin;
	u8 NibbleType;
} SSD_Type;

void SSD_Init(SSD_Type SSD_Configuration);
void SSD_Enable(SSD_Type SSD_Configuration);
void SSD_Disable(SSD_Type SSD_Configuration);
void SSD_SendNumber(SSD_Type SSD_Configuration, u8 CopyNumber);

#endif /* SSD_SSD_INTERFACE_H_ */
