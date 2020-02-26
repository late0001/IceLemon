
// IceLemonDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "DlgMain.h"
#include "DlgChariot.h"

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
};
