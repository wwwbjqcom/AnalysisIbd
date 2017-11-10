#include "byte_read.h"
#include <cstring>



//convert the byte of Big-Endian and Little-Endian


ulint conversion_byte_order_4(ulint num)
{
	ulint tmp;
	tmp = ((num & 0x000000FF) << 24) |
		((num & 0x0000FF00) << 8) |
		((num & 0x00FF0000) >> 8) |
		((num & 0xFF000000) >> 24);
	return tmp;
}

ulint conversion_byte_order_3(short num)
{
	ulint tmp;
	tmp = ((num & 0x0000FF) << 16) |
		((num & 0x00FF00)) |
		((num & 0xFF0000) >> 16);
	return tmp;
}

ulint conversion_byte_order_2(short num)
{
	ulint tmp;
	tmp = ((num & 0x00FF) << 8) |
		((num & 0xFF00) >> 8);
	return tmp;
}

/********************************************************//**
														  The following function is used to fetch data from 8 consecutive
														  bytes. The most significant byte is at the lowest address.
														  @return 64-bit integer */
ulint mach_read_from_8(
	/*=============*/
	const byte*	b)	/*!< in: pointer to 8 bytes */
{
	/*
	ib_uint64_t tmp_value;
	memcpy(&tmp_value, b, 8);
	return conversion_byte_order_8(tmp_value);
	*/
	ulint	u64;

	u64 = mach_read_from_4(b);
	u64 <<= 32;
	u64 |= mach_read_from_4(b + 4);

	return u64;
}

/********************************************************//**
														  The following function is used to fetch data from 4 consecutive
														  bytes. The most significant byte is at the lowest address.
														  @return ulint integer */
ulint mach_read_from_4(const byte* b)	/*!< in: pointer to four bytes */
{

	//ulint tmp_value;
	//memcpy(&tmp_value, b, 4);
	//return conversion_byte_order_4(tmp_value);
	
	return ( ((ulint)((b[0]) << 24))
		| ((ulint)((b[1]) << 16))
		| ((ulint)((b[2]) << 8))
		| (ulint)(b[3])
		);
}

ulint mach_little_read_from_4(const byte* b)	/*!< in: pointer to four bytes for little ending */
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

	ulint tmp_value;
	memcpy(&tmp_value, b, 3);
	return conversion_byte_order_3(tmp_value);
}

ulint mach_little_read_from_3(
	/*=============*/
	const byte*	b)	/*!< in: pointer to 3 bytes for little ending*/
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
	const byte*	b)	/*!< in: pointer to 2 bytes */
{
	ulint tmp_value;
	memcpy(&tmp_value, b, 2);
	return conversion_byte_order_2(tmp_value);
}

ulint
mach_little_read_from_2(
	/*=============*/
	const byte*	b)	/*!< in: pointer to 2 bytes for little ending */
{
	return((ulint)(b[0]) | ((ulint)(b[1]) << 8));
}

/********************************************************//**
														  The following function is used to fetch data from one byte.
														  @return ulint integer, >= 0, < 256 */
ulint
mach_read_from_1(
	/*=============*/
	const byte*	b)	/*!< in: pointer to byte */
{
	return((ulint)(b[0]));
}


//读取4bytes
uint read_int(FILE *file)
{
	uint value;
	fread(&value, sizeof(int), 1, file);
	return value;
}


//获取一页数据
byte* get_page_value(byte* buffer,FILE* fp, uint* page_size)
{

	fread(buffer, *page_size, 1, fp);
}