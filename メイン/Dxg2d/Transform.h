// ΐWΦW
// 
//
// `XVπ`
// 2018/07/24	μ¬
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
	//Φ

	// transformΜξρπXvCgΙXV
	void TransformToSprite(Sprite *sprite);	
	void SetTag(LPCSTR name);




	//Ο
	D3DXVECTOR2 size;
	D3DXVECTOR2 pos;
	D3DXVECTOR2 scale;
	float rotate;
	bool notScroll;		// XN[π΅Θ’

	Transform();
	

private:
	D3DXVECTOR2 parentSize;
	D3DXVECTOR2 parentPos;
	float parentRotate;

};



#endif // !__TRANSFORM__
