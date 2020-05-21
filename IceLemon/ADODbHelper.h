#pragma once
class CADODbHelper
{
public:
	CADODbHelper(void);
	virtual ~CADODbHelper(void);
	BOOL ExecuteSQL(_bstr_t bstrSQL);
	_RecordsetPtr& GetRecordSet(_bstr_t bstrSQL);
	void ExitConn();
	void OnInitADOConn();

	_ConnectionPtr m_pCon;
	_RecordsetPtr m_pRs;
};

