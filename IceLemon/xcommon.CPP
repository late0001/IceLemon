#include "stdafx.h"
#include "xcommon.h"
#include "StatusDlg.h"

IMPLEMENT_DYNCREATE(RunThread, CWinThread)
BOOL RunThread::InitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类

	//return CWinThread::InitInstance();
	ASSERT(::IsWindow(m_hParentWnd)); 
	CWnd *pParent = CWnd::FromHandle(m_hParentWnd);
	CStatusDlg* pDlg = new CStatusDlg(pParent);
	pDlg->Create(IDD_DIALOG1, pParent);
	pDlg->ShowWindow(SW_SHOW);
	return TRUE;
}


int RunThread::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类

	return CWinThread::ExitInstance();
}
#define  WM_TEST (WM_USER +101)
BEGIN_MESSAGE_MAP(RunThread, CWinThread)
	ON_THREAD_MESSAGE(WM_TEST,OnTest)
END_MESSAGE_MAP()
void RunThread::OnTest(WPARAM wParam,LPARAM lParam)
{
	AfxMessageBox("test");
}
