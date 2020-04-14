
// IceLemonDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "IceLemon.h"
#include "IceLemonDlg.h"
#include "afxdialogex.h"
#include "xcommon.h"
#include "Ping.h"
#include <IPHlpApi.h>

using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "Iphlpapi.lib")

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CIceLemonDlg 对话框
CIceLemonDlg *pIceLemonDlg;


CIceLemonDlg::CIceLemonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIceLemonDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	pIceLemonDlg = this;
}

void CIceLemonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX, IDC_STATIC_T, m_chartPic);
}

BEGIN_MESSAGE_MAP(CIceLemonDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CIceLemonDlg::OnTcnSelchangeTab1)
	ON_WM_CREATE()
	ON_MESSAGE(WM_UPDATEUSERDATA, &CIceLemonDlg::OnUpdateuserdata)
	ON_MESSAGE(WM_UPDATE_CHART, &CIceLemonDlg::OnUpdateChart)
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CIceLemonDlg 消息处理程序
void CIceLemonDlg::InitTabCtrl()
{
	m_tab.InsertItem(0,_T("Main"));
	m_tab.InsertItem(1,_T("Chariot"));
	m_page_main.Create(IDD_DLG_MAIN, &m_tab);
	m_page_chariot.Create(IDD_DLG_CHARIOT, &m_tab);
	m_page_main.setContext(this);
	m_page_chariot.setContext(this);
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 32;
	//rc.bottom -= 0;
	//rc.left += 0;
	//rc.right -= 0;
	m_page_main.MoveWindow(&rc);
	m_page_chariot.MoveWindow(&rc);
	//把对话框对象指针保存起来
	pDlg[0] = &m_page_main;
	pDlg[1] = &m_page_chariot;
	//显示初始页面
	pDlg[0]->ShowWindow(SW_SHOW);
	pDlg[1]->ShowWindow(SW_HIDE);
	//保存当前选择
	m_curSelTab = 0;

	
}
void CIceLemonDlg::InitChariotPage()
{
	m_page_chariot.cbxProtocol.AddString("TCP");
	m_page_chariot.cbxProtocol.AddString("UDP");
	m_page_chariot.cbxProtocol.AddString("IPX");
	m_page_chariot.m_cbx_use_case.AddString("单卡单AP");
	m_page_chariot.m_cbx_use_case.AddString("单卡双AP");
	m_page_chariot.m_cbx_use_case.AddString("双卡单AP");
	m_page_chariot.m_cbx_use_case.SetCurSel(0);
}

void CIceLemonDlg::PrintToMemo(CString str, int autoScrollToCur)
{
	if(autoScrollToCur) {
		int lineCnt = m_page_main.m_redit.GetLineCount();
		m_page_main.m_redit.LineScroll(lineCnt);
	}
	m_page_main.m_redit.SetSel(-1,-1);
	m_page_main.m_redit.ReplaceSel(str);
}

void CIceLemonDlg::PrintRtfToMemo(CString rtfStr)
{
	SETTEXTEX st;
	st.codepage = 1200;
	st.flags = ST_SELECTION | ST_KEEPUNDO ;
	m_page_main.m_redit.SendMessage(EM_SETTEXTEX, (WPARAM)&st,(LPARAM)(LPCSTR)rtfStr);	
}
void CIceLemonDlg::PrintlnToMemo(CString str, int autoScrollToCur)
{
	if(autoScrollToCur){
		int lineCnt = m_page_main.m_redit.GetLineCount();
		m_page_main.m_redit.LineScroll(lineCnt);
	}
	m_page_main.m_redit.SetSel(-1,-1);
	m_page_main.m_redit.ReplaceSel(str+"\n");
	
}

int CIceLemonDlg::PingCmd()
{
	CPing objPing;
	CString str;
	if(ChariotParameter.e2.IsEmpty()){
		return -1;
	}
	char *szDestIP = ChariotParameter.e2.GetBuffer(ChariotParameter.e2.GetLength());
	PingReply reply;
	str.Format("Pinging %s with %d bytes of data:\n", szDestIP, DEF_PACKET_SIZE);
	PrintlnToMemo(str, 1);
	int i =4;

	while (i-- > 0)
	{
		objPing.Ping(szDestIP, &reply);
		str.Format("Reply from %s: bytes=%d time=%ldms TTL=%ld\n", szDestIP, reply.m_dwBytes, reply.m_dwRoundTripTime, reply.m_dwTTL);
		PrintlnToMemo(str);
		Sleep(500);
	}
	return 0;
}

