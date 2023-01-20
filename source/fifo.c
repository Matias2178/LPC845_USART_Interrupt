/*
 * fifo.c
 *
 *  Created on: 19 ene. 2023
 *      Author: Matias Martelossi
 */
#include "stdbool.h"
#include "fifo.h"


/*!
 * @brief Inicializa el sistema de buffer FIFO
 *
 * @param base    GPIO peripheral base pointer(Typically GPIO)
 *
 */
void FIFO_Init(union _flag *flag, struct _index *index ){
	index->read = 0;
	index->write = 0;
	flag->val = 0;
	flag->bits.empty = 1;
}

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
unsigned char FIFO_Read(union _flag *flag, struct _index *index, int buffer_size, unsigned char *buffer){
	unsigned char val;

	if(flag->bits.empty){
		return 0;
	}
	buffer = buffer + index->read;  ///ver si funciona bien
	index->read ++;
	val = *buffer;

	if(index->read == buffer_size){
		index->read = 0;
	}

	if(index->read == index->write){
		flag->bits.empty = true;
	}
	return val;
}

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
unsigned char FIFO_Write(union _flag *flag, struct _index *index, int buffer_size, unsigned char *buffer, char val)
{
	if((index->write == index->read) && !flag->bits.empty){
		flag->bits.overflow = true;
		return false;
	}
	buffer = buffer + index->write;
	index->write ++;
	*buffer = val;
	flag->bits.empty = false;

	if(index->write == buffer_size){
		index->write = 0;
	}

	return true;
}

/*!
 * @brief Read status empty flag
 *
 * @param flag  		union flags address.
 * @param output  		return empty Flag
 */
unsigned char FIFO_Empty(union _flag *flag)
{
	return flag->bits.empty;
}

/*!
 * @brief Read status full flag
 *
 * @param flag  		union flags address.
 * @param output  		return full Flag
 */
unsigned char FIFO_Full(union _flag *flag)
{
	return flag->bits.full;

}

/*!
 * @brief Get free space in the buffer
 *
 * @param flag  		union flags address.
 * @param index  		struct index address.
 * @param buffer_size  	size of the buffer to use.
 * @param output  		number of characters aviable
 */
unsigned int FIFO_Space(union _flag *flag, struct _index *index, int buffer_size)
{
	if((index->read == index->write)&& !flag->bits.empty){
		return buffer_size;
	}
	else if(flag->bits.empty){
		return 0;
	}
	else if(index->read > index->write){
		return index->read - index->write;
	}
	else if(index->read < index->write){
		return index->read + buffer_size - index->write;
	}
	else{
		return 0;
	}
}

/*!
 * @brief Set transmit flag
 *
 * @param flag  		union flags address.
 */
void FIFO_Transmit_Set(union _flag *flag)
{
	flag->bits.transmit = true;
}

/*!
 * @brief Clear transmit flag
 *
 * @param flag  		union flags address.
 */
void FIFO_Transmit_Clear(union _flag *flag)
{
	flag->bits.transmit = false;
}

/*!
 * @brief Read status transmit flag
 *
 * @param flag  		union flags address.
 * @param output  		return full Flag
 */
unsigned char FIFO_Transmit_Get(union _flag *flag)
{
	return flag->bits.transmit;
}

/*!
 * @brief Read status OverFlow flag
 *
 * @param flag  		union flags address.
 * @param output  		return full Flag
 */
unsigned char FIFO_OverFlow(union _flag *flag)
{
	return flag->bits.overflow;
}

/*!
 * @brief Clear OverFlow flag
 *
 * @param flag  		union flags address.
 */
void FIFO_ClearOverFlow(union _flag *flag)
{
	flag->bits.overflow = false;
}

