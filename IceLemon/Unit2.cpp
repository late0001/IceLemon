#include "stdafx.h"
#include "xcommon.h"
#include "IceLemonDlg.h"

RunThread::RunThread(CIceLemonDlg *pDlg, bool CreateSuspended)
{
	pIceLemonDlg = pDlg;
}

void RunThread::SetContext(CIceLemonDlg *pDlg)
{
	pIceLemonDlg = pDlg;
}
RunThread::RunThread()
{
}

void RunThread::Creat_Test()
{

	// Create a Chariot test object
	CHR_test_new(&test);

	if (pIceLemonDlg->m_page_chariot.ckbLoadTestFile.GetCheck() )
	{
		CHR_test_load(test, pIceLemonDlg->ExtChariotTestFile.GetBuffer(pIceLemonDlg->ExtChariotTestFile.GetLength()),
			pIceLemonDlg->ExtChariotTestFile.GetLength());
	}

	// Create a Chariot run object
	CHR_test_get_runopts(test, &run);

	// Set realtime reporting
	CHR_runopts_set_reporting_type(run, CHR_TEST_REPORTING_REALTIME);

	// Set stop on initial fail
	CHR_runopts_set_stop_on_init_failure(run, true);

	// Set Chariot test end to be "Fixed duration"
	CHR_runopts_set_test_end(run, CHR_TEST_END_AFTER_FIXED_DURATION);

}
extern CIceLemonDlg *pIceLemonDlg;
//---------------------------------------------------------------------------
void ChariotCheck(CHR_HANDLE handle, CHR_API_RC code, CHR_STRING where)
{
   /*  Print information about an error and exit
    *  handle - what object had the error
    *  rc     - the Chariot API return code
    *  where  - what function call failed
    */

   char msg[CHR_MAX_RETURN_MSG];
   char errorInfo[CHR_MAX_ERROR_INFO];
   unsigned long msgLen, errorLen;
   int rc;
   CString DisplayWord;

   // for no handle error (Initialize,Get Chariot Version...)
   if (handle == (CHR_HANDLE) NULL)
    {
       if (code != CHR_OK)
        {
           pIceLemonDlg->m_page_main.m_redit.SetSel(-1,-1);
		   pIceLemonDlg->m_page_main.m_redit.ReplaceSel("****** Chariot: Error Message ******\r\n");
           DisplayWord.Format("%s failed: rc = %d \n", where, code);
           pIceLemonDlg->m_page_main.m_redit.ReplaceSel(DisplayWord);
        }
    }
   else
    {
       // Get the API message for this return code
       rc = CHR_api_get_return_msg(code, msg,
                                CHR_MAX_RETURN_MSG, &msgLen);

       if (rc != CHR_OK)
        {
           // Could not get the message: show why
		   pIceLemonDlg->m_page_main.m_redit.SetSel(-1,-1);
           pIceLemonDlg->m_page_main.m_redit.ReplaceSel("****** Chariot: Error Message ******\r\n");
           DisplayWord.Format("%s failed\nUnable to get message for return code %d, rc = %d\n", where, code, rc);
           pIceLemonDlg->m_page_main.m_redit.ReplaceSel(DisplayWord);
        }
       else
        {
           // Tell the user about the error

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
                // Get the extended error info
               rc = CHR_common_error_get_info(handle,
                                              CHR_DETAIL_LEVEL_ALL,
                                              errorInfo,
                                              CHR_MAX_ERROR_INFO,
                                              &errorLen);
			   pIceLemonDlg->m_page_main.m_redit.SetSel(-1,-1);
               pIceLemonDlg->m_page_main.m_redit.ReplaceSel("****** Chariot: Error Message ******\r\n");
               DisplayWord.Format("%s failed: rc = %d (%s)\n errorInfo: %s\n", where, code, msg, errorInfo);
               pIceLemonDlg->m_page_main.m_redit.ReplaceSel(DisplayWord);
            }
        }
    }
}
void RunThread::Creat_Pair(unsigned int n)
{
	int rc;
	CString DisplayWord;

	// Create Chariot pair1 object
	rc = CHR_pair_new(&pair[n]);
	ChariotCheck((CHR_HANDLE) NULL, rc, "pair_new");

	if ( rc != CHR_OK )
	{
		DisplayWord.Format("Creat_Pair: pair_new fail rc = %d\n", rc);
		pIceLemonDlg->m_page_main.m_redit.SetSel(-1, -1);
		pIceLemonDlg->m_page_main.m_redit.ReplaceSel(DisplayWord);
		pIceLemonDlg->m_page_main.m_redit.ReplaceSel("\r\n");
		IsError = true;
	}

	// Set protocol for pair1
	rc = CHR_pair_set_protocol(pair[n], ChariotParameter.protocol);

	// Set chariot script for pair1
    rc = CHR_pair_use_script_filename(pair[n], ChariotParameter.script, strlen(ChariotParameter.script));

	ChariotCheck(pair[n], rc, "pair_use_script_filename");

	if ( rc != CHR_OK)
	{
		DisplayWord.Format("Creat_Pair: pair_use_script_filename fail rc = %d\n", rc); 
		pIceLemonDlg->m_page_main.m_redit.ReplaceSel(DisplayWord);
		IsError = true;
	}

	//Set QOS name
	if (0)
	{
		rc = CHR_pair_set_qos_name(pair[n], ChariotParameter.Qos, strlen(ChariotParameter.Qos));
		ChariotCheck(pair[n], rc, "pair_use_Qos_name");

		if ( rc != CHR_OK) {
			DisplayWord.Format("Creat_Pair: pair_use_Qos_name fail rc = %d\n", rc); 	
			pIceLemonDlg->m_page_main.m_redit.ReplaceSel(DisplayWord);
			IsError = true;
		}
	}
}

