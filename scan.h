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
	ulint page_no; //页id
	ulint page_type; //页类型
	ulint page_lsn; //页当前刷到的LSN号
	ulint slots; //拥有的slot槽数
	uint records; //记录数
	uint page_level; //该页是所属索引的叶子结点还是root页等
	uint index_id; //所属索引ID
	uint direction; //最后一次插入的放心，可以用于估算页分裂情况
	uint deleted_bytes; //该页当前标记删除的字节数
}page_content;

int ScanPage(FILE* fp, uint* page_size, ulint* pages);

void PrintPageInfo(page_content* page_info);

void ScanPageContent(byte* buffer);