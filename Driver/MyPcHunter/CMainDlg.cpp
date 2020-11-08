// CMainDlg.cpp: 实现文件
//

#include "pch.h"
#include "MyPcHunter.h"
#include "CMainDlg.h"
#include "afxdialogex.h"

// CMainDlg 对话框

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DLG_MAIN, pParent)
{
	//获取对象实例
	m_pInstance = CService::get_instance();
}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::AutoSize()
{
	//取对话框客户区大小并移动tab到指定位置
	CRect rectClient;
	GetClientRect(&rectClient);
	m_tabMain.MoveWindow(rectClient, TRUE);
	//调整子对话框在tab中的位置
	m_tabMain.GetClientRect(&rectClient);
	rectClient.top += 26;
	//设置子对话框尺寸并移动到指定位置
	m_pageProcess.MoveWindow(rectClient, TRUE);
	m_pageKernel.MoveWindow(rectClient, TRUE);
	m_pageKernelHook.MoveWindow(rectClient, TRUE);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, TAB_MAIN, m_tabMain);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, TAB_MAIN, &CMainDlg::OnTcnSelchangeMain)
END_MESSAGE_MAP()


// CMainDlg 消息处理程序


BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//tab控件添加页
	unsigned int nTabItem = 0;
	m_tabMain.InsertItem(nTabItem++, "进程");
	m_tabMain.InsertItem(nTabItem++, "内核");
	m_tabMain.InsertItem(nTabItem++, "内核钩子");

	//关联对话框,并且将TAB_MAIN控件设为父窗口
	m_pageProcess.Create(PAGE_PROCESS, GetDlgItem(TAB_MAIN));
	m_pageKernel.Create(PAGE_KERNEL, GetDlgItem(TAB_MAIN));
	m_pageKernelHook.Create(PAGE_KERNELHOOK, GetDlgItem(TAB_MAIN));
	//自适应窗口
	AutoSize();

	//分别设置隐藏和显示
	m_pageProcess.ShowWindow(true);
	m_pageKernel.ShowWindow(false);
	m_pageKernelHook.ShowWindow(false);

	//设置默认的选项卡
	m_tabMain.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CMainDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		if (::IsWindow(m_tabMain) && ::IsWindow(m_pageProcess) && ::IsWindow(m_pageKernel))
		{
			AutoSize();
		}
	}
}


void CMainDlg::OnTcnSelchangeMain(NMHDR* pNMHDR, LRESULT* pResult)
{

	// TODO: 在此添加控件通知处理程序代码
	switch (m_tabMain.GetCurSel())
	{
	case 0:
		m_pageProcess.ShowWindow(SW_SHOW);
		m_pageKernel.ShowWindow(SW_HIDE);
		m_pageKernelHook.ShowWindow(SW_HIDE);
		m_pageProcess.SetFocus();
		break;
	case 1:
		m_pageKernel.ShowWindow(SW_SHOW);
		m_pageProcess.ShowWindow(SW_HIDE);
		m_pageKernelHook.ShowWindow(SW_HIDE);
		m_pageKernel.SetFocus();
		break;
	case 2:
		m_pageKernelHook.ShowWindow(SW_SHOW);
		m_pageProcess.ShowWindow(SW_HIDE);
		m_pageKernel.ShowWindow(SW_HIDE);
		m_pageKernelHook.SetFocus();
		break;
	default:
		break;
	}
	*pResult = 0;
}
