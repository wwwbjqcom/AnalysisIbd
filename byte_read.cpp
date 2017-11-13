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
ib_uint64_t mach_read_from_8(
	/*=============*/
	const byte*	b)	/*!< in: pointer to 8 bytes */
{
	/*
	ib_uint64_t tmp_value;
	memcpy(&tmp_value, b, 8);
	return conversion_byte_order_8(tmp_value);
	*/
	ib_uint64_t	u64;
	uint u32;

	u64 = mach_read_from_4(b);
	u64 <<= 32;
	u32 = mach_read_from_4(b + 4);
	return(u64 | u32);
}

/*******************************************************//**
														 The following function is used to store data in four consecutive
														 bytes. We store the most significant byte to the lowest address. */
void mach_write_to_4(
	/*============*/
	byte*	b,	/*!< in: pointer to four bytes where to store */
	ulint	n)	/*!< in: ulint integer to be stored */
{
	b[0] = (byte)(n >> 24);
	b[1] = (byte)(n >> 16);
	b[2] = (byte)(n >> 8);
	b[3] = (byte)n;
}

/********************************************************//**
														  The following function is used to fetch data from 4 consecutive
														  bytes. The most significant byte is at the lowest address.
														  @return ulint integer */
ulint mach_read_from_4(const byte* b)	/*!< in: pointer to four bytes */
{
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
	const byte*	b)	/*!< in: pointer to 3 bytes */
{

	return((ulint)(b[0]) << 16
		| ((ulint)(b[1]) << 8)
		| ((ulint)(b[2]))
		);
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
	return((ulint)(b[0]) << 8 | ((ulint)(b[1])));
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