#ifndef RTL_WIRELESS_FUNCTION
#define RTL_WIRELESS_FUNCTION

#ifdef RT_EXPORTS
#define RT_API extern "C" __declspec(dllexport)
#else
#define RT_API extern "C" __declspec(dllimport)
#endif

#ifndef ULONGLONG
	typedef unsigned __int64 ULONGLONG;
#endif

		
/* add for 802.1x */
#include <Wincrypt.h>
/* end */

// define ================================================================================
#define WM_RTL_PORT_NOTIFY	(WM_USER+5408)


// enum ================================================================================

typedef enum	_CCX_PORT_STATE{
	PORT_STATE_UNAUTHENTICATED,
	PORT_STATE_AUTHENTICATING,
	PORT_STATE_FAST_PROVISION_START,
	PORT_STATE_FAST_PROVISION_SUCCESS,
	PORT_STATE_FAST_PROVISION_FAILED,
	PORT_STATE_FAST_AUTHENTICATION_START,
	PORT_STATE_FAST_AUTHENTICATION_SUCCESS,
	PORT_STATE_FAST_AUTHENTICATION_FAILED,
	PORT_STATE_AUTHENTICATED,
	PORT_STATE_DETECTING_LINK,
	PORT_STATE_LINK_DOWN,
	PORT_STATE_LINK_UP,
	PORT_STATE_RENEWING_IP,
	PORT_STATE_RENEW_IP_SUCCESS,
	PORT_STATE_RENEW_IP_FAILED,
	PORT_STATE_DETECTING_IPX_FRAME,
	PORT_STATE_IPX_SUCCESS,
	PORT_STATE_IPX_FAILED,
	PORT_STATE_FINDING_DOMAIN_CONTROLLER,
	PORT_STATE_DOMAIN_CONTROLLER_FOUND,
	PORT_STATE_DOMAIN_CONTROLLER_NOT_FOUND,
	PORT_STATE_ERROR_MESSAGE,
}CCX_PORT_STATE;

typedef	enum	_AUTH_STATUS{
	AUTH_STATUS_IDLE,
	AUTH_STATUS_IN_PROGRESS,
	AUTH_STATUS_FAILED,
	AUTH_STATUS_SUCCESSFUL,
}AUTH_STATUS;

typedef enum _AC_FAILURE_CODE {
        eUnknownReject = 150,        ///< Unknown reject
        eClientGenericReject,        ///< Could be because of a EAP-SECURID reject.
        eClientIdentityReject,        ///< Client identity/username was rejected.
        eClientPasswordReject,        ///< Client password was rejected by server (obsolete and should not be used).
        eClientTlsCertReject,        ///< Client certificate (TLS) was rejected.
        eServerGenericReject,        ///< Server could not be autenticated (a non-password, non-cert EAP type).
        eServerIdentityReject,        ///< Server identity was not recognized.
        eServerCertReject,                ///< Server certificate was rejected.
        eAuthenticationSuccess,        ///< Authentication success.
        eInvalidPin,                        ///< Invalid PIN.
        eDhcpFailure,                        ///< DHCP failure.
        eDhcpSucceeded,                        ///< DHCP success.
        eEapTypeRejected,                ///< The EAP-method was rejected.
        eRemoveSCard,                        ///< Using a smart card that was removed.
        eRemoveGSMCard,                 ///< GSM card was removed.
        eNoAAAServer,                        ///< Possibly no AAA server is available.
        eFastPacAvailable,                ///< A PAC is available.
        eFastInvalidOpaque,         ///< EAP-FAST authentication failed due to an invalid PAC.
        eFastPacAutoProvision,        ///< A PAC was provisioned but auto provisioning was turned off.
        eWpaPskWrongKey,                        ///< Wrong WPA PSK key.
        eErrorChangingPassword,        ///< Password change attempt failed. Server rejected the password.
        eRestrictedLogonHours,        ///< User has restricted logon hours.
        eAccountDisabled,                ///< The user's account is disabled.
        eNoDialInPermission,                ///< The user has no dial-in permission.
        eFastPacAutoProvisionOff,                ///< Auto provisioning is turned off.
        eFastAidMismatchAndGroupLocked, ///< Authority ID (A-ID) does not match what is expected and A-ID group is locked.
        ePasswordRetry,                        ///< Password retry requested (if OTP profile, next token is requested)
        eFastProvisioningDone,        ///< Done provisioning PACs, client can resume normal EAP-FAST authentication.
        eRogueApTimeout,                ///< Possibly no AAA server is available (Rogue AP timeout).
        eFastPacRequired,                ///< A PAC is required to continue EAP-FAST authentication. See GetFastPACIdEx/ResumeFastAuthEx.
        ePostureValidationFailed,        ///< Posture validation failed.	
}AC_FAILURE_CODE;

