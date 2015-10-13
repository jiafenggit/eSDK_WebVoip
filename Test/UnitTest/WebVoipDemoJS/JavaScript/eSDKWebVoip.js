var WebVoipCtrl = null;
var isLoad = false;
var isLogin = false;
var varcallid = 0;

function UpadteWindow(result)
{
	// alert(result);
	var text = document.getElementById("result").innerHTML + "\r\n" + result;
	document.getElementById("result").innerHTML = text;
	document.getElementById('result').scrollTop = document.getElementById('result').scrollHeight;
}
function VoipLoginResultEvent(sip_id, sip_username, sip_account, acc_status, errorCode)
{
	var sip_id="sip_id="+sip_id;
	var sip_username="sip_username="+sip_username;
	var sip_account="sip_account="+sip_account;
	var acc_status="acc_status="+acc_status;
	var errorCode="errorCode="+errorCode;
	var result=sip_id+";"+sip_username+";"+sip_account+";"+acc_status+";"+errorCode+";";
	if(WebVoipCtrl)
	{
		//WebVoipCtrl.WebVoipSetMediaDevice(2,1);
	}

	UpadteWindow(result);
}

function VoipLogoutResultEvent(result, errcode)
{
	var content="result = "+result+";errcode = "+errcode+";";
	UpadteWindow(content);
}

function VoipCallOutgoingEvent(callId,callType,callStatus,callerName,callerNum,isCallIn,isPeerHangup,errorCode)
{
	var content = "VoipCallOutgoingEvent";
	UpadteWindow(content);
}
function VoipPeerRingbackEvent(callId,callType,callStatus,callerName,isPeerHangup,errorCode)
{
	var content = "VoipPeerRingbackEvent";
	UpadteWindow(content);
}
function VoipRtpCreatedEvent(callId)
{
	var content = "VoipRtpCreatedEvent";
	UpadteWindow(content);
}
function VoipIncomingCallEvent(callId,callType,callStatus,callerName,callerNum,isCallIn,isPeerHangup,errorCode)
{
	var content = "VoipIncomingCallEvent";
	$("#incomingvalue").val(callerNum);
	UpadteWindow(content);
}
function VoipStartTalkingEvent(callId,callType,callStatus,callerName,callerNum,isCallIn,isPeerHangup,errorCode)
{
	var content = "VoipStartTalkingEvent";
	varcallid = callId;
	UpadteWindow(content);
}
function VoipCallCloseResultEvent(callId,callType,callStatus,callerName,callerNum,isCallIn,isPeerHangup,errorCode)
{
	var content = "VoipCallCloseResultEvent";
	WebVoipCtrl.VoipCallInfo_Id = 0;
	UpadteWindow(content);
}
function VoipVoiceVideoSwitchResultEvent()
{
	var content = "VoipVoiceVideoSwitchResultEvent";
	UpadteWindow(content);
}
function VoipNotifyVoiceSwitchToVideoReqEvent()
{
	var content = "VoipNotifyVoiceSwitchToVideoReqEvent";
	UpadteWindow(content);
}
function VoipNotifyVideoSwitchToVoiceReqEvent()
{
	var content = "VoipNotifyVideoSwitchToVoiceReqEvent";
	UpadteWindow(content);
}

function VoipCallHoldSuccessEvent()
{
	var content = "VoipCallHoldSuccessEvent";
	UpadteWindow(content);
}


function VoipCallHoldFailedEvent()
{
	var content = "VoipCallHoldFailedEvent";
	UpadteWindow(content);
}


function VoipCallUnHoldSuccessEvent()
{
	var content = "VoipCallUnHoldSuccessEvent";
	UpadteWindow(content);
}

function VoipCallUnHoldFailedEvent()
{
	var content = "VoipCallUnHoldFailedEvent";
	UpadteWindow(content);
}

function VoipCallBlindTransSuccessEvent()
{
	var content = "VoipCallBlindTransSuccessEvent";
	UpadteWindow(content);
}

