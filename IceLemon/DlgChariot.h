#pragma once


// CDlgChariot �Ի���

class CDlgChariot : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgChariot)

public:
	CDlgChariot(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgChariot();

// �Ի�������
	enum { IDD = IDD_DLG_CHARIOT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