typedef enum	_WIRELESS_MODE{
	WIRELESS_MODE_AUTO,
	WIRELESS_MODE_802_11B,
	WIRELESS_MODE_802_11G,
	WIRELESS_MODE_802_11A,
	WIRELESS_MODE_802_11NG_20,   
	WIRELESS_MODE_802_11NG_40, 
	WIRELESS_MODE_802_11NA,   //Add for 8190 by Jacken 2007/04/11
	WIRELESS_MODE_UNKNOWN,
}WIRELESS_MODE;

// structure ===========================================================================
//--------Add by Jacken 2006/09/11-----------//
typedef struct _SC_Connect
{
	UCHAR 	SConfig_ssid[33];
	UINT	SConfig_auth_type;
	UINT	SConfig_enc_type;
	UCHAR	SConfig_network_key[65];
	UCHAR	SConfig_network_wep_key[4][26];
	int 	SConfig_wep_keyIndex;
	int		SConfig_wep_keylen;
}SC_Connect;

typedef struct _RT_BssidList
{
	UCHAR	NeworkType;			// 0:IBSS, 1:Infrastructure
	char	SSID[33];
	char	BSSID[6];
	UCHAR	SignalStrength;		// 0-100
	UCHAR	Channel;			// 1-14
	bool	Privacy;			// Use wep ?
	UCHAR	SupportedRates[8];	// In 0.5 Mbps, bit7 means basic rate
}RT_BssidList;

typedef struct _RT_BssidListEx
{
	UCHAR	NeworkType;			// 0:IBSS, 1:Infrastructure
	char	SSID[33];
	char	BSSID[6];
	UCHAR	SignalStrength;		// 0-100
	UCHAR	Channel;			// 1-14
	bool	Privacy;			// Use wep ?
	UCHAR	AvailableRateCount;	// Count for SupportedRates
	UCHAR	SupportedRates[256];// In 0.5 Mbps, bit7 means basic rate
	ULONG	CapEx;
	ULONG	GroupKeyCipherSuiteBitmap;
	ULONG	PairwiseKeyCipherSuiteBitmap;
	ULONG	AuthenticatedKeyManagementSuiteBitmap;
	WIRELESS_MODE	APWirelessMode;
	bool    WPS;                //IS Supported (Wi-Fi Protected Setup) Add by karl 
}RT_BssidListEx;

typedef struct _RT_AdapterList
{
	ULONG	AdapterNumber;
	char	AdapterName[50][200];
	bool    IsDisable[50];
	char    InstanceID[50][50];
	char    Mode[50][50];
}RT_AdapterList;

typedef union _RT_Statistics
{
	ULONG	Counter[12];
	struct
	{
		ULONG TxOK;
		ULONG TxError;
		ULONG TxRetry;
		ULONG TxBeaconOK;
		ULONG TxBeaconError;
		ULONG RxOK;
		ULONG RxPacketCount;
		ULONG RxRetry;
		ULONG RxCRC0_500;
		ULONG RxCRC500_1000;
		ULONG RxCRC1000_;
		ULONG RxICVError;
	}Name;
}RT_Statistics;

typedef union _RT_ExtendedStatistics
{
	ULONGLONG	Counter[2];
	struct
	{
		ULONGLONG TxBytes;
		ULONGLONG RxBytes;
	}Name;
}RT_ExtendedStatistics;

typedef struct _AssociateEntry{
	BOOLEAN			bUsed;
	UCHAR			Sum;
	UCHAR			MacAddr[6];
	ULONG			AuthAlg;		// 0:Open, 1:Shared
	UCHAR			AuthPassSeq;	// 2,4
	BOOLEAN			bAssociated;
	USHORT			AID;
	LARGE_INTEGER	LastActiveTime;
}AssociateEntry,*pAssociateEntry;

/* add for 802.1x by CCW */
typedef struct CertDesc
{
  struct CertDesc        *nextp;
  TCHAR                  *name;
  TCHAR                  *issuer;
  CRYPT_HASH_BLOB         hash;
  BOOL                    inMachineStore;
} CertDesc;

