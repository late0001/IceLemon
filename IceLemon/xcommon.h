#ifndef __X_COMMON_H__248990009877__
#define __X_COMMON_H__248990009877__
#include "afxwin.h"
#define EPDirectionCnt  4

struct Chariot
{
	CString e1,e2;      // Define Endpoint1&2 IP address
	char script[256];      // The pointer which point to Chariot script file
	char script2[256];      // The pointer which point to Chariot script file if att> x dB
	char Qos[256];         //The service of quality
	CString testfile;    // The pointer which point to Chariot test file
	char protocol;
	bool TwoWay;   // Define if Tx/RX simultaneous test enable
	unsigned long testduration,
		Pair_Count,
		Round_Count,
		Test_Direction[EPDirectionCnt],   //index 0 not use
		iteration;
	unsigned long PairNum[3]; //how many Pair Numbers in each direction  //2008/3/20
};

// Define flag varibles
struct SFlag
{
	bool Run,
		Halt,
		Abort;
};

typedef struct _Through_Curve_X{
	int cnt;
	int cur_idx;
	double th_val;
	double th_val_max;
	POINT point[15];
}Through_Curve_X, *PThrough_Curve_X;

#define	WM_UPDATEUSERDATA	(WM_USER + 1)
#define	WM_UPDATE_STEXT	(WM_USER + 2)
#define	WM_UPDATE_CHART	(WM_USER + 3)

class CIceLemonDlg;
class RunThread :public CWinThread
{
	 DECLARE_DYNCREATE(RunThread);
private:
	 CIceLemonDlg *pIceLemonDlg;
	 struct Chariot ChariotParameter;
	 struct SFlag Flag;
	 unsigned long test, run, pair[15];
	 bool IsError;
	 double avg1, avg2, avg3, avg4,avg5, avg6;
	 Through_Curve_X th_curve;
public:
	 RunThread();
	 RunThread(CIceLemonDlg *pDlg, bool CreateSuspended);
	 void SetContext(CIceLemonDlg *pDlg);
	 bool SetupChariot(int x, unsigned long TestDuration);
	 CString GetChariotStatus(char x);
	 void GetThroughput(int x, int h);
	 void GetThroughputMax(int x, int h);
	 void GetThroughput(int AttIndex, int x, int h);
	 bool EndChariotTest();
	 void Creat_Test();
	 void Creat_Pair(unsigned int n);
	 void Save_ChariotTestFile(unsigned long direction, unsigned loopcount,
		 unsigned long j, unsigned long k);
	 void Set_Flag(struct SFlag flag);
	 void Set_Chariot(struct Chariot chariotP);
	 int Run();
	 bool IsPreRun; 
	 virtual BOOL InitInstance();
	 virtual int ExitInstance();
protected:
	afx_msg void OnTest(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	HWND m_hParentWnd;
};

#endif