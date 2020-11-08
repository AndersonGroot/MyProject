#pragma once

#include <memory> // 智能指针
#include <mutex>  // 互斥体
#include <Winsvc.h>
#include "common.h"

//定义控制码和设置控制派遣函数的通讯方式METHOD_BUFFERED
#define MY_CTL_CODE(code)  CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800 + code, METHOD_BUFFERED , FILE_ANY_ACCESS)
#define KERNAL_GDT_CORES 0
#define KERNAL_GDT_ADDR  1
#define KERNAL_GDT_GET   2

class CService
{
public:
	//构造一个智能指针
	typedef std::shared_ptr<CService> SmartPtr;
	~CService();
	static SmartPtr get_instance();
	//控制设备
	BOOL DoCtrlDev(int nCtrlCode, LPVOID pInBuf, int nInBufLenth, LPVOID pOutBuf, int nOutBufLenth, DWORD* pRecBytes);
private:
	CService();

	//防止拷贝构造
	CService(CService&) = delete;
	CService& operator=(const CService&) = delete;
	//创建服务
	BOOL SvcInstall();
	//启动服务
	BOOL DoStartSvc();
	//关闭服务
	BOOL DoStopSvc();
	//卸载服务
	BOOL DoDeleteSvc();
	//打开设备
	BOOL DoOpenDev();
	//关闭设备
	void DoCloseDev();
	//安全退出
	void SafeExit();

private:
	static SmartPtr m_pInstance;
	static std::mutex m_mutex;
	CString m_strServiceName;		//服务名称
	CString m_strPath;				//驱动路径
	HANDLE m_hDevice;				//设备句柄
};

