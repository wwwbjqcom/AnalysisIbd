#include "fsp.h"
#include "pag0page.h"
#include <iostream>


#define byte unsigned char
/*索引基本信息*/
typedef struct {
	char index_name;
	uint index_id;
	ulint total_pages;
	uint root_page;
	ulint leaf_pages;
}index_info;


typedef struct {
	ulint page_no;
	ulint page_type;
	ulint page_lsn;
	ulint slots;
	ulint page_direction;
	uint records;
	uint page_level;
	uint index_id;
}page_content;

int ScanPage(FILE* fp, uint* page_size, ulint* pages);

void PrintPageInfo(page_content* page_info);

void ScanPageContent(byte* buffer);