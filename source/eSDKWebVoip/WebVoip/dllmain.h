// dllmain.h : Declaration of module class.

class CWebVoipModule : public ATL::CAtlDllModuleT< CWebVoipModule >
{
public :
	DECLARE_LIBID(LIBID_WebVoipLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_WEBVOIP, "{0ED3E14D-6C73-4270-A75D-2B8B23C9718F}")
};

extern class CWebVoipModule _AtlModule;
