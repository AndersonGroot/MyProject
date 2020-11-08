#pragma once


// CPageProcess 对话框

class CPageProcess : public CDialogEx
{
	DECLARE_DYNAMIC(CPageProcess)

public:
	CPageProcess(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPageProcess();
	void AutoSize();						//控件自适应窗口

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = PAGE_PROCESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 进程列表控件
	CListCtrl m_lstcProcess;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
