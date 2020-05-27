// StatusDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "IceLemon.h"
#include "ChariotParaDlg.h"
#include "afxdialogex.h"

// CStatusDlg 对话框

IMPLEMENT_DYNAMIC(CChariotParaDlg, CDialogEx)

CChariotParaDlg::CChariotParaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChariotParaDlg::IDD, pParent)
	, m_hour(0)
	, m_min(0)
	, m_sec(0)
	, m_radio_tr(0)
{

}

CChariotParaDlg::CChariotParaDlg(CDlgChariot2 *pDlgChariot2,CWnd* pParent /*=NULL*/)
	: CDialogEx(CChariotParaDlg::IDD, pParent)
	, m_hour(0)
	, m_min(0)
	, m_sec(0)
	, bPreUpdate(FALSE)
{
	this->pDlgChariot2 = pDlgChariot2;
}

CChariotParaDlg::~CChariotParaDlg()
{
}

void CChariotParaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDR1_E1, m_ip_e1);
	DDX_Control(pDX, IDC_IPADDR1_E2, m_ip_e2);
	DDX_Control(pDX, IDC_CBO_PROF1_E1, m_cbo_e1_profile);
	DDX_Control(pDX, IDC_CBO_PROF1_E2, m_cbo_e2_profile);
	DDX_Text(pDX, IDC_EDT_HOURC1, m_hour);
	DDX_Text(pDX, IDC_EDT_MINC1, m_min);
	DDV_MinMaxInt(pDX, m_min, 0, 60);
	DDX_Text(pDX, IDC_EDT_SECC1, m_sec);
	DDV_MinMaxInt(pDX, m_sec, 0, 60);
}


BEGIN_MESSAGE_MAP(CChariotParaDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_OK, &CChariotParaDlg::OnBnClickedBtnOk)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SC1, &CChariotParaDlg::OnDeltaposSpinSc1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MC1, &CChariotParaDlg::OnDeltaposSpinMc1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_HC1, &CChariotParaDlg::OnDeltaposSpinHc1)
	ON_BN_CLICKED(IDOK, &CChariotParaDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RDO_TX, &CChariotParaDlg::OnBnClickedRdoTx)
	ON_BN_CLICKED(IDC_RDO_RX, &CChariotParaDlg::OnBnClickedRdoRx)
END_MESSAGE_MAP()


// CStatusDlg 消息处理程序




int CChariotParaDlg::CheckItem(Chariot2_Item *xItem)
{

	CString ip_e1_str, ip_e2_str;
	char msg[255]={0};
	//xItem.id = i;
	//if( m_ckb1.GetCheck()){
	xItem->proflag = 0;
	m_ip_e1.GetWindowText(ip_e1_str);
	if(ip_e1_str =="0.0.0.0"){
		CString str_p1;
		m_cbo_e1_profile.GetWindowText(str_p1);
		if(str_p1 == ""){
			sprintf_s(msg,"The endpoint1 of item is set incorrectly. It must be set!!\nPlease recheck!!");
			MessageBox(msg, "Error", MB_OK | MB_ICONERROR);		
			m_cbo_e1_profile.SetFocus();
			return 0;
		}
		strcpy_s(xItem->profile_e1,str_p1.GetBuffer(str_p1.GetLength()));
		xItem->proflag = 1;
		xItem->e1 = "";
	}else{
		xItem->e1 = ip_e1_str;
		xItem->profile_e1[0]='\0';
	}
	m_ip_e2.GetWindowText(ip_e2_str);
	if(ip_e2_str == "0.0.0.0"){
		if(xItem->proflag == 1){//if endpoint1 select profile
			sprintf_s(msg,"The endpoint2 of item is set incorrectly. The IP address must be set !!\nPlease recheck!!");
			MessageBox(msg, "Error", MB_OK | MB_ICONERROR);
			m_ip_e2.SetFocus();
			return 0;
		} else {//if(xItem.proflag == 0){
			CString str_p2;
			m_cbo_e2_profile.GetWindowText(str_p2);
			if(str_p2 == ""){
				sprintf_s(msg,"The endpoint of item is set incorrectly. It must be set!!\nPlease recheck!!");
				MessageBox(msg, "Error", MB_OK | MB_ICONERROR);		
				m_cbo_e2_profile.SetFocus();
				return 0;
			}
			strcpy_s(xItem->profile_e2, str_p2.GetBuffer(str_p2.GetLength()));
			xItem->proflag = 2;
			xItem->e2 = "";
		}
	}else{
		xItem->e2 = ip_e2_str;
		xItem->profile_e2[0]='\0';
	}
	UpdateData(TRUE);
	xItem->test_duration = (m_hour *3600 + m_min *60 + m_sec);
	sprintf_s(xItem->pszTestDuration, "%02d:%02d:%02d", m_hour, m_min, m_sec); 
	if (xItem->test_duration == 0)
	{
		sprintf_s(msg,"Test duration must not be zero!!\nPlease recheck!!");
		MessageBox(msg, "Error", MB_OK | MB_ICONERROR);
		GetDlgItem(IDC_EDT_SECC1)->SetFocus();
		return 0;
	}

	xItem->pairNum = 5;
	xItem->TorR = m_radio_tr;
	//}
	return 1;
}