//---add By rcnjko on 07/07/11, for EAP-FAST related definition.
#define MAX_PAC_FILES_NUM 64

typedef enum _RT_EAP_FAST_PAC_TYPE
{
	RT_TUNNEL_PAC = 1,
	RT_MACHINE_PAC = 2
} RT_EAP_FAST_PAC_TYPE;

typedef struct _RT_PAC_FILE_INFO{
	char AID[128];
	char IID[128];
	RT_EAP_FAST_PAC_TYPE PACType;
}RT_PAC_FILE_INFO, *PRT_PAC_FILE_INFO;

typedef enum _EAP_FAST_VER {
	FAST_V1,
	FAST_V1A
}EAP_FAST_VER;

//---add By rcnjko on 07/09/24, implement callback mechanism for some 802.1x steps requiring UI involved.
typedef bool (*RT_UI_HANDLER)(void* pInput, void* pOutput);

typedef enum _RT_UI_CALLBACK_E{
	UI_CHANGE_PASSWORD, // Server required supplicant to change the password for it is expired.
	UI_SAVE_PAC, // Allow user to determine if he want to save the PAC file or not.
	UI_SHOW_AID_WARNNING, // Notify AID warnning message to user during AID selection.
	UI_IS_AUTO_PROVISION_ENABLED, // Check if auto-provision is enabled or not.

	UI_CALLBACK_COUNT // Total number of UI callback functions. This declaration musb be kept as last one.
}RT_UI_CALLBACK_E;

typedef struct _WPS_BSSID
{
    char             MacAddress[6];         // BSSID
    char                    Ssid[32];               // SSID
} WPS_BSSID, *PWPS_BSSID;

typedef struct _MIMO_RSSI
{
    ULONG			EnabledAntenna;
    ULONG			RSSI_AntennaA;
	ULONG			RSSI_AntennaB;
	ULONG			RSSI_AntennaC;
	ULONG			RSSI_AntennaD;
	ULONG			Average;
} MIMO_RSSI, *PMIMO_RSSI;

typedef struct _MIMO_SQ
{
    ULONG			SQ_AntennaA;
	ULONG			SQ_AntennaB;
} MIMO_SQ, *PMIMO_SQ;

/*
typedef struct _DriverInfo
{
	CString RegFolder;
	CString DriverDesc;
	CString sDriverDesc;
	CString DriverVersion;
	CString MatchingDeviceId;
	char    DriverDateData[8];
	CString InfPath;
	CString InfSection;
	CString ProviderName;
	CString Service;
}DriverInfo,*PDriverInfo;
*/

typedef enum _MAC_FILTER_TYPE{
           MAC_FILTER_DISABLE,
           MAC_FILTER_ACCEPT,
           MAC_FILTER_REJECT,
           MAC_FILTER_LOCK,
}MAC_FILTER_TYPE, *PMAC_FLTER_TYPE; //Add By Karl

typedef enum _WPS_METHOD_FLAG{
	METHOD_FLAG_DEFAULT,
	METHOD_FALG_PIN,
	METHOD_FLAG_PBC,
	METHOD_FLAG_ASSIGNED_PIN,
	METHOD_FLAG_CONFIG_AP,
	METHOD_FLAG_ADD_DEVICE,
	METHOD_FLAG_ASSIGNED_AP_PIN,
	METHOD_FLAG_AP_PIN,
}WPS_METHOD_FLAG;

//======================================================================================

//////////////////////////////////
//set server Certificate 
typedef enum
{
		True  = 1,
		False = 0
} Bool;
typedef struct _RT_server
{
    Bool	verifyChain;
    char	caCertUrl[100];
    char	domain[100];
    Bool	allowSubdomain;
    char	name[100];
    Bool	ignoreCase;
}RT_server,*PRT_server; //Add by Karl (2009/1/20) for set server Certificate 
//////////////////////////////////

RT_API bool RT_IsCardDisabled(void);

RT_API void RT_GetAdapterList(RT_AdapterList *pAdapterList,bool EnableDisabledDev=true);
RT_API void RT_SetDefaultAdapterIndex(LONG index);
RT_API bool RT_Initialize(bool EnableDisabledDev=true);
//RT_API bool RT_Initialize(bool EnableDisabledDev, RT_UI_HANDLER UiCallbackTable[UI_CALLBACK_COUNT]);
RT_API void RT_Stop();
RT_API void RT_SetDriverFileName(char *name);


