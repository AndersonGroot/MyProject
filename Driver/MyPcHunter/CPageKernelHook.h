#pragma once
#include "CPageSSDT.h"

// CPageKernelHook 对话框

class CPageKernelHook : public CDialogEx
{
	DECLARE_DYNAMIC(CPageKernelHook)

public:
	CPageKernelHook(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPageKernelHook();
	void AutoSize();							//自适应窗口

private:
	CPageSSDT m_pageSSDT;		//GDT对话框

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = PAGE_KERNELHOOK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 内核钩子tab
	CTabCtrl m_tabKernelHook;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeTabKernelhook(NMHDR* pNMHDR, LRESULT* pResult);
};
