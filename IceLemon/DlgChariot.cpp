// DlgChariot.cpp : 实现文件
//

#include "stdafx.h"
#include "IceLemon.h"
#include "DlgChariot.h"
#include "afxdialogex.h"
#include "IceLemonDlg.h"

// CDlgChariot 对话框

IMPLEMENT_DYNAMIC(CDlgChariot, CDialogEx)

CDlgChariot::CDlgChariot(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgChariot::IDD, pParent)
	, m_edit_hour(0)
	, m_edit_min(0)
	, m_edit_sec(0)
	, m_edit_preRun(5)
	, E12PairCount(1)
	, E21PairCount(1)
	, E1221PairCount(1)
{

}

CDlgChariot::~CDlgChariot()
{
}

void CDlgChariot::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPIN1, m_spin_hour);
	DDX_Text(pDX, IDC_EDT_HOUR, m_edit_hour);
	DDV_MinMaxInt(pDX, m_edit_hour, 0, 60);
	DDX_Text(pDX, IDC_EDT_MIN, m_edit_min);
	DDV_MinMaxInt(pDX, m_edit_min, 0, 60);
	DDX_Text(pDX, IDC_EDT_SEC, m_edit_sec);
	DDV_MinMaxInt(pDX, m_edit_sec, 0, 60);
	DDX_Text(pDX, IDC_EDT_PRERUNDUR, m_edit_preRun);
	DDX_Control(pDX, IDC_CKB_LOADTSTFILE, ckbLoadTestFile);
	DDX_Control(pDX, IDC_CKB_E1E2, ckbEndpoint12);
	DDX_Control(pDX, IDC_CKB_E2E1, ckbEndpoint21);
	DDX_Control(pDX, IDC_CKB_2WAY, ckb2way);
	DDX_Control(pDX, IDC_CBO_ENTPOINT1, cbxEndpoint1);
	DDX_Control(pDX, IDC_CBO_ENTPOINT2, cbxEndpoint2);
	//  DDX_Control(pDX, IDC_EDT_SEC, m_editctl_sec);
	DDX_Control(pDX, IDC_CKB_SAVETST, ckbSaveChariotTest);
	DDX_Text(pDX, IDC_EDT_E12, E12PairCount);
	DDX_Text(pDX, IDC_EDT_E21, E21PairCount);
	DDX_Text(pDX, IDC_EDT_E1221, E1221PairCount);
	DDX_Control(pDX, IDC_LBL_SAVENAME, lbl_saveName);
	DDX_Control(pDX, IDC_CKB_PRERUN, ckbEnablePreRun);
	DDX_Control(pDX, IDC_LBL_SCRIPT, lblScript);
	DDX_Control(pDX, IDC_CBX_PROTOCOL, cbxProtocol);
}


BEGIN_MESSAGE_MAP(CDlgChariot, CDialogEx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CDlgChariot::OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &CDlgChariot::OnDeltaposSpin2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &CDlgChariot::OnDeltaposSpin3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN4, &CDlgChariot::OnDeltaposSpin4)
	ON_EN_CHANGE(IDC_EDT_PRERUNDUR, &CDlgChariot::OnEnChangeEdtPrerundur)
	ON_BN_CLICKED(IDC_BTN_SCRIPT, &CDlgChariot::OnClickedBtnScript)
	ON_CBN_KILLFOCUS(IDC_CBX_PROTOCOL, &CDlgChariot::OnKillfocusCbxProtocol)
//	ON_BN_CLICKED(IDC_CKB_SAVETST, &CDlgChariot::OnBnClickedCkbSavetst)
ON_BN_CLICKED(IDC_CKB_SAVETST, &CDlgChariot::OnClickedCkbSaveTst)
END_MESSAGE_MAP()


// CDlgChariot 消息处理程序
int CDlgChariot::setContext(CIceLemonDlg *context)
{
	this->pIceLemonDlg = context;
	return (this->pIceLemonDlg != NULL);
}

void CDlgChariot::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgChariot::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_edit_hour +=1;
		
	}else if(pNMUpDown->iDelta == 1){
		m_edit_hour -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot::OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_edit_min +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_edit_min -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot::OnDeltaposSpin3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_edit_sec +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_edit_sec -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot::OnDeltaposSpin4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_edit_preRun +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_edit_preRun -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot::OnEnChangeEdtPrerundur()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(TRUE);
	pIceLemonDlg->PreRunDuration = m_edit_preRun;
	// TODO:  在此添加控件通知处理程序代码
}


void CDlgChariot::OnClickedBtnScript()
{
	// TODO: 在此添加控件通知处理程序代码
	pIceLemonDlg->OnClickedBtnScript();

}


BOOL CDlgChariot::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;
}


void CDlgChariot::OnKillfocusCbxProtocol()
{
	// TODO: 在此添加控件通知处理程序代码
	pIceLemonDlg->OnKillfocusCbxProtocol();
}


//void CDlgChariot::OnBnClickedCkbSavetst()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}


void CDlgChariot::OnClickedCkbSaveTst()
{
	// TODO: 在此添加控件通知处理程序代码
	pIceLemonDlg->OnClickedCkbSaveTst();
}
