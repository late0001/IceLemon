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
	ON_BN_CLICKED(IDC_BTN_SAVERESULT, &CDlgMain::OnBnClickedBtnSaveresult)
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
	char tmp[WLAN_MAX_NAME_LENGTH];
	int index = m_cb_WlInf.GetCurSel();
	if(index == -1) index = 0;
	m_cb_profile.GetWindowText((LPTSTR)tmp,WLAN_MAX_NAME_LENGTH);
	pIceLemonDlg->OnConnect(index, tmp, 0);
}





void CDlgMain::OnKillfocusCbAdapter()
{
	// TODO: 在此添加控件通知处理程序代码
	pIceLemonDlg->GetAvailableNetList();

	int index = m_cb_WlInf.GetCurSel();
	pIceLemonDlg->GetProfileList(index);

}


void CDlgMain::OnCbnSelchangeCbProfile()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDlgMain::OnBnClickedBtnSaveresult()
{
	// TODO: 在此添加控件通知处理程序代码
	CFile file;
	int cnt;
	CString FileName=_T(".\\DatFile.txt");
	CADODbHelper dbHelper;
	CString sql;
	Chariot2_result iResult;
	dbHelper.OnInitADOConn();
	file.Open(FileName, CFile::modeRead);
	file.Read(&cnt,sizeof(int));
	CString slinkRate;
	for(int i=0; i < cnt; i++){
		
		memset(&iResult,0,sizeof(iResult));
		file.Read(&iResult,sizeof(iResult));
		slinkRate.Format("%dM",iResult.linkRate/1000);
		sql.Format("insert into Result ( ReportId, ItemId, Throughput, SSID, Channel, LinkRate, StartTime, EndTime, TestLog) \
				   values (%d, %d, %.02f, '%s', %d, '%s', '%s', '%s', '%s')",
				   iResult.report_id, iResult.item_id, iResult.throughput, iResult.SSID, iResult.channel, slinkRate,iResult.start_time, iResult.end_time, iResult.testLog
				   );
		dbHelper.ExecuteSQL((_bstr_t)sql);
	}
	dbHelper.ExitConn();
	file.Close();
		
	
}