void CIceLemonDlg::GetLocalIPInfo()
{
	CString szMark;
	CString str;

	PIP_ADAPTER_INFO pAdapterInfo;
	PIP_ADAPTER_INFO pAdapter = NULL; 
	DWORD dwRetVal = 0; 

	pAdapterInfo = ( IP_ADAPTER_INFO * ) malloc( sizeof( IP_ADAPTER_INFO ) );
	ULONG ulOutBufLen; 
	ulOutBufLen = sizeof(IP_ADAPTER_INFO); 



	// 第一次调用GetAdapterInfo获取ulOutBufLen大小 
	if (GetAdaptersInfo( pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) 
	{ 
		free(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *) malloc (ulOutBufLen); 
	} 

	if ((dwRetVal = GetAdaptersInfo( pAdapterInfo, &ulOutBufLen)) == NO_ERROR) 
	{ 
		pAdapter = pAdapterInfo; 
		PrintToMemo("",1);
		while (pAdapter) 
		{
			PIP_ADDR_STRING pIPAddr;
			pIPAddr = &pAdapter->IpAddressList;
			while (pIPAddr)
			{
				str.Format("%s\n type: %d\nIP: %s\tMask: %s\n", 
					pAdapter->Description, 
					pAdapter->Type,
					pIPAddr->IpAddress.String, 
					pIPAddr->IpMask.String );
				if(strcmp(pIPAddr->IpAddress.String,"0.0.0.0")){

					m_page_chariot.cbxEndpoint1.AddString(pIPAddr->IpAddress.String);
					m_page_chariot.cbxEndpoint2.AddString(pIPAddr->IpAddress.String);
					if(pAdapter->Type == 6 && strstr(pAdapter->Description, "PCI")){
						m_page_chariot.cbxEndpoint1.SetWindowText(pIPAddr->IpAddress.String);
						m_page_chariot.m_ip_ap1.SetWindowText(pIPAddr->IpAddress.String);
					}
					if(pAdapter->Type == 71 )
						m_page_chariot.cbxEndpoint2.SetWindowText(pIPAddr->IpAddress.String);
				}
				PrintlnToMemo(str);
				pIPAddr = pIPAddr->Next;
			}
			pAdapter = pAdapter->Next; 
		} 
	} 
	free(pAdapterInfo);
}

void CIceLemonDlg::GetLocalIPInfo(int index, CString &str_addr)
{
	char adapter_name[256+4];
	
	CString szMark;
	CString str;

	PIP_ADAPTER_INFO pAdapterInfo;
	PIP_ADAPTER_INFO pAdapter = NULL; 
	DWORD dwRetVal = 0; 
	PIP_ADDR_STRING pIPAddr;
	pAdapterInfo = ( IP_ADAPTER_INFO * ) malloc( sizeof( IP_ADAPTER_INFO ) );
	ULONG ulOutBufLen; 
	ulOutBufLen = sizeof(IP_ADAPTER_INFO); 
	if(index <0)index = 0;
	m_page_chariot.m_cbx_card1.GetLBText(index, adapter_name);
	// 第一次调用GetAdapterInfo获取ulOutBufLen大小 
	if (GetAdaptersInfo( pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) 
	{ 
		free(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *) malloc (ulOutBufLen); 
	} 

	if ((dwRetVal = GetAdaptersInfo( pAdapterInfo, &ulOutBufLen)) == NO_ERROR) 
	{ 
		pAdapter = pAdapterInfo; 
		PrintToMemo("",1);
		while (pAdapter) 
		{

			if(strcmp(pAdapter->Description, adapter_name) == 0){
				pIPAddr = &pAdapter->IpAddressList;
				while (pIPAddr)
				{

					if(strcmp(pIPAddr->IpAddress.String,"0.0.0.0")){
						str.Format("%s\n type: %d\nIP: %s\tMask: %s\n", 
							pAdapter->Description, 
							pAdapter->Type,
							pIPAddr->IpAddress.String, 
							pIPAddr->IpMask.String );
						str_addr = pIPAddr->IpAddress.String;
					}
					PrintlnToMemo(str);
					pIPAddr = pIPAddr->Next;
				}
			}

			pAdapter = pAdapter->Next; 
		} 
	} 
	free(pAdapterInfo);
}


void CIceLemonDlg::OnClickedBtnScript()
{
	CString defaultExt = "*.scr";	//默认打开的文件路径
	CString fileName = "D:\\xv\\Projects\\IceLemon\\IceLemon\\Scripts\\Throughput.scr";	//默认打开的文件名
	CString filter = "文件 (*.scr; *.*)|*.scr;*.*||";	//文件过虑的类型
	CFileDialog openFileDlg(TRUE, defaultExt, fileName, OFN_HIDEREADONLY|OFN_READONLY, filter, NULL);
	//openFileDlg.GetOFN().lpstrInitialDir = "E:\\FileTest\\test.doc";
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = fileName ;
	if(result == IDOK) {
		filePath = openFileDlg.GetPathName();
	}
	strcpy_s(ChariotParameter.script, filePath.GetBuffer(filePath.GetLength()));
	filePath.ReleaseBuffer();
	int x=-1;
	if(x = filePath.ReverseFind('\\')){
		filePath = filePath.Mid(x+1,filePath.GetLength()-x);
	}

	m_page_chariot.lblScript.SetWindowText(filePath);
	//AfxMessageBox(filePath);
}

void CIceLemonDlg::OnClickedCkbSaveTst()
{
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
	if (m_page_chariot.ckbSaveChariotTest.GetCheck())
	{
		fileName = "D:\\xv\\Projects\\IceLemon\\IceLemon\\test_result\\test1";
		CFileDialog openFileDlg(FALSE, NULL,fileName, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, "文件(*.tst)| *.tst||", NULL);
		//openFileDlg.GetOFN().lpstrInitialDir = strFilename +"\\test1.tst";
		INT_PTR result = openFileDlg.DoModal();
		CString filePath = strFilename +"\\test1.tst";//defaultDir + "\\" + fileName;
		if(result == IDOK) {
			filePath = openFileDlg.GetPathName();
		}
		ChariotParameter.testfile = filePath;
	}
	else
		ChariotParameter.testfile = "";

//	SetCurrentDir(Form1->WorkDictionary); 
}
UINT enum_wlaninf_func(LPVOID param)
{
	char desc[WLAN_MAX_NAME_LENGTH] ;
	int nRet=0;
	int i;
	int count;
	CIceLemonDlg *pIceLemonDlg = (CIceLemonDlg *)param;
	CWlanOp *pWlop = new CWlanOp;
	pIceLemonDlg->pWlOp = pWlop;
	CComboBox *pCb = &pIceLemonDlg->m_page_main.m_cb_WlInf;
	CComboBox *pCb1 = &pIceLemonDlg->m_page_chariot.m_cbx_card1;
	CComboBox *pCb2 = &pIceLemonDlg->m_page_chariot.m_cbx_card2;
	pWlop->setContext(pIceLemonDlg);
	count = pWlop->GetNumberOfInterfaces();
	//CString str;

	for(i=0; i < count; i++){
		nRet=WideCharToMultiByte(CP_OEMCP, 0, (LPCWCH)pWlop->GetDescription(i), -1, desc, 256, NULL, FALSE);
		pCb->InsertString(i,desc);
		pCb1->InsertString(i,desc);
		pCb2->InsertString(i,desc);
	}
	return 0;
}
int CIceLemonDlg::GetAvailableNetList()
{
	int index = m_page_main.m_cb_WlInf.GetCurSel();
	if(index == -1) index = 0;
	pGuid = pWlOp->GetInterfaceGuid(index);
	pWlOp->listAllNetwork(pGuid);
	return 0;
}

DWORD CIceLemonDlg::GetProfileList(int index)
{
	DWORD dwResult;
	int i;
	char profileName[WLAN_MAX_NAME_LENGTH] ;
	PWLAN_PROFILE_INFO_LIST pProfileList;
	PWLAN_PROFILE_INFO pProfileInfo;
	CComboBox *pCb = &m_page_main.m_cb_profile; 
	CComboBox *pCb1 = &m_page_chariot.m_cbx_profile1;
	CComboBox *pCb2 = &m_page_chariot.m_cbx_profile2;
	if(index == -1) index = 0;
	pGuid = pWlOp->GetInterfaceGuid(index);
	dwResult = pWlOp->GetProfileList(pGuid, &pProfileList);
	pCb->ResetContent();
	pCb1->ResetContent();
	pCb2->ResetContent();
	for(i = 0; i < pProfileList->dwNumberOfItems; i++){
		pProfileInfo = &pProfileList->ProfileInfo[i];
		WideCharToMultiByte(CP_ACP, 0, pProfileInfo->strProfileName, WLAN_MAX_NAME_LENGTH, profileName, WLAN_MAX_NAME_LENGTH,NULL,NULL) ;
		pCb->InsertString(i, profileName);
		pCb1->InsertString(i, profileName);
		pCb2->InsertString(i, profileName);
	}
	return dwResult;
}

DWORD CIceLemonDlg::Card2GetProfileList(int index)
{
	DWORD dwResult;
	int i;
	char profileName[WLAN_MAX_NAME_LENGTH] ;
	PWLAN_PROFILE_INFO_LIST pProfileList;
	PWLAN_PROFILE_INFO pProfileInfo;
	CComboBox *pCb2 = &m_page_chariot.m_cbx_profile2;
	if(index == -1) index = 0;
	pGuid = pWlOp->GetInterfaceGuid(index);
	dwResult = pWlOp->GetProfileList(pGuid, &pProfileList);
	pCb2->ResetContent();
	for(i = 0; i < pProfileList->dwNumberOfItems; i++){
		pProfileInfo = &pProfileList->ProfileInfo[i];
		WideCharToMultiByte(CP_ACP, 0, pProfileInfo->strProfileName, WLAN_MAX_NAME_LENGTH, 
			profileName, WLAN_MAX_NAME_LENGTH,NULL,NULL) ;
		pCb2->InsertString(i, profileName);
	}
	return dwResult;
}

UINT get_connect_state_func(LPVOID param)
{
	CIceLemonDlg *pIceLemonDlg = (CIceLemonDlg *)param;
	CWlanOp *pWlop = pIceLemonDlg->pWlOp ;
	PWLAN_CONNECTION_ATTRIBUTES pConnectAttr =(PWLAN_CONNECTION_ATTRIBUTES)GlobalAlloc(GMEM_ZEROINIT,sizeof(WLAN_CONNECTION_ATTRIBUTES)) ;
	int i = 10;
	int con_state ;
	while(i-->0){
		con_state = pWlop->GetConnectionAttributes(*pIceLemonDlg->pGuid, &pConnectAttr);
		if(con_state == 1) break;
		Sleep(500);
	}
	pIceLemonDlg->cur_is_connected = con_state;
	//Sleep(500);
	//delete pConnectAttr;
	GlobalFree(pConnectAttr);
	return 0;
}

int CIceLemonDlg::OnConnect( int index, char *profile, int wait)
{
	CString str;

//	WCHAR strProfileName[WLAN_MAX_NAME_LENGTH];
	//str.Format("=== %d",index);
	//AfxMessageBox(str);
	if(index == -1) index = 0;
	pGuid = pWlOp->GetInterfaceGuid(index);
	pWlOp->Connect(pGuid, profile);
	CWinThread *pthread = AfxBeginThread(get_connect_state_func,this,0,0,0);
	if(wait)
		WaitForSingleObject(pthread->m_hThread,INFINITE);
	return 0;
}


int CIceLemonDlg::OnConnect(struct Chariot *chariot)
{
	//pGuid =
	DWORD ret;
	CString str;
	char tmp[WLAN_MAX_NAME_LENGTH];
	WCHAR strProfileName[WLAN_MAX_NAME_LENGTH];
	int index = m_page_main.m_cb_WlInf.GetCurSel();
	if(index == -1) index = 0;
	//str.Format("=== %d",index);
	//AfxMessageBox(str);
	m_page_main.m_cb_profile.GetWindowText((LPTSTR)tmp,WLAN_MAX_NAME_LENGTH);

	pGuid = pWlOp->GetInterfaceGuid(index);
	pWlOp->Connect(pGuid, tmp);
	CWinThread *pWndTh = AfxBeginThread(get_connect_state_func,this,0,0,0);
	ret = WaitForSingleObject(pWndTh->m_hThread,INFINITE);
	return 0;
}

void CIceLemonDlg::InitDBConn()
{
	HRESULT hr;
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection");///创建Connection对象
		if(SUCCEEDED(hr))
		{
			m_pConnection->ConnectionTimeout = 5;
			//"Provider=Microsoft.ACE.OLEDB.12.0;Data Source=D:\xv\Projects\IceLemon\IceLemon\DAT.accdb"
			hr = m_pConnection->Open("Provider=Microsoft.ACE.OLEDB.12.0;Data Source=D:\\xv\\Projects\\IceLemon\\IceLemon\\DAT.accdb","","",adModeUnknown);///连接数据库
			///上面一句中连接字串中的Provider是针对ACCESS2000环境的，对于ACCESS97,需要改为:Provider=Microsoft.Jet.OLEDB.3.51;
		}
	}
	catch(_com_error e)///捕捉异常
	{
		CString errormessage;
		errormessage.Format("连接数据库失败!\r错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);///显示错误信息
	} 
}

BOOL CIceLemonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitTabCtrl();
	InitChariotPage();
	AfxBeginThread(enum_wlaninf_func,this,0,0,0,0);
	InitDBConn();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CIceLemonDlg::InsertRecord(Test1_item *item)
{
	///往表格里面添加记录
	 _variant_t RecordsAffected;
	CString sql;
#if 1
	sql.Format("INSERT INTO test1(endpoint1_ip,endpoint2_ip,throughput_avg,time1) VALUES ( '%s','%s',%f,Format(Now(),'hh:mm:ss'))",
		item->e1_ip.GetBuffer(item->e1_ip.GetLength()), 
		item->e2_ip.GetBuffer(item->e2_ip.GetLength()),
		item->throughput
		);
#else 
	sql = "INSERT INTO test1(endpoint1_ip,endpoint2_ip,throughput_avg,time1) VALUES ( 'ss','bb',1,Format(Now(),'hh:mm:ss'))";
#endif

	try{
		if(m_pConnection == NULL)
			InitDBConn();
		//m_pConnection->Execute(_bstr_t(sql),&RecordsAffected,adCmdText);
		m_pConnection->Execute(_bstr_t(sql),NULL,adCmdText);
	}catch(_com_error e){
		CString errormessage;
		errormessage.Format("失败!\r\n错误信息:%s",e.ErrorMessage());
	}

}

void CIceLemonDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
typedef struct _TH_Y_AXIS{
	int y_fac;
	int y_ulimit;
}TH_Y_AXIS;

typedef struct _TH_X_AXIS{
	int x_unit;
	int x_ulimit;
}TH_X_AXIS;

const TH_Y_AXIS th_y_axis[8] = {
	{5, 100},
	{4, 200},
	{4, 400},
	{4, 800},
	{5, 1000},
	{6, 1200},
	{5, 2000},
	{6, 2400},
};
const TH_X_AXIS th_x_axis[] = {
	{1, 15},
	{2, 30},
	{4, 60},
	{8, 120},
	{16,240},
	{32,480},
	{64,960},
};


// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CIceLemonDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	//-----------------------------------

#if 1	
	CFont font;
	int i; CString s;
	font.CreateFont(13,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,NULL);
	CWnd *pWnd=GetDlgItem(IDC_STATIC_T);
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	CFont *pOldFont;
	//CBrush *pOldBrush;
	CDC *pDC = pWnd->GetDC();
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetViewportExt(1,1);
	pDC->SetWindowExt(1,-1);
	CRect rc;
	pWnd->GetWindowRect(&rc);
	pDC->SetViewportOrg(25,rc.bottom - rc.top - 20);
	//CBrush *pBrush = new CBrush();
	//pBrush->CreateSolidBrush(RGB(0,0,0));
	
	//pOldBrush = pDC->SelectObject(pBrush);
	//pDC->SetBkColor(RGB(0,0,0));
	pDC->Rectangle(-25, -25, 710, 310);

	pOldFont=pDC->SelectObject(&font);   //换字体


	CPen *pPenRed = new CPen(); //创建画笔对象
	CPen *pPenGreen = new CPen(); //创建画笔对象
	CPen *pPenBlack=new CPen;
	pPenBlack->CreatePen(PS_DOT,1,RGB(0,0,0));
	pPenRed ->CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); //红色画笔
	pPenGreen ->CreatePen(PS_SOLID, 2, RGB(0, 255, 0)); //绿色画笔
	//选中当前红色画笔,并保存以前的画笔
	CGdiObject *pOldPen = pDC ->SelectObject(pPenRed);
	
	//绘制坐标轴
	pDC->MoveTo(0, 0);
	pDC ->LineTo(0, 310); //竖起轴
	pDC->MoveTo(0, 0);
	pDC ->LineTo(700,0); //水平轴

	pDC->MoveTo(0-5,310-7);//y轴箭头
	pDC->LineTo(0,310);
	pDC->LineTo(0+5,310-7);
	pDC->MoveTo(700-7,0-5);//x轴箭头
	pDC->LineTo(700,0);
	pDC->LineTo(700-7,0+5);

	pDC->TextOut(27,310,"吞吐量");
	pDC->TextOut(27,300,"(MBps)");
	pDC->TextOut(650,-7,"时间轴");
	

	
// 	for(i = 1; i <= 15; i++){ //横标
// 		s.Format("%d", i);
// 		pDC->MoveTo(i*40,0);
// 		pDC->LineTo(i*40,5);
// 		pDC->TextOut(i*40,-10, s);
// 	}
// 	    pDC->TextOut(7,50+0*40-5,"30");
// 		pDC->TextOut(7,50+1*40-5,"25");
// 		pDC->TextOut(7,50+2*40-5,"20");
// 		pDC->TextOut(7,50+3*40-5,"15");
// 		pDC->TextOut(7,50+4*40-5,"10");
// 		pDC->TextOut(7,50+5*40-5,"5");
// 		pDC->TextOut(7,50+6*40-5,"0");
	int upper_ylimit_ord= 0,
		upper_xlimit_ord = 0;
	if(th_Cx != NULL){
		int len = sizeof(th_y_axis)/sizeof(th_y_axis[0]);
		for(i=0 ; i < len; i++){
			if(th_Cx->th_val<th_y_axis[i].y_ulimit){
				upper_ylimit_ord = i;
				break;
			}
		}
		len = sizeof(th_x_axis)/sizeof(th_x_axis[0]);
		for(i = 0; i < len; i++){
			if(th_Cx->cur_idx < th_x_axis[i].x_ulimit){
				upper_xlimit_ord = i;
				break;
			}
		}
	}
	pDC->SelectObject(pPenBlack);    //换笔触
	int y_fac = th_y_axis[upper_ylimit_ord].y_fac,
		y_unit = 0,
	upper_limit = th_y_axis[upper_ylimit_ord].y_ulimit;
	y_unit = 290*1.0/y_fac;
	for(i = 0; i <= y_fac; i++){ //纵标
		s.Format("%d", i*upper_limit/y_fac);
		pDC->TextOut(-20,y_unit*i+5, s);
	}
	for (int i=1;i*y_unit<300;i++)  //行线
	{
		
		pDC->MoveTo(0,y_unit*i);
		pDC->LineTo(700,y_unit*i);
	}
	int x_unit_x = th_x_axis[upper_xlimit_ord].x_unit;
	float x_unit = 40*1.0/x_unit_x;
	for(i = 1; i <= 15; i++){
		s.Format("%d", i*x_unit_x);
 		pDC->MoveTo(i*40,0);
		pDC->LineTo(i*40,5);
		pDC->TextOut(i*40,-10, s);
	}
	for(i = 1; i <= 15; i++){ //竖线
		pDC->MoveTo(i*40,0);
		pDC->LineTo(i*40,290);
	}
	pPenRed->DeleteObject();
	pPenRed->CreatePen(PS_SOLID, 2, RGB(255, 0, 0)); //红色画笔
	pDC->SelectObject(pPenRed);    //换笔触

	if(th_Cx != NULL){
			if(th_Cx->cur_idx == 0){ xl.clear();}
		// 			pDC->MoveTo(0,0);
		 CV_META cm;
		 cm.idx = th_Cx->cur_idx;
		 cm.th_val=th_Cx->th_val;
		 cm.th_val_max = th_Cx->th_val_max;
		 xl.push_back(cm);
		// xl_max.push_back(th_Cx->th_val_max);
		list<CV_META>::iterator plist; 
		plist = xl.begin();
		POINT p1;
		p1.y= (*plist).th_val/upper_limit*290;
		p1.x = (*plist).idx*x_unit;
		pDC->MoveTo(p1);
		for(plist = xl.begin(); plist != xl.end(); plist++) {  
			POINT p2;
			p2.y= (*plist).th_val/upper_limit*290;
			p2.x = (*plist).idx*x_unit;
			pDC->LineTo(p2);
		}
#if 0
		pDC->SelectObject(pPenGreen);    //换笔触
		plist = xl.begin();
		//pDC->MoveTo(0,0);
		p1.y= (*plist).th_val_max/upper_limit*290;
		p1.x = (*plist).idx*x_unit;
		pDC->MoveTo(p1);
		for(plist = xl.begin(); plist != xl.end(); plist++) {  
			POINT p2;
			p2.y= (*plist).th_val_max/upper_limit*290;
			p2.x = (*plist).idx*x_unit;
			pDC->LineTo(p2);
		}
#endif
	}
	//pDC->LineTo(x,y)
	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldPen);
	//pDC->SelectObject(pOldBrush);
	delete pPenRed;
	delete pPenGreen;
	delete pPenBlack;
