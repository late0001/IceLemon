// DlgChariot.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IceLemon.h"
#include "DlgChariot.h"
#include "afxdialogex.h"


// CDlgChariot �Ի���

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


// CDlgChariot ��Ϣ�������


void CDlgChariot::OnBnClickedCheck3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
