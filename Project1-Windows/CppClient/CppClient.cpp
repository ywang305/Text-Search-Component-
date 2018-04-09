///////////////////////////////////////////////////////////////////////
// Client.cpp - creates FileMgr and Search, hooks together, and uses //
//                                                                  //
// Yaodong Wang, CSE775 - Distributed Objects, Spring 2018          //
// CppClient for calling ATLCOM SerachComponent						//
//   and indirectly calling FileMgrComponent						//
//																	//
///////////////////////////////////////////////////////////////////////

/*
//  Package Operations:												//
//  -------------------------										//
//  This client console is  provided to demo Search COM uses FileMgr //
//  COM. Search text regular express function is implemented by c++   //
//  <regex> in Search COM, and file retriving recursion is implemented //
//  by FileInfo class integred with FileMgr COM.					 //
//																	//
*	usage
*	-----------
*	CppClient [path] [regex]
*
*	note
*	-----------
*	1. _WIN32_WINNT 0x0601 for Win7 and later
*
*	2. conversion between BSTR and wstring
*		wstring wstr = wstring(bstr)
*		BSTR bstr = CComBSTR(wstr.c_str())
*	3. CComBSTR constor
*		CComBSTR regexp = L"CLSID"
*		CComBSTR path(L"../foobar");
*		
*/



#define _WIN32_WINNT 0x0601
#include <atlbase.h>
#include <atlsafe.h>
#include <iostream>
#include <string>
#include "../FileMgrComponent/FileMgrComponent_i.h"
#include "../SearchComponent/SearchComponent_i.h"


int main(int argc, char *argv[])
{
	std::cout << "\n  CSE775 Project #1 C++ client";
	std::cout << "\n =================================";

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (!SUCCEEDED(hr)) {
		std::wcout << L"\n   could not initialize COM";
	}

	try {
		// create a Helper instance of FileMgr

		CComQIPtr<IFileManager> pHelper;
		pHelper.CoCreateInstance(CLSID_FileManager);
		if (pHelper)
		{
			CComBSTR path = argc>1? CComBSTR(argv[1]) : L"./demoDir";
			pHelper->SetReadPath(path);
		}
		else { throw std::exception("CoCreateInstance pHelper failed"); }

		// create a Using instance of Search

		CComQIPtr<ITextSearch> pUsing;
		pUsing.CoCreateInstance(CLSID_TextSearch);
		if (pUsing)
		{
			pUsing->SetFileMgrIF(pHelper);
			{   // test case 1: input regex Argv[2] = "CLSID*"
				CComBSTR regexp = argc>2 ? CComBSTR(argv[2]) : L"CLSID*";
				std::wcout << L"\n\n   ----< test case 1: input regex argv[2] = " << L"\"" << std::wstring(regexp) << L"\" > ----\n";
				SAFEARRAY list;
				SAFEARRAY* pList = &list;
				pUsing->SearchLineNum((BSTR)regexp, &pList);
				CComSafeArray<BSTR> csList;
				csList.Attach(pList);
				std::wcout << L"\n\n getting result for text regex: " << L"\"" << std::wstring(regexp) << L"\"" << L"\n  ----------------------------------------------";
				for (int i = 0; i < (int)csList.GetCount(); ++i) {
					std::wcout << L"\n\n" << std::wstring(csList[i]);
				}
				std::wcout << "\n";
			}
			{  // test case 2 : "\b(sub)([^ ]*)"
				CComBSTR regexp = L"\\b(sub)([^ ]*)";
				std::wcout << L"\n\n\n\n   ----< test case 2: regex = " << L"\"" << std::wstring(regexp) << L"\" > ----\n";
				SAFEARRAY list;
				SAFEARRAY* pList = &list;
				pUsing->SearchLineNum((BSTR)regexp, &pList);
				CComSafeArray<BSTR> csList;
				csList.Attach(pList);
				std::wcout << L"\n\n getting result for text regex: " << L"\"" << std::wstring(regexp) << L"\"" << L"\n  ----------------------------------------------";
				for (int i = 0; i < (int)csList.GetCount(); ++i) {
					std::wcout << L"\n\n" << std::wstring(csList[i]);
				}
				std::wcout << "\n";
			}
		}
		else { throw std::exception("CoCreateInstance pUsing failed"); }
	}
	catch (std::exception &ex) {
		std::wcout << L"\n   " << ex.what() << L"\n\n";
		return 0;
	}
	std::wcout << L"\n\n";
	CoUninitialize();

	//system("pause");
	return 0;
}