#include <stdio.h>
#include <stdlib.h>  
#include <iostream>
#include "fsp.h"


#define byte unsigned char 
/********************************************************//**
														  The following function is used to fetch data from 8 consecutive
														  bytes. The most significant byte is at the lowest address.
														  @return 64-bit integer */
ib_uint64_t mach_read_from_8(
	/*=============*/
	const byte*	b);	/*!< in: pointer to 8 bytes */
/********************************************************//**
														  The following function is used to fetch data from 4 consecutive
														  bytes. The most significant byte is at the lowest address.
														  @return ulint integer */
ulint mach_read_from_4(const byte* b); /*!< in: pointer to 4 bytes */



/********************************************************//**
														  The following function is used to fetch data from 3 consecutive
														  bytes. The most significant byte is at the lowest address.
														  @return ulint integer */
ulint mach_read_from_3(const byte* b);	/*!< in: pointer to 3 bytes */


								/********************************************************//**
																						  The following function is used to fetch data from 2 consecutive
																						  bytes. The most significant byte is at the lowest address.
																						  @return ulint integer */
ulint mach_read_from_2(const byte* b);	/*!< in: pointer to 2 bytes */


					/********************************************************//**
																			  The following function is used to fetch data from one byte.
																			  @return ulint integer, >= 0, < 256 */
ulint mach_read_from_1(const byte* b);	/*!< in: pointer to byte */



										
uint read_int(FILE *file); //¶ÁÈ¡4bytes


byte* get_page_value(byte* buffer,FILE* fp, uint* page_size);






