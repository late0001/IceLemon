
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
}

void CIceLemonDlg::PrintToMemo(CString str, int autoScrollToCur)
{
	if(autoScrollToCur) m_page_main.m_redit.LineScroll(m_page_main.m_redit.GetLineCount());
	m_page_main.m_redit.SetSel(-1,-1);
	m_page_main.m_redit.ReplaceSel(str);
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
				str.Format("%s\n IP: %s\tMask: %s\n",  pAdapter->Description, pIPAddr->IpAddress.String, pIPAddr->IpMask.String );
				m_page_chariot.cbxEndpoint1.AddString(pIPAddr->IpAddress.String);
				m_page_chariot.cbxEndpoint2.AddString(pIPAddr->IpAddress.String);
				PrintlnToMemo(str);
				pIPAddr = pIPAddr->Next;
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

const int th_ulimit[5] = {
	100, 200, 400, 800, 1000
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
	pPenGreen ->CreatePen(PS_SOLID, 1, RGB(0, 255, 0)); //绿色画笔
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
	

	for(i = 1; i <= 15; i++){ //横标
		s.Format("%d", i);
		pDC->MoveTo(i*40,0);
		pDC->LineTo(i*40,5);
		pDC->TextOut(i*40,-10, s);
	}
// 	    pDC->TextOut(7,50+0*40-5,"30");
// 		pDC->TextOut(7,50+1*40-5,"25");
// 		pDC->TextOut(7,50+2*40-5,"20");
// 		pDC->TextOut(7,50+3*40-5,"15");
// 		pDC->TextOut(7,50+4*40-5,"10");
// 		pDC->TextOut(7,50+5*40-5,"5");
// 		pDC->TextOut(7,50+6*40-5,"0");
	int upper_limit=th_ulimit[0];
	if(th_Cx != NULL){
		for(i=0 ; i < 5; i++){
			if(th_Cx->th_val_max<th_ulimit[i]){
				upper_limit = th_ulimit[i];
				break;
			}
		}
	}
	pDC->SelectObject(pPenBlack);    //换笔触
	int y_fac = 4,
		y_unit;
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
	for(i = 1; i <= 15; i++){ //竖线
		pDC->MoveTo(i*40,0);
		pDC->LineTo(i*40,290);
	}
	pDC->SelectObject(pPenRed);    //换笔触
	if(th_Cx != NULL){
		// 			pDC->MoveTo(0,0);
		 th_Cx->point[0].y =  th_Cx->th_val/upper_limit*290;
		 th_Cx->point[0].x = th_Cx->cur_idx*40;
		 th_Cx->point[1].y = th_Cx->th_val_max/upper_limit*290;
		 th_Cx->point[1].x = th_Cx->cur_idx*40;

		 xl.push_back(th_Cx->point[0]);
		 xl_max.push_back(th_Cx->point[1]);
		list<POINT>::iterator plist; 
		plist = xl.begin();
		pDC->MoveTo(*plist);
		for(plist = xl.begin(); plist != xl.end(); plist++) {  
			//POINT x = *plist; 
			pDC->LineTo(*plist);
		}
		pDC->SelectObject(pPenGreen);    //换笔触
		plist = xl_max.begin();
		//pDC->MoveTo(0,0);
		pDC->MoveTo(*plist);
		for(plist = xl_max.begin(); plist != xl_max.end(); plist++) {  
			//POINT x = *plist; 
			pDC->LineTo(*plist);
		}
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
	int i, QDirCount;
	
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

	m_page_main.KillTimer(1);

	if (!m_page_chariot.ckbEnablePreRun.GetCheck())
		remainTime = ChariotParameter.testduration * remainItem;
	else
	{
		if (h == 1) //before Pre-Run
		{
			remainTime = ((m_page_chariot.m_edit_preRun ) + (ChariotParameter.testduration))* remainItem/2;
		}
		else //before No-Pre-Run
		{
			remainTime = (m_page_chariot.m_edit_preRun) *  remainItem/2 + (ChariotParameter.testduration) * (remainItem/2+1) - 3;
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



