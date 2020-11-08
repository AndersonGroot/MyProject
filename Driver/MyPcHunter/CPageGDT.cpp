// CPageGDT.cpp: 实现文件
//

#include "pch.h"
#include "MyPcHunter.h"
#include "CPageGDT.h"
#include "afxdialogex.h"

// CPageGDT 对话框

IMPLEMENT_DYNAMIC(CPageGDT, CDialogEx)

CPageGDT::CPageGDT(CWnd* pParent /*=nullptr*/)
	: CDialogEx(PAGE_KERNEL_GDT, pParent)
{
	//获取实例对象
	m_pInstance = CService::get_instance();
	//获取核心数
	m_ulCores = GetCoreNumbers();

	//获取所有GDTR
	m_pGDTAddr = new tagGDTR[m_ulCores];
	GetGDTAddr(m_ulCores, m_pGDTAddr);


	ULONG ulAllGdtSize = 0;
	//所有GDT表总大小
	for (size_t i = 0; i < m_ulCores; i++)
	{
		ulAllGdtSize += (m_pGDTAddr + i)->sLimit + 1;
	}
	ULONG ulAllGdtNum = ulAllGdtSize / sizeof(tagGDT);
	//申请内存
	m_pGDT = new tagGDT[ulAllGdtNum]{0};
	int nOffset = 0;
	//遍历cpu核心 获取所有GDT表
	for (size_t i = 0; i < m_ulCores; i++)
	{
		GetGDT(m_pGDTAddr + i, m_pGDT + nOffset, (m_pGDTAddr + i)->sLimit + 1);
		nOffset += ((m_pGDTAddr + i)->sLimit + 1) / sizeof(tagGDT);
	}
}

CPageGDT::~CPageGDT()
{
}

void CPageGDT::AutoSize()
{
	//取对话框客户区大小并移动lstc到指定位置
	CRect rectClient;
	GetClientRect(&rectClient);
	m_lstcGDT.MoveWindow(rectClient, TRUE);
	//设置lstc列宽
	int nHeaderWidth = rectClient.right - rectClient.left;
	int nCol = 0;
	m_lstcGDT.SetColumnWidth(nCol++, (int)(0.099 * nHeaderWidth));
	m_lstcGDT.SetColumnWidth(nCol++, (int)(0.099 * nHeaderWidth));
	m_lstcGDT.SetColumnWidth(nCol++, (int)(0.133 * nHeaderWidth));
	m_lstcGDT.SetColumnWidth(nCol++, (int)(0.133 * nHeaderWidth));
	m_lstcGDT.SetColumnWidth(nCol++, (int)(0.099 * nHeaderWidth));
	m_lstcGDT.SetColumnWidth(nCol++, (int)(0.099 * nHeaderWidth));
	m_lstcGDT.SetColumnWidth(nCol++, (int)(0.338 * nHeaderWidth));
}

ULONG CPageGDT::GetCoreNumbers()
{
	//获取核心数
	ULONG ulCores = 0;
	DWORD dwRecBytes = 0;
	m_pInstance->DoCtrlDev(
		KERNAL_GDT_CORES, 
		NULL, 
		0, 
		&ulCores, 
		sizeof(ulCores), 
		&dwRecBytes);
	return ulCores;
}

void CPageGDT::GetGDTAddr(ULONG ulCores, LPVOID pGDTAddr)
{
	//GDTR结构体指针
	tagGDTR* pGDTR = nullptr;
	ULONG ulOffset = 0;
	DWORD dwRecBytes = 0;
	//获取所有GDTR
	for (size_t i = 0; i < ulCores; i++)
	{
		m_pInstance->DoCtrlDev(
			KERNAL_GDT_ADDR, 
			&i, 
			sizeof(i), 
			(tagGDTR*)pGDTAddr + ulOffset, 
			sizeof(tagGDTR), 
			&dwRecBytes);
		pGDTR = (tagGDTR*)pGDTAddr + ulOffset;
		ulOffset += 1;
	}
}

void CPageGDT::GetGDT(LPVOID pGDTAddr, LPVOID pGDT, ULONG nGDTLenth)
{
	DWORD dwRecBytes = 0;
	m_pInstance->DoCtrlDev(
		KERNAL_GDT_GET,
		pGDTAddr,
		sizeof(tagGDTR),
		(tagGDTR*)pGDT,
		nGDTLenth,
		&dwRecBytes);
}