bool RunThread::SetupChariot(int x, unsigned long TestDuration)
{
	unsigned long i, PairNum;
	//pIceLemonDlg->m_page_chariot.UpdateData(true);
	pIceLemonDlg->SendMessage(WM_UPDATEUSERDATA, true, 0);
	switch(x)
	{
	case 1:
		Creat_Test();

		// Set Chariot test duration
		CHR_runopts_set_test_duration(run, TestDuration);
		
		PairNum = pIceLemonDlg->m_page_chariot.E12PairCount;

		for (i=1; i<=PairNum; i++)
		{
			Creat_Pair(i);

			if (IsError == true)
				return false;

			// Set IP address for Endpoint1 to Endpoint2
			CHR_pair_set_e1_addr(pair[i], ChariotParameter.e1.GetBuffer(ChariotParameter.e1.GetLength()), ChariotParameter.e1.GetLength());

			CHR_pair_set_e2_addr(pair[i], ChariotParameter.e2.GetBuffer(ChariotParameter.e2.GetLength()), ChariotParameter.e2.GetLength());

			// Add the pair to the test
			CHR_test_add_pair(test, pair[i]);
		}

		break;
	case 2:
		Creat_Test();

		// Set Chariot test duration
		CHR_runopts_set_test_duration(run, TestDuration);

		PairNum = pIceLemonDlg->m_page_chariot.E21PairCount;

		for (i=1; i<=PairNum; i++)
		{
			Creat_Pair(i);

			if (IsError == true)
				return false;

			// Set IP address for Endpoint2 to Endpoint1
			CHR_pair_set_e1_addr(pair[i], ChariotParameter.e2.GetBuffer(ChariotParameter.e2.GetLength()), ChariotParameter.e2.GetLength());

			CHR_pair_set_e2_addr(pair[i], ChariotParameter.e1.GetBuffer(ChariotParameter.e1.GetLength()), ChariotParameter.e1.GetLength());
			// Add the pair to the test
			CHR_test_add_pair(test, pair[i]);
		}
		break;
	case 3:
		Creat_Test();


		// Set Chariot test duration
		CHR_runopts_set_test_duration(run, TestDuration);

		PairNum = pIceLemonDlg->m_page_chariot.E1221PairCount;

		for (i=1; i<=PairNum; i++)  //create pair for up-link or down-link
		{
			Creat_Pair(i);

			if (IsError == true)
				return false;

			CHR_pair_set_e1_addr(pair[i], ChariotParameter.e1.GetBuffer(ChariotParameter.e1.GetLength()), ChariotParameter.e1.GetLength());

			CHR_pair_set_e2_addr(pair[i], ChariotParameter.e2.GetBuffer(ChariotParameter.e2.GetLength()), ChariotParameter.e2.GetLength());

			// Add the pair1 to the test
			CHR_test_add_pair(test, pair[i]);
		}

		for (i=PairNum+1; i<=PairNum*2; i++)  //create pair for up-link or down-link
		{
			Creat_Pair(i);

			if (IsError == true)
				return false;

			CHR_pair_set_e1_addr(pair[i], ChariotParameter.e2.GetBuffer(ChariotParameter.e2.GetLength()), ChariotParameter.e2.GetLength());

			CHR_pair_set_e2_addr(pair[i], ChariotParameter.e1.GetBuffer(ChariotParameter.e1.GetLength()), ChariotParameter.e1.GetLength());

			// Add the pair1 to the test
			CHR_test_add_pair(test, pair[i]);
		}
		break;
	case 4:  //load external *.tst
		Creat_Test();

		// Set Chariot test duration
		CHR_runopts_set_test_duration(run, TestDuration);

		//Get how many pairs in the ext load *.tst
		pIceLemonDlg->ExtTstPairCount = 0;
		CHR_test_get_pair_count(test, &pIceLemonDlg->ExtTstPairCount);

		if (pIceLemonDlg->ExtTstPairCount == 0)
		{
			pIceLemonDlg->m_page_main.m_redit.SetSel(-1, -1);
			pIceLemonDlg->m_page_main.m_redit.ReplaceSel("Error!! No Paris found in the Ext-loaded .tst file\r\n");
			return false;
		}
		else
		{
			//get pair
			for (i=1; i<=pIceLemonDlg->ExtTstPairCount; i++)
			{
				CHR_test_get_pair(test, i-1, &pair[i]);

				if (i == 14)
					break;
			}
		}
		break;
	}  // End for "switch case"
	pIceLemonDlg->SendMessage(WM_UPDATEUSERDATA, false, 0);
	return true;
}

