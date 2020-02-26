// DlgMain.cpp : 实现文件
//

#include "stdafx.h"
#include "IceLemon.h"
#include "DlgMain.h"
#include "afxdialogex.h"


// CDlgMain 对话框

IMPLEMENT_DYNAMIC(CDlgMain, CDialogEx)

CDlgMain::CDlgMain(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMain::IDD, pParent)
{

}

CDlgMain::~CDlgMain()
{
}

void CDlgMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMain, CDialogEx)
END_MESSAGE_MAP()


// CDlgMain 消息处理程序
