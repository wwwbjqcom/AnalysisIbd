
/* Info bit denoting the predefined minimum record: this bit is set
if and only if the record is the first user record on a non-leaf
B-tree page that is the leftmost page on its level
(PAGE_LEVEL is nonzero and FIL_PAGE_PREV is FIL_NULL). */
#define REC_INFO_MIN_REC_FLAG	0x10UL
/* The deleted flag in info bits */
#define REC_INFO_DELETED_FLAG	0x20UL	/* when bit is set to 1, it means the
record has been delete marked */

/* Number of extra bytes in an old-style record,
in addition to the data and the offsets */
#define REC_N_OLD_EXTRA_BYTES	6
/* Number of extra bytes in a new-style record,
in addition to the data and the offsets */
#define REC_N_NEW_EXTRA_BYTES	5

/* Record status values */
#define REC_STATUS_ORDINARY	0
#define REC_STATUS_NODE_PTR	1
#define REC_STATUS_INFIMUM	2
#define REC_STATUS_SUPREMUM	3

/* The following four constants are needed in page0zip.cc in order to
efficiently compress and decompress pages. */

/* The offset of heap_no in a compact record */
#define REC_NEW_HEAP_NO		4
/* The shift of heap_no in a compact record.
The status is stored in the low-order bits. */
#define	REC_HEAP_NO_SHIFT	3

/* Length of a B-tree node pointer, in bytes */
#define REC_NODE_PTR_SIZE	4

/** SQL null flag in a 1-byte offset of ROW_FORMAT=REDUNDANT records */
#define REC_1BYTE_SQL_NULL_MASK	0x80UL
/** SQL null flag in a 2-byte offset of ROW_FORMAT=REDUNDANT records */
#define REC_2BYTE_SQL_NULL_MASK	0x8000UL

/** In a 2-byte offset of ROW_FORMAT=REDUNDANT records, the second most
significant bit denotes that the tail of a field is stored off-page. */
#define REC_2BYTE_EXTERN_MASK	0x4000UL

#ifdef UNIV_DEBUG
/* Length of the rec_get_offsets() header */
# define REC_OFFS_HEADER_SIZE	4
#else /* UNIV_DEBUG */
/* Length of the rec_get_offsets() header */
# define REC_OFFS_HEADER_SIZE	2
#endif /* UNIV_DEBUG */

/* Number of elements that should be initially allocated for the
offsets[] array, first passed to rec_get_offsets() */
#define REC_OFFS_NORMAL_SIZE	100
#define REC_OFFS_SMALL_SIZE	10
