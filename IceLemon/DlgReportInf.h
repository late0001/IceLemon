#pragma once
#include "afxwin.h"
#include "ADODbHelper.h"
class CIceLemonDlg;
// CDlgReportInf �Ի���

class CDlgReportInf : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgReportInf)

public:
	CDlgReportInf(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgReportInf();

// �Ի�������
	enum { IDD = IDD_DLG_REPORTINF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
