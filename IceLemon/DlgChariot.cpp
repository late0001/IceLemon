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
	, m_edit_hour_s(0)
	, m_edit_min_s(0)
	, m_edit_sec_s(30)
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
	DDX_Text(pDX, IDC_EDT_HOUR2, m_edit_hour_s);
	DDV_MinMaxInt(pDX, m_edit_hour_s, 0, 60);
	DDX_Text(pDX, IDC_EDT_MIN2, m_edit_min_s);
	DDV_MinMaxInt(pDX, m_edit_min_s, 0, 60);
	DDX_Text(pDX, IDC_EDT_SEC2, m_edit_sec_s);
	DDV_MinMaxInt(pDX, m_edit_sec_s, 0, 60);
	DDX_Control(pDX, IDC_CBX_TESTCASE, m_cbx_use_case);
	DDX_Control(pDX, IDC_CBX_CARD1, m_cbx_card1);
	DDX_Control(pDX, IDC_CBX_CARD2, m_cbx_card2);
	DDX_Control(pDX, IDC_CBX_PROFILE1, m_cbx_profile1);
	DDX_Control(pDX, IDC_CBX_PROFILE2, m_cbx_profile2);
	DDX_Control(pDX, IDC_IPADDR_AP1, m_ip_ap1);
	DDX_Control(pDX, IDC_IPADDR_AP2, m_ip_ap2);
	DDX_Control(pDX, IDC_CBX_CARD3, m_cbx_card3);
	DDX_Control(pDX, IDC_CBX_PROFILE3, m_cbx_profile3);
	DDX_Control(pDX, IDC_IPADDR_AP3, m_ip_ap3);
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
ON_BN_CLICKED(IDC_BTN_UPD_CD, &CDlgChariot::OnClickedBtnUpdateChariotParamData)
ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN5, &CDlgChariot::OnDeltaposSpin5)
ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN6, &CDlgChariot::OnDeltaposSpin6)
ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN7, &CDlgChariot::OnDeltaposSpin7)
ON_CBN_KILLFOCUS(IDC_CBX_CARD1, &CDlgChariot::OnCbnKillfocusCbxCard1)
ON_BN_CLICKED(IDC_BUTTON2, &CDlgChariot::OnBnClickedButton2)
ON_CBN_KILLFOCUS(IDC_CBX_CARD2, &CDlgChariot::OnCbnKillfocusCbxCard2)
ON_WM_RBUTTONDOWN()
ON_COMMAND(ID_LOADCONF1, &CDlgChariot::OnLoadconf1)
ON_COMMAND(ID_LOADCONF2, &CDlgChariot::OnLoadconf2)
ON_COMMAND(ID_LOADCONF3, &CDlgChariot::OnLoadconf3)
ON_COMMAND(ID_SAVE_CONF, &CDlgChariot::OnSaveConf)
ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgChariot 消息处理程序
int CDlgChariot::setContext(CIceLemonDlg *context)
{
	this->pIceLemonDlg = context;
	return (this->pIceLemonDlg != NULL);
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

int CDlgChariot::InitConf(){
	// TODO: 在此添加命令处理程序代码
	CString str, protocol;
	char buf[50];
	int tmp;
	CString strPath=_T("./CurInfo.ini");
	if(!m_cbx_card2.IsWindowVisible()){
		GetDlgItem(IDC_LB_CARD2)->ShowWindow(SW_SHOW);
		m_cbx_card2.ShowWindow(SW_SHOW);
	}


	
	tmp =::GetPrivateProfileInt(_T("ChariotInfo"), _T("test_mode"), 0, strPath);
	m_cbx_use_case.SetCurSel(tmp);
	::GetPrivateProfileString(_T("ChariotInfo"), _T("ep1"), "127.0.0.1", str.GetBuffer(20),20,strPath);
	cbxEndpoint1.SetWindowText(str);
	::GetPrivateProfileString(_T("ChariotInfo"), _T("ep2"), "127.0.0.1", str.GetBuffer(20),20,strPath);
	cbxEndpoint2.SetWindowText(str);

	::GetPrivateProfileString(_T("ChariotInfo"), _T("protocol"), "TCP", str.GetBuffer(20),20, strPath);
	cbxProtocol.SetWindowText(str);
	::GetPrivateProfileString(_T("ChariotInfo"), _T("script"), "", str.GetBuffer(255),255, strPath);
	lblScript.SetWindowText(str);
	
	::GetPrivateProfileString(_T("ChariotInfo"), _T("E12"), "0 1", buf, 50, strPath);
	sscanf_s(buf, "%d %d", &tmp, &E12PairCount);
	if(tmp >0) ckbEndpoint12.SetCheck(1);
	::GetPrivateProfileString(_T("ChariotInfo"), _T("E21"), "0 1", buf, 50, strPath);
	sscanf_s(buf, "%d %d", &tmp, &E21PairCount);
	if(tmp >0) ckbEndpoint21.SetCheck(1);
	::GetPrivateProfileString(_T("ChariotInfo"), _T("E21"), "0 1", buf, 50, strPath);
	sscanf_s(buf, "%d %d", &tmp, &E1221PairCount);
	if(tmp >0) ckb2way.SetCheck(1);


	m_edit_hour = ::GetPrivateProfileInt(_T("Total Time"), _T("hour"), 0, strPath);

	m_edit_min = ::GetPrivateProfileInt(_T("Total Time"), _T("min"), 0, strPath);

	m_edit_sec = ::GetPrivateProfileInt(_T("Total Time"), _T("sec"), 0, strPath);

	m_edit_hour_s = ::GetPrivateProfileInt(_T("Single Time"), _T("hour"), 0, strPath);
	m_edit_min_s = ::GetPrivateProfileInt(_T("Single Time"), _T("min"), 0, strPath);
	m_edit_sec_s = ::GetPrivateProfileInt(_T("Single Time"), _T("sec"), 0, strPath);


	::GetPrivateProfileString(_T("ChariotInfo"), _T("card1"), "", str.GetBuffer(255),255, strPath);
	m_cbx_card1.SetWindowText(str);
	::GetPrivateProfileString(_T("ChariotInfo"), _T("card2"), "", str.GetBuffer(255),255, strPath);
	m_cbx_card2.GetWindowText(str);
	::GetPrivateProfileString(_T("ChariotInfo"), _T("profile1"), "", str.GetBuffer(255),255, strPath);
	m_cbx_profile1.SetWindowText(str);
	::GetPrivateProfileString(_T("ChariotInfo"), _T("profile2"), "", str.GetBuffer(255),255, strPath);
	m_cbx_profile2.SetWindowText(str);
	::GetPrivateProfileString(_T("ChariotInfo"), _T("AP1"), "", str.GetBuffer(255), 255, strPath);
	m_ip_ap1.SetWindowText(str);
	::GetPrivateProfileString(_T("ChariotInfo"), _T("AP2"), "", str.GetBuffer(255), 255, strPath);
	m_ip_ap2.SetWindowText(str);

	UpdateData(FALSE);
	return 0;
}
BOOL CDlgChariot::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//InitConf();
	CRect m_rect;
	GetClientRect(&m_rect);  //获取对话框的大小
	old.x=m_rect.right-m_rect.left;  
	old.y=m_rect.bottom-m_rect.top;
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


void CDlgChariot::OnClickedBtnUpdateChariotParamData()
{
	// TODO: 在此添加控件通知处理程序代码
	CString ep1,ep2,str;
	UpdateData(TRUE);
	cbxEndpoint1.GetWindowText(ep1);
	cbxEndpoint2.GetWindowText(ep2);
	struct Chariot *pChariotParameter = &pIceLemonDlg->ChariotParameter;
	pChariotParameter->e1 = ep1;
	pChariotParameter->e2 = ep2;
	//ckbEndpoint12.SetCheck(1);
	//E12PairCount = 5;
	//ckbEndpoint21.SetCheck(1);
	//E21PairCount = 5;

	CString fileName="" ;
	pIceLemonDlg->m_page_chariot.lblScript.GetWindowText(fileName);
	if(fileName == "")
		fileName = "D:\\xv\\Projects\\IceLemon\\IceLemon\\Scripts\\Throughput.scr";	//默认打开的文件名
	strcpy_s(pChariotParameter->script, fileName);
	int use_case = m_cbx_use_case.GetCurSel();
	if(use_case <0){
		AfxMessageBox("please recheck test mode that must be set");
	}
	pChariotParameter->use_case = use_case;
	if(use_case == 0){
		if(ep1.Mid(0,3) != ep2.Mid(0,3)){
			MessageBox("不在同一网段, 是否输入有误");
		}
	}
	if(use_case == 1){
		m_ip_ap2.GetWindowText(ep2);
		pChariotParameter->e2 = ep2;
	}
	pIceLemonDlg->CheckTestDirection();
	//str.Format("pair count: %d", pChariotParameter->Pair_Count);
	//AfxMessageBox(str);
	if(pChariotParameter->Pair_Count < 1)
		AfxMessageBox("please set direction at least one");
	UpdateData(FALSE);
}


void CDlgChariot::OnDeltaposSpin5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_edit_hour_s +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_edit_hour_s -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot::OnDeltaposSpin6(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_edit_min_s +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_edit_min_s -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot::OnDeltaposSpin7(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_edit_sec_s +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_edit_sec_s -=1;
	}
	UpdateData(false);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CDlgChariot::OnCbnKillfocusCbxCard1()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_cbx_card1.GetCurSel();
	pIceLemonDlg->GetProfileList(index);
}


void CDlgChariot::OnCbnKillfocusCbxCard2()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_cbx_card2.GetCurSel();
	pIceLemonDlg->Card2GetProfileList(index);
}