#endif 
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CIceLemonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CIceLemonDlg::DisplayPage(int i)
{
	
	pDlg[m_curSelTab]->ShowWindow(SW_HIDE);
	m_tab.SetCurSel(i);
	m_curSelTab = m_tab.GetCurSel();
	pDlg[m_curSelTab]->ShowWindow(SW_SHOW);
}

void CIceLemonDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	pDlg[m_curSelTab]->ShowWindow(SW_HIDE);
	m_curSelTab = m_tab.GetCurSel();
	pDlg[m_curSelTab]->ShowWindow(SW_SHOW);
	*pResult = 0;
}

void CIceLemonDlg::UpdateIPAddressListItem()
{
	CString s1[5],s2[5];
	int i;
	UpdateData(TRUE);
	int index = m_page_chariot.cbxEndpoint1.GetCurSel();
	CString s;
	if(index >= 0 )
		m_page_chariot.cbxEndpoint1.GetLBText(index,s);
	else 
		m_page_chariot.cbxEndpoint1.GetWindowText(s);
	s1[0] = s;

	for(i=1; i<=4; i++){
		if(i <= m_page_chariot.cbxEndpoint1.GetCount())
			m_page_chariot.cbxEndpoint1.GetLBText(i-1,s);
		s1[i] = s;
	}
	m_page_chariot.cbxEndpoint1.ResetContent();

	m_page_chariot.cbxEndpoint1.SetWindowText(s1[0]);
	for(i=0; i<=4; i++)
		m_page_chariot.cbxEndpoint1.AddString(s1[i]);

	index = m_page_chariot.cbxEndpoint2.GetCurSel();
	if(index >= 0 )
		m_page_chariot.cbxEndpoint2.GetLBText(index,s);
	else 
		m_page_chariot.cbxEndpoint2.GetWindowText(s);
	s2[0] =  s;

	for(i=1; i<=4; i++){
		if(i <= m_page_chariot.cbxEndpoint2.GetCount())
			m_page_chariot.cbxEndpoint2.GetLBText(i-1,s);
		s2[i] = s;
	}

	m_page_chariot.cbxEndpoint2.ResetContent();

	m_page_chariot.cbxEndpoint2.SetWindowText (s2[0]);
	for(i=0; i<=4; i++)
		m_page_chariot.cbxEndpoint2.AddString(s2[i]);
}

