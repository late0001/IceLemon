// DlgMain.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IceLemon.h"
#include "DlgMain.h"
#include "afxdialogex.h"


// CDlgMain �Ի���

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
	ON_BN_CLICKED(IDC_BTN_RUN, &CDlgMain::OnBnClickedBtnRun)
END_MESSAGE_MAP()


// CDlgMain ��Ϣ�������


void CDlgMain::OnBnClickedBtnRun()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}
