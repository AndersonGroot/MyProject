#pragma once
#include <WinIoCtl.h>
#include <Windows.h>

/*
�������ݵĽṹ��
����ֵΪ1λ
*/
#pragma pack(push)
#pragma pack(1)

//GDTR�ṹ��
typedef struct tagGDTR {
	unsigned short sLimit;
	unsigned int nAddr;
}tagGDTR;

//GDT����ṹ��
typedef struct tagGDT {
	unsigned int limit_0 : 16;
	unsigned int base_16 : 16;
	unsigned int base_32 : 8;
    unsigned int A : 1;
    unsigned int WR : 1;
    unsigned int EC : 1;
    unsigned int flag : 1;
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

//���ڽ����λ�ַ�Ͷν���
typedef struct _SEGMENT_BASE_LIMIT
{
    union
    {
        unsigned int nSegLimit;

        struct
        {
            unsigned int nSegtLimit_0_15 : 16;
            unsigned int nSegtLimit_16_19 : 4;
        }SegLimitChild;
    }SegmentLimit;

    union
    {
        unsigned int nSegBase;

        struct
        {
            unsigned int nSegBase_0_15 : 16;
            unsigned int nSegBase_16_23 : 8;
            unsigned int nSegBase_24_31 : 8;
        }SegBaseChild;

    }SegmentBase;

}SEGMENT_BASE_LIMIT, P_SEGMENT_BASE_LIMIT;

//���ڽ���������������
typedef struct _SEGMENT_TYPE
{
    union
    {
        unsigned char chType;

        struct
        {
            unsigned int A : 1;
            unsigned int WR : 1;
            unsigned int EC : 1;
            unsigned int flag : 1;
        }TypeChild;
    }SegmentType;

}SEGMENT_TYPE, P_SEGMENT_TYPE;

#pragma pack(pop)