void CIceLemonDlg::OnKillfocusCbxProtocol()
{
	CString Protocol_Set[4] = {"","TCP","UDP","IPX"};
	bool IsValid = false;
	int i;
	CString s;
	for (i=1;i<=3;i++)
	{
		m_page_chariot.cbxProtocol.GetWindowText(s);
		if  (s == Protocol_Set[i])
		{
			IsValid = true;
			switch(i)
			{
			case 1:
				ChariotParameter.protocol = CHR_PROTOCOL_TCP;
				break;
			case 2:
				ChariotParameter.protocol = CHR_PROTOCOL_UDP;
				break;
			case 3:
				ChariotParameter.protocol = CHR_PROTOCOL_IPX;
				break;
			}
		}
	}

	if (!IsValid)
	{
		sprintf_s(msg,"Network protocol error!!\nplease recheck!!");
		MessageBox(msg, "Error", MB_OK | MB_ICONSTOP);

		DisplayPage(1); // To avoid page switch while input error

		m_page_chariot.cbxProtocol.SetFocus();
	}
}
void CIceLemonDlg::onBtnRun()
{
	// TODO: 在此添加控件通知处理程序代码
	int state;
	bool OutLoop;
	CString str;
	m_page_chariot.UpdateData(TRUE);
	m_page_main.mBtnRun.GetWindowText(str);
	if(str == "Run"){
		Flag.Run = false;
	}
	if( (IsSave == false) && (Flag.Run == false)){
		sprintf_s(msg, "The last test results are not saved yet!!\nDo you want to continue?");
		MessageBox(msg, "Run: Warning Message");
	}
	if(Flag.Run == false){
		state = 1;
		OutLoop = false;
		do{
			switch(state){
			case 1:
				state = 2;
				break;
			case 2:
				state = 3;
				break;
			case 3:  //******* Check attenuator connection and value
				state = 4;
				break;
			case 4:
				//CheckCardSetting();
				if(CheckUseCase() == false){
					state = 99;
					break;
				}
				state = 5;
				break;
			case 5://******* Check test duration setting
				if (CheckTestDuration() == false)
				{
					state = 99;
					break;
				}
				
				if(CheckEndpointIP() == false)
				{
					state = 99;
					break;
				}
				state = 6;
				break;
			case 6:
				if (CheckTestDirection() == false)
				{
					state = 99;
					break;
				}	         	 
				state = 7;
				break;
			case 7:
				CalculateLoopCount();
				state = 8;
				break;
			case 8:
				CalculateTotalTestTime();
				state = 9;
				break;
			case 9:
				if (CheckChariotSetting()== false)
				{
					state = 99;
					break;
				}  
				state = 10;
				break;
			case 10:
				state = 100;
				break;
			case 99:   //Error Occurs
				OutLoop = true;
				break;
			case 100:  //OK
				OutLoop = true;
				break;
			}
		}while(!OutLoop);
		if (state == 99)
			return;
		//Update IP address List Item
		UpdateIPAddressListItem();
		// New a RunThread, but halt operation temporary
// 		MyRunThread = new RunThread(this, true);
// 		//  Set Flag
// 		Flag.Run = true;
// 		Flag.Abort = false;
// 		Flag.Halt = false;
// 		// Pass status flag to Running thread
// 		MyRunThread->Set_Flag(Flag);
// 
// 		// Pass Chariot parameters to Running thread
// 		MyRunThread->Set_Chariot(ChariotParameter);

		//CWinThread *m_pThrd = AfxBeginThread(RUNTIME_CLASS(RunThread));//,0,0,CREATE_SUSPENDED,NULL);

		RunThread *MyRunThread  = (RunThread *)AfxBeginThread(RUNTIME_CLASS(RunThread),0,0,CREATE_SUSPENDED,NULL);
		
		MyRunThread->m_hParentWnd = this->m_hWnd;
		MyRunThread->SetContext(this);
		Flag.Run = true;
		Flag.Abort = false;
		Flag.Halt = false;
		// Pass status flag to Running thread
		MyRunThread->Set_Flag(Flag);

		// Pass Chariot parameters to Running thread
		MyRunThread->Set_Chariot(ChariotParameter);
		MyRunThread->ResumeThread();

	} 
	else if ( (Flag.Halt == false) && (Flag.Run == true) )
	{
		// Press Halt, the button change to "Continue"
		m_page_main.mBtnRun.SetWindowText("Continue");
		Flag.Run = true;
		Flag.Halt = true;

		// Pass status flag to Running thread
		MyRunThread->Set_Flag(Flag);
	}
	else if ( (Flag.Halt == true) && (Flag.Run == true) )
	{
		// Press continue, the button changes to "Halt"

		m_page_main.mBtnRun.SetWindowText("Halt");

		Flag.Run = true;
		Flag.Halt = false;
		m_page_main.mBtnAbort.EnableWindow(TRUE);

		// Pass status flag to Running thread
		MyRunThread->Set_Flag(Flag);
	}

}

int CIceLemonDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Set default protocol
	ChariotParameter.protocol = CHR_PROTOCOL_TCP;
	//  Set Chariot testfile
	ChariotParameter.testfile = "";
	// Set Chariot twoway test false
	ChariotParameter.TwoWay = false;
	// set pre run time
	PreRunDuration = 5;
	// the default max throughput for plot
	maxThroughput = 30;
	// Set save state to false
	IsSave = false;
	return 0;
}

void CIceLemonDlg::UpdateProgress(int finishRound)
{
	remainItem =  totalTestItem - finishRound;

	CString s;
	s.Format("%d", ((totalTestItem-remainItem)*100)/totalTestItem);
	m_page_main.lblProgressPercent.SetWindowText(s);

}
void CIceLemonDlg::SetTotalTestTime()
{
	m_page_main.SetTestTime(totalTestTime);
}
void CIceLemonDlg::CalculateTotalTestTime()
{
	int i;
	LoopCount =ChariotParameter.loop_count;
	if (m_page_chariot.ckbEnablePreRun.GetCheck())
	{
		UpdateData(TRUE);
		ChariotParameter.Round_Count = 2;
		totalTestTime = ( (m_page_chariot.m_edit_preRun + (ChariotParameter.testduration)) * ChariotParameter.Pair_Count)
			 * LoopCount;
		UpdateData(FALSE);
	}
	else
	{
		ChariotParameter.Round_Count = 1;
		totalTestTime = ChariotParameter.testduration * ChariotParameter.Pair_Count
			* LoopCount;
	}

	totalTestItem = ChariotParameter.Round_Count * ChariotParameter.Pair_Count 
		* LoopCount;    

	SetTotalTestTime();
	UpdateProgress(0);
}
void CIceLemonDlg::CorrectTimeRemain(int h)
{
	unsigned long remainTime;
	unsigned long  test_duration; 
	m_page_main.KillTimer(1);
	test_duration = ChariotParameter.testduration;
	if(ChariotParameter.use_case == 1 || ChariotParameter.use_case == 2) test_duration = ChariotParameter.duration_single;
	if (!m_page_chariot.ckbEnablePreRun.GetCheck())
		remainTime = test_duration * remainItem;
	else
	{
		if (h == 1) //before Pre-Run
		{
			remainTime = ((m_page_chariot.m_edit_preRun ) + test_duration)* remainItem/2;
		}
		else //before No-Pre-Run
		{
			remainTime = (m_page_chariot.m_edit_preRun) *  remainItem/2 + test_duration * (remainItem/2+1) - 3;
		}
	}
	m_page_main.SetTestTime(remainTime);

	m_page_main.SetUpdateInterval(0);
	m_page_main.SetTimer(1, 200, NULL);

}