RT_API char *RT_QueryOID(ULONG oid, char *Buf, int BufLen);
RT_API void RT_SetOID(ULONG oid, char *Data, int DataLen);

// add from shang, david
RT_API void RT_CustomRequest(ULONG oid, char *Data, ULONG *DataLen);

RT_API char *RT_GetRegistry(char *RegName,char *buf,int BufLen);
RT_API void RT_SetRegistry(char *RegName,char *RegValue);
RT_API HKEY RT_OpenClassRegKey(void);


RT_API void RT_Passphrase64(char *string,UCHAR key[4][16]);
RT_API void RT_Passphrase128(char *string,UCHAR *key);


RT_API void RT_GetMacAddress(char *retbuf);
RT_API void RT_GetMacAddressString(char *retbuf);
RT_API void RT_GetDriverPath(char *retbuf);
RT_API void RT_GetDriverDescription(char *retbuf);


RT_API ULONG RT_GetSupportedWirelessMode(void);
RT_API void RT_Disassociate(void);
RT_API void RT_Rescan(void);
RT_API void RT_NoAutoRescan(bool flag);
RT_API int  RT_SiteSurvey(RT_BssidList *retbuf,int WaitTimeInMS=0);
RT_API int  RT_SiteSurveyEx(RT_BssidListEx *retbuf,int WaitTimeInMS=0);
RT_API bool RT_IsXPConfig(void);
RT_API void RT_EnableZeroConfig(bool enable);
RT_API void RT_EnableZeroConfigService(bool enable);
RT_API bool RT_IsUnplug(void);
RT_API void RT_SaveLog(char *fileName);
RT_API int	RT_GetChannelList(UCHAR *listBuf);


RT_API WIRELESS_MODE RT_GetWirelessMode(void);
RT_API WIRELESS_MODE RT_GetCurrentWirelessMode(void);
RT_API int  RT_GetNetworkType(void);
RT_API void RT_GetSSID(char *ssid);
RT_API int  RT_GetFragmentationThreshold(void);
RT_API int  RT_GetRTSThreshold(void);
RT_API int	RT_GetBeaconInterval(void);
RT_API int  RT_GetPowerSaveMode(void);
RT_API int  RT_GetPreambleMode(void);
RT_API bool RT_GetShowIcon(void);
RT_API int  RT_GetChannel(void);
RT_API void RT_GetRates(int *Auto,int *rate1,int *rate2,int *rate5_5,int *rate11);
RT_API void RT_GetPrivacy(int *DataEncryptionMode,int *KeyLengh);
RT_API int  RT_GetAuthenticaionMode(void);
RT_API int  RT_GetDefaultKeyID(void);
RT_API bool RT_GetWEPKeyValid(int KeyLength,int index);
RT_API bool RT_Get802_1xStatus(void);
RT_API bool RT_GetIsRadioOff(void);
RT_API bool RT_GetIsDedicateProbe(void);
RT_API int	RT_GetDefaultEncryptionAlgorithm(void);
RT_API int	RT_GetTxPower(int channel);
RT_API bool RT_GetBSSID(char *bssid);
RT_API int	RT_GetChannelPlanByCountry(void);
RT_API int	RT_GetDTIMPeriod(void);


