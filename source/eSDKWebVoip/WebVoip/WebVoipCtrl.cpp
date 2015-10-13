// WebVoipCtrl.cpp : Implementation of CWebVoipCtrl
#include "stdafx.h"
#include "WebVoipCtrl.h"
#include "comutil.h"


#define USER_AGENT				"Huawei SoftCoPCA"//其他任何字段，softco都不认
// CWebVoipCtrl

string GetLocalIPAddress()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	char name[255];
	string ip;
	PHOSTENT hostinfo;
	wVersionRequested = MAKEWORD( 2, 0 );
	if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
	{
		if( gethostname ( name, sizeof(name)) == 0)
		{
			if((hostinfo = gethostbyname(name)) != NULL)
			{
				ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
			}
		}
		WSACleanup();
	}
	return ip;
}

void CWebVoipCtrl::NotifyVoipLoginResultEvent(unsigned int sip_id, const std::string& sip_username, const std::string& sip_account, unsigned short acc_status, unsigned int errorCode)
{
	LOG_INFO("sip_id = %d",sip_id);
	CComVariant varResult;
	CComVariant avarParams[5];
	avarParams[4] = sip_id;       
	avarParams[4].vt = VT_UINT;
	avarParams[3] = CTools::UTF2UNICODE(sip_username.c_str()).c_str();        
	avarParams[3].vt = VT_BSTR;
	avarParams[2] = CTools::UTF2UNICODE(sip_account.c_str()).c_str();          
	avarParams[2].vt = VT_BSTR;
	avarParams[1] = acc_status;       
	avarParams[1].vt = VT_UI2;
	avarParams[0] = errorCode;       
	avarParams[0].vt = VT_UINT;

	DISPPARAMS params = { avarParams, NULL, 5, 0 };
	try
	{
		if(NULL != m_VoipLoginResultEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipLoginResultEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipLoginResultEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipLoginResultEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipLoginResultEvent Failed,exception");
	}
}

void CWebVoipCtrl::NotifyVoipLogoutResultEvent(bool result, unsigned int errorCode)
{
	LOG_INFO("errorCode = %d",errorCode);
	CComVariant varResult;
	CComVariant avarParams[2];
	if(result)
	{
		unsigned int i = 1;
		avarParams[1] = i;       
		avarParams[1].vt = VT_UINT;
	}
	else
	{
		unsigned int i = 0;
		avarParams[1] = i;       
		avarParams[1].vt = VT_UINT;
	}

	avarParams[0] = errorCode;       
	avarParams[0].vt = VT_UINT;

	DISPPARAMS params = { avarParams, NULL, 2, 0 };
	try
	{
		if(NULL != m_VoipLogoutResultEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipLogoutResultEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipLogoutResultEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipLogoutResultEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipLogoutResultEvent Failed,exception");
	}
}
void CWebVoipCtrl::NotifyVoipCallOutgoingEvent(TUP_UINT32 callId,
	unsigned short callType,
	unsigned short callStatus,
	const std::string& callerName,
	const std::string& callerNum,
	TUP_BOOL isCallIn,
	TUP_BOOL isPeerHangup,
	unsigned int errorCode)
{
	LOG_INFO("NotifyVoipCallOutgoingEvent:callId=%d,callType=%d,callStatus=%d,callerName=%s,callerNum=%s,isCallIn=%d,isPeerHangup=%d,code=%d",
		callId,
		callType,
		callStatus,
		CTools::UTF2UNICODE(callerName).c_str(),
		callerNum.c_str(),
		isCallIn,
		isPeerHangup,
		errorCode);

	CComVariant varResult;
	CComVariant avarParams[8];

	avarParams[7] = callId;       
	avarParams[7].vt = VT_UINT;
	avarParams[6] = callType;       
	avarParams[6].vt = VT_UI2;
	avarParams[5] = callStatus;       
	avarParams[5].vt = VT_UI2;

	avarParams[4] = CTools::UTF2UNICODE(callerName.c_str()).c_str();;       
	avarParams[4].vt = VT_BSTR;
	avarParams[3] = CTools::UTF2UNICODE(callerNum.c_str()).c_str();;       
	avarParams[3].vt = VT_BSTR;

	if(isCallIn)
	{
		avarParams[2] = TRUE;       
		avarParams[2].vt = VT_UI2;
	}
	else
	{
		avarParams[2] = FALSE;       
		avarParams[2].vt = VT_UI2;
	}
	if(isPeerHangup)
	{
		avarParams[1] = TRUE;       
		avarParams[1].vt = VT_UI2;
	}
	else
	{
		avarParams[1] = FALSE;       
		avarParams[1].vt = VT_UI2;
	}
	avarParams[0] = errorCode;       
	avarParams[0].vt = VT_UINT;

	DISPPARAMS params = { avarParams, NULL, 8, 0 };
	try
	{
		if(NULL != m_VoipCallOutgoingEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipCallOutgoingEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipCallOutgoingEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipCallOutgoingEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipCallOutgoingEvent Failed,exception");
	}
}

void CWebVoipCtrl::NotifyVoipPeerRingbackEvent(TUP_UINT32 callId,
	unsigned short callType,
	unsigned short callStatus,
	const std::string& callerName,
	TUP_BOOL isPeerHangup,
	unsigned int errorCode)
{
	LOG_INFO("NotifyVoipPeerRingbackEvent:callId=%d,callType=%d,callStatus=%d,callerName=%s,isPeerHangup=%d,code=%d",
		callId,
		callType,
		callStatus,
		CTools::UTF2UNICODE(callerName).c_str(),
		isPeerHangup,
		errorCode);
	CComVariant varResult;
	CComVariant avarParams[6];

	avarParams[5] = callId;       
	avarParams[5].vt = VT_UINT;
	avarParams[4] = callType;       
	avarParams[4].vt = VT_UI2;
	avarParams[3] = callStatus;       
	avarParams[3].vt = VT_UI2;
	avarParams[2] = CTools::UTF2UNICODE(callerName.c_str()).c_str();;       
	avarParams[2].vt = VT_BSTR;

	if(isPeerHangup)
	{
		avarParams[1] = TRUE;       
		avarParams[1].vt = VT_UI2;
	}
	else
	{
		avarParams[1] = FALSE;       
		avarParams[1].vt = VT_UI2;
	}
	avarParams[0] = errorCode;       
	avarParams[0].vt = VT_UINT;

	DISPPARAMS params = { avarParams, NULL, 6, 0 };
	try
	{
		if(NULL != m_VoipPeerRingbackEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipPeerRingbackEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipPeerRingbackEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipPeerRingbackEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipPeerRingbackEvent Failed,exception");
	}
}

void CWebVoipCtrl::NotifyVoipRtpCreatedEvent(TUP_UINT32 callId)
{
	LOG_INFO("NotifyVoipRtpCreatedEvent:callId = %d",callId);
	CComVariant varResult;
	CComVariant avarParams[1];

	avarParams[0] = callId;       
	avarParams[0].vt = VT_UI4;

	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	try
	{
		if(NULL != m_VoipRtpCreatedEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipRtpCreatedEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipRtpCreatedEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipRtpCreatedEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipRtpCreatedEvent Failed,exception");
	}

}
void CWebVoipCtrl::NotifyVoipIncomingCallEvent(TUP_UINT32 callId,
	unsigned short callType,
	unsigned short callStatus,
	const std::string& callerName,
	const std::string& callerNum,
	TUP_BOOL isCallIn,
	TUP_BOOL isPeerHangup,
	unsigned int errorCode)
{
	LOG_INFO("NotifyVoipIncomingCallEvent:callId=%d,callType=%d,callStatus=%d,callerName=%s,callerNum=%s,isCallIn=%d,isPeerHangup=%d,code=%d",
		callId,
		callType,
		callStatus,
		CTools::UTF2UNICODE(callerName).c_str(),
		callerNum.c_str(),
		isCallIn,
		isPeerHangup,
		errorCode);

	CComVariant varResult;
	CComVariant avarParams[8];

	avarParams[7] = callId;       
	avarParams[7].vt = VT_UINT;
	avarParams[6] = callType;       
	avarParams[6].vt = VT_UI2;
	avarParams[5] = callStatus;       
	avarParams[5].vt = VT_UI2;
	avarParams[4] = CTools::UTF2UNICODE(callerName.c_str()).c_str();;       
	avarParams[4].vt = VT_BSTR;
	avarParams[3] = CTools::UTF2UNICODE(callerNum.c_str()).c_str();;       
	avarParams[3].vt = VT_BSTR;
	if(isCallIn)
	{
		avarParams[2] = TRUE;       
		avarParams[2].vt = VT_UI2;
	}
	else
	{
		avarParams[2] = FALSE;       
		avarParams[2].vt = VT_UI2;
	}
	if(isPeerHangup)
	{
		avarParams[1] = TRUE;       
		avarParams[1].vt = VT_UI2;
	}
	else
	{
		avarParams[1] = FALSE;       
		avarParams[1].vt = VT_UI2;
	}
	avarParams[0] = errorCode;       
	avarParams[0].vt = VT_UINT;

	DISPPARAMS params = { avarParams, NULL, 8, 0 };
	try
	{
		if(NULL != m_VoipIncomingCallEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipIncomingCallEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipIncomingCallEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipIncomingCallEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipIncomingCallEvent Failed,exception");
	}
}

void CWebVoipCtrl::NotifyVoipStartTalkingEvent(TUP_UINT32 callId,
	unsigned short callType,
	unsigned short callStatus,
	const std::string& callerName,
	const std::string& callerNum,
	TUP_BOOL isCallIn,
	TUP_BOOL isPeerHangup,
	unsigned int errorCode)
{
	LOG_INFO("NotifyVoipStartTalkingEvent:callId=%d,callType=%d,callStatus=%d,callerName=%s,callerNum=%s,isCallIn=%d,isPeerHangup=%d,code=%d",
		callId,
		callType,
		callStatus,
		CTools::UTF2UNICODE(callerName).c_str(),
		callerNum.c_str(),
		isCallIn,
		isPeerHangup,
		errorCode);
	CComVariant varResult;
	CComVariant avarParams[8];

	avarParams[7] = callId;       
	avarParams[7].vt = VT_UINT;
	avarParams[6] = callType;       
	avarParams[6].vt = VT_UI2;
	avarParams[5] = callStatus;       
	avarParams[5].vt = VT_UI2;
	avarParams[4] = CTools::UTF2UNICODE(callerName.c_str()).c_str();;       
	avarParams[4].vt = VT_BSTR;
	avarParams[3] = CTools::UTF2UNICODE(callerNum.c_str()).c_str();;       
	avarParams[3].vt = VT_BSTR;
	if(isCallIn)
	{
		avarParams[2] = TRUE;       
		avarParams[2].vt = VT_UI2;
	}
	else
	{
		avarParams[2] = FALSE;       
		avarParams[2].vt = VT_UI2;
	}
	if(isPeerHangup)
	{
		avarParams[1] = TRUE;       
		avarParams[1].vt = VT_UI2;
	}
	else
	{
		avarParams[1] = FALSE;       
		avarParams[1].vt = VT_UI2;
	}
	avarParams[0] = errorCode;       
	avarParams[0].vt = VT_UINT;

	DISPPARAMS params = { avarParams, NULL, 8, 0 };
	try
	{
		if(NULL != m_VoipStartTalkingEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipStartTalkingEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipStartTalkingEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipStartTalkingEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipStartTalkingEvent Failed,exception");
	}
}

void CWebVoipCtrl::NotifyCallCloseResultEvent(TUP_UINT32 callId,
	unsigned short callType,
	unsigned short callStatus,
	const std::string& callerName,
	const std::string& callerNum,
	TUP_BOOL isCallIn,
	TUP_BOOL isPeerHangup,
	unsigned int errorCode
	)
{
	LOG_INFO("NotifyCallCloseResultEvent:callId=%d,callType=%d,callStatus=%d,callerName=%s,callerNum=%s,isCallIn=%d,isPeerHangup=%d,code=%d",
		callId,
		callType,
		callStatus,
		CTools::UTF2UNICODE(callerName).c_str(),
		callerNum.c_str(),
		isCallIn,
		isPeerHangup,
		errorCode);

	CComVariant varResult;
	CComVariant avarParams[8];

	avarParams[7] = callId;       
	avarParams[7].vt = VT_UINT;
	avarParams[6] = callType;       
	avarParams[6].vt = VT_UI2;
	avarParams[5] = callStatus;       
	avarParams[5].vt = VT_UI2;
	avarParams[4] = CTools::UTF2UNICODE(callerName.c_str()).c_str();;       
	avarParams[4].vt = VT_BSTR;
	avarParams[3] = CTools::UTF2UNICODE(callerNum.c_str()).c_str();;       
	avarParams[3].vt = VT_BSTR;
	if(isCallIn)
	{
		avarParams[2] = TRUE;       
		avarParams[2].vt = VT_UI2;
	}
	else
	{
		avarParams[2] = FALSE;       
		avarParams[2].vt = VT_UI2;
	}
	if(isPeerHangup)
	{
		avarParams[1] = TRUE;       
		avarParams[1].vt = VT_UI2;
	}
	else
	{
		avarParams[1] = FALSE;       
		avarParams[1].vt = VT_UI2;
	}
	avarParams[0] = errorCode;       
	avarParams[0].vt = VT_UINT;

	DISPPARAMS params = { avarParams, NULL, 8, 0 };
	try
	{
		if(NULL != m_VoipCallCloseResultEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipCallCloseResultEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyCallCloseResultEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyCallCloseResultEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyCallCloseResultEvent Failed,exception");
	}
}
void CWebVoipCtrl::NotifyVoipVoiceVideoSwitchResultEvent(TUP_UINT32 callId,TUP_UINT32 ulResult,TUP_BOOL bIsVideo)
{
	LOG_INFO("NotifyVoipVoiceVideoSwitchResultEvent,callId = %d",callId);
	CComVariant varResult;
	CComVariant avarParams[3];

	avarParams[2] = callId;       
	avarParams[2].vt = VT_UI4;
	avarParams[1] = ulResult;       
	avarParams[1].vt = VT_UI4;
	if(bIsVideo)
	{
		avarParams[0] = TRUE;       
		avarParams[0].vt = VT_UI2;
	}
	else
	{
		avarParams[0] = FALSE;       
		avarParams[0].vt = VT_UI2;
	}

	DISPPARAMS params = { avarParams, NULL, 3, 0 };
	try
	{
		if(NULL != m_VoipVoiceVideoSwitchResultEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipVoiceVideoSwitchResultEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipVoiceVideoSwitchResultEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipVoiceVideoSwitchResultEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipVoiceVideoSwitchResultEvent Failed,exception");
	}
}
void CWebVoipCtrl::NotifyVoipVoiceSwitchToVideoReqEvent(TUP_UINT32 callId)
{
	LOG_INFO("NotifyVoipVoiceSwitchToVideoReqEvent,callId = %d",callId);
	CComVariant varResult;
	CComVariant avarParams[1];

	avarParams[0] = callId;       
	avarParams[0].vt = VT_UI4;

	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	try
	{
		if(NULL != m_VoipNotifyVoiceSwitchToVideoReqEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipNotifyVoiceSwitchToVideoReqEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipVoiceSwitchToVideoReqEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipVoiceSwitchToVideoReqEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipVoiceSwitchToVideoReqEvent Failed,exception");
	}
}
void CWebVoipCtrl::NotifyVoipVideoSwitchToVoiceReqEvent(TUP_UINT32 callId)
{
	LOG_INFO("NotifyVideoSwitchToVoiceReqEvent,callId = %d",callId);
	CComVariant varResult;
	CComVariant avarParams[1];

	avarParams[0] = callId;       
	avarParams[0].vt = VT_UI4;

	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	try
	{
		if(NULL != m_VoipNotifyVideoSwitchToVoiceReqEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipNotifyVideoSwitchToVoiceReqEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVideoSwitchToVoiceReqEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVideoSwitchToVoiceReqEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVideoSwitchToVoiceReqEvent Failed,exception");
	}
}
void CWebVoipCtrl::NotifyVoipCallHoldSuccessEvent(TUP_UINT32 callId)
{
	LOG_INFO("NotifyVoipCallHoldSuccessEvent,callId = %d",callId);
	CComVariant varResult;
	CComVariant avarParams[1];

	avarParams[0] = callId;       
	avarParams[0].vt = VT_UI4;

	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	try
	{
		if(NULL != m_VoipCallHoldSuccessEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipCallHoldSuccessEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipCallHoldSuccessEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipCallHoldSuccessEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipCallHoldSuccessEvent Failed,exception");
	}
}
void CWebVoipCtrl::NotifyVoipCallHoldFailedEvent(TUP_UINT32 callId)
{
	LOG_INFO("NotifyVoipCallHoldFailedEvent,callId = %d",callId);
	CComVariant varResult;
	CComVariant avarParams[1];

	avarParams[0] = callId;       
	avarParams[0].vt = VT_UI4;

	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	try
	{
		if(NULL != m_VoipCallHoldFailedEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipCallHoldFailedEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipCallHoldFailedEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipCallHoldFailedEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipCallHoldFailedEvent Failed,exception");
	}
}
void CWebVoipCtrl::NotifyVoipCallUnHoldSuccessEvent(TUP_UINT32 callId)
{
	LOG_INFO("NotifyVoipCallUnHoldSuccessEvent,callId = %d",callId);
	CComVariant varResult;
	CComVariant avarParams[1];

	avarParams[0] = callId;       
	avarParams[0].vt = VT_UI4;

	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	try
	{
		if(NULL != m_VoipCallUnHoldSuccessEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipCallUnHoldSuccessEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipCallUnHoldSuccessEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipCallUnHoldSuccessEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipCallUnHoldSuccessEvent Failed,exception");
	}
}
void CWebVoipCtrl::NotifyVoipCallUnHoldFailedEvent(TUP_UINT32 callId)
{
	LOG_INFO("NotifyVoipCallUnHoldFailedEvent,callId = %d",callId);
	CComVariant varResult;
	CComVariant avarParams[1];

	avarParams[0] = callId;       
	avarParams[0].vt = VT_UI4;

	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	try
	{
		if(NULL != m_VoipCallUnHoldFailedEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipCallUnHoldFailedEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipCallUnHoldFailedEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipCallUnHoldFailedEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipCallUnHoldFailedEvent Failed,exception");
	}
}
void CWebVoipCtrl::NotifyVoipCallBlindTransSuccessEvent(TUP_UINT32 callId)
{
	LOG_INFO("NotifyVoipCallBlindTransSuccessEvent,callId = %d",callId);
	CComVariant varResult;
	CComVariant avarParams[1];

	avarParams[0] = callId;       
	avarParams[0].vt = VT_UI4;

	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	try
	{
		if(NULL != m_VoipCallBlindTransSuccessEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipCallBlindTransSuccessEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipCallBlindTransSuccessEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipCallBlindTransSuccessEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipCallBlindTransSuccessEvent Failed,exception");
	}
}
void CWebVoipCtrl::NotifyVoipCallBlindTransFailedEvent(TUP_UINT32 callId)
{
	LOG_INFO("NotifyVoipCallBlindTransFailedEvent,callId = %d",callId);
	CComVariant varResult;
	CComVariant avarParams[1];

	avarParams[0] = callId;       
	avarParams[0].vt = VT_UI4;

	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	try
	{
		if(NULL != m_VoipCallBlindTransFailedEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipCallBlindTransFailedEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipCallBlindTransFailedEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipCallBlindTransFailedEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipCallBlindTransFailedEvent Failed,exception");
	}
}
void CWebVoipCtrl::NotifyVoipCallConsultTransSuccessEvent(TUP_UINT32 callId)
{
	LOG_INFO("NotifyVoipCallConsultTransSuccessEvent,callId = %d",callId);
	CComVariant varResult;
	CComVariant avarParams[1];

	avarParams[0] = callId;       
	avarParams[0].vt = VT_UI4;

	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	try
	{
		if(NULL != m_VoipCallConsultTransSuccessEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipCallConsultTransSuccessEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipCallConsultTransSuccessEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipCallConsultTransSuccessEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipCallConsultTransSuccessEvent Failed,exception");
	}
}
void CWebVoipCtrl::NotifyVoipCallConsultTransFailedEvent(TUP_UINT32 callId)
{
	LOG_INFO("NotifyVoipCallConsultTransFailedEvent,callId = %d",callId);
	CComVariant varResult;
	CComVariant avarParams[1];

	avarParams[0] = callId;       
	avarParams[0].vt = VT_UI4;

	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	try
	{
		if(NULL != m_VoipCallConsultTransFailedEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipCallConsultTransFailedEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipCallConsultTransFailedEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipCallConsultTransFailedEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipCallUnHoldFailedEvent Failed,exception");
	}
}
void CWebVoipCtrl::NotifyVoipIPTServiceRegSuccessEvent(unsigned int service)
{
	LOG_INFO("NotifyVoipIPTServiceRegSuccessEvent,service = %d",service);
	CComVariant varResult;
	CComVariant avarParams[1];

	avarParams[0] = service;       
	avarParams[0].vt = VT_UI4;

	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	try
	{
		if(NULL != m_VoipIPTServiceRegSuccessEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipIPTServiceRegSuccessEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipIPTServiceRegSuccessEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipIPTServiceRegSuccessEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipIPTServiceRegSuccessEvent Failed,exception");
	}
}
void CWebVoipCtrl::NotifyVoipIPTServiceRegFailedEvent(unsigned int service)
{
	LOG_INFO("NotifyIPTServiceRegFailedEvent,service = %d",service);
	CComVariant varResult;
	CComVariant avarParams[1];

	avarParams[0] = service;       
	avarParams[0].vt = VT_UI4;

	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	try
	{
		if(NULL != m_VoipIPTServiceRegFailedEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipIPTServiceRegFailedEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipIPTServiceRegFailedEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipIPTServiceRegFailedEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipIPTServiceRegFailedEvent Failed,exception");
	}
}
void CWebVoipCtrl::NotifyVoipPhoneStatusChangeEvent(TUP_UINT32 callId,
	const std::string& phoneNum,
	unsigned short status)
{
	LOG_INFO("NotifyVoipPhoneStatusChangeEvent,callId = %d",callId);
}
void CWebVoipCtrl::NotifyVoipStartRecordingEvent(TUP_UINT32 callId)
{
	LOG_INFO("NotifyVoipStartRecordingEvent,callId = %d",callId);
	CComVariant varResult;
	CComVariant avarParams[1];

	avarParams[0] = callId;       
	avarParams[0].vt = VT_UI4;

	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	try
	{
		if(NULL != m_VoipStartRecordingEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipStartRecordingEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipStartRecordingEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipStartRecordingEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipCallUnHoldFailedEvent Failed,exception");
	}
}
void CWebVoipCtrl::NotifyVoipRecordFailedEvent(TUP_UINT32 callId)
{
	LOG_INFO("NotifyVoipRecordFailedEvent,callId = %d",callId);
	CComVariant varResult;
	CComVariant avarParams[1];

	avarParams[0] = callId;       
	avarParams[0].vt = VT_UI4;

	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	try
	{
		if(NULL != m_VoipRecordFailedEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipRecordFailedEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipRecordFailedEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipRecordFailedEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipRecordFailedEvent Failed,exception");
	}
}
void CWebVoipCtrl::NotifyVoipUnRecordSuccessEvent(TUP_UINT32 callId)
{
	LOG_INFO("NotifyVoipUnRecordSuccessEvent,callId = %d",callId);
	CComVariant varResult;
	CComVariant avarParams[1];

	avarParams[0] = callId;       
	avarParams[0].vt = VT_UI4;

	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	try
	{
		if(NULL != m_VoipUnRecordSuccessEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipUnRecordSuccessEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipUnRecordSuccessEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipUnRecordSuccessEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipUnRecordSuccessEvent Failed,exception");
	}
}
void CWebVoipCtrl::NotifyVoipUnRecordFailedEvent(TUP_UINT32 callId)
{
	LOG_INFO("NotifyVoipUnRecordFailedEvent,callId = %d",callId);
	CComVariant varResult;
	CComVariant avarParams[1];

	avarParams[0] = callId;       
	avarParams[0].vt = VT_UI4;

	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	try
	{
		if(NULL != m_VoipUnRecordFailedEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipUnRecordFailedEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipUnRecordFailedEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipUnRecordFailedEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipUnRecordFailedEvent Failed,exception");
	}
}
void CWebVoipCtrl::NotifyVoipJointStartResultEvent()
{
	LOG_INFO("NotifyVoipJointStartResultEvent");
	CComVariant varResult;
	CComVariant avarParams[1];
	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	try
	{
		if(NULL != m_VoipJointStartResultEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipJointStartResultEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipJointStartResultEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipJointStartResultEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipJointStartResultEvent Failed,exception");
	}
}
void CWebVoipCtrl::NotifyVoipJointStopResultEvent()
{
	LOG_INFO("NotifyVoipJointStopResultEvent");
	CComVariant varResult;
	CComVariant avarParams[1];
	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	try
	{
		if(NULL != m_VoipJointStopResultEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipJointStopResultEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipJointStopResultEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipJointStopResultEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipJointStopResultEvent Failed,exception");
	}
}
void CWebVoipCtrl::NotifyVoipNotifyJointSwitchToPhoneEvent()
{
	LOG_INFO("NotifyVoipNotifyJointSwitchToPhoneEvent");
	CComVariant varResult;
	CComVariant avarParams[1];
	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	try
	{
		if(NULL != m_VoipNotifyJointSwitchToPhoneEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipNotifyJointSwitchToPhoneEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipNotifyJointSwitchToPhoneEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipNotifyJointSwitchToPhoneEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipNotifyJointSwitchToPhoneEvent Failed,exception");
	}
}
void CWebVoipCtrl::NotifyVoipNotifyJointSwitchToPCEvent()
{
	LOG_INFO("NotifyVoipNotifyJointSwitchToPCEvent");
	CComVariant varResult;
	CComVariant avarParams[1];
	DISPPARAMS params = { avarParams, NULL, 1, 0 };
	try
	{
		if(NULL != m_VoipNotifyJointSwitchToPCEvent)
		{
			EXCEPINFO excepInfo;  
			memset(&excepInfo, 0, sizeof(excepInfo));  
			UINT nArgErr = (UINT)-1;  // initialize to invalid arg
			HRESULT hRet = m_VoipNotifyJointSwitchToPCEvent->Invoke(0,
				IID_NULL, 
				LOCALE_USER_DEFAULT, 
				DISPATCH_METHOD, 
				&params, 
				&varResult, 
				&excepInfo,
				&nArgErr);
			if(hRet == S_OK)
			{
				LOG_INFO("Invoke NotifyVoipNotifyJointSwitchToPCEvent Success");
			}
			else
			{
				LOG_ERROR("Invoke NotifyVoipNotifyJointSwitchToPCEvent Failed");
			}
		}
	}
	catch(...)
	{
		LOG_ERROR("Invoke NotifyVoipNotifyJointSwitchToPCEvent Failed,exception");
	}
}

LRESULT CWebVoipCtrl::OnCallNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	TUP_UINT32 msgid = (TUP_UINT32)wParam;
	LOG_INFO("wParam=%d",msgid);
	switch (msgid)
	{
	case CALL_E_EVT_SIPACCOUNT_INFO:
		{
			CALL_S_SIP_ACCOUNT_INFO* pNotify = (CALL_S_SIP_ACCOUNT_INFO*)lParam;
			if(NULL != pNotify)
			{
				LOG_INFO("RegState=%d",pNotify->enRegState);
				if(pNotify->enRegState == CALL_E_REG_STATE_BUTT)
				{
					NotifyVoipLogoutResultEvent(true,0);
				}
				else
				{
					NotifyVoipLoginResultEvent(pNotify->ulSipAccountID,pNotify->acUserNum,pNotify->acTelNum,pNotify->enRegState,pNotify->ulReasonCode);	
				}
				delete pNotify;
				pNotify = NULL;
			}		
		}
		break;
	case CALL_E_EVT_CALL_AUTHORIZE_SUCCESS:
		{
			//sip鉴权成功
		}
		break;

	case CALL_E_EVT_CALL_AUTHORIZE_FAILED:
		{
			//鉴权失败
		}
		break;
	case CALL_E_EVT_CALL_INCOMMING:
		{
			CALL_S_CALL_INFO* pInfo = (CALL_S_CALL_INFO*)lParam;
			if(NULL != pInfo)
			{
				VoipCallInfo_Id = pInfo->stCallStateInfo.ulCallID;
				NotifyVoipIncomingCallEvent(pInfo->stCallStateInfo.ulCallID,
					pInfo->stCallStateInfo.enCallType,
					pInfo->stCallStateInfo.enCallState,
					pInfo->stCallStateInfo.acDisplayName,
					pInfo->stCallStateInfo.acTelNum,				
					pInfo->stCallStateInfo.bIsIn,
					pInfo->stCallStateInfo.bIsPassiveEnd,
					pInfo->stCallStateInfo.ulReasonCode);
				delete pInfo;
				pInfo = NULL;
			}
		}
		break;
	case CALL_E_EVT_CALL_OUTGOING:
		{
			CALL_S_CALL_INFO* pInfo = (CALL_S_CALL_INFO*)lParam;
			if(NULL != pInfo)
			{
				NotifyVoipCallOutgoingEvent(pInfo->stCallStateInfo.ulCallID,
					pInfo->stCallStateInfo.enCallType,
					pInfo->stCallStateInfo.enCallState,
					pInfo->stCallStateInfo.acDisplayName,
					pInfo->stCallStateInfo.acTelNum,			
					pInfo->stCallStateInfo.bIsIn,
					pInfo->stCallStateInfo.bIsPassiveEnd,
					pInfo->stCallStateInfo.ulReasonCode);
				delete pInfo;
				pInfo = NULL;
			}
		}
		break;
	case CALL_E_EVT_CALL_RINGBACK:
		{
			CALL_S_CALL_INFO* pInfo = (CALL_S_CALL_INFO*)lParam;
			if(NULL != pInfo)
			{
				NotifyVoipPeerRingbackEvent(pInfo->stCallStateInfo.ulCallID,
					pInfo->stCallStateInfo.enCallType,
					pInfo->stCallStateInfo.enCallState,
					pInfo->stCallStateInfo.acDisplayName,		
					pInfo->stCallStateInfo.bIsPassiveEnd,
					pInfo->stCallStateInfo.ulReasonCode);
				delete pInfo;
				pInfo = NULL;
			}
		}
		break;
	case CALL_E_EVT_CALL_CONNECTED:
		{
			CALL_S_CALL_INFO* pInfo = (CALL_S_CALL_INFO*)lParam;
			if(NULL != pInfo)
			{
				NotifyVoipStartTalkingEvent(pInfo->stCallStateInfo.ulCallID,
					pInfo->stCallStateInfo.enCallType,
					pInfo->stCallStateInfo.enCallState,
					pInfo->stCallStateInfo.acDisplayName,
					pInfo->stCallStateInfo.acTelNum,
					pInfo->stCallStateInfo.bIsIn,
					pInfo->stCallStateInfo.bIsPassiveEnd,
					pInfo->stCallStateInfo.ulReasonCode);
				delete pInfo;
				pInfo = NULL;
			}
		}
		break;
	case CALL_E_EVT_CALL_ENDED:
		{
			CALL_S_CALL_INFO* pInfo = (CALL_S_CALL_INFO*)lParam;
			if(NULL != pInfo)
			{
				NotifyCallCloseResultEvent(pInfo->stCallStateInfo.ulCallID,
					pInfo->stCallStateInfo.enCallType,
					pInfo->stCallStateInfo.enCallState,
					pInfo->stCallStateInfo.acDisplayName,
					pInfo->stCallStateInfo.acTelNum,		
					pInfo->stCallStateInfo.bIsIn,
					pInfo->stCallStateInfo.bIsPassiveEnd,
					pInfo->stCallStateInfo.ulReasonCode);
				//VoipCallInfo_Id = 0;盲转不改变callid
				delete pInfo;
				pInfo = NULL;
			}
		}
		break;
	case CALL_E_EVT_CALL_ADD_VIDEO:
		{
			TUP_UINT32 callid = (TUP_UINT32)lParam;
			NotifyVoipVoiceSwitchToVideoReqEvent(callid);

		}
		break;
	case CALL_E_EVT_CALL_DEL_VIDEO:
		{
			TUP_UINT32 callid = (TUP_UINT32)lParam;
			NotifyVoipVideoSwitchToVoiceReqEvent(callid);
		}
		break;
	case CALL_E_EVT_CALL_MODIFY_VIDEO_RESULT:
		{
			CALL_S_MODIFY_VIDEO_RESULT* pInfo = (CALL_S_MODIFY_VIDEO_RESULT*)lParam;
			if(NULL != pInfo)
			{
				NotifyVoipVoiceVideoSwitchResultEvent(pInfo->ulCallID,pInfo->ulResult,pInfo->bIsVideo);
				delete pInfo;
				pInfo = NULL;
			}
		}
		break;
	case CALL_E_EVT_CALL_RTP_CREATED:
		{
			TUP_UINT32 callid = (TUP_UINT32)lParam;
			NotifyVoipRtpCreatedEvent(callid);
		}
		break;
	case CALL_E_EVT_CALL_HOLD_SUCCESS:
		{
			//呼叫保持成功
			TUP_UINT32 callid = (TUP_UINT32)lParam;
			NotifyVoipCallHoldSuccessEvent(callid);
		}
		break;	
	case CALL_E_EVT_CALL_HOLD_FAILED:
		{
			//呼叫保持失败
			TUP_UINT32 callid = (TUP_UINT32)lParam;
			NotifyVoipCallHoldFailedEvent(callid);
		}
		break;
	case CALL_E_EVT_CALL_UNHOLD_SUCCESS:
		{
			//取消呼叫保持成功
			TUP_UINT32 callid = (TUP_UINT32)lParam;
			NotifyVoipCallUnHoldSuccessEvent(callid);
		}
		break;
	case CALL_E_EVT_CALL_UNHOLD_FAILED:
		{
			//取消呼叫保持失败
			TUP_UINT32 callid = (TUP_UINT32)lParam;
			NotifyVoipCallUnHoldFailedEvent(callid);
		}
		break;
	case CALL_E_EVT_CALL_BLD_TRANSFER_SUCCESS:
		{
			//盲转成功
			TUP_UINT32 callid = (TUP_UINT32)lParam;
			NotifyVoipCallBlindTransSuccessEvent(callid);
			VoipCallInfo_Id = callid;
		}
		break;
	case CALL_E_EVT_CALL_BLD_TRANSFER_FAILED:
		{
			//盲转失败
			TUP_UINT32 callid = (TUP_UINT32)lParam;
			NotifyVoipCallBlindTransFailedEvent(callid);
		}
		break;
	case CALL_E_EVT_CALL_ATD_TRANSFER_SUCCESS:
		{
			//咨询转成功
			TUP_UINT32 callid = (TUP_UINT32)lParam;
			NotifyVoipCallConsultTransSuccessEvent(callid);
		}
		break;
	case CALL_E_EVT_CALL_ATD_TRANSFER_FAILED:
		{
			//咨询转失败
			TUP_UINT32 callid = (TUP_UINT32)lParam;
			NotifyVoipCallConsultTransFailedEvent(callid);
		}
		break;
	case CALL_E_EVT_SET_IPT_SERVICE_SUCCESS:
		{
			//IPT服务登记成功
			TUP_UINT32 callid = (TUP_UINT32)lParam;
			NotifyVoipIPTServiceRegSuccessEvent(callid);
		}
		break;
	case CALL_E_EVT_SET_IPT_SERVICE_FAILED:
		{
			//IPT服务登记失败
			TUP_UINT32 callid = (TUP_UINT32)lParam;
			NotifyVoipIPTServiceRegFailedEvent(callid);
		}
		break;
	case CALL_E_EVT_CALL_RECORD_SUCCESS:        /**< 录音开启成功 */
		{
			TUP_UINT32 callid = (TUP_UINT32)lParam;
			NotifyVoipStartRecordingEvent(callid);

		}
		break;
	case CALL_E_EVT_CALL_RECORD_FAILED:         /**< 录音开启失败 */
		{
			TUP_UINT32 callid = (TUP_UINT32)lParam;
			NotifyVoipRecordFailedEvent(callid);
		}
		break;
	case CALL_E_EVT_CALL_UNRECORD_SUCCESS:      /**< 录音关闭成功 */
		{
			TUP_UINT32 callid = (TUP_UINT32)lParam;
			NotifyVoipUnRecordSuccessEvent(callid);			
		}
		break;
	case CALL_E_EVT_CALL_UNRECORD_FAILED:       /**< 录音关闭失败 */
		{
			TUP_UINT32 callid = (TUP_UINT32)lParam;
			NotifyVoipUnRecordFailedEvent(callid);
		}
		break;
	case CALL_E_EVT_TO_UI_JOINT_START:
		{
			CALL_S_JOINT_CMD_INFOS* pNotifyInfo = (CALL_S_JOINT_CMD_INFOS*)lParam;
			if(NULL != pNotifyInfo)
			{
				NotifyVoipJointStartResultEvent();
				delete pNotifyInfo;
				pNotifyInfo = NULL;
			}
		}
		break;
	case CALL_E_EVT_TO_UI_JOINT_CLOSE:
		{
			CALL_S_JOINT_CMD_INFOS* pNotifyInfo = (CALL_S_JOINT_CMD_INFOS*)lParam;
			if(NULL != pNotifyInfo)
			{
				NotifyVoipJointStopResultEvent();
				delete pNotifyInfo;
				pNotifyInfo = NULL;
			}

		}
		break;
	case CALL_E_EVT_TO_UI_JOINT_SWITCH_TO_PHONE:
		{
			CALL_S_JOINT_CMD_INFOS* pNotifyInfo = (CALL_S_JOINT_CMD_INFOS*)lParam;
			if(NULL != pNotifyInfo)
			{
				NotifyVoipNotifyJointSwitchToPhoneEvent();
				delete pNotifyInfo;
				pNotifyInfo = NULL;
			}
		}
		break;
	case CALL_E_EVT_TO_UI_JOINT_SWITCH_TO_PC:
		{
			CALL_S_JOINT_CMD_INFOS* pNotifyInfo = (CALL_S_JOINT_CMD_INFOS*)lParam;
			if(NULL != pNotifyInfo)
			{
				NotifyVoipNotifyJointSwitchToPCEvent();
				delete pNotifyInfo;
				pNotifyInfo = NULL;
			}
		}
		break;
	case CALL_E_EVT_CONTACT_STATUS_CHANGE:
		{

		}
		break;
	case CALL_E_EVT_NEW_SERVICE_RIGHT:
		{
			//业务权限变更通知
			//CALL_S_SERVICERIGHT_CFG* pNotifyInfo = (CALL_S_SERVICERIGHT_CFG*)lParam;
			//if(NULL != pNotifyInfo)
			//{
			//	for(int i=0;i<CALL_E_SERVICE_RIGHT_TYPE_BUTT;i++)
			//	{
			//		TEX0_LOG_INFO("IntercomNum=%s,right=%d,register=%d,ActiveCode=%s,DeactiveCode=%s",
			//			pNotifyInfo->acIntercomNum,
			//			pNotifyInfo->astSrvInfo[i].ulRight,
			//			pNotifyInfo->astSrvInfo[i].ulRegister,
			//			pNotifyInfo->astSrvInfo[i].acActiveAccessCode,
			//			pNotifyInfo->astSrvInfo[i].acDeactiveAccessCode);
			//	}
			//	delete pNotifyInfo;
			//	pNotifyInfo = NULL;
			//}
		}
		break;
	}
	return 0;
}

STDMETHODIMP CWebVoipCtrl::WebVoipInitialize(void)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	RECT rc = {0,0,0,0};
	if(NULL == m_ATLWnd)
	{
		m_ATLWnd = CreateControlWindow(::GetDesktopWindow(), rc);   
		_ASSERT(m_ATLWnd); 
	}  

	std::string strPath;
	CTools::getCurrentPath(strPath);
	strPath.append("\\log");
	tup_call_log_start(CALL_E_LOG_DEBUG,10000,10,strPath.c_str());
	TUP_RESULT tRet = tup_call_init();	
	if (TUP_SUCCESS != tRet)
	{
		LOG_ERROR("tup_call_init failed.");
		return S_FALSE;
	}
	tRet = tup_call_register_process_notifiy(NotifyCallBack::CallNotify);
	if (TUP_SUCCESS != tRet)
	{
		LOG_ERROR("tup_call_register_process_notifiy failed.");
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CWebVoipCtrl::WebVoipUninitialize(void)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	tup_call_uninit();
	
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipLogin(void)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");

	CALL_E_TRANSPORTMODE eTransMode =  CALL_E_TRANSPORTMODE_UDP;
	TUP_RESULT tRet = tup_call_set_cfg(CALL_D_CFG_SIP_TRANS_MODE, &eTransMode);
	if (TUP_SUCCESS != tRet)
	{
		return S_FALSE;
	}

	std::string ip = VoipSIPServerIP;
	int iServerPort = VoipSIPServerPort;

	TUP_UINT32 server_port = iServerPort;
	if (eTransMode == CALL_E_TRANSPORTMODE_TLS)
	{
		TUP_CHAR path[] = "D:\\V200R002\\Winbin\\Debug_vc11\\root_cert_1.pem";
		tRet = tup_call_set_cfg(CALL_D_CFG_SIP_TLS_ROOTCERTPATH, path);
		server_port = 5061;
	}


	CALL_S_SERVER_CFG sipServerCfg = {0};
	strcpy_s(sipServerCfg.server_address, ip.c_str());
	sipServerCfg.server_port = iServerPort;
	tRet = tup_call_set_cfg(CALL_D_CFG_SERVER_REG_PRIMARY, &sipServerCfg );
	if (TUP_SUCCESS != tRet)
	{
		return S_FALSE;
	}

	memset(&sipServerCfg,0,sizeof(sipServerCfg));
	strcpy_s(sipServerCfg.server_address, ip.c_str());
	sipServerCfg.server_port = iServerPort;

	tRet = tup_call_set_cfg(CALL_D_CFG_SERVER_PROXY_PRIMARY,&sipServerCfg);
	if (TUP_SUCCESS != tRet)
	{
		return S_FALSE;
	}

	tRet = tup_call_set_cfg(CALL_D_CFG_ENV_USEAGENT,  USER_AGENT);
	if (TUP_SUCCESS != tRet)
	{
		return S_FALSE;
	}

	CALL_E_PRODUCT_TYPE eProductType = CALL_E_PRODUCT_TYPE_PC;
	tRet = tup_call_set_cfg(CALL_D_CFG_ENV_PRODUCT_TYPE, (TUP_VOID*)&eProductType);
	if (TUP_SUCCESS != tRet)
	{
		return S_FALSE;
	}

	CALL_S_IF_INFO IFInfo  ;
	memset(&IFInfo,0,sizeof(CALL_S_IF_INFO));
	IFInfo.ulType =  CALL_E_IP_V4;
	IFInfo.uAddress.ulIPv4 = inet_addr(GetLocalIPAddress().c_str());
	tRet = tup_call_set_cfg(CALL_D_CFG_NET_NETADDRESS,  &IFInfo);
	if (TUP_SUCCESS != tRet)
	{
		return S_FALSE;
	}


	std::string sipAccount = VoipUserInfo_Id;
	std::string sipUserName = sipAccount + "@" + GetLocalIPAddress();
	std::string sipUserPWD = VoipUserInfo_Password;

	tRet = tup_call_register(sipAccount.c_str(),sipUserName.c_str(),sipUserPWD.c_str());
	if (TUP_SUCCESS != tRet)
	{
		return S_FALSE;
	}

	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipLogout(void)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	TUP_RESULT tRet = tup_call_deregister(VoipUserInfo_Id.c_str());

	if(TUP_FAIL == tRet)
	{
		NotifyVoipLogoutResultEvent(false,tRet);
	}

	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipCall(BSTR phoneNum, USHORT callType, SHORT* ret)
{
	// TODO: Add your implementation code here
	std::string calleeNum = CTools::UNICODE2UTF(phoneNum);
	INFO_TRACE("phoneNum = %s,callType=%d",calleeNum.c_str(),callType);
	
	CALL_E_CALL_TYPE tupCallType;
	if(callType == AudioCall)
	{
		tupCallType = CALL_E_CALL_TYPE_IPAUDIO;
	}
	else if(callType == VideoCall)
	{
		tupCallType = CALL_E_CALL_TYPE_IPVIDEO;
	}
	else
	{
		LOG_ERROR("callType is invalid");
		*ret = -1;//请求发送失败
		return S_FALSE;
	}	

	if(0 != VoipCallInfo_Id)
	{
		LOG_ERROR("has already been calling.");
		*ret = -1;//已经有呼叫
		return S_FALSE;
	}

	TUP_RESULT tRet = tup_call_start_call(&VoipCallInfo_Id,tupCallType,calleeNum.c_str());
	if(TUP_SUCCESS == tRet)
	{
		*ret = 0;
		return S_OK;
	}
	else
	{
		*ret = -1;//请求发送失败
		LOG_ERROR("tup_call_start_call failed");
		return S_FALSE;
	}
	
}

STDMETHODIMP CWebVoipCtrl::WebVoipHangup(SHORT* ret)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(0 == VoipCallInfo_Id)
	{
		LOG_ERROR("WebVoipHangup failed,reason:VoipCallInfo_Id is 0");
		*ret = 0;
		return S_FALSE;
	}
	TUP_RESULT tRet = tup_call_end_call(VoipCallInfo_Id);
	if(tRet != TUP_SUCCESS)
	{
		LOG_ERROR("tup_call_end_call failed.");
		*ret = -1;
		return S_FALSE;
	}

	VoipCallInfo_Id = 0;
	*ret = 0;
	return S_OK;
}
STDMETHODIMP CWebVoipCtrl::WebVoipCallRingAlert(SHORT* ret)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(0 == VoipCallInfo_Id)
	{
		LOG_ERROR("WebVoipCallRingAlert failed,reason:VoipCallInfo_Id is 0");
		*ret = -1;
		return S_FALSE;
	}

	TUP_RESULT tRet = tup_call_alerting_call(VoipCallInfo_Id);
	if(tRet != TUP_SUCCESS)
	{
		LOG_ERROR("tup_call_alerting_call failed.");
		*ret = -1;
		return S_FALSE;
	}

	*ret = 0;
	return S_OK;
}
STDMETHODIMP CWebVoipCtrl::WebVoipAccept(USHORT callMode, SHORT* ret)
{
	// TODO: Add your implementation code here
	INFO_TRACE("callMode=%d",callMode);

	if(callMode == SoftCall)
	{		
		TUP_RESULT tRet = tup_call_accept_call(VoipCallInfo_Id,TUP_FALSE);
		if(tRet != TUP_SUCCESS)
		{
			LOG_ERROR("tup_call_accept_call failed.");
			*ret = -1;
			return S_FALSE;
		}
	}
	else if(callMode == IPPhoneCall)
	{
		//tup_call_create_callid();
	}

	*ret = 0;
	return S_OK;
}
STDMETHODIMP CWebVoipCtrl::WebVoipReject(SHORT* ret)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	TUP_RESULT tRet = tup_call_end_call(VoipCallInfo_Id);
	if(tRet != TUP_SUCCESS)
	{
		LOG_ERROR("tup_call_end_call failed.");
		*ret = -1;
		return S_FALSE;
	}
	*ret = 0;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipIsEnableVideo(VARIANT_BOOL isEnable, SHORT* ret)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(0 == VoipCallInfo_Id)
	{
		LOG_ERROR("WebVoipIsEnableVideo failed,reason:VoipCallInfo_Id is 0");
		*ret = -1;
		return S_FALSE;
	}
	if(isEnable)
	{
		TUP_RESULT tRet = tup_call_add_video(VoipCallInfo_Id);
		if(tRet != TUP_SUCCESS)
		{
			LOG_ERROR("tup_call_add_video failed.");
			*ret = -1;
			return S_FALSE;
		}
	}
	else
	{
		TUP_RESULT tRet = tup_call_del_video(VoipCallInfo_Id);
		if(tRet != TUP_SUCCESS)
		{
			LOG_ERROR("tup_call_del_video failed.");
			*ret = -1;
			return S_FALSE;
		}
	}
	*ret = 0;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipEnableVideoReply(VARIANT_BOOL isAccept, SHORT* ret)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(0 == VoipCallInfo_Id)
	{
		LOG_ERROR("WebVoipEnableVideoReply failed,reason:VoipCallInfo_Id is 0");
		*ret = -1;
		return S_FALSE;
	}
	if(isAccept)
	{	
		TUP_RESULT tRet = tup_call_reply_add_video(VoipCallInfo_Id,TUP_TRUE);
		if(tRet != TUP_SUCCESS)
		{
			LOG_ERROR("add video failed.");
			*ret = -1;
			return S_FALSE;
		}
	}
	else
	{
		TUP_RESULT tRet = tup_call_reply_add_video(VoipCallInfo_Id,TUP_FALSE);
		if(tRet != TUP_SUCCESS)
		{
			LOG_ERROR("reject video failed.");
			*ret = -1;
			return S_FALSE;
		}
	}

	*ret = 0;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipDisableVideoReply(VARIANT_BOOL isAccept, SHORT* ret)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(0 == VoipCallInfo_Id)
	{
		LOG_ERROR("WebVoipDisableVideoReply failed,reason:VoipCallInfo_Id is 0");
		*ret = -1;
		return S_FALSE;
	}
	if(isAccept)
	{	
		TUP_RESULT tRet = tup_call_reply_del_video(VoipCallInfo_Id,TUP_TRUE);
		if(tRet != TUP_SUCCESS)
		{
			LOG_ERROR("add video failed.");
			*ret = -1;
			return S_FALSE;
		}

	}
	else
	{
		TUP_RESULT tRet = tup_call_reply_del_video(VoipCallInfo_Id,TUP_FALSE);
		if(tRet != TUP_SUCCESS)
		{
			LOG_ERROR("del video failed.");
			*ret = -1;
			return S_FALSE;
		}
	}
	*ret = 0;
	return S_OK;
}

STDMETHODIMP CWebVoipCtrl::WebVoipSetLocalVideoWindow(unsigned long wndhandle, unsigned short wndType, unsigned long pos_x, unsigned long pos_y, unsigned long pos_w, unsigned long pos_h ,SHORT* ret)
{
	// TODO: Add your implementation code here
	LOG_INFO("WebVoipSetLocalVideoWindow:m_hWnd=%lu.wndType=%d,%d,%d,%d,%d",wndhandle,wndType,pos_x,pos_y,pos_w,pos_h);

	CALL_S_VIDEOWND_INFO videoWndInfo[1];
	memset(videoWndInfo, 0, sizeof(CALL_S_VIDEOWND_INFO)*1);
	if(0 == wndType)//远端窗口
	{
		videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ulRender = (TUP_UINT32)wndhandle;
		videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ulVideoWndType = CALL_E_VIDEOWND_CALLREMOTE;
		videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ulIndex = 0;
		videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ulDisplayType = CALL_E_VIDEOWND_DISPLAY_FULL;
		videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ucCoordinate[CALL_E_COORDINATE_X] = pos_x;
		videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ucCoordinate[CALL_E_COORDINATE_Y] = pos_y;
		videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ucCoordinate[CALL_E_COORDINATE_W] = pos_w;
		videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ucCoordinate[CALL_E_COORDINATE_H] = pos_h;
	}
	else//本端窗口
	{
		videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ulRender = (TUP_UINT32)wndhandle;
		videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ulVideoWndType = CALL_E_VIDEOWND_CALLLOCAL;
		videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ulIndex = 0;
		videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ulDisplayType = CALL_E_VIDEOWND_DISPLAY_FULL;
		videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ucCoordinate[CALL_E_COORDINATE_X] = pos_x;
		videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ucCoordinate[CALL_E_COORDINATE_Y] = pos_y;
		videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ucCoordinate[CALL_E_COORDINATE_W] = pos_w;
		videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ucCoordinate[CALL_E_COORDINATE_H] = pos_h;
	}

	TUP_RESULT tRet = tup_call_create_video_window(1, (CALL_S_VIDEOWND_INFO *)videoWndInfo);
	if(TUP_FAIL == tRet)
	{
		LOG_ERROR("WebVoipSetLocalVideoWindow failed.");
		*ret = -1;
		return S_FALSE;
	}
	*ret = 0;
	return S_OK;
}

STDMETHODIMP CWebVoipCtrl::WebVoipDMTFSecondDial(BSTR strKey, SHORT* ret)
{
	// TODO: Add your implementation code here
	std::string key = CTools::UNICODE2UTF(strKey);
	INFO_TRACE("strKey=%s",key.c_str());

	CALL_E_DTMF_TONE t;
	if(key == "0")
	{
		t = CALL_E_DTMF0;
	}
	else if(key == "1")
	{
		t = CALL_E_DTMF1;
	}
	else if(key == "2")
	{
		t = CALL_E_DTMF2;
	}
	else if(key == "3")
	{
		t = CALL_E_DTMF3;
	}
	else if(key == "4")
	{
		t = CALL_E_DTMF4;
	}
	else if(key == "5")
	{
		t = CALL_E_DTMF5;
	}
	else if(key == "6")
	{
		t = CALL_E_DTMF6;
	}
	else if(key == "7")
	{
		t = CALL_E_DTMF7;
	}
	else if(key == "8")
	{
		t = CALL_E_DTMF8;
	}
	else if(key == "9")
	{
		t = CALL_E_DTMF9;
	}
	else if(key == "*")
	{
		t = CALL_E_DTMFSTAR;
	}
	else if(key == "#")
	{
		t = CALL_E_DTMFJIN;
	}


	TUP_RESULT tRet =  tup_call_send_DTMF(VoipCallInfo_Id,t);
	if(tRet == TUP_FAIL)
	{
		LOG_ERROR("tup_call_send_DTMF failed.");
		*ret = -1;
		return S_FALSE;
	}
	*ret = 0;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipCallHold(VARIANT_BOOL isHold, SHORT* ret)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");

	if(VARIANT_TRUE == isHold)
	{
		TUP_RESULT tRet = tup_call_hold_call(VoipCallInfo_Id);
		if(tRet == TUP_FAIL)
		{
			LOG_ERROR("tup_call_hold_call failed.");
			*ret = -1;
			return S_FALSE;
		}
	}
	else
	{
		TUP_RESULT tRet = tup_call_unhold_call(VoipCallInfo_Id);
		if(tRet == TUP_FAIL)
		{
			LOG_ERROR("tup_call_unhold_call failed.");
			*ret = -1;
			return S_FALSE;
		}
	}
	
	*ret = 0;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipCallBlindTransfer(BSTR transToNum, SHORT* ret)
{
	// TODO: Add your implementation code here
	std::string strTranToNum = CTools::UNICODE2UTF(transToNum);
	INFO_TRACE("transToNum=%s",strTranToNum.c_str());

	TUP_RESULT tRet = tup_call_blind_transfer(VoipCallInfo_Id,strTranToNum.c_str());
	if(tRet == TUP_FAIL)
	{
		LOG_ERROR("tup_call_blind_transfer failed.");
		*ret = -1;
		return S_FALSE;
	}
	*ret = 0;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipCallConsultTransfer(SHORT* ret)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");

	//tup_call_consult_transfer()

	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipCallDivertTransfer(BSTR divertToNum, SHORT* ret)
{
	// TODO: Add your implementation code here
	std::string strdivertToNum = CTools::UNICODE2UTF(divertToNum);
	INFO_TRACE("divertToNum=%s",strdivertToNum.c_str());

	TUP_RESULT tRet = tup_call_divert_call(VoipCallInfo_Id,strdivertToNum.c_str());
	if(tRet == TUP_FAIL)
	{
		LOG_ERROR("tup_call_divert_call failed.");
		*ret = -1;
		return S_FALSE;
	}
	*ret = 0;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipSetCallForward(unsigned int service, BSTR divertToNum, SHORT* ret)
{
	// TODO: Add your implementation code here
	std::string strdivertToNum = CTools::UNICODE2UTF(divertToNum);
	INFO_TRACE("WebVoipSetCallForward:service=%d,divertToNum=%s",service,strdivertToNum.c_str());

	CALL_S_SERVICE_RIGHT_CFG stServiceCfg;  /* 业务权限集结构体指针 */
	memset(&stServiceCfg, 0, sizeof(stServiceCfg));
	stServiceCfg.ulRight = 1;

	CALL_E_SERVICE_CALL_TYPE forwardType;
	switch (service)
	{
	case FORWARD_UNCONDITION_Active:
		{
			forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION_Active;
			strncpy_s(stServiceCfg.acActiveAccessCode, "*57*", CALL_D_ACCESSCODE_MAX_LENGTH);
			strncpy_s(stServiceCfg.acDeactiveAccessCode, "#57#", CALL_D_ACCESSCODE_MAX_LENGTH);
			TUP_RESULT lRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_CFU, (TUP_VOID*)&stServiceCfg);
			if(lRet != TUP_SUCCESS)
			{
				LOG_ERROR("update service right FORWARD_UNCONDITION_Active failed.");
			}
			break;
		}
	case FORWARD_UNCONDITION_Deactive:
		{
			forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_UNCONDITION_Deactive;

			strncpy_s(stServiceCfg.acActiveAccessCode, "*57*", CALL_D_ACCESSCODE_MAX_LENGTH);
			strncpy_s(stServiceCfg.acDeactiveAccessCode, "#57#", CALL_D_ACCESSCODE_MAX_LENGTH);
			TUP_RESULT lRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_CFU, (TUP_VOID*)&stServiceCfg);
			if(lRet != TUP_SUCCESS)
			{
				LOG_ERROR("update service right FORWARD_UNCONDITION_Deactive failed.");
			}
			break;
		}
	case FORWARD_ONBUSY_Active:
		{
			forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY_Active;
			strncpy_s(stServiceCfg.acActiveAccessCode, "*40*", CALL_D_ACCESSCODE_MAX_LENGTH); 
			strncpy_s(stServiceCfg.acDeactiveAccessCode, "#40#", CALL_D_ACCESSCODE_MAX_LENGTH);
			TUP_RESULT lRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_CFB, (TUP_VOID*)&stServiceCfg);
			if(lRet != TUP_SUCCESS)
			{
				LOG_ERROR("update service right FORWARD_ONBUSY_Active failed.");
			}
			break;
		}
	case FORWARD_ONBUSY_Deactive:
		{
			forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_ONBUSY_Deactive;
			strncpy_s(stServiceCfg.acActiveAccessCode, "*40*", CALL_D_ACCESSCODE_MAX_LENGTH); 
			strncpy_s(stServiceCfg.acDeactiveAccessCode, "#40#", CALL_D_ACCESSCODE_MAX_LENGTH);
			TUP_RESULT lRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_CFB, (TUP_VOID*)&stServiceCfg);
			if(lRet != TUP_SUCCESS)
			{
				LOG_ERROR("update service right FORWARD_ONBUSY_Deactive failed.");
			}
			break;
		}
	case FORWARD_NOREPLY_Active:
		{
			forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY_Active;
			strncpy_s(stServiceCfg.acActiveAccessCode, "*41*", CALL_D_ACCESSCODE_MAX_LENGTH);
			strncpy_s(stServiceCfg.acDeactiveAccessCode, "#41#", CALL_D_ACCESSCODE_MAX_LENGTH);
			TUP_RESULT lRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_CFNA, (TUP_VOID*)&stServiceCfg);
			if(lRet != TUP_SUCCESS)
			{
				LOG_ERROR("update service right FORWARD_NOREPLY_Active failed.");
			}
			break;
		}
	case FORWARD_NOREPLY_Deactive:
		{
			forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_NOREPLY_Deactive;
			strncpy_s(stServiceCfg.acActiveAccessCode, "*41*", CALL_D_ACCESSCODE_MAX_LENGTH);
			strncpy_s(stServiceCfg.acDeactiveAccessCode, "#41#", CALL_D_ACCESSCODE_MAX_LENGTH);
			TUP_RESULT lRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_CFNA, (TUP_VOID*)&stServiceCfg);
			if(lRet != TUP_SUCCESS)
			{
				LOG_ERROR("update service right FORWARD_NOREPLY_Deactive failed.");
			}
			break;
		}
	case FORWARD_OFFLINE_Active:
		{
			forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_OFFLINE_Active;
			strncpy_s(stServiceCfg.acActiveAccessCode, "*45*", CALL_D_ACCESSCODE_MAX_LENGTH);
			strncpy_s(stServiceCfg.acDeactiveAccessCode, "#45#", CALL_D_ACCESSCODE_MAX_LENGTH);
			TUP_RESULT lRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_CFNR , (TUP_VOID*)&stServiceCfg);
			if(lRet != TUP_SUCCESS)
			{
				LOG_ERROR("update service right FORWARD_OFFLINE_Active failed.");
			}
			break;
		}
	case FORWARD_OFFLINE_Deactive:
		{
			forwardType = CALL_E_SERVICE_CALL_TYPE_FORWARD_OFFLINE_Deactive;
			strncpy_s(stServiceCfg.acActiveAccessCode, "*45*", CALL_D_ACCESSCODE_MAX_LENGTH);
			strncpy_s(stServiceCfg.acDeactiveAccessCode, "#45#", CALL_D_ACCESSCODE_MAX_LENGTH);
			TUP_RESULT lRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_CFNR, (TUP_VOID*)&stServiceCfg);
			if(lRet != TUP_SUCCESS)
			{
				LOG_ERROR("update service right FORWARD_OFFLINE_Deactive failed.");
			}
			break;
		}
	default:
		{
			LOG_ERROR("WebVoipSetCallForward failed,reason:service is %d",service);
			*ret = -1;
			return S_FALSE;
		}

	}

	TUP_RESULT tRet = tup_call_set_IPTservice(forwardType,(void*)strdivertToNum.c_str());
	if(tRet == TUP_FAIL)
	{
		LOG_ERROR("tup_call_set_IPTservice failed.");
		*ret = -1;
		return S_FALSE;
	}

	*ret = 0;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipSetCallDND(unsigned int service, SHORT* ret)
{
	// TODO: Add your implementation code here
	INFO_TRACE("WebVoipSetCallDND:service=%d",service);

	CALL_E_SERVICE_CALL_TYPE DNDType;
	if(REG_DND == service)
	{
		DNDType = CALL_E_SERVICE_CALL_TYPE_REG_DND;
	}
	else if(UNREG_DND == service)
	{
		DNDType = CALL_E_SERVICE_CALL_TYPE_UNREG_DND;
	}
	else
	{
		LOG_ERROR("WebVoipSetCallDND failed,reason:service is invalid");
		*ret = -1;
		return S_FALSE;
	}

	CALL_S_SERVICE_RIGHT_CFG stServiceCfg;  /* 业务权限集结构体指针 */
	memset(&stServiceCfg, 0, sizeof(stServiceCfg));
	stServiceCfg.ulRight = 1;
	strncpy_s(stServiceCfg.acActiveAccessCode, "*56#", 32); //DND reg
	strncpy_s(stServiceCfg.acDeactiveAccessCode, "#56#", 32);
	TUP_RESULT lRet = tup_call_set_cfg(CALL_D_CFG_SERVRIGHT_DND, (TUP_VOID*)&stServiceCfg);
	if(lRet != TUP_SUCCESS)
	{
		LOG_ERROR("WebVoipSetCallDND:update service right failed.");
	}

	TUP_RESULT tRet = tup_call_set_IPTservice(DNDType,"");
	if(tRet == TUP_FAIL)
	{
		LOG_ERROR("WebVoipSetCallDND:tup_call_set_IPTservice failed.");
		*ret = -1;
		return S_FALSE;
	}

	*ret = 0;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipSetCallACB(unsigned int service, SHORT* ret)
{
	// TODO: Add your implementation code here
	INFO_TRACE("WebVoipSetCallACB:service=%d",service);

	CALL_E_SERVICE_CALL_TYPE CallACBType;
	if(ACBCALL_ACTIVE == service)
	{
		CallACBType = CALL_E_SERVICE_CALL_TYPE_ACBCALL_ACTIVE;
	}
	else if(ACBCALL_DEACTIVE == service)
	{
		CallACBType = CALL_E_SERVICE_CALL_TYPE_ACBCALL_DEACTIVE;
	}
	else
	{
		LOG_ERROR("WebVoipSetCallACB failed,reason:service is invalid");
		*ret = -1;
		return S_FALSE;
	}

	TUP_RESULT tRet = tup_call_set_IPTservice(CallACBType,"");
	if(tRet == TUP_FAIL)
	{
		LOG_ERROR("tup_call_set_IPTservice failed.");
		*ret = -1;
		return S_FALSE;
	}
	*ret = 0;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipSetMediaMute(unsigned short media, VARIANT_BOOL isMute, SHORT* ret)
{
	// TODO: Add your implementation code here
	INFO_TRACE("WebVoipSetMediaMute:media=%d,isMute=%d",media,isMute);
	TUP_RESULT tRet = TUP_FAIL;
	switch (media)
	{
	case DEVICE_MIC:
		{
			if(isMute)
			{
				tRet = tup_call_media_mute_mic(VoipCallInfo_Id,TUP_TRUE);
			}
			else
			{
				tRet = tup_call_media_mute_mic(VoipCallInfo_Id,TUP_FALSE);
			}
			
			break;
		}
	case DEVICE_SPK:
		{
			if(isMute)
			{
				tRet = tup_call_media_mute_speak(VoipCallInfo_Id,TUP_TRUE);
			}
			else
			{
				tRet = tup_call_media_mute_speak(VoipCallInfo_Id,TUP_FALSE);
			}
			
			break;
		}
	case DEVICE_VIDEO:
		{
			if(isMute)
			{
				tRet = tup_call_media_mute_video(VoipCallInfo_Id,TUP_TRUE);
			}
			else
			{
				tRet = tup_call_media_mute_video(VoipCallInfo_Id,TUP_FALSE);
			}
			
			break;
		}
	default:
		{
			LOG_ERROR("WebVoipSetMediaMute failed.media is invalid.");
			*ret = -1;
			return S_FALSE;
		}
	}

	if(tRet == TUP_FAIL)
	{
		LOG_ERROR("WebVoipSetMediaMute failed.");
		*ret = -1;
		return S_FALSE;
	}

	*ret = 0;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipSetCurrMediaVolume(unsigned short media, unsigned int volume, SHORT* ret)
{
	// TODO: Add your implementation code here
	INFO_TRACE("WebVoipSetCurrMediaVolume:media=%d,volume=%d",media,volume);

	TUP_RESULT tRet = TUP_FAIL;
	switch (media)
	{
	case DEVICE_MIC:
		{
			tRet = tup_call_media_set_mic_volume(CALL_E_AUD_DEV_ROUTE_LOUDSPEAKER,volume);
			break;
		}
	case DEVICE_SPK:
		{
			tRet = tup_call_media_set_speak_volume(CALL_E_AO_DEV_SPEAKER,volume);
			break;
		}
	default:
		{
			LOG_ERROR("WebVoipSetCurrMediaVolume failed.media is invalid.");
			*ret = -1;
			return S_FALSE;
		}
	}

	if(tRet == TUP_FAIL)
	{
		LOG_ERROR("WebVoipSetCurrMediaVolume failed.");
		*ret = -1;
		return S_FALSE;
	}

	*ret = 0;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipGetCurrMediaVolume(unsigned short media, unsigned int* volume)
{
	// TODO: Add your implementation code here
	INFO_TRACE("WebVoipGetCurrMediaVolume:media=%d",media);

	TUP_RESULT tRet = TUP_FAIL;
	switch (media)
	{
	case DEVICE_MIC:
		{
			tRet = tup_call_media_get_mic_volume(volume);
			break;
		}
	case DEVICE_SPK:
		{
			tRet = tup_call_media_get_speak_volume(volume);
			break;
		}
	default:
		{
			LOG_ERROR("WebVoipGetCurrMediaVolume failed.media is invalid.");
			*volume = 0;
			return S_FALSE;
		}
	}

	if(tRet == TUP_FAIL)
	{
		LOG_ERROR("WebVoipGetCurrMediaVolume failed.");
		*volume = 0;
		return S_FALSE;
	}

	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipSetMediaDevice(unsigned short media, unsigned int index, SHORT* ret)
{
	// TODO: Add your implementation code here
	INFO_TRACE("WebVoipSetMediaDevice:media=%d,index=%d",media,index);
	TUP_RESULT tRet = TUP_FAIL;
	switch (media)
	{
	case DEVICE_MIC:
		{
			tRet = tup_call_media_set_mic_index(index);
			break;
		}
	case DEVICE_SPK:
		{
			tRet = tup_call_media_set_speak_index(index);
			break;
		}
	case DEVICE_VIDEO:
		{
			tRet = tup_call_media_set_video_index(index);
			break;
		}
	default:
		{
			LOG_ERROR("WebVoipSetMediaDevice failed.media is invalid.");
			*ret = -1;
			return S_FALSE;
		}
	}

	if(tRet == TUP_FAIL)
	{
		LOG_ERROR("WebVoipSetMediaDevice failed.");
		*ret = -1;
		return S_FALSE;
	}

	*ret = 0;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipGetMediaDevice(unsigned short media, unsigned int* count, BSTR* deviceInfo)
{
	// TODO: Add your implementation code here
	INFO_TRACE("WebVoipGetMediaDevice:media=%d",media);

	TUP_UINT32 uiSize = 10;
	CALL_S_DEVICEINFO* pstDevice = new CALL_S_DEVICEINFO[uiSize];

	TUP_RESULT tRet = TUP_FAIL;
	switch (media)
	{
	case DEVICE_MIC:
		{
			tRet = tup_call_media_get_devices(&uiSize,pstDevice,CALL_E_CALL_DEVICE_MIC);
			break;
		}
	case DEVICE_SPK:
		{
			tRet = tup_call_media_get_devices(&uiSize,pstDevice,CALL_E_CALL_DEVICE_SPEAK);
			break;
		}
	case DEVICE_VIDEO:
		{
			tRet = tup_call_media_get_devices(&uiSize,pstDevice,CALL_E_CALL_DEVICE_VIDEO);
			break;
		}
	default:
		{
			LOG_ERROR("WebVoipGetMediaDevice failed.media is invalid.");
			delete[] pstDevice;
			pstDevice = NULL;
			return S_FALSE;
		}
	}

	if(tRet == TUP_FAIL)
	{
		LOG_ERROR("WebVoipGetMediaDevice failed.");
		delete[] pstDevice;
		pstDevice = NULL;
		return S_FALSE;
	}	

	std::string xml("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	xml.append("<devicelist>");
	const unsigned int MAXSIZE = 100;//index从整数转换为字符串的缓存长度
	for(TUP_UINT32 i=0;i<uiSize;i++)
	{		
		char cindex[MAXSIZE] = {0};
		sprintf_s(cindex,"<index>%d</index>",pstDevice[i].ulIndex);
		cindex[MAXSIZE-1] = 0;
		xml.append(cindex);
		xml.append("<name>");
		xml.append(pstDevice[i].strName);
		xml.append("</name>");
	}
	xml.append("</devicelist>");

	*deviceInfo = SysAllocString(CTools::UTF2UNICODE(xml.c_str()).c_str());

	delete[] pstDevice;
	pstDevice = NULL;
	*count = uiSize;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipChangeUserPhoneStatus(unsigned short sip_status, SHORT* ret)
{
	// TODO: Add your implementation code here
	INFO_TRACE("WebVoipChangeUserPhoneStatus:sip_status=%d",sip_status);

	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipAudioRecord(VARIANT_BOOL isOnRecord, SHORT* ret)
{
	// TODO: Add your implementation code here
	INFO_TRACE("WebVoipAudioRecord:isOnRecord=%d",isOnRecord);

	if(0 == VoipCallInfo_Id)
	{
		LOG_ERROR("WebVoipAudioRecord failed,reason:VoipCallInfo_Id is 0");
		*ret = -1;
		return S_FALSE;
	}

	TUP_RESULT tRet = TUP_FAIL;
	if(isOnRecord)
	{
		tRet = tup_call_server_recordcall_on(VoipCallInfo_Id);
	}
	else
	{
		tRet = tup_call_server_recordcall_off(VoipCallInfo_Id);
	}

	if(tRet == TUP_FAIL)
	{
		LOG_ERROR("WebVoipAudioRecord failed.");
		*ret = -1;
		return S_FALSE;
	}

	*ret = 0;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipJointSetting(BSTR linkage_number, SHORT* ret)
{
	// TODO: Add your implementation code here
	std::string strLinkNum = CTools::UNICODE2UTF(linkage_number);
	INFO_TRACE("linkage_number=%s",strLinkNum.c_str());

	TUP_RESULT tRet = tup_call_joint_setting(0, TUP_TRUE, strLinkNum.c_str());
	if(tRet == TUP_FAIL)
	{
		LOG_ERROR("tup_call_joint_setting failed.");
		*ret = -1;
		return S_FALSE;
	}
	*ret = 0;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipPhoneJoint(VARIANT_BOOL isJoint, SHORT* ret)
{
	// TODO: Add your implementation code here
	INFO_TRACE("WebVoipPhoneJoint:isJoint=%d",isJoint);
	TUP_RESULT tRet = TUP_FAIL;
	if(isJoint)
	{
		tRet = tup_call_joint_start();
	}
	else
	{
		tRet = tup_call_joint_stop();
	}

	if(tRet == TUP_FAIL)
	{
		LOG_ERROR("WebVoipPhoneJoint failed.");
		*ret = -1;
		return S_FALSE;
	}

	*ret = 0;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipJointSwitch(SHORT* ret)
{
	// TODO: Add your implementation code here
	INFO_TRACE("WebVoipJointSwitch");
	TUP_RESULT tRet = tup_call_joint_switch();
	if(tRet == TUP_FAIL)
	{
		LOG_ERROR("WebVoipJointSwitch failed.");
		*ret = -1;
		return S_FALSE;
	}
	*ret = 0;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::WebVoipGetLastError(unsigned int errornum, BSTR* errDesc)
{
	// TODO: Add your implementation code here
	INFO_TRACE("WebVoipGetLastError:errornum=%d",errornum);
	const TUP_CHAR* desc = tup_call_get_err_description(errornum);
	if(desc == NULL)
	{
		LOG_ERROR("WebVoipJointSwitch failed.");
		return S_FALSE;
	}
	*errDesc = SysAllocString(CTools::UTF2UNICODE(desc).c_str());
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::get_VoipLoginResultEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");

	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipLoginResultEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipLoginResultEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipLoginResultEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipLogoutResultEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");

	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipLogoutResultEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipLogoutResultEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipLogoutResultEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipCallOutgoingEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipCallOutgoingEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipCallOutgoingEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipCallOutgoingEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipPeerRingbackEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipPeerRingbackEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipPeerRingbackEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipPeerRingbackEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipRtpCreatedEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipRtpCreatedEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipRtpCreatedEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipRtpCreatedEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipIncomingCallEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipIncomingCallEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipIncomingCallEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipIncomingCallEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipStartTalkingEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipStartTalkingEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipStartTalkingEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipStartTalkingEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipCallCloseResultEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipCallCloseResultEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipCallCloseResultEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipCallCloseResultEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipVoiceVideoSwitchResultEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipVoiceVideoSwitchResultEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipVoiceVideoSwitchResultEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipVoiceVideoSwitchResultEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipNotifyVoiceSwitchToVideoReqEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipNotifyVoiceSwitchToVideoReqEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipNotifyVoiceSwitchToVideoReqEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipNotifyVoiceSwitchToVideoReqEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipNotifyVideoSwitchToVoiceReqEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipNotifyVideoSwitchToVoiceReqEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipNotifyVideoSwitchToVoiceReqEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipNotifyVideoSwitchToVoiceReqEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipCallHoldSuccessEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipCallHoldSuccessEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipCallHoldSuccessEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipCallHoldSuccessEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipCallHoldFailedEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipCallHoldFailedEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipCallHoldFailedEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipCallHoldFailedEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipCallUnHoldSuccessEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipCallUnHoldSuccessEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipCallUnHoldSuccessEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipCallUnHoldSuccessEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipCallUnHoldFailedEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipCallUnHoldFailedEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipCallUnHoldSuccessEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipCallUnHoldSuccessEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipCallBlindTransSuccessEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipCallBlindTransSuccessEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipCallBlindTransSuccessEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipCallBlindTransSuccessEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipCallBlindTransFailedEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipCallBlindTransFailedEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipCallBlindTransFailedEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipCallBlindTransFailedEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipCallConsultTransSuccessEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipCallConsultTransSuccessEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipCallConsultTransSuccessEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipCallConsultTransSuccessEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipCallConsultTransFailedEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipCallConsultTransFailedEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipCallConsultTransFailedEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipCallConsultTransFailedEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipIPTServiceRegSuccessEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipIPTServiceRegSuccessEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipIPTServiceRegSuccessEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipIPTServiceRegSuccessEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipIPTServiceRegFailedEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipIPTServiceRegFailedEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipIPTServiceRegFailedEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipIPTServiceRegFailedEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipPhoneStatusChangeEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipPhoneStatusChangeEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipPhoneStatusChangeEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipPhoneStatusChangeEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipStartRecordingEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipStartRecordingEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipStartRecordingEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipStartRecordingEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipRecordFailedEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipRecordFailedEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipRecordFailedEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipRecordFailedEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipUnRecordSuccessEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipUnRecordSuccessEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipUnRecordSuccessEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipUnRecordSuccessEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipUnRecordFailedEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipUnRecordFailedEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipUnRecordFailedEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipUnRecordFailedEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipJointStartResultEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipJointStartResultEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipJointStartResultEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipJointStartResultEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipJointStopResultEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipJointStopResultEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipJointStopResultEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipJointStopResultEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipNotifyJointSwitchToPhoneEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipNotifyJointSwitchToPhoneEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipNotifyJointSwitchToPhoneEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipNotifyJointSwitchToPhoneEvent failed");
	return S_FALSE;
}


STDMETHODIMP CWebVoipCtrl::get_VoipNotifyJointSwitchToPCEvent(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipNotifyJointSwitchToPCEvent(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if (newVal.vt == VT_DISPATCH)
	{
		m_VoipNotifyJointSwitchToPCEvent = newVal.pdispVal;
		return S_OK;
	}

	LOG_ERROR("put_VoipNotifyJointSwitchToPCEvent failed");
	return S_FALSE;
}

STDMETHODIMP CWebVoipCtrl::get_VoipSIPServerIP(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(NULL == pVal)
	{
		return S_FALSE;
	}
	pVal->vt = VT_BSTR;
	pVal->bstrVal = SysAllocString(CTools::UTF2UNICODE(VoipSIPServerIP).c_str());
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipSIPServerIP(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");

	switch (newVal.vt)
	{
	case VT_BSTR://字符串
		VoipSIPServerIP = CTools::UNICODE2UTF(newVal.bstrVal);
		break;
	}

	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::get_VoipSIPServerPort(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(NULL == pVal)
	{
		return S_FALSE;
	}
	pVal->vt = VT_I4;
	pVal->intVal = VoipSIPServerPort;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipSIPServerPort(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	switch (newVal.vt)
	{
	case VT_I4://整形
		VoipSIPServerPort = newVal.intVal;
		break;
	}

	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::get_VoipUserInfo_Id(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(NULL == pVal)
	{
		return S_FALSE;
	}
	pVal->vt = VT_BSTR;
	pVal->bstrVal = SysAllocString(CTools::UTF2UNICODE(VoipUserInfo_Id).c_str());
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipUserInfo_Id(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	switch (newVal.vt)
	{
	case VT_BSTR://字符串
		VoipUserInfo_Id = CTools::UNICODE2UTF(newVal.bstrVal);
		break;
	}
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::get_VoipUserInfo_UserName(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(NULL == pVal)
	{
		return S_FALSE;
	}
	pVal->vt = VT_BSTR;
	pVal->bstrVal = SysAllocString(CTools::UTF2UNICODE(VoipUserInfo_UserName).c_str());
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipUserInfo_UserName(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	switch (newVal.vt)
	{
	case VT_BSTR://字符串
		VoipUserInfo_UserName = CTools::UNICODE2UTF(newVal.bstrVal);
		break;
	}

	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::get_VoipUserInfo_Password(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(NULL == pVal)
	{
		return S_FALSE;
	}
	pVal->vt = VT_BSTR;
	pVal->bstrVal = SysAllocString(CTools::UTF2UNICODE(VoipUserInfo_Password).c_str());
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipUserInfo_Password(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	switch (newVal.vt)
	{
	case VT_BSTR://字符串
		VoipUserInfo_Password = CTools::UNICODE2UTF(newVal.bstrVal);
		break;
	}

	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::get_VoipCallInfo_Type(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(NULL == pVal)
	{
		return S_FALSE;
	}
	pVal->vt = VT_I4;
	pVal->intVal = VoipCallInfo_Type;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipCallInfo_Type(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	switch (newVal.vt)
	{
	case VT_I4://整形
		VoipCallInfo_Type = newVal.intVal;
		break;
	}
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::get_VoipCallMode(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(NULL == pVal)
	{
		return S_FALSE;
	}
	pVal->vt = VT_I4;
	pVal->intVal = VoipCallMode;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipCallMode(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	switch (newVal.vt)
	{
	case VT_I4://整形
		VoipCallMode = newVal.intVal;
		break;
	}
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::get_VoipCallInfo_Id(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(NULL == pVal)
	{
		return S_FALSE;
	}
	pVal->vt = VT_I4;
	pVal->intVal = VoipCallInfo_Id;

	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipCallInfo_Id(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	switch (newVal.vt)
	{
	case VT_I4://整形
		VoipCallInfo_Id = newVal.intVal;
		break;
	}

	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::get_VoipCallInfo_CallerStatus(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(NULL == pVal)
	{
		return S_FALSE;
	}
	pVal->vt = VT_I4;
	pVal->intVal = VoipCallInfo_CallerStatus;

	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipCallInfo_CallerStatus(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	switch (newVal.vt)
	{
	case VT_I4:
		VoipCallInfo_CallerStatus = newVal.intVal;
		break;
	}

	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::get_VoipCallInfo_CalleeStatus(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(NULL == pVal)
	{
		return S_FALSE;
	}
	pVal->vt = VT_I4;
	pVal->intVal = VoipCallInfo_CalleeStatus;

	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipCallInfo_CalleeStatus(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	switch (newVal.vt)
	{
	case VT_I4:
		VoipCallInfo_CalleeStatus = newVal.intVal;
		break;
	}
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::get_VoipCallInfo_CallerNum(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(NULL == pVal)
	{
		return S_FALSE;
	}
	pVal->vt = VT_BSTR;
	pVal->bstrVal = SysAllocString(CTools::UTF2UNICODE(VoipCallInfo_CallerNum).c_str());

	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipCallInfo_CallerNum(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	switch (newVal.vt)
	{
	case VT_BSTR:
		VoipCallInfo_CallerNum = CTools::UNICODE2UTF(newVal.bstrVal);;
		break;
	}
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::get_VoipCallInfo_CalleeNum(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(NULL == pVal)
	{
		return S_FALSE;
	}
	pVal->vt = VT_BSTR;
	pVal->bstrVal = SysAllocString(CTools::UTF2UNICODE(VoipCallInfo_CalleeNum).c_str());

	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipCallInfo_CalleeNum(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	switch (newVal.vt)
	{
	case VT_BSTR:
		VoipCallInfo_CalleeNum = CTools::UNICODE2UTF(newVal.bstrVal);;
		break;
	}
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::get_VoipCallInfo_OrgCalleeNum(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	if(NULL == pVal)
	{
		return S_FALSE;
	}
	pVal->vt = VT_BSTR;
	pVal->bstrVal = SysAllocString(CTools::UTF2UNICODE(VoipCallInfo_OrgCalleeNum).c_str());
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipCallInfo_OrgCalleeNum(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	switch (newVal.vt)
	{
	case VT_BSTR:
		VoipCallInfo_OrgCalleeNum = CTools::UNICODE2UTF(newVal.bstrVal);;
		break;
	}
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::get_VoipCallInfo_LineId(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(NULL == pVal)
	{
		return S_FALSE;
	}
	pVal->vt = VT_I4;
	pVal->intVal = VoipCallInfo_LineId;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipCallInfo_LineId(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	switch (newVal.vt)
	{
	case VT_I4:
		VoipCallInfo_LineId = newVal.intVal;
		break;
	}
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::get_VoipCallInfo_LineType(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(NULL == pVal)
	{
		return S_FALSE;
	}
	pVal->vt = VT_I4;
	pVal->intVal = VoipCallInfo_LineType;

	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipCallInfo_LineType(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	switch (newVal.vt)
	{
	case VT_I4:
		VoipCallInfo_LineType = newVal.intVal;
		break;
	}
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::get_MediaType(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(NULL == pVal)
	{
		return S_FALSE;
	}
	pVal->vt = VT_I4;
	pVal->intVal = MediaType;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_MediaType(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	switch (newVal.vt)
	{
	case VT_I4:
		MediaType = newVal.intVal;
		break;
	}

	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::get_VoipUserInfo_AccNum(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(NULL == pVal)
	{
		return S_FALSE;
	}
	pVal->vt = VT_BSTR;
	pVal->bstrVal = SysAllocString(CTools::UTF2UNICODE(VoipUserInfo_AccNum).c_str());

	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipUserInfo_AccNum(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	switch (newVal.vt)
	{
	case VT_BSTR:
		VoipUserInfo_AccNum = CTools::UNICODE2UTF(newVal.bstrVal);;
		break;
	}
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::get_VoipUserInfo_AccStatus(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(NULL == pVal)
	{
		return S_FALSE;
	}
	pVal->vt = VT_I4;
	pVal->intVal = VoipUserInfo_AccStatus;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipUserInfo_AccStatus(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	switch (newVal.vt)
	{
	case VT_I4:
		VoipUserInfo_AccStatus = newVal.intVal;
		break;
	}
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::get_VoipUserInfo_SipStatus(VARIANT* pVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	if(NULL == pVal)
	{
		return S_FALSE;
	}
	pVal->vt = VT_I4;
	pVal->intVal = VoipUserInfo_SipStatus;
	return S_OK;
}


STDMETHODIMP CWebVoipCtrl::put_VoipUserInfo_SipStatus(VARIANT newVal)
{
	// TODO: Add your implementation code here
	INFO_TRACE("");
	switch (newVal.vt)
	{
	case VT_I4:
		VoipUserInfo_SipStatus = newVal.intVal;
		break;
	}
	return S_OK;
}