void CDlgChariot::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//CString ap;
	//pIceLemonDlg->GetLocalIPInfo(m_cbx_card1.GetCurSel(),ap);
	
	//AfxMessageBox(ap);

}





void CDlgChariot::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMenu menu;//菜单
	CMenu* pPopupMenu;//菜单指针
	CBitmap m_bitmap1;//位图

	menu.LoadMenu(IDR_MENU2);

	pPopupMenu = menu.GetSubMenu(0);   

	ClientToScreen(&point);

	pPopupMenu->TrackPopupMenu(TPM_TOPALIGN,point.x,point.y,this,NULL);
	CDialogEx::OnRButtonDown(nFlags, point);
}


void CDlgChariot::OnLoadconf1()
{
	// TODO: 在此添加命令处理程序代码
	ckbEndpoint12.SetCheck(1);
	E12PairCount = 5;
	cbxProtocol.SetCurSel(1);//TCP
	char tmpBuf[255] = { 0 };
	GetCurrentDirectory(255, tmpBuf);
	CString fileName;
	fileName.Format("%s\\Scripts\\Throughput.scr", tmpBuf);	//默认打开的文件名
	pIceLemonDlg->m_page_chariot.lblScript.SetWindowText(fileName);
	m_edit_min = 1;
	m_edit_sec = 0;
	m_cbx_use_case.SetCurSel(0);

	UpdateData(FALSE);
}


