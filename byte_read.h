#ifndef _BYTE_READ_H_

#include "fsp.h"

/********************************************************//**
														  The following function is used to fetch data from 4 consecutive
														  bytes. The most significant byte is at the lowest address.
														  @return ulint integer */
extern ulint mach_read_from_4;


/********************************************************//**
														  The following function is used to fetch data from 3 consecutive
														  bytes. The most significant byte is at the lowest address.
														  @return ulint integer */
extern ulint mach_read_from_3;	/*!< in: pointer to 3 bytes */



								/********************************************************//**
																						  The following function is used to fetch data from 2 consecutive
																						  bytes. The most significant byte is at the lowest address.
																						  @return ulint integer */
extern ulint mach_read_from_2;	/*!< in: pointer to 2 bytes */


					/********************************************************//**
																			  The following function is used to fetch data from one byte.
																			  @return ulint integer, >= 0, < 256 */
extern ulint mach_read_from_1;	/*!< in: pointer to byte */

#endif // !_BYTE_READ_H_











