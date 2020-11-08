#include "pch.h"
#include "CService.h"

//��̬�ֲ�������ʼ��
CService::SmartPtr CService::m_pInstance;
std::mutex CService::m_mutex;

CService::~CService()
{
	SafeExit();
}

CService::SmartPtr CService::get_instance()
{
	if (m_pInstance == nullptr) {
		//������������̻߳�ȡ���������ظ���
		std::lock_guard<std::mutex> lk(m_mutex);
		if (m_pInstance == nullptr) {
			m_pInstance = std::shared_ptr<CService>(new CService);
		}
	}

	return m_pInstance;
}

CService::CService()
{
	//��ȡ��������·��
	CString strExePath;
	GetModuleFileName(NULL, strExePath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	strExePath.ReleaseBuffer();
	int nPos = strExePath.ReverseFind(L'\\');
	strExePath = strExePath.Left(nPos);
	strExePath.Append("\\FirstDriver.sys");
	//������ʼ��
	m_strServiceName = "MyPcHunterService";
	m_strPath = strExePath;
	m_hDevice = NULL;
	//��������
	BOOL bRet = SvcInstall();
	if (!bRet)
	{
		SafeExit();
		return;
	}
	//��������
	bRet = DoStartSvc();
	if (!bRet)
	{
		SafeExit();
		return;
	}
	//���豸
	bRet = DoOpenDev();
	if (!bRet)
	{
		SafeExit();
		return;
	}
}

BOOL CService::SvcInstall()
{
	//�򿪷��������
	SC_HANDLE scManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!scManager)
	{
		AfxMessageBox("��������ʱ�򿪷��������ʧ��");
		return FALSE;
	}


	//��������
	SC_HANDLE scService = CreateService(scManager,
		m_strServiceName,
		m_strServiceName,
		SERVICE_ALL_ACCESS,
		SERVICE_KERNEL_DRIVER,
		SERVICE_DEMAND_START,
		SERVICE_ERROR_NORMAL,
		m_strPath,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL
	);
	if (!scService)
	{
		AfxMessageBox("��������ʧ��");
		CloseServiceHandle(scService);
		return FALSE;
	}

	CloseServiceHandle(scService);
	CloseServiceHandle(scManager);
	return TRUE;
}

BOOL CService::DoStartSvc()
{
	//�򿪷��������
	SC_HANDLE scManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!scManager)
	{
		AfxMessageBox("��������ʱ�򿪷��������ʧ��");
		return FALSE;
	}

	//�򿪷���
	SC_HANDLE schService = OpenService(
		scManager,         // SCM database 
		m_strServiceName,            // name of service 
		SERVICE_ALL_ACCESS);  // full access 

	if (schService == NULL)
	{
		AfxMessageBox("��������ʱ�򿪷���ʧ��");
		CloseServiceHandle(scManager);
		return FALSE;
	}

	if (!StartService(
		schService,  // handle to service 
		0,           // number of arguments 
		NULL))      // no arguments 
	{
		AfxMessageBox("��������ʧ��");
		CloseServiceHandle(schService);
		CloseServiceHandle(scManager);
		return FALSE;
	}

	CloseServiceHandle(schService);
	CloseServiceHandle(scManager);
	return TRUE;
}

BOOL CService::DoStopSvc()
{
	SERVICE_STATUS_PROCESS ssp;
	SC_HANDLE schSCManager;
	SC_HANDLE schService;
	// Get a handle to the SCM database. 

	schSCManager = OpenSCManager(
		NULL,                    // local computer
		NULL,                    // ServicesActive database 
		SC_MANAGER_ALL_ACCESS);  // full access rights 

	if (NULL == schSCManager)
	{
		AfxMessageBox("�رշ���ʱ�򿪷��������ʧ��");
		return FALSE;
	}

	// Get a handle to the service.

	schService = OpenService(
		schSCManager,         // SCM database 
		m_strServiceName,            // name of service 
		SERVICE_STOP |
		SERVICE_QUERY_STATUS |
		SERVICE_ENUMERATE_DEPENDENTS);

	if (schService == NULL)
	{
		CloseServiceHandle(schSCManager);
		return FALSE;
	}

	if (!ControlService(
		schService,
		SERVICE_CONTROL_STOP,
		(LPSERVICE_STATUS)&ssp))
	{
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		return FALSE;
	}

	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);
	return TRUE;
}

BOOL CService::DoDeleteSvc()
{
	SC_HANDLE schSCManager;
	SC_HANDLE schService;
	SERVICE_STATUS ssStatus;

	// Get a handle to the SCM database. 

	schSCManager = OpenSCManager(
		NULL,                    // local computer
		NULL,                    // ServicesActive database 
		SC_MANAGER_ALL_ACCESS);  // full access rights 

	if (NULL == schSCManager)
	{
		AfxMessageBox("ж�ط���ʱ�򿪷��������ʧ��");
		return FALSE;
	}

	// Get a handle to the service.

	schService = OpenService(
		schSCManager,       // SCM database 
		m_strServiceName,          // name of service 
		DELETE);            // need delete access 
	if (schService == NULL)
	{
		CloseServiceHandle(schSCManager);
		return FALSE;
	}

	// Delete the service.
	if (!DeleteService(schService))
	{
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		return FALSE;
	}

	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);
	return TRUE;
}

BOOL CService::DoOpenDev()
{
	m_hDevice = CreateFile("\\\\?\\MyPcHunter",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (m_hDevice == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox("���豸ʧ��");
		return FALSE;
	}

	return TRUE;
}

BOOL CService::DoCtrlDev(int nCtrlCode, LPVOID pInBuf, int nInBufLenth, LPVOID pOutBuf, int nOutBufLenth, DWORD* pRecBytes)
{
	if (!DeviceIoControl(m_hDevice, MY_CTL_CODE(nCtrlCode), pInBuf, nInBufLenth,
		pOutBuf, nOutBufLenth, pRecBytes, NULL))
	{
		AfxMessageBox("�����豸ʧ��");
		//��������
		return FALSE;
	}
	return TRUE;
}

void CService::DoCloseDev()
{
	//�ر��豸
	if (m_hDevice != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hDevice);
	}
}

void CService::SafeExit()
{
	//�ر��豸
	DoCloseDev();
	//�رշ���
	DoStopSvc();
	//ж�ط���
	DoDeleteSvc();
}
