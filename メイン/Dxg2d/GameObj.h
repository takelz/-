// ゲームオブジェクト
// ゲームの基本的な要素。
//
// ～更新履歴～
//

#ifndef __GAMEOBJ__
#define __GAMEOBJ__

#include"Sprite.h"
#include"Transform.h"
#include"Collision.h"

class GameObj {
protected:
	Transform transform;
	Sprite sprite;
	Collision collision;



public:
	// 子オジェクトの更新。
	void AttachChild(Transform *parentTransform, D3DXVECTOR2 offsetPos);
	// 子オジェクトの更新。
	void AttachChild(Transform *parentTransform,float offsetX,float offsetY);
	// 子オジェクトの更新。
	void AttachChild(Transform *parentTransform);

};



#endif // !
