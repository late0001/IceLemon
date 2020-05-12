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
	list<Chariot2_Item> m_chariot2_List;

	CString testfile;	   // The pointer which point to Chariot test file

//	CString m_hour_c1;
	int m_hour_total;
	
	int m_min_total;
	
	int m_sec_total;
	int item_id; 

	PIL_PROFILE_INFO_LIST pPrfList;

	afx_msg void OnDeltaposSpinHc11(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMc11(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinSc11(NMHDR *pNMHDR, LRESULT *pResult);
	void Chariot2_itemAdd(Chariot2_Item *item);
	void C2UpdateItem(Chariot2_Item *item,int i);
	void C2AddItem(Chariot2_Item *item);
	afx_msg void OnBnClickedBtnC2ok();
	afx_msg void OnBnClickedCkbC2savetst();
	CButton m_ckbSaveChariotTest;
	CListCtrl m_list;
	afx_msg void OnBnClickedBtnAddci();
//	CComboBox m_card;
	CComboBox m_cbo_card;
	afx_msg void OnKillfocusCbxCard();
	
	afx_msg void OnBnClickedBtnC2update();
};