RT_API void RT_SetWirelessMode(WIRELESS_MODE mode);
RT_API void RT_SetAdhocDefaultWirelessMode(WIRELESS_MODE mode);
RT_API void RT_SetNetworkType(int type);
RT_API void RT_SetSSID(char *ssid);
RT_API void RT_SetFragmentationThreshold(int threshold);
RT_API void RT_SetRTSThreshold(int threshold);
RT_API void	RT_SetBeaconInterval(int interval);
RT_API void RT_SetPowerSaveMode(int mode);
RT_API void RT_SetPreambleMode(int mode);
RT_API void RT_SetShowIcon(bool flag);
RT_API void RT_SetChannel(int channel);
RT_API void RT_SetRates(bool Auto,int rate1,int rate2,int rate5_5,int rate11);
//RT_API void RT_SetRates(int rate);  //Temp Add by Jacken 2007/05/25
RT_API void RT_SetRatesG(bool Auto,int rate1,int rate2,int rate5_5,int rate11,int rate6,int rate9,int rate12,int rate18,int rate24,int rate36,int rate48,int rate54);
RT_API void RT_SetPrivacy(int DataEncryptionMode,int KeyLengh);
// By David & Owen on 04/11/19 for Easy Configuration
RT_API void RT_SetEncryptionStatus(unsigned long DataEncryptionMode);
//
RT_API void RT_SetAuthenticaionMode(int mode);
RT_API void RT_SetDefaultKeyID(int id);
RT_API void RT_SetWEPKey(int index,int len,UCHAR *key);
RT_API void RT_Set802_1xStatus(bool enable);
RT_API void RT_SetRadioOff(bool OffFlag);
RT_API void RT_SetDedicateProbe(bool Flag);
RT_API void RT_SetDefaultEncryptionAlgorithm(int Algorithm);
RT_API void RT_SetTxPower(int channel,int power);
RT_API void RT_SetBSSID(char *bssid);
RT_API void RT_SetChannelPlan(int plan);
RT_API void RT_SetChannelPlanByCountry(int country);
RT_API void RT_SetDTIMPeriod(int period);


RT_API bool RT_GetStatusMediaStatus(void);
RT_API void RT_GetStatusLinkInfo(int *LinkStaus,int *NetworkType,char *SSID,char *BSSID);
RT_API void RT_GetStatusSecurityInfo(int *Privacy,int *AuthType);
RT_API void RT_GetStatusChannelInfo(int *ChannelSet,int *Channel);
RT_API int	RT_GetStatusChannel(void);
RT_API int	RT_GetStatusPermanentChannelSet(void);
RT_API void RT_GetStatusPerformanceInfo(int *PreambleMode,UCHAR *Rates );
RT_API int  RT_GetStatusPowerMode(void);
RT_API void RT_GetStatusSignalInfo(int *Strength,int *quality);
RT_API void RT_GetStatusDriverInfo(char *ver,ULONG *UpTime);
RT_API bool RT_GetStatusAPIP(UCHAR *APIP);
RT_API bool RT_GetStatusHardwareRadioOff(void);
RT_API ULONG RT_GetStatusDynamicRate(void);
RT_API AUTH_STATUS RT_GetStatusAuthStatus(void);
RT_API AC_FAILURE_CODE RT_GetStatusACAuthStatus(void);
RT_API ULONG RT_GetStatus_11N_Txrate(void);  //Add by Jacken 2008/03/12
RT_API ULONG RT_GetStatus_11N_Rxrate(void);  //Add by Jacken 2008/03/12

RT_API void RT_GetStatistics(RT_Statistics *statistics);
RT_API void RT_GetExtendedStatistics(RT_ExtendedStatistics *statistics);
RT_API void RT_GetEncKeyMatchStatistics(ULONG *MatchCount,ULONG *MismatchCount);

RT_API bool RT_AP_GetIsAPMode(void);
RT_API void RT_AP_SwitchToAPMode(void);
RT_API void RT_AP_SwitchToStationMode(void);
RT_API bool RT_AP_GetStationList(char *buf,int bufsize,ULONG *pTotalSize,ULONG *pEntrySize,char **ppData,ULONGLONG *pCurrentTimeStame);
RT_API bool RT_AP_IsSupported(void);
// By David & Owen on 04/11/19 for Easy Configuration
RT_API int RT_AutoCfgScan(RT_BssidListEx *retbuf,int WaitTimeInMS, char *ssid);

RT_API void RT_ForceTxDataRate(UCHAR btDataRate);
RT_API bool RT_EnableWirelessMode(bool bEnableA, bool bEnableB, bool bEnableG, bool bEnableN_24G, bool bEnableN_5G);   

RT_API WIRELESS_MODE RT_GetBssWirelessMode();

RT_API void RT_ReNewIPAddress();

RT_API bool RT_GetStatusWEPKeyMisMatch(void);
RT_API bool RT_GetEncCAMStatus(void);
RT_API bool RT_ZeroConfigService(void);
RT_API void RT_PasswordHash(char *password, int passwordlength, unsigned char *ssid, int ssidlength, unsigned char *output);

RT_API char* RT_GetNicGuid(void);

RT_API bool RT_SetNicTcpipAddr(char* lpszAdapterName, int dhcp, char* mszIPAddress, char* mszNetMask, char* mszNetGate, char* mszNameServer);
RT_API bool RT_NicChangeState(char* lpszAdapterName, int state);
RT_API void RT_SendMagicPacket(UCHAR MacAddr[6]);

