// CPageKernel.cpp: 实现文件
//

#include "pch.h"
#include "MyPcHunter.h"
#include "CPageKernel.h"
#include "afxdialogex.h"


// CPageKernel 对话框

IMPLEMENT_DYNAMIC(CPageKernel, CDialogEx)

CPageKernel::CPageKernel(CWnd* pParent /*=nullptr*/)
	: CDialogEx(PAGE_KERNEL, pParent)
{

}

CPageKernel::~CPageKernel()
{
}

void CPageKernel::AutoSize()
{
	//取对话框客户区大小并移动tab到指定位置
	CRect rectClient;
	GetClientRect(&rectClient);
	m_tabKernel.MoveWindow(rectClient, TRUE);
	//调整子对话框在tab中的位置
	m_tabKernel.GetClientRect(&rectClient);
	rectClient.top += 22;
	//设置子对话框尺寸并移动到指定位置
	m_pageGDT.MoveWindow(rectClient, TRUE);
}

void CPageKernel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, TAB_KERNEL, m_tabKernel);
}


BEGIN_MESSAGE_MAP(CPageKernel, CDialogEx)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, TAB_KERNEL, &CPageKernel::OnTcnSelchangeChild)
END_MESSAGE_MAP()


// CPageKernel 消息处理程序


BOOL CPageKernel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//tab控件添加页
	m_tabKernel.InsertItem(0, "GDT");

	//关联对话框,并且将TAB_MAIN控件设为父窗口
	m_pageGDT.Create(PAGE_KERNEL_GDT, GetDlgItem(TAB_KERNEL));

	//自适应窗口
	AutoSize();

	//分别设置隐藏和显示
	m_pageGDT.ShowWindow(true);

	//设置默认的选项卡
	m_tabKernel.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CPageKernel::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		if (::IsWindow(m_tabKernel) && ::IsWindow(m_pageGDT))
		{
			AutoSize();
		}
	}
}


void CPageKernel::OnTcnSelchangeChild(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
