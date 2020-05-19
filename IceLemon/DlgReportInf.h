#pragma once

class CIceLemonDlg;
// CDlgReportInf 对话框

class CDlgReportInf : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgReportInf)

public:
	CDlgReportInf(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgReportInf();

// 对话框数据
	enum { IDD = IDD_DLG_REPORTINF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CIceLemonDlg *pIceLemonDlg;
	int SetContext(CIceLemonDlg *context);
};