function VoipCallBlindTransFailedEvent()
{
	var content = "VoipCallBlindTransFailedEvent";
	UpadteWindow(content);
}

function VoipCallConsultTransSuccessEvent()
{
	var content = "VoipCallConsultTransSuccessEvent";
	UpadteWindow(content);
}
function VoipCallConsultTransFailedEvent()
{
	var content = "VoipCallConsultTransFailedEvent";
	UpadteWindow(content);
}
function VoipIPTServiceRegSuccessEvent()
{
	var content = "VoipIPTServiceRegSuccessEvent";
	UpadteWindow(content);
}
function VoipIPTServiceRegFailedEvent()
{
	var content = "VoipIPTServiceRegFailedEvent";
	UpadteWindow(content);
}
function VoipPhoneStatusChangeEvent()
{
	var content = "VoipPhoneStatusChangeEvent";
	UpadteWindow(content);
}
function VoipStartRecordingEvent()
{
	var content = "VoipStartRecordingEvent";
	UpadteWindow(content);
}
function VoipRecordFailedEvent()
{
	var content = "VoipRecordFailedEvent";
	UpadteWindow(content);
}
function VoipUnRecordSuccessEvent()
{
	var content = "VoipUnRecordSuccessEvent";
	UpadteWindow(content);
}
function VoipUnRecordFailedEvent()
{
	var content = "VoipUnRecordFailedEvent";
	UpadteWindow(content);
}
function VoipJointStartResultEvent()
{
	var content = "VoipJointStartResultEvent";
	UpadteWindow(content);
}

function VoipJointStopResultEvent()
{
	var content = "VoipJointStopResultEvent";
	UpadteWindow(content);
}

function VoipNotifyJointSwitchToPhoneEvent()
{
	var content = "VoipNotifyJointSwitchToPhoneEvent";
	UpadteWindow(content);
}

function VoipNotifyJointSwitchToPCEvent()
{
	var content = "VoipNotifyJointSwitchToPCEvent";
	UpadteWindow(content);
}


