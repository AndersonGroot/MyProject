#ifdef __cplusplus
extern "C" {
#endif

#pragma once
#include "FirstDriver.h"


//
//��ں���
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
	
	//�����豸����
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
	
	//������ͨѶ��ʽ
	pDevObj->Flags |=  DO_BUFFERED_IO;
	
	//������������
	RtlInitUnicodeString(&ustrSymbolName, SYMBOLIC_LINK_NAME);
	IoCreateSymbolicLink(&ustrSymbolName, &ustrDevName);
	if (!NT_SUCCESS(status))
	{
		dprintf("[DriverEntry] IoCreateSymbolicLink Error status=%p\n", status);
		return status;
	}
	dprintf("[DriverEntry] IoCreateSymbolicLink OK\n");
	
	//ע����ǲ����
	pDriverObj->MajorFunction[IRP_MJ_CREATE]         = DispatchCreate;
	pDriverObj->MajorFunction[IRP_MJ_CLOSE]          = DispatchClose;
	pDriverObj->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DispatchControl;
	
	//ע��ж�غ���
	pDriverObj->DriverUnload = DriverUnload;
	dprintf("[DriverEntry] Driver load");
	return status;		//�ɹ�������STATUS_SUCCESS
}

//
//ж�غ����ص�
//
VOID DriverUnload(IN PDRIVER_OBJECT pDriverObj)
{
    UNICODE_STRING ustrSymbolName;
	
	dprintf("[DriverUnload] Driver unload\n");
	//ɾ���豸
    if (pDriverObj->DeviceObject != NULL)
	{
		IoDeleteDevice(pDriverObj->DeviceObject);
	}

    //ɾ����������
    RtlInitUnicodeString(&ustrSymbolName, SYMBOLIC_LINK_NAME);
    IoDeleteSymbolicLink(&ustrSymbolName);
	return;
}

//
//Create��ǲ�����ص�
//
NTSTATUS DispatchCreate(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	//�������
	Irp->IoStatus.Status = STATUS_SUCCESS;      //�����ɹ�
	Irp->IoStatus.Information = 0;        		//�����ĳ���
	//��ǲ����ȷ�����
	IoCompleteRequest(Irp, IO_NO_INCREMENT);    //IO_NO_INCREMENT����������Ȩ
	
	dprintf("[DispatchCreate]\n");
	return STATUS_SUCCESS; 
}

//
//Close��ǲ�����ص�
//
NTSTATUS DispatchClose(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	//�������
	Irp->IoStatus.Status = STATUS_SUCCESS;      //�����ɹ�
	Irp->IoStatus.Information = 0;        		//�����ĳ���
	//��ǲ����ȷ�����
	IoCompleteRequest(Irp, IO_NO_INCREMENT);    //IO_NO_INCREMENT����������Ȩ
	
	dprintf("[DispatchClose]\n");
	return STATUS_SUCCESS; 
}

//
//Control��ǲ�����ص�
//
NTSTATUS DispatchControl(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	NTSTATUS status = STATUS_INVALID_DEVICE_REQUEST;	 // STATUS_UNSUCCESSFUL
	//��ȡirp��ջ
	PIO_STACK_LOCATION pIrpStack = IoGetCurrentIrpStackLocation(Irp);
	//��ȡ������
	PVOID pBuffer = Irp->AssociatedIrp.SystemBuffer;      
	//��ȡ��������С
	ULONG nInLength = pIrpStack->Parameters.DeviceIoControl.InputBufferLength;
	ULONG nOutLength = pIrpStack->Parameters.DeviceIoControl.OutputBufferLength;
	ULONG nIoControlCode = pIrpStack->Parameters.DeviceIoControl.IoControlCode;
	
	//ָ��
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
			//��ȡ���ĸ���
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
			//תΪGDTR�ṹ��ָ�룬��ȡlimit
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
	
	
	//�������
	Irp->IoStatus.Status = STATUS_SUCCESS;      //�����ɹ�
	Irp->IoStatus.Information = nOperateLength;        //�����ĳ���
	//��ǲ����ȷ�����
	IoCompleteRequest(Irp, IO_NO_INCREMENT);    //IO_NO_INCREMENT����������Ȩ
	return status; 
}

//
//��ȡ���ĸ�������
//
ULONG GetCoreNumbers(PVOID pOutBuff)
{
	//��ȡ���ĸ�������
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
//��ȡָ���˵�GDT��ַ
//
ULONG GetGdtAddr(ULONG ulCoreIndex, PVOID pOutBuff)
{
	//��ȡ����CPU�ˣ�int�������롣
	KAFFINITY CoreMask = 1;
	char GDTR[6];
	
	CoreMask <<= ulCoreIndex;
	//���õ�ǰ���е�cpu����
	KeSetSystemAffinityThread(CoreMask);

    //��ȡGDT��ĵ�ַ�ʹ�С
    __asm
    {
        sgdt GDTR;	
    }
	
	//����������������
	RtlCopyMemory(pOutBuff, GDTR, sizeof(GDTR));
	dprintf("[GetGdtAddr] GDTAddr=%p  size=%x\n", *(ULONG_PTR*)((char*)pOutBuff+2), *(short*)pOutBuff);

	//���ز�������
	return (ULONG)sizeof(GDTR);
	
}

//
//��ȡָ��GDT��ַ��GDT��
//
ULONG GetGdt(tagGDTR* pGDTR, PVOID pOutBuff)
{
	//����ռ�
	char szGDT[0x400];
	//������С
	ULONG ulOutLength = (pGDTR->sLimit + 1);
	//����GDT����
	short sGdtNum = (pGDTR->sLimit + 1) / sizeof(tagGDT);
	//����ƫ��
	ULONG ulOffset = 0;
	
	dprintf("[GetGdt] Limit:%d Addr:%p\n", pGDTR->sLimit, pGDTR->nAddr);
	dprintf("[GetGdt] GDTNumber:%d\n", sGdtNum);
	while(sGdtNum != 0)
	{
		//��������
		RtlCopyMemory(((tagGDT*)szGDT) + ulOffset, ((tagGDT*)pGDTR->nAddr) + ulOffset, sizeof(tagGDT));
		ulOffset++;
		sGdtNum--;
	}
	dprintf("[GetGdt] nOperateLength:%d\n", pGDTR->sLimit + 1);
	RtlCopyMemory(pOutBuff, szGDT, pGDTR->sLimit + 1);
	//���ز�������
	return ulOutLength;
}



#ifdef __cplusplus
}
#endif