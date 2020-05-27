#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "xcommon.h"
// CStatusDlg 对话框
#include "DlgChariot2.h"

class CChariotParaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChariotParaDlg)

public:
	CChariotParaDlg(CWnd* pParent = NULL);   // 标准构造函数
	CChariotParaDlg(CDlgChariot2 *pDlgChariot2,CWnd* pParent = NULL);
	virtual ~CChariotParaDlg();

// 对话框数据
	enum { IDD = IDD_DLG_CHARIOTITEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CDlgChariot2 *pDlgChariot2;
	int CheckItem(Chariot2_Item *xItem);
	afx_msg void OnBnClickedBtnOk();
	CIPAddressCtrl m_ip_e1;
	CIPAddressCtrl m_ip_e2;
	CComboBox m_cbo_e1_profile;
	CComboBox m_cbo_e2_profile;
	PIL_PROFILE_INFO_LIST pPrfList;
	int m_hour;
	int m_min;
	int m_sec;
	Chariot2_Item item;
	Chariot2_Item *pItem;
	BOOL bPreUpdate;
	afx_msg void OnDeltaposSpinSc1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMc1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinHc1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	DWORD InitProfileComboBox();
	int ShowItem(Chariot2_Item &xItem);
	int caculTimeToUI(unsigned long testDuration);
	int m_radio_tr;
	afx_msg void OnBnClickedRdoTx();
	afx_msg void OnBnClickedRdoRx();
};
