// DlgMain.cpp : 实现文件
//

#include "stdafx.h"
#include "IceLemon.h"
#include "DlgMain.h"
#include "afxdialogex.h"

#include "IceLemonDlg.h"
// CDlgMain 对话框

IMPLEMENT_DYNAMIC(CDlgMain, CDialogEx)

CDlgMain::CDlgMain(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMain::IDD, pParent)
{
	AfxInitRichEdit2();
	timeFreeze = false;
}

CDlgMain::~CDlgMain()
{
}

void CDlgMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_RUN, mBtnRun);
	DDX_Control(pDX, IDC_RICHEDIT22, m_redit);
	DDX_Control(pDX, IDC_LBL_RH, lblTimeRemainHour);
	DDX_Control(pDX, IDC_LBL_RM, lblTimeRemainMinute);
	DDX_Control(pDX, IDC_LBL_RS, lblTimeRemainSecond);
	DDX_Control(pDX, IDC_LBL_PROGRESSPERCENT, lblProgressPercent);
	DDX_Control(pDX, IDC_BTN_ABORT, mBtnAbort);
	DDX_Control(pDX, IDC_CB_ADAPTER, m_cb_WlInf);
	DDX_Control(pDX, IDC_CB_PROFILE, m_cb_profile);
}
int CDlgMain::setContext(CIceLemonDlg *context)
{
	this->pIceLemonDlg = context;
	return (this->pIceLemonDlg != NULL);
}

BEGIN_MESSAGE_MAP(CDlgMain, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_RUN, &CDlgMain::OnBnClickedBtnRun)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_PING, &CDlgMain::OnBnClickedBtnPing)
	ON_BN_CLICKED(IDC_BTN_IPCONF, &CDlgMain::OnBnClickedBtnIpconf)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CDlgMain::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_CONN, &CDlgMain::OnBnClickedBtnConn)
	ON_WM_KILLFOCUS()
	ON_CBN_KILLFOCUS(IDC_CB_ADAPTER, &CDlgMain::OnKillfocusCbAdapter)
	ON_CBN_SELCHANGE(IDC_CB_PROFILE, &CDlgMain::OnCbnSelchangeCbProfile)
END_MESSAGE_MAP()


// CDlgMain 消息处理程序

bool CheckAdapterExistence()
{
	RT_AdapterList AdapterList;
	CString AP_IPAddress, AP_PortNumber;
	ZeroMemory(&AdapterList, sizeof(AdapterList));
	
	return true;
}
void CDlgMain::OnBnClickedBtnRun()
{
	pIceLemonDlg->onBtnRun();

}

void CDlgMain::SetTestTime(int testTime)
{
	CString s;
	s.Format("%d",testTime / 3600);
	lblTimeRemainHour.SetWindowText(s);
	s.Format("%d",(testTime % 3600) / 60);
	lblTimeRemainMinute.SetWindowText(s);
	s.Format("%d",(testTime % 3600) % 60);
	lblTimeRemainSecond.SetWindowText(s);
}
int UpdateInterval = 1;

void CDlgMain::SetUpdateInterval(int x)
{
	UpdateInterval = x;
}
void CDlgMain::UpdateTimeRemain()
{
	unsigned long TimeRemain;
	CString  s_TimeRemainHour,
			s_TimeRemainMinute,
			s_TimeRemainSecond;

	lblTimeRemainHour.GetWindowText(s_TimeRemainHour);
	lblTimeRemainMinute.GetWindowText(s_TimeRemainMinute);
	lblTimeRemainSecond.GetWindowText(s_TimeRemainSecond);
	TimeRemain = StrToInt(s_TimeRemainHour) * 3600 +
		StrToInt(s_TimeRemainMinute) * 60 +
		StrToInt(s_TimeRemainSecond);

	if (TimeRemain != 0)
		TimeRemain--;
	CString s;
	s.Format("%d",TimeRemain / 3600);
	lblTimeRemainHour.SetWindowText(s);
	s.Format("%d",(TimeRemain % 3600) / 60);
	lblTimeRemainMinute.SetWindowText(s);
	s.Format("%d",(TimeRemain % 3600) % 60);
	lblTimeRemainSecond.SetWindowText(s);

}

void CDlgMain::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent){
	case 1:
		if (timeFreeze == false )
		{
			if (UpdateInterval == 5)
			{
				UpdateTimeRemain();
				UpdateInterval = 1;
			}
			else
				UpdateInterval++;
		}
		break;
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CDlgMain::FreezeTimeRemain()
{
	timeFreeze = true;
}

void CDlgMain::RestartTimeRemain()
{
	timeFreeze = false;
	UpdateInterval = 1;
}




void CDlgMain::OnBnClickedBtnPing()
{
	// TODO: 在此添加控件通知处理程序代码
	pIceLemonDlg->PingCmd();
}


void CDlgMain::OnBnClickedBtnIpconf()
{
	// TODO: 在此添加控件通知处理程序代码
	pIceLemonDlg->GetLocalIPInfo();
}


void CDlgMain::OnBnClickedBtnClear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_redit.SetWindowText("");
}


void CDlgMain::OnBnClickedBtnConn()
{
	// TODO: 在此添加控件通知处理程序代码
	pIceLemonDlg->OnConnect();
}





void CDlgMain::OnKillfocusCbAdapter()
{
	// TODO: 在此添加控件通知处理程序代码
	pIceLemonDlg->GetAvailableNetList();
	pIceLemonDlg->GetProfileList();

}


void CDlgMain::OnCbnSelchangeCbProfile()
{
	// TODO: 在此添加控件通知处理程序代码
}
