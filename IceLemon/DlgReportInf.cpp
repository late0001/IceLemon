// DlgReportInf.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IceLemon.h"
#include "DlgReportInf.h"
#include "afxdialogex.h"


// CDlgReportInf �Ի���

IMPLEMENT_DYNAMIC(CDlgReportInf, CDialogEx)

CDlgReportInf::CDlgReportInf(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgReportInf::IDD, pParent)
{

}

CDlgReportInf::~CDlgReportInf()
{
}

void CDlgReportInf::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_TESTER, m_cbo_tester);
	DDX_Control(pDX, IDC_CBO_CUSTOMER, m_cbo_customer);
}


BEGIN_MESSAGE_MAP(CDlgReportInf, CDialogEx)
END_MESSAGE_MAP()


// CDlgReportInf ��Ϣ�������
int CDlgReportInf::SetContext(CIceLemonDlg *context)
{
	this->pIceLemonDlg = context;
	return (this->pIceLemonDlg != NULL);
}

BOOL CDlgReportInf::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	char tester[][20]={"Sam", "GuoJie"};
	char customers[][20]={"�ѻ�","����", "����"};
	m_cbo_tester.AddString(tester[0]);
	m_cbo_tester.AddString(tester[1]);
	for(int i=0; i < sizeof(customers)/sizeof(customers[0]); i++)
		m_cbo_customer.AddString(customers[i]);

	return TRUE;  // return TRUE unless you set the focus to a control

}
