// DlgChariot.cpp : 实现文件
//

#include "stdafx.h"
#include "IceLemon.h"
#include "DlgChariot.h"
#include "afxdialogex.h"


// CDlgChariot 对话框

IMPLEMENT_DYNAMIC(CDlgChariot, CDialogEx)

CDlgChariot::CDlgChariot(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgChariot::IDD, pParent)
{

}

CDlgChariot::~CDlgChariot()
{
}

void CDlgChariot::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgChariot, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK3, &CDlgChariot::OnBnClickedCheck3)
END_MESSAGE_MAP()


// CDlgChariot 消息处理程序


void CDlgChariot::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
}
