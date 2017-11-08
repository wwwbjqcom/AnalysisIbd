#include <stdio.h>
#include <stdlib.h>  
#include <iostream>
#include "fsp.h"

/********************************************************//**
														  The following function is used to fetch data from 4 consecutive
														  bytes. The most significant byte is at the lowest address.
														  @return ulint integer */
ulint mach_read_from_4(const char* b); /*!< in: pointer to 4 bytes */

ulint mach_little_read_from_4(const char* b);/*!< in: pointer to 4 bytes for little ending */


/********************************************************//**
														  The following function is used to fetch data from 3 consecutive
														  bytes. The most significant byte is at the lowest address.
														  @return ulint integer */
ulint mach_read_from_3(const char* b);	/*!< in: pointer to 3 bytes */

ulint mach_little_read_from_3(const char* b); /*!< in: pointer to 3 bytes for little ending */

								/********************************************************//**
																						  The following function is used to fetch data from 2 consecutive
																						  bytes. The most significant byte is at the lowest address.
																						  @return ulint integer */
ulint mach_read_from_2(const char* b);	/*!< in: pointer to 2 bytes */

ulint mach_little_read_from_2(const char* b); /*!< in: pointer to 2 bytes for little ending */

					/********************************************************//**
																			  The following function is used to fetch data from one byte.
																			  @return ulint integer, >= 0, < 256 */
ulint mach_read_from_1(const char* b);	/*!< in: pointer to byte */



										
uint* read_int(FILE *file); //¶ÁÈ¡4bytes


char* get_page_value(FILE* fp, uint* page_size);