function Init()
{
	WebVoipCtrl=document.createElement('object');
	document.body.appendChild(WebVoipCtrl);
	WebVoipCtrl.style.width = "100px";
	WebVoipCtrl.style.height = "200px";
	WebVoipCtrl.style.position = "absolute";
	WebVoipCtrl.style.left = "800px";
	WebVoipCtrl.style.top = "250px";
	WebVoipCtrl.classid= "clsid:25DEB499-D532-48E2-9704-4DBB71115A31"; 
	WebVoipCtrl.visible = "false";

	if(WebVoipCtrl)
	{		
		WebVoipCtrl.WebVoipInitialize();
		WebVoipCtrl.VoipLoginResultEvent = VoipLoginResultEvent;	
		WebVoipCtrl.VoipLogoutResultEvent = VoipLogoutResultEvent;		
		WebVoipCtrl.VoipCallOutgoingEvent = VoipCallOutgoingEvent;
		WebVoipCtrl.VoipPeerRingbackEvent = VoipPeerRingbackEvent;
		WebVoipCtrl.VoipRtpCreatedEvent = VoipRtpCreatedEvent;
		WebVoipCtrl.VoipIncomingCallEvent = VoipIncomingCallEvent;
		WebVoipCtrl.VoipStartTalkingEvent = VoipStartTalkingEvent;
		WebVoipCtrl.VoipCallCloseResultEvent = VoipCallCloseResultEvent;
		WebVoipCtrl.VoipVoiceVideoSwitchResultEvent = VoipVoiceVideoSwitchResultEvent;
		WebVoipCtrl.VoipNotifyVoiceSwitchToVideoReqEvent = VoipNotifyVoiceSwitchToVideoReqEvent;
		WebVoipCtrl.VoipNotifyVideoSwitchToVoiceReqEvent = VoipNotifyVideoSwitchToVoiceReqEvent;
		WebVoipCtrl.VoipCallHoldSuccessEvent = VoipCallHoldSuccessEvent;
		WebVoipCtrl.VoipCallHoldFailedEvent = VoipCallHoldFailedEvent;
		WebVoipCtrl.VoipCallUnHoldSuccessEvent = VoipCallUnHoldSuccessEvent;
		WebVoipCtrl.VoipCallUnHoldFailedEvent = VoipCallUnHoldFailedEvent;
		WebVoipCtrl.VoipCallHoldSuccessEvent = VoipCallHoldSuccessEvent;
		WebVoipCtrl.VoipCallHoldFailedEvent = VoipCallHoldFailedEvent;
		WebVoipCtrl.VoipCallUnHoldSuccessEvent = VoipCallUnHoldSuccessEvent;
		WebVoipCtrl.VoipCallUnHoldFailedEvent = VoipCallUnHoldFailedEvent;
		WebVoipCtrl.VoipCallBlindTransSuccessEvent = VoipCallBlindTransSuccessEvent;
		WebVoipCtrl.VoipCallBlindTransFailedEvent = VoipCallBlindTransFailedEvent;
		WebVoipCtrl.VoipCallConsultTransSuccessEvent = VoipCallConsultTransSuccessEvent;
		WebVoipCtrl.VoipCallConsultTransFailedEvent = VoipCallConsultTransFailedEvent;
		WebVoipCtrl.VoipIPTServiceRegSuccessEvent = VoipIPTServiceRegSuccessEvent;
		WebVoipCtrl.VoipIPTServiceRegFailedEvent = VoipIPTServiceRegFailedEvent;
		WebVoipCtrl.VoipPhoneStatusChangeEvent = VoipPhoneStatusChangeEvent;
		WebVoipCtrl.VoipStartRecordingEvent = VoipStartRecordingEvent;
		WebVoipCtrl.VoipRecordFailedEvent = VoipRecordFailedEvent;
		WebVoipCtrl.VoipUnRecordSuccessEvent = VoipUnRecordSuccessEvent;
		WebVoipCtrl.VoipUnRecordFailedEvent = VoipUnRecordFailedEvent;
		WebVoipCtrl.VoipJointStartResultEvent = VoipJointStartResultEvent;
		WebVoipCtrl.VoipJointStopResultEvent = VoipJointStopResultEvent;
		WebVoipCtrl.VoipNotifyJointSwitchToPhoneEvent = VoipNotifyJointSwitchToPhoneEvent;
		WebVoipCtrl.VoipNotifyJointSwitchToPCEvent = VoipNotifyJointSwitchToPCEvent;
		
	}
}

function Login()
{
	if(WebVoipCtrl)
	{

		WebVoipCtrl.WebVoipLogin();
	}
}

