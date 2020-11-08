#pragma once

#include <memory> // ����ָ��
#include <mutex>  // ������
#include <Winsvc.h>
#include "common.h"

//�������������ÿ�����ǲ������ͨѶ��ʽMETHOD_BUFFERED
#define MY_CTL_CODE(code)  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800 + code, METHOD_BUFFERED , FILE_ANY_ACCESS)
#define KERNAL_GDT_CORES 0
#define KERNAL_GDT_ADDR  1
#define KERNAL_GDT_GET   2

class CService
{
public:
	//����һ������ָ��
	typedef std::shared_ptr<CService> SmartPtr;
	~CService();
	static SmartPtr get_instance();
	//�����豸
	BOOL DoCtrlDev(int nCtrlCode, LPVOID pInBuf, int nInBufLenth, LPVOID pOutBuf, int nOutBufLenth, DWORD* pRecBytes);
private:
	CService();

	//��ֹ��������
	CService(CService&) = delete;
	CService& operator=(const CService&) = delete;
	//��������
	BOOL SvcInstall();
	//��������
	BOOL DoStartSvc();
	//�رշ���
	BOOL DoStopSvc();
	//ж�ط���
	BOOL DoDeleteSvc();
	//���豸
	BOOL DoOpenDev();
	//�ر��豸
	void DoCloseDev();
	//��ȫ�˳�
	void SafeExit();

private:
	static SmartPtr m_pInstance;
	static std::mutex m_mutex;
	CString m_strServiceName;		//��������
	CString m_strPath;				//����·��
	HANDLE m_hDevice;				//�豸���
};

