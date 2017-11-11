#include "scan.h"
#include "byte_read.h"
#include <cstring>


void PrintPageInfo(page_content* page_info)
{
	printf("page_no: %lu, page_type: %u, page_lsn: %lu, page_level:%u, index_id:%lu, records:%u, slots:%u, deleted bytes:%u, last inserted direction:%u\n",
		page_info->page_no,page_info->page_type,page_info->page_lsn,page_info->page_level,page_info->index_id,page_info->records,page_info->slots,
		page_info->deleted_bytes,page_info->direction);
}


void ScanPageContent(byte* buffer)
{
	page_content* page_info = new page_content;
	page_info->page_no = mach_read_from_4(buffer + FIL_PAGE_OFFSET);

	page_info->page_type = mach_read_from_2(buffer + FIL_PAGE_TYPE);

	page_info->page_lsn = mach_read_from_8(buffer + FIL_PAGE_LSN);

	byte* offset = buffer + FIL_PAGE_DATA;
	page_info->page_level = mach_read_from_2(offset + PAGE_LEVEL);

	page_info->index_id = mach_read_from_8(offset + PAGE_INDEX_ID);

	page_info->records = mach_read_from_2(offset + PAGE_N_RECS);

	page_info->slots = mach_read_from_2(offset + PAGE_N_DIR_SLOTS);

	page_info->deleted_bytes = mach_read_from_2(offset + PAGE_GARBAGE);

	page_info->direction = mach_read_from_2(offset + PAGE_DIRECTION);
	PrintPageInfo(page_info);

}


int ScanPage(FILE* fp,uint* page_size,ulint* pages)
{

	fseek(fp,(*page_size) * 3 , 0);
	byte *buffer;
	buffer = new byte[*page_size];
	for (ulint i = 4; i <= *pages; i++)
	{
		get_page_value(buffer,fp, page_size);
		ScanPageContent(buffer);

		memset(buffer,'\0',*page_size);
	}
	delete[]buffer;
	return 1;

}
