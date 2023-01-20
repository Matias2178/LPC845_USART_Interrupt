/*
 * fifo.h
 *
 *  Created on: 19 ene. 2023
 *      Author: Matias Martelossi
 */

#ifndef FIFO_H_
#define FIFO_H_

union _flag {
	struct{
		unsigned empty: 1;
		unsigned overflow: 1;
		unsigned full: 1;
		unsigned transmit: 1;
	}bits;
	unsigned char val;
};

struct _index {
	unsigned int read;
	unsigned int write;
};

/*Prototipes*/
void FIFO_Init(union _flag *flag, struct _index *index);


/*!
 * @brief Read data from FIFO buffer
 *
 * @param flag  		union flags address.
 * @param index  		struct index address.
 * @param buffer_size  	size of the buffer to use.
 * @param buffer	  	buffer address.
 * @param output  		return ASCII character.
 *        				return 0: buffer empty
 */
unsigned char FIFO_Read(union _flag *flag, struct _index *index, int buffer_size, unsigned char *buffer);

/*!
 * @brief Write data from FIFO buffer
 *
 * @param flag  		union flags address.
 * @param index  		struct index address.
 * @param buffer_size  	size of the buffer to use.
 * @param buffer	  	buffer address.
 * @param output  		return true: Write ok
 *        				return false: Write fail
 */
unsigned char FIFO_Write(union _flag *flag, struct _index *index, int buffer_size, unsigned char *buffer, char val);

/*!
 * @brief Read status empty flag
 *
 * @param flag  		union flags address.
 * @param output  		return empty Flag
 */
unsigned char FIFO_Empty(union _flag *flag);

/*!
 * @brief Read status full flag
 *
 * @param flag  		union flags address.
 * @param output  		return full Flag
 */
unsigned char FIFO_Full(union _flag *flag);

/*!
 * @brief Get free space in the buffer
 *
 * @param flag  		union flags address.
 * @param index  		struct index address.
 * @param buffer_size  	size of the buffer to use.
 * @param output  		number of characters aviable
 */
unsigned int  FIFO_Space(union _flag *flag, struct _index *index, int buffer_size);

/*!
 * @brief Set transmit flag
 *
 * @param flag  		union flags address.
 */
void FIFO_Transmit_Set(union _flag *flag);

/*!
 * @brief Clear transmit flag
 *
 * @param flag  		union flags address.
 */
void FIFO_Transmit_Clear(union _flag *flag);

/*!
 * @brief Read status transmit flag
 *
 * @param flag  		union flags address.
 * @param output  		return full Flag
 */
unsigned char FIFO_Transmit_Get(union _flag *flag);

/*!
 * @brief Read status OverFlow flag
 *
 * @param flag  		union flags address.
 * @param output  		return full Flag
 */
unsigned char FIFO_OverFlow(union _flag *flag);

/*!
 * @brief Clear OverFlow flag
 *
 * @param flag  		union flags address.
 */
void FIFO_ClearOverFlow(union _flag *flag);



#endif /* FIFO_H_ */
