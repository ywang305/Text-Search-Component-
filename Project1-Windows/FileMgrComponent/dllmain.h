// dllmain.h : Declaration of module class.

class CFileMgrComponentModule : public ATL::CAtlDllModuleT< CFileMgrComponentModule >
{
public :
	DECLARE_LIBID(LIBID_FileMgrComponentLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_FILEMGRCOMPONENT, "{baf154d3-d074-456e-b821-66f4ebf9d2f1}")
};

extern class CFileMgrComponentModule _AtlModule;
