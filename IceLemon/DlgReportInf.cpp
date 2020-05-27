// DlgReportInf.cpp : 实现文件
//

#include "stdafx.h"
#include "IceLemon.h"
#include "DlgReportInf.h"
#include "afxdialogex.h"


// CDlgReportInf 对话框

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
	DDX_Control(pDX, IDC_EDT_EQUI, m_edit_equiment);
	DDX_Control(pDX, IDC_EDT_ENVI, m_edit_environment);
	DDX_Control(pDX, IDC_EDT_METH, m_edit_method);
	DDX_Control(pDX, IDC_CBO_CONDITION, m_cbo_condition);
	DDX_Control(pDX, IDC_EDT_PURPOSE, m_edit_purpose);
	DDX_Control(pDX, IDC_EDT_BENCH, m_edit_workbench);
	DDX_Control(pDX, IDC_CBO_REPORTTYPE, m_cbo_reporttype);
}


BEGIN_MESSAGE_MAP(CDlgReportInf, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgReportInf::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgReportInf 消息处理程序
int CDlgReportInf::SetContext(CIceLemonDlg *context)
{
	this->pIceLemonDlg = context;
	return (this->pIceLemonDlg != NULL);
}

BOOL CDlgReportInf::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	char tester[][20]={"Sam", "JieGuo"};
	char customers[][20]={"友华","友尚", "瑞昱"};
	m_cbo_tester.AddString(tester[0]);
	m_cbo_tester.AddString(tester[1]);
	for(int i=0; i < sizeof(customers)/sizeof(customers[0]); i++)
		m_cbo_customer.AddString(customers[i]);
	m_cbo_reporttype.AddString("1");
	m_cbo_reporttype.AddString("2");
	m_cbo_reporttype.AddString("3");
	return TRUE;  // return TRUE unless you set the focus to a control

}


void CDlgReportInf::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	CString sql = "";
	CString customer;
	CString tester;
	CString condition;
	CString environment;
	CString equiment;
	CString method;
	CString purpose;
	CString workbench;
	CString reportType;
	m_cbo_tester.GetWindowText(tester);
	m_cbo_customer.GetWindowText(customer);
	m_cbo_condition.GetWindowText(condition);
	m_edit_environment.GetWindowText(environment);
	m_edit_equiment.GetWindowText(equiment);
	m_edit_method.GetWindowText(method);
	m_edit_purpose.GetWindowText(purpose);
	m_edit_workbench.GetWindowText(workbench);
	m_cbo_reporttype.GetWindowText(reportType);
	sql.Format("insert into Report (ReportId, TesterName, CustomerName, TestPurpose, Workbench, ReportType, TestCondition,\
		TestEquipment, TestEnvironment, TestMethod) values (%d, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s' )",
		12, tester, customer, purpose, workbench, reportType, condition, equiment, environment, method);
	
	try{
		m_dbHelper.OnInitADOConn();
		m_dbHelper.ExecuteSQL((_bstr_t)sql);
		m_dbHelper.ExitConn();
	}
	catch(...)
	{
		AfxMessageBox("操作失败");
		return;
	}
	//CDialogEx::OnOK();
}
