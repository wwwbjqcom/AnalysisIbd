


#define FIL_ADDR_SIZE 6
/* The physical size of a list base node in bytes */
#define	FLST_BASE_NODE_SIZE	(4 + 2 * FIL_ADDR_SIZE)
/* page_size*/
#define UNI_PAGE_SIZE 16384



/*			SPACE HEADER
============

File space header data structure: this data structure is contained in the
first page of a space. The space for this header is reserved in every extent
descriptor page, but used only in the first. */

#define FSEG_HEADER_SIZE	10	/*!< Length of the file system
header, in bytes */

/*-------------------------------------*/
#define FSP_SPACE_ID		0	/* space id */
#define FSP_NOT_USED		4	/* this field contained a value up to
which we know that the modifications
in the database have been flushed to
the file space; not used now */
#define	FSP_SIZE		8	/* Current size of the space in
pages */
#define	FSP_FREE_LIMIT		12	/* Minimum page number for which the
free list has not been initialized:
the pages >= this limit are, by
definition, free; note that in a
single-table tablespace where size
< 64 pages, this number is 64, i.e.,
we have initialized the space
about the first extent, but have not
physically allocated those pages to the
file */
#define	FSP_SPACE_FLAGS		16	/* fsp_space_t.flags, similar to
dict_table_t::flags */
#define	FSP_FRAG_N_USED		20	/* number of used pages in the
FSP_FREE_FRAG list */
#define	FSP_FREE		24	/* list of free extents */
#define	FSP_FREE_FRAG		(24 + FLST_BASE_NODE_SIZE)
/* list of partially free extents not
belonging to any segment */
#define	FSP_FULL_FRAG		(24 + 2 * FLST_BASE_NODE_SIZE)
/* list of full extents not belonging
to any segment */
#define FSP_SEG_ID		(24 + 3 * FLST_BASE_NODE_SIZE)
/* 8 bytes which give the first unused
segment id */
#define FSP_SEG_INODES_FULL	(32 + 3 * FLST_BASE_NODE_SIZE)
/* list of pages containing segment
headers, where all the segment inode
slots are reserved */
#define FSP_SEG_INODES_FREE	(32 + 4 * FLST_BASE_NODE_SIZE)
/* list of pages containing segment
headers, where not all the segment
header slots are reserved */
/*-------------------------------------*/
/* File space header size */
#define	FSP_HEADER_SIZE		(32 + 5 * FLST_BASE_NODE_SIZE)

#define	FSP_FREE_ADD		4	/* this many free extents are added
to the free list from above
FSP_FREE_LIMIT at a time */
/* @} */

/* We define the field offsets of a base node for the list */
#define FLST_LEN	0	/* 32-bit list length field */



/*			Calculate
============*/
typedef unsigned long int ulint;
typedef unsigned int uint;
typedef unsigned short uint16;
#define byte unsigned char;
#define ib_page_t unsigned char;
#define page_t	   ib_page_t


/* Define the Min, Max, Default page sizes. */
/** Minimum Page Size Shift (power of 2) */
#define UNIV_PAGE_SIZE_SHIFT_MIN	12
/** Maximum Page Size Shift (power of 2) */
#define UNIV_PAGE_SIZE_SHIFT_MAX	16
/** Default Page Size Shift (power of 2) */
#define UNIV_PAGE_SIZE_SHIFT_DEF	14
/** Original 16k InnoDB Page Size Shift, in case the default changes */
#define UNIV_PAGE_SIZE_SHIFT_ORIG	14
/** Original 16k InnoDB Page Size as an ssize (log2 - 9) */
#define UNIV_PAGE_SSIZE_ORIG		(UNIV_PAGE_SIZE_SHIFT_ORIG - 9)
/** log2 of smallest compressed page size (1<<10 == 1024 bytes)
Note: This must never change! */
#define UNIV_ZIP_SIZE_SHIFT_MIN		10
/** Minimum page size InnoDB currently supports. */
#define UNIV_PAGE_SIZE_MIN	(1 << UNIV_PAGE_SIZE_SHIFT_MIN)
/** Maximum page size InnoDB currently supports. */
#define UNIV_PAGE_SIZE_MAX	(1 << UNIV_PAGE_SIZE_SHIFT_MAX)
/** Smallest compressed page size */
#define UNIV_ZIP_SIZE_MIN	(1 << UNIV_ZIP_SIZE_SHIFT_MIN)



