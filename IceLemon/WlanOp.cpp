#include "stdafx.h"
#include "WlanOp.h"
#include "IceLemonDlg.h"
#include <vector>
#pragma comment(lib, "wlanapi.lib")
#pragma comment( lib, "Rpcrt4.lib") // for UuidToString
using namespace std;

CWlanOp::CWlanOp(void)
{
	DWORD sVer; // version for open handle output. We don't use ir for anything.
	errorState = ERROR_SUCCESS;
	errorState = WlanOpenHandle(WLAN_API_VERSION, NULL, &sVer, &hClientHandle);
	if (ERROR_SUCCESS != errorState )
	{
		if (hClientHandle != NULL)
		{
			WlanCloseHandle(hClientHandle, NULL);
			//	TRACE("WLAN CLose for open fail %d \n",hClientHandle);
			hClientHandle = NULL;
		}
		return;
	}
	//	TRACE("Open OK for handle %d\n", hClientHandle);
	PWLAN_INTERFACE_INFO_LIST pIntfList = NULL;
	//RPC_WSTR strGuid = NULL;
	RPC_CSTR strGuid = NULL;
	UINT i = 0;
	int NumberOfInterfaces = 0;
	
	
	// enumerate wireless interfaces
	if ((errorState = WlanEnumInterfaces(hClientHandle, NULL, &pIntfList)) != ERROR_SUCCESS)
	{
		return;
	}
	NumberOfInterfaces = pIntfList->dwNumberOfItems;
	for (i = 0; i < pIntfList->dwNumberOfItems; i++)
	{
		//if (UuidToStringW(&pIntfList->InterfaceInfo[i].InterfaceGuid, &strGuid) == RPC_S_OK)
		if (UuidToString(&pIntfList->InterfaceInfo[i].InterfaceGuid, &strGuid) == RPC_S_OK)
		{

			TCHAR * tmp = NULL;
			GUID * ptmpGuidValue = NULL;
			TCHAR * desc = NULL;
			int * connectiontype = NULL;
			PWLIfInfo pInf=NULL;
			try
			{
				tmp = new TCHAR[_tcsclen ((const char *)strGuid)+1];
				ptmpGuidValue = new GUID;
				desc = new TCHAR[256];
				connectiontype = new int;
				//CString tempStr;
				pInf = new WLIfInfo;
				_tcscpy_s(tmp, _tcsclen((TCHAR *)strGuid)+1, (const char *)strGuid);
				*ptmpGuidValue =  pIntfList->InterfaceInfo[i].InterfaceGuid;
				//tempStr = pIntfList->InterfaceInfo[i].strInterfaceDescription;
				//_tcscpy_s(desc, 256, (const char *)pIntfList->InterfaceInfo[i].strInterfaceDescription);
				memcpy(desc ,pIntfList->InterfaceInfo[i].strInterfaceDescription , 256 );
				*connectiontype = pIntfList->InterfaceInfo[i].isState;
				pInf->guid = tmp;
				pInf->guidValue = ptmpGuidValue;
				pInf->ifcDescription = desc;
				pInf->connection = connectiontype;
				infArray.push_back(pInf);
				RpcStringFree(&strGuid);
			}
			catch(...)
			{
				if(tmp)
				{
					delete [] tmp;
					tmp = NULL;
				}
				if( ptmpGuidValue)
				{
					delete ptmpGuidValue;
					ptmpGuidValue = NULL;
				}
				if(desc)
				{
					delete [] desc;
					desc = NULL;
				}
				if(connectiontype)
				{
					delete connectiontype;
					connectiontype = NULL;
				}
				if(pInf)
				{
					delete pInf;
					pInf = NULL;
				}
			}
		}
	}
	if (pIntfList != NULL)
	{
		WlanFreeMemory(pIntfList);
	}
}