function getvalue()
{
	if(WebVoipCtrl)
	{
		var VoipSIPServerIP = "VoipSIPServerIP="+WebVoipCtrl.VoipSIPServerIP;
		UpadteWindow(VoipSIPServerIP);
		var VoipSIPServerPort = "VoipSIPServerPort="+WebVoipCtrl.VoipSIPServerPort;
		UpadteWindow(VoipSIPServerPort);

		var VoipCallInfo_Id = "VoipCallInfo_Id="+WebVoipCtrl.VoipCallInfo_Id;
		UpadteWindow(VoipCallInfo_Id);
		var VoipCallInfo_Type = "VoipCallInfo_Type="+WebVoipCtrl.VoipCallInfo_Type;
		UpadteWindow(VoipCallInfo_Type);
		var VoipCallInfo_CallerStatus = "VoipCallInfo_CallerStatus="+WebVoipCtrl.VoipCallInfo_CallerStatus;
		UpadteWindow(VoipCallInfo_CallerStatus);
		var VoipCallInfo_CalleeStatus = "VoipCallInfo_CalleeStatus="+WebVoipCtrl.VoipCallInfo_CalleeStatus;
		UpadteWindow(VoipCallInfo_CalleeStatus);
		var VoipCallInfo_CallerNum = "VoipCallInfo_CallerNum="+WebVoipCtrl.VoipCallInfo_CallerNum;
		UpadteWindow(VoipCallInfo_CallerNum);
		var VoipCallInfo_CalleeNum = "VoipCallInfo_CalleeNum="+WebVoipCtrl.VoipCallInfo_CalleeNum;
		UpadteWindow(VoipCallInfo_CalleeNum);
		var VoipCallInfo_OrgCalleeNum = "VoipCallInfo_OrgCalleeNum="+WebVoipCtrl.VoipCallInfo_OrgCalleeNum;
		UpadteWindow(VoipCallInfo_OrgCalleeNum);
		var VoipCallInfo_LineId = "VoipCallInfo_LineId="+WebVoipCtrl.VoipCallInfo_LineId;
		UpadteWindow(VoipCallInfo_LineId);
		var VoipCallInfo_LineType = "VoipCallInfo_LineType="+WebVoipCtrl.VoipCallInfo_LineType;
		UpadteWindow(VoipCallInfo_LineType);

		var VoipCallMode = "VoipCallMode="+WebVoipCtrl.VoipCallMode;
		UpadteWindow(VoipCallMode);
		var MediaType = "MediaType="+WebVoipCtrl.MediaType;
		UpadteWindow(MediaType);

		var VoipUserInfo_Id = "VoipUserInfo_Id="+WebVoipCtrl.VoipUserInfo_Id;
		UpadteWindow(VoipUserInfo_Id);
		var VoipUserInfo_UserName = "VoipUserInfo_UserName="+WebVoipCtrl.VoipUserInfo_UserName;
		UpadteWindow(VoipUserInfo_UserName);
		var VoipUserInfo_Password = "VoipUserInfo_Password="+WebVoipCtrl.VoipUserInfo_Password;
		UpadteWindow(VoipUserInfo_Password);
		var VoipUserInfo_AccNum = "VoipUserInfo_AccNum="+WebVoipCtrl.VoipUserInfo_AccNum;
		UpadteWindow(VoipUserInfo_AccNum);
		var VoipUserInfo_AccStatus = "VoipUserInfo_AccStatus="+WebVoipCtrl.VoipUserInfo_AccStatus;
		UpadteWindow(VoipUserInfo_AccStatus);
		var VoipUserInfo_SipStatus = "VoipUserInfo_SipStatus="+WebVoipCtrl.VoipUserInfo_SipStatus;
		UpadteWindow(VoipUserInfo_SipStatus);
	}
}

