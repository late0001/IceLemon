#pragma once
#include "afxcmn.h"
#include "afxwin.h"
class CIceLemonDlg;

// CDlgChariot 对话框

class CDlgChariot : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgChariot)

public:
	CDlgChariot(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgChariot();

// 对话框数据
	enum { IDD = IDD_DLG_CHARIOT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


public:
	int setContext(CIceLemonDlg *pDlg);
	CIceLemonDlg *pIceLemonDlg;
	CSpinButtonCtrl m_spin_hour;
//	int m_edit_hour;
//	int m_edit_min;
//	int m_edit_sec;
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	int m_edit_hour;
	int m_edit_min;
	int m_edit_sec;

	
	afx_msg void OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin3(NMHDR *pNMHDR, LRESULT *pResult);
	int m_edit_preRun;
	afx_msg void OnDeltaposSpin4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEdtPrerundur();
	CButton ckbLoadTestFile;
	CButton ckbEndpoint12;
	CButton ckbEndpoint21;
	CButton ckb2way;
	CComboBox cbxEndpoint1;
	CComboBox cbxEndpoint2;
//	CEdit m_editctl_sec;
	CButton ckbSaveChariotTest;
	int E12PairCount;
	int E21PairCount;
	int E1221PairCount;
	CStatic lbl_saveName;
	CButton ckbEnablePreRun;
	CStatic lblScript;
	afx_msg void OnClickedBtnScript();
	virtual BOOL OnInitDialog();
	CComboBox cbxProtocol;
	afx_msg void OnKillfocusCbxProtocol();
//	afx_msg void OnBnClickedCkbSavetst();
	afx_msg void OnClickedCkbSaveTst();
	afx_msg void OnClickedBtnUpdateChariotParamData();
	int m_edit_hour_s;
	int m_edit_min_s;
	int m_edit_sec_s;
	afx_msg void OnDeltaposSpin5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin7(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_cbx_use_case;
	CComboBox m_cbx_card1;
	CComboBox m_cbx_card2;
	CComboBox m_cbx_profile1;
	CComboBox m_cbx_profile2;
	afx_msg void OnCbnKillfocusCbxCard1();
	afx_msg void OnCbnKillfocusCbxCard2();
	CIPAddressCtrl m_ip_ap1;
	CIPAddressCtrl m_ip_ap2;
	afx_msg void OnBnClickedButton2();
};
