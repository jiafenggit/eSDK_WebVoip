#pragma once
#include "tup_def.h"

class CWebVoipCtrl;
class NotifyCallBack
{
private:
	NotifyCallBack(void);
	~NotifyCallBack(void);
public:
	static TUP_VOID CallNotify(TUP_UINT32 msgid, TUP_UINT32 param1, TUP_UINT32 param2, TUP_VOID *data);
	static CWebVoipCtrl* m_pCtrl;
};


