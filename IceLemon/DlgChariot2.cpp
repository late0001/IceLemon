// DlgChariot2.cpp : 实现文件
//

#include "stdafx.h"
#include "IceLemon.h"
#include "DlgChariot2.h"
#include "afxdialogex.h"
#include "IceLemonDlg.h"

// CDlgChariot2 对话框

IMPLEMENT_DYNAMIC(CDlgChariot2, CDialogEx)

CDlgChariot2::CDlgChariot2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgChariot2::IDD, pParent)
	, m_hour_total(0)
	, m_hour_c1(0)
	, m_hour_c10(0)
	, m_hour_c2(0)
	, m_hour_c3(0)
	, m_hour_c4(0)
	, m_hour_c5(0)
	, m_hour_c6(0)
	, m_hour_c7(0)
	, m_hour_c8(0)
	, m_hour_c9(0)
	, m_min_total(0)
	, m_min_c1(0)
	, m_min_c10(0)
	, m_min_c2(0)
	, m_min_c3(0)
	, m_min_c4(0)
	, m_min_c5(0)
	, m_min_c6(0)
	, m_min_c7(0)
	, m_min_c8(0)
	, m_min_c9(0)
	, m_sec_total(0)
	, m_sec_c1(0)
	, m_sec_c10(0)
	, m_sec_c2(0)
	, m_sec_c3(0)
	, m_sec_c4(0)
	, m_sec_c5(0)
	, m_sec_c6(0)
	, m_sec_c7(0)
	, m_sec_c8(0)
	, m_sec_c9(0)
{

}

CDlgChariot2::~CDlgChariot2()
{
}

