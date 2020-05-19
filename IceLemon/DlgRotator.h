#pragma once
#include "afxwin.h"

class CIceLemonDlg;
// CDlgRotator 对话框

class CDlgRotator : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRotator)

public:
	CDlgRotator(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgRotator();

	int SetContext(CIceLemonDlg *context);

// 对话框数据
	enum { IDD = IDD_DLG_ROTATOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CIceLemonDlg *pIceLemonDlg;
	virtual BOOL OnInitDialog();
	CCheckListBox m_clbRotator;
	afx_msg void OnBnClickedBtnRotatorSelectall();
};
