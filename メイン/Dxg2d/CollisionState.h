// コライダの登録情報
//
// ～更新履歴～
// 2018/07/24	完成
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

// 計算用の構造体
typedef struct {
	float leftX;	// 左X
	float rightX;	// 右X
	float upY;		// 上Y
	float downY;	// 下Y
	float centerX;	// 中心X
	float centerY;	// 中心Y
	float radiusX;	// 半径X(中心からの距離)
	float radiusY;	// 半径Y
	float rotate;
}CollCalcNum;

// 頂点
typedef struct {
	float x;
	float y;
}LINEPOINT;

// コライダ調節用の構造体
typedef struct {
	float top;		// 上部
	float bottom;	// 下部
	float left;		// 左
	float right;	// 右
	float radius;	// 半径(コライダが円の場合)
	D3DXVECTOR2 pos;// 位置
}EDITCOLLIDER;


// コライダの保存
class CollisionState {
public:

	//＝＝＝＝＝関数＝＝＝＝＝

	CollisionState();
	CollisionState(Transform *paramTransform, TagName paramTagName, int registerNum,CollisionType paramType, TagName *notCollArray,EDITCOLLIDER *editColl);
	CollCalcNum CollisionState::CalcPosNum();

	//＝＝＝＝＝変数＝＝＝＝＝

	Transform		*pTransform;	// 座標のアドレスを保存
	TagName			tagName;		// 検索用のタグ名
	CollisionType	type;			// コライダのタイプ(無)
	TagName			*notCollideTag;
	EDITCOLLIDER	*editCollider;

	unsigned int collNum;	// コライダの個別番号
	bool	enable;			// コライダが有効化
	bool	trigger;		// trueなら物体は貫通する

private:
	CollCalcNum cPos;
};




#endif // !__COLLISION_STATE__
