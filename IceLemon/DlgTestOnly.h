#pragma once

class CIceLemonDlg;
// CDlgTestOnly �Ի���

class CDlgTestOnly : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTestOnly)

public:
	CDlgTestOnly(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTestOnly();
	int setContext(CIceLemonDlg *context);
	CIceLemonDlg *pIceLemonDlg;
// �Ի�������
	enum { IDD = IDD_DLG_TESTONLY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedInfo();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
