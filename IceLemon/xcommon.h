#ifndef __X_COMMON_H__248990009877__
#define __X_COMMON_H__248990009877__
#include "afxwin.h"


#define EPDirectionCnt  4
#define AttValueCnt     60
#include "wlanapi.h"
#include <list>

using namespace std;
struct Chariot
{
	CString e1,e2;         // Define Endpoint1&2 IP address
	char script[256];      // The pointer which point to Chariot script file
	char script2[256];     // The pointer which point to Chariot script file if att> x dB
	char Qos[256];         //The service of quality
	CString testfile;	   // The pointer which point to Chariot test file
	char protocol;
	bool TwoWay;		   // Define if Tx/RX simultaneous test enable
	int use_case;
	int loop_count;
	unsigned long testduration,
		duration_single,
		Pair_Count,
		Round_Count,
		Test_Direction[EPDirectionCnt],   //index 0 not use
		iteration;
	unsigned long PairNum[3]; //how many Pair Numbers in each direction  //2008/3/20
	int card1_index;
	int card2_index;
	int  ap_count;
	char profile1[WLAN_MAX_NAME_LENGTH];
	char profile2[WLAN_MAX_NAME_LENGTH];
	char profile3[WLAN_MAX_NAME_LENGTH];
	CString str_ap1_addr;
	CString str_ap2_addr;
	CString str_ap3_addr;
};
typedef struct _Chariot2_Item
{
	CString e1,e2;
	int proflag;
	char profile_e1[WLAN_MAX_NAME_LENGTH];
	char profile_e2[WLAN_MAX_NAME_LENGTH];
	char script[256];  
	char protocol;
	unsigned long testduration;
	unsigned long pairNum;
	CString testfile;
}Chariot2_Item;

struct Attenuator
{
	unsigned long Attenuator_Value[AttValueCnt+1]; // Attenuator value matrix, index 0 not use
	unsigned long Value_Count;          // The number of attenuator value
	unsigned long MaxAttValue,
		MinAttValue;          // The Max and Min Attenuation value
	unsigned long Ext_Attenuation;      // External attenuation
	int Dev;
	int Dev2;
	int Dev3;
	int Dev4;
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

typedef struct _Test1_item{
	char SSID[255];
	CString e1_ip;
	CString e2_ip;
	double e1_e2;
	double e2_e1;
	double e1s_e2;
	double e2s_e1;
	double two_way;
	long time;
}Test1_item;

typedef struct _CV_META{
	int idx;
	float th_val;
	float th_val_max;
}CV_META;

#define	WM_UPDATEUSERDATA	(WM_USER + 1)
#define	WM_UPDATE_STEXT	(WM_USER + 2)
#define	WM_UPDATE_CHART	(WM_USER + 3)

class CIceLemonDlg;
class RunThread :public CWinThread
{
	 DECLARE_DYNCREATE(RunThread);
private:
	 CIceLemonDlg *pIceLemonDlg;
	 struct Attenuator AttenuatorParameter;
	 struct Chariot ChariotParameter;
	 struct SFlag Flag;
	 unsigned long test, run, pair[30];
	 bool IsError;
	 double avg1, avg2, avg3, avg4,avg5, avg6;
	 Through_Curve_X th_curve;
	 list<CV_META> xl;
	 Test1_item t_item;
	 CString datFileName;
	 char  DataTmpFileList[512];
	 list<Chariot2_Item> m_chariot2_List;
public:
	 CString dataFullName;
	 int run_flag;
public:
	 RunThread();
	 RunThread(CIceLemonDlg *pDlg, bool CreateSuspended);
	 void SetContext(CIceLemonDlg *pDlg);
	 bool SetupChariot(int x, unsigned long TestDuration);
	 bool SetupChariot2(Chariot2_Item *item);

	 CString GetChariotStatus(char x);
	 void GetThroughput(int x, int h);
	 void GetThroughputMax(int x, int h);
	 void GetThroughput(int AttIndex, int x, int h);
	 void GetThroughput2(Chariot2_Item *item, int AttIndex);
	 void SaveOneToDb(unsigned long saveFormat);
	 bool EndChariotTest();
	 void Creat_Test();
	 void Creat_Pair(unsigned int n);
	 void Save_ChariotTestFile(unsigned long direction, unsigned long loopcount,
		 unsigned long j, unsigned long k);
	 void Save_ChariotTestFile2(Chariot2_Item *item, unsigned loopcount,
		 unsigned long j, unsigned long k);
	 int GetSaveDataFileName(unsigned long direction, unsigned loop_count,
		 unsigned long j, unsigned long k, CString &fileName);
	 void SetDataTmpFile2(unsigned long jj, unsigned long k);
	 void TouchFile(int k);
	 int SaveTPToFile();
	 int GetDateTime(char (&buf)[255], int fmt);
	 void Set_Flag(struct SFlag flag);
	 void Set_Chariot(struct Chariot chariotP);
	 void SetDataTmpFile(unsigned long jj, unsigned long k);
	 void SaveTmpData(unsigned long saveFormat, unsigned long j, int k);
	 void SaveTmpData2(unsigned long j, int k);
	 int ConnectAndGetIP(int card_index, char *profile, CString &str_ap_addr);
	 int ConnectAndGetIP2(int card_index, char *profile, CString &str, CString lanIP);
	 void Set_Chariot2(list<Chariot2_Item> clist);
	 int Run();
	 int Run1();
	 int Run2();
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