// TextSearch.cpp : Implementation of CTextSearch
// Yaodong Wang, CSE775 - Distribted Objects, Spring 2018
/*
* Module Operations
* =================
* SetFileMgrIF set FileMgr point to TextSearch inner IUnknown pointer
* , the TextSearch COM can call FileMgr COM methods.
*
* SearchLineNum uses FileMgr pointer to search directory tree with file
* name pattern, if find matched files, it uses c++ fstream to read line
* by line, and return the file pathSpec and line number that 
* matched regex text.
*
* Required Files:
* ===============
*   "stdafx.h" - in property, set c++, preprocessed head to null
*	FileMgrComponent_i.h
*	TextSearch.h
*
* Build Process:
* ==============
* - Build FileMgrComponent first
* - Build Search Component second
* - Build client last
*
* Maintenance History
* ===================
* 12 Mar 2018
* - first release
*
*/


#include "stdafx.h"
#include <atlsafe.h>
#include "TextSearch.h"
#include "../FileMgrComponent/FileMgrComponent_i.h"
#include <regex>
#include <iostream>
#include <vector>
#include <fstream>

// CTextSearch

// --- < convert to a point to IFileMgr, type known from osidl.idl > ---

STDMETHODIMP CTextSearch::SetFileMgrIF(IUnknown* pFileMgrIF)
{
	std::wcout << L"\n CTextSearch is setting a FileMgr pointer to IUnknown\n";
	_pFileMgr = pFileMgrIF;

	return S_OK;
}

// --- < get line number of regex from retrieved filenames > ---

STDMETHODIMP CTextSearch::SearchLineNum(BSTR regexp, SAFEARRAY ** result)
{
	CComQIPtr<IFileManager> pHelper = _pFileMgr;  // note: pFileMgr is a smart pointer object created with this declaration
	if (!pHelper)
		return E_NOINTERFACE;
	std::wcout << L"\n SearchComponent gets text regex : " << regexp << 
		L"\n filename_pattern : " << L"*.h, *.hpp, *.c,  *.cpp ,  *.cs, *.txt \n";
	std::vector<BSTR> fileNames{ L"*.h", L"*.hpp", L"*.c", L"*.cpp", L"*.cs", L"*.txt"};
	CComSafeArray<BSTR> Result;

	for (BSTR name : fileNames) {
		SAFEARRAY files;
		SAFEARRAY* pFiles = &files;
		HRESULT hr = pHelper->GetFiles(name, &pFiles);
		if (!SUCCEEDED(hr)) return E_FAIL;
		if (hr == S_FALSE) continue;

		CComSafeArray<BSTR> Files;
		Files.Attach(pFiles);
		
		std::wsmatch wm;
		std::wregex wrx(regexp);

		for (int i = 0; i < (int)Files.GetCount(); ++i) {
			int line = 0;
			std::wifstream ifs(Files[i]); // wifstream
			if (!ifs) continue;
			std::wstring text;
			while (std::getline(ifs, text)) {
				++line;
				if (std::regex_search(text, wm, wrx)) {
					std::wstring record = std::wstring(Files[i]) + L"\n    line# : " + std::to_wstring(line);
					Result.Add(CComBSTR(record.c_str()));
				}
			}
		}
	}
	*result = Result.Detach();
	return S_OK;
}
