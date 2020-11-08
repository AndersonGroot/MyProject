#pragma once

#include <ntddk.h> 

/*
解析数据的结构体
对齐值为1位
*/
#pragma pack(push)
#pragma pack(1)

//GDTR结构体
typedef struct tagGDTR {
	unsigned short sLimit;
	unsigned int nAddr;
}tagGDTR;

//GDT表项结构体
typedef struct tagGDT {
	unsigned int limit_0 : 16;
	unsigned int base_16 : 16;
	unsigned int base_32 : 8;
	unsigned int Type : 4;
	unsigned int S : 1;
	unsigned int DPL : 2;
	unsigned int P : 1;
	unsigned int limit_48 : 4;
	unsigned int AVL : 1;
	unsigned int L : 1;
	unsigned int DB : 1;
	unsigned int G : 1;
	unsigned int base_56 : 8;
}tagGDT;


#pragma pack(pop)