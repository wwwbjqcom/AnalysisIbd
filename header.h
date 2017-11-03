#include "fsp.h"
#include "pag0page.h"


struct point_info
{
	uint addr_page;
	uint addr_offset;
};

struct fsp_info
{
	uint flst_len;  //链表长度
	point_info flst_first; //链表第一个的指针
	point_info flst_last; //链表中最后最后一个的指针
};


struct Fsp_Info
{
	FILE *fp;
	uint page_ssize;
	uint space_id; //表空间id
	uint page_size; //页大小
	uint free_len;
	uint free_limit;
	bool is_com;
	uint page_number;
	uint fil_page_type; //类型
	uint fsp_space_id; //表空间id
	uint fsp_not_used; //未使用的簇数量
	uint fsp_size; //表空间总页数
	uint fsp_space_flags; //flags 按位存放space_id、压缩页大小,压缩类型等
	uint fsp_frag_n_used; //FSP_FREE_FRAG中已经被使用的页面数
	fsp_info fsp_free; //偏移FSP_FREE + FLST_LEN,写入0占用4bytes,偏移FSP_FREE + FLST_FIRST/FLST_LAST + FIL_ADDR_PAGE的4bytes记录指针信息
					   //FSP_FREE + FLST_FIRST/FLST_LAST + FIL_ADDR_BYTE占用2bytes的offset信息， 记录表空间中所有空闲簇的链表信息
	fsp_info fsp_free_frag;//与FSP_FREE类似，只是这是记录的簇为已经部分使用的，即不是空簇又不是满簇的链表
	fsp_info fsp_full_frag;//同上，字面意思就清楚存储的为满簇
	fsp_info fsp_seg_inodes_full;//同上，用于存放管理数据段的页面链表，该指针为已满的数据页链表
	fsp_info fsp_seg_inodes_free;//同上，存放指针为半满存放数据段管理信息的数据页链表
	uint fsp_seg_id;//偏移FSP_SEG_ID记录段ID，占用1bytes，数据段ID
};

//读取page数据
char* get_page_value(FILE* fp, uint* page_size);

void Print_content(Fsp_Info *fsp_info_value);

//获取page_size
int page_size_t(uint fsp_flags);

//convert the byte of Big-Endian and Little-Endian
int conversion_byte_order(int num);

int check_unside(uint value);

int conversion_byte_order_two(short num);

//读取4bytes
int read_int(FILE *file);

//获取簇、段的指针信息
void *read_fsp_content(Fsp_Info *fsp_info_value, char* buffer, uint offset, int type);

void Enter(char *file_name);

void Print_content(Fsp_Info *fsp_info_value);

//读取页数据
char* get_page_value(FILE* fp, uint* page_size);
