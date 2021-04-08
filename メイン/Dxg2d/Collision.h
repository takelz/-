// コライダ関連
// コライダの中にRigidbodyを含む
// 地形判定にしたいオブジェクトはOncollideを作らない
//
// ～更新履歴～
// 2018/07/24	完成
// 2018/07/25	関数名変更
//

#ifndef __COLLISION__
#define __COLLISION__



#include"Transform.h"
#include"CollisionState.h"
#include"Rigidbody.h"
 

// 登録しているコライダを取得するための構造体
typedef struct {
	CollCalcNum num;
	CollisionType type;
	bool trigger;
	TagName notCollideTag[MAX_NOTCOLL_NUM];
	TagName tag;
}COLL_CALC_ST;


class Collision {
public:
	//＝＝＝＝＝関数＝＝＝＝＝

	// コライダの登録。コライダ使うなら必ずコンストラクタで呼び出す
	void Register(Transform *transform, TagName paramTagName,CollisionType collType);

	// コライダの削除。消すときに必ず呼び出す
	void DeleteCollision();
	
	// タグの変更
	void SetTag(TagName tagName);

	// 有効化
	void SetEnable(bool enable);

	// 貫通するか
	void SetTrigger(bool trigger);

	// 貫通したい相手のタグを登録(16個まで)
	void SetNotCollideTag(TagName tag);

	// 貫通したい相手のタグの登録解除
	void DeleteNotCollideTag(TagName tag);

	bool OnCollide(TagName targetTag);

	Collision();
	~Collision();

	//＝＝＝＝＝変数＝＝＝＝＝

	Rigidbody rigid;		// 物理関係
	bool trigger;
	EDITCOLLIDER editColl;	// コライダの位置大きさの調節。円の場合は大きさ変更はradiusだけでよい

private:
	COLL_CALC_ST* SeachState(TagName tagName);
	CollCalcNum GetCalcNum();	
	bool LineCollide(LINEPOINT pointA, LINEPOINT pointB, LINEPOINT targetA, LINEPOINT targetB);
	bool Square(COLL_CALC_ST *collCalc);
	bool Circle(COLL_CALC_ST *collCalc);
	bool SquareCircle(COLL_CALC_ST *pSquare,COLL_CALC_ST *pCircle);
	bool CheckNotCollideTag(TagName *baseTag, TagName targetTag);		

	int collRegisterNum;	// コライダの個別番号
	TagName tagName;		// このオブジェクトのタグ
	CollisionType type;
	Transform *pCollTrans;	// 座標情報を保存	
	TagName notCollideTag[MAX_NOTCOLL_NUM];	// どvのコライダのタグと判定しないかを保存。0で何も入っていない

};

void ResetCollisionDeque();	// 保存しているコライダをすべて初期化

#endif // !__COLLISION__

