
// IceLemonDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "DlgMain.h"
#include "DlgChariot.h"
#include "xcommon.h"
#include "afxwin.h"
#include <list>
#include "WlanOp.h"
using namespace std;

typedef struct _CV_META{
	int idx;
	float th_val;
	float th_val_max;
}CV_META;
// CIceLemonDlg �Ի���
class CIceLemonDlg : public CDialogEx
{
// ����
public:
	CIceLemonDlg(CWnd* pParent = NULL);	// ��׼���캯��
	
// �Ի�������
	enum { IDD = IDD_ICELEMON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;
	CDlgMain m_page_main;
	CDlgChariot m_page_chariot;
	int m_curSelTab;
	CDialogEx *pDlg[2];
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void DisplayPage(int i);
public:
	void InitTabCtrl();
	void onBtnRun();
	void OnKillfocusCbxProtocol();
	void OnClickedBtnScript();
	void OnClickedCkbSaveTst();
	void PrintToMemo(CString str, int autoScrollToCur = 0);
	void PrintlnToMemo(CString str, int autoScrollToCur = 0);
	void PrintRtfToMemo(CString rtfStr);
	int  PingCmd();
	void GetLocalIPInfo();
	void InitChariotPage();
	bool CheckCardSetting();
	bool CheckEndpointIP();
	bool CheckTestDuration();
	bool CheckTestDirection();
	void CalculateLoopCount();
	void ChariotCheck(CHR_HANDLE handle, CHR_API_RC code, CHR_STRING where);
	bool CheckChariotSetting();
	void CalculateTotalTestTime();
	void CorrectTimeRemain(int h);
	void SetTotalTestTime();
	void UpdateProgress(int FinishRound);
	int OnConnect();
	int GetAvailableNetList();
	DWORD GetProfileList();
	void UpdateIPAddressListItem();
	// Define Chariot struct varibles
	struct Chariot ChariotParameter;
	// Define flag varibles
	struct SFlag Flag;
	int SaveFormat;
	bool IsSave;
	int FinishItem;
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
	

private:
	unsigned long remainItem;
	

protected:
	afx_msg LRESULT OnUpdateuserdata(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateChart(WPARAM wParam, LPARAM lParam);
public:
	CStatic m_chartPic;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
};
