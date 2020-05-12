// DlgChariot2.cpp : 实现文件
//

#include "stdafx.h"
#include "IceLemon.h"
#include "DlgChariot2.h"
#include "afxdialogex.h"
#include "IceLemonDlg.h"
#include "ChariotParaDlg.h"
// CDlgChariot2 对话框

IMPLEMENT_DYNAMIC(CDlgChariot2, CDialogEx)

CDlgChariot2::CDlgChariot2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgChariot2::IDD, pParent)
	, m_hour_total(0)
	, m_min_total(0)
	, m_sec_total(0)
	, item_id(0)
	
{

}

CDlgChariot2::~CDlgChariot2()
{
}

void CDlgChariot2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//	DDX_Control(pDX, IDC_CBO_PROF1_E1, m_cbo_p1e1);
	//	DDX_Control(pDX, IDC_CBO_PROF1_E2, m_cbo_p1e2);
	// 	DDX_Control(pDX, IDC_CBO_PROF2_E1, m_cbo_p2e1);
	// 	DDX_Control(pDX, IDC_CBO_PROF2_E2, m_cbo_p2e2);
	// 	DDX_Control(pDX, IDC_CBO_PROF3_E1, m_cbo_p3e1);
	// 	DDX_Control(pDX, IDC_CBO_PROF3_E2, m_cbo_p3e2);
	// 	DDX_Control(pDX, IDC_CBO_PROF4_E1, m_cbo_p4e1);
	// 	DDX_Control(pDX, IDC_CBO_PROF4_E2, m_cbo_p4e2);
	// 	DDX_Control(pDX, IDC_CBO_PROF5_E1, m_cbo_p5e1);
	// 	DDX_Control(pDX, IDC_CBO_PROF5_E2, m_cbo_p5e2);
	// 	DDX_Control(pDX, IDC_CBO_PROF6_E1, m_cbo_p6e1);
	// 	DDX_Control(pDX, IDC_CBO_PROF6_E2, m_cbo_p6e2);
	// 	DDX_Control(pDX, IDC_CBO_PROF7_E1, m_cbo_p7e1);
	// 	DDX_Control(pDX, IDC_CBO_PROF7_E2, m_cbo_p7e2);
	// 	DDX_Control(pDX, IDC_CBO_PROF8_E1, m_cbo_p8e1);
	// 	DDX_Control(pDX, IDC_CBO_PROF8_E2, m_cbo_p8e2);
	// 	DDX_Control(pDX, IDC_CBO_PROF9_E1, m_cbo_p9e1);
	// 	DDX_Control(pDX, IDC_CBO_PROF9_E2, m_cbo_p9e2);
	// 	DDX_Control(pDX, IDC_CBO_PROF10_E1, m_cbo_p10e1);
	// 	DDX_Control(pDX, IDC_CBO_PROF10_E2, m_cbo_p10e2);
	// 	DDX_Control(pDX, IDC_IPADDR1_E1, m_IPAddr1_e1);
	// 	DDX_Control(pDX, IDC_IPADDR1_E2, m_IPAddr1_e2);
	// 	DDX_Control(pDX, IDC_IPADDR10_E1, m_IPAddr10_e1);
	// 	DDX_Control(pDX, IDC_IPADDR10_E2, m_IPAddr10_e2);
	// 	DDX_Control(pDX, IDC_IPADDR2_E1, m_IPAddr2_e1);
	// 	DDX_Control(pDX, IDC_IPADDR2_E2, m_IPAddr2_e2);
	// 	DDX_Control(pDX, IDC_IPADDR3_E1, m_IPAddr3_e1);
	// 	DDX_Control(pDX, IDC_IPADDR3_E2, m_IPAddr3_e2);
	// 	DDX_Control(pDX, IDC_IPADDR4_E1, m_IPAddr4_e1);
	// 	DDX_Control(pDX, IDC_IPADDR4_E2, m_IPAddr4_e2);
	// 	DDX_Control(pDX, IDC_IPADDR5_E1, m_IPAddr5_e1);
	// 	DDX_Control(pDX, IDC_IPADDR5_E2, m_IPAddr5_e2);
	// 	DDX_Control(pDX, IDC_IPADDR6_E1, m_IPAddr6_e1);
	// 	DDX_Control(pDX, IDC_IPADDR6_E2, m_IPAddr6_e2);
	// 	DDX_Control(pDX, IDC_IPADDR7_E1, m_IPAddr7_e1);
	// 	DDX_Control(pDX, IDC_IPADDR7_E2, m_IPAddr7_e2);
	// 	DDX_Control(pDX, IDC_IPADDR8_E1, m_IPAddr8_e1);
	// 	DDX_Control(pDX, IDC_IPADDR9_E1, m_IPAddr9_e1);
	// 	DDX_Control(pDX, IDC_IPADDR8_E2, m_IPAddr8_e2);
	// 	DDX_Control(pDX, IDC_IPADDR9_E2, m_IPAddr9_e2);
	//  DDX_Text(pDX, IDC_EDT_HOURC1, m_hour_c1);
	DDX_Text(pDX, IDC_EDT_HOURC11, m_hour_total);
	DDV_MinMaxInt(pDX, m_hour_total, 0, 60);

	DDX_Text(pDX, IDC_EDT_MINC11, m_min_total);
	DDV_MinMaxInt(pDX, m_min_total, 0, 60);

	DDX_Text(pDX, IDC_EDT_SECC11, m_sec_total);
	DDV_MinMaxInt(pDX, m_sec_total, 0, 60);

	DDX_Control(pDX, IDC_CKB_C2SAVETST, m_ckbSaveChariotTest);
	DDX_Control(pDX, IDC_LIST1, m_list);
	//  DDX_Control(pDX, IDC_CBX_C2CARD, m_card);
	DDX_Control(pDX, IDC_CBX_C2CARD, m_cbo_card);
}


