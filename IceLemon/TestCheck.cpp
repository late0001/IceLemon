
// TestCheck.cpp : 实现文件
//

#include "stdafx.h"
#include "IceLemon.h"
#include "IceLemonDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
bool CIceLemonDlg::CheckCardSetting()
{
	return 1;
}

bool CIceLemonDlg::CheckEndpointIP()
{
	CString str;

	m_page_chariot.cbxEndpoint2.GetWindowText(str);
	ChariotParameter.e2 = str;
	if(ChariotParameter.use_case == 0){
		//m_page_chariot.cbxEndpoint1.GetLBText()
		m_page_chariot.cbxEndpoint1.GetWindowText(str);
		ChariotParameter.e1 = str;
	}
	if(ChariotParameter.use_case == 1){
		m_page_chariot.m_ip_ap1.GetWindowText(ChariotParameter.str_ap1_addr);
		m_page_chariot.m_ip_ap2.GetWindowText(ChariotParameter.str_ap2_addr);
		if (ChariotParameter.str_ap1_addr == "" || ChariotParameter.str_ap2_addr == "" )
		{
			sprintf_s(msg,"Endpoint must not be null!!\nPlease recheck!!");
			MessageBox(msg, "Error", MB_OK | MB_ICONERROR);
			DisplayPage(1);
			m_page_chariot.m_ip_ap1.SetFocus();
			//ClearCardInitialState(); //Stop Rtllib, Socket, unload 8187DLL

			PrintlnToMemo("<<<<<<<<<<<<<<<<< Please enter the IP address of the PC connected to AP1 through LAN port(Test Abort!!) >>>>>>>>>>>>>>>>>");

			return 0;
		}
		ChariotParameter.card1_index = m_page_chariot.m_cbx_card1.GetCurSel();
		//ChariotParameter.card2_index = m_page_chariot.m_cbx_card2.GetCurSel();
		if(ChariotParameter.card1_index <0 /*|| ChariotParameter.card2_index < 0 */){
			sprintf_s(msg,"card1 must not be null!!\nPlease recheck!!");
			MessageBox(msg, "Error", MB_OK | MB_ICONERROR);
			DisplayPage(1);
			m_page_chariot.m_cbx_card1.SetFocus();
		
			PrintlnToMemo("<<<<<<<<<<<<<<<<< please select card1  (Test Abort!!) >>>>>>>>>>>>>>>>>");

			return 0;
		}
		CString str_p1;
		m_page_chariot.m_cbx_profile1.GetWindowText(str_p1);
		if(str_p1 == ""){
			sprintf_s(msg,"profile1 must not be null!!\nPlease recheck!!");
			MessageBox(msg, "Error", MB_OK | MB_ICONERROR);
			DisplayPage(1);
			m_page_chariot.m_cbx_profile1.SetFocus();

			PrintlnToMemo("<<<<<<<<<<<<<<<<< please set profile1  (Test Abort!!) >>>>>>>>>>>>>>>>>");
			return 0;
		}
		strcpy_s(ChariotParameter.profile1 ,str_p1.GetBuffer(str_p1.GetLength()));
		CString str_p2;
		m_page_chariot.m_cbx_profile2.GetWindowText(str_p2);
		if(str_p2 == ""){
			sprintf_s(msg,"profile2 must not be null!!\nPlease recheck!!");
			MessageBox(msg, "Error", MB_OK | MB_ICONERROR);
			DisplayPage(1);
			m_page_chariot.m_cbx_profile2.SetFocus();

			PrintlnToMemo("<<<<<<<<<<<<<<<<< please set profile2  (Test Abort!!) >>>>>>>>>>>>>>>>>");
			return 0;
		}
		strcpy_s(ChariotParameter.profile2 ,str_p2.GetBuffer(str_p2.GetLength()));

	}
	if(ChariotParameter.use_case == 0 ){
		if (ChariotParameter.e1 == "" ||  ChariotParameter.e2 == "" )
		{
			sprintf_s(msg,"Endpoint must not be null!!\nPlease recheck!!");
			MessageBox(msg, "Error", MB_OK | MB_ICONERROR);
			DisplayPage(1);
			m_page_chariot.GetDlgItem(IDC_CBO_ENTPOINT1)->SetFocus();
			//ClearCardInitialState(); //Stop Rtllib, Socket, unload 8187DLL

			PrintlnToMemo("<<<<<<<<<<<<<<<<< please input endpoint ip (Test Abort!!) >>>>>>>>>>>>>>>>>");

			return 0;
		}
	}
	if(ChariotParameter.use_case == 2 ){
		if (ChariotParameter.e1 == "" )
		{
			sprintf_s(msg,"Endpoint must not be null!!\nPlease recheck!!");
			MessageBox(msg, "Error", MB_OK | MB_ICONERROR);
			DisplayPage(1);
			m_page_chariot.GetDlgItem(IDC_CBO_ENTPOINT1)->SetFocus();
			//ClearCardInitialState(); //Stop Rtllib, Socket, unload 8187DLL

			PrintlnToMemo("<<<<<<<<<<<<<<<<< please input endpoint ip (Test Abort!!) >>>>>>>>>>>>>>>>>");

			return 0;
		}
	}
	
	
	return 1;
}

