#pragma once

class CIceLemonDlg;

// CDlgAttenuator 对话框

class CDlgAttenuator : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAttenuator)

public:
	CDlgAttenuator(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAttenuator();

// 对话框数据
	enum { IDD = IDD_DLG_ATTENUATOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CIceLemonDlg *pIceLemonDlg;
	CPtrArray pStatics;
	CPtrArray pEdits;
	void CreateEdits();
	int setContext(CIceLemonDlg *context);
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButton1();
};
