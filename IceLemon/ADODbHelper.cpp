#include "stdafx.h"
#include "ADODbHelper.h"


CADODbHelper::CADODbHelper(void)
{
}


CADODbHelper::~CADODbHelper(void)
{
}
void CADODbHelper::OnInitADOConn()
{

	try
	{
		m_pCon.CreateInstance("ADODB.Connection");
		m_pCon->ConnectionTimeout=3;
		m_pCon->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=D:\\xv\\Projects\\IceLemon\\IceLemon\\DAT.accdb","","",adModeUnknown);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
}

void CADODbHelper::ExitConn()
{
	if(m_pRs!=NULL)
		m_pRs->Close();
	m_pCon->Close();

}

_RecordsetPtr& CADODbHelper::GetRecordSet(_bstr_t bstrSQL)
{
	try
	{
		if(m_pCon==NULL)
			OnInitADOConn();
		m_pRs.CreateInstance("ADODB.Recordset");
		m_pRs->Open(bstrSQL,m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	return m_pRs;
}

BOOL CADODbHelper::ExecuteSQL(_bstr_t bstrSQL)
{
	try
	{
		if(m_pCon==NULL)
			OnInitADOConn();
		m_pCon->Execute(bstrSQL,NULL,adCmdText);
		return true;
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return false;
	}

}
