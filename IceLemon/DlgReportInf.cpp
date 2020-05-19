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
}


BEGIN_MESSAGE_MAP(CDlgReportInf, CDialogEx)
END_MESSAGE_MAP()


// CDlgReportInf 消息处理程序
int CDlgReportInf::SetContext(CIceLemonDlg *context)
{
	this->pIceLemonDlg = context;
	return (this->pIceLemonDlg != NULL);
}