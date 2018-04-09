///////////////////////////////////////////////////////////////////////
// Client.cpp - creates FileMgr and Search, hooks together, and uses   //
//                                                                   //
// Yaodong Wang, CSE775 - Distributed Objects, Spring 2018            //
///////////////////////////////////////////////////////////////////////

#include <atlbase.h>
#include <atlsafe.h>
#include <iostream>
#include <string>
#include "../FileMgrComponent/FileMgrComponent_i.h"
#include "../SearchComponent/SearchComponent_i.h"

// below line is used
//  for test text-regex "some word start with 'sub' like submarine, subject

int main()
{
	std::cout << "\n  CSE775 Project #1 C++ client";
	std::cout << "\n =================================";
	CoInitialize(NULL);
	{
		// create a Helper instance of FileMgr

		CComQIPtr<IFileManager> pHelper;
		pHelper.CoCreateInstance(CLSID_FileManager);
		if (pHelper)
		{
			// send path string to helper

			CComBSTR path("./demofiles");
			pHelper->SetReadPath(path);
		}
		// create a Using instance of Search

		CComQIPtr<ITextSearch> pUsing;
		pUsing.CoCreateInstance(CLSID_TextSearch);
		if (pUsing)
		{
			// send Using an IUnknow pointer to Helper

			pUsing->SetFileMgrIF(pHelper);

			// get result from Using

			CComBSTR regexp = L"CLSID*";
			SAFEARRAY list;
			SAFEARRAY* pList = &list;
			
			pUsing->SearchLineNum(regexp, &pList);
			CComSafeArray<BSTR> csList;

			csList.Attach(pList);
			for (int i = 0; i < (int)csList.GetCount(); ++i) {
				std::wcout << "\n" << csList[i];
			}
			std::wcout << "\n";
		}
		std::wcout << "\n\n";
	}
	CoUninitialize();
	return 0;
}
