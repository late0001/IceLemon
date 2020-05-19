// DlgRotator.cpp : 实现文件
//

#include "stdafx.h"
#include "IceLemon.h"
#include "DlgRotator.h"
#include "afxdialogex.h"


// CDlgRotator 对话框

IMPLEMENT_DYNAMIC(CDlgRotator, CDialogEx)

CDlgRotator::CDlgRotator(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRotator::IDD, pParent)
{

}

CDlgRotator::~CDlgRotator()
{
}

void CDlgRotator::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CLB_ROTATOR, m_clbRotator);
}


BEGIN_MESSAGE_MAP(CDlgRotator, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ROTATOR_SELECTALL, &CDlgRotator::OnBnClickedBtnRotatorSelectall)
END_MESSAGE_MAP()


// CDlgRotator 消息处理程序
int CDlgRotator::SetContext(CIceLemonDlg *context)
{
	this->pIceLemonDlg = context;
	return (this->pIceLemonDlg != NULL);
}

BOOL CDlgRotator::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_clbRotator.AddString(_T("15"));
	m_clbRotator.AddString(_T("30"));
	m_clbRotator.AddString(_T("45"));
	m_clbRotator.AddString(_T("60"));
	m_clbRotator.AddString(_T("75"));
	m_clbRotator.AddString(_T("90"));
	m_clbRotator.AddString(_T("105"));
	m_clbRotator.AddString(_T("120"));
	m_clbRotator.AddString(_T("135"));
	m_clbRotator.AddString(_T("150"));
	m_clbRotator.AddString(_T("165"));
	m_clbRotator.AddString(_T("180"));
	m_clbRotator.AddString(_T("195"));
	m_clbRotator.AddString(_T("210"));
	m_clbRotator.AddString(_T("225"));
	m_clbRotator.AddString(_T("240"));
	m_clbRotator.AddString(_T("255"));
	m_clbRotator.AddString(_T("270"));
	m_clbRotator.AddString(_T("285"));
	m_clbRotator.AddString(_T("300"));
	m_clbRotator.AddString(_T("315"));
	m_clbRotator.AddString(_T("330"));
	m_clbRotator.AddString(_T("345"));
	m_clbRotator.AddString(_T("360"));	
		

	return TRUE;  // return TRUE unless you set the focus to a control

}


void CDlgRotator::OnBnClickedBtnRotatorSelectall()
{
	// TODO: 在此添加控件通知处理程序代码
	for(int i=0; i < m_clbRotator.GetCount(); i++)
	{
		m_clbRotator.SetCheck(i, TRUE);
	}
}
