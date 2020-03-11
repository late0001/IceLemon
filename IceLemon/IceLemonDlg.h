
// IceLemonDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "DlgMain.h"
#include "DlgChariot.h"
#include "xcommon.h"
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
	int m_curSelTab;
	CDialogEx *pDlg[2];
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	void DisplayPage(int i);
public:
	void InitTabCtrl();
	void onBtnRun();
	void OnKillfocusCbxProtocol();
	void OnClickedBtnScript();
	void OnClickedCkbSaveTst();
	void PrintlnToMemo(CString str);
	int  PingCmd();
	void GetLocalIPInfo();
	void InitChariotPage();
	bool CheckCardSetting();
	bool CheckTestDuration();
	bool CheckTestDirection();
	void CalculateLoopCount();
	void ChariotCheck(CHR_HANDLE handle, CHR_API_RC code, CHR_STRING where);
	bool CheckChariotSetting();
	void CalculateTotalTestTime();
	void CorrectTimeRemain(int h);
	void SetTotalTestTime();
	void UpdateProgress(int FinishRound);

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
	RunThread *MyRunThread;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	

private:
	unsigned long remainItem;
	

protected:
	afx_msg LRESULT OnUpdateuserdata(WPARAM wParam, LPARAM lParam);
};