void CDlgChariot::OnLoadconf2()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
	if(m_cbx_card2.IsWindowVisible()){
		GetDlgItem(IDC_LB_CARD2)->ShowWindow(SW_HIDE);
		m_cbx_card2.ShowWindow(SW_HIDE);
	}
	if(m_cbx_card3.IsWindowVisible()){
		GetDlgItem(IDC_LB_CARD3)->ShowWindow(SW_HIDE);
		m_cbx_card3.ShowWindow(SW_HIDE);
	}
	ckbEndpoint12.SetCheck(1);
	E12PairCount = 5;
	ckbEndpoint21.SetCheck(1);
	E21PairCount = 5;
	ckb2way.SetCheck(1);
	E1221PairCount = 5;
	cbxProtocol.SetCurSel(1);//TCP
	char tmpBuf[255] = { 0 };
	GetCurrentDirectory(255, tmpBuf);
	CString fileName;
	fileName.Format("%s\\Scripts\\Throughput.scr", tmpBuf);	//默认打开的文件名
	pIceLemonDlg->m_page_chariot.lblScript.SetWindowText(fileName);
	m_edit_hour = 0;
	m_edit_min = 6;
	m_edit_sec = 0;
	m_edit_hour_s = 0;
	m_edit_min_s = 0;
	m_edit_sec_s = 20;
	m_cbx_card1.SetCurSel(0);
	m_cbx_use_case.SetCurSel(1);
	m_ip_ap2.SetWindowTextA("192.168.1.100");
	pIceLemonDlg->ChariotParameter.e2 = "192.168.1.100";

	UpdateData(FALSE);
}


