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
	run_flag = 1;
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
          
		   pIceLemonDlg->PrintlnToMemo("****** Chariot: Error Message ******");
           DisplayWord.Format("%s failed: rc = %d", where, code);
           pIceLemonDlg->PrintlnToMemo(DisplayWord);
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
           pIceLemonDlg->PrintlnToMemo("****** Chariot: Error Message ******");
           DisplayWord.Format("%s failed\nUnable to get message for return code %d, rc = %d", where, code, rc);
           pIceLemonDlg->PrintlnToMemo(DisplayWord);
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
               pIceLemonDlg->PrintlnToMemo("****** Chariot: Error Message ******");
               DisplayWord.Format("%s failed: rc = %d (%s)\n errorInfo: %s", where, code, msg, errorInfo);
               pIceLemonDlg->PrintlnToMemo(DisplayWord);
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
		DisplayWord.Format("Creat_Pair: pair_new fail rc = %d", rc);
		pIceLemonDlg->PrintlnToMemo(DisplayWord);
		IsError = true;
	}

	// Set protocol for pair1
	rc = CHR_pair_set_protocol(pair[n], ChariotParameter.protocol);

	// Set chariot script for pair1
    rc = CHR_pair_use_script_filename(pair[n], ChariotParameter.script, strlen(ChariotParameter.script));

	ChariotCheck(pair[n], rc, "pair_use_script_filename");

	if ( rc != CHR_OK)
	{
		DisplayWord.Format("Creat_Pair: pair_use_script_filename fail rc = %d", rc); 
		pIceLemonDlg->PrintlnToMemo(DisplayWord);
		IsError = true;
	}

	//Set QOS name
	if (0)
	{
		rc = CHR_pair_set_qos_name(pair[n], ChariotParameter.Qos, strlen(ChariotParameter.Qos));
		ChariotCheck(pair[n], rc, "pair_use_Qos_name");

		if ( rc != CHR_OK) {
			DisplayWord.Format("Creat_Pair: pair_use_Qos_name fail rc = %d", rc); 	
			pIceLemonDlg->PrintlnToMemo(DisplayWord);
			IsError = true;
		}
	}
}