RT_API void RT_REMOVE_PSK_CONX(void);
RT_API void RT_ADD_PSK_CONX(char *Data, ULONG *DataLen);
RT_API void RT_ADD_PMK_CONX( UCHAR *Data, int DataLen );
RT_API void RT_SetMHSecurityInfo(int NetworkType, int AuthenticaionMode,int DataEncryptionMode);
RT_API bool RT_AP_SetPassphrase(char *szPassphrase, int nLength);
RT_API bool RT_Aegis_Event_Port_Changed(void);
RT_API void RT_SetSuspendState(bool flag);
RT_API void RT_SetWakeUpState(bool flag);

//--add by karl
RT_API int RT_RefreshAdapter();
//--

/* add  by CCW */
RT_API CertDesc * RT_GetUserCertList();
RT_API bool RT_Set_8021x_conf( char* field_data ,int field_index  );
RT_API bool RT_CertUrlWin32String( CertDesc * cert,char *certUrlBuf, int certUrlBufLen );
RT_API void RT_Set_8021x_tunnle( int EAPtype ,int TTLStunnel,int EAPtunnel  );
/* end by CCW */

//--add by karl (2005/12/23)
RT_API void RT_SetTurboMode(BYTE mode);
RT_API BYTE RT_GetTurboMode(void);
//--

RT_API bool RT_ReadEepromByte(ULONG Offset, UCHAR* ValueRead); // For 8187 only, 2006.02.14, by rcnjko.
RT_API bool RT_WriteEepromByte(ULONG Offset, UCHAR ValueToWrite); // For 8187 only, 2006.02.16, by rcnjko.

//--add by karl for ASUS -------------------
RT_API void RT_SetAUTOChannel(BYTE autoCH);
RT_API BYTE RT_GetAUTOChannel(void);
RT_API void RT_SetIsHidden_SSID(bool bIsHidden);
RT_API bool RT_GetIsHidden_SSID(void);
RT_API void RT_SetLOCKED_STA_ADDRESS(CHAR * pMacAddr,BYTE nAddr);
RT_API BYTE RT_GetLOCKED_STA_ADDRESS(CHAR * pMacAddr,BYTE nAddr);
RT_API int  RT_GetLiveTime(void);
RT_API void RT_SetDATA_RATE_STA(CHAR * pMacAddrDataRate,BYTE nAddr);
//------------------------------------------
RT_API void RT_Set_Filter_Type(int FType);   //MAC_FILTER_TYPE

//--add by karl for WDS AP MODE ------------
RT_API void RT_SetIsWDS_MODE(bool bIsWDS);
RT_API bool RT_GetIsWDS_MODE(void);
RT_API void RT_SetWDS_AP_LIST(CHAR * pMacAddr,BYTE nAddr);
RT_API BYTE RT_GetWDS_AP_LIST(CHAR * pMacAddr,BYTE nAddr);
//------------------------------------------

//--add By Karl on 06/7/6 for Simple Configuration   //Modify by Jacken 2006/11/07
RT_API BOOLEAN  RT_WS2_init(char *RTssid , char *RTMAC);
RT_API BOOLEAN  RT_WS2_stop(void);
//For set customized data added by Mars
RT_API void RT_SET_WPS_CUSTOMIZED_FLAG(bool Flag);
RT_API void RT_SET_WPS_MANUFACTURER(UCHAR manufacturer[64]);
RT_API void RT_SET_WPS_MODEL_NAME(UCHAR model_name[32]);
RT_API void RT_SET_WPS_MODEL_NUMBER(UCHAR model_number[32]);
RT_API void RT_SET_WPS_SERIAL_NUMBER(UCHAR serial_num[32]);
RT_API void RT_SET_WPS_DEVICE_NAME(UCHAR device_name[32]);
//end here
RT_API int  RT_SiteSurvey_WS2(RT_BssidListEx *retbuf,int WaitTimeInMS=0);
RT_API BOOLEAN  RT_GetPIN_WS2(char *PINPBC);
RT_API BOOLEAN  RT_WPS_External_Registrar(char PIN[8]);
RT_API BOOLEAN  RT_WPS_External_Registrar_Add_New_Device(char PIN[8]);
RT_API VOID  RT_WPS_Disable_WEP_Key_Parse(void);
RT_API BOOLEAN RT_WPS_External_Registrar_AP_PIN(char PIN[8]);
RT_API void  RT_WPS_Registrar_APConfig(SC_Connect APConfig);
RT_API bool RT_WSC_Connect(SC_Connect *SCConnect , int *WPS_status,char AssoAPName[32]);
RT_API int RT_WPSAPSurvey(WPS_BSSID WPS_BSSID_List[150]);
RT_API VOID  RT_GEN_PIN(char *PIN);
RT_API BOOLEAN  RT_WPS(char PIN[8]);
RT_API bool  RT_VERIFY_PIN(char *PIN);
//--add by hpfan on 2008/07/09 for customized timeout
RT_API void RT_SET_WPS_CUSTOMIZED_TIMEOUT_FLAG(bool flag);
//--add by hpfan on 2008/07/23 for finding if AP is Setup Locked 
RT_API int RT_WPSAPLockedSurvey(WPS_BSSID WPS_BSSID_List[150]);
//--add by hpfan on 2008/12/08 for finding if AP is in unconfig state
RT_API int RT_WPSAPUnconfiguredSurvey(WPS_BSSID WPS_BSSID_List[150]);
//------------------------------------------

