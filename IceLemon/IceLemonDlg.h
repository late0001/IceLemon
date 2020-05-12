
// IceLemonDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "DlgMain.h"
#include "DlgChariot.h"
#include "DlgChariot2.h"
#include "DlgTestOnly.h"
#include "xcommon.h"
#include "afxwin.h"
#include <list>
#include "WlanOp.h"
using namespace std;


// CIceLemonDlg 对话框
class CIceLemonDlg : public CDialogEx
{
// 构造
public:
	CIceLemonDlg(CWnd* pParent = NULL);	// 标准构造函数
	
// 对话框数据
	enum { IDD = IDD_ICELEMON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	CMenu m_menu;
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;
	CDlgMain m_page_main;
	CDlgChariot m_page_chariot;
	CDlgChariot2 m_page_chariot2;
	CDlgTestOnly m_page_testonly;
	int m_curSelTab;
	CDialogEx *pDlg[4];
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void DisplayPage(int i);
public:
	void InitTabCtrl();
	void InitDBConn();
	void onBtnRun();
	void Run1();
	void Run2();
	void OnKillfocusCbxProtocol();
	void OnClickedBtnScript();
	void OnClickedCkbSaveTst();
	void PrintToMemo(CString str, int autoScrollToCur = 0);
	void PrintlnToMemo(CString str, int autoScrollToCur = 0);
	void PrintRtfToMemo(CString rtfStr);
	int  PingCmd();
	void GetLocalIPInfo();
	void GetLocalIPInfo(int index, CString &str_addr);
	void InitChariotPage();
	bool CheckCardSetting();
	bool CheckEndpointIP();
	bool CheckTestDuration();
	bool CheckUseCase();
	bool CheckTestDirection();
	void CalculateLoopCount();
	void ChariotCheck(CHR_HANDLE handle, CHR_API_RC code, CHR_STRING where);
	bool CheckChariotSetting();
	void CalculateTotalTestTime();
	void CorrectTimeRemain(int h);
	void CorrectTimeRemain2(Chariot2_Item *item);
	void SetTotalTestTime();
	void UpdateProgress(int FinishRound);
	int OnConnect( int index, char *profile, int wait);
	int OnConnect(struct Chariot *chariot);
	int GetAvailableNetList();
	DWORD GetProfileList(int index);
	DWORD Card2GetProfileList(int index);
	DWORD CardNGetProfileList(int index, PIL_PROFILE_INFO_LIST *ppPrfList);
	void UpdateIPAddressListItem();
	void InsertRecord(CString sql);
	PWLAN_PROFILE_INFO_LIST pProfileList;
	// Define Chariot struct varibles
	struct Chariot ChariotParameter;
	// Define flag varibles
	struct SFlag Flag;
	int cur_sel_card;
	int saveFormat;
	bool IsSave;
	CString workDirectory;
	int FinishItem;
	int finishAttItem;
	char msg[CHR_MAX_RETURN_MSG];
	char errorInfo[CHR_MAX_ERROR_INFO];
	unsigned long PreRunDuration;
	unsigned long msgLen, errorLen;
	int rc;
	CString ExtChariotTestFile;
	unsigned long ExtTstPairCount;
	int LoopCount;
	int CurrentLoopCount;
	int totalTestItem, totalTestTime;
	int FinishChariotRoundCount;
	double maxThroughput;
	Through_Curve_X *th_Cx;
	list<CV_META> xl;
	//list<double> xl_max;
	RunThread *MyRunThread;
	CWlanOp *pWlOp;
	GUID *pGuid;
	int cur_is_connected;
	PIL_PROFILE_INFO_LIST pPrfList;

	_ConnectionPtr m_pConnection;
	

private:
	unsigned long remainItem;
	

protected:
	afx_msg LRESULT OnUpdateuserdata(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateChart(WPARAM wParam, LPARAM lParam);
public:
	CStatic m_chartPic;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnImportConf();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
