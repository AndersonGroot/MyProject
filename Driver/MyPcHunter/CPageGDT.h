#pragma once

#include "CService.h"
// CPageGDT 对话框

class CPageGDT : public CDialogEx
{
	DECLARE_DYNAMIC(CPageGDT)

public:
	CPageGDT(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPageGDT();
	void AutoSize();						//控件自适应窗口

private:
	ULONG GetCoreNumbers();												//获取核心数
	void GetGDTAddr(ULONG ulCores, LPVOID pGDTAddr);					//获取GDT地址
	void GetGDT(LPVOID pGDTAddr, LPVOID pGDT, ULONG nGDTLenth);			//获取GDT表
	void DrawList();													//画表

private:
	CService::SmartPtr m_pInstance;	//CService的智能指针
	ULONG m_ulCores;				//核心总数
	tagGDTR* m_pGDTAddr;			//GDT地址结构体指针
	tagGDT* m_pGDT;					//保存GDT表的结构体指针

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = PAGE_KERNEL_GDT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// GDT表
	CListCtrl m_lstcGDT;
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