void CDlgChariot2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBO_PROF1_E1, m_cbo_p1e1);
	DDX_Control(pDX, IDC_CBO_PROF1_E2, m_cbo_p1e2);
	DDX_Control(pDX, IDC_CBO_PROF2_E1, m_cbo_p2e1);
	DDX_Control(pDX, IDC_CBO_PROF2_E2, m_cbo_p2e2);
	DDX_Control(pDX, IDC_CBO_PROF3_E1, m_cbo_p3e1);
	DDX_Control(pDX, IDC_CBO_PROF3_E2, m_cbo_p3e2);
	DDX_Control(pDX, IDC_CBO_PROF4_E1, m_cbo_p4e1);
	DDX_Control(pDX, IDC_CBO_PROF4_E2, m_cbo_p4e2);
	DDX_Control(pDX, IDC_CBO_PROF5_E1, m_cbo_p5e1);
	DDX_Control(pDX, IDC_CBO_PROF5_E2, m_cbo_p5e2);
	DDX_Control(pDX, IDC_CBO_PROF6_E1, m_cbo_p6e1);
	DDX_Control(pDX, IDC_CBO_PROF6_E2, m_cbo_p6e2);
	DDX_Control(pDX, IDC_CBO_PROF7_E1, m_cbo_p7e1);
	DDX_Control(pDX, IDC_CBO_PROF7_E2, m_cbo_p7e2);
	DDX_Control(pDX, IDC_CBO_PROF8_E1, m_cbo_p8e1);
	DDX_Control(pDX, IDC_CBO_PROF8_E2, m_cbo_p8e2);
	DDX_Control(pDX, IDC_CBO_PROF9_E1, m_cbo_p9e1);
	DDX_Control(pDX, IDC_CBO_PROF9_E2, m_cbo_p9e2);
	DDX_Control(pDX, IDC_CBO_PROF10_E1, m_cbo_p10e1);
	DDX_Control(pDX, IDC_CBO_PROF10_E2, m_cbo_p10e2);
	DDX_Control(pDX, IDC_IPADDR1_E1, m_IPAddr1_e1);
	DDX_Control(pDX, IDC_IPADDR1_E2, m_IPAddr1_e2);
	DDX_Control(pDX, IDC_IPADDR10_E1, m_IPAddr10_e1);
	DDX_Control(pDX, IDC_IPADDR10_E2, m_IPAddr10_e2);
	DDX_Control(pDX, IDC_IPADDR2_E1, m_IPAddr2_e1);
	DDX_Control(pDX, IDC_IPADDR2_E2, m_IPAddr2_e2);
	DDX_Control(pDX, IDC_IPADDR3_E1, m_IPAddr3_e1);
	DDX_Control(pDX, IDC_IPADDR3_E2, m_IPAddr3_e2);
	DDX_Control(pDX, IDC_IPADDR4_E1, m_IPAddr4_e1);
	DDX_Control(pDX, IDC_IPADDR4_E2, m_IPAddr4_e2);
	DDX_Control(pDX, IDC_IPADDR5_E1, m_IPAddr5_e1);
	DDX_Control(pDX, IDC_IPADDR5_E2, m_IPAddr5_e2);
	DDX_Control(pDX, IDC_IPADDR6_E1, m_IPAddr6_e1);
	DDX_Control(pDX, IDC_IPADDR6_E2, m_IPAddr6_e2);
	DDX_Control(pDX, IDC_IPADDR7_E1, m_IPAddr7_e1);
	DDX_Control(pDX, IDC_IPADDR7_E2, m_IPAddr7_e2);
	DDX_Control(pDX, IDC_IPADDR8_E1, m_IPAddr8_e1);
	DDX_Control(pDX, IDC_IPADDR9_E1, m_IPAddr9_e1);
	DDX_Control(pDX, IDC_IPADDR8_E2, m_IPAddr8_e2);
	DDX_Control(pDX, IDC_IPADDR9_E2, m_IPAddr9_e2);
	//  DDX_Text(pDX, IDC_EDT_HOURC1, m_hour_c1);
	DDX_Text(pDX, IDC_EDT_HOURC11, m_hour_total);
	DDV_MinMaxInt(pDX, m_hour_total, 0, 60);
	DDX_Text(pDX, IDC_EDT_HOURC1, m_hour_c1);
	DDV_MinMaxInt(pDX, m_hour_c1, 0, 60);
	DDX_Text(pDX, IDC_EDT_HOURC10, m_hour_c10);
	DDV_MinMaxInt(pDX, m_hour_c10, 0, 60);
	DDX_Text(pDX, IDC_EDT_HOURC2, m_hour_c2);
	DDV_MinMaxInt(pDX, m_hour_c2, 0, 60);
	DDX_Text(pDX, IDC_EDT_HOURC3, m_hour_c3);
	DDV_MinMaxInt(pDX, m_hour_c3, 0, 60);
	DDX_Text(pDX, IDC_EDT_HOURC4, m_hour_c4);
	DDV_MinMaxInt(pDX, m_hour_c4, 0, 60);
	DDX_Text(pDX, IDC_EDT_HOURC5, m_hour_c5);
	DDV_MinMaxInt(pDX, m_hour_c5, 0, 60);
	DDX_Text(pDX, IDC_EDT_HOURC6, m_hour_c6);
	DDV_MinMaxInt(pDX, m_hour_c6, 0, 60);
	DDX_Text(pDX, IDC_EDT_HOURC7, m_hour_c7);
	DDV_MinMaxInt(pDX, m_hour_c7, 0, 60);
	DDX_Text(pDX, IDC_EDT_HOURC8, m_hour_c8);
	DDV_MinMaxInt(pDX, m_hour_c8, 0, 60);
	DDX_Text(pDX, IDC_EDT_HOURC9, m_hour_c9);
	DDV_MinMaxInt(pDX, m_hour_c9, 0, 60);
	DDX_Text(pDX, IDC_EDT_MINC11, m_min_total);
	DDV_MinMaxInt(pDX, m_min_total, 0, 60);
	DDX_Text(pDX, IDC_EDT_MINC1, m_min_c1);
	DDV_MinMaxInt(pDX, m_min_c1, 0, 60);
	DDX_Text(pDX, IDC_EDT_MINC10, m_min_c10);
	DDV_MinMaxInt(pDX, m_min_c10, 0, 60);
	DDX_Text(pDX, IDC_EDT_MINC2, m_min_c2);
	DDV_MinMaxInt(pDX, m_min_c2, 0, 60);
	DDX_Text(pDX, IDC_EDT_MINC3, m_min_c3);
	DDV_MinMaxInt(pDX, m_min_c3, 0, 60);
	DDX_Text(pDX, IDC_EDT_MINC4, m_min_c4);
	DDV_MinMaxInt(pDX, m_min_c4, 0, 60);
	DDX_Text(pDX, IDC_EDT_MINC5, m_min_c5);
	DDV_MinMaxInt(pDX, m_min_c5, 0, 60);
	DDX_Text(pDX, IDC_EDT_MINC6, m_min_c6);
	DDV_MinMaxInt(pDX, m_min_c6, 0, 60);
	DDX_Text(pDX, IDC_EDT_MINC7, m_min_c7);
	DDV_MinMaxInt(pDX, m_min_c7, 0, 60);
	DDX_Text(pDX, IDC_EDT_MINC8, m_min_c8);
	DDV_MinMaxInt(pDX, m_min_c8, 0, 60);
	DDX_Text(pDX, IDC_EDT_MINC9, m_min_c9);
	DDV_MinMaxInt(pDX, m_min_c9, 0, 60);
	DDX_Text(pDX, IDC_EDT_SECC11, m_sec_total);
	DDV_MinMaxInt(pDX, m_sec_total, 0, 60);
	DDX_Text(pDX, IDC_EDT_SECC1, m_sec_c1);
	DDV_MinMaxInt(pDX, m_sec_c1, 0, 60);
	DDX_Text(pDX, IDC_EDT_SECC2, m_sec_c2);
	DDV_MinMaxInt(pDX, m_sec_c2, 0, 60);
	DDX_Text(pDX, IDC_EDT_SECC3, m_sec_c3);
	DDV_MinMaxInt(pDX, m_sec_c3, 0, 60);
	DDX_Text(pDX, IDC_EDT_SECC4, m_sec_c4);
	DDV_MinMaxInt(pDX, m_sec_c4, 0, 60);
	DDX_Text(pDX, IDC_EDT_SECC5, m_sec_c5);
	DDV_MinMaxInt(pDX, m_sec_c5, 0, 60);
	DDX_Text(pDX, IDC_EDT_SECC6, m_sec_c6);
	DDV_MinMaxInt(pDX, m_sec_c6, 0, 60);
	DDX_Text(pDX, IDC_EDT_SECC7, m_sec_c7);
	DDV_MinMaxInt(pDX, m_sec_c7, 0, 60);
	DDX_Text(pDX, IDC_EDT_SECC8, m_sec_c8);
	DDV_MinMaxInt(pDX, m_sec_c8, 0, 60);
	DDX_Text(pDX, IDC_EDT_SECC9, m_sec_c9);
	DDV_MinMaxInt(pDX, m_sec_c9, 0, 60);
	DDX_Text(pDX, IDC_EDT_SECC10, m_sec_c10);
	DDV_MinMaxInt(pDX, m_sec_c10, 0, 60);

	DDX_Control(pDX, IDC_CHECK21, m_ckb1);
	DDX_Control(pDX, IDC_CHECK22, m_ckb2);
	DDX_Control(pDX, IDC_CHECK23, m_ckb3);
	DDX_Control(pDX, IDC_CHECK24, m_ckb4);
	DDX_Control(pDX, IDC_CHECK25, m_ckb5);
	DDX_Control(pDX, IDC_CHECK26, m_ckb6);
	DDX_Control(pDX, IDC_CHECK27, m_ckb7);
	DDX_Control(pDX, IDC_CHECK28, m_ckb8);
	DDX_Control(pDX, IDC_CHECK29, m_ckb9);
	DDX_Control(pDX, IDC_CHECK210, m_ckb10);
	DDX_Control(pDX, IDC_CKB_C2SAVETST, m_ckbSaveChariotTest);
}


