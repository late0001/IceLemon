
// IceLemon.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIceLemonApp:
// �йش����ʵ�֣������ IceLemon.cpp
//

class CIceLemonApp : public CWinApp
{
public:
	CIceLemonApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIceLemonApp theApp;