void RunThread::Creat_Pair2(Chariot2_Item *item, unsigned int n)
{
	int rc;
	CString DisplayWord;

	// Create Chariot pair1 object
	rc = CHR_pair_new(&pair[n]);
	ChariotCheck((CHR_HANDLE) NULL, rc, "pair_new");

	if ( rc != CHR_OK )
	{
		DisplayWord.Format("Creat_Pair2: pair_new fail rc = %d", rc);
		pIceLemonDlg->PrintlnToMemo(DisplayWord);
		IsError = true;
	}

	// Set protocol for pair1
	rc = CHR_pair_set_protocol(pair[n], item->protocol);

	// Set chariot script for pair1
	rc = CHR_pair_use_script_filename(pair[n], item->script, strlen(item->script));

	ChariotCheck(pair[n], rc, "pair_use_script_filename");

	if ( rc != CHR_OK)
	{
		DisplayWord.Format("Creat_Pair2: pair_use_script_filename fail rc = %d", rc); 
		pIceLemonDlg->PrintlnToMemo(DisplayWord);
		IsError = true;
	}

	//Set QOS name
	if (0)
	{
		rc = CHR_pair_set_qos_name(pair[n], ChariotParameter.Qos, strlen(ChariotParameter.Qos));
		ChariotCheck(pair[n], rc, "pair_use_Qos_name");

		if ( rc != CHR_OK) {
			DisplayWord.Format("Creat_Pair2: pair_use_Qos_name fail rc = %d", rc); 	
			pIceLemonDlg->PrintlnToMemo(DisplayWord);
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
			pIceLemonDlg->PrintlnToMemo("Error!! No Paris found in the Ext-loaded .tst file");
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

bool RunThread::SetupChariot2(Chariot2_Item *item)
{
	unsigned long i;
	int pair_num;
	//pIceLemonDlg->m_page_chariot.UpdateData(true);
	switch(item->TorR)
	{
	case 0:
	case 1:
		Creat_Test();

		// Set Chariot test duration
		CHR_runopts_set_test_duration(run, item->test_duration);

		for (i=1; i<=item->pairNum; i++)
		{
			Creat_Pair2(item, i);

			if (IsError == true)
				return false;

			// Set IP address for Endpoint1 to Endpoint2
			CHR_pair_set_e1_addr(pair[i], item->e1.GetBuffer(item->e1.GetLength()), item->e1.GetLength());

			CHR_pair_set_e2_addr(pair[i], item->e2.GetBuffer(item->e2.GetLength()), item->e2.GetLength());

			// Add the pair to the test
			CHR_test_add_pair(test, pair[i]);
		}
		break;
	case 2:
		Creat_Test();

		// Set Chariot test duration
		CHR_runopts_set_test_duration(run, item->test_duration);

		pair_num = item->pairNum;

		for (i=1; i<=pair_num; i++)  //create pair for up-link or down-link
		{
			Creat_Pair2(item, i);
			if (IsError == true)
				return false;
			CHR_pair_set_e1_addr(pair[i], item->e1.GetBuffer(item->e1.GetLength()), item->e1.GetLength());
			CHR_pair_set_e2_addr(pair[i], item->e2.GetBuffer(item->e2.GetLength()), item->e2.GetLength());
			// Add the pair1 to the test
			CHR_test_add_pair(test, pair[i]);
		}

		for (i=pair_num+1; i<=pair_num*2; i++)  //create pair for up-link or down-link
		{
			Creat_Pair2(item, i);
			if (IsError == true)
				return false;	
			CHR_pair_set_e1_addr(pair[i], item->e2.GetBuffer(item->e2.GetLength()), item->e2.GetLength());
			CHR_pair_set_e2_addr(pair[i], item->e1.GetBuffer(item->e1.GetLength()), item->e1.GetLength());
			// Add the pair1 to the test
			CHR_test_add_pair(test, pair[i]);
		}
		break;
	}
	return true;
}

void RunThread::Save_ChariotTestFile(unsigned long direction, unsigned long loopcount,
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
void RunThread::Save_ChariotTestFile2(Chariot2_Item *item, unsigned loopcount,
									 unsigned long j, unsigned long k)
{
	CString  HeadName = item->testfile,
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

	DirectionName = "_Pair12";



	if (loopcount >1)
	{
		DirectionName = DirectionName + "_Att%d_Round%d_item%d";
		ExtendName = DirectionName.GetBuffer(100);
		DirectionName.ReleaseBuffer();
		TypeName.Format(ExtendName, 0, k, item->id);
	}
	else
	{
		DirectionName = DirectionName + "_Att%d_item%d";
		ExtendName = DirectionName.GetBuffer(100);
		DirectionName.ReleaseBuffer();
		TypeName.Format(ExtendName, 0, item->id);
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
//	int retry_count =5;
	CHR_COUNT timeout = 10;

	while (!IsStopped)
	{
		CHR_test_stop(test);
		//ChariotCheck(test, rc, "abandon_ test");
		//Form1->Memo->Lines->Add("Force Chariot stop...");

		rc = CHR_test_query_stop(test, timeout);
		
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
			pIceLemonDlg->PrintlnToMemo("Test fail...\r\n");
/*
			if(retry_count-- > 0){
				continue;
			}*/
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

void RunThread::Set_Chariot2(STest test)
{
	sTest = test;
	//m_chariot2_List = clist;
}


void RunThread::GetThroughput(int AttIndex, int x, int h)
{
	CString DisplayWord;
	int rc, PairNum, k;
	unsigned long i;
	double avg;
	//char tmp[128];
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
		avg1 *=0.944;

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
		avg2*=0.944;
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
		avg3 *=0.944;
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
		avg4 *=0.944;
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

void RunThread::GetThroughput2(Chariot2_Item *item, int AttIndex, Chariot2_result *pResult, int needPrint)
{
	CString DisplayWord;
	int rc, pairNum, k;
	unsigned long i;
	double avg;
	//char tmp[128];
	//pIceLemonDlg->SendMessage(WM_UPDATEUSERDATA, true, 0);
	pairNum = item->pairNum;
	switch (item->TorR)
	{
	case 0:
	case 1:
		{

			avg1 = 0;

			for (k=1; k<=pairNum; k++)
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
			avg1 *=0.944;
			th_curve.th_val = avg1;
			pResult->throughput = avg1;
			if(needPrint){
				pIceLemonDlg->PrintlnToMemo("");
				DisplayWord.Format(" throughput: %3.2f Mbps", avg1);

				pIceLemonDlg->PrintlnToMemo(DisplayWord);
			}
			for (k=1; k<=pairNum; k++)
				CHR_pair_delete(pair[k]);

			CHR_test_delete(test);
			break;
		}
	case 2:  //E1<->E2
		{

			pIceLemonDlg->PrintlnToMemo("");
			pIceLemonDlg->PrintlnToMemo("--- Down&Up Link test ---");

			avg3 = 0;

			for (k=1; k<=pairNum; k++)
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
			avg3 *=0.944;
			pResult->throughput = avg3;
			pIceLemonDlg->PrintlnToMemo("");
			DisplayWord.Format("Endpoint1 -> Endpoint2 throughput: %3.2f Mbps", avg3);
			pIceLemonDlg->PrintlnToMemo(DisplayWord);
			avg4 = 0;

			for (k=pairNum+1; k<=pairNum*2; k++)
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
			avg4 *=0.944;
			pResult->throughput1 = avg4;
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

			for (k=1; k<=pairNum*2; k++)
				CHR_pair_delete(pair[k]);

			CHR_test_delete(test);

			break;
		}
	}
	//pIceLemonDlg->SendMessage(WM_UPDATEUSERDATA, false, 0);
}

void RunThread::SaveOneToDb(unsigned long saveFormat)
{
	//Test1_item item;
	//item.e1_ip = ChariotParameter.e1;
	//item.e2_ip = ChariotParameter.e2;
	//item.throughput = th_curve.th_val;
	//item.time = time(NULL);
	Test1_item *item = &t_item;
	CString sql;
	switch(saveFormat)
	{
	case 1:   //E1->E2
		sql.Format("INSERT INTO test1(SSID, endpoint1_ip,endpoint2_ip,[E1->E2], time1)"
			"VALUES ('%s', '%s','%s', %f, Format(Now(),'hh:mm:ss'))",
			item->SSID,
			item->e1_ip.GetBuffer(item->e1_ip.GetLength()), 
			item->e2_ip.GetBuffer(item->e2_ip.GetLength()),
			item->e1_e2
			);

		break;
	case 2:    //E2->E1
		sql.Format("INSERT INTO test1(SSID, endpoint1_ip,endpoint2_ip, [E2->E1], time1)"
			"VALUES ('%s', '%s','%s', %f, Format(Now(),'hh:mm:ss'))",
			item->SSID,
			item->e1_ip.GetBuffer(item->e1_ip.GetLength()), 
			item->e2_ip.GetBuffer(item->e2_ip.GetLength()),
			item->e2_e1
			);

		break;
	case 3:  //E1<->E2
		sql.Format("INSERT INTO test1(SSID, endpoint1_ip,endpoint2_ip, [#E1->E2], [#E2->E1], [#E1<->E2], time1)"
			"VALUES ('%s', '%s','%s', %f, %f, %f, Format(Now(),'hh:mm:ss'))",
			item->SSID,
			item->e1_ip.GetBuffer(item->e1_ip.GetLength()), 
			item->e2_ip.GetBuffer(item->e2_ip.GetLength()),
			item->e1s_e2, item->e2s_e1, item->two_way
			);

		break;

	case 4:   //Est Load Test File
		sql.Format("INSERT INTO test1(SSID, endpoint1_ip,endpoint2_ip,[E1->E2], [#E1->E2], [#E2->E1], [#E1<->E2], time1)"
			"VALUES ('%s', '%s','%s', %f, %f, %f, %f, Format(Now(),'hh:mm:ss'))",
			item->SSID,
			item->e1_ip.GetBuffer(item->e1_ip.GetLength()), 
			item->e2_ip.GetBuffer(item->e2_ip.GetLength()),
			item->e1_e2, item->e1s_e2, item->e2s_e1, item->two_way
			);

		break;
	case 5:   //Est Load Test File
		sql.Format("INSERT INTO test1(SSID, endpoint1_ip,endpoint2_ip,[E2->E1], [#E1->E2], [#E2->E1], [#E1<->E2], time1)"
			"VALUES ('%s', '%s','%s', %f, %f, %f, %f, Format(Now(),'hh:mm:ss'))",
			item->SSID,
			item->e1_ip.GetBuffer(item->e1_ip.GetLength()), 
			item->e2_ip.GetBuffer(item->e2_ip.GetLength()),
			item->e2_e1, item->e1s_e2, item->e2s_e1, item->two_way
			);

		break;
	case 6:
		sql.Format("INSERT INTO test1(SSID, endpoint1_ip,endpoint2_ip,[E1->E2], [E2->E1], [#E1->E2], [#E2->E1], [#E1<->E2], time1)"
			"VALUES ('%s', '%s','%s', %f, %f, %f, %f, %f, Format(Now(),'hh:mm:ss'))",
			item->SSID,
			item->e1_ip.GetBuffer(item->e1_ip.GetLength()), 
			item->e2_ip.GetBuffer(item->e2_ip.GetLength()),
			item->e1_e2, item->e2_e1, item->e1s_e2, item->e2s_e1, item->two_way
			);
		break;
	}  // end for "switch(ChariotParameter.Test_Direction[i])"

	pIceLemonDlg->InsertRecord(sql);
}

void RunThread::GetThroughput(int x, int h)
{
	CString DisplayWord;
	int rc, PairNum, k;
//	unsigned long i;
	double avg;
	//char tmp[128];
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

			if (rc != CHR_OK){
				avg = 0;
			}
			avg1 = avg1 + avg;
		}
		avg1 *=0.944;
// 		if ( (avg1 < 0.0001) || (avg1 > 1000) )
// 		{
// 			avg1 = 0;
// 		}

		if ((h != 1) || (ChariotParameter.Round_Count != 2))
		{
			//pIceLemonDlg->PrintlnToMemo("");
//			DisplayWord.Format("Endpoint1 -> Endpoint2 throughput: %3.2f Mbps", avg1);
//			pIceLemonDlg->PrintlnToMemo(DisplayWord,1);
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

		avg2 *=0.944;
//		DisplayWord.Format("Endpoint2 -> Endpoint1 throughput: %3.2f Mbps", avg2);
//		pIceLemonDlg->PrintlnToMemo(DisplayWord);

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

//		pIceLemonDlg->PrintlnToMemo("--- Down&Up Link test ---");

		avg3 = 0;

		for (k=1; k<=PairNum; k++)
		{
			avg = 0;
			rc = CHR_pair_results_get_average(pair[k], CHR_RESULTS_THROUGHPUT, &avg);

			if (rc != CHR_OK)
				avg = 0;

			avg3 = avg3 + avg;
		}


		avg3 *=0.944;
	//	pIceLemonDlg->PrintlnToMemo("");
	//	DisplayWord.Format("Endpoint1 -> Endpoint2 throughput: %3.2f Mbps", avg3);
	//	pIceLemonDlg->PrintlnToMemo(DisplayWord);

		avg4 = 0;

		for (k=PairNum+1; k<=PairNum*2; k++)
		{
			avg = 0;
			rc = CHR_pair_results_get_average(pair[k], CHR_RESULTS_THROUGHPUT, &avg);

			if (rc != CHR_OK)
				avg = 0;

			avg4 = avg4 + avg;
		}
		avg4 *=0.944;
// 		pIceLemonDlg->PrintlnToMemo("");
// 		DisplayWord.Format("Endpoint2 -> Endpoint1 throughput: %3.2f Mbps", avg4);
// 		pIceLemonDlg->PrintlnToMemo(DisplayWord);
// 
// 		pIceLemonDlg->PrintlnToMemo("");
// 		DisplayWord.Format("Sum of Bi-direction throughput: %3.2f Mbps", avg3+avg4);
// 		pIceLemonDlg->PrintlnToMemo(DisplayWord);

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
//	unsigned long i;
	double avg;
	char tmp[128];
	//pIceLemonDlg->SendMessage(WM_UPDATEUSERDATA, true, 0);
	switch(x)
	{
	case 1:   //E1->E2
		PairNum = pIceLemonDlg->m_page_chariot.E12PairCount;
		avg1 = 0;
		pIceLemonDlg->maxThroughput = avg1;
		for (k=1; k<=PairNum; k++)
		{
			avg = 0;
			rc = CHR_pair_results_get_maximum(pair[k], CHR_RESULTS_THROUGHPUT, &avg);

			if (rc != CHR_OK){
				avg = 0;
				pIceLemonDlg->PrintlnToMemo("Error occur");
			}
			//avg1 = avg1 + avg;
			if (avg > pIceLemonDlg->maxThroughput)
			{
				pIceLemonDlg->maxThroughput = avg;
			}
		}

		// 		if ( (avg1 < 0.0001) || (avg1 > 1000) )
		// 		{
		// 			avg1 = 0;
		// 		}

		if ((h != 1) || (ChariotParameter.Round_Count != 2))
		{
			pIceLemonDlg->PrintlnToMemo("");
			DisplayWord.Format("E1 -> E2 max throughput: %3.2f Mbps", pIceLemonDlg->maxThroughput);
			pIceLemonDlg->PrintlnToMemo(DisplayWord);
		}



		// 		for (k=1; k<=PairNum; k++)
		// 			CHR_pair_delete(pair[k]);
		// 
		// 		CHR_test_delete(test);
		th_curve.th_val_max = pIceLemonDlg->maxThroughput;
		break;
	case 2:    //E2->E1
		PairNum = pIceLemonDlg->m_page_chariot.E21PairCount;

		avg2 = 0;
		pIceLemonDlg->maxThroughput = avg2;
		for (k=1; k<=PairNum; k++)
		{
			avg = 0;
			rc = CHR_pair_results_get_maximum(pair[k], CHR_RESULTS_THROUGHPUT, &avg);
			if (rc != CHR_OK)
				avg = 0;

			//avg2 = avg2 + avg;
			if (avg > pIceLemonDlg->maxThroughput)
			{
				pIceLemonDlg->maxThroughput = avg;
			}
		}


		pIceLemonDlg->PrintlnToMemo("");
		DisplayWord.Format("E2 -> E1 max throughput: %3.2f Mbps", avg2);
		pIceLemonDlg->PrintlnToMemo(DisplayWord);

		// set flag for throughput > MaxThroughput


		// 		for (k=1; k<=PairNum; k++)
		// 			CHR_pair_delete(pair[k]);
		// 
		// 		CHR_test_delete(test);
		th_curve.th_val_max = pIceLemonDlg->maxThroughput;
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

			if (avg > avg3)
			{
				avg3 = avg;
			}
		}



		pIceLemonDlg->PrintlnToMemo("");
		DisplayWord.Format("E1 -> E2 max throughput: %3.2f Mbps", avg3);
		pIceLemonDlg->PrintlnToMemo(DisplayWord);

		avg4 = 0;

		for (k=PairNum+1; k<=PairNum*2; k++)
		{
			avg = 0;
			rc = CHR_pair_results_get_maximum(pair[k], CHR_RESULTS_THROUGHPUT, &avg);
			if (rc != CHR_OK)
				avg = 0;

			if (avg > avg4)
			{
				avg4 = avg;
			}
		}

		pIceLemonDlg->PrintlnToMemo("");
		DisplayWord.Format("E2 -> E1 max throughput: %3.2f Mbps", avg4);
		pIceLemonDlg->PrintlnToMemo(DisplayWord);

	//	pIceLemonDlg->PrintlnToMemo("");
	//	DisplayWord.Format("Sum of Bi-direction max throughput: %3.2f Mbps", avg3+avg4);
	//	pIceLemonDlg->PrintlnToMemo(DisplayWord);

		// 		for (k=1; k<=PairNum*2; k++)
		// 			CHR_pair_delete(pair[k]);
		// 
		// 		CHR_test_delete(test);
		th_curve.th_val_max =pIceLemonDlg->maxThroughput;
		break;

	}  // end for "switch(ChariotParameter.Test_Direction[i])"
	//pIceLemonDlg->SendMessage(WM_UPDATEUSERDATA, false, 0);
}

int RunThread::GetSaveDataFileName(unsigned long direction, unsigned loop_count,
				  unsigned long j, unsigned long k, CString &fileName)
{
	CString  HeadName = ChariotParameter.testfile,
		TypeName = "",
		FullName = "",
		DirectionName = "";
	char *ExtendName;
	int length;
	char pBuf[MAX_PATH];
	if(HeadName == ""){
		 //存放路径
		GetCurrentDirectory(MAX_PATH,pBuf); 
		HeadName.Format("%s\\test1",pBuf);
	}
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



	if (loop_count >1)
	{
		DirectionName = DirectionName + "_Att%d_Round%d";
		ExtendName = DirectionName.GetBuffer(100);
		DirectionName.ReleaseBuffer();
		if(k %2 == 1) 
			k=1;
		else
			k=2;
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

	FullName = FullName + ".txt";

	//pIceLemonDlg->m_page_chariot.lbl_saveName.SetWindowText(FullName);
	fileName = FullName;
	return 0;
}



int RunThread::SaveTPToFile()
{
	FILE *file = NULL;
	char file_name[255];
	char buf[255];
	int ret = 0;
	float throughput;
	time_t t;
	struct tm p ;
	char *wday[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
	strncpy_s(file_name,datFileName.GetBuffer(datFileName.GetLength()),datFileName.GetLength());
	ret = fopen_s(&file, file_name, "a");
	t = time(NULL);
	ret=gmtime_s(&p , &t);
	sprintf_s(buf, "%d年%02d月%02d日 %s %02d:%02d:%02d\n",
			(1900+p.tm_year), (1+p.tm_mon),p.tm_mday,
			wday[p.tm_wday],p.tm_hour+8>=24?p.tm_hour+8-24:p.tm_hour+8, p.tm_min, p.tm_sec
			);
	fwrite(buf, strlen(buf), 1, file);
	list<CV_META>::iterator plist; 
	for(plist = xl.begin(); plist != xl.end(); plist++) {  
		throughput = plist->th_val;
		sprintf_s(buf, "%.02f \0", throughput);
		fwrite(buf, strlen(buf)+1, 1, file);
	}
	fwrite("\n", 1, 1, file);
	fclose(file);
	return 0;
}

/*
* @param
*   buf  need a buffer to return values
*	fmt if 0,return date, otherwise return time
*/

int RunThread::GetDateTimeNow(char (&buf)[50], int fmt)
{
	//char *buf;
	int ret = 0;
	time_t t;
	struct tm p ;
	char *wday[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
	t = time(NULL);
	ret=gmtime_s(&p , &t);
	switch(fmt){
	case 0:
		sprintf_s(buf, "%d年%02d月%02d日 %s",
			(1900+p.tm_year), (1+p.tm_mon),p.tm_mday,
			wday[p.tm_wday]
			);
		break;
	case 1:
		sprintf_s(buf, "%02d:%02d:%02d", p.tm_hour+8>=24? p.tm_hour+8-24: p.tm_hour+8, p.tm_min, p.tm_sec);
		break;
	case 3:
		sprintf_s(buf, "%d%02d%02d%02d%02d%02d",(1900+p.tm_year), (1+p.tm_mon),p.tm_mday, p.tm_hour+8>=24? p.tm_hour+8-24: p.tm_hour+8, p.tm_min, p.tm_sec);
		break;
	}

	return 0;
}

int RunThread::GetDateTime(time_t time, char (&buf)[50], int fmt)
{
	//char *buf;
	int ret = 0;
	//time_t t;
	struct tm p;
	char *wday[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
	//t = time(NULL);
	ret=gmtime_s(&p , &time);
	switch(fmt){
	case 0:
		sprintf_s(buf, "%d年%02d月%02d日 %s",
			(1900+p.tm_year), (1+p.tm_mon),p.tm_mday,
			wday[p.tm_wday]
		);
		break;
	case 1:
		sprintf_s(buf, "%02d:%02d:%02d", p.tm_hour+8>=24? p.tm_hour+8-24: p.tm_hour+8, p.tm_min, p.tm_sec);
		break;
	case 2:
	default:
		sprintf_s(buf, "%04d/%02d/%02d %02d:%02d:%02d", 
			(1900+p.tm_year), (1+p.tm_mon),p.tm_mday, 
			p.tm_hour+8>=24? p.tm_hour+8-24: p.tm_hour+8, p.tm_min, p.tm_sec);
		break;
	}

	return 0;
}

void RunThread::TouchFile(int k)
{
	char fileName[255]={0};
	FILE *pFile;
	int ret;
	if(k>2) return; // have no need create new file
	strncpy_s(fileName, datFileName.GetBuffer(datFileName.GetLength()),datFileName.GetLength());
	ret = fopen_s( &pFile, fileName, "w");
	fclose(pFile);
}

//---------------------------------------------------------------------------
void RunThread::SetDataTmpFile(unsigned long jj, unsigned long k)
{
   /* Define tmp file pointer for save data
    * Name Rule: FullName = HeadName + TypeName (if required) + TailName
    * General Filename: C:/DataTmp_Typexx.txt
    * HeadName-> "DataTmp" ;
    * TypeName->  "_Typexx", Type means Round or Rate or Angle, xx means type value;
    * TailName->  ".txt",
    * Example1: C:\DataTmp_Round2.txt   --> Round2 test data
    * Example2: C:\DataTmp_RateOFDM 12M.txt  --> 54Mbps test data
    * Example3: C:\DataTmp_Angle180.txt --> 180 degree test data
    * Example4: C:\DataTmp_Parameter1.txt --> Parameter1 test data
    * Example4: C:\DataTmp_Temperature30.txt --> tempaerature test data
    */

   /* Also Define Chariot test file pointer
    * Name Rule: FullName = HeadName + TypeName (if required)
    * HeadName-> ChariotParameter.testfile (String format-> path/****.tst)
    * TypeName-> "_Type1xx_Type2yy_Type3zz"
    * Type1-> Pair  xx: 12 or 21 or #(2way)
    * Type2-> Att   yy: 0~119
    * Type3-> Round or Rate or Angle  zz: 1~3 or 54~1 or 15~360 or -10~+80
    * Example1: C:\Program Files\NetIQ\Chariot\Tests\****_Pair12_Att25_Rate36.tst
    */

   CString HeadName = "DataTmp",
          TypeName,
          TailName = ".txt",
          DisplayWord;
   int LoopCount, LoopType, ks;
   char *DataTmpFilename;
   FILE *tmpFile;
   errno_t err;
   LoopCount = pIceLemonDlg->LoopCount;

 
       LoopType = 3;

       // build the tmp data filename for iteration test
       if (LoopCount == 1)  // if only one iteration, no type-name required!!
        {
           TypeName = "";
        }
       else
        {

           pIceLemonDlg->PrintlnToMemo(DisplayWord);
           DisplayWord.Format("<<< Iteraion: %d >>>", k);
           pIceLemonDlg->PrintlnToMemo(DisplayWord);
		   //if(ChariotParameter.use_case == 1){
#if 0
		   if(k %2 == 1) 
			    ks =1;
		   else
				ks =2;
#else
		   ks = 1;
#endif
		   //}
           TypeName.Format( "_Round%d", ks);
		 
        }


   //SetCurrentDir(Form1->WorkDictionary);
   dataFullName = pIceLemonDlg->workDirectory + "\\test_result\\" + HeadName + TypeName + TailName;
   DataTmpFilename = dataFullName.GetBuffer(dataFullName.GetLength());
   if(k > 1) return ; //if k>2 have no need to create file
   // Delete the existing data in tmp file & new a data tmp file
   if (jj == 1)       //create new file if the first att value
    {
      err = fopen_s(&tmpFile, DataTmpFilename,"w+t");

      fclose(tmpFile);

      //Add DataTmpFile to DataTmpFileList

      sprintf_s(DataTmpFileList, "%s\\test_result\\DataTmpFileList.txt", pIceLemonDlg->workDirectory);
       err = fopen_s(&tmpFile, DataTmpFileList,"a+t");
      fprintf(tmpFile,"%s\n",dataFullName);
      fclose(tmpFile);
    }

}

void RunThread::SetDataTmpFile2(Chariot2_result *pCRInfo, unsigned long jj, unsigned long k, int t)
{
   /* Define tmp file pointer for save data
    * Name Rule: FullName = HeadName + TypeName (if required) + TailName
    * General Filename: C:/DataTmp_Typexx.txt
    * HeadName-> "DataTmp" ;
    * TypeName->  "_Typexx", Type means Round or Rate or Angle, xx means type value;
    * TailName->  ".txt",
    * Example1: C:\DataTmp_Round2.txt   --> Round2 test data
    * Example2: C:\DataTmp_RateOFDM 12M.txt  --> 54Mbps test data
    * Example3: C:\DataTmp_Angle180.txt --> 180 degree test data
    * Example4: C:\DataTmp_Parameter1.txt --> Parameter1 test data
    * Example4: C:\DataTmp_Temperature30.txt --> tempaerature test data
    */

   /* Also Define Chariot test file pointer
    * Name Rule: FullName = HeadName + TypeName (if required)
    * HeadName-> ChariotParameter.testfile (String format-> path/****.tst)
    * TypeName-> "_Type1xx_Type2yy_Type3zz"
    * Type1-> Pair  xx: 12 or 21 or #(2way)
    * Type2-> Att   yy: 0~119
    * Type3-> Round or Rate or Angle  zz: 1~3 or 54~1 or 15~360 or -10~+80
    * Example1: C:\Program Files\NetIQ\Chariot\Tests\****_Pair12_Att25_Rate36.tst
    */

   CString HeadName = "DataTmp",
          TypeName,
          TailName = ".txt",
          DisplayWord;
   int LoopCount, LoopType, ks;
   char *DataTmpFilename;
   char *DbFormatFile;
   char datetime[50] = {0};
   FILE *tmpFile;
   errno_t err;
   LoopCount = pIceLemonDlg->LoopCount;

 
       LoopType = 3;
	  if(k > 1|| t > 1) return ; //if k>2 have no need to create file
       // build the tmp data filename for iteration test
       if (LoopCount == 1)  // if only one iteration, no type-name required!!
        {
           TypeName = "";
        }
       else
        {

           pIceLemonDlg->PrintlnToMemo(DisplayWord);
           DisplayWord.Format("<<< Iteraion: %d >>>", k);
           pIceLemonDlg->PrintlnToMemo(DisplayWord);
		   //if(ChariotParameter.use_case == 1){
#if 0
		   if(k %2 == 1) 
			    ks =1;
		   else
				ks =2;
#else
		   ks = 1;
#endif
		   //}
           TypeName.Format( "_Round%d", ks);
		 
        }
	
	GetDateTimeNow(datetime,3);
   //SetCurrentDir(Form1->WorkDictionary);
   dataFullName = pIceLemonDlg->workDirectory + "\\test_result\\" + HeadName + TypeName + datetime + TailName;
   DataTmpFilename = dataFullName.GetBuffer(dataFullName.GetLength());
   svtodbName = pIceLemonDlg->workDirectory + "\\test_result\\DbFomat" +  + TypeName + datetime + TailName;
   DbFormatFile = svtodbName.GetBuffer(svtodbName.GetLength());
  strcpy_s(pCRInfo->testLog ,dataFullName.GetBuffer(dataFullName.GetLength()));
   // Delete the existing data in tmp file & new a data tmp file
   if (jj == 1)       //create new file if the first att value
    {
      err = fopen_s(&tmpFile, DataTmpFilename,"w+t"); 
      fclose(tmpFile);

	  err = fopen_s(&tmpFile, DbFormatFile,"w+t");
	  fclose(tmpFile);
      //Add DataTmpFile to DataTmpFileList

      sprintf_s(DataTmpFileList, "%s\\test_result\\DataTmpFileList.txt", pIceLemonDlg->workDirectory);
       err = fopen_s(&tmpFile, DataTmpFileList,"a+t");
      fprintf(tmpFile,"%s\n",dataFullName);
      fclose(tmpFile);
    }

}

//---------------------------------------------------------------------------
void RunThread::SaveTmpData(unsigned long saveFormat, unsigned long j, int k)
{
	FILE *TmpFile;
	char *DataTmpFilename;
	CString xValName;
	errno_t err;
	char buf[50]={0};
	DataTmpFilename = dataFullName.GetBuffer(dataFullName.GetLength());
	//Form1->Label1->Caption = DataFullName;
	// Save test result to tmp file (the current attenuator value)

	//if ( (Form1->ckbRotatorEnable->Checked == true) && (Form1->ckbEnableFieldTryMode->Checked == true) )
	//	xValName = "Ang    Ofs    Ang    ";
	//else
		xValName = "Att     ";

	err = fopen_s(&TmpFile, DataTmpFilename,"a+t"); // open temp file for append data

	switch (saveFormat)
	{
	case 0:
		if (j==1 && k==1)   // print header file at the first attenuator value
		{
			GetDateTimeNow(buf, 0);
			fprintf(TmpFile, "Date: %s\n",buf);

			fprintf(TmpFile,"Throughput(unit: Mbps)\n");
			fprintf(TmpFile,"%s    %-20s    E1->E2    E2->E1\n", xValName, "SSID");
			fprintf(TmpFile,"===   %-20s   =======   =======\n", "=======");
		}
		GetDateTimeNow(buf, 1);
		fprintf(TmpFile,"%3d  %-20s  %9.2f %9.2f %s\n", 0, t_item.SSID,
			avg1, avg2, buf);
		break;
	case 1:
		if (j==1 && k==1)
		{
			GetDateTimeNow(buf, 0);
			fprintf(TmpFile, "Date: %s\n",buf);
		
			fprintf(TmpFile, "Throughput(unit: Mbps)\n");

//			if (Form1->ckbLoadTestFile->Checked == true)
//			{               
//				fprintf(TmpFile,"%sExt_ALL    Ext_DLP    Ext_ULP\n", xValName);
//				fprintf(TmpFile, "===    ===    ===   ========   ========   ========\n");
//			}
//			else
//			{
				fprintf(TmpFile, "Att  %-20s     E1->E2     k      time\n", "SSID");
				fprintf(TmpFile, "===  %-20s    ========	  =====	  =====\n", "=======");
//			}
		}

//		if (Form1->ckbLoadTestFile->Checked == true)
//			fprintf(TmpFile,"%3d %6d %6d %9.2f %9.2f %9.2f\n", AttenuatorParameter.Attenuator_Value[j],
//			AttenuatorParameter.Ext_Attenuation,
//			AttenuatorParameter.Attenuator_Value[j]+AttenuatorParameter.Ext_Attenuation,
//			avg4, avg5, avg6);
//		else
			GetDateTimeNow(buf, 1);
			fprintf(TmpFile,"%d %-20s %9.2f  %9d       %-15s\n", 0, t_item.SSID,
			avg1, k, buf);

		break;
	case 2:
		if (j==1 && k==1)
		{
			GetDateTimeNow(buf, 0);
			fprintf(TmpFile, "Date: %s\n",buf);
	
			fprintf(TmpFile,"Throughput(unit: Mbps)\n");
			fprintf(TmpFile,"Att   %-20s   E2->E1   time\n", "SSID");
			fprintf(TmpFile,"===   %-20s   ======   ======\n","======");
		}
		GetDateTimeNow(buf, 1);
		fprintf(TmpFile,"%3d  %-20s %9.2f %-15s\n", 0, t_item.SSID,
			avg2, buf);
		break;
	case 3:
		if (j==1 && k==1)
		{
			GetDateTimeNow(buf, 0);
			fprintf(TmpFile, "Date: %s\n",buf);
		
			fprintf(TmpFile,"Throughput(unit: Mbps)\n");
			fprintf(TmpFile,"Att  %-20s    #E1->E2   #E2->E1   #E2<->E1  time\n", "SSID");
			fprintf(TmpFile,"===  %-20s    =======   =======   =======   ======\n", "=======");
		}
		GetDateTimeNow(buf, 1);
		fprintf(TmpFile,"%3d  %-20s %9.2f %9.2f %9.2f    %-15s\n",0, t_item.SSID,
			avg3, avg4, avg3+avg4, buf);
		break;
	case 4:
		if (j==1 && k==1)
		{
			GetDateTimeNow(buf, 0);
			fprintf(TmpFile, "Date: %s\n",buf);
			
			fprintf(TmpFile,"Throughput(unit: Mbps)\n");
			fprintf(TmpFile,"Att   %-20s    E1->E2   #E1->E2   #E2->E1   #E1<->E2  time\n", "SSID");
			fprintf(TmpFile,"===   %-20s    ======   =======   =======   =======   ======\n", "=======");
		}
		GetDateTimeNow(buf, 1);
		fprintf(TmpFile,"%3d  %-20s %9.2f %9.2f %9.2f %9.2f %15s\n",0, t_item.SSID,
			avg1, avg3, avg4, avg3+avg4, buf);
		break;
	case 5:
		if (j==1 && k==1)
		{
			GetDateTimeNow(buf, 0);
			fprintf(TmpFile, "Date: %s\n",buf);
		
			fprintf(TmpFile,"Throughput(unit: Mbps)\n");
			fprintf(TmpFile,"Att  %-20s    E2->E1   #E1->E2   #E2->E1   #E1<->E2  time\n", "SSID");
			fprintf(TmpFile,"===  %-20s   =======   =======   =======   =======   =======\n", "======");
		}
		GetDateTimeNow(buf, 1);
		fprintf(TmpFile,"%3d  %-20s %9.2f %9.2f %9.2f %9.2f %-15s\n", 0, t_item.SSID,
			avg2, avg3, avg4, avg3+avg4, buf);
		break;
	case 6:
		if (j==1 && k==1)
		{
			GetDateTimeNow(buf, 0);
			fprintf(TmpFile, "Date: %s\n",buf);
		
			fprintf(TmpFile,"Throughput(unit: Mbps)\n");
			fprintf(TmpFile,"Att   %-20s   E1->E2    E2->E1    #E1->E2   #E2->E1   #E1<->E2	  time\n", "SSID");
			fprintf(TmpFile,"===   %-20s   =======   =======   =======   =======   ========	  =====\n", "======");
		}
		GetDateTimeNow(buf, 1);
		fprintf(TmpFile,"%3d  %-20s %9.2f %9.2f %9.2f %9.2f %9.2f       %-15s\n", 0, t_item.SSID,
			avg1, avg2, avg3, avg4, avg3+avg4, buf);
		break;
	} //end for switch (saveformat)
	fclose(TmpFile);
	t_item.e1_e2 = avg1;
	t_item.e2_e1 = avg2;
	t_item.e1s_e2 = avg3;
	t_item.e2s_e1 = avg4;
	t_item.two_way = avg3+avg4;
	SaveOneToDb(saveFormat);
}
void RunThread::WriteResultCnt()
{
	CFile file;
	CString FileName=_T(".\\DatFile.txt");
	file.Open(FileName, CFile::modeWrite);
	file.Write(&result_cnt,sizeof(int));
	file.Close();
}

void RunThread::SaveTmpData2(Chariot2_result *pResult,unsigned long j, int k, int t)
{
	FILE *TmpFile;
	char *DataTmpFilename;
	CString xValName;
	errno_t err;
	char start_time[255]={0};
	char end_time[255]={0};

	CFile file;
	CString slinkRate;
//	DataTmpFilename = dataFullName.GetBuffer(dataFullName.GetLength());
	char *dbFormatFile = svtodbName.GetBuffer(svtodbName.GetLength());
	err = fopen_s(&TmpFile, dbFormatFile,"a+t"); // open temp file for append data
	
 		if (j==1 && k==1 && t==1)
 		{
			
			
			fprintf(TmpFile, "ReportId, ItemId, Throughput, SSID, Channel, LinkRate, StartTime, EndTime, TestLog\n");
		}
		else{
		
			slinkRate.Format("%dM",pResult->linkRate/1000);
			fprintf(TmpFile, "%d, %d, %.02f, %-20s, %d, %s, %s, %s, %s\n",pResult->report_id, pResult->item_id, pResult->throughput, pResult->SSID, pResult->channel, slinkRate,pResult->start_time, pResult->end_time, pResult->testLog );
		}
		fclose(TmpFile);
// 			GetDateTimeNow(buf, 0);
// 			fprintf(TmpFile, "Date: %s\n",buf);
// 
// 			fprintf(TmpFile, "Throughput(unit: Mbps)\n");
// 
// 			//			if (Form1->ckbLoadTestFile->Checked == true)
// 			//			{               
// 			//				fprintf(TmpFile,"%sExt_ALL    Ext_DLP    Ext_ULP\n", xValName);
// 			//				fprintf(TmpFile, "===      ========   ========   ========\n");
// 			//			}
// 			//			else
// 			//			{
// 			fprintf(TmpFile, "item_id        Att      	E1->E2	          k	     	 start          	end \n");
// 			fprintf(TmpFile, "=======        ===       ========	     =====	   ========      	======== \n");
// 			//			}
// 		}

		//		if (Form1->ckbLoadTestFile->Checked == true)
		//			fprintf(TmpFile,"%3d %6d %6d %9.2f %9.2f %9.2f\n", AttenuatorParameter.Attenuator_Value[j],
		//			AttenuatorParameter.Ext_Attenuation,
		//			AttenuatorParameter.Attenuator_Value[j]+AttenuatorParameter.Ext_Attenuation,
		//			avg4, avg5, avg6);
		//		else

		CString FileName=_T(".\\DatFile.txt");
		file.Open(FileName, CFile::modeWrite);
		file.SeekToEnd();
		file.Write(pResult,sizeof(Chariot2_result));
		result_cnt++;
		file.Close();
// 		fprintf(TmpFile,"%5d		%5d		%9.2f  %9d       %-15s\t%-15s\n",
// 			pResult->item_id, 0, pResult->throughput, pResult->kcnt, buf, end_time);
// 	fclose(TmpFile);
	//t_item.e1_e2 = avg1;
	//t_item.e2_e1 = avg2;
	//t_item.e1s_e2 = avg3;
	//t_item.e2s_e1 = avg4;
	//t_item.two_way = avg3+avg4;
	//SaveOneToDb(saveFormat);
}
typedef struct _Chariot2ResultTxtItem
{
	float att;
	int kcnt;
	float TxThroughput;
	float RxThroughput;
	char *pszSSID;
}Chariot2ResultTxtItem;

int  ssid_match(char *ssid, char (*p)[256], int size)
{
	for (int i =0; i < size; i++){
		if(strcmp(ssid, p[i]) == 0)
			return 1;
	}
	return 0;
}

void RunThread::SaveTmpDataOneTimes(unsigned long j, int k)
{
	FILE *TmpFile;
	char *DataTmpFilename;
	CString xValName;
	errno_t err;
	char buf[50]={0};
	char end_time[255]={0};
	int i=0,l=0;
	Chariot2_result result;
	Chariot2ResultTxtItem txtResult;
	DataTmpFilename = dataFullName.GetBuffer(dataFullName.GetLength());

	//if ( (Form1->ckbRotatorEnable->Checked == true) && (Form1->ckbEnableFieldTryMode->Checked == true) )
	//	xValName = "Ang    Ofs    Ang    ";
	//else

	err = fopen_s(&TmpFile, DataTmpFilename,"a+t"); // open temp file for append data

	//if (j==1 && k==1 && t==1)
	if ( k==1 )
	{
		GetDateTimeNow(buf, 0);
		fprintf(TmpFile, "Date: %s\n",buf);

		fprintf(TmpFile, "Throughput(unit: Mbps)\n");

		fprintf(TmpFile, "%-20s    Att      	TX	       	  RX	    k	    \n", "SSID");
		fprintf(TmpFile, "%-20s    ===       ========	    =======    =====	    \n", "=============");

	}
	char (*p)[256] = (char (*)[256])malloc(256*m_vec_Result.size());
	char (*q)[256] = p;
	for(i = 0; i < m_vec_Result.size(); i++)
	{
		result = m_vec_Result[i];
		txtResult.pszSSID = result.SSID;
		if(ssid_match(txtResult.pszSSID, p,m_vec_Result.size()))
			continue;
		memcpy(*q++, result.SSID, 256);
		for (l= 0; l < m_vec_Result.size();l++){
			if(strcmp(result.SSID,m_vec_Result[l].SSID) == 0){
				txtResult.kcnt = m_vec_Result[l].kcnt;
				if(m_vec_Result[l].TorR == 1){
					txtResult.TxThroughput = m_vec_Result[l].throughput;
				}else if(m_vec_Result[l].TorR == 0){
					txtResult.RxThroughput = m_vec_Result[l].throughput;
				}else if(m_vec_Result[l].TorR == 2){
					txtResult.TxThroughput = m_vec_Result[l].throughput;
					txtResult.RxThroughput = m_vec_Result[l].throughput1;
				}

			}
		}
		fprintf(TmpFile,"%-20s    %5d    %9.2f    %9.2f    %9d\n",
			txtResult.pszSSID, 0, txtResult.TxThroughput, txtResult.RxThroughput, txtResult.kcnt);
	}

	free(p);
	
	fclose(TmpFile);

}

int RunThread::ConnectAndGetIP(int card_index, char *profile, CString &str_ap_addr)
{
	CString DisplayWord;
	int retry = 5;
	while(retry--){
		pIceLemonDlg->OnConnect(card_index, profile , 1);
		if(pIceLemonDlg->cur_is_connected == 1) break;
		Sleep(200);
	}
	if(!pIceLemonDlg->cur_is_connected) {
		AfxMessageBox("can not connect to network!");
		return -1;
	}

	ChariotParameter.e1 = str_ap_addr;
	ChariotParameter.e2 = "";//
	retry = 5;
	do{
		pIceLemonDlg->GetLocalIPInfo(card_index, ChariotParameter.e2);

		if(ChariotParameter.e2 == "" ){
			DisplayWord.Format("[%d/5] Try to get ip address",6-retry);
			pIceLemonDlg->PrintlnToMemo(DisplayWord);
			Sleep(1000);
			continue;
		}else if(ChariotParameter.e2.Mid(0,3) != ChariotParameter.e1.Mid(0,3)){
			DisplayWord.Format("[%d/5] Try to get ip address",6-retry);
			pIceLemonDlg->PrintlnToMemo(DisplayWord);
			Sleep(1000);
			continue;
		}else{
			break;
		}
	}while(retry--);
	if(ChariotParameter.e2 ==""){
		AfxMessageBox("can not fetch ip address of endpoint2!");
		return -1;
	}
	strcpy_s(t_item.SSID, profile);
	return 0;
}

int RunThread::ConnectAndGetIP2(int card_index, char *profile, CString &str, CString lanIP, Chariot2_result *cResult)
{
	CString DisplayWord;
	int retry = 5;
	while(retry--){
		pIceLemonDlg->OnConnect(card_index, profile , 1);
		if(pIceLemonDlg->cur_is_connected == 1) break;
		Sleep(200);
	}
	if(!pIceLemonDlg->cur_is_connected) {
		AfxMessageBox("can not connect to network!");
		return -1;
	}

	retry = 5;
	do{
		pIceLemonDlg->GetLocalIPInfo(card_index, str);

		if(str == "" ){
			DisplayWord.Format("[%d/5] Try to get ip address",6-retry);
			pIceLemonDlg->PrintlnToMemo(DisplayWord);
			Sleep(1000);
			continue;
		}else if(str.Mid(0,3) != lanIP.Mid(0,3)){
			DisplayWord.Format("[%d/5] Try to get ip address",6-retry);
			pIceLemonDlg->PrintlnToMemo(DisplayWord);
			Sleep(1000);
			continue;
		}else{
			break;
		}
	}while(retry--);
	if(str ==""){
		AfxMessageBox("can not fetch ip address of endpoint!");
		return -1;
	}
	pIceLemonDlg->GetRxRate(cResult);
	return 0;
}

int RunThread::SaveResult()
{
    CADODbHelper dbHelper;
	CString sql;
	vector<Chariot2_result>::iterator iter;
	char start_time[50],
		end_time[50];
//	CString end_time;
	
	//GetDateTime(pResult->end, end_time, 1);
	try{
		dbHelper.OnInitADOConn();
		for(iter = m_vec_Result.begin(); iter != m_vec_Result.end(); iter++){
			Chariot2_result iResult = *iter;
			//GetDateTime(pResult->start, start_time, 1);
			sql.Format("insert into Result ( ReportId, ItemId, Throughput, StartTime, EndTime, TestLog) \
				   values (%d, %d, %.02f, '%s', '%s', '%s')",
				   iResult.report_id, iResult.item_id, iResult.throughput, iResult.start_time, iResult.end_time, iResult.testLog
			);
			dbHelper.ExecuteSQL((_bstr_t)sql);
		}
		dbHelper.ExitConn();
	}
	catch(...)
	{
		AfxMessageBox("操作失败");
		return -1;
	}
	

	return 0;
}

int RunThread::SetRunFlag(int flag)
{
	run_flag = flag;
	return 0;
}
int RunThread::Run()
{
	int ret;
	if(run_flag == 1){
		ret = Run1();
	}else{
		ret = Run2();
	}
	return ret;
}

int RunThread::Run1()
{
	char ChariotStatus;
	int FinishItem, finishAttItem;
	unsigned long saveFormat, TestDuration;    // used for tmp file format
	time_t tStart,tNow;
	int tCntSec = 0;
	int state = -1;
	FILE *tmpFile;
	bool OutLoop = false;
	bool status;
	unsigned long h, i, j;
	int k=0,LoopCount;
	int FinishTmpRound;
	CString DisplayWord;
	int ap_count = ChariotParameter.ap_count;
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
				saveFormat = pIceLemonDlg->saveFormat;
				FinishItem = 0; // record total finish item in test rounds
				finishAttItem = 0; // record total finish attenuator count in test rounds
				LoopCount = ChariotParameter.loop_count;//pIceLemonDlg->LoopCount; // set the test round
				AttenuatorParameter.Value_Count = 1;//2;
				j = 0;
				state = 1;
				break;
			case 1:
				//if finish j-loop?
				if (++j > AttenuatorParameter.Value_Count)
				{
					state = 100;
					break;
				}
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
				if(ChariotParameter.use_case == 1){
					if(k % ap_count == 1){
					//连线
						ConnectAndGetIP(ChariotParameter.card1_index, ChariotParameter.profile1, ChariotParameter.str_ap1_addr);
					}else if(k % ap_count == 2){
						ConnectAndGetIP(ChariotParameter.card1_index, ChariotParameter.profile2, ChariotParameter.str_ap2_addr);
						
					}else {// if(k % ap_count == ...){
						if(ap_count == 2){
							ConnectAndGetIP(ChariotParameter.card1_index, ChariotParameter.profile2, ChariotParameter.str_ap2_addr);
						}else{
							ConnectAndGetIP(ChariotParameter.card1_index, ChariotParameter.profile3, ChariotParameter.str_ap3_addr);
						}
					}//End if(k % 2 == 1){
				}//End if(ChariotParameter.use_case == 1)
				else if (ChariotParameter.use_case == 2){
					if(k % 2 == 1){
						//连线
						int retry = 5;
						while(retry--){
							pIceLemonDlg->OnConnect(ChariotParameter.card1_index, ChariotParameter.profile1 , 1);
							if(pIceLemonDlg->cur_is_connected == 1)break;
							Sleep(200);
						}
						if(!pIceLemonDlg->cur_is_connected) {
							AfxMessageBox("can not connect to network!");
							return -1;
						}
						//Sleep(1000);
						//ChariotParameter.e1 = ChariotParameter.str_ap1_addr;
						ChariotParameter.e2 = "";//
						retry = 5;
						do{
							pIceLemonDlg->GetLocalIPInfo(ChariotParameter.card1_index,ChariotParameter.e2);
							if(ChariotParameter.e2 == ""){
								DisplayWord.Format("[%d/5] Try to get ip address",6-retry);
								pIceLemonDlg->PrintlnToMemo(DisplayWord);
								Sleep(1000);
								continue;
							}else{
								break;
							}
						}while(retry--);
						if(ChariotParameter.e2 ==""){
							AfxMessageBox("can not fetch ip address of endpoint2!");
							return -1;
						}
						//else{
						//	AfxMessageBox(ChariotParameter.e2);
						//}
					}else{
						//pIceLemonDlg->OnConnect();
						int retry = 5;
						while(retry--){
							pIceLemonDlg->OnConnect(ChariotParameter.card2_index, ChariotParameter.profile2 , 1);
							if(pIceLemonDlg->cur_is_connected == 1)break;
							Sleep(200);
						}
						if(!pIceLemonDlg->cur_is_connected) {
							AfxMessageBox("can not connect to network!");
							return -1;
						}

						//ChariotParameter.e1 = ChariotParameter.str_ap2_addr;
						ChariotParameter.e2 = "";//
						retry = 5;
						do{
							pIceLemonDlg->GetLocalIPInfo(ChariotParameter.card2_index,ChariotParameter.e2);
							if(ChariotParameter.e2 == ""){
								DisplayWord.Format("[%d/5] Try to get ip address",6-retry);
								pIceLemonDlg->PrintlnToMemo(DisplayWord);
								Sleep(1000);
								continue;
							}else{
								break;
							}
						}while(retry--);
						if(ChariotParameter.e2 ==""){
							AfxMessageBox("can not fetch ip address of endpoint2!");
							return -1;
						}
					}//End if(k % 2 == 1){
					strcpy_s(t_item.SSID, ChariotParameter.profile1);
				}

				//return 0;
				t_item.e1_ip = ChariotParameter.e1;
				t_item.e2_ip = ChariotParameter.e2;
				pIceLemonDlg->m_page_main.SetTimer(1, 200, NULL); //Enable Timer
				SetDataTmpFile(j,k);  // Set Data Tmp Filename, (The filename varies with "k")

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
					pIceLemonDlg->PrintlnToMemo("");
					pIceLemonDlg->PrintlnToMemo("*************************");
					pIceLemonDlg->PrintlnToMemo("Start Pre-Running...");
					IsPreRun = true;
				}
				else
				{
					TestDuration = ChariotParameter.testduration;
					if(ChariotParameter.use_case == 1 || ChariotParameter.use_case == 2){
						TestDuration = ChariotParameter.duration_single;
					}
					IsPreRun = false;
				}

				status = SetupChariot(ChariotParameter.Test_Direction[i], TestDuration);

				DisplayWord.Format("i = %d, TestDuration = %d", i, TestDuration);
				//Form1->Memo->Lines->Add(DisplayWord);			

				if (status == false)
				{
					pIceLemonDlg->PrintlnToMemo("Setup Chariot Fail!!");			
					CHR_test_force_delete(test);
					state = 99;   //error
					break;
				}
				if (ChariotParameter.testfile != "")
					Save_ChariotTestFile(ChariotParameter.Test_Direction[i], LoopCount, j, k);
				GetSaveDataFileName(ChariotParameter.Test_Direction[i], LoopCount, j, k, datFileName);
				TouchFile(k); // clear the file content

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
				//if(difftime(tNow, tStart) > TestDuration +1)//test finish
				if(difftime(tNow, tStart) > TestDuration)//test finish
				{
					state = 6;
					break;
				}else {
					if(difftime(tNow,tStart) > tCntSec) {
						GetThroughput(ChariotParameter.Test_Direction[i],h);
						//GetThroughputMax(ChariotParameter.Test_Direction[i],h);
						//SaveOneToDb();
						th_curve.cur_idx = tCntSec;
						pIceLemonDlg->SendMessage(WM_UPDATE_CHART,(WPARAM)&th_curve, NULL);
						tCntSec++;

						if(th_curve.cur_idx == 0){ xl.clear();}
						CV_META cm;
						cm.idx = th_curve.cur_idx;
						cm.th_val=th_curve.th_val;
						//cm.th_val_max = th_curve.th_val_max;
						xl.push_back(cm);
					}
					
					if ( (Flag.Halt == true) || (Flag.Abort == true) ) // if press halt, stop the current pair test!!
					{
						pIceLemonDlg->m_page_main.FreezeTimeRemain();
						EndChariotTest();
						
						if (Flag.Halt == true)
						{
							pIceLemonDlg->PrintlnToMemo("Wait for halt....", 1);
							state = 18;
							break;
						}

						if (Flag.Abort == true)
						{
							pIceLemonDlg->PrintlnToMemo("");
							pIceLemonDlg->PrintlnToMemo("Wait for stop....", 1);
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
							pIceLemonDlg->PrintlnToMemo("");
							pIceLemonDlg->PrintlnToMemo("*******Charior error: IP address unreachable !!*******");
							pIceLemonDlg->PrintlnToMemo("");
							pIceLemonDlg->PrintlnToMemo("--> Please check IP address setting & AP/cable connection!!");
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

				SaveTPToFile();
				if (IsPreRun == false)
				{
					if (ChariotParameter.testfile != "")
						CHR_test_save(test); //save Chariot test file *.tst
					//GetThroughput(j, ChariotParameter.Test_Direction[i], h); //Get Throughput ane delete test object
					 GetThroughput(j, ChariotParameter.Test_Direction[i], h); //Get Throughput ane delete test object
					
					
				}
				else
				{
					CHR_test_force_delete(test);  //delete test if pre-run
					pIceLemonDlg->PrintlnToMemo("Stop Pre-Running...\n");
					pIceLemonDlg->PrintlnToMemo("*************************\n");
				}

				FinishTmpRound++;
				pIceLemonDlg->FinishChariotRoundCount++;
				state = 4;
				break;
			case 18:
				pIceLemonDlg->m_page_main.KillTimer(1);
				pIceLemonDlg->PrintlnToMemo("");
				pIceLemonDlg->PrintlnToMemo("Test Halt!!",1);
				i--;   // go back to the halt pair-test if continue to run

				while (1)  //wait for continue or abort
				{
					//  wait for "Halt off" or "Abort on"
					if  (Flag.Halt == false)
					{
						//ShowRunApperance();
						pIceLemonDlg->m_page_main.SetTimer(1, 200, NULL);
						pIceLemonDlg->PrintlnToMemo("");
						pIceLemonDlg->PrintlnToMemo("Test Continue....",1);

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
				 SaveTmpData(saveFormat, j, k);  //save tmp data
			

				FinishItem++;  // total finish item in all loopcount
				pIceLemonDlg->FinishItem = FinishItem;
				if (j == AttenuatorParameter.Value_Count && k == LoopCount)  //the last attenuator value
				{
					 errno_t err= fopen_s(&tmpFile, dataFullName.GetBuffer(dataFullName.GetLength()),"a+t");
					fprintf(tmpFile,"### %6d", finishAttItem + 1);  //how many att item in this loop
					fclose(tmpFile);
				}

				state = 2;  // to the next-k (loop)
				break;
			case 90:
				if (k-1 == LoopCount)
				{
					// Update finish item
					finishAttItem++;  // record at each k-loop (it means finish att count)
					pIceLemonDlg->finishAttItem = finishAttItem;
				}

				state = 1;  //to the next-j (attenuator Value)
				//state = 101;  //to finish attenuator test
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
			case 100:
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

int RunThread::Run2()
{
	int card_idx;
	int i, k = 0;
	//card_idx = pIceLemonDlg->cur_sel_card;
	card_idx = sTest.card_idx;
	list<Chariot2_Item>::iterator plist; 
	Chariot2_result re_info;
	bool status;
	time_t tStart,tNow;
	unsigned long  testDuration;  
	int loopCount = 1;
	int state = -1;
	char ChariotStatus;
	FILE *tmpFile;
	int j = 0;
	int t = 0;// index of m_chariot2_List 
	int outLoop = false;
	int tCntSec = 0;
	list<Chariot2_Item> *pC2List  = &sTest.clist;
	loopCount = sTest.total_time / sTest.single_time;
	loopCount = loopCount > 0 ? loopCount:1;
	//if(sTest.total_time % sTest.single_time > 0) loopCount++;
	CFile file;
	CString FileName=_T(".\\DatFile.txt");
	file.Open(FileName, CFile::modeCreate|CFile::modeWrite);
	result_cnt=0;
	file.Write(&result_cnt,sizeof(int));
	file.Close();
	++j;
	for(k = 1; k <= loopCount ; k++){
		re_info.kcnt = k;
		//for(j=0; j < 1;j++){ 
		//next j
		pIceLemonDlg->CurrentLoopCount = k; //to set what loop the program run now.
		t = 0;
		for(plist = pC2List->begin(); plist != pC2List->end(); plist++) { 
			Chariot2_Item xItem = *plist;
			re_info.item_id = xItem.id;
			re_info.TorR = xItem.TorR;
			t++;
			testDuration = xItem.test_duration;
			//DisplayWord.Format("i = %d, TestDuration = %d", i, testDuration);
			if(xItem.proflag == 1){
				strcpy_s(re_info.SSID, xItem.profile_e1);
				ConnectAndGetIP2(card_idx, xItem.profile_e1, xItem.e1, xItem.e2, &re_info);
			}else if(xItem.proflag == 2){
				strcpy_s(re_info.SSID, xItem.profile_e2);
				ConnectAndGetIP2(card_idx, xItem.profile_e2, xItem.e2, xItem.e1, &re_info);
			}
			SetDataTmpFile2(&re_info,j,k,t);
			status = SetupChariot2(&xItem);
			if (xItem.testfile != "")
				Save_ChariotTestFile2(&xItem, loopCount, 0, k);
			CHR_test_start(test);  //  Start Test!!
			time(&tStart);
			time(&tNow);
			tCntSec = 0;
			GetDateTime(tStart, re_info.start_time, 3);
			//tCntSec = 0;
			pIceLemonDlg->CorrectTimeRemain2(&xItem);
			pIceLemonDlg->m_page_main.RestartTimeRemain();
			outLoop = false;
			state = 5;
			
			do{
				switch(state){
				case 5:
					if(difftime(tNow, tStart) > testDuration)//test finish
					{
						GetDateTime(tNow,re_info.end_time, 3);
						state = 6;
						break;
					}else{
						if(difftime(tNow,tStart) > tCntSec) {
							GetThroughput2(&xItem, j, &re_info, 0);
							//GetThroughputMax(ChariotParameter.Test_Direction[i],h);
							//SaveOneToDb();
							th_curve.cur_idx = tCntSec;
							pIceLemonDlg->SendMessage(WM_UPDATE_CHART,(WPARAM)&th_curve, NULL);
							tCntSec++;

						}
						if ( (Flag.Halt == true) || (Flag.Abort == true) ) // if press halt, stop the current pair test!!
						{
							pIceLemonDlg->m_page_main.FreezeTimeRemain();
							EndChariotTest();

							if (Flag.Halt == true)
							{
								pIceLemonDlg->PrintlnToMemo("Wait for halt....", 1);
								state = 18;
								break;
							}

							if (Flag.Abort == true)
							{
								pIceLemonDlg->PrintlnToMemo("");
								pIceLemonDlg->PrintlnToMemo("Wait for stop....", 1);
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
								pIceLemonDlg->PrintlnToMemo("");
								pIceLemonDlg->PrintlnToMemo("*******Charior error: IP address unreachable !!*******");
								pIceLemonDlg->PrintlnToMemo("");
								pIceLemonDlg->PrintlnToMemo("--> Please check IP address setting & AP/cable connection!!");
								IsError = true;
								//IsStopped = true;
								
								CHR_test_force_delete(test);
								state = 99;
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

					if (xItem.testfile != "")
						CHR_test_save(test); //save Chariot test file *.tst
					//GetThroughput(j, ChariotParameter.Test_Direction[i], h); //Get Throughput ane delete test object
					GetThroughput2(&xItem, j, &re_info,1); //Get Throughput ane delete test object
					
					state = 80;
					break;
				case 80: //i-loop (chariot pair) finish process
					//SaveTmpData(saveformat, j);  //save tmp data
					SaveTmpData2(&re_info, j, k, t);  //save tmp data		
					m_vec_Result.push_back(re_info);
					//state = 2;  // to the next-k (loop)
					outLoop = true;
					break;
				}//switch(state){
			}while(!outLoop);


		}//for(plist = pC2List->begin(); plist != pC2List->end(); plist++) { 
		//}//for(j=0; j < 1;j++){
		SaveTmpDataOneTimes(j,k);
	}//for(k = 0; k < loopCount ; k++){
	//	errno_t err= fopen_s(&tmpFile, dataFullName.GetBuffer(dataFullName.GetLength()),"a+t");
	//	fprintf(tmpFile,"### %6d", finishAttItem + 1);  //how many att item in this loop
	//	fclose(tmpFile);
	WriteResultCnt();
	errno_t err= fopen_s(&tmpFile, dataFullName.GetBuffer(dataFullName.GetLength()),"a+t");
	fprintf(tmpFile,"### finish ###");  //how many att item in this loop
	fclose(tmpFile);
	
	return 0;
}