#include "byte_read.h"
#include <cstring>
#include <iostream>
using namespace std;


//convert the byte of Big-Endian and Little-Endian
int conversion_byte_order_4(int num)
{
	uint tmp;
	tmp = ((num & 0x000000FF) << 24) |
		((num & 0x0000FF00) << 8) |
		((num & 0x00FF0000) >> 8) |
		((num & 0xFF000000) >> 24);
	return tmp;
}

int conversion_byte_order_3(short num)
{
	uint tmp;
	tmp = ((num & 0x0000FF) << 16) |
		((num & 0x00FF00)) |
		((num & 0xFF0000) >> 16);
	return tmp;
}

int conversion_byte_order_2(short num)
{
	uint tmp;
	tmp = ((num & 0x00FF) << 8) |
		((num & 0xFF00) >> 8);
	return tmp;
}

/********************************************************//**
														  The following function is used to fetch data from 4 consecutive
														  bytes. The most significant byte is at the lowest address.
														  @return ulint integer */
ulint mach_read_from_4(const char* b)	/*!< in: pointer to four bytes */
{


	return conversion_byte_order_4((((ulint)(b[0]) << 24)
		| ((ulint)(b[1]) << 16)
		| ((ulint)(b[2]) << 8)
		| (ulint)(b[3])
		));
}

ulint mach_little_read_from_4(const char* b)	/*!< in: pointer to four bytes for little ending */
{
	
	return((ulint)(b[0])
		| ((ulint)(b[1]) << 8)
		| ((ulint)(b[2]) << 16)
		| ((ulint)(b[3]) << 24)
		);
}


/********************************************************//**
														  The following function is used to fetch data from 3 consecutive
														  bytes. The most significant byte is at the lowest address.
														  @return ulint integer */
ulint mach_read_from_3(
	/*=============*/
	const char*	b)	/*!< in: pointer to 3 bytes */
{

	return conversion_byte_order_3(((ulint)(b[0]) << 16)
		| ((ulint)(b[1]) << 8)
		| (ulint)(b[2])
		);
}

ulint mach_little_read_from_3(
	/*=============*/
	const char*	b)	/*!< in: pointer to 3 bytes for little ending*/
{

	return((ulint)(b[0])
		| ((ulint)(b[1]) << 8)
		| ((ulint)(b[2]) << 16)
		);
}


/********************************************************//**
														  The following function is used to fetch data from 2 consecutive
														  bytes. The most significant byte is at the lowest address.
														  @return ulint integer */
ulint
mach_read_from_2(
	/*=============*/
	const char*	b)	/*!< in: pointer to 2 bytes */
{
	return conversion_byte_order_2(((ulint)(b[0]) << 8) | (ulint)(b[1]));
}

ulint
mach_little_read_from_2(
	/*=============*/
	const char*	b)	/*!< in: pointer to 2 bytes for little ending */
{
	return((ulint)(b[0]) | ((ulint)(b[1]) << 8));
}

/********************************************************//**
														  The following function is used to fetch data from one byte.
														  @return ulint integer, >= 0, < 256 */
ulint
mach_read_from_1(
	/*=============*/
	const char*	b)	/*!< in: pointer to byte */
{
	return((ulint)(b[0]));
}

