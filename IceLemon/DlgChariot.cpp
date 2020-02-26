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
END_MESSAGE_MAP()


// CDlgChariot 消息处理程序