#define FIL_PAGE_DATA		38U	/*!< start of the data on the page */
/** Offset of the space header within a file page */
#define FSP_HEADER_OFFSET	FIL_PAGE_DATA
/** starting from 4.1.x this contains the space id of the page */
#define FIL_PAGE_ARCH_LOG_NO_OR_SPACE_ID  34
#define	FSP_SPACE_FLAGS		16	/* fsp_space_t.flags, similar to
dict_table_t::flags */
/** Offset of the space header within a file page */
#define FSP_HEADER_OFFSET	FIL_PAGE_DATA

#define FIL_PAGE_OFFSET		4	/*!< page offset inside space */


/** Width of the ATOMIC_BLOBS flag.  The ability to break up a long
column into an in-record prefix and an externally stored part is available
to the two Barracuda row formats COMPRESSED and DYNAMIC. */
#define FSP_FLAGS_WIDTH_ATOMIC_BLOBS	1
/** Width of the encryption flag.  This flag indicates that the tablespace
is a tablespace with encryption. */
#define FSP_FLAGS_WIDTH_ENCRYPTION	1
/** Width of the TEMPORARY flag.  This flag indicates that the tablespace
is a temporary tablespace and everything in it is temporary, meaning that
it is for a single client and should be deleted upon startup if it exists. */
#define FSP_FLAGS_WIDTH_TEMPORARY	1
/** Width of the DATA_DIR flag.  This flag indicates that the tablespace
is found in a remote location, not the default data directory. */
#define FSP_FLAGS_WIDTH_DATA_DIR	1
/** Width of the SHARED flag.  This flag indicates that the tablespace
was created with CREATE TABLESPACE and can be shared by multiple tables. */
#define FSP_FLAGS_WIDTH_SHARED		1
/** Number of flag bits used to indicate the tablespace page size */
#define FSP_FLAGS_WIDTH_PAGE_SSIZE	4
/** Number of flag bits used to indicate the tablespace zip page size */
#define FSP_FLAGS_WIDTH_ZIP_SSIZE	4
/** Zero relative shift position of the POST_ANTELOPE field */
#define FSP_FLAGS_POS_POST_ANTELOPE	0
/** Width of the POST_ANTELOPE flag */
#define FSP_FLAGS_WIDTH_POST_ANTELOPE	1
/** Zero relative shift position of the ZIP_SSIZE field */
#define FSP_FLAGS_POS_ZIP_SSIZE		(FSP_FLAGS_POS_POST_ANTELOPE	\
					+ FSP_FLAGS_WIDTH_POST_ANTELOPE)
/** Zero relative shift position of the ATOMIC_BLOBS field */
#define FSP_FLAGS_POS_ATOMIC_BLOBS	(FSP_FLAGS_POS_ZIP_SSIZE	\
					+ FSP_FLAGS_WIDTH_ZIP_SSIZE)
/** Zero relative shift position of the PAGE_SSIZE field */
#define FSP_FLAGS_POS_PAGE_SSIZE	(FSP_FLAGS_POS_ATOMIC_BLOBS	\
					+ FSP_FLAGS_WIDTH_ATOMIC_BLOBS)
/** Zero relative shift position of the start of the DATA_DIR bit */
#define FSP_FLAGS_POS_DATA_DIR		(FSP_FLAGS_POS_PAGE_SSIZE	\
					+ FSP_FLAGS_WIDTH_PAGE_SSIZE)
/** Zero relative shift position of the start of the SHARED bit */
#define FSP_FLAGS_POS_SHARED		(FSP_FLAGS_POS_DATA_DIR		\
					+ FSP_FLAGS_WIDTH_DATA_DIR)
/** Zero relative shift position of the start of the TEMPORARY bit */
#define FSP_FLAGS_POS_TEMPORARY		(FSP_FLAGS_POS_SHARED		\
					+ FSP_FLAGS_WIDTH_SHARED)
/** Zero relative shift position of the start of the ENCRYPTION bit */
#define FSP_FLAGS_POS_ENCRYPTION	(FSP_FLAGS_POS_TEMPORARY	\
					+ FSP_FLAGS_WIDTH_TEMPORARY)
