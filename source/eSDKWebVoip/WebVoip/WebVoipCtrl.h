// WebVoipCtrl.h : Declaration of the CWebVoipCtrl
#pragma once
#include "resource.h"       // main symbols
#include <atlctl.h>
#include "WebVoip_i.h"
#include "_IWebVoipCtrlEvents_CP.h"
#include "NotifyCallBack.h"
#include "Tools.h"
#include "Log.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;



// CWebVoipCtrl
class ATL_NO_VTABLE CWebVoipCtrl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IWebVoipCtrl, &IID_IWebVoipCtrl, &LIBID_WebVoipLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IPersistStreamInitImpl<CWebVoipCtrl>,
	public IOleControlImpl<CWebVoipCtrl>,
	public IOleObjectImpl<CWebVoipCtrl>,
	public IOleInPlaceActiveObjectImpl<CWebVoipCtrl>,
	public IViewObjectExImpl<CWebVoipCtrl>,
	public IOleInPlaceObjectWindowlessImpl<CWebVoipCtrl>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CWebVoipCtrl>,
	public CProxy_IWebVoipCtrlEvents<CWebVoipCtrl>,
	public IObjectWithSiteImpl<CWebVoipCtrl>,
	public IServiceProviderImpl<CWebVoipCtrl>,
	public IPersistStorageImpl<CWebVoipCtrl>,
	public ISpecifyPropertyPagesImpl<CWebVoipCtrl>,
	public IQuickActivateImpl<CWebVoipCtrl>,
#ifndef _WIN32_WCE
	public IDataObjectImpl<CWebVoipCtrl>,
#endif
	public IProvideClassInfo2Impl<&CLSID_WebVoipCtrl, &__uuidof(_IWebVoipCtrlEvents), &LIBID_WebVoipLib>,
	public IPropertyNotifySinkCP<CWebVoipCtrl>,
	public IObjectSafetyImpl<CWebVoipCtrl, INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public CComCoClass<CWebVoipCtrl, &CLSID_WebVoipCtrl>,
	public CComControl<CWebVoipCtrl>
{
public:
	CWebVoipCtrl()
		: m_ATLWnd(NULL)
		, VoipSIPServerIP("")
		, VoipSIPServerPort(0)
		, VoipCallInfo_Id(0)
		, VoipCallInfo_CallerStatus(0)
		, VoipCallInfo_CalleeStatus(0)
		, VoipCallInfo_CallerNum("")
		, VoipCallInfo_CalleeNum("")
		, VoipCallInfo_OrgCalleeNum("")
		, VoipCallInfo_LineId(0)
		, VoipCallInfo_LineType(0)
		, VoipCallMode(0)
		, MediaType(0)
		, VoipUserInfo_Id("")
		, VoipUserInfo_UserName("")
		, VoipUserInfo_Password("")
		, VoipUserInfo_AccNum("")
		, VoipUserInfo_AccStatus(0)
		, VoipUserInfo_SipStatus(0)
	{
	}

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_INSIDEOUT |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_WEBVOIPCTRL)