void RunThread::Save_ChariotTestFile(unsigned long direction, unsigned loopcount,
									 unsigned long j, unsigned long k)
{
	CString  HeadName = ChariotParameter.testfile,
		TypeName = "",
		FullName = "",
		DirectionName = "";
	char *ExtendName;
	int length, rc;

	//remove sub-filename .xxx to avoid error
	
	if (HeadName.Mid(HeadName.GetLength()-3, 1) == ".")
	{
		HeadName = HeadName.Mid(1, HeadName.GetLength()-4);
	}

	length = HeadName.GetLength();

	switch (direction)
	{
	case 1:
		DirectionName = "_Pair12";
		break;
	case 2:
		DirectionName = "_Pair21";
		break;
	case 3:
		DirectionName = "_Pair#";
		break;
	case 4:
		DirectionName = "_ExtPair";
		break;
	}
	

	
		if (loopcount >1)
		{
			DirectionName = DirectionName + "_Att%d_Round%d";
			ExtendName = DirectionName.GetBuffer(100);
			DirectionName.ReleaseBuffer();
			TypeName.Format(ExtendName, 0, k);
		}
		else
		{
			DirectionName = DirectionName + "_Att%d";
			ExtendName = DirectionName.GetBuffer(100);
			DirectionName.ReleaseBuffer();
			TypeName.Format(ExtendName, 0);
		}
	

	FullName = HeadName + TypeName;

	FullName = FullName + ".tst";

	pIceLemonDlg->m_page_chariot.lbl_saveName.SetWindowText(FullName);
	rc = CHR_test_set_filename(test, FullName.GetBuffer(FullName.GetLength()), FullName.GetLength());
	ChariotCheck(test, rc, "set_test_filename");
}

CString RunThread::GetChariotStatus(char x)
{
	switch ( (int) x)
	{
	case 0:
		return ("unitialized...");
	case 1:
		return ("initializing_1...");
	case 2:
		return ("initializing_2...");
	case 3:
		return ("initializing_3...");
	case 4:
		return ("unitialized...");
	case 5:
		return ("running...");
	case 6:
		return ("stopping...");
	case 7:
		return ("requested_stop...");
	case 8:
		return ("error...");
	case 9:
		return ("resolving_names...");
	case 10:
		return ("polling...");
	case 11:
		return ("finished...");
	case 12:
		return ("requesting_stop...");
	case 13:
		return ("finished_warnings...");
	}
	return("");
}
//---------------------------------------------------------------------------
bool RunThread::EndChariotTest()
{
	int rc;
	bool IsStopped = false;
	char ChariotStatus;
	CHR_COUNT timeout = 10;

	while (!IsStopped)
	{
		CHR_test_stop(test);
		//ChariotCheck(test, rc, "abandon_ test");
		//Form1->Memo->Lines->Add("Force Chariot stop...");

		rc = CHR_test_query_stop(test, timeout);
		pIceLemonDlg->m_page_main.m_redit.SetSel(-1, -1);
		
		if (rc == CHR_OK)
		{
			IsStopped = true;
		}
		else if (rc == CHR_TIMED_OUT)
		{
			// if time out, abandon test
			rc = CHR_pair_get_runStatus(pair[1], &ChariotStatus);
			pIceLemonDlg->PrintlnToMemo(GetChariotStatus(ChariotStatus));
			pIceLemonDlg->PrintlnToMemo("Chariot Time out...");

			rc = CHR_test_abandon(test);
		}
		else
		{
			pIceLemonDlg->m_page_main.m_redit.ReplaceSel("Test fail...\r\n");
			IsStopped = true;
			//Flag.Abort = true;
		}
	}
	return(IsStopped);
}

void RunThread::Set_Flag(struct SFlag flag)
{
	Flag = flag;
}

void RunThread::Set_Chariot(struct Chariot chariotP)
{
	ChariotParameter = chariotP;
}

