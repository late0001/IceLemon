#pragma once
#include "afxwin.h"
#include "ADODbHelper.h"
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
	virtual BOOL OnInitDialog();
	CComboBox m_cbo_tester;
	CComboBox m_cbo_customer;
	CEdit m_edit_equiment;
	CEdit m_edit_environment;
	CEdit m_edit_method;
	CComboBox m_cbo_condition;
	CEdit m_edit_purpose;
	CEdit m_edit_workbench;
	CADODbHelper m_dbHelper;
	afx_msg void OnBnClickedOk();
	CComboBox m_cbo_reporttype;
};