//--add By Jacken on 06/09/06 for simple Config Debug
RT_API void RT_Debug_Methodflag(int flag);
RT_API BOOLEAN RT_Check_Session_Overlap(void);

//--add By Karl on 06/9/12 for Realtek Test Utility (RT_Throughput_Test)
RT_API bool RT_ReadRegData(UINT Offset, UINT RegDataWidth,ULONG* ValueRead);
RT_API bool RT_WriteRegData(UINT  Offset,UINT  RegDataWidth,ULONG ValueToWrite);
RT_API bool RT_GetSwAntennaDiversity();
RT_API bool RT_SetSwAntennaDiversity(bool bture);
RT_API void RT_SwAntenna(int nAntenna);
//--

//------------------------------------------
//--add By Karl on 07/1/12 (PSP XLink)
RT_API bool RT_GetIsXlink(void);
RT_API bool RT_SetIsXlink(bool bXlink);

//WMM QoS StaUapsd 
RT_API bool RT_Set_WMM_QoS_APSD(bool bQoS, int nStaUapsd);
RT_API bool RT_Get_WMM_QoS_APSD(bool * bQoS, int * nStaUapsd);
//------------------------------------------

//------------------------------------------
//--Aadd by Vincent on 07/06/01 (RTL8190 MIMO)
RT_API void RT_GetStatusSignalInfoMIMO(MIMO_RSSI *RSSI_MIMO, MIMO_SQ *SQ_MIMO);
//------------------------------------------

//------------------------------------------
//--Add by Jacken 2007/06/28
RT_API void RT_SetSBW(int SBW);
RT_API int RT_GetSBW();
//------------------------------------------

//------Add by Jacken 2007/07/03------------
RT_API BOOLEAN RT_DebugCmdSend(int DbgCmdLength,UCHAR *InData);
RT_API BOOLEAN RT_DebugCmdCheck(int *ready);
RT_API BOOLEAN RT_DebuggCmdReturn(UCHAR *OutData);
//------------------------------------------


//---add By CCW on 06/10/20 ROAM by Selsct BSSID
RT_API void RT_RoamToSelBSSID(char* ssid , int ssidlen , char* bssid );
//------------------------------------------

//RT_API void RT_GetDriverInfo(char *szGUID ,PDriverInfo DrvInfo); //Add By Karl


//--add By Karl for Mesh (2008/1/15)
RT_API int RT_GetMeshMode(); //return 0: none, MP: 1, MAP: 2, MPP: 3, MSTA: 4  ,Fail:-1 
RT_API bool RT_SetMeshMode(int nMode); //For Set Mesh Mode ,nMode= 0: none, MP: 1, MAP: 2, MPP: 3, MSTA: 4
RT_API bool RT_SetMeshID(char *szMeshID); //Max Length 32-byte
RT_API bool RT_GetMeshID(char *szMeshID);
RT_API void RT_SetFILTER_STA_ADDRESS(CHAR * pMacAddr,BYTE nAddr);    
RT_API BYTE RT_GetFILTER_STA_ADDRESS(CHAR * pMacAddr,BYTE nAddr);  
//--

