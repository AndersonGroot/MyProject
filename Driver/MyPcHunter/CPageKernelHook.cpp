// CPageKernelHook.cpp: 实现文件
//

#include "pch.h"
#include "MyPcHunter.h"
#include "CPageKernelHook.h"
#include "afxdialogex.h"


// CPageKernelHook 对话框

IMPLEMENT_DYNAMIC(CPageKernelHook, CDialogEx)

CPageKernelHook::CPageKernelHook(CWnd* pParent /*=nullptr*/)
	: CDialogEx(PAGE_KERNELHOOK, pParent)
{

}

CPageKernelHook::~CPageKernelHook()
{
}

void CPageKernelHook::AutoSize()
{
	//取对话框客户区大小并移动tab到指定位置
	CRect rectClient;
	GetClientRect(&rectClient);
	m_tabKernelHook.MoveWindow(rectClient, TRUE);
	//调整子对话框在tab中的位置
	m_tabKernelHook.GetClientRect(&rectClient);
	rectClient.top += 22;
	//设置子对话框尺寸并移动到指定位置
	m_pageSSDT.MoveWindow(rectClient, TRUE);
}

void CPageKernelHook::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, TAB_KERNELHOOK, m_tabKernelHook);
}


BEGIN_MESSAGE_MAP(CPageKernelHook, CDialogEx)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, TAB_KERNELHOOK, &CPageKernelHook::OnSelchangeTabKernelhook)
END_MESSAGE_MAP()


// CPageKernelHook 消息处理程序


BOOL CPageKernelHook::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//tab控件添加页
	m_tabKernelHook.InsertItem(0, "SSDT");

	//关联对话框,并且将TAB_MAIN控件设为父窗口
	m_pageSSDT.Create(PAGE_KERNELHOOK_SSDT, GetDlgItem(TAB_KERNELHOOK));

	//自适应窗口
	AutoSize();

	//分别设置隐藏和显示
	m_pageSSDT.ShowWindow(true);

	//设置默认的选项卡
	m_tabKernelHook.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CPageKernelHook::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		if (::IsWindow(m_tabKernelHook) && ::IsWindow(m_pageSSDT))
		{
			AutoSize();
		}
	}
}


void CPageKernelHook::OnSelchangeTabKernelhook(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
