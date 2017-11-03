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

ulint page_is_comp(
	/*=========*/
	char*	page)	/*!< in: index page */
{
	ulint tmp_value;
	memcpy(&tmp_value, page + PAGE_HEADER + PAGE_N_HEAP, 1);
	return(tmp_value & 0x8000);
}


ulint page_is_comp(
	/*=========*/
	char*	page)	/*!< in: index page */
{
	ulint tmp_value;
	memcpy(&tmp_value, page + PAGE_HEADER + PAGE_N_HEAP, 1);
	return(tmp_value & 0x8000);
}