CWlanOp::~CWlanOp(void)
{
	if (hClientHandle != NULL)
	{
		WlanCloseHandle(hClientHandle, NULL);
		//TRACE("WLANClose handle %d for destructure \n",hClientHandle);
		hClientHandle = NULL;
	}
	//TCHAR * tmp;
	PWLIfInfo tmp;

	for (int i = (int)infArray.size() -1; i >= 0; i--)
	{
		tmp = (PWLIfInfo)infArray.at(i);
		delete tmp->guid;
		delete tmp->guidValue;
		delete tmp->connection;
		delete tmp->ifcDescription;
		//delete tmp->ifName;
		delete []tmp;
		infArray.erase(infArray.end() -1);
	}
}

int CWlanOp::GetNumberOfInterfaces()
{
	vector <PWLIfInfo>::size_type count;
	count = infArray.size();

	//int i = (int)count;

	return(int)count;
}

WLAN_INTERFACE_STATE CWlanOp::GetInterfaceState(int index)
{
	if (index < (int)infArray.size())
	{
		return(WLAN_INTERFACE_STATE)*infArray[index]->connection;
	} else
	{
		return(WLAN_INTERFACE_STATE)-1;
	}
}

TCHAR *CWlanOp::GetDescription(int index)
{
	int size=infArray.size();

	if (index < size)
	{
		return infArray[index]->ifcDescription;
	} else
	{
		return NULL;
	}
}

DWORD CWlanOp::GetConnectionAttributes(
	IN GUID Guid, 
	OUT PWLAN_CONNECTION_ATTRIBUTES *ppConnAttr
	)
{
	DWORD dwDataSize = 0;
	DWORD dwRet = ERROR_SUCCESS;
	errorState = WlanQueryInterface(
		hClientHandle,
		&Guid,
		wlan_intf_opcode_current_connection,
		NULL, // reserved
		&dwDataSize,
		(PVOID*)ppConnAttr,
		NULL
		);
	dwRet = errorState;
	return dwRet;
}