BEGIN_MESSAGE_MAP(CDlgChariot2, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_C2OK, &CDlgChariot2::OnBnClickedBtnC2ok)
	ON_BN_CLICKED(IDC_CKB_C2SAVETST, &CDlgChariot2::OnBnClickedCkbC2savetst)
	ON_BN_CLICKED(IDC_BTN_ADDCI, &CDlgChariot2::OnBnClickedBtnAddci)
	ON_CBN_KILLFOCUS(IDC_CBX_C2CARD, &CDlgChariot2::OnKillfocusCbxCard)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_HC11, &CDlgChariot2::OnDeltaposSpinHc11)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MC11, &CDlgChariot2::OnDeltaposSpinMc11)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SC11, &CDlgChariot2::OnDeltaposSpinSc11)
	ON_BN_CLICKED(IDC_BTN_C2UPDATE, &CDlgChariot2::OnBnClickedBtnC2update)
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
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES); // 整行选择、网格线
	m_list.InsertColumn(0,"id",LVCFMT_LEFT, 50);
	m_list.InsertColumn(1,"E1 IP",LVCFMT_LEFT, 150);
	m_list.InsertColumn(2,"E1 profile",LVCFMT_LEFT, 150);
	m_list.InsertColumn(3,"E2 IP",LVCFMT_LEFT, 150);
	m_list.InsertColumn(4,"E2 profile",LVCFMT_LEFT, 150);
	m_list.InsertColumn(5,"time",LVCFMT_LEFT, 150);

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

	list<Chariot2_Item>::iterator pItem;  //定义迭代器
	for( pItem = m_chariot2_List.begin(); pItem != m_chariot2_List.end();pItem++){
		strcpy_s(pItem->script,script.GetBuffer(script.GetLength())); 
		pItem->protocol = CHR_PROTOCOL_TCP;
	}

#if 0
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
#endif	
	
	
}

void CDlgChariot2::Chariot2_itemAdd(Chariot2_Item *item)
{
	m_chariot2_List.push_back(*item);
}

void CDlgChariot2::C2AddItem(Chariot2_Item *item)
{
	CString str;
	int i = m_list.GetItemCount();
	m_list.InsertItem(i,"haha");
	str.Format("%d",i);
	m_list.SetItemText(i, 0, str );
	m_list.SetItemText(i, 1, item->e1);
	m_list.SetItemText(i, 2, item->profile_e1);
	m_list.SetItemText(i, 3, item->e2);
	m_list.SetItemText(i, 4, item->profile_e2);
	m_list.SetItemText(i, 5, item->pszTestDuration);
	item->lv_id = i;
	m_chariot2_List.push_back(*item);
}

void CDlgChariot2::C2UpdateItem(Chariot2_Item *item,int i)
{
	CString str;
	//m_list.InsertItem(i,"haha");
	str.Format("%d",i);
	m_list.SetItemText(i, 0, str );
	m_list.SetItemText(i, 1, item->e1);
	m_list.SetItemText(i, 2, item->profile_e1);
	m_list.SetItemText(i, 3, item->e2);
	m_list.SetItemText(i, 4, item->profile_e2);
	m_list.SetItemText(i, 5, item->pszTestDuration);
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


void CDlgChariot2::OnBnClickedBtnAddci()
{
	// TODO: 在此添加控件通知处理程序代码

	if(pPrfList ==NULL){
		MessageBox("Please select net card first!", "Info", MB_OK | MB_ICONINFORMATION);
		return ;
	}
	CChariotParaDlg dlg = new CChariotParaDlg(this);
	dlg.pPrfList = this->pPrfList;
	dlg.bPreUpdate = FALSE;
	if(IDOK == dlg.DoModal()){
		C2AddItem(&dlg.item);
	}
}

void CDlgChariot2::OnBnClickedBtnC2update()
{
	// TODO: 在此添加控件通知处理程序代码

	POSITION pos =  m_list.GetFirstSelectedItemPosition();   
	int sel_index = m_list.GetNextSelectedItem(pos); 
	if(sel_index == -1) {
		MessageBox("Not selected", "Error", MB_OK|MB_ICONERROR);
		return;
	}
	Chariot2_Item *sel_item=NULL;
	list<Chariot2_Item>::iterator iter;
	for(iter=m_chariot2_List.begin();iter !=m_chariot2_List.end(); iter++)
	{
		if(iter->lv_id == sel_index){
			sel_item = &(*iter);
		}

	}
	CChariotParaDlg dlg = new CChariotParaDlg(this);
	dlg.pPrfList = this->pPrfList;
	dlg.pItem = sel_item;
	dlg.bPreUpdate = TRUE;
	if(IDOK == dlg.DoModal()){
		C2UpdateItem(dlg.pItem, sel_index);
	}
}

void CDlgChariot2::OnKillfocusCbxCard()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_cbo_card.GetCurSel();
	
	pIceLemonDlg->CardNGetProfileList(index,&pPrfList);
	 
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



