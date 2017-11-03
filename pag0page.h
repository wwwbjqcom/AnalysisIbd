#include "fsp.h"
#include "rec.h"

/*			PAGE HEADER
===========

Index page header starts at the first offset left free by the FIL-module */

#define	PAGE_HEADER	FIL_PAGE_DATA	/* index page header starts at this
offset */
/*-----------------------------*/
#define PAGE_N_DIR_SLOTS 0	/* number of slots in page directory */
#define	PAGE_HEAP_TOP	 2	/* pointer to record heap top */
#define	PAGE_N_HEAP	 4	/* number of records in the heap,
bit 15=flag: new-style compact page format */
#define	PAGE_FREE	 6	/* pointer to start of page free record list */
#define	PAGE_GARBAGE	 8	/* number of bytes in deleted records */
#define	PAGE_LAST_INSERT 10	/* pointer to the last inserted record, or
NULL if this info has been reset by a delete,
for example */
#define	PAGE_DIRECTION	 12	/* last insert direction: PAGE_LEFT, ... */
#define	PAGE_N_DIRECTION 14	/* number of consecutive inserts to the same
direction */
#define	PAGE_N_RECS	 16	/* number of user records on the page */
#define PAGE_MAX_TRX_ID	 18	/* highest id of a trx which may have modified
a record on the page; trx_id_t; defined only
in secondary indexes and in the insert buffer
tree */
#define PAGE_HEADER_PRIV_END 26	/* end of private data structure of the page
header which are set in a page create */
/*----*/
#define	PAGE_LEVEL	 26	/* level of the node in an index tree; the
leaf level is the level 0.  This field should
not be written to after page creation. */
#define	PAGE_INDEX_ID	 28	/* index id where the page belongs.
This field should not be written to after
page creation. */


#define PAGE_BTR_SEG_LEAF 36	/* file segment header for the leaf pages in
a B-tree: defined only on the root page of a
B-tree, but not in the root of an ibuf tree */
#define PAGE_BTR_IBUF_FREE_LIST	PAGE_BTR_SEG_LEAF
#define PAGE_BTR_IBUF_FREE_LIST_NODE PAGE_BTR_SEG_LEAF
/* in the place of PAGE_BTR_SEG_LEAF and _TOP
there is a free list base node if the page is
the root page of an ibuf tree, and at the same
place is the free list node if the page is in
a free list */
#define PAGE_BTR_SEG_TOP (36 + FSEG_HEADER_SIZE)
/* file segment header for the non-leaf pages
in a B-tree: defined only on the root page of
a B-tree, but not in the root of an ibuf
tree */
/*----*/
#define PAGE_DATA	(PAGE_HEADER + 36 + 2 * FSEG_HEADER_SIZE)
/* start of data on the page */

#define PAGE_OLD_INFIMUM	(PAGE_DATA + 1 + REC_N_OLD_EXTRA_BYTES)
/* offset of the page infimum record on an
old-style page */
#define PAGE_OLD_SUPREMUM	(PAGE_DATA + 2 + 2 * REC_N_OLD_EXTRA_BYTES + 8)
/* offset of the page supremum record on an
old-style page */
#define PAGE_OLD_SUPREMUM_END (PAGE_OLD_SUPREMUM + 9)
/* offset of the page supremum record end on
an old-style page */
#define PAGE_NEW_INFIMUM	(PAGE_DATA + REC_N_NEW_EXTRA_BYTES)
/* offset of the page infimum record on a
new-style compact page */
#define PAGE_NEW_SUPREMUM	(PAGE_DATA + 2 * REC_N_NEW_EXTRA_BYTES + 8)
/* offset of the page supremum record on a
new-style compact page */
#define PAGE_NEW_SUPREMUM_END (PAGE_NEW_SUPREMUM + 8)
/* offset of the page supremum record end on
a new-style compact page */
/*-----------------------------*/

/* Heap numbers */
#define PAGE_HEAP_NO_INFIMUM	0	/* page infimum */
#define PAGE_HEAP_NO_SUPREMUM	1	/* page supremum */
#define PAGE_HEAP_NO_USER_LOW	2	/* first user record in
creation (insertion) order,
not necessarily collation order;
this record may have been deleted */

/* Directions of cursor movement */
#define	PAGE_LEFT		1
#define	PAGE_RIGHT		2
#define	PAGE_SAME_REC		3
#define	PAGE_SAME_PAGE		4
#define	PAGE_NO_DIRECTION	5

/*			PAGE DIRECTORY
==============
*/


/* Offset of the directory start down from the page end. We call the
slot with the highest file address directory start, as it points to
the first record in the list of records. */
#define	PAGE_DIR		FIL_PAGE_DATA_END

/* We define a slot in the page directory as two bytes */
#define	PAGE_DIR_SLOT_SIZE	2

/* The offset of the physically lower end of the directory, counted from
page end, when the page is empty */
#define PAGE_EMPTY_DIR_START	(PAGE_DIR + 2 * PAGE_DIR_SLOT_SIZE)

/* The maximum and minimum number of records owned by a directory slot. The
number may drop below the minimum in the first and the last slot in the
directory. */
#define PAGE_DIR_SLOT_MAX_N_OWNED	8
#define	PAGE_DIR_SLOT_MIN_N_OWNED	4


/************************************************************//**
			TRUE if the record is on a page in compact format.
			@return nonzero if in compact format */
ulint page_is_comp(char*	page);

/************************************************************//**
	Determine whether the page is a B-tree leaf.
	@return true if the page is a B-tree leaf (PAGE_LEVEL = 0) */
bool page_is_leaf(const char*	page)	/*!< in: page */;


/*************************************************************//**
					Gets the number of records in the heap.
					@return number of user records */
ulint
page_dir_get_n_heap(
	/*================*/
	const char*	page)	/*!< in: index page */