bool CIceLemonDlg::CheckTestDuration()
{
	int cnt = 0;
	ChariotParameter.testduration = (m_page_chariot.m_edit_hour*3600 + m_page_chariot.m_edit_min*60 + m_page_chariot.m_edit_sec);
	PreRunDuration = m_page_chariot.m_edit_preRun;
	if (ChariotParameter.testduration == 0)
	{
		sprintf_s(msg,"Test duration must not be zero!!\nPlease recheck!!");
		MessageBox(msg, "Error", MB_OK | MB_ICONERROR);
		DisplayPage(1);
		m_page_chariot.GetDlgItem(IDC_EDT_SEC)->SetFocus();
		//ClearCardInitialState(); //Stop Rtllib, Socket, unload 8187DLL

		PrintlnToMemo("<<<<<<<<<<<<<<<<< Finish (Test Abort!!) >>>>>>>>>>>>>>>>>", 1);
		return 0;
	}
	ChariotParameter.loop_count = 1;
	if(ChariotParameter.use_case == 1 || ChariotParameter.use_case == 2){
		ChariotParameter.duration_single = (m_page_chariot.m_edit_hour_s*3600 + m_page_chariot.m_edit_min_s*60 + m_page_chariot.m_edit_sec_s);
		if(ChariotParameter.duration_single == 0){
			sprintf_s(msg,"Single execution time cannot be set to zero!!\nPlease recheck!!");
			MessageBox(msg, "Error", MB_OK | MB_ICONERROR);
			DisplayPage(1);
			m_page_chariot.GetDlgItem(IDC_EDT_SEC2)->SetFocus();
			PrintlnToMemo("<<<<<<<<<<<<<<<<< Finish (Test Abort!!) >>>>>>>>>>>>>>>>>", 1);
			return 0;
		}
		if(ChariotParameter.testduration < ChariotParameter.duration_single){
			sprintf_s(msg,"Error! total time less than single time!!\nPlease recheck!!");
			MessageBox(msg, "Error", MB_OK | MB_ICONERROR);
			DisplayPage(1);
			PrintlnToMemo("<<<<<<<<<<<<<<<<< Finish (Test Abort!!) >>>>>>>>>>>>>>>>>", 1);
			return 0;
		}
		cnt = ChariotParameter.testduration / (ChariotParameter.duration_single *ChariotParameter.Pair_Count);
		cnt = cnt%2 == 0 ? cnt: cnt-1;
		if(cnt == 0) {
			sprintf_s(msg,"Error! total time equal to single time!!\nPlease recheck!!");
			MessageBox(msg, "Error", MB_OK | MB_ICONERROR);
			DisplayPage(1);
			PrintlnToMemo("<<<<<<<<<<<<<<<<< Finish (Test Abort!!) >>>>>>>>>>>>>>>>>", 1);
			return 0;
		}
		ChariotParameter.loop_count = cnt;
		sprintf_s(msg, "ChariotParameter.testduration %d\n"
						"ChariotParameter.duration_single %d\n"
						"ChariotParameter.loop_count %d\n",
						ChariotParameter.testduration,
						ChariotParameter.duration_single,
						ChariotParameter.loop_count
						);
		MessageBox(msg,"Info", MB_OK | MB_ICONINFORMATION);
	}
	
	return 1;
}

