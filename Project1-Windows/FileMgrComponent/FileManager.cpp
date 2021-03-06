// FileManager.cpp : Implementation of CFileManager
// Yaodong Wang, CSE775 - Distribted Objects, Spring 2018
/*
* Module Operations
* =================
* SetReadPath specifies path as root of directory tree
*
* GetFiles retrieves qualified file fullspec path in a directory
* tree
*
* DFS is a recursive dir searching method, invoked by GetFiles
*
* Required Files:
* ===============
*   "stdafx.h" - in property, set c++, preprocessed head to null
*	"FileManager.h"
*	"FileInfo.h"
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
#include <iostream>
#include <string>
#include <vector>
#include "FileManager.h"
#include "FileInfo.h"

// CFileManager

// -- < set path > --

STDMETHODIMP CFileManager::SetReadPath(BSTR path)
{
	_ReadPath = path;
	std::wcout << L"\n  setting path: " << (BSTR)_ReadPath;

	return S_OK;
}


// -- < get files based on fname pattern "ptn" on dir tree, root at specific path > --

STDMETHODIMP CFileManager::GetFiles(BSTR ptn, SAFEARRAY ** files)
{
	/*
	CComSafeArray<BSTR> _files;
	fileInfo f;
	f.setPath((BSTR)_ReadPath);

	// search filename
	if (f.firstFile(ptn)) {
		_files.Add(CComBSTR(f.name().c_str()));
		while (f.nextFile()) {
			_files.Add(CComBSTR(f.name().c_str()));
		}
	}
	f.closeFile();

	// search sub-directory
	if (f.firstFile(L"*.*")) {
		if (f.isDirectory() && f.name() != L"." && f.name() != L"..") {
			SAFEARRAY stmpfiles;
			SAFEARRAY* pTFiles = &stmpfiles;
			GetFiles(ptn, &pTFiles);  // dfs
			CComSafeArray<BSTR> csTmpFiles;
			csTmpFiles.Attach(pTFiles);
			for (int i = 0; i < (int)csTmpFiles.GetCount(); ++i) {
				_files.Add(csTmpFiles[i]);
			}
		}
		while (f.nextFile()) {
			if (f.isDirectory() && f.name() != L"." && f.name() != L"..") {
				SAFEARRAY stmpfiles;
				SAFEARRAY* pTFiles = &stmpfiles;
				GetFiles(ptn, &pTFiles);  // dfs
				CComSafeArray<BSTR> csTmpFiles;
				csTmpFiles.Attach(pTFiles);
				for (int i = 0; i < (int)csTmpFiles.GetCount(); ++i) {
					_files.Add(csTmpFiles[i]);
				}
			}
		}
	}
	f.closeFile();
	HRESULT hres = (int)_files.GetCount() > 0 ? S_OK : S_FALSE;
	*files = _files.Detach();
	return hres;
	*/
	_FilePtn = ptn;
	CComSafeArray<BSTR> _files((ULONG)0); // set size = 0, otherwise null exception??

	std::vector<std::wstring> _fileVec = DFS((BSTR)_ReadPath);
	for (int i = 0; i < (int)_fileVec.size(); ++i) {
		_files.Add(CComBSTR(_fileVec[i].c_str()));
	}

	HRESULT hres =  (int)_files.GetCount() > 0 ? S_OK : S_FALSE;
	*files = _files.Detach();
	hres == S_OK ? std::wcout << L"\n\n    file patten : \"" << ptn << L"\" is found, and "<< L"FileMgr returns \"S_OK\"\n" : 
		std::wcout << L"\n\n    file patten : \"" << ptn << L"\" is not found, and " << L"FileMgr returns \"S_FALSE\"\n";
	return hres;
}

// -- < recursively serach directory tree, for fullSpec filename > --

std::vector<std::wstring> CFileManager::DFS(std::wstring path) {
	std::vector<std::wstring> _files;
	fileInfo f(path);
	
	// search filename
	if (f.firstFile((BSTR)_FilePtn)) {
		_files.push_back(f.getPath() + L"\\" + f.name());
		while (f.nextFile()) {
			_files.push_back(f.getPath() + L"\\" + f.name());
		}
	}
	//f.closeFile();

	// search sub-directory
	if (f.firstFile(L"*.*")) {
		if (f.isDirectory() && f.name() != L"." && f.name() != L"..") {
			std::vector<std::wstring> tempfiles = DFS(f.name());  // dfs
			_files.insert(_files.end(), tempfiles.begin(), tempfiles.end());
		}
		while (f.nextFile()) {
			if (f.isDirectory() && f.name() != L"." && f.name() != L"..") {
				std::vector<std::wstring> tempfiles = DFS(f.name());  // dfs
				_files.insert(_files.end(), tempfiles.begin(), tempfiles.end());
			}
		}
	}
	f.closeFile();
	return _files;
}