DWORD CWlanOp::GetAvailableNetworkList(GUID *pGuid, PWLAN_AVAILABLE_NETWORK_LIST *ppNetList)
{
	DWORD dwResult;
	CString str;

	/*获得网络信息列表*/
	dwResult = WlanGetAvailableNetworkList(  hClientHandle , //客户端的会话句柄  
		pGuid,//要搜索的接口的GUID
		0x00,   //控制list中返回的网络的类型，XP SP2和SP3为零
		NULL, //指向返回的可用网络的 WLAN_AVAILABLE_NETWORK_LIST 的指针
		ppNetList);
	
	if(ERROR_SUCCESS != dwResult)
	{
		switch (dwResult)
		{
		case ERROR_INVALID_PARAMETER:    //参数四不为空，或其他参数为空
			str = "Para is NULL\n";
			break;
		case ERROR_INVALID_HANDLE:
			str = "Failed to INVALID HANDLE \n";
			break; 
		case ERROR_NOT_ENOUGH_MEMORY:
			str = "Failed to allocate memory \n";
			break;
		case ERROR_NDIS_DOT11_POWER_STATE_INVALID:    //广播关闭无法搜索
			str = "The radio for the interface is turned off \n";
			break;
		default:
			dwResult = GetLastError();
			str.Format("WlanGetAvailableNetworkList Fail： %wd\n", dwResult);
			break;
		}
		PrintlnToMemo(str);
		return false;
	}
	str.Format("WlanGetAvailableNetworkList Number %wd\n", (*ppNetList)->dwNumberOfItems);    //输出网络数量
	PrintlnToMemo(str);

	return dwResult;
}
void CWlanOp::listAllNetwork(GUID *pGuid)
{
	CString str;
	PWLAN_AVAILABLE_NETWORK_LIST pNetList = NULL;
	PWLAN_AVAILABLE_NETWORK pNet;
	int nNetNumber = 0;
	/*连接网络*/
	bool resultSearch = true;
	GetAvailableNetworkList(pGuid, &pNetList);
	str.Format("ssid \t");
	PrintToMemo(str);
	str.Format("uNumberOfPhyTypes \t");
	PrintToMemo(str);
	str.Format("wlanSignalQuality \t");
	PrintlnToMemo(str);

	CString szBuf = "{\\rtf1\\ansi\\ansicpg936\\deff0\\nouicompat\\deflang1033\\deflangfe2052{\\fonttbl{\\f0\\froman\\fprq2\\fcharset0 Times New Roman;}{\\f1\\fnil\\fprq2\\fcharset134 \\'b5\\'c8\\'cf\\'df;}{\\f2\\fnil\\fprq2\\fcharset134 \\'cb\\'ce\\'cc\\'e5;}}"
		"{\\colortbl ;\\red255\\green0\\blue0;}"
		"{\\*\\generator Riched20 10.0.14393}{\\*\\mmathPr\\mdispDef1\\mwrapIndent1440 }\\viewkind4\\uc1\\trowd\\trgaph108\\trleft5\\trbrdrl\\brdrs\\brdrw10 \\trbrdrt\\brdrs\\brdrw10 \\trbrdrr\\brdrs\\brdrw10 \\trbrdrb\\brdrs\\brdrw10 \\trpaddl108\\trpaddr108\\trpaddfl3\\trpaddfr3";
		
		str.Format("\\clbrdrl\\brdrw10\\brdrs\\clbrdrt\\brdrw10\\brdrs\\clbrdrr\\brdrw10\\brdrs\\clbrdrb\\brdrw10\\brdrs \\cellx2771\\clbrdrl\\brdrw10\\brdrs\\clbrdrt\\brdrw10\\brdrs\\clbrdrr\\brdrw10\\brdrs\\clbrdrb\\brdrw10\\brdrs \\cellx5536\\clbrdrl\\brdrw10\\brdrs\\clbrdrt\\brdrw10\\brdrs\\clbrdrr\\brdrw10\\brdrs\\clbrdrb\\brdrw10\\brdrs \\cellx8301" 
		"\\pard\\intbl\\nowidctlpar\\qj\\cf1\\kerning2\\f1\\fs21\\lang2052 %s\\lang1033\\cell %s\\cell %s\\cell\\row\\trowd\\trgaph108\\trleft5\\trbrdrl\\brdrs\\brdrw10 \\trbrdrt\\brdrs\\brdrw10 \\trbrdrr\\brdrs\\brdrw10 \\trbrdrb\\brdrs\\brdrw10 \\trpaddl108\\trpaddr108\\trpaddfl3\\trpaddfr3",
		"SSID", "uNumberOfPhyTypes", "wlanSignalQuality");
		szBuf+=str;
		
	for(nNetNumber = 0; nNetNumber < pNetList->dwNumberOfItems; nNetNumber++)
	{
		/*获取网络信息，去重复*/
		pNet = (PWLAN_AVAILABLE_NETWORK)&pNetList->Network[nNetNumber];  
		str.Format("%-30s ", pNet->dot11Ssid.ucSSID);
		PrintToMemo(str);
		str.Format("%10u \t", pNet->uNumberOfPhyTypes);
		PrintToMemo(str);
		str.Format("%10u \t", pNet->wlanSignalQuality);
		PrintlnToMemo(str);
		str.Format("\\clbrdrl\\brdrw10\\brdrs\\clbrdrt\\brdrw10\\brdrs\\clbrdrr\\brdrw10\\brdrs\\clbrdrb\\brdrw10\\brdrs \\cellx2771\\clbrdrl\\brdrw10\\brdrs\\clbrdrt\\brdrw10\\brdrs\\clbrdrr\\brdrw10\\brdrs\\clbrdrb\\brdrw10\\brdrs \\cellx5536\\clbrdrl\\brdrw10\\brdrs\\clbrdrt\\brdrw10\\brdrs\\clbrdrr\\brdrw10\\brdrs\\clbrdrb\\brdrw10\\brdrs \\cellx8301" 
			"\\pard\\intbl\\nowidctlpar\\qj\\cf0 %s\\cell %u\\cell %u\\cell\\row\\trowd\\trgaph108\\trleft5\\trbrdrl\\brdrs\\brdrw10 \\trbrdrt\\brdrs\\brdrw10 \\trbrdrr\\brdrs\\brdrw10 \\trbrdrb\\brdrs\\brdrw10 \\trpaddl108\\trpaddr108\\trpaddfl3\\trpaddfr3",
			pNet->dot11Ssid.ucSSID, pNet->uNumberOfPhyTypes, pNet->wlanSignalQuality);
		szBuf += str;
	}
	szBuf+=
		"\\clbrdrl\\brdrw10\\brdrs\\clbrdrt\\brdrw10\\brdrs\\clbrdrr\\brdrw10\\brdrs\\clbrdrb\\brdrw10\\brdrs \\cellx2771\\clbrdrl\\brdrw10\\brdrs\\clbrdrt\\brdrw10\\brdrs\\clbrdrr\\brdrw10\\brdrs\\clbrdrb\\brdrw10\\brdrs \\cellx5536\\clbrdrl\\brdrw10\\brdrs\\clbrdrt\\brdrw10\\brdrs\\clbrdrr\\brdrw10\\brdrs\\clbrdrb\\brdrw10\\brdrs \\cellx8301" 
		"\\pard\\intbl\\nowidctlpar\\qj\\cell\\cell\\cell\\row" 
		"\\pard\\nowidctlpar\\sa200\\sl276\\slmult1\\kerning0\\f2\\fs22\\lang2052\\par"
		"}";
	pDlg->PrintRtfToMemo(szBuf);
}


