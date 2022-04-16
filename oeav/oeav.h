
// oeav.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// основные символы


// CoeavApp:
// Сведения о реализации этого класса: oeav.cpp
//

class CoeavApp : public CWinApp
{
public:
	CoeavApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CoeavApp theApp;