BEGIN_MESSAGE_MAP(CDlgChariot2, CDialogEx)
	ON_WM_SIZE()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_HC1, &CDlgChariot2::OnDeltaposSpinHc1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MC1, &CDlgChariot2::OnDeltaposSpinMc1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SC1, &CDlgChariot2::OnDeltaposSpinSc1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_HC2, &CDlgChariot2::OnDeltaposSpinHc2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MC2, &CDlgChariot2::OnDeltaposSpinMc2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SC2, &CDlgChariot2::OnDeltaposSpinSc2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_HC3, &CDlgChariot2::OnDeltaposSpinHc3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MC3, &CDlgChariot2::OnDeltaposSpinMc3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SC3, &CDlgChariot2::OnDeltaposSpinSc3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_HC4, &CDlgChariot2::OnDeltaposSpinHc4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MC4, &CDlgChariot2::OnDeltaposSpinMc4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SC4, &CDlgChariot2::OnDeltaposSpinSc4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_HC5, &CDlgChariot2::OnDeltaposSpinHc5)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MC5, &CDlgChariot2::OnDeltaposSpinMc5)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SC5, &CDlgChariot2::OnDeltaposSpinSc5)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_HC6, &CDlgChariot2::OnDeltaposSpinHc6)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MC6, &CDlgChariot2::OnDeltaposSpinMc6)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SC6, &CDlgChariot2::OnDeltaposSpinSc6)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_HC7, &CDlgChariot2::OnDeltaposSpinHc7)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MC7, &CDlgChariot2::OnDeltaposSpinMc7)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SC7, &CDlgChariot2::OnDeltaposSpinSc7)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_HC8, &CDlgChariot2::OnDeltaposSpinHc8)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MC8, &CDlgChariot2::OnDeltaposSpinMc8)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SC8, &CDlgChariot2::OnDeltaposSpinSc8)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_HC9, &CDlgChariot2::OnDeltaposSpinHc9)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MC9, &CDlgChariot2::OnDeltaposSpinMc9)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SC9, &CDlgChariot2::OnDeltaposSpinSc9)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_HC10, &CDlgChariot2::OnDeltaposSpinHc10)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MC10, &CDlgChariot2::OnDeltaposSpinMc10)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SC10, &CDlgChariot2::OnDeltaposSpinSc10)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_HC11, &CDlgChariot2::OnDeltaposSpinHc11)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MC11, &CDlgChariot2::OnDeltaposSpinMc11)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SC11, &CDlgChariot2::OnDeltaposSpinSc11)
	ON_BN_CLICKED(IDC_BTN_C2OK, &CDlgChariot2::OnBnClickedBtnC2ok)
	ON_BN_CLICKED(IDC_CKB_C2SAVETST, &CDlgChariot2::OnBnClickedCkbC2savetst)
