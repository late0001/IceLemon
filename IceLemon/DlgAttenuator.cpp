// DlgAttenuator.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IceLemon.h"
#include "DlgAttenuator.h"
#include "afxdialogex.h"


// CDlgAttenuator �Ի���

IMPLEMENT_DYNAMIC(CDlgAttenuator, CDialogEx)

CDlgAttenuator::CDlgAttenuator(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAttenuator::IDD, pParent)
{

}

CDlgAttenuator::~CDlgAttenuator()
{
}

void CDlgAttenuator::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgAttenuator, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgAttenuator::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDlgAttenuator ��Ϣ�������
void CDlgAttenuator::CreateEdits()
{

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString m_staticCaption;
	CRect rect,rect2;
	GetClientRect(&rect);
	GetDlgItem(IDOK)->GetWindowRect(&rect2);
	ScreenToClient(&rect2);

	int m_counts =60;
	int perWidth = rect.Width()/16;
	int perHeight =rect2.top/10 - 5;
	CStatic *p_MyStatic;
	CEdit *p_MyEdit;
	int j;
	int len = 10;
	for(int i=0;i<6;i++)
	{
		for(j=0; j < 10; j++){
			p_MyStatic = new CStatic();
			p_MyEdit = new CEdit();
			m_staticCaption.Format("%d:",j+(i*len)+1); 
	
			p_MyStatic->Create(m_staticCaption,WS_CHILD|WS_VISIBLE|SS_CENTER,
				CRect(perWidth*(2*i), j*perHeight+5, perWidth*(2*i+1)-3, (j+1)*perHeight),this);
			m_staticCaption.Format("%d",j+(i*len)+1); 
			p_MyEdit->Create(WS_CHILD|WS_VISIBLE|WS_BORDER|SS_CENTER,
				CRect(perWidth*(2*i+1), j*perHeight+5, perWidth*(2*i+2), (j+1)*perHeight),this,ID_EDIT_ATT_X+j+(i*len)+1);
			p_MyEdit->SetWindowText(m_staticCaption);
			if(p_MyStatic!=NULL)
			{
				pStatics.Add((void*)p_MyStatic);
				//delete p_MyStatic;
			}
			if(p_MyEdit!=NULL)
			{
				pEdits.Add((void*)p_MyEdit);
				//	delete p_MyEdit;
			}
		
		}
	}

}

void CDlgAttenuator::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	


	CDialogEx::OnClose();
}


BOOL CDlgAttenuator::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CreateEdits();

	return TRUE;  // return TRUE unless you set the focus to a control

	// �쳣: OCX ����ҳӦ���� FALSE
}

int CDlgAttenuator::setContext(CIceLemonDlg *context)
{
	this->pIceLemonDlg = context;
	return (this->pIceLemonDlg != NULL);
}

void CDlgAttenuator::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	int n=pStatics.GetSize();
	for(int i=0;i<n;i++)
	{
		CStatic* pStatic=(CStatic*)pStatics.GetAt(i);
		//	pStatic->DestroyWindow();
		if(pStatic!=NULL)
			delete pStatic;
		pStatics[i]=NULL;
	}
	pStatics.RemoveAll();
	n=pEdits.GetSize();
	for(int i=0;i<n;i++)
	{
		CEdit* pEdit=(CEdit*)pEdits.GetAt(i);
		//pEdit->DestroyWindow();
		if(pEdit!=NULL)
			delete pEdit;
		pEdits[i]=NULL;
	}
	pEdits.RemoveAll();
}


void CDlgAttenuator::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CString str;
	//GetDlgItem(ID_EDIT_ATT_X + 5)->GetWindowText(str);
	//MessageBox(str);
}
