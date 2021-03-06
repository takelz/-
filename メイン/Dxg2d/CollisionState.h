// RC_Ìo^îñ
//
// `XVð`
// 2018/07/24	®¬
//


#ifndef __COLLISION_STATE__
#define __COLLISION_STATE__

//#include"StParam.h"
#include"Transform.h"

#define MAX_NOTCOLL_NUM (16)


enum CollisionType {
	C_TYPE_SQUARE,
	C_TYPE_CIRCLE,
};

// vZpÌ\¢Ì
typedef struct {
	float leftX;	// ¶X
	float rightX;	// EX
	float upY;		// ãY
	float downY;	// ºY
	float centerX;	// SX
	float centerY;	// SY
	float radiusX;	// ¼aX(S©çÌ£)
	float radiusY;	// ¼aY
	float rotate;
}CollCalcNum;

// ¸_
typedef struct {
	float x;
	float y;
}LINEPOINT;

// RC_²ßpÌ\¢Ì
typedef struct {
	float top;		// ã
	float bottom;	// º
	float left;		// ¶
	float right;	// E
	float radius;	// ¼a(RC_ª~Ìê)
	D3DXVECTOR2 pos;// Êu
}EDITCOLLIDER;


// RC_ÌÛ¶
class CollisionState {
public:

	//Ö

	CollisionState();
	CollisionState(Transform *paramTransform, TagName paramTagName, int registerNum,CollisionType paramType, TagName *notCollArray,EDITCOLLIDER *editColl);
	CollCalcNum CollisionState::CalcPosNum();

	//Ï

	Transform		*pTransform;	// ÀWÌAhXðÛ¶
	TagName			tagName;		// õpÌ^O¼
	CollisionType	type;			// RC_Ì^Cv(³)
	TagName			*notCollideTag;
	EDITCOLLIDER	*editCollider;

	unsigned int collNum;	// RC_ÌÂÊÔ
	bool	enable;			// RC_ªLø»
	bool	trigger;		// trueÈç¨ÌÍÑÊ·é

private:
	CollCalcNum cPos;
};




#endif // !__COLLISION_STATE__
