
// MyPcHunter.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "MyPcHunter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyPcHunterApp

BEGIN_MESSAGE_MAP(CMyPcHunterApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMyPcHunterApp 构造

CMyPcHunterApp::CMyPcHunterApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	m_hMutex = NULL;
}

CMyPcHunterApp::~CMyPcHunterApp()
{
	//释放
	if (m_hMutex != NULL)
	{
		ReleaseMutex(m_hMutex);
		CloseHandle(m_hMutex);
		m_hMutex = NULL;
	}
}


// 唯一的 CMyPcHunterApp 对象

CMyPcHunterApp theApp;


// CMyPcHunterApp 初始化

BOOL CMyPcHunterApp::InitInstance()
{
	//单例进程模式
	m_hMutex = ::CreateMutex(NULL, TRUE, _T("CSSegment"));
	if (m_hMutex != NULL)
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			AfxMessageBox(_T("程序已经运行!"));
			CloseHandle(m_hMutex);
			return   FALSE;
		}
	}
	CMainDlg dlgMain;
	dlgMain.DoModal();

	return TRUE;
}