bool CIceLemonDlg::CheckUseCase()
{
	ChariotParameter.use_case = m_page_chariot.m_cbx_use_case.GetCurSel();
	CString str;
	if (ChariotParameter.use_case == -1)
	{
		sprintf_s(msg,"The test case must be set!!\nPlease recheck!!");
		MessageBox(msg, "Error", MB_OK | MB_ICONERROR);
		DisplayPage(1);
		m_page_chariot.m_cbx_use_case.SetFocus();
		//ClearCardInitialState(); //Stop Rtllib, Socket, unload 8187DLL

		PrintlnToMemo("<<<<<<<<<<<<<<<<< Finish (Test Abort!!) >>>>>>>>>>>>>>>>>",1);
		return 0;
	}
	if (ChariotParameter.use_case == 1){
		ChariotParameter.card1_index = m_page_chariot.m_cbx_card1.GetCurSel();
		if(ChariotParameter.card1_index == -1) {
			sprintf_s(msg,"The card must be set!!\nPlease recheck!!");
			MessageBox(msg, "Error", MB_OK | MB_ICONERROR);	
			DisplayPage(1);
			m_page_chariot.m_cbx_card1.SetFocus();
			PrintlnToMemo("<<<<<<<<<<<<<<<<< Finish (Test Abort!!) >>>>>>>>>>>>>>>>>",1);
			return 0;
		}
	    m_page_chariot.m_cbx_profile1.GetWindowTextA(ChariotParameter.profile1,WLAN_MAX_NAME_LENGTH);
		str = ChariotParameter.profile1;
		if(str.Compare("")== 0){
			sprintf_s(msg,"The profile1 must be set!!\nPlease recheck!!");
			MessageBox(msg, "Error", MB_OK | MB_ICONERROR);	
			DisplayPage(1);
			m_page_chariot.m_cbx_profile1.SetFocus();
			PrintlnToMemo("<<<<<<<<<<<<<<<<< Finish (Test Abort!!) >>>>>>>>>>>>>>>>>",1);
			return 0;
		}
		m_page_chariot.m_cbx_profile2.GetWindowTextA(ChariotParameter.profile2,WLAN_MAX_NAME_LENGTH);
		str = ChariotParameter.profile2;
		if(str.Compare("") == 0){
			sprintf_s(msg,"The profile2 must be set!!\nPlease recheck!!");
			MessageBox(msg, "Error", MB_OK | MB_ICONERROR);	
			DisplayPage(1);
			m_page_chariot.m_cbx_profile2.SetFocus();
			PrintlnToMemo("<<<<<<<<<<<<<<<<< Finish (Test Abort!!) >>>>>>>>>>>>>>>>>",1);
			return 0;
		}
	}else if (ChariotParameter.use_case == 2){
		ChariotParameter.card1_index = m_page_chariot.m_cbx_card1.GetCurSel();
		if(ChariotParameter.card1_index == -1) {
			sprintf_s(msg,"The card 1 must be set!!\nPlease recheck!!");
			MessageBox(msg, "Error", MB_OK | MB_ICONERROR);	
			DisplayPage(1);
			m_page_chariot.m_cbx_card1.SetFocus();
			PrintlnToMemo("<<<<<<<<<<<<<<<<< Finish (Test Abort!!) >>>>>>>>>>>>>>>>>",1);
			return 0;
		}
		ChariotParameter.card2_index = m_page_chariot.m_cbx_card2.GetCurSel();
		if(ChariotParameter.card2_index == -1) {
			sprintf_s(msg,"The card 2 must be set!!\nPlease recheck!!");
			MessageBox(msg, "Error", MB_OK | MB_ICONERROR);	
			DisplayPage(1);
			m_page_chariot.m_cbx_card2.SetFocus();
			PrintlnToMemo("<<<<<<<<<<<<<<<<< Finish (Test Abort!!) >>>>>>>>>>>>>>>>>",1);
			return 0;
		}
		if(ChariotParameter.card1_index == ChariotParameter.card2_index){
			sprintf_s(msg,"Two cards cannot be the same!!\nPlease recheck!!");
			MessageBox(msg, "Error", MB_OK | MB_ICONERROR);	
			DisplayPage(1);
			m_page_chariot.m_cbx_card2.SetFocus();
			PrintlnToMemo("<<<<<<<<<<<<<<<<< Finish (Test Abort!!) >>>>>>>>>>>>>>>>>",1);
			return 0;
		}
		m_page_chariot.m_cbx_profile1.GetWindowTextA(ChariotParameter.profile1,WLAN_MAX_NAME_LENGTH);
		CString str = ChariotParameter.profile1;
		if(str.Compare("")== 0){
			sprintf_s(msg,"The profile1 must be set!!\nPlease recheck!!");
			MessageBox(msg, "Error", MB_OK | MB_ICONERROR);	
			DisplayPage(1);
			m_page_chariot.m_cbx_profile1.SetFocus();
			PrintlnToMemo("<<<<<<<<<<<<<<<<< Finish (Test Abort!!) >>>>>>>>>>>>>>>>>",1);
			return 0;
		}
		m_page_chariot.m_cbx_profile2.GetWindowTextA(ChariotParameter.profile2,WLAN_MAX_NAME_LENGTH);
		str = ChariotParameter.profile2;
		if(str.Compare("")== 0){
			sprintf_s(msg,"The profile1 must be set!!\nPlease recheck!!");
			MessageBox(msg, "Error", MB_OK | MB_ICONERROR);	
			DisplayPage(1);
			m_page_chariot.m_cbx_profile1.SetFocus();
			PrintlnToMemo("<<<<<<<<<<<<<<<<< Finish (Test Abort!!) >>>>>>>>>>>>>>>>>",1);
			return 0;
		}
	}
	return 1;
}

