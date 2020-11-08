// CPageSSDT.cpp: 实现文件
//

#include "pch.h"
#include "MyPcHunter.h"
#include "CPageSSDT.h"
#include "afxdialogex.h"


// CPageSSDT 对话框

IMPLEMENT_DYNAMIC(CPageSSDT, CDialogEx)

CPageSSDT::CPageSSDT(CWnd* pParent /*=nullptr*/)
	: CDialogEx(PAGE_KERNELHOOK_SSDT, pParent)
{

}

CPageSSDT::~CPageSSDT()
{
}

void CPageSSDT::AutoSize()
{
	//取对话框客户区大小并移动lstc到指定位置
	CRect rectClient;
	GetClientRect(&rectClient);
	m_lstcSSDT.MoveWindow(rectClient, TRUE);
	//设置lstc列宽
	int nHeaderWidth = rectClient.right - rectClient.left;
	int nCol = 0;
	m_lstcSSDT.SetColumnWidth(nCol++, (int)(0.1 * nHeaderWidth));
	m_lstcSSDT.SetColumnWidth(nCol++, (int)(0.25 * nHeaderWidth));
	m_lstcSSDT.SetColumnWidth(nCol++, (int)(0.15 * nHeaderWidth));
	m_lstcSSDT.SetColumnWidth(nCol++, (int)(0.1 * nHeaderWidth));
	m_lstcSSDT.SetColumnWidth(nCol++, (int)(0.15 * nHeaderWidth));
	m_lstcSSDT.SetColumnWidth(nCol++, (int)(0.25 * nHeaderWidth));
}

void CPageSSDT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, LSTC_SSDT, m_lstcSSDT);
}


BEGIN_MESSAGE_MAP(CPageSSDT, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPageSSDT 消息处理程序


BOOL CPageSSDT::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//列表风格
	m_lstcSSDT.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); // 整行选择、网格线
	//列表添加表头
	int nCol = 0;
	m_lstcSSDT.InsertColumn(nCol++, _T("序号"), LVCFMT_LEFT);
	m_lstcSSDT.InsertColumn(nCol++, _T("函数名称"), LVCFMT_LEFT);
	m_lstcSSDT.InsertColumn(nCol++, _T("当前函数地址"), LVCFMT_LEFT);
	m_lstcSSDT.InsertColumn(nCol++, _T("Hook"), LVCFMT_LEFT);
	m_lstcSSDT.InsertColumn(nCol++, _T("原始函数地址"), LVCFMT_LEFT);
	m_lstcSSDT.InsertColumn(nCol++, _T("当前函数地址所在模块"), LVCFMT_LEFT);
	//自适应窗口
	AutoSize();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CPageSSDT::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		if (::IsWindow(m_lstcSSDT))
		{
			AutoSize();
		}
	}
}
