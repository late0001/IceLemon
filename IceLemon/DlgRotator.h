#pragma once
#include "afxwin.h"

class CIceLemonDlg;
// CDlgRotator �Ի���

class CDlgRotator : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRotator)

public:
	CDlgRotator(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgRotator();

	int SetContext(CIceLemonDlg *context);

// �Ի�������
	enum { IDD = IDD_DLG_ROTATOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CIceLemonDlg *pIceLemonDlg;
	virtual BOOL OnInitDialog();
	CCheckListBox m_clbRotator;
	afx_msg void OnBnClickedBtnRotatorSelectall();
};