/** Zero relative shift position of the start of the UNUSED bits */
#define FSP_FLAGS_POS_UNUSED		(FSP_FLAGS_POS_ENCRYPTION	\
					+ FSP_FLAGS_WIDTH_ENCRYPTION)
/** Zero relative shift position of the PAGE_SSIZE field */
#define FSP_FLAGS_POS_PAGE_SSIZE	(FSP_FLAGS_POS_ATOMIC_BLOBS	\
					+ FSP_FLAGS_WIDTH_ATOMIC_BLOBS)
/** Number of flag bits used to indicate the tablespace page size */
#define FSP_FLAGS_WIDTH_PAGE_SSIZE 4
/** Bit mask of the PAGE_SSIZE field */
#define FSP_FLAGS_MASK_PAGE_SSIZE				\
		((~(~0U << FSP_FLAGS_WIDTH_PAGE_SSIZE))		\
		<< FSP_FLAGS_POS_PAGE_SSIZE)

/** Return the value of the PAGE_SSIZE field */
#define FSP_FLAGS_GET_PAGE_SSIZE(flags)				\
		((flags & FSP_FLAGS_MASK_PAGE_SSIZE)		\
		>> FSP_FLAGS_POS_PAGE_SSIZE)

/*
=============================*/
/* We define the field offsets of a base node for the list */
#define FLST_LEN	0	/* 32-bit list length field */
#define	FLST_FIRST	4	/* 6-byte address of the first element
of the list; undefined if empty list */
#define	FLST_LAST	(4 + FIL_ADDR_SIZE) /* 6-byte address of the
last element of the list; undefined
if empty list */
#define FIL_ADDR_PAGE	0	/* first in address is the page offset */
#define	FIL_ADDR_BYTE	4	/* then comes 2-byte byte offset within page*/
#define	FIL_PAGE_TYPE		24	/*!< file page type: FIL_PAGE_INDEX,...,
							2 bytes.

							The contents of this field can only
							be trusted in the following case:
							if the page is an uncompressed
							B-tree index page, then it is
							guaranteed that the value is
							FIL_PAGE_INDEX.
							The opposite does not hold.

							In tablespaces created by
							MySQL/InnoDB 5.1.7 or later, the
							contents of this field is valid
							for all uncompressed pages. */
/** File page types (values of FIL_PAGE_TYPE) @{ */
#define FIL_PAGE_INDEX		17855	/*!< B-tree node */
#define FIL_PAGE_RTREE		17854	/*!< B-tree node */
#define FIL_PAGE_UNDO_LOG	2	/*!< Undo log page */
#define FIL_PAGE_INODE		3	/*!< Index node */
#define FIL_PAGE_IBUF_FREE_LIST	4	/*!< Insert buffer free list */
/* File page types introduced in MySQL/InnoDB 5.1.7 */
#define FIL_PAGE_TYPE_ALLOCATED	0	/*!< Freshly allocated page */
#define FIL_PAGE_IBUF_BITMAP	5	/*!< Insert buffer bitmap */
#define FIL_PAGE_TYPE_SYS	6	/*!< System page */
#define FIL_PAGE_TYPE_TRX_SYS	7	/*!< Transaction system data */
#define FIL_PAGE_TYPE_FSP_HDR	8	/*!< File space header */
#define FIL_PAGE_TYPE_XDES	9	/*!< Extent descriptor page */
#define FIL_PAGE_TYPE_BLOB	10	/*!< Uncompressed BLOB page */
#define FIL_PAGE_TYPE_ZBLOB	11	/*!< First compressed BLOB page */
#define FIL_PAGE_TYPE_ZBLOB2	12	/*!< Subsequent compressed BLOB page */
#define FIL_PAGE_TYPE_UNKNOWN	13	/*!< In old tablespaces, garbage
in FIL_PAGE_TYPE is replaced with this
value when flushing pages. */
#define FIL_PAGE_COMPRESSED	14	/*!< Compressed page */
#define FIL_PAGE_ENCRYPTED	15	/*!< Encrypted page */
#define FIL_PAGE_COMPRESSED_AND_ENCRYPTED 16
#define FIL_PAGE_DATA_END	8	/*!< size of the page trailer */

/* Directions of cursor movement */
#define	PAGE_LEFT		1
#define	PAGE_RIGHT		2
#define	PAGE_SAME_REC		3
#define	PAGE_SAME_PAGE		4
#define	PAGE_NO_DIRECTION	5