void CPageGDT::DrawList()
{
	unsigned int nRow = 0;					//行数
	unsigned int nCol = 0;					//列数
	CString strFormat;						//格式化字符串
	unsigned int nGDTIndex = 0;				//GDT表的索引值
	//核心数循环
	for (size_t i = 0; i < m_ulCores; i++)
	{
		//GDT表项数循环
		for (size_t j = 0; j < (m_pGDTAddr->sLimit + 1)/ sizeof(tagGDT); j++)
		{
			nCol = 1;
			SEGMENT_BASE_LIMIT GDT = { 0 };
			SEGMENT_TYPE Type = { 0 };
			tagGDT* pCurGDT = m_pGDT + nGDTIndex;
			//填入段基址和界限
			GDT.SegmentBase.SegBaseChild.nSegBase_0_15 = pCurGDT->base_16;
			GDT.SegmentBase.SegBaseChild.nSegBase_16_23 = pCurGDT->base_32;
			GDT.SegmentBase.SegBaseChild.nSegBase_24_31 = pCurGDT->base_56;
			GDT.SegmentLimit.SegLimitChild.nSegtLimit_0_15 = pCurGDT->limit_0;
			GDT.SegmentLimit.SegLimitChild.nSegtLimit_16_19 = pCurGDT->limit_48;
			//填入段描述符类型
			Type.SegmentType.TypeChild.A = pCurGDT->A;
			Type.SegmentType.TypeChild.WR = pCurGDT->WR;
			Type.SegmentType.TypeChild.EC = pCurGDT->EC;
			Type.SegmentType.TypeChild.flag = pCurGDT->flag;
			//判断有效位
			if (pCurGDT->P != 0)
			{
				//插入CPU核
				strFormat.Format("%d", i);
				m_lstcGDT.InsertItem(nRow, strFormat);
				//插入段选择子
				strFormat.Format("0x%04X", j);
				m_lstcGDT.SetItemText(nRow, nCol++, strFormat);
				//插入基址
				strFormat.Format("0x%08X", GDT.SegmentBase.nSegBase);
				m_lstcGDT.SetItemText(nRow, nCol++, strFormat);
				//插入界限
				strFormat.Format("0x%08X", GDT.SegmentLimit.nSegLimit);
				m_lstcGDT.SetItemText(nRow, nCol++, strFormat);
				//插入段粒度
				if (pCurGDT->G == 0)
				{
					m_lstcGDT.SetItemText(nRow, nCol++, "Byte");
				}
				else
				{
					m_lstcGDT.SetItemText(nRow, nCol++, "Page");
				}
				//插入段特权级
				strFormat.Format("%d", pCurGDT->DPL);
				m_lstcGDT.SetItemText(nRow, nCol++, strFormat);
				//插入类型
				//系统描述符
				if (pCurGDT->S == 0)
				{
					strFormat.Format("T5532");
					if (pCurGDT->A == 1 && pCurGDT->WR == 1)
					{
						strFormat.Append(" Busy");
					}
					else if(pCurGDT->A == 1 && pCurGDT->WR == 0)
					{
						strFormat.Append(" Avl");
					}
					m_lstcGDT.SetItemText(nRow++, nCol++, strFormat);
				}
				else
				{
					//数据段描述符
					if (pCurGDT->flag == 0)
					{
						strFormat.Format("Data");
						switch (Type.SegmentType.chType)
						{
						case 0:
							strFormat.Append(" RO");
							break;
						case 1:
							strFormat.Append(" RO Ac");
							break;
						case 2:
							strFormat.Append(" RW");
							break;
						case 3:
							strFormat.Append(" RW Ac");
							break;
						case 4:
							strFormat.Append(" RO E");
							break;
						case 5:
							strFormat.Append(" RO Ac E");
							break;
						case 6:
							strFormat.Append(" RW E");
							break;
						case 7:
							strFormat.Append(" RW Ac E");
							break;
						default:
							break;
						}
						m_lstcGDT.SetItemText(nRow++, nCol++, strFormat);
					}
					//代码段描述符
					else
					{
						strFormat.Format("Code");
						switch (Type.SegmentType.chType)
						{
						case 8:
							strFormat.Append(" EO");
							break;
						case 9:
							strFormat.Append(" EO Ac");
							break;
						case 10:
							strFormat.Append(" RE");
							break;
						case 11:
							strFormat.Append(" RE Ac");
							break;
						case 12:
							strFormat.Append(" EO C");
							break;
						case 13:
							strFormat.Append(" EO CA");
							break;
						case 14:
							strFormat.Append(" RE C");
							break;
						case 15:
							strFormat.Append(" RE CA");
							break;
						default:
							break;
						}
						m_lstcGDT.SetItemText(nRow++, nCol++, strFormat);
					}
				}
			}
			
			//GDT表偏移到下一项
			nGDTIndex++;
		}
	}
	
}

void CPageGDT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, LSTC_GDT, m_lstcGDT);
}


BEGIN_MESSAGE_MAP(CPageGDT, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPageGDT 消息处理程序


BOOL CPageGDT::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//列表风格
	m_lstcGDT.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); // 整行选择、网格线
	//列表添加表头
	int nCol = 0;
	m_lstcGDT.InsertColumn(nCol++, _T("CPU序号"), LVCFMT_LEFT);
	m_lstcGDT.InsertColumn(nCol++, _T("段选择子"), LVCFMT_LEFT);	
	m_lstcGDT.InsertColumn(nCol++, _T("基址"), LVCFMT_LEFT);
	m_lstcGDT.InsertColumn(nCol++, _T("界限"), LVCFMT_LEFT);
	m_lstcGDT.InsertColumn(nCol++, _T("段粒度"), LVCFMT_LEFT);
	m_lstcGDT.InsertColumn(nCol++, _T("段特权级"), LVCFMT_LEFT);
	m_lstcGDT.InsertColumn(nCol++, _T("类型"), LVCFMT_LEFT);
	//自适应窗口
	AutoSize();
	//做表
	DrawList();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CPageGDT::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		if (::IsWindow(m_lstcGDT))
		{
			AutoSize();
		}
	}
}
