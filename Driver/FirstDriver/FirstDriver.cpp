#ifdef __cplusplus
extern "C" {
#endif

#pragma once
#include "FirstDriver.h"


//
//入口函数
//
NTSTATUS DriverEntry(
IN PDRIVER_OBJECT pDriverObj, 
IN PUNICODE_STRING pRegistryString
)
{
	NTSTATUS status = STATUS_SUCCESS;
	UNICODE_STRING ustrDevName;
	UNICODE_STRING ustrSymbolName;
	PDEVICE_OBJECT pDevObj = NULL;
	
	//创建设备对象
	RtlInitUnicodeString(&ustrDevName, DEVICE_NAME);
	status = IoCreateDevice(
                              pDriverObj,                         	//DriverObject
                              0,                                    //DeviceExtensionSize
                              &ustrDevName,                         //DeviceName
                              FILE_DEVICE_UNKNOWN,                  //DeviceType
                              0,                                    //DeviceCharacteristics
                              FALSE,                                //Exclusive
                              &pDevObj);                            //DeviceObject
	if (!NT_SUCCESS(status))
	{
		dprintf("[DriverEntry] IoCreateDevice Error status=%p\n", status);
		return status;
	}
	dprintf("[DriverEntry] IoCreateDevice OK pDevObj=%p\n", pDevObj);
	
	//缓冲区通讯方式
	pDevObj->Flags |=  DO_BUFFERED_IO;
	
	//创建符号链接
	RtlInitUnicodeString(&ustrSymbolName, SYMBOLIC_LINK_NAME);
	IoCreateSymbolicLink(&ustrSymbolName, &ustrDevName);
	if (!NT_SUCCESS(status))
	{
		dprintf("[DriverEntry] IoCreateSymbolicLink Error status=%p\n", status);
		return status;
	}
	dprintf("[DriverEntry] IoCreateSymbolicLink OK\n");
	
	//注册派遣函数
	pDriverObj->MajorFunction[IRP_MJ_CREATE]         = DispatchCreate;
	pDriverObj->MajorFunction[IRP_MJ_CLOSE]          = DispatchClose;
	pDriverObj->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DispatchControl;
	
	//注册卸载函数
	pDriverObj->DriverUnload = DriverUnload;
	dprintf("[DriverEntry] Driver load");
	return status;		//成功，返回STATUS_SUCCESS
}

//
//卸载函数回调
//
VOID DriverUnload(IN PDRIVER_OBJECT pDriverObj)
{
    UNICODE_STRING ustrSymbolName;
	
	dprintf("[DriverUnload] Driver unload\n");
	//删除设备
    if (pDriverObj->DeviceObject != NULL)
	{
		IoDeleteDevice(pDriverObj->DeviceObject);
	}

    //删除符号链接
    RtlInitUnicodeString(&ustrSymbolName, SYMBOLIC_LINK_NAME);
    IoDeleteSymbolicLink(&ustrSymbolName);
	return;
}

//
//Create派遣函数回调
//
NTSTATUS DispatchCreate(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	//完成请求
	Irp->IoStatus.Status = STATUS_SUCCESS;      //操作成功
	Irp->IoStatus.Information = 0;        		//操作的长度
	//派遣函数确认完成
	IoCompleteRequest(Irp, IO_NO_INCREMENT);    //IO_NO_INCREMENT不提升优先权
	
	dprintf("[DispatchCreate]\n");
	return STATUS_SUCCESS; 
}

//
//Close派遣函数回调
//
NTSTATUS DispatchClose(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	//完成请求
	Irp->IoStatus.Status = STATUS_SUCCESS;      //操作成功
	Irp->IoStatus.Information = 0;        		//操作的长度
	//派遣函数确认完成
	IoCompleteRequest(Irp, IO_NO_INCREMENT);    //IO_NO_INCREMENT不提升优先权
	
	dprintf("[DispatchClose]\n");
	return STATUS_SUCCESS; 
}

//
//Control派遣函数回调
//
NTSTATUS DispatchControl(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	NTSTATUS status = STATUS_INVALID_DEVICE_REQUEST;	 // STATUS_UNSUCCESSFUL
	//获取irp堆栈
	PIO_STACK_LOCATION pIrpStack = IoGetCurrentIrpStackLocation(Irp);
	//获取缓冲区
	PVOID pBuffer = Irp->AssociatedIrp.SystemBuffer;      
	//获取缓冲区大小
	ULONG nInLength = pIrpStack->Parameters.DeviceIoControl.InputBufferLength;
	ULONG nOutLength = pIrpStack->Parameters.DeviceIoControl.OutputBufferLength;
	ULONG nIoControlCode = pIrpStack->Parameters.DeviceIoControl.IoControlCode;
	
	//指针
	ULONG nOperateLength = 0;
	
	dprintf("[DispatchControl] nIoControlCode=%p pBuffer=%p nInLength=%p nOutLength=%p\n",
			nIoControlCode, 
			pBuffer, 
			nInLength,
			nOutLength);
	__try{
		switch(nIoControlCode) 
		{
		case KERNAL_GDT_CORES:
		{
			//获取核心个数
			nOperateLength = GetCoreNumbers(pBuffer);
			dprintf("[KERNAL_GDT_CORES] CoreNumbers=%d\r\n",*(ULONG*)pBuffer);
			dprintf("[KERNAL_GDT_CORES] nOperateLength=%d\n", nOperateLength);
			status = STATUS_SUCCESS;
			break;
		}
		case KERNAL_GDT_ADDR:
		{
			nOperateLength = GetGdtAddr(*(ULONG*)pBuffer, pBuffer);
			dprintf("[KERNAL_GDT_ADDR] GDTAddr=%p  size=%x\n", *(ULONG_PTR*)((char*)pBuffer+2), *(short*)pBuffer);
			dprintf("[KERNAL_GDT_ADDR] nOperateLength=%d\n", nOperateLength);
			status = STATUS_SUCCESS;
			break;
		}
		case KERNAL_GDT_GET:
		{
			//转为GDTR结构体指针，获取limit
			tagGDTR* pGDTR = (tagGDTR*)pBuffer;
			dprintf("[KERNAL_GDT_GET] Limit=%d Addr=%p\n", pGDTR->sLimit, pGDTR->nAddr);
			nOperateLength = GetGdt(pGDTR, pBuffer);
			dprintf("[KERNAL_GDT_GET] nOperateLength=%d\n", nOperateLength);
			status = STATUS_SUCCESS;
			break;
		}
		default:
			dprintf("[DispatchControl default]\n");
			status = STATUS_SUCCESS;
			break;
		}
	}
	__except(1) 
	{
		dprintf("__except(1)\n");
		nOperateLength = 0;
	}
	
	
	//完成请求
	Irp->IoStatus.Status = STATUS_SUCCESS;      //操作成功
	Irp->IoStatus.Information = nOperateLength;        //操作的长度
	//派遣函数确认完成
	IoCompleteRequest(Irp, IO_NO_INCREMENT);    //IO_NO_INCREMENT不提升优先权
	return status; 
}

//
//获取核心个数掩码
//
ULONG GetCoreNumbers(PVOID pOutBuff)
{
	//获取核心个数掩码
	KAFFINITY ActiveProcessors = KeQueryActiveProcessors();
	ULONG ulProcessorsNum = 0;
	
	while (ActiveProcessors != 0)
	{  
		ActiveProcessors >>= 1;
		ulProcessorsNum++;
	}
	RtlCopyMemory(pOutBuff, &ulProcessorsNum, sizeof(ulProcessorsNum));
	
	return (ULONG)sizeof(ulProcessorsNum);
}

//
//获取指定核的GDT地址
//
ULONG GetGdtAddr(ULONG ulCoreIndex, PVOID pOutBuff)
{
	//获取传入CPU核（int）的掩码。
	KAFFINITY CoreMask = 1;
	char GDTR[6];
	
	CoreMask <<= ulCoreIndex;
	//设置当前运行的cpu掩码
	KeSetSystemAffinityThread(CoreMask);

    //获取GDT表的地址和大小
    __asm
    {
        sgdt GDTR;	
    }
	
	//拷贝到传出缓冲区
	RtlCopyMemory(pOutBuff, GDTR, sizeof(GDTR));
	dprintf("[GetGdtAddr] GDTAddr=%p  size=%x\n", *(ULONG_PTR*)((char*)pOutBuff+2), *(short*)pOutBuff);

	//返回操作长度
	return (ULONG)sizeof(GDTR);
	
}

//
//获取指定GDT地址的GDT表
//
ULONG GetGdt(tagGDTR* pGDTR, PVOID pOutBuff)
{
	//申请空间
	char szGDT[0x400];
	//传出大小
	ULONG ulOutLength = (pGDTR->sLimit + 1);
	//计算GDT项数
	short sGdtNum = (pGDTR->sLimit + 1) / sizeof(tagGDT);
	//计算偏移
	ULONG ulOffset = 0;
	
	dprintf("[GetGdt] Limit:%d Addr:%p\n", pGDTR->sLimit, pGDTR->nAddr);
	dprintf("[GetGdt] GDTNumber:%d\n", sGdtNum);
	while(sGdtNum != 0)
	{
		//拷贝数据
		RtlCopyMemory(((tagGDT*)szGDT) + ulOffset, ((tagGDT*)pGDTR->nAddr) + ulOffset, sizeof(tagGDT));
		ulOffset++;
		sGdtNum--;
	}
	dprintf("[GetGdt] nOperateLength:%d\n", pGDTR->sLimit + 1);
	RtlCopyMemory(pOutBuff, szGDT, pGDTR->sLimit + 1);
	//返回操作长度
	return ulOutLength;
}



#ifdef __cplusplus
}
#endif