END_MESSAGE_MAP()


// CDlgChariot2 消息处理程序

int CDlgChariot2::setContext(CIceLemonDlg *context)
{
	this->pIceLemonDlg = context;
	return (this->pIceLemonDlg != NULL);
}
void CDlgChariot2::ReSize(void)
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

BOOL CDlgChariot2::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect m_rect;
	GetClientRect(&m_rect);  //获取对话框的大小
	old.x=m_rect.right-m_rect.left;  
	old.y=m_rect.bottom-m_rect.top;

	return TRUE;  // return TRUE unless you set the focus to a control

}


void CDlgChariot2::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if(nType!=SIZE_MINIMIZED )  
	{
		ReSize();
	}
}


void CDlgChariot2::OnDeltaposSpinHc1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_hour_c1 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_hour_c1 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot2::OnDeltaposSpinMc1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_min_c1 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_min_c1 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot2::OnDeltaposSpinSc1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_sec_c1 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_sec_c1 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}

void CDlgChariot2::OnDeltaposSpinHc2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_hour_c2 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_hour_c2 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot2::OnDeltaposSpinMc2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_min_c2 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_min_c2 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot2::OnDeltaposSpinSc2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_sec_c2 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_sec_c2 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}
void CDlgChariot2::OnDeltaposSpinHc3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_hour_c3 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_hour_c3 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot2::OnDeltaposSpinMc3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_min_c3 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_min_c3 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot2::OnDeltaposSpinSc3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_sec_c3 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_sec_c3 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}
void CDlgChariot2::OnDeltaposSpinHc4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_hour_c4 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_hour_c4 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot2::OnDeltaposSpinMc4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_min_c4 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_min_c4 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot2::OnDeltaposSpinSc4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_sec_c4 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_sec_c4 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}