void CDlgChariot::OnLoadconf3()
{
	// TODO: 在此添加命令处理程序代码
	if(!m_cbx_card2.IsWindowVisible()){
		GetDlgItem(IDC_LB_CARD2)->ShowWindow(SW_SHOW);
		m_cbx_card2.ShowWindow(SW_SHOW);
	}
	if(!m_cbx_card3.IsWindowVisible()){
		GetDlgItem(IDC_LB_CARD3)->ShowWindow(SW_SHOW);
		m_cbx_card3.ShowWindow(SW_SHOW);
	}
	ckbEndpoint12.SetCheck(1);
	E12PairCount = 5;
	ckbEndpoint21.SetCheck(1);
	E21PairCount = 5;
	ckb2way.SetCheck(1);
	E1221PairCount = 5;
	cbxProtocol.SetCurSel(1);//TCP
	char tmpBuf[255] = { 0 };
	GetCurrentDirectory(255, tmpBuf);
	CString fileName;
	fileName.Format("%s\\Scripts\\Throughput.scr", tmpBuf);	//默认打开的文件名
	pIceLemonDlg->m_page_chariot.lblScript.SetWindowText(fileName);
	m_edit_hour = 0;
	m_edit_min = 6;
	m_edit_sec = 0;
	m_edit_hour_s = 0;
	m_edit_min_s = 0;
	m_edit_sec_s = 20;
	m_cbx_card1.SetCurSel(0);
	m_cbx_use_case.SetCurSel(2);
	m_ip_ap2.SetWindowTextA("192.168.1.100");
	pIceLemonDlg->ChariotParameter.e2 = "192.168.1.100";
	UpdateData(FALSE);
}