void RunThread::GetThroughput(int AttIndex, int x, int h)
{
	CString DisplayWord;
	int rc, PairNum, k;
	unsigned long i;
	double avg;
	char tmp[128];
	//pIceLemonDlg->SendMessage(WM_UPDATEUSERDATA, true, 0);
	switch(x)
	{
	case 1:   //E1->E2
		PairNum = pIceLemonDlg->m_page_chariot.E12PairCount;
		avg1 = 0;

		for (k=1; k<=PairNum; k++)
		{
			avg = 0;
			rc = CHR_pair_results_get_average(pair[k], CHR_RESULTS_THROUGHPUT, &avg);

			if (rc != CHR_OK)
				avg = 0;

			avg1 = avg1 + avg;
		}

		if ( (avg1 < 0.0001) || (avg1 > 1000) )
		{
			avg1 = 0;
		}

		if ((h != 1) || (ChariotParameter.Round_Count != 2))
		{
			pIceLemonDlg->PrintlnToMemo("");
			DisplayWord.Format("Endpoint1 -> Endpoint2 throughput: %3.2f Mbps", avg1);
			pIceLemonDlg->PrintlnToMemo(DisplayWord);
		}

		// set flag for throughput > MaxThroughput
		if (avg1 > pIceLemonDlg->maxThroughput)
		{
			pIceLemonDlg->maxThroughput = avg1;
		}

		for (k=1; k<=PairNum; k++)
			CHR_pair_delete(pair[k]);

		CHR_test_delete(test);

		break;
	case 2:    //E2->E1
		PairNum = pIceLemonDlg->m_page_chariot.E21PairCount;

		avg2 = 0;

		for (k=1; k<=PairNum; k++)
		{
			avg = 0;
			rc = CHR_pair_results_get_average(pair[k], CHR_RESULTS_THROUGHPUT, &avg);

			if (rc != CHR_OK)
				avg = 0;

			avg2 = avg2 + avg;
		}

		if ( (avg2 < 0.0001) || (avg2 > 1000) )
		{
			avg2 = 0;
		}

		pIceLemonDlg->PrintlnToMemo("");
		DisplayWord.Format("Endpoint2 -> Endpoint1 throughput: %3.2f Mbps", avg2);
		pIceLemonDlg->PrintlnToMemo(DisplayWord);

		// set flag for throughput > MaxThroughput
		if (avg2 > pIceLemonDlg->maxThroughput)
		{
			pIceLemonDlg->maxThroughput = avg2;
		}

		for (k=1; k<=PairNum; k++)
			CHR_pair_delete(pair[k]);

		CHR_test_delete(test);

		break;
	case 3:  //E1<->E2
		PairNum = pIceLemonDlg->m_page_chariot.E1221PairCount;

		pIceLemonDlg->PrintlnToMemo("");
		pIceLemonDlg->PrintlnToMemo("--- Down&Up Link test ---");

		avg3 = 0;

		for (k=1; k<=PairNum; k++)
		{
			avg = 0;
			rc = CHR_pair_results_get_average(pair[k], CHR_RESULTS_THROUGHPUT, &avg);

			if (rc != CHR_OK)
				avg = 0;

			avg3 = avg3 + avg;
		}

		if ( (avg3 < 0.0001) || (avg3 > 1000) )
		{
			avg3 = 0;
		}

		pIceLemonDlg->PrintlnToMemo("");
		DisplayWord.Format("Endpoint1 -> Endpoint2 throughput: %3.2f Mbps", avg3);
		pIceLemonDlg->PrintlnToMemo(DisplayWord);

		avg4 = 0;

		for (k=PairNum+1; k<=PairNum*2; k++)
		{
			avg = 0;
			rc = CHR_pair_results_get_average(pair[k], CHR_RESULTS_THROUGHPUT, &avg);

			if (rc != CHR_OK)
				avg = 0;

			avg4 = avg4 + avg;
		}

		if ( (avg4 < 0.0001) || (avg4 > 1000) )
		{
			avg4 = 0;
		}

		pIceLemonDlg->PrintlnToMemo("");
		DisplayWord.Format("Endpoint2 -> Endpoint1 throughput: %3.2f Mbps", avg4);
		pIceLemonDlg->PrintlnToMemo(DisplayWord);

		pIceLemonDlg->PrintlnToMemo("");
		DisplayWord.Format("Sum of Bi-direction throughput: %3.2f Mbps", avg3+avg4);
		pIceLemonDlg->PrintlnToMemo(DisplayWord);

		if ((avg3 + avg4) > pIceLemonDlg->maxThroughput)
		{
			pIceLemonDlg->maxThroughput = avg3 + avg4;
		}

		for (k=1; k<=PairNum*2; k++)
			CHR_pair_delete(pair[k]);

		CHR_test_delete(test);

		break;

	case 4:   //Est Load Test File
		pIceLemonDlg->PrintlnToMemo("");
		pIceLemonDlg->PrintlnToMemo("--- Ext-Loaded Pairs Link test ---");

		avg4 = 0;
		avg5 = 0;  //DL
		avg6 = 0;  //UL

		for (i = 1; i<=pIceLemonDlg->ExtTstPairCount; i++)
		{
			avg = 0;
			rc = CHR_pair_results_get_average(pair[i], CHR_RESULTS_THROUGHPUT, &avg);

			if (rc != CHR_OK)
				avg = 0;

			if (i <= (pIceLemonDlg->ExtTstPairCount/2) )
				avg5 = avg5 + avg;
			else
				avg6 = avg6 + avg;

			avg4 = avg4 + avg;

			if (pIceLemonDlg->ExtTstPairCount == 1) //only one pair
			{
				avg5 = avg4;
				avg6 = avg4;
			}
		}

		if ( (avg4 < 0.0001) || (avg4 > 1000) )
		{
			avg4 = 0;
		}

		if ( (avg5 < 0.0001) || (avg5 > 1000) )
		{
			avg5 = 0;
		}

		if ( (avg6 < 0.0001) || (avg6 > 1000) )
		{
			avg6 = 0;
		}

		
		pIceLemonDlg->PrintlnToMemo("");
		DisplayWord.Format("Ext-Loaded Pairs throughput: %3.2f Mbps", avg4);
		pIceLemonDlg->PrintlnToMemo(DisplayWord);

		

		CHR_test_force_delete(test);
		//CHR_test_delete(test);

		break;

	}  // end for "switch(ChariotParameter.Test_Direction[i])"
	//pIceLemonDlg->SendMessage(WM_UPDATEUSERDATA, false, 0);
}

