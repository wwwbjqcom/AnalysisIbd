#include "fsp.h"
#include "pag0page.h"
#include <iostream>

/*索引基本信息*/
typedef struct {
	char index_name;
	uint index_id;
	ulint total_pages;
	uint root_page;
	ulint leaf_pages;
}index_info;


typedef struct {
	unsigned char page_no;
	uint page_type;
	ulint page_lsn;
	uint slots;
	char page_direction;
	uint records;
	uint page_level;
	uint index_id;
}page_content;

int ScanPage(FILE* fp, uint* page_size, ulint* pages);

void PrintPageInfo(page_content* page_info);

void ScanPageContent(char* buffer);