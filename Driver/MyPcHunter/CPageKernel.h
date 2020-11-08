#pragma once

#include "CPageGDT.h"
// CPageKernel 对话框

class CPageKernel : public CDialogEx
{
	DECLARE_DYNAMIC(CPageKernel)

public:
	CPageKernel(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPageKernel();
	void AutoSize();					//自适应窗口

private:
	CPageGDT m_pageGDT;		//GDT对话框

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = PAGE_KERNEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 内核tab控件
	CTabCtrl m_tabKernel;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTcnSelchangeChild(NMHDR* pNMHDR, LRESULT* pResult);
};