void RunThread::GetThroughput(int x, int h)
{
	CString DisplayWord;
	int rc, PairNum, k;
	unsigned long i;
	double avg;
	char tmp[128];
	//pIceLemonDlg->SendMessage(WM_UPDATEUSERDATA, true, 0);
	switch(x)
	{
	case 1:   //E1->E2
		PairNum = pIceLemonDlg->m_page_chariot.E12PairCount;
		avg1 = 0;

		for (k=1; k<=PairNum; k++)
		{
			avg = 0;
			rc = CHR_pair_results_get_average(pair[k], CHR_RESULTS_THROUGHPUT, &avg);

			if (rc != CHR_OK)
				avg = 0;

			avg1 = avg1 + avg;
		}

// 		if ( (avg1 < 0.0001) || (avg1 > 1000) )
// 		{
// 			avg1 = 0;
// 		}

		if ((h != 1) || (ChariotParameter.Round_Count != 2))
		{
			pIceLemonDlg->PrintlnToMemo("");
			DisplayWord.Format("Endpoint1 -> Endpoint2 throughput: %3.2f Mbps", avg1);
			pIceLemonDlg->PrintlnToMemo(DisplayWord);
		}

		// set flag for throughput > MaxThroughput
		if (avg1 > pIceLemonDlg->maxThroughput)
		{
			pIceLemonDlg->maxThroughput = avg1;
		}

// 		for (k=1; k<=PairNum; k++)
// 			CHR_pair_delete(pair[k]);
// 
// 		CHR_test_delete(test);
		th_curve.th_val = avg1;
		break;
	case 2:    //E2->E1
		PairNum = pIceLemonDlg->m_page_chariot.E21PairCount;

		avg2 = 0;

		for (k=1; k<=PairNum; k++)
		{
			avg = 0;
			rc = CHR_pair_results_get_average(pair[k], CHR_RESULTS_THROUGHPUT, &avg);

			if (rc != CHR_OK)
				avg = 0;

			avg2 = avg2 + avg;
		}


		pIceLemonDlg->PrintlnToMemo("");
		DisplayWord.Format("Endpoint2 -> Endpoint1 throughput: %3.2f Mbps", avg2);
		pIceLemonDlg->PrintlnToMemo(DisplayWord);

		// set flag for throughput > MaxThroughput
		if (avg2 > pIceLemonDlg->maxThroughput)
		{
			pIceLemonDlg->maxThroughput = avg2;
		}

// 		for (k=1; k<=PairNum; k++)
// 			CHR_pair_delete(pair[k]);
// 
// 		CHR_test_delete(test);
		th_curve.th_val = avg2;
		break;
	case 3:  //E1<->E2
		PairNum = pIceLemonDlg->m_page_chariot.E1221PairCount;

		pIceLemonDlg->PrintlnToMemo("");
		pIceLemonDlg->PrintlnToMemo("--- Down&Up Link test ---");

		avg3 = 0;

		for (k=1; k<=PairNum; k++)
		{
			avg = 0;
			rc = CHR_pair_results_get_average(pair[k], CHR_RESULTS_THROUGHPUT, &avg);

			if (rc != CHR_OK)
				avg = 0;

			avg3 = avg3 + avg;
		}



		pIceLemonDlg->PrintlnToMemo("");
		DisplayWord.Format("Endpoint1 -> Endpoint2 throughput: %3.2f Mbps", avg3);
		pIceLemonDlg->PrintlnToMemo(DisplayWord);

		avg4 = 0;

		for (k=PairNum+1; k<=PairNum*2; k++)
		{
			avg = 0;
			rc = CHR_pair_results_get_average(pair[k], CHR_RESULTS_THROUGHPUT, &avg);

			if (rc != CHR_OK)
				avg = 0;

			avg4 = avg4 + avg;
		}

		pIceLemonDlg->PrintlnToMemo("");
		DisplayWord.Format("Endpoint2 -> Endpoint1 throughput: %3.2f Mbps", avg4);
		pIceLemonDlg->PrintlnToMemo(DisplayWord);

		pIceLemonDlg->PrintlnToMemo("");
		DisplayWord.Format("Sum of Bi-direction throughput: %3.2f Mbps", avg3+avg4);
		pIceLemonDlg->PrintlnToMemo(DisplayWord);

		if ((avg3 + avg4) > pIceLemonDlg->maxThroughput)
		{
			pIceLemonDlg->maxThroughput = avg3 + avg4;
		}

// 		for (k=1; k<=PairNum*2; k++)
// 			CHR_pair_delete(pair[k]);
// 
// 		CHR_test_delete(test);
		th_curve.th_val = avg3+avg4;
		break;

	}  // end for "switch(ChariotParameter.Test_Direction[i])"
	//pIceLemonDlg->SendMessage(WM_UPDATEUSERDATA, false, 0);
}