bool CIceLemonDlg::CheckTestDirection()
{
	unsigned long p;

	ChariotParameter.Pair_Count = 0;

	//if load external *.tst file
	if (m_page_chariot.ckbLoadTestFile.GetCheck() >0)
	{
		ChariotParameter.Pair_Count = 1;
		ChariotParameter.Test_Direction[1] = 4;
		saveFormat = 1;
		return 1;
	}

	if (m_page_chariot.ckbEndpoint12.GetCheck()  > 0)
	{
		ChariotParameter.Pair_Count++;
		ChariotParameter.Test_Direction[ChariotParameter.Pair_Count] = 1;
	}

	if (m_page_chariot.ckbEndpoint21.GetCheck() >0)
	{
		ChariotParameter.Pair_Count++;
		ChariotParameter.Test_Direction[ChariotParameter.Pair_Count] = 2;
	}

	if (m_page_chariot.ckb2way.GetCheck() >0)
	{
		ChariotParameter.TwoWay = true;
		ChariotParameter.Pair_Count++;
		ChariotParameter.Test_Direction[ChariotParameter.Pair_Count] = 3;
	}
	

	// decide the format of test result of tmpfile
	saveFormat = 0;    //save format: 0: E1->E2 + E2->E1, 1: E1->E2, 2: E2->E1
	//3: #E1->E2 + #E2->E1 + #sum
	//4: E1->E2 + #E1->E2 + #E2->E1 + #sum
	//5: E2->E1 + #E1->E2 + #E2->E1 + #sum
	//5: E1->E2 + E2->E1 + #E1->E2 + #E2->E1 + #sum

	for (p = 1 ; p <= ChariotParameter.Pair_Count; p++)
	{
		saveFormat = saveFormat + ChariotParameter.Test_Direction[p];
	}

	if  ( (ChariotParameter.Pair_Count == 2) && (saveFormat == 3) )
	{
		saveFormat = 0; // to distinct 1+2 & 3 only
	}

	return 1;
}

