#ifdef __cplusplus
extern "C" {
#endif

#include <ntddk.h>
#include <devioctl.h>
#include "common.h"
#include "struct.h"

//函数声明
NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDriverObj, IN PUNICODE_STRING pRegistryString);
VOID DriverUnload(IN PDRIVER_OBJECT pDriverObj);
NTSTATUS DispatchCreate(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
NTSTATUS DispatchClose(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
NTSTATUS DispatchControl(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
//获取核心数
ULONG GetCoreNumbers(PVOID pOutBuff);
//获取GDT地址
ULONG GetGdtAddr(ULONG ulCoreIndex, PVOID pOutBuff);
//获取GDT
ULONG GetGdt(tagGDTR* pGDTR, PVOID pOutBuff);

//////////////////////////////////////////////////////////////////////////

//使用内存池	PAGE为分页内存池	INIT为初始化内存池
#pragma alloc_text("INIT", DriverEntry)
#pragma alloc_text("PAGE", DriverUnload)
#pragma alloc_text("PAGE", DispatchCreate)
#pragma alloc_text("PAGE", DispatchClose)
#pragma alloc_text("PAGE", DispatchControl)



#ifdef __cplusplus
}
#endif