void RunThread::GetThroughputMax(int x, int h)
{
	CString DisplayWord;
	int rc, PairNum, k;
	unsigned long i;
	double avg;
	char tmp[128];
	//pIceLemonDlg->SendMessage(WM_UPDATEUSERDATA, true, 0);
	switch(x)
	{
	case 1:   //E1->E2
		PairNum = pIceLemonDlg->m_page_chariot.E12PairCount;
		avg1 = 0;

		for (k=1; k<=PairNum; k++)
		{
			avg = 0;
			rc = CHR_pair_results_get_maximum(pair[k], CHR_RESULTS_THROUGHPUT, &avg);

			if (rc != CHR_OK){
				avg = 0;
				pIceLemonDlg->PrintlnToMemo("Error occur");
			}
			avg1 = avg1 + avg;
		}

		// 		if ( (avg1 < 0.0001) || (avg1 > 1000) )
		// 		{
		// 			avg1 = 0;
		// 		}

		if ((h != 1) || (ChariotParameter.Round_Count != 2))
		{
			pIceLemonDlg->PrintlnToMemo("");
			DisplayWord.Format("Endpoint1 -> Endpoint2 throughput: %3.2f Mbps", avg1);
			pIceLemonDlg->PrintlnToMemo(DisplayWord);
		}

		// set flag for throughput > MaxThroughput
		if (avg1 > pIceLemonDlg->maxThroughput)
		{
			pIceLemonDlg->maxThroughput = avg1;
		}

		// 		for (k=1; k<=PairNum; k++)
		// 			CHR_pair_delete(pair[k]);
		// 
		// 		CHR_test_delete(test);
		th_curve.th_val_max = avg1;
		break;
	case 2:    //E2->E1
		PairNum = pIceLemonDlg->m_page_chariot.E21PairCount;

		avg2 = 0;

		for (k=1; k<=PairNum; k++)
		{
			avg = 0;
			rc = CHR_pair_results_get_maximum(pair[k], CHR_RESULTS_THROUGHPUT, &avg);
			if (rc != CHR_OK)
				avg = 0;

			avg2 = avg2 + avg;
		}


		pIceLemonDlg->PrintlnToMemo("");
		DisplayWord.Format("Endpoint2 -> Endpoint1 throughput: %3.2f Mbps", avg2);
		pIceLemonDlg->PrintlnToMemo(DisplayWord);

		// set flag for throughput > MaxThroughput
		if (avg2 > pIceLemonDlg->maxThroughput)
		{
			pIceLemonDlg->maxThroughput = avg2;
		}

		// 		for (k=1; k<=PairNum; k++)
		// 			CHR_pair_delete(pair[k]);
		// 
		// 		CHR_test_delete(test);
		th_curve.th_val_max = avg2;
		break;
	case 3:  //E1<->E2
		PairNum = pIceLemonDlg->m_page_chariot.E1221PairCount;

		pIceLemonDlg->PrintlnToMemo("");
		pIceLemonDlg->PrintlnToMemo("--- Down&Up Link test ---");

		avg3 = 0;

		for (k=1; k<=PairNum; k++)
		{
			avg = 0;
			rc = CHR_pair_results_get_maximum(pair[k], CHR_RESULTS_THROUGHPUT, &avg);

			if (rc != CHR_OK)
				avg = 0;

			avg3 = avg3 + avg;
		}



		pIceLemonDlg->PrintlnToMemo("");
		DisplayWord.Format("Endpoint1 -> Endpoint2 throughput: %3.2f Mbps", avg3);
		pIceLemonDlg->PrintlnToMemo(DisplayWord);

		avg4 = 0;

		for (k=PairNum+1; k<=PairNum*2; k++)
		{
			avg = 0;
			rc = CHR_pair_results_get_maximum(pair[k], CHR_RESULTS_THROUGHPUT, &avg);
			if (rc != CHR_OK)
				avg = 0;

			avg4 = avg4 + avg;
		}

		pIceLemonDlg->PrintlnToMemo("");
		DisplayWord.Format("Endpoint2 -> Endpoint1 throughput: %3.2f Mbps", avg4);
		pIceLemonDlg->PrintlnToMemo(DisplayWord);

		pIceLemonDlg->PrintlnToMemo("");
		DisplayWord.Format("Sum of Bi-direction throughput: %3.2f Mbps", avg3+avg4);
		pIceLemonDlg->PrintlnToMemo(DisplayWord);

		if ((avg3 + avg4) > pIceLemonDlg->maxThroughput)
		{
			pIceLemonDlg->maxThroughput = avg3 + avg4;
		}

		// 		for (k=1; k<=PairNum*2; k++)
		// 			CHR_pair_delete(pair[k]);
		// 
		// 		CHR_test_delete(test);
		th_curve.th_val_max = avg3+avg4;
		break;

	}  // end for "switch(ChariotParameter.Test_Direction[i])"
	//pIceLemonDlg->SendMessage(WM_UPDATEUSERDATA, false, 0);
}