function setvalue()
{
	if(WebVoipCtrl)
	{
		var ip = $("#SIPServerIP").val();
		var port = parseInt($("#SIPServerPort").val());
		WebVoipCtrl.VoipSIPServerIP = ip;
		WebVoipCtrl.VoipSIPServerPort = port;

		var user = $("#UserInfo_Id").val();
		var pwd = $("#UserInfo_Password").val();
		var name = $("#UserInfo_UserName").val();
		WebVoipCtrl.VoipUserInfo_Id = user;
		WebVoipCtrl.VoipUserInfo_UserName = name;
		WebVoipCtrl.VoipUserInfo_Password = pwd;


		var VoipCallInfo_Id = parseInt($("#CallInfo_Id").val());
		WebVoipCtrl.VoipCallInfo_Id = VoipCallInfo_Id;

		var VoipCallInfo_Type =  parseInt($("#CallInfo_Type").val());
		WebVoipCtrl.VoipCallInfo_Type = VoipCallInfo_Type;

		var VoipCallInfo_CallerStatus = parseInt($("#CallInfo_CallerStatus").val());
		WebVoipCtrl.VoipCallInfo_CallerStatus = VoipCallInfo_CallerStatus;

		var VoipCallInfo_CalleeStatus = parseInt($("#CallInfo_CalleeStatus").val());
		WebVoipCtrl.VoipCallInfo_CalleeStatus = VoipCallInfo_CalleeStatus;

		var VoipCallInfo_CallerNum = $("#CallInfo_CallerNum").val();;
		WebVoipCtrl.VoipCallInfo_CallerNum = VoipCallInfo_CallerNum;

		var VoipCallInfo_CalleeNum = $("#CallInfo_CalleeNum").val();;
		WebVoipCtrl.VoipCallInfo_CalleeNum = VoipCallInfo_CalleeNum;

		var VoipCallInfo_OrgCalleeNum = $("#CallInfo_OrgCalleeNum").val();;
		WebVoipCtrl.VoipCallInfo_OrgCalleeNum = VoipCallInfo_OrgCalleeNum;

		var VoipCallInfo_LineId = parseInt($("#CallInfo_LineId").val());
		WebVoipCtrl.VoipCallInfo_LineId = VoipCallInfo_LineId;

		var VoipCallInfo_LineType = parseInt($("#CallInfo_LineType").val());
		WebVoipCtrl.VoipCallInfo_LineType = VoipCallInfo_LineType;


		var VoipCallMode = parseInt($("#CallMode").val())
		WebVoipCtrl.VoipCallMode = VoipCallMode;
		var MediaType = parseInt($("#MediaTypeinput").val())
		WebVoipCtrl.MediaType = MediaType;



		var VoipUserInfo_AccNum = $("#UserInfo_AccNum").val();;
		WebVoipCtrl.VoipUserInfo_AccNum = VoipUserInfo_AccNum;

		var VoipUserInfo_AccStatus = parseInt($("#UserInfo_AccStatus").val())
		WebVoipCtrl.VoipUserInfo_AccStatus = VoipUserInfo_AccStatus;

		var VoipUserInfo_SipStatus = parseInt($("#UserInfo_SipStatus").val())
		WebVoipCtrl.VoipUserInfo_SipStatus = VoipUserInfo_SipStatus;

	}
}

function Logout()
{
	if(WebVoipCtrl)
	{
		WebVoipCtrl.WebVoipLogout();
	}
}

function Uninit()
{
	if(WebVoipCtrl)
	{
		WebVoipCtrl.WebVoipUninitialize();
	}
}

function WebVoipCall()
{
	if(WebVoipCtrl)
	{
		var ret=5;
		var callee = $("#callee").val(); 
		ret = WebVoipCtrl.WebVoipCall(callee,0);
		var content = "WebVoipCall RET="+ret;
		UpadteWindow(content);
		
	}
}

function WebVoipSetLocalVideoWindow()
{
	if(WebVoipCtrl)
	{
		var localwnd = parseInt($("#localwndid").val());
		ret = WebVoipCtrl.WebVoipSetLocalVideoWindow(localwnd,1,0,0,40,50);
		var remotewnd = parseInt($("#remotewndid").val());		
		ret = WebVoipCtrl.WebVoipSetLocalVideoWindow(remotewnd,0,0,0,50,40);
		var content = "WebVoipSetLocalVideoWindow RET="+ret;
		UpadteWindow(content);
	}
}

function WebVoipVideoCall()
{
	if(WebVoipCtrl)
	{
		var callee = $("#callee").val(); 
		var ret = WebVoipCtrl.WebVoipCall(callee,1);
		var content = "WebVoipCall RET="+ret;
		UpadteWindow(content);		
	}
}

function WebVoipIsEnableVideo(type)
{
	if(WebVoipCtrl)
	{
		var ret = WebVoipCtrl.WebVoipIsEnableVideo(type);
		var content = "WebVoipIsEnableVideo RET="+ret;
		UpadteWindow(content);
	}
}

