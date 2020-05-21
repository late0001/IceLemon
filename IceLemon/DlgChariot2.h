#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "xcommon.h"
class CIceLemonDlg;
// CDlgChariot2 �Ի���

class CDlgChariot2 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgChariot2)

public:
	CIceLemonDlg *pIceLemonDlg;
	CDlgChariot2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgChariot2();
	int SetContext(CIceLemonDlg *context);
	void ReSize(void);
// �Ի�������
	enum { IDD = IDD_DLG_CHARIOTV2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	CButton m_ckbSaveChariotTest;
	CListCtrl m_list;
	PIL_PROFILE_INFO_LIST pPrfList;
	//	CComboBox m_card;
	CComboBox m_cbo_card;
	int  m_sel_card_idx;
	STest simple_test;
	afx_msg void OnDeltaposSpinHc11(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMc11(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinSc11(NMHDR *pNMHDR, LRESULT *pResult);
	void Chariot2_itemAdd(Chariot2_Item *item);
	void C2UpdateItem(Chariot2_Item *item,int i);
	void C2AddItem(Chariot2_Item *item);
	void C2ClearAllItem();
	afx_msg void OnBnClickedBtnC2ok();
	afx_msg void OnBnClickedCkbC2savetst();
	afx_msg void OnBnClickedBtnAddci();
	afx_msg void OnKillfocusCbxCard();
	afx_msg void OnBnClickedBtnC2update();
	afx_msg void OnBnClickedBtnC2del();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnSaveitems();
	afx_msg void OnBnClickedBtnLoadfromfile();

};