BEGIN_COM_MAP(CWebVoipCtrl)
	COM_INTERFACE_ENTRY(IWebVoipCtrl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
#ifndef _WIN32_WCE
	COM_INTERFACE_ENTRY(IDataObject)
#endif
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY(IObjectWithSite)
	COM_INTERFACE_ENTRY(IServiceProvider)
	COM_INTERFACE_ENTRY_IID(IID_IObjectSafety, IObjectSafety)
END_COM_MAP()

BEGIN_PROP_MAP(CWebVoipCtrl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY_TYPE("Property Name", dispid, clsid, vtType)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CWebVoipCtrl)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(__uuidof(_IWebVoipCtrlEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CWebVoipCtrl)
	CHAIN_MSG_MAP(CComControl<CWebVoipCtrl>)
	MESSAGE_HANDLER(WM_CALL_NOTIFY,OnCallNotify)	
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* const arr[] =
		{
			&IID_IWebVoipCtrl,
		};

		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IWebVoipCtrl
public:
	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		// Set Clip region to the rectangle specified by di.prcBounds
		HRGN hRgnOld = NULL;
		if (GetClipRgn(di.hdcDraw, hRgnOld) != 1)
			hRgnOld = NULL;
		bool bSelectOldRgn = false;

		HRGN hRgnNew = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);

		if (hRgnNew != NULL)
		{
			bSelectOldRgn = (SelectClipRgn(di.hdcDraw, hRgnNew) != ERROR);
		}

		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("WebVoipCtrl");
#ifndef _WIN32_WCE
		TextOut(di.hdcDraw,
			(rc.left + rc.right) / 2,
			(rc.top + rc.bottom) / 2,
			pszText,
			lstrlen(pszText));
#else
		ExtTextOut(di.hdcDraw,
			(rc.left + rc.right) / 2,
			(rc.top + rc.bottom) / 2,
			ETO_OPAQUE,
			NULL,
			pszText,
			ATL::lstrlen(pszText),
			NULL);
#endif

		if (bSelectOldRgn)
			SelectClipRgn(di.hdcDraw, hRgnOld);

		return S_OK;
	}

	STDMETHOD(_InternalQueryService)(REFGUID guidService, REFIID riid, void** ppvObject)
	{
		//return E_NOTIMPL;
		CComPtr<IOleClientSite> pocs;
		GetSite(IID_IOleClientSite,(void**)&pocs);

		CComPtr<IServiceProvider> sp;
		if (m_spUnkSite)
		{
			m_spUnkSite->QueryInterface(IID_IServiceProvider, (void**)&sp);
		}

		if (sp)
		{
			sp->QueryService(guidService, riid,  ppvObject);
		}

		return S_OK;
	}



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		std::string path;
		CTools::getCurrentPath(path);
		std::string strLogCfgFile = path+"\\eSDKClientLogCfg.ini";
		std::string strLogStorePath = path+"\\eSDKWebVoipLog";
		unsigned int logLevel[LOG_CATEGORY] = {INVALID_LOG_LEVEL,INVALID_LOG_LEVEL,INVALID_LOG_LEVEL};
		(void)LogInit(PRODUCT_NAME,strLogCfgFile.c_str(),logLevel,strLogStorePath.c_str());
		NotifyCallBack::m_pCtrl = this;
		return S_OK;
	}

	void FinalRelease()
	{
		LogFini(PRODUCT_NAME);
	}

	STDMETHOD(SetClientSite)(IOleClientSite *pClientSite)   
	{   
		if(pClientSite)   
		{   
			RECT rc = {0,0,0,0};
			//   Don't   have   access   to   the   container's   window   so   just   use   the   
			//   desktop.     Window   will   be   resized   correctly   during   in-place   
			//   activation.   
			if(NULL == m_ATLWnd)
			{
				m_ATLWnd = CreateControlWindow(::GetDesktopWindow(), rc);   
				_ASSERT(m_ATLWnd); 
			}  
		}
		return   IOleObjectImpl<CWebVoipCtrl>::SetClientSite(pClientSite);   
	}

	HRESULT   InPlaceActivate(LONG   iVerb,   const   RECT*   prcPosRect)   
	{
		//Get the container's window. 
		_ASSERT(m_spClientSite);   
		CComPtr<IOleInPlaceSite>  pInPlaceSite;
		HRESULT	hr	=	m_spClientSite->QueryInterface(IID_IOleInPlaceSite, (void **)&pInPlaceSite);   
		if(SUCCEEDED   (hr)   &&   pInPlaceSite)
		{
			HWND   hParent   =   NULL;
			hr   =   pInPlaceSite->GetWindow(&hParent);
			if(SUCCEEDED   (hr)   &&   hParent)
			{
				//Set   container   window   as   our   parent   window   
				SetParent(hParent);   
			}
		}

		return   CComControlBase::InPlaceActivate(iVerb,   prcPosRect);   
	}

	LRESULT OnCallNotify(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	//控件窗口
	HWND m_ATLWnd;

	// SIP服务器地址
	std::string VoipSIPServerIP;
	// SIP服务器端口号。（SIP注册时使用）
	unsigned short VoipSIPServerPort;

	//呼叫信息
	// 呼叫唯一标识
	TUP_UINT32 VoipCallInfo_Id;
	// 呼叫类型
	unsigned short VoipCallInfo_Type;
	// 主叫呼叫状态
	unsigned short VoipCallInfo_CallerStatus;
	// 被叫呼叫状态
	unsigned short VoipCallInfo_CalleeStatus;
	// 主叫号码
	std::string VoipCallInfo_CallerNum;
	// 被叫号码
	std::string VoipCallInfo_CalleeNum;
	// 原始被叫号码
	std::string VoipCallInfo_OrgCalleeNum;
	// 线路ID，共享线功能时使用。普通呼叫时，该参数设为0
	unsigned short VoipCallInfo_LineId;
	// 呼叫线路类型
	unsigned short VoipCallInfo_LineType;

	// 呼叫模式
	unsigned short VoipCallMode;
	// 媒体设备类型
	unsigned short MediaType;

	// 用户信息
	// SIP帐号ID
	std::string VoipUserInfo_Id;
	// SIP帐号用户名
	std::string VoipUserInfo_UserName;
	// SIP帐号密码
	std::string VoipUserInfo_Password;
	// SIP账户号码（本地号码）
	std::string VoipUserInfo_AccNum;
	// SIP帐号状态
	unsigned short VoipUserInfo_AccStatus;
	// 用户SIP电话状态
	unsigned short VoipUserInfo_SipStatus;

	void NotifyVoipLoginResultEvent(unsigned int sip_id, 
		const std::string& sip_username, 
		const std::string& sip_account,
		unsigned short acc_status, 
		unsigned int errorCode);
	void NotifyVoipLogoutResultEvent(bool result, 
		unsigned int errorCode);

	void NotifyVoipCallOutgoingEvent(TUP_UINT32 callId,
		unsigned short callType,
		unsigned short callStatus,
		const std::string& callerName,
		const std::string& callerNum,
		TUP_BOOL isCallIn,
		TUP_BOOL isPeerHangup,
		unsigned int errorCode);

	void NotifyVoipPeerRingbackEvent(TUP_UINT32 callId,
		unsigned short callType,
		unsigned short callStatus,
		const std::string& callerName,
		TUP_BOOL isPeerHangup,
		unsigned int errorCode);

	void NotifyVoipRtpCreatedEvent(TUP_UINT32 callId);
	void NotifyVoipIncomingCallEvent(TUP_UINT32 callId,
		unsigned short callType,
		unsigned short callStatus,
		const std::string& callerName,
		const std::string& callerNum,
		TUP_BOOL isCallIn,
		TUP_BOOL isPeerHangup,
		unsigned int errorCode);

	void NotifyVoipStartTalkingEvent(TUP_UINT32 callId,
		unsigned short callType,
		unsigned short callStatus,
		const std::string& callerName,
		const std::string& callerNum,
		TUP_BOOL isCallIn,
		TUP_BOOL isPeerHangup,
		unsigned int errorCode);

	void NotifyCallCloseResultEvent(TUP_UINT32 callId,
		unsigned short callType,
		unsigned short callStatus,
		const std::string& callerName,
		const std::string& callerNum,
		TUP_BOOL isCallIn,
		TUP_BOOL isPeerHangup,
		unsigned int errorCode
		);

	void NotifyVoipVoiceVideoSwitchResultEvent(TUP_UINT32 callId,TUP_UINT32 ulResult,TUP_BOOL bIsVideo);
	void NotifyVoipVoiceSwitchToVideoReqEvent(TUP_UINT32 callId);
	void NotifyVoipVideoSwitchToVoiceReqEvent(TUP_UINT32 callId);

	void NotifyVoipCallHoldSuccessEvent(TUP_UINT32 callId);
	void NotifyVoipCallHoldFailedEvent(TUP_UINT32 callId);
	void NotifyVoipCallUnHoldSuccessEvent(TUP_UINT32 callId);
	void NotifyVoipCallUnHoldFailedEvent(TUP_UINT32 callId);
	void NotifyVoipCallBlindTransSuccessEvent(TUP_UINT32 callId);
	void NotifyVoipCallBlindTransFailedEvent(TUP_UINT32 callId);
	void NotifyVoipCallConsultTransSuccessEvent(TUP_UINT32 callId);
	void NotifyVoipCallConsultTransFailedEvent(TUP_UINT32 callId);
	void NotifyVoipIPTServiceRegSuccessEvent(unsigned int service);
	void NotifyVoipIPTServiceRegFailedEvent(unsigned int service);
	void NotifyVoipPhoneStatusChangeEvent(TUP_UINT32 callId,
		const std::string& phoneNum,
		unsigned short status);
	void NotifyVoipStartRecordingEvent(TUP_UINT32 callId);
	void NotifyVoipRecordFailedEvent(TUP_UINT32 callId);
	void NotifyVoipUnRecordSuccessEvent(TUP_UINT32 callId);
	void NotifyVoipUnRecordFailedEvent(TUP_UINT32 callId);
	void NotifyVoipJointStartResultEvent();
	void NotifyVoipJointStopResultEvent();
	void NotifyVoipNotifyJointSwitchToPhoneEvent();
	void NotifyVoipNotifyJointSwitchToPCEvent();


private:
	//注册注销事件
	CComPtr<IDispatch> m_VoipLoginResultEvent;		//登录注册结果
	CComPtr<IDispatch> m_VoipLogoutResultEvent;		//登录注销结果
	//普通呼叫事件
	CComPtr<IDispatch> m_VoipCallOutgoingEvent;		//呼叫已发出
	CComPtr<IDispatch> m_VoipPeerRingbackEvent;		//对方振铃
	CComPtr<IDispatch> m_VoipRtpCreatedEvent;		//RTP通道建立
	CComPtr<IDispatch> m_VoipIncomingCallEvent;		//来电通知
	CComPtr<IDispatch> m_VoipStartTalkingEvent;		//开始通话
	CComPtr<IDispatch> m_VoipCallCloseResultEvent;	//关闭呼叫结果
	//视频呼叫事件
	CComPtr<IDispatch> m_VoipVoiceVideoSwitchResultEvent;			//音视频转换结果
	CComPtr<IDispatch> m_VoipNotifyVoiceSwitchToVideoReqEvent;		//语音转换视频请求通知
	CComPtr<IDispatch> m_VoipNotifyVideoSwitchToVoiceReqEvent;		//视频转换语音请求通知
	//呼叫管理事件
	CComPtr<IDispatch> m_VoipCallHoldSuccessEvent;			//保持成功
	CComPtr<IDispatch> m_VoipCallHoldFailedEvent;			//保持失败
	CComPtr<IDispatch> m_VoipCallUnHoldSuccessEvent;		//取消保持成功
	CComPtr<IDispatch> m_VoipCallUnHoldFailedEvent;			//取消保持失败
	CComPtr<IDispatch> m_VoipCallBlindTransSuccessEvent;	//呼叫盲转成功
	CComPtr<IDispatch> m_VoipCallBlindTransFailedEvent;		//呼叫盲转失败
	CComPtr<IDispatch> m_VoipCallConsultTransSuccessEvent;	//呼叫咨询转成功
	CComPtr<IDispatch> m_VoipCallConsultTransFailedEvent;	//呼叫咨询转失败
	CComPtr<IDispatch> m_VoipIPTServiceRegSuccessEvent;		//IPT服务登记成功
	CComPtr<IDispatch> m_VoipIPTServiceRegFailedEvent;		//IPT服务登记失败

	//状态呈现事件
	CComPtr<IDispatch> m_VoipPhoneStatusChangeEvent;		//电话状态变化通知
	//录音管理事件
	CComPtr<IDispatch> m_VoipStartRecordingEvent;		//开始录音
	CComPtr<IDispatch> m_VoipRecordFailedEvent;			//启动录音失败
	CComPtr<IDispatch> m_VoipUnRecordSuccessEvent;		//停止录音成功
	CComPtr<IDispatch> m_VoipUnRecordFailedEvent;		//停止录音失败

	//联动控制事件
	CComPtr<IDispatch> m_VoipJointStartResultEvent;			//联动开启结果
	CComPtr<IDispatch> m_VoipJointStopResultEvent;			//联动关闭结果
	CComPtr<IDispatch> m_VoipNotifyJointSwitchToPhoneEvent;	//联动语音切换至话机通知
	CComPtr<IDispatch> m_VoipNotifyJointSwitchToPCEvent;	//联动语音切换至PC通知
public:
	STDMETHOD(WebVoipInitialize)(void);
	STDMETHOD(WebVoipUninitialize)(void);
	STDMETHOD(WebVoipLogin)(void);
	STDMETHOD(WebVoipLogout)(void);	
	STDMETHOD(WebVoipCall)(BSTR phoneNum, USHORT callType, SHORT* ret);	
	STDMETHOD(WebVoipHangup)(SHORT* ret);
	STDMETHOD(WebVoipCallRingAlert)(SHORT* ret);
	STDMETHOD(WebVoipAccept)(USHORT callMode, SHORT* ret);
	STDMETHOD(WebVoipReject)(SHORT* ret);
	STDMETHOD(WebVoipIsEnableVideo)(VARIANT_BOOL isEnable, SHORT* ret);
	STDMETHOD(WebVoipEnableVideoReply)(VARIANT_BOOL isAccept, SHORT* ret);
	STDMETHOD(WebVoipDisableVideoReply)(VARIANT_BOOL isAccept, SHORT* ret);
	STDMETHOD(WebVoipSetLocalVideoWindow)(unsigned long wndhandle, unsigned short wndType, unsigned long pos_x, unsigned long pos_y, unsigned long pos_w, unsigned long pos_h ,SHORT* ret);
	STDMETHOD(WebVoipDMTFSecondDial)(BSTR strKey, SHORT* ret);
	STDMETHOD(WebVoipCallHold)(VARIANT_BOOL isHold, SHORT* ret);
	STDMETHOD(WebVoipCallBlindTransfer)(BSTR transToNum, SHORT* ret);
	STDMETHOD(WebVoipCallConsultTransfer)(SHORT* ret);
	STDMETHOD(WebVoipCallDivertTransfer)(BSTR divertToNum, SHORT* ret);
	STDMETHOD(WebVoipSetCallForward)(unsigned int service,BSTR divertToNum,SHORT* ret);
	STDMETHOD(WebVoipSetCallDND)(unsigned int service, SHORT* ret);
	STDMETHOD(WebVoipSetCallACB)(unsigned int service, SHORT* ret);
	STDMETHOD(WebVoipSetMediaMute)(unsigned short media, VARIANT_BOOL isMute, SHORT* ret);
	STDMETHOD(WebVoipSetCurrMediaVolume)(unsigned short media, unsigned int volume, SHORT* ret);
	STDMETHOD(WebVoipGetCurrMediaVolume)(unsigned short media, unsigned int* volume);
	STDMETHOD(WebVoipSetMediaDevice)(unsigned short media, unsigned int index, SHORT* ret);
	STDMETHOD(WebVoipGetMediaDevice)(unsigned short media, unsigned int* count, BSTR* deviceInfo);
	STDMETHOD(WebVoipChangeUserPhoneStatus)(unsigned short sip_status, SHORT* ret);
	STDMETHOD(WebVoipAudioRecord)(VARIANT_BOOL isOnRecord, SHORT* ret);
	STDMETHOD(WebVoipJointSetting)(BSTR linkage_number, SHORT* ret);
	STDMETHOD(WebVoipPhoneJoint)(VARIANT_BOOL isJoint, SHORT* ret);
	STDMETHOD(WebVoipJointSwitch)(SHORT* ret);
	STDMETHOD(WebVoipGetLastError)(unsigned int errornum, BSTR* errDesc);
	STDMETHOD(get_VoipLoginResultEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipLoginResultEvent)(VARIANT newVal);
	STDMETHOD(get_VoipLogoutResultEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipLogoutResultEvent)(VARIANT newVal);
	STDMETHOD(get_VoipCallOutgoingEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipCallOutgoingEvent)(VARIANT newVal);
	STDMETHOD(get_VoipPeerRingbackEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipPeerRingbackEvent)(VARIANT newVal);
	STDMETHOD(get_VoipRtpCreatedEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipRtpCreatedEvent)(VARIANT newVal);
	STDMETHOD(get_VoipIncomingCallEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipIncomingCallEvent)(VARIANT newVal);
	STDMETHOD(get_VoipStartTalkingEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipStartTalkingEvent)(VARIANT newVal);
	STDMETHOD(get_VoipCallCloseResultEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipCallCloseResultEvent)(VARIANT newVal);
	STDMETHOD(get_VoipVoiceVideoSwitchResultEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipVoiceVideoSwitchResultEvent)(VARIANT newVal);
	STDMETHOD(get_VoipNotifyVoiceSwitchToVideoReqEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipNotifyVoiceSwitchToVideoReqEvent)(VARIANT newVal);
	STDMETHOD(get_VoipNotifyVideoSwitchToVoiceReqEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipNotifyVideoSwitchToVoiceReqEvent)(VARIANT newVal);
	STDMETHOD(get_VoipCallHoldSuccessEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipCallHoldSuccessEvent)(VARIANT newVal);
	STDMETHOD(get_VoipCallHoldFailedEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipCallHoldFailedEvent)(VARIANT newVal);
	STDMETHOD(get_VoipCallUnHoldSuccessEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipCallUnHoldSuccessEvent)(VARIANT newVal);
	STDMETHOD(get_VoipCallUnHoldFailedEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipCallUnHoldFailedEvent)(VARIANT newVal);
	STDMETHOD(get_VoipCallBlindTransSuccessEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipCallBlindTransSuccessEvent)(VARIANT newVal);
	STDMETHOD(get_VoipCallBlindTransFailedEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipCallBlindTransFailedEvent)(VARIANT newVal);
	STDMETHOD(get_VoipCallConsultTransSuccessEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipCallConsultTransSuccessEvent)(VARIANT newVal);
	STDMETHOD(get_VoipCallConsultTransFailedEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipCallConsultTransFailedEvent)(VARIANT newVal);
	STDMETHOD(get_VoipIPTServiceRegSuccessEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipIPTServiceRegSuccessEvent)(VARIANT newVal);
	STDMETHOD(get_VoipIPTServiceRegFailedEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipIPTServiceRegFailedEvent)(VARIANT newVal);
	STDMETHOD(get_VoipPhoneStatusChangeEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipPhoneStatusChangeEvent)(VARIANT newVal);
	STDMETHOD(get_VoipStartRecordingEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipStartRecordingEvent)(VARIANT newVal);
	STDMETHOD(get_VoipRecordFailedEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipRecordFailedEvent)(VARIANT newVal);
	STDMETHOD(get_VoipUnRecordSuccessEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipUnRecordSuccessEvent)(VARIANT newVal);
	STDMETHOD(get_VoipUnRecordFailedEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipUnRecordFailedEvent)(VARIANT newVal);
	STDMETHOD(get_VoipJointStartResultEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipJointStartResultEvent)(VARIANT newVal);
	STDMETHOD(get_VoipJointStopResultEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipJointStopResultEvent)(VARIANT newVal);
	STDMETHOD(get_VoipNotifyJointSwitchToPhoneEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipNotifyJointSwitchToPhoneEvent)(VARIANT newVal);
	STDMETHOD(get_VoipNotifyJointSwitchToPCEvent)(VARIANT* pVal);
	STDMETHOD(put_VoipNotifyJointSwitchToPCEvent)(VARIANT newVal);
	STDMETHOD(get_VoipSIPServerIP)(VARIANT* pVal);
	STDMETHOD(put_VoipSIPServerIP)(VARIANT newVal);
	STDMETHOD(get_VoipSIPServerPort)(VARIANT* pVal);
	STDMETHOD(put_VoipSIPServerPort)(VARIANT newVal);
	STDMETHOD(get_VoipCallInfo_Id)(VARIANT* pVal);
	STDMETHOD(put_VoipCallInfo_Id)(VARIANT newVal);
	STDMETHOD(get_VoipCallInfo_Type)(VARIANT* pVal);
	STDMETHOD(put_VoipCallInfo_Type)(VARIANT newVal);
	STDMETHOD(get_VoipCallInfo_CallerStatus)(VARIANT* pVal);
	STDMETHOD(put_VoipCallInfo_CallerStatus)(VARIANT newVal);
	STDMETHOD(get_VoipCallInfo_CalleeStatus)(VARIANT* pVal);
	STDMETHOD(put_VoipCallInfo_CalleeStatus)(VARIANT newVal);
	STDMETHOD(get_VoipCallInfo_CallerNum)(VARIANT* pVal);
	STDMETHOD(put_VoipCallInfo_CallerNum)(VARIANT newVal);
	STDMETHOD(get_VoipCallInfo_CalleeNum)(VARIANT* pVal);
	STDMETHOD(put_VoipCallInfo_CalleeNum)(VARIANT newVal);
	STDMETHOD(get_VoipCallInfo_OrgCalleeNum)(VARIANT* pVal);
	STDMETHOD(put_VoipCallInfo_OrgCalleeNum)(VARIANT newVal);
	STDMETHOD(get_VoipCallInfo_LineId)(VARIANT* pVal);
	STDMETHOD(put_VoipCallInfo_LineId)(VARIANT newVal);
	STDMETHOD(get_VoipCallInfo_LineType)(VARIANT* pVal);
	STDMETHOD(put_VoipCallInfo_LineType)(VARIANT newVal);
	STDMETHOD(get_VoipCallMode)(VARIANT* pVal);
	STDMETHOD(put_VoipCallMode)(VARIANT newVal);
	STDMETHOD(get_MediaType)(VARIANT* pVal);
	STDMETHOD(put_MediaType)(VARIANT newVal);
	STDMETHOD(get_VoipUserInfo_Id)(VARIANT* pVal);
	STDMETHOD(put_VoipUserInfo_Id)(VARIANT newVal);
	STDMETHOD(get_VoipUserInfo_UserName)(VARIANT* pVal);
	STDMETHOD(put_VoipUserInfo_UserName)(VARIANT newVal);
	STDMETHOD(get_VoipUserInfo_Password)(VARIANT* pVal);
	STDMETHOD(put_VoipUserInfo_Password)(VARIANT newVal);
	STDMETHOD(get_VoipUserInfo_AccNum)(VARIANT* pVal);
	STDMETHOD(put_VoipUserInfo_AccNum)(VARIANT newVal);
	STDMETHOD(get_VoipUserInfo_AccStatus)(VARIANT* pVal);
	STDMETHOD(put_VoipUserInfo_AccStatus)(VARIANT newVal);
	STDMETHOD(get_VoipUserInfo_SipStatus)(VARIANT* pVal);
	STDMETHOD(put_VoipUserInfo_SipStatus)(VARIANT newVal);
};

OBJECT_ENTRY_AUTO(__uuidof(WebVoipCtrl), CWebVoipCtrl)