function  WebVoipEnableVideoReply(type)
{
	if(WebVoipCtrl)
	{
		var ret = WebVoipCtrl.WebVoipEnableVideoReply(type);
		var content = "WebVoipEnableVideoReply RET="+ret;
		UpadteWindow(content);
	}
}
function  WebVoipDisableVideoReply(type)
{
	if(WebVoipCtrl)
	{
		var ret = WebVoipCtrl.WebVoipDisableVideoReply(type);
		var content = "WebVoipDisableVideoReply RET="+ret;
		UpadteWindow(content);
	}
}

function HangupVoipCall()
{
	if(WebVoipCtrl)
	{
		var ret = WebVoipCtrl.WebVoipHangup();
		var content = "WebVoipHangup RET="+ret;
		UpadteWindow(content);
	}
}

function AcceptVoipCall()
{
	if(WebVoipCtrl)
	{
		var ret = WebVoipCtrl.WebVoipAccept(0);
		var content = "WebVoipAccept RET="+ret;
		UpadteWindow(content);
	}
}
function RejectVoipCall()
{
	if(WebVoipCtrl)
	{
		var ret = WebVoipCtrl.WebVoipReject();
		var content = "WebVoipReject RET="+ret;
		UpadteWindow(content);
	}
}

function WebVoipDMTFSecondDial(key)
{
	if(WebVoipCtrl)
	{
		var ret = WebVoipCtrl.WebVoipDMTFSecondDial("0");
		var content = "WebVoipDMTFSecondDial RET="+ret;
		UpadteWindow(content);
	}
}

function WebVoipCallHold(ishold)
{
	if(WebVoipCtrl)
	{
		var ret = WebVoipCtrl.WebVoipCallHold(ishold);
		var content = "WebVoipCallHold RET="+ret;
		UpadteWindow(content);
	}
}


function WebVoipCallRingAlert()
{
	if(WebVoipCtrl)
	{
		var ret = WebVoipCtrl.WebVoipCallRingAlert();
		var content = "WebVoipCallRingAlert RET="+ret;
		UpadteWindow(content);
	}
}
function WebVoipCallBlindTransfer()
{
	if(WebVoipCtrl)
	{
		var phonenum = $("#transnum").val();
		var ret = WebVoipCtrl.WebVoipCallBlindTransfer(phonenum);
		var content = "WebVoipCallBlindTransfer RET="+ret;
		UpadteWindow(content);
	}
}

function WebVoipCallConsultTransfer()
{
	if(WebVoipCtrl)
	{
		var ret = WebVoipCtrl.WebVoipCallConsultTransfer(phonenum);
		var content = "WebVoipCallConsultTransfer RET="+ret;
		UpadteWindow(content);
	}
}

function WebVoipCallDivertTransfer()
{
	if(WebVoipCtrl)
	{
		var phonenum = $("#transnum").val();
		var ret = WebVoipCtrl.WebVoipCallDivertTransfer(phonenum);
		var content = "WebVoipCallDivertTransfer RET="+ret;
		UpadteWindow(content);
	}
}

function WebVoipSetCallForward(type)
{
	if(WebVoipCtrl)
	{
		var phonenum = $("#transnum").val();
		var ret = WebVoipCtrl.WebVoipSetCallForward(type,phonenum);
		var content = "WebVoipSetCallForward RET="+ret;
		UpadteWindow(content);
	}
}

function WebVoipSetCallDND(type)
{
	if(WebVoipCtrl)
	{
		var ret = WebVoipCtrl.WebVoipSetCallDND(type);
		var content = "WebVoipSetCallDND RET="+ret;
		UpadteWindow(content);
	}
}

function WebVoipSetCallACB(type)
{
	if(WebVoipCtrl)
	{
		var ret = WebVoipCtrl.WebVoipSetCallACB(type);
		var content = "WebVoipSetCallACB RET="+ret;
		UpadteWindow(content);
	}
}

function WebVoipSetMediaMute(type,ismute)
{
	if(WebVoipCtrl)
	{
		var ret = WebVoipCtrl.WebVoipSetMediaMute(type,ismute);
		var content = "WebVoipSetMediaMute RET="+ret;
		UpadteWindow(content);
	}
}

