#pragma once


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
};
