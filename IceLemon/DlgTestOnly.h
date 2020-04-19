#pragma once

class CIceLemonDlg;
// CDlgTestOnly 对话框

class CDlgTestOnly : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTestOnly)

public:
	CDlgTestOnly(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTestOnly();
	int setContext(CIceLemonDlg *context);
	CIceLemonDlg *pIceLemonDlg;
// 对话框数据
	enum { IDD = IDD_DLG_TESTONLY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedInfo();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
