// dllmain.h : Declaration of module class.

class CSearchComponentModule : public ATL::CAtlDllModuleT< CSearchComponentModule >
{
public :
	DECLARE_LIBID(LIBID_SearchComponentLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SEARCHCOMPONENT, "{72e1997d-0945-4ac4-ae48-62e7fed255aa}")
};

extern class CSearchComponentModule _AtlModule;
