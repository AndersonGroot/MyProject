#pragma once


// CPageSSDT 对话框

class CPageSSDT : public CDialogEx
{
	DECLARE_DYNAMIC(CPageSSDT)

public:
	CPageSSDT(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPageSSDT();
	void AutoSize();						//控件自适应窗口


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = PAGE_KERNELHOOK_SSDT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// SSDT表列表
	CListCtrl m_lstcSSDT;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