function WebVoipGetCurrMediaVolume(type)
{
	if(WebVoipCtrl)
	{
		var ret = WebVoipCtrl.WebVoipGetCurrMediaVolume(type);
		var content = "WebVoipGetCurrMediaVolume RET="+ret;
		if(type == 0)
		{
			$("#getmicvolume").val(ret);
		}
		else if(type == 1)
		{
			$("#getspkvolume").val(ret);
		}
		UpadteWindow(content);
	}
}

function WebVoipSetCurrMediaVolume0()
{
	if(WebVoipCtrl)
	{
		var volume = $("#setmicvolume").val();
		var ret = WebVoipCtrl.WebVoipSetCurrMediaVolume(0,volume);
		var content = "WebVoipSetCurrMediaVolume RET="+ret;
		UpadteWindow(content);
	}
}
function WebVoipSetCurrMediaVolume1()
{
	if(WebVoipCtrl)
	{
		var volume = $("#setspkvolume").val();
		var ret = WebVoipCtrl.WebVoipSetCurrMediaVolume(1,volume);
		var content = "WebVoipSetCurrMediaVolume RET="+ret;
		UpadteWindow(content);
	}
}

function WebVoipSetMediaDevice(type)
{
	if(WebVoipCtrl)
	{
		var index = 0;
		if(0 == type)
		{
			index = parseInt($("#setmicindex").val());
		}
		if(1 == type)
		{
			index = parseInt($("#setspkindex").val());
		}
		if(2 == type)
		{
			index = parseInt($("#setvideoindex").val());
		}
		
		var ret = WebVoipCtrl.WebVoipSetMediaDevice(type,index);
		var content = "WebVoipSetMediaDevice RET="+ret;
		UpadteWindow(content);
	}
}

function WebVoipGetMediaDevice(type)
{
	if(WebVoipCtrl)
	{	
		var count;
		var ret = WebVoipCtrl.WebVoipGetMediaDevice(type,count);
		if(0 == type)
		{
			$("#getmicdev").val(ret);
		}
		if(1 == type)
		{
			$("#getspkdev").val(ret);
		}
		if(2 == type)
		{
			$("#getvideodev").val(ret);
		}		
		var content = "WebVoipGetMediaDevice RET="+ret;
		UpadteWindow(content);
	}	
}
function WebVoipAudioRecord(type)
{
	if(WebVoipCtrl)
	{
		var ret = WebVoipCtrl.WebVoipAudioRecord(type);
		var content = "WebVoipAudioRecord RET="+ret;
		UpadteWindow(content);
	}
}

function WebVoipJointSetting()
{
	if(WebVoipCtrl)
	{
		var linknum = parseInt($("#linknum").val());
		var ret = WebVoipCtrl.WebVoipJointSetting(linknum);
		var content = "WebVoipPhoneJoint RET="+ret;
		UpadteWindow(content);
	}
}

function WebVoipPhoneJoint(type)
{
	if(WebVoipCtrl)
	{
		var ret = WebVoipCtrl.WebVoipPhoneJoint(type);
		var content = "WebVoipPhoneJoint RET="+ret;
		UpadteWindow(content);
	}
}
function WebVoipJointSwitch()
{
	if(WebVoipCtrl)
	{
		var ret = WebVoipCtrl.WebVoipJointSwitch();
		var content = "WebVoipJointSwitch RET="+ret;
		UpadteWindow(content);
	}
}
function WebVoipGetLastError()
{
	if(WebVoipCtrl)
	{
		var errorcode = parseInt($("#geterrorcode").val());
		var ret = WebVoipCtrl.WebVoipGetLastError(errorcode);
		$("#geterrordesc").val(ret);
		var content = "WebVoipGetLastError RET="+ret;
		UpadteWindow(content);
	}
}