void CDlgChariot::OnSaveConf()
{
	// TODO: 在此添加命令处理程序代码
	CString str, protocol;
	CString strPath=_T("./CurInfo.ini");
	UpdateData(TRUE);
	str.Format("%d",m_cbx_use_case.GetCurSel());
	::WritePrivateProfileString(_T("ChariotInfo"), _T("test_mode"), str, strPath);
	cbxEndpoint1.GetWindowText(str);
	::WritePrivateProfileString(_T("ChariotInfo"), _T("ep1"), str, strPath);
	cbxEndpoint2.GetWindowText(str);
	::WritePrivateProfileString(_T("ChariotInfo"), _T("ep2"), str, strPath);
	cbxProtocol.GetWindowText(protocol);
	::WritePrivateProfileString(_T("ChariotInfo"), _T("protocol"), protocol, strPath);
	lblScript.GetWindowText(str);
	::WritePrivateProfileString(_T("ChariotInfo"), _T("script"), str, strPath);
	
	str.Format("%d %d", ckbEndpoint12.GetCheck(),E12PairCount);
	::WritePrivateProfileString(_T("ChariotInfo"), _T("E12"), str, strPath);
	str.Format("%d %d", ckbEndpoint21.GetCheck(), E21PairCount);
	::WritePrivateProfileString(_T("ChariotInfo"), _T("E21"), str, strPath);
	str.Format("%d %d", ckb2way.GetCheck(), E1221PairCount);
	::WritePrivateProfileString(_T("ChariotInfo"), _T("E1221"), str, strPath);
	
	str.Format("%d", m_edit_hour);
	::WritePrivateProfileString(_T("Total Time"), _T("hour"), str, strPath);
	str.Format("%d", m_edit_min);
	::WritePrivateProfileString(_T("Total Time"), _T("min"), str, strPath);
	str.Format("%d", m_edit_sec);
	::WritePrivateProfileString(_T("Total Time"), _T("sec"), str, strPath);
	str.Format("%d", m_edit_hour_s);
	::WritePrivateProfileString(_T("Single Time"), _T("hour"), str, strPath);
	str.Format("%d", m_edit_min_s);
	::WritePrivateProfileString(_T("Single Time"), _T("min"), str, strPath);
	str.Format("%d", m_edit_sec_s);
	::WritePrivateProfileString(_T("Single Time"), _T("sec"), str, strPath);
	m_cbx_card1.GetWindowText(str);
	::WritePrivateProfileString(_T("ChariotInfo"), _T("card1"), str, strPath);
	m_cbx_card2.GetWindowText(str);
	::WritePrivateProfileString(_T("ChariotInfo"), _T("card2"), str, strPath);
	m_cbx_profile1.GetWindowText(str);
	::WritePrivateProfileString(_T("ChariotInfo"), _T("profile1"), str, strPath);
	m_cbx_profile2.GetWindowText(str);
	::WritePrivateProfileString(_T("ChariotInfo"), _T("profile2"), str, strPath);
	m_ip_ap1.GetWindowText(str);
	::WritePrivateProfileString(_T("ChariotInfo"), _T("AP1"), str, strPath);
	m_ip_ap2.GetWindowText(str);
	::WritePrivateProfileString(_T("ChariotInfo"), _T("AP2"), str, strPath);	
	MessageBox("完成!");
}


void CDlgChariot::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if(nType!=SIZE_MINIMIZED )  
	{
		ReSize();
	}
}


void CDlgChariot::ReSize(void)
{

    float fsp[2];  
    POINT Newp; //获取现在对话框的大小  
    CRect recta;      
    GetClientRect(&recta);     //取客户区大小    
    Newp.x=recta.right-recta.left;  
    Newp.y=recta.bottom-recta.top;  
    fsp[0]=(float)Newp.x/old.x;  
    fsp[1]=(float)Newp.y/old.y;  
    CRect Rect;  
    int woc;  
    CPoint OldTLPoint,TLPoint; //左上角  
    CPoint OldBRPoint,BRPoint; //右下角  
    HWND  hwndChild=::GetWindow(m_hWnd,GW_CHILD);  //列出所有控件    
    while(hwndChild){      
        woc=::GetDlgCtrlID(hwndChild);//取得ID  
        GetDlgItem(woc)->GetWindowRect(Rect);    
        ScreenToClient(Rect);    
        OldTLPoint = Rect.TopLeft();    
        TLPoint.x = long(OldTLPoint.x*fsp[0]);    
        TLPoint.y = long(OldTLPoint.y*fsp[1]);    
        OldBRPoint = Rect.BottomRight();    
        BRPoint.x = long(OldBRPoint.x *fsp[0]);    
        BRPoint.y = long(OldBRPoint.y *fsp[1]);    
        Rect.SetRect(TLPoint,BRPoint);    
        GetDlgItem(woc)->MoveWindow(Rect,TRUE);  
        hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);      
    }
    old=Newp;  

}