void CIceLemonDlg::CalculateLoopCount()
{
	//calculate the loop count by test type



		LoopCount = 1;
		LoopCount = 4;
	
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------- Check Chariot return code --------------------------------------
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void CIceLemonDlg::ChariotCheck(CHR_HANDLE handle, CHR_API_RC code, CHR_STRING where)
{
   /*  Print information about an error and exit
    *  handle - what object had the error
    *  rc     - the Chariot API return code
    *  where  - what function call failed
    */

   /*for no handle error (Initialize,Get Chariot Version...)   */
   if (handle == (CHR_HANDLE) NULL)
    {
       if (code !=CHR_OK)
        {
           sprintf_s(msg, "%s failed: rc = %d \n", where, code);
           MessageBox(msg, "Chariot: Error Message", MB_OK | MB_ICONERROR);
        }
    }
   else
    {
       /* Get the API message for this return code  */
       rc = CHR_api_get_return_msg(code, msg,
                                CHR_MAX_RETURN_MSG, &msgLen);

       if (rc !=CHR_OK)
        {
           /* Could not get the message: show why   */
           sprintf_s(msg, "%s failed\nUnable to get message for return code %d, rc = %d\n", where, code, rc);
           MessageBox(msg, "Chariot: Error Message", MB_OK | MB_ICONERROR);
        }
       else
        {
           /* Tell the user about the error */

           /*
            * See if there is extended error information available.
            * It's meaningful only after the CHR_OPERATION_FAILED
            * and CHR_OBJECT_INVALID error returns. After failed
            * "new" function calls, we don't have a handle so we
            * cannot check for extended error information.
            */

           if ((code == CHR_OPERATION_FAILED ||  code == CHR_OBJECT_INVALID)
                       &&  handle != (CHR_HANDLE) NULL)
            {
                /* Get the extended error info */
               rc = CHR_common_error_get_info(handle,
                                              CHR_DETAIL_LEVEL_ALL,
                                              errorInfo,
                                              CHR_MAX_ERROR_INFO,
                                              &errorLen);

               sprintf_s(msg, "%s failed: rc = %d (%s)\nerrorInfo:%s", where, code, msg, errorInfo);
               MessageBox(msg, "Chariot: Error Message", MB_OK | MB_ICONERROR);
            }
        }
    }
}

bool CIceLemonDlg::CheckChariotSetting()
{
	CString DisplayWord;

	if ( m_page_chariot.ckbSaveChariotTest.GetCheck() )
	{
		if (ChariotParameter.testfile == "")
		{
			sprintf_s(msg, "No Chariot test filename!! \n\n  Please assign it!!");
			MessageBox(msg, "Chariot Error", MB_OK | MB_ICONSTOP);

			DisplayPage(1);

			//btnSaveChariotTest->SetFocus();

			//ClearCardInitialState(); //Stop Rtllib, Socket, unload 8187DLL
			m_page_main.m_redit.SetSel(-1,-1);
			m_page_main.m_redit.ReplaceSel("\r\n");
			m_page_main.m_redit.ReplaceSel("<<<<<<<<<<<<<<<<< Finish (Test Abort!!) >>>>>>>>>>>>>>>>>\r\n");

			return 0;
		}
	}

	if (ChariotParameter.script == "") //no assign chariot script
	{
		sprintf_s(msg, "No Chariot Script!! \n\n  Please assign it!!");
		MessageBox(msg, "Chariot Error", MB_OK | MB_ICONSTOP);

		DisplayPage(1);

		//ClearCardInitialState(); //Stop Rtllib, Socket, unload 8187DLL

		m_page_main.m_redit.ReplaceSel("\r\n");
		m_page_main.m_redit.ReplaceSel("<<<<<<<<<<<<<<<<< Finish (Test Abort!!) >>>>>>>>>>>>>>>>>\r\n");
		return 0;
	}

	// Initialize the Chariot API
	rc = CHR_api_initialize( CHR_DETAIL_LEVEL_ALL, errorInfo,
		CHR_MAX_ERROR_INFO, &errorLen);

	ChariotCheck((CHR_HANDLE) NULL, rc, "Initialization");

	if (rc != CHR_OK)
	{
		m_page_main.m_redit.ReplaceSel("Chariot Initialize: fail !!\r\n");

		m_page_main.m_redit.ReplaceSel(errorInfo);
		m_page_main.m_redit.ReplaceSel("\r\n");

		//ClearCardInitialState(); //Stop Rtllib, Socket, unload 8187DLL

		m_page_main.m_redit.ReplaceSel("\r\n");
		m_page_main.m_redit.ReplaceSel("<<<<<<<<<<<<<<<<< Finish (Test Abort!!) >>>>>>>>>>>>>>>>>\r\n");

		return 0;
	}
	else
		m_page_main.m_redit.ReplaceSel("Chariot Initialize: ok !!\r\n");


	// Check Chariot Version
	rc = CHR_api_get_version(msg, CHR_MAX_RETURN_MSG, &msgLen);
	ChariotCheck((CHR_HANDLE) NULL, rc, "Get_Chariot_Version");


	DisplayWord.Format("The Chariot version: %s", msg);
	m_page_main.m_redit.ReplaceSel(DisplayWord);
	m_page_main.m_redit.ReplaceSel("\r\n");


	return 1;
}