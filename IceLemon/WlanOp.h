#pragma once
#include <vector>
#include <wlanapi.h>
#define OUTPUT_DEBUG_INFO 1
#ifdef OUTPUT_DEBUG_INFO
class CIceLemonDlg;
#endif
typedef struct _WLIfInfo{
	TCHAR * guid;
	GUID * guidValue;
	TCHAR * ifcDescription;
	int * connection;
	char * ifName;
}WLIfInfo, *PWLIfInfo;

typedef struct _APInfo{
	char  Ssid[32];
	LONG  lRssi;
	ULONG  uLinkQuality;
	ULONG  ulChCenterFrequency;
	int channel;
}APInfo, *PAPInfo;

class CWlanOp
{
public:
	CWlanOp(void);
	~CWlanOp(void);
#ifdef OUTPUT_DEBUG_INFO
	int setContext(CIceLemonDlg *pDialog);
	void PrintToMemo(CString str, int autoScrollToCur = 0);
	void PrintlnToMemo(CString str, int autoScrollToCur = 0);
#endif
	int GetNumberOfInterfaces();
	WLAN_INTERFACE_STATE GetInterfaceState(int index);
	TCHAR *GetDescription(int index);
	DWORD GetConnectionAttributes(
		IN GUID Guid, 
		OUT PWLAN_CONNECTION_ATTRIBUTES *ppConnAttr,
		int print
		);
	int GetChannelByFrequency(int frequency);
	DWORD GetChCenterFrequency(
		_In_ GUID Guid,
		_In_opt_ CONST PDOT11_SSID pDot11Ssid,
		_In_ DOT11_BSS_TYPE dot11BssType,
		_In_ BOOL bSecurityEnabled,
		_In_ PAPInfo pApInfo
		);
	DWORD GetAvailableNetworkList(GUID *pGuid, PWLAN_AVAILABLE_NETWORK_LIST *ppNetList);
	DWORD GetProfileList(GUID *pGuid, PWLAN_PROFILE_INFO_LIST *ppProfileList);
	GUID* GetInterfaceGuid(int index);
	int Connect(GUID *pGuid, char *ssid);
	void listAllNetwork(GUID *pGuid);
public:
	HANDLE hClientHandle;
	DWORD errorState;
#ifdef OUTPUT_DEBUG_INFO
	CIceLemonDlg *pDlg;
#endif
private:
	std::vector<PWLIfInfo> infArray;
};

