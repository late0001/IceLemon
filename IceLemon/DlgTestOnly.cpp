// DlgTestOnly.cpp : 实现文件
//

#include "stdafx.h"
#include "IceLemon.h"
#include "DlgTestOnly.h"
#include "afxdialogex.h"
#include "IceLemonDlg.h"

// CDlgTestOnly 对话框

IMPLEMENT_DYNAMIC(CDlgTestOnly, CDialogEx)

CDlgTestOnly::CDlgTestOnly(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTestOnly::IDD, pParent)
{

}

CDlgTestOnly::~CDlgTestOnly()
{
}

void CDlgTestOnly::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTestOnly, CDialogEx)
	ON_BN_CLICKED(ID_INFO, &CDlgTestOnly::OnBnClickedInfo)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgTestOnly::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgTestOnly::OnBnClickedButton2)
END_MESSAGE_MAP()


volatile double throughput_instant;
int gAvgThAddr;
int gOldAddr;
int gJmpBackAddr;
extern CIceLemonDlg *pIceLemonDlg;

// CDlgTestOnly 消息处理程序
int CDlgTestOnly::setContext(CIceLemonDlg *context)
{
	this->pIceLemonDlg = context;
	pIceLemonDlg = this->pIceLemonDlg;
	return (this->pIceLemonDlg != NULL);
}

//  00000000`011c7c90 55              push    rbp
//  00000000`011c7c91 8bec            mov     ebp,esp
//	00000000`011c7c93 81eca8000000    sub     esp,0A8h
//  00000000`011c7c99 8b450c          mov     eax,dword ptr [rbp+0Ch]
void my_report_get_extended_stats(int a, int b,int c, int d)
{
	throughput_instant = b;
	CString str;
	str.Format("%f", throughput_instant);
	pIceLemonDlg->m_page_testonly.GetDlgItem(IDC_LB_TP_INSTANT)->SetWindowText(str);
}
_declspec(naked) void hook_report_get_extended_stats()
{
	__asm{
			call  my_report_get_extended_stats
			push    ebp
			mov     ebp,esp
			sub     esp,0A8h
			push   gJmpBackAddr
			ret
	}
}


void CDlgTestOnly::OnBnClickedInfo()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	HMODULE  hMoudle = GetModuleHandle("chrcore.dll");
	if(NULL == hMoudle)
	{
		//hMoudle = LoadLibraryA("chrcore.dll");
		//if(NULL == hMoudle)
		{
			AfxMessageBox("can not get module handle!");
			return ;
		}
	}
	str.Format("0x%x", hMoudle);
	GetDlgItem(IDC_LB_MODBASE)->SetWindowText(str);
	int report_get_extended_stats_addr = (int)GetProcAddress(hMoudle, "report_get_extended_stats");
	gOldAddr = report_get_extended_stats_addr;
	gJmpBackAddr = gOldAddr +9;
	str.Format("0x%x", report_get_extended_stats_addr);
	GetDlgItem(IDC_LB_FUNC1_ADDR)->SetWindowText(str);
	SIZE_T NumOfBytesWritten;
	//Old_addr = *(int *)((int)xinc+1)+ (int)xinc + 5;
	int JmpOffSet = (int)hook_report_get_extended_stats - gOldAddr -5;
	unsigned char JmpCode[5] = { 0xe9, 0x00, 0x00, 0x00, 0x00 };
	RtlCopyMemory ( JmpCode+1, &JmpOffSet, 4 );
	WriteProcessMemory(GetCurrentProcess(),(BYTE*)gOldAddr,JmpCode,5,&NumOfBytesWritten);
	
	/*
	ixchariot.dll+6AD6EA - 8B 55 0C              - mov edx,[ebp+0C]
ixchariot.dll+6AD6ED - 8B 45 08              - mov eax,[ebp+08]
ixchariot.dll+6AD6F0 - E8 472F96FF           - call ixchariot.dll+1063C { 这里会改eax
 }
ixchariot.dll+6AD6F5 - 83 C4 0C              - add esp,0C { 12 }
ixchariot.dll+6AD6F8 - 8B E5                 - mov esp,ebp
ixchariot.dll+6AD6FA - 5D                    - pop ebp
ixchariot.dll+6AD6FB - C3                    - ret

	*/

}
int bTerminalThread = 0;
UINT read_th_func(LPVOID param)
{
	while (!bTerminalThread) {
		CIceLemonDlg *pIceLemonDlg = (CIceLemonDlg *)param;
		CDlgTestOnly *pDlgTestOnly = &pIceLemonDlg->m_page_testonly;
		CString str;
		str.Format("%g", throughput_instant);
		pDlgTestOnly->GetDlgItem(IDC_LB_TP_INSTANT)->SetWindowText(str);
		Sleep(100);
	}
	return 0;
}

void CDlgTestOnly::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//CString str;
	//str.Format("%g", throughput_instant);
	//pIceLemonDlg->m_page_testonly.GetDlgItem(IDC_LB_TP_INSTANT)->SetWindowText(str);

	AfxBeginThread(read_th_func, pIceLemonDlg, 0, 0, 0, 0);

}


void CDlgTestOnly::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	bTerminalThread = true;
}
