#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "xcommon.h"
class CIceLemonDlg;
// CDlgChariot2 对话框

class CDlgChariot2 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgChariot2)

public:
	CIceLemonDlg *pIceLemonDlg;
	CDlgChariot2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgChariot2();
	int setContext(CIceLemonDlg *context);
	void ReSize(void);
// 对话框数据
	enum { IDD = IDD_DLG_CHARIOTV2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
protected:
		POINT old;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	int CheckItem(int i,Chariot2_Item &xItem,
		CIPAddressCtrl &IPAddr_e1,
		CIPAddressCtrl &IPAddr_e2,
		CComboBox &cbo_e1,CComboBox &cbo_e2, 
		int hour, int min, int sec, int nID);
	DWORD GetProfileList();
	list<Chariot2_Item> m_chariot2_List;
	CString testfile;	   // The pointer which point to Chariot test file
	CComboBox m_cbo_p1e1;
	CComboBox m_cbo_p1e2;
	CComboBox m_cbo_p2e1;
	CComboBox m_cbo_p2e2;
	CComboBox m_cbo_p3e1;
	CComboBox m_cbo_p3e2;
	CComboBox m_cbo_p4e1;
	CComboBox m_cbo_p4e2;
	CComboBox m_cbo_p5e1;
	CComboBox m_cbo_p5e2;
	CComboBox m_cbo_p6e1;
	CComboBox m_cbo_p6e2;
	CComboBox m_cbo_p7e1;
	CComboBox m_cbo_p7e2;
	CComboBox m_cbo_p8e1;
	CComboBox m_cbo_p8e2;
	CComboBox m_cbo_p9e1;
	CComboBox m_cbo_p9e2;
	CComboBox m_cbo_p10e1;
	CComboBox m_cbo_p10e2;
	CIPAddressCtrl m_IPAddr1_e1;
	CIPAddressCtrl m_IPAddr1_e2;
	CIPAddressCtrl m_IPAddr10_e1;
	CIPAddressCtrl m_IPAddr10_e2;
	CIPAddressCtrl m_IPAddr2_e1;
	CIPAddressCtrl m_IPAddr2_e2;
	CIPAddressCtrl m_IPAddr3_e1;
	CIPAddressCtrl m_IPAddr3_e2;
	CIPAddressCtrl m_IPAddr4_e1;
	CIPAddressCtrl m_IPAddr4_e2;
	CIPAddressCtrl m_IPAddr5_e1;
	CIPAddressCtrl m_IPAddr5_e2;
	CIPAddressCtrl m_IPAddr6_e1;
	CIPAddressCtrl m_IPAddr6_e2;
	CIPAddressCtrl m_IPAddr7_e1;
	CIPAddressCtrl m_IPAddr7_e2;
	CIPAddressCtrl m_IPAddr8_e1;
	CIPAddressCtrl m_IPAddr9_e1;
	CIPAddressCtrl m_IPAddr8_e2;
	CIPAddressCtrl m_IPAddr9_e2;
//	CString m_hour_c1;
	int m_hour_total;
	int m_hour_c1;
	int m_hour_c10;
	int m_hour_c2;
	int m_hour_c3;
	int m_hour_c4;
	int m_hour_c5;
	int m_hour_c6;
	int m_hour_c7;
	int m_hour_c8;
	int m_hour_c9;
	int m_min_total;
	int m_min_c1;
	int m_min_c10;
	int m_min_c2;
	int m_min_c3;
	int m_min_c4;
	int m_min_c5;
	int m_min_c6;
	int m_min_c7;
	int m_min_c8;
	int m_min_c9;
	int m_sec_total;
	int m_sec_c1;
	int m_sec_c10;
	int m_sec_c2;
	int m_sec_c3;
	int m_sec_c4;
	int m_sec_c5;
	int m_sec_c6;
	int m_sec_c7;
	int m_sec_c8;
	int m_sec_c9;
	CButton m_ckb1;
	CButton m_ckb2;
	CButton m_ckb3;
	CButton m_ckb4;
	CButton m_ckb5;
	CButton m_ckb6;
	CButton m_ckb7;
	CButton m_ckb8;
	CButton m_ckb9;
	CButton m_ckb10;
	afx_msg void OnDeltaposSpinHc1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMc1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinSc1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinHc2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMc2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinSc2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinHc3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMc3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinSc3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinHc4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMc4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinSc4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinHc5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMc5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinSc5(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinHc6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMc6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinSc6(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinHc7(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMc7(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinSc7(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinHc8(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMc8(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinSc8(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinHc9(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMc9(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinSc9(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinHc10(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMc10(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinSc10(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinHc11(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMc11(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinSc11(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnC2ok();
	afx_msg void OnBnClickedCkbC2savetst();
	CButton m_ckbSaveChariotTest;
};