GUID* CWlanOp::GetInterfaceGuid(int index)
{
	if (index < (int)infArray.size())
	{
		return infArray[index]->guidValue;
	} else
	{
		return NULL;
	}
}

#ifdef OUTPUT_DEBUG_INFO
int CWlanOp::setContext(CIceLemonDlg *pDialog)
{
	if(pDialog == NULL) return -1;
	pDlg = pDialog;
	return 0;
}
void CWlanOp::PrintToMemo(CString str, int autoScrollToCur)
{
	pDlg->PrintToMemo(str, autoScrollToCur);
}
void CWlanOp::PrintlnToMemo(CString str, int autoScrollToCur)
{
	pDlg->PrintlnToMemo(str,autoScrollToCur);
}
#endif

#if 1
int CWlanOp::Connect(GUID *pGuid, CHAR *ucSsid){
	LPCWSTR profileXml;
	CString str;
	WLAN_REASON_CODE wlanReason;
	char buf[256];
	WCHAR wbuf[256];
	DWORD dwResult;

 	DOT11_SSID dot11_ssid;
 	int len = strlen(ucSsid);
 	strcpy_s((char *)dot11_ssid.ucSSID , 32, ucSsid);
 	dot11_ssid.uSSIDLength = len;
	PWLAN_CONNECTION_PARAMETERS parameters = new WLAN_CONNECTION_PARAMETERS;
	MultiByteToWideChar(CP_ACP,0,ucSsid,256,wbuf,256);
	parameters->strProfile = wbuf;
	parameters->dot11BssType = dot11_BSS_type_any	;
	parameters->wlanConnectionMode = wlan_connection_mode_profile;
	parameters->dwFlags = 0;
	parameters->pDot11Ssid = &dot11_ssid;
	parameters->pDesiredBssidList = NULL;
	DWORD reserved;
	dwResult = WlanConnect(hClientHandle,pGuid,parameters,NULL);
	if(ERROR_SUCCESS != dwResult)
	{
		switch (dwResult)
		{
		case ERROR_INVALID_PARAMETER:
			wsprintf(buf, "Para is NULL\n");
			break;
		case ERROR_INVALID_HANDLE:
			wsprintf(buf, "Failed to INVALID HANDLE \n");
			break; 
		case ERROR_ACCESS_DENIED:
			wsprintf(buf, "The caller does not have sufficient permissions. \n");
			break;
		default:
			dwResult = GetLastError();
			wsprintf(buf, "WlanConnect Fail： %wd\n", dwResult);
			break;
		}
		AfxMessageBox(buf);
	}
#ifdef OUTPUT_DEBUG_INFO	
	else {
		PrintlnToMemo("Connect successful!");
	}
#endif
	delete parameters;
	return dwResult;
	
}
#else
int CWlanOp::Connect(GUID *pGuid){
	LPCWSTR profileXml;
	CString str;
	WLAN_REASON_CODE wlanReason;
	DWORD dwResult;
	char buf[256];
	std::wstring strHead=
		L"<?xml version=\"1.0\" encoding=\"US-ASCII\"?>\
		 <WLANProfile xmlns=\"http://www.microsoft.com/networking/WLAN/profile/v1\">\
		 <name>archC9V4_5G_XXX</name>\
		 <SSIDConfig>\
		 <SSID>\
		 <name>archC9V4_5G</name>\
		 </SSID>\
		 </SSIDConfig>\
		 <connectionType>ESS</connectionType>\
		 <connectionMode>auto</connectionMode>\
		 <autoSwitch>false</autoSwitch>\
		 <MSM>\
		 <security>\
		 <authEncryption>\
		 <authentication>WPA2PSK</authentication>\
		 <encryption>AES</encryption>\
		 <useOneX>false</useOneX>\
		 </authEncryption>\
		 <sharedKey>\
		 <keyType>passPhrase</keyType>\
		 <protected>false</protected>\
		 <keyMaterial>12345678</keyMaterial>\
		 </sharedKey>\
		 </security>\
		 </MSM>\
		 </WLANProfile>";
	profileXml=strHead.c_str();
	//	WlanSetProfileCustomUserData(hClientHandle,pGuid,profileXml,strHead.length(),NULL);
	dwResult=WlanSetProfile(hClientHandle,
		pGuid, 0,profileXml,NULL,TRUE,NULL,&wlanReason);
	if(ERROR_SUCCESS!=dwResult)
	{
		str.Format("wlan set profile failed,Error code %lu.\r\n",dwResult);
		AfxMessageBox(str);
	}

	DOT11_SSID dot11_ssid;
	int len = strlen("archC9V4_5G");
	strcpy_s((char *)dot11_ssid.ucSSID , 32, "archC9V4_5G");
	dot11_ssid.uSSIDLength = len;
	PWLAN_CONNECTION_PARAMETERS parameters = new WLAN_CONNECTION_PARAMETERS;
	parameters->strProfile = L"archC9V4_5G_XXX";
	parameters->dot11BssType = dot11_BSS_type_any	;
	parameters->wlanConnectionMode = wlan_connection_mode_profile;
	parameters->dwFlags = 0;
	parameters->pDot11Ssid = &dot11_ssid;
	parameters->pDesiredBssidList = NULL;
	DWORD reserved;
	dwResult = WlanConnect(hClientHandle,pGuid,parameters,NULL);
	if(ERROR_SUCCESS != dwResult)
	{
		switch (dwResult)
		{
		case ERROR_INVALID_PARAMETER:
			wsprintf(buf, "Para is NULL\n");
			break;
		case ERROR_INVALID_HANDLE:
			wsprintf(buf, "Failed to INVALID HANDLE \n");
			break; 
		case ERROR_ACCESS_DENIED:
			wsprintf(buf, "The caller does not have sufficient permissions. \n");
			break;
		default:
			dwResult = GetLastError();
			wsprintf(buf, "WlanConnect Fail： %wd\n", dwResult);
			break;
		}
		AfxMessageBox(buf);
	}
#ifdef OUTPUT_DEBUG_INFO	
	else {
		PrintlnToMemo("Connect successful!");
	}
#endif
	delete parameters;
	return dwResult;

}
#endif 
DWORD CWlanOp::GetProfileList(GUID *pGuid, PWLAN_PROFILE_INFO_LIST *ppProfileList)
{
	DWORD dwResult;
	dwResult = WlanGetProfileList(hClientHandle, pGuid, NULL, ppProfileList);
	return dwResult;
}