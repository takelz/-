
#include"HookPoint.h"
#include"Dxg2d\input.h"
#include"PlayerManager.h"

void HookPoint::Hook(D3DXVECTOR2 position) {
	if (PlayerManager::Instance()->hookOn) return;

	if (DIGetMouseTrigger(DIK_RIGHT_CLICK)) {
		POINT lpPoint;

		GetCursorPos(&lpPoint);
		ScreenToClient(GetHwnd(), &lpPoint);

		if (lpPoint.x > position.x - 30 && lpPoint.x < position.x + 30 &&
			lpPoint.y > position.y -30 && lpPoint.y < position.y + 30)
		PlayerManager::Instance()->StartHook(position);
	}

}


/*É}ÉEÉX
//POINT lpPoint;

//GetCursorPos(&lpPoint);
//ScreenToClient(GetHwnd(), &lpPoint);
*/