int RunThread::Run()
{
	char ChariotStatus;
	int FinishItem;
	unsigned long  TestDuration;    // used for tmp file format
	time_t tStart,tNow;
	int tCntSec = 0;
	int state = -1;
	bool OutLoop = false;
	bool status;
	unsigned long h, i, j;
	int k,LoopCount;
	int FinishTmpRound;
	CString DisplayWord;
	//while(!Terminate){
	if(Flag.Run)
	{
		do{
			switch(state){
			case -1:
				DisplayWord.Format("~~~~~~ Normal Mode Test ~~~~~");
				pIceLemonDlg->PrintlnToMemo(DisplayWord);
				pIceLemonDlg->FinishChariotRoundCount = 0; //total chariot round count (include pre-run chariot)
				state = 0;
				break;
			case 0:
				FinishItem = 0; // record total finish item in test rounds
				LoopCount = pIceLemonDlg->LoopCount; // set the test round
				j = 0;
				state = 1;
				break;
			case 1:
				k = 0;
				state = 2;
				break;
			case 2:
				//If finish k-loop??
				if (++k > LoopCount)
				{
					state = 90;
					break;
				}
				pIceLemonDlg->CurrentLoopCount = k; //to set what loop the program run now.
				pIceLemonDlg->m_page_main.SetTimer(1, 200, NULL);
				i = 0;
				state = 3;
				break;	
			case 3:
				//if i-loop finish??
				if (++i > ChariotParameter.Pair_Count)
				{
					state = 80;
					break;
				}

				if (Flag.Abort == true) // set for "attenuator setting value"
				{
					state = 95;  // user abort
					break;
				}
				h = 0;
				FinishTmpRound = 0;

				state = 4;
				break;	
			case 4:  //start chariot running (h-loop)
				if (++h > ChariotParameter.Round_Count)
				{
					state = 3;
					break;
				}

				if ((h == 1) && (ChariotParameter.Round_Count == 2))   //Pre-Run
				{
					TestDuration = pIceLemonDlg->PreRunDuration;
					pIceLemonDlg->m_page_main.m_redit.SetSel(-1,-1);
					pIceLemonDlg->m_page_main.m_redit.ReplaceSel("\r\n");
					pIceLemonDlg->m_page_main.m_redit.ReplaceSel("*************************\r\n");
					pIceLemonDlg->m_page_main.m_redit.ReplaceSel("Start Pre-Running...\r\n");
					IsPreRun = true;
				}
				else
				{
					TestDuration = ChariotParameter.testduration;
					IsPreRun = false;
				}

				status = SetupChariot(ChariotParameter.Test_Direction[i], TestDuration);

				DisplayWord.Format("i = %d, TestDuration = %d", i, TestDuration);
				//Form1->Memo->Lines->Add(DisplayWord);			

				if (status == false)
				{
					pIceLemonDlg->m_page_main.m_redit.ReplaceSel("Setup Chariot Fail!!\r\n");			
					CHR_test_force_delete(test);
					state = 99;   //error
					break;
				}
				if (ChariotParameter.testfile != "")
					Save_ChariotTestFile(ChariotParameter.Test_Direction[i], LoopCount, j, k);
				CHR_test_start(test);  //  Start Test!!
				time(&tStart);
				time(&tNow);
				tCntSec = 0;
				pIceLemonDlg->UpdateProgress(pIceLemonDlg->FinishChariotRoundCount);
				pIceLemonDlg->CorrectTimeRemain(h);
				pIceLemonDlg->m_page_main.RestartTimeRemain();
				state = 5;
				break;
			case 5://wait for pair test complete
				if(difftime(tNow, tStart) > TestDuration +1)//test finish
				{
					state = 6;
					break;
				}else {
					if(difftime(tNow,tStart) > tCntSec) {
						GetThroughput(ChariotParameter.Test_Direction[i],h);
						GetThroughputMax(ChariotParameter.Test_Direction[i],h);
						th_curve.cur_idx = tCntSec;
						pIceLemonDlg->SendMessage(WM_UPDATE_CHART,(WPARAM)&th_curve, NULL);
						tCntSec++;
					}
					pIceLemonDlg->m_page_main.m_redit.SetSel(-1,-1);
					if ( (Flag.Halt == true) || (Flag.Abort == true) ) // if press halt, stop the current pair test!!
					{
						pIceLemonDlg->m_page_main.FreezeTimeRemain();
						EndChariotTest();
						
						if (Flag.Halt == true)
						{
							pIceLemonDlg->m_page_main.m_redit.ReplaceSel("Wait for halt....");
							state = 18;
							break;
						}

						if (Flag.Abort == true)
						{
							pIceLemonDlg->m_page_main.m_redit.ReplaceSel("\r\n");
							pIceLemonDlg->m_page_main.m_redit.ReplaceSel("Wait for stop....");
							CHR_test_force_delete(test);
							state = 95;
							break;
						}

					}  // end for "if ( (Flag.Halt == true) || (Flag.Abort == true))"
					else {
						CHR_pair_get_runStatus(pair[1], &ChariotStatus);

						//error occurs at start, if error occurs within 1 second
						if ( ((int) ChariotStatus == 8) && (difftime(tNow,tStart) <= 1) )
						{
							pIceLemonDlg->m_page_main.m_redit.ReplaceSel("\n");
							pIceLemonDlg->m_page_main.m_redit.ReplaceSel("*******Charior error: IP address unreachable !!*******\n");
							pIceLemonDlg->m_page_main.m_redit.ReplaceSel("\n");
							pIceLemonDlg->m_page_main.m_redit.ReplaceSel("--> Please check IP address setting & AP/cable connection!!\n");
							IsError = true;
							//IsStopped = true;
							state = 99;
							CHR_test_force_delete(test);
							break;
						}

						Sleep(300);  //Bryant Add 2009/10
						time(&tNow);
						state = 5;
						break;
					}
				}
				break;
			case 6://h-loop  stop  process (Get card statistics, throughput)
				pIceLemonDlg->m_page_main.FreezeTimeRemain();

				CHR_pair_get_runStatus(pair[1], &ChariotStatus);

				// Deal with the case: "not finished or error while test duration time up"
				if ( ((int) ChariotStatus != 11) && ((int) ChariotStatus != 8) )
					EndChariotTest();

				if (IsPreRun == false)
				{
					if (ChariotParameter.testfile != "")
						CHR_test_save(test); //save Chariot test file *.tst
					GetThroughput(j, ChariotParameter.Test_Direction[i], h); //Get Throughput ane delete test object
					
				}
				else
				{
					CHR_test_force_delete(test);  //delete test if pre-run
					pIceLemonDlg->m_page_main.m_redit.ReplaceSel("Stop Pre-Running...\n");
					pIceLemonDlg->m_page_main.m_redit.ReplaceSel("*************************\n");
				}

				FinishTmpRound++;
				pIceLemonDlg->FinishChariotRoundCount++;
				state = 4;
				break;
			case 18:
				pIceLemonDlg->m_page_main.KillTimer(1);
				pIceLemonDlg->m_page_main.m_redit.ReplaceSel("\n");
				pIceLemonDlg->m_page_main.m_redit.ReplaceSel("Test Halt!!\n");
				i--;   // go back to the halt pair-test if continue to run

				while (1)  //wait for continue or abort
				{
					//  wait for "Halt off" or "Abort on"
					if  (Flag.Halt == false)
					{
						//ShowRunApperance();
						pIceLemonDlg->m_page_main.SetTimer(1, 200, NULL);
						pIceLemonDlg->m_page_main.m_redit.ReplaceSel("\n");
						pIceLemonDlg->m_page_main.m_redit.ReplaceSel("Test Continue....\n");

						pIceLemonDlg->FinishChariotRoundCount = pIceLemonDlg->FinishChariotRoundCount - FinishTmpRound; //correct progress

						pIceLemonDlg->m_page_main.RestartTimeRemain();
						CHR_test_force_delete(test);

						state = 3;
						break;
					}
					else if (Flag.Abort == true) //if abort in "halt"
					{
						EndChariotTest();
						CHR_test_force_delete(test);
						state = 95;
						break;
					}
				}
				break;
			case 80: //i-loop (chariot pair) finish process
				//SaveTmpData(saveformat, j);  //save tmp data

			

				FinishItem++;  // total finish item in all loopcount


				state = 2;  // to the next-k (loop)
				break;
			case 90:

				state = 101;  //to the next-j (attenuator Value)
				break;
			case 95://Abort process
				pIceLemonDlg->PrintlnToMemo("");
				pIceLemonDlg->PrintlnToMemo("<<<<<<<<<<<<<<<<< Finish (Test Abort!!) >>>>>>>>>>>>>>>>>");
				state = 101;
				break;
			case 99:
				Flag.Abort = false;   // used to distinct the stop reason of run thread
				pIceLemonDlg->PrintlnToMemo("");
				pIceLemonDlg->PrintlnToMemo("<<<<<<<<<<<<<<<< Finish (Error Occur!!) >>>>>>>>>>>>>>>>>");
				state = 101;
				break;
			case 101:
				Flag.Run = false; // to break "if (Flag_run)"

				OutLoop = true;
				break;
			}
		}while(!OutLoop);
	}

	pIceLemonDlg->PrintlnToMemo("");
	pIceLemonDlg->PrintlnToMemo("<<<<<<<<<<<<<<<< Finish (!!!!!!!) >>>>>>>>>>>>>>>>>");
	//CString s = "<<<<<<<<<<<<<<<< Finish (!!!!!!!) >>>>>>>>>>>>>>>>>";
	//pIceLemonDlg->SendMessage(WM_UPDATE_STEXT,(WPARAM)&s,0);
	//AfxMessageBox("Test Completed!");
	//}
	return 0;
}