int CChariotParaDlg::ShowItem(Chariot2_Item &xItem)
{
	//xItem.id = i;
	//if( m_ckb1.GetCheck()){
	xItem.proflag = 0;
	m_ip_e1.SetWindowText(xItem.e1);
	m_cbo_e1_profile.SetWindowText(xItem.profile_e1);

	m_ip_e2.SetWindowText(xItem.e2);
	m_cbo_e2_profile.SetWindowText(xItem.profile_e2);
	
	caculTimeToUI(xItem.test_duration);
	//sprintf_s(xItem.pszTestDuration, "%02d:%02d:%02d", m_hour, m_min, m_sec); 
	
	//}
	return 1;
}

int CChariotParaDlg::caculTimeToUI(unsigned long testDuration)
{
	int tmp;
	m_hour = testDuration /3600;
	tmp = testDuration % 3600;
	m_min = tmp /60;
	m_sec = tmp % 60;
	UpdateData(FALSE);
	return 0;
}

void CChariotParaDlg::OnBnClickedBtnOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	int ret;
	if(!bPreUpdate){
		ret = CheckItem( &item);
	}else{
		ret = CheckItem(pItem);
	}
	
	if(ret <= 0) return;
	CDialogEx::OnOK();
}


void CChariotParaDlg::OnDeltaposSpinSc1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_sec +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_sec -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CChariotParaDlg::OnDeltaposSpinMc1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_min +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_min -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CChariotParaDlg::OnDeltaposSpinHc1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_hour +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_hour -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CChariotParaDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

DWORD CChariotParaDlg::InitProfileComboBox()
{
	DWORD dwResult=0;
	int i;
	char profileName[WLAN_MAX_NAME_LENGTH] ;
	//PWLAN_PROFILE_INFO_LIST pProfileList;
	PIL_PROFILE_INFO pProfileInfo;
	CComboBox *pCbE1 = &m_cbo_e1_profile; 
	CComboBox *pCbE2 = &m_cbo_e2_profile;
	pCbE1->ResetContent();
	pCbE2->ResetContent();
	for(i = 0; i < pPrfList->dwNumberOfItems; i++){
		pProfileInfo = &pPrfList->ProfileInfo[i];
		pCbE1->InsertString(i, pProfileInfo->strProfileName);
		pCbE2->InsertString(i, pProfileInfo->strProfileName);
	}
	return dwResult;
}
BOOL CChariotParaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitProfileComboBox();
	if(bPreUpdate){
		ShowItem(*pItem);
	}
	return TRUE;  // return TRUE unless you set the focus to a control

	// 异常: OCX 属性页应返回 FALSE
}





void CChariotParaDlg::OnBnClickedRdoTx()
{
	// TODO: 在此添加控件通知处理程序代码
	m_radio_tr = 1;
}


void CChariotParaDlg::OnBnClickedRdoRx()
{
	// TODO: 在此添加控件通知处理程序代码
	m_radio_tr = 0;
}
