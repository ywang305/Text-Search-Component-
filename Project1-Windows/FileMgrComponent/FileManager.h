// FileManager.h : Declaration of the CFileManager

#pragma once
#include "resource.h"       // main symbols



#include "FileMgrComponent_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CFileManager

class ATL_NO_VTABLE CFileManager :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFileManager, &CLSID_FileManager>,
	public IDispatchImpl<IFileManager, &IID_IFileManager, &LIBID_FileMgrComponentLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CFileManager()
	{
	}

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CFileManager)
	COM_INTERFACE_ENTRY(IFileManager)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	STDMETHOD(SetReadPath)(BSTR path);
	STDMETHOD(GetFiles)(BSTR ptn, SAFEARRAY ** files);

private:
	CComBSTR _ReadPath;	
	CComBSTR _FilePtn;
	std::vector<std::wstring> DFS(std::wstring path);
};

OBJECT_ENTRY_AUTO(__uuidof(FileManager), CFileManager)
