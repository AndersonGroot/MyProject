#pragma once
#include <mutex>

#include "CService.h"
#include "CPageKernel.h"
#include "CPageProcess.h"
#include "CPageKernelHook.h"
// CMainDlg 对话框

class CMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMainDlg();
	void AutoSize();					//自适应窗口

private:
	CService::SmartPtr m_pInstance;		//CService的智能指针
	CPageKernel m_pageKernel;			//内核对话框分页
	CPageProcess m_pageProcess;			//进程对话框分页
	CPageKernelHook m_pageKernelHook;	//内核钩子对话框分页

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DLG_MAIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 主tab控件
	CTabCtrl m_tabMain;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTcnSelchangeMain(NMHDR* pNMHDR, LRESULT* pResult);
};
