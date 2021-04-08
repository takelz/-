// プレイヤーの地面接地判定等
//
#ifndef __PLAYERSENSORCOLLIDER__
#define __PLAYERSENSORCOLLIDER__

#include"main.h"
#include"Dxg2d\GameObj.h"


class GroundedCollider:public GameObj {
public:
	void Init();
	void Update();
	void Draw();		// デバック用
	
	bool isJumped;		// ジャンプを消費したか(地面に着くまで回復しない)


private:
	bool isGround;		// 今地面に足をついているか


};


#endif // !__PLAYERSENSORCOLLIDER__