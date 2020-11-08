// CPageProcess.cpp: 实现文件
//

#include "pch.h"
#include "MyPcHunter.h"
#include "CPageProcess.h"
#include "afxdialogex.h"


// CPageProcess 对话框

IMPLEMENT_DYNAMIC(CPageProcess, CDialogEx)

CPageProcess::CPageProcess(CWnd* pParent /*=nullptr*/)
	: CDialogEx(PAGE_PROCESS, pParent)
{

}

CPageProcess::~CPageProcess()
{
}

void CPageProcess::AutoSize()
{
	//取对话框客户区大小并移动lstc到指定位置
	CRect rectClient;
	GetClientRect(&rectClient);
	m_lstcProcess.MoveWindow(rectClient, TRUE);
	//设置lstc列宽
	int nHeaderWidth = rectClient.right - rectClient.left;
	int nCol = 0;
	m_lstcProcess.SetColumnWidth(nCol++, (int)(0.216 * nHeaderWidth));
	m_lstcProcess.SetColumnWidth(nCol++, (int)(0.067 * nHeaderWidth));
	m_lstcProcess.SetColumnWidth(nCol++, (int)(0.067 * nHeaderWidth));
	m_lstcProcess.SetColumnWidth(nCol++, (int)(0.270 * nHeaderWidth));
	m_lstcProcess.SetColumnWidth(nCol++, (int)(0.094 * nHeaderWidth));
	m_lstcProcess.SetColumnWidth(nCol++, (int)(0.108 * nHeaderWidth));
	m_lstcProcess.SetColumnWidth(nCol++, (int)(0.178 * nHeaderWidth));
}

void CPageProcess::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, LSTC_PROCESS, m_lstcProcess);
}


BEGIN_MESSAGE_MAP(CPageProcess, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPageProcess 消息处理程序


BOOL CPageProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//列表风格
	m_lstcProcess.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); // 整行选择、网格线
	//列表添加表头
	int nCol = 0;
	m_lstcProcess.InsertColumn(nCol++, _T("映像名称"), LVCFMT_LEFT);
	m_lstcProcess.InsertColumn(nCol++, _T("进程ID"), LVCFMT_LEFT);
	m_lstcProcess.InsertColumn(nCol++, _T("父进程ID"), LVCFMT_LEFT);
	m_lstcProcess.InsertColumn(nCol++, _T("映像路径"), LVCFMT_LEFT);
	m_lstcProcess.InsertColumn(nCol++, _T("EPROCESS"), LVCFMT_LEFT);
	m_lstcProcess.InsertColumn(nCol++, _T("应用层访问状态"), LVCFMT_LEFT);
	m_lstcProcess.InsertColumn(nCol++, _T("文件厂商"), LVCFMT_LEFT);

	/*int nSmallCx = ::GetSystemMetrics(SM_CXSMICON);
	int nSmallCy = ::GetSystemMetrics(SM_CYSMICON);
	CImageList ProcessImage;
	ProcessImage.Create(nSmallCx, nSmallCy, ILC_COLOR32, 0, 1);
	m_lstcProcess.SetImageList(&ProcessImage, LVSIL_NORMAL);

	for (i = 0; i < 2; i++)
	{
		LVITEM lvitem;
		lvitem.mask = LVIF_IMAGE | LVIF_TEXT;
		lvitem.iItem = i;
		lvitem.pszText = " hello";
		lvitem.iImage = i;
		lvitem.iSubItem = 0;
		m_listctrl.InsertItem(&lvitem);
	}*/

	//自适应窗口
	AutoSize();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CPageProcess::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		if (::IsWindow(m_lstcProcess))
		{
			AutoSize();
		}
	}
}