void CDlgChariot2::OnDeltaposSpinHc5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_hour_c5 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_hour_c5 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot2::OnDeltaposSpinMc5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_min_c5 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_min_c5 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot2::OnDeltaposSpinSc5(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_sec_c5 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_sec_c5 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}

void CDlgChariot2::OnDeltaposSpinHc6(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_hour_c6 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_hour_c6 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot2::OnDeltaposSpinMc6(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_min_c6 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_min_c6 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot2::OnDeltaposSpinSc6(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_sec_c6 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_sec_c6 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}

void CDlgChariot2::OnDeltaposSpinHc7(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_hour_c7 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_hour_c7 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot2::OnDeltaposSpinMc7(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_min_c7 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_min_c7 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot2::OnDeltaposSpinSc7(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_sec_c7 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_sec_c7 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}
void CDlgChariot2::OnDeltaposSpinHc8(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_hour_c8 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_hour_c8 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot2::OnDeltaposSpinMc8(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_min_c8 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_min_c8 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot2::OnDeltaposSpinSc8(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_sec_c8 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_sec_c8 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}
void CDlgChariot2::OnDeltaposSpinHc9(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_hour_c9 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_hour_c9 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot2::OnDeltaposSpinMc9(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_min_c9 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_min_c9 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot2::OnDeltaposSpinSc9(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_sec_c9 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_sec_c9 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}

void CDlgChariot2::OnDeltaposSpinHc10(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_hour_c10 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_hour_c10 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot2::OnDeltaposSpinMc10(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_min_c10 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_min_c10 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot2::OnDeltaposSpinSc10(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_sec_c10 +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_sec_c10 -=1;
	}
	UpdateData(false);
	*pResult = 0;
}
void CDlgChariot2::OnDeltaposSpinHc11(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_hour_total +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_hour_total -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot2::OnDeltaposSpinMc11(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_min_total +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_min_total -=1;
	}
	UpdateData(false);
	*pResult = 0;
}


void CDlgChariot2::OnDeltaposSpinSc11(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	UpdateData(true);
	if(pNMUpDown->iDelta == -1){
		m_sec_total +=1;

	}else if(pNMUpDown->iDelta == 1){
		m_sec_total -=1;
	}
	UpdateData(false);
	*pResult = 0;
}

int CDlgChariot2::CheckItem(int i, Chariot2_Item &xItem,
			CIPAddressCtrl &IPAddr_e1,
			CIPAddressCtrl &IPAddr_e2,
			CComboBox &cbo_e1,CComboBox &cbo_e2, 
			int hour, int min, int sec, int nID)
{
	
	CString ip_e1_str, ip_e2_str;
	char msg[255]={0};
	xItem.id = i;
	//if( m_ckb1.GetCheck()){
		xItem.proflag = 0;
		IPAddr_e1.GetWindowText(ip_e1_str);
		if(ip_e1_str =="0.0.0.0"){
			CString str_p1;
			cbo_e1.GetWindowText(str_p1);
			if(str_p1 == ""){
				sprintf_s(msg,"The endpoint1 of item %d is set incorrectly. It must be set!!\nPlease recheck!!", i);
				MessageBox(msg, "Error", MB_OK | MB_ICONERROR);		
				cbo_e1.SetFocus();
				return 0;
			}
			strcpy_s(xItem.profile_e1,str_p1.GetBuffer(str_p1.GetLength()));
			xItem.proflag = 1;
		}
		xItem.e1 = ip_e1_str;
		IPAddr_e2.GetWindowText(ip_e2_str);
		if(ip_e2_str == "0.0.0.0" && xItem.proflag == 0){
			CString str_p2;
			cbo_e2.GetWindowText(str_p2);
			if(str_p2 == ""){
				sprintf_s(msg,"The endpoint of item %d is set incorrectly. It must be set!!\nPlease recheck!!", i);
				MessageBox(msg, "Error", MB_OK | MB_ICONERROR);		
				cbo_e2.SetFocus();
				return 0;
			}
			strcpy_s(xItem.profile_e2,str_p2.GetBuffer(str_p2.GetLength()));
			xItem.proflag = 2;
		}
		xItem.e2 = ip_e2_str;
		UpdateData(TRUE);
		xItem.testduration = (hour *3600 + min *60 + sec);

		if (xItem.testduration == 0)
		{
			sprintf_s(msg,"Test duration must not be zero!!\nPlease recheck!!");
			MessageBox(msg, "Error", MB_OK | MB_ICONERROR);
			GetDlgItem(nID)->SetFocus();
			return 0;
		}
		if(testfile != ""){
			xItem.testfile = testfile;
		}
		xItem.pairNum = 5;
	//}
	return 1;
}
void getScript(CString &script)
{
	char tmpBuf[255] = { 0 };
	GetCurrentDirectory(255, tmpBuf);
	script.Format("%s\\Scripts\\Throughput.scr", tmpBuf);	//默认打开的文件名
	
}
DWORD CDlgChariot2::GetProfileList()
{
	DWORD dwResult = 0;
	int i=0, k=0,cbLen = 0;
	char profileName[WLAN_MAX_NAME_LENGTH] ;
	PWLAN_PROFILE_INFO_LIST pProfileList;
	PWLAN_PROFILE_INFO pProfileInfo;
	CComboBox *pCb[] ={ 
		&m_cbo_p1e1, &m_cbo_p1e2,
		&m_cbo_p2e1, &m_cbo_p2e2,
		&m_cbo_p3e1, &m_cbo_p3e2,
		&m_cbo_p4e1, &m_cbo_p4e2,
		&m_cbo_p5e1, &m_cbo_p5e2,
		&m_cbo_p6e1, &m_cbo_p6e2,
		&m_cbo_p7e1, &m_cbo_p7e2,
		&m_cbo_p8e1, &m_cbo_p8e2,
		&m_cbo_p9e1, &m_cbo_p9e2,
		&m_cbo_p10e1, &m_cbo_p10e2,
		}; 

	pProfileList = pIceLemonDlg->pProfileList;
	cbLen = sizeof(pCb)/ sizeof(pCb[0]);
	for(i = 0; i < cbLen; i++){
		pCb[i]->ResetContent();
		for(k = 0; k < pProfileList->dwNumberOfItems; k++){
			pProfileInfo = &pProfileList->ProfileInfo[k];
			WideCharToMultiByte(CP_ACP, 0, pProfileInfo->strProfileName, WLAN_MAX_NAME_LENGTH, profileName, WLAN_MAX_NAME_LENGTH, NULL, NULL) ;
			pCb[i]->InsertString(k, profileName);

		}
	}
	
	return dwResult;
}

void CDlgChariot2::OnBnClickedBtnC2ok()
{
	// TODO: 在此添加控件通知处理程序代码
	Chariot2_Item xItem;
	CString script;
	CString ip_e1_str, ip_e2_str;
	char msg[255]={0};
	int cnt = 0 ;

	UpdateData(TRUE);
	getScript(script);
	strcpy_s(xItem.script,script.GetBuffer(script.GetLength())); 
	xItem.protocol = CHR_PROTOCOL_TCP;
	if( m_ckb1.GetCheck()){
		CheckItem(1, xItem,m_IPAddr1_e1,m_IPAddr1_e2, m_cbo_p1e1, m_cbo_p1e2, m_hour_c1, m_min_c1, m_sec_c1, IDC_EDT_SECC1);
		m_chariot2_List.push_back(xItem);
		cnt++;
	}else{
		return;
	}
	if( m_ckb2.GetCheck()){
		CheckItem(2, xItem,m_IPAddr2_e1,m_IPAddr2_e2, m_cbo_p2e1, m_cbo_p2e2, m_hour_c2, m_min_c2, m_sec_c2, IDC_EDT_SECC2);
		m_chariot2_List.push_back(xItem);
		cnt++;
	}else
		return;
	if( m_ckb3.GetCheck()){
		CheckItem(3, xItem,m_IPAddr3_e1,m_IPAddr3_e2, m_cbo_p3e1, m_cbo_p3e2, m_hour_c3, m_min_c3, m_sec_c3, IDC_EDT_SECC3);
		m_chariot2_List.push_back(xItem);
		cnt++;
	}else
		return;
	if( m_ckb4.GetCheck()){
		CheckItem(4, xItem,m_IPAddr4_e1,m_IPAddr4_e2, m_cbo_p4e1, m_cbo_p4e2, m_hour_c4, m_min_c4, m_sec_c4, IDC_EDT_SECC4);
		m_chariot2_List.push_back(xItem);
		cnt++;
	}else
		return;
	if( m_ckb5.GetCheck()){
		CheckItem(5, xItem,m_IPAddr5_e1,m_IPAddr5_e2, m_cbo_p5e1, m_cbo_p5e2, m_hour_c5, m_min_c5, m_sec_c5, IDC_EDT_SECC5);
		m_chariot2_List.push_back(xItem);
		cnt++;
	}else 
		return;
	if( m_ckb6.GetCheck()){
		CheckItem(6, xItem,m_IPAddr6_e1,m_IPAddr6_e2, m_cbo_p6e1, m_cbo_p6e2, m_hour_c6, m_min_c6, m_sec_c6, IDC_EDT_SECC6);
		m_chariot2_List.push_back(xItem);
		cnt++;
	}else
		return;
	if( m_ckb7.GetCheck()){
		CheckItem(7, xItem,m_IPAddr7_e1,m_IPAddr7_e2, m_cbo_p7e1, m_cbo_p7e2, m_hour_c7, m_min_c7, m_sec_c7, IDC_EDT_SECC7);
		m_chariot2_List.push_back(xItem);
		cnt++;
	}else
		return;
	if( m_ckb8.GetCheck()){
		CheckItem(8, xItem,m_IPAddr8_e1,m_IPAddr8_e2, m_cbo_p8e1, m_cbo_p8e2, m_hour_c8, m_min_c8, m_sec_c8, IDC_EDT_SECC8);
		m_chariot2_List.push_back(xItem);
		cnt++;
	}else
		return;
	if( m_ckb9.GetCheck()){
		CheckItem(9, xItem,m_IPAddr9_e1,m_IPAddr9_e2, m_cbo_p9e1, m_cbo_p9e2, m_hour_c9, m_min_c9, m_sec_c9, IDC_EDT_SECC9);
		m_chariot2_List.push_back(xItem);
		cnt++;
	}else
		return;
	if( m_ckb10.GetCheck()){
		CheckItem(10, xItem,m_IPAddr10_e1,m_IPAddr10_e2, m_cbo_p10e1, m_cbo_p10e2, m_hour_c10, m_min_c10, m_sec_c10, IDC_EDT_SECC10);
		m_chariot2_List.push_back(xItem);
		cnt++;
	}else
		return;
	
	
	
}


void CDlgChariot2::OnBnClickedCkbC2savetst()
{
	// TODO: 在此添加控件通知处理程序代码
	CString fileName,strFilename;
	int iniValue = 0,nPos;
	iniValue = GetModuleFileName(0,strFilename.GetBuffer(MAX_PATH),MAX_PATH);
	if(iniValue<=0)
		return;
	strFilename.ReleaseBuffer();

	nPos=strFilename.ReverseFind('\\');   
	strFilename=strFilename.Left(nPos);   

	//AfxMessageBox(strFilename);
	//return ;
	if (m_ckbSaveChariotTest.GetCheck())
	{
		fileName = "D:\\xv\\Projects\\IceLemon\\IceLemon\\test_result\\test1";
		CFileDialog openFileDlg(FALSE, NULL,fileName, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, "文件(*.tst)| *.tst||", NULL);
		//openFileDlg.GetOFN().lpstrInitialDir = strFilename +"\\test1.tst";
		INT_PTR result = openFileDlg.DoModal();
		CString filePath = strFilename +"\\test1.tst";//defaultDir + "\\" + fileName;
		if(result == IDOK) {
			filePath = openFileDlg.GetPathName();
		}
		testfile = filePath;
	}
	else
		testfile = "";
}
