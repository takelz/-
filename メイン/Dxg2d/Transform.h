// 座標関係
// 
//
// ～更新履歴～
// 2018/07/24	作成
//

#ifndef __TRANSFORM__
#define __TRANSFORM__

//#include"../main.h"
#include"Sprite.h"
#include"StParam.h"


class Scale {
public:
	float x;
	float y;
};


class Transform {
public:
	//＝＝＝＝＝関数＝＝＝＝＝

	// transformの情報をスプライトに更新
	void TransformToSprite(Sprite *sprite);	
	void SetTag(LPCSTR name);




	//＝＝＝＝＝変数＝＝＝＝＝
	D3DXVECTOR2 size;
	D3DXVECTOR2 pos;
	D3DXVECTOR2 scale;
	float rotate;
	bool notScroll;		// スクロールをしない

	Transform();
	

private:
	D3DXVECTOR2 parentSize;
	D3DXVECTOR2 parentPos;
	float parentRotate;

};



#endif // !__TRANSFORM__
