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
	DWORD CWlanOp::GetConnectionAttributes(
		IN GUID Guid, 
		OUT PWLAN_CONNECTION_ATTRIBUTES *ppConnAttr
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

