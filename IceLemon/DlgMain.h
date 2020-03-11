#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "resource.h"
class CIceLemonDlg;
// CDlgMain �Ի���

class CDlgMain : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMain)

public:
	CDlgMain(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgMain();

// �Ի�������
	enum { IDD = IDD_DLG_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	bool timeFreeze;
public:
	int setContext(CIceLemonDlg *pDlg);
	afx_msg void OnBnClickedBtnRun();
	CIceLemonDlg *pIceLemonDlg;
	CButton mBtnRun;
	CRichEditCtrl m_redit;
	CStatic lblTimeRemainHour;
	CStatic lblTimeRemainMinute;
	CStatic lblTimeRemainSecond;
	void SetTestTime(int testTime);
	void CorrectTimeRemain(int h);
	void SetUpdateInterval(int x);
	void UpdateTimeRemain();
	void FreezeTimeRemain();
	void RestartTimeRemain();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic lblProgressPercent;
	CButton mBtnAbort;
	afx_msg void OnBnClickedBtnPing();
	afx_msg void OnBnClickedBtnIpconf();
};