afx_msg LRESULT CIceLemonDlg::OnUpdateuserdata(WPARAM wParam, LPARAM lParam)
{
	bool x = (bool)wParam;
	m_page_chariot.UpdateData(x);
	return 0;
}




afx_msg LRESULT CIceLemonDlg::OnUpdateChart(WPARAM wParam, LPARAM lParam)
{
	Through_Curve_X *thCx =  (Through_Curve_X *)wParam;
	th_Cx = thCx;
	CRect rc;
	m_chartPic.GetClientRect(&rc);
	ScreenToClient(&rc);
	//UpdateWindow();
	InvalidateRect(&rc);
	return 0;
}


BOOL CIceLemonDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*sint ret = CDialogEx::OnEraseBkgnd(pDC);
	CWnd *pWnd=GetDlgItem(IDC_STATIC_T);
	CDC *pSDC = pWnd->GetDC();
	CBrush brush;
	brush.CreateSolidBrush(RGB(255,0,0));
	CRect rc;
	pWnd->GetWindowRect(&rc);
	pSDC->FillRect(rc, &brush);
	
	//return ret;
	*/
	return CDialogEx::OnEraseBkgnd(pDC);
}





void CIceLemonDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	pWlOp->~CWlanOp();
	if(pWlOp != NULL)
		delete pWlOp;
	if(m_pConnection->State)
		 m_pConnection->Close(); ///如果已经打开了连接则关闭它
}
