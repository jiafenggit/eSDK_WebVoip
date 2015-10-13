#include "stdafx.h"
#include "NotifyCallBack.h"
#include "WebVoipCtrl.h"
#include "Log.h"

CWebVoipCtrl* NotifyCallBack::m_pCtrl = NULL;
NotifyCallBack::NotifyCallBack(void)
{
}

NotifyCallBack::~NotifyCallBack(void)
{
}

TUP_VOID NotifyCallBack::CallNotify(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *pBody)
{
	LOG_INFO("msgid=%d,param1=%d,param2=%d",msgid,param1,param2);
	switch (msgid)
	{
	case CALL_E_EVT_SIPACCOUNT_INFO:
		{
			CALL_S_SIP_ACCOUNT_INFO* accountInfo = (CALL_S_SIP_ACCOUNT_INFO*)pBody;
			CALL_S_SIP_ACCOUNT_INFO* Info = new CALL_S_SIP_ACCOUNT_INFO;
			memcpy(Info,accountInfo,sizeof(CALL_S_SIP_ACCOUNT_INFO));
			if(m_pCtrl != NULL)
			{
				m_pCtrl->PostMessage(WM_CALL_NOTIFY,(WPARAM)msgid,(LPARAM)Info);
			}
		}
		break;
	case CALL_E_EVT_CALL_STARTCALL_RESULT:
		break;
	case CALL_E_EVT_CALL_INCOMMING:
	case CALL_E_EVT_CALL_OUTGOING:
	case CALL_E_EVT_CALL_RINGBACK:
	case CALL_E_EVT_CALL_CONNECTED:
	case CALL_E_EVT_CALL_ENDED:
		{
			CALL_S_CALL_INFO* info = (CALL_S_CALL_INFO*)pBody;
			CALL_S_CALL_INFO* notifyInfo = new CALL_S_CALL_INFO;
			memcpy(notifyInfo,info,sizeof(CALL_S_CALL_INFO));
			if(m_pCtrl != NULL)
			{
				m_pCtrl->PostMessage(WM_CALL_NOTIFY,(WPARAM)msgid,(LPARAM)notifyInfo);
			}
		}
		break;
	case CALL_E_EVT_CALL_ADD_VIDEO:
	case CALL_E_EVT_CALL_DEL_VIDEO:	
		{
			TUP_UINT32 callid = param1;
			if(m_pCtrl != NULL)
			{
				m_pCtrl->PostMessage(WM_CALL_NOTIFY,(WPARAM)msgid,(LPARAM)callid);
			}
		}
		break;
	case CALL_E_EVT_CALL_MODIFY_VIDEO_RESULT:
		{
			CALL_S_MODIFY_VIDEO_RESULT* info = (CALL_S_MODIFY_VIDEO_RESULT*)pBody;
			CALL_S_MODIFY_VIDEO_RESULT* notifyInfo = new CALL_S_MODIFY_VIDEO_RESULT;
			memcpy(notifyInfo,info,sizeof(CALL_S_MODIFY_VIDEO_RESULT));
			if(m_pCtrl != NULL)
			{
				m_pCtrl->PostMessage(WM_CALL_NOTIFY,(WPARAM)msgid,(LPARAM)notifyInfo);
			}
		}
		break;
	case CALL_E_EVT_CALL_RTP_CREATED:
		{
			TUP_UINT32 callid = param1;
			if(m_pCtrl != NULL)
			{
				m_pCtrl->PostMessage(WM_CALL_NOTIFY,(WPARAM)msgid,(LPARAM)callid);
			}
		}
		break;
	case CALL_E_EVT_NET_QUALITY_CHANGE:
		{
			CALL_S_NETQUALITY_CHANGE* pInfo = (CALL_S_NETQUALITY_CHANGE*)pBody;
			CALL_S_NETQUALITY_CHANGE* pChangeInfo = new CALL_S_NETQUALITY_CHANGE;
			memcpy(pChangeInfo,pInfo,sizeof(CALL_S_NETQUALITY_CHANGE));

		}
		break;
	case CALL_E_EVT_STATISTIC_NETINFO:
		{
			CALL_S_STATISTIC_NETINFO* pNetInfo = (CALL_S_STATISTIC_NETINFO*)pBody;
		}
		break;
	case CALL_E_EVT_CALL_HOLD_SUCCESS:			//呼叫保持成功
	case CALL_E_EVT_CALL_HOLD_FAILED:			//呼叫保持失败
	case CALL_E_EVT_CALL_UNHOLD_SUCCESS:		//取消呼叫保持失败
	case CALL_E_EVT_CALL_UNHOLD_FAILED:			//取消呼叫保持失败
	case CALL_E_EVT_CALL_BLD_TRANSFER_SUCCESS:	//盲转成功
	case CALL_E_EVT_CALL_BLD_TRANSFER_FAILED:	//盲转失败
	case CALL_E_EVT_CALL_ATD_TRANSFER_SUCCESS:	//咨询转成功
	case CALL_E_EVT_CALL_ATD_TRANSFER_FAILED:	//咨询转失败
	case CALL_E_EVT_SET_IPT_SERVICE_SUCCESS:	//IPT服务登记成功
	case CALL_E_EVT_SET_IPT_SERVICE_FAILED:		//IPT服务登记失败
	case CALL_E_EVT_CALL_RECORD_SUCCESS:        /**< 录音开启成功 */
	case CALL_E_EVT_CALL_RECORD_FAILED:         /**< 录音开启失败 */
	case CALL_E_EVT_CALL_UNRECORD_SUCCESS:      /**< 录音关闭成功 */
	case CALL_E_EVT_CALL_UNRECORD_FAILED:       /**< 录音关闭失败 */
		{			
			TUP_UINT32 callid = param1;
			if(m_pCtrl != NULL)
			{
				m_pCtrl->PostMessage(WM_CALL_NOTIFY,(WPARAM)msgid,(LPARAM)callid);
			}
		}
		break;
	case CALL_E_EVT_TO_UI_JOINT_START:
	case CALL_E_EVT_TO_UI_JOINT_CLOSE:
	case CALL_E_EVT_TO_UI_JOINT_SWITCH_TO_PHONE:
	case CALL_E_EVT_TO_UI_JOINT_SWITCH_TO_PC:
		{
			CALL_S_JOINT_CMD_INFOS* pInfo = (CALL_S_JOINT_CMD_INFOS*)pBody;
			CALL_S_JOINT_CMD_INFOS* pNotifyInfo = new CALL_S_JOINT_CMD_INFOS;
			memcpy(pNotifyInfo,pInfo,sizeof(CALL_S_JOINT_CMD_INFOS));
			if(m_pCtrl != NULL)
			{
				m_pCtrl->PostMessage(WM_CALL_NOTIFY,(WPARAM)msgid,(LPARAM)pNotifyInfo);
			}			
		}
		break;
	case CALL_E_EVT_CONTACT_STATUS_CHANGE:
		{

		}
		break;
	case CALL_E_EVT_CALL_AUTHORIZE_SUCCESS:
		{
		}
		break;		
	case CALL_E_EVT_CALL_AUTHORIZE_FAILED:
		{
			//鉴权失败
		}
		break;
	case CALL_E_EVT_NEW_SERVICE_RIGHT:
		{
			//业务权限变更通知
			CALL_S_SERVICERIGHT_CFG* pInfo = (CALL_S_SERVICERIGHT_CFG*)pBody;
			CALL_S_SERVICERIGHT_CFG* pNotifyInfo = new CALL_S_SERVICERIGHT_CFG;
			memcpy(pNotifyInfo,pInfo,sizeof(CALL_S_SERVICERIGHT_CFG));
			if(m_pCtrl != NULL)
			{
				m_pCtrl->PostMessage(WM_CALL_NOTIFY,(WPARAM)msgid,(LPARAM)pNotifyInfo);
			}
		}
		break;

	}
	return;
}