//--For Hardward PBC , Add by Jacken 2008/03/12
RT_API bool RT_Get_HW_PBCStatus(void);
RT_API void RT_Set_HW_PBCStatus(void);

//--Debug Page Add by Karl
RT_API ULONG RT_GetInitial_11N_Txrate(void);
RT_API ULONG RT_Get_11N_Retry_Count(void);
//--

RT_API bool RT_Get_11N_LINK_CURRENT_BANDWIDTH(void);  //Add by Jacken 2008/09/01


///////////////////////////////////////////////////////////
// for CCX4
RT_API bool RT_CCX_InitCallback(RT_UI_HANDLER UiCallbackTable[UI_CALLBACK_COUNT]);//add by Karl for init CCX Callback.
//---add By CCW on 06/09/11 Config CCX for AEGIS
RT_API void RT_ConfigCCX(int CfgCCXFlag);
//------------------------------------------

//---add By CCW on 06/09/27 Config show Tx power
RT_API int RT_CCX_GetTpower();
RT_API bool RT_CCX_SetTpower( int Powerlevel); //dbm
//------------------------------------------

//For CCX show error message...
RT_API int RT_GetPort_Auth_State();

//---add By rcnjko on 07/07/11, for EAP-FAST related routines.
RT_API void RT_SetUserLogOff(bool bUserLogOff);
RT_API bool RT_GetUserLogOff();
RT_API bool RT_RefreshPacFileNameList(); 
//RT_API bool RT_GetPacFileNameList(CString **ppPacFileNameLists, int *pPacFileCount);
RT_API bool RT_GetszPacFileNameList(char **ppPacFileNameLists, int *pPacFileCount);
//RT_API bool RT_GetPacFileInfo(CString strPacFileName, PRT_PAC_FILE_INFO pPacFileInfo);
RT_API bool RT_SetPacFileIndex(int nPacFileIndex);
RT_API EAP_FAST_VER RT_GetEapFastVersion(bool bLoadFromRegistry);
RT_API bool RT_SetEapFastVersion(EAP_FAST_VER EapFastVer);

//---add by shienchang, 2007.07/07/23.
RT_API void RT_RegisterMessageHandler(HWND hMsgHandler);
//------------------------------------------

//--add by Karl on 2009/01/07
RT_API bool RT_GetLoginInfo(char *UserName ,char *Password ,char *Domain); 
RT_API bool RT_SetLoginInfo(char *pUserName ,char *pPASSWORD ,char *pDomain);
//--

RT_API int RT_Get_FIRMWARE_VERSION();   //Add by Karl 2009/01/15
RT_API bool RT_CCX_GetTxPowerRange( int *MindBm ,int *MaxdBm);//(dBm) ,Add by Karl 2009/01/15
RT_API bool RT_CCX_SetTxPowerPercentage( int mPower); //(1 ~ 100 ) ,Add By Karl 2009/1/20
RT_API int  RT_CCX_GetTxPowerPercentage(); //(Return 1 ~ 100) fail:-1 ,Add By Karl 2009/1/20

RT_API bool RT_Import_PacFile(char *fullPath);//Add by Karl 2009/01/19
RT_API bool RT_Delete_PacFile(char *PacFileName);//Add by Karl 2009/01/19
RT_API bool RT_Delete_PacFileByIndex(int nIndex);//Add by Karl 2009/01/21

RT_API void RT_CCX_ENABLE_RM(bool enable); //Add by Karl(2009/1/20)

RT_API void RT_GetStatusAegisInfo(char *APIver,char *PROTOCOLver);//Add by Vincent

//////////////////////////////
//Server Verify ,add by Karl
RT_API CertDesc * RT_Get_Cert_CA_List();//Add by Karl 2009/01/19
RT_API bool RT_Get_Cert_CA_URL( CertDesc * cert,char *certUrlBuf, int *certUrlBufLen );//Add by Karl 2009/01/19
RT_API bool RT_credServerVerify(RT_server ser);// set server Certificate ,Add By Karl 2009/1/20
RT_API bool RT_Get_credServerVerify(RT_server *pser);// Get server Certificate ,Add By Karl 2009/1/23
RT_API void RT_UIDlgView_Cert(CertDesc * cert);//A certificate was retrieved, display it ,Add By Karl 2009/1/23
///////////////////////////////

///////////////////////////////////////////////////////////
#endif

