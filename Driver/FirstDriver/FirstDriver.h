#ifdef __cplusplus
extern "C" {
#endif

#include <ntddk.h>
#include <devioctl.h>
#include "common.h"
#include "struct.h"

//��������
NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDriverObj, IN PUNICODE_STRING pRegistryString);
VOID DriverUnload(IN PDRIVER_OBJECT pDriverObj);
NTSTATUS DispatchCreate(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
NTSTATUS DispatchClose(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
NTSTATUS DispatchControl(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
//��ȡ������
ULONG GetCoreNumbers(PVOID pOutBuff);
//��ȡGDT��ַ
ULONG GetGdtAddr(ULONG ulCoreIndex, PVOID pOutBuff);
//��ȡGDT
ULONG GetGdt(tagGDTR* pGDTR, PVOID pOutBuff);

//////////////////////////////////////////////////////////////////////////

//ʹ���ڴ��	PAGEΪ��ҳ�ڴ��	INITΪ��ʼ���ڴ��
#pragma alloc_text("INIT", DriverEntry)
#pragma alloc_text("PAGE", DriverUnload)
#pragma alloc_text("PAGE", DispatchCreate)
#pragma alloc_text("PAGE", DispatchClose)
#pragma alloc_text("PAGE", DispatchControl)



#ifdef __cplusplus
}
#endif