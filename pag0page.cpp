#include "fsp.h"
#include "pag0page.h"
#include <cstring>

/** The page infimum and supremum of an empty page in ROW_FORMAT=REDUNDANT */
static const char infimum_supremum_redundant[] = {
	/* the infimum record */
	0x08/*end offset*/,
	0x01/*n_owned*/,
	0x00, 0x00/*heap_no=0*/,
	0x03/*n_fields=1, 1-byte offsets*/,
	0x00, 0x74/* pointer to supremum */,
	'i', 'n', 'f', 'i', 'm', 'u', 'm', 0,
	/* the supremum record */
	0x09/*end offset*/,
	0x01/*n_owned*/,
	0x00, 0x08/*heap_no=1*/,
	0x03/*n_fields=1, 1-byte offsets*/,
	0x00, 0x00/* end of record list */,
	's', 'u', 'p', 'r', 'e', 'm', 'u', 'm', 0
};

/** The page infimum and supremum of an empty page in ROW_FORMAT=COMPACT */
static const char infimum_supremum_compact[] = {
	/* the infimum record */
	0x01/*n_owned=1*/,
	0x00, 0x02/* heap_no=0, REC_STATUS_INFIMUM */,
	0x00, 0x0d/* pointer to supremum */,
	'i', 'n', 'f', 'i', 'm', 'u', 'm', 0,
	/* the supremum record */
	0x01/*n_owned=1*/,
	0x00, 0x0b/* heap_no=1, REC_STATUS_SUPREMUM */,
	0x00, 0x00/* end of record list */,
	's', 'u', 'p', 'r', 'e', 'm', 'u', 'm'
};



/************************************************************//**
		TRUE if the record is on a page in compact format.
		@return nonzero if in compact format */
ulint page_is_comp(
	/*=========*/
	char*	page)	/*!< in: index page */
{
	ulint tmp_value;
	memcpy(&tmp_value, page + PAGE_HEADER + PAGE_N_HEAP, 2);
	return(tmp_value & 0x8000);
}

/************************************************************//**
	Determine whether the page is a B-tree leaf.
	@return true if the page is a B-tree leaf (PAGE_LEVEL = 0) */
bool
page_is_leaf(
	/*=========*/
	char*	page)	/*!< in: page */
{
	return(!*(const uint16*)(page + (PAGE_HEADER + PAGE_LEVEL)));
}


/*************************************************************//**
					Gets the number of records in the heap.
					@return number of user records */
ulint
page_dir_get_n_heap(
	/*================*/
	const char*	page)	/*!< in: index page */
{
	uint16 tmpvalue;
	memcpy(&tmpvalue, page + PAGE_HEADER + PAGE_N_HEAP, 2);
	return(tmpvalue & 0x7fff);
}