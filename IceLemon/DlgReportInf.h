#pragma once
#include "afxwin.h"

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
};
