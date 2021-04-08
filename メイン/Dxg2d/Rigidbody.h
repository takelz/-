// 演算処理
// オブジェクトの押し戻し等
//
// ～更新履歴～
// 2018/07/24	完成
//
// ＝＝メモ＝＝
// 地形判定をとるisGroundの使い方は
// 例えば乗ることが出来る敵なら、triggerがonの敵本体とそれに重ねる地形用のオブジェクトも作りそれにisGroundをtrueに。
// rigid.OnCollide()は使わない
//
//
#ifndef __RIGIDBODY__
#define __RIGIDBODY__

#include"Transform.h"


class Rigidbody {
public:
	//＝＝＝＝＝関数＝＝＝＝＝

	void UpdatePos();	// 座標の更新
	void OnCollide(float depth);	// 物体に衝突した際に戻すか
	void OnCollideSquareCircle(D3DXVECTOR2 target ,D3DXVECTOR2 lineAB, float lengthAB, D3DXVECTOR2 circlePos,float circleRadius);
	bool OnCollidePointCircle(D3DXVECTOR2 vecPtCircle, D3DXVECTOR2 target, float radius,D3DXVECTOR2 vecAB, float vecAB_Len);
	void OnCollideCircle(D3DXVECTOR2 baseCircle, float baseRadius, D3DXVECTOR2 targetCircle, float targetRadisus);
	void ResetVelocity();

	void Init(Transform *paramTransform);

	//＝＝＝＝＝変数＝＝＝＝＝
	D3DXVECTOR2 velocity;	//	速度
	D3DXVECTOR2 vector;		//	移動量
	D3DXVECTOR2 oldPos;		// 
	D3DXVECTOR2 oldVector;	// 1フレーム前のベクトル
	bool useGravity;	// 重力を適用させるか
	bool useReflect;	// 反射させるか(速度は減衰しない)

	bool reflected;		// 反射したか。手動でもどす
	//float deceleration;	// どのくらい減速するか(1.0fで減速しない。それより大きな値だと加速する)
	float mass;			// 質量(未使用)

private:
	//＝＝＝＝＝関数＝＝＝＝＝
	void RewindPos();							// 衝突時にオブジェクトを巻き戻す
	void ReflectVector(D3DXVECTOR2 normalVec);	// 反射ベクトル。タイミングは位置調整後に呼び出す

	//＝＝＝＝＝変数＝＝＝＝＝
	Transform *pTransform;		// 当たりに行く側(自身)の情報
	Transform *pReceiveTrans;	// 受ける側の情報

	bool onCollide;				// 壁に当たってもとに戻すかどうか
	bool rockGravity;			// 地面に当たっている判定なら重力ロック
	bool isGround;				// 地形判定をとるか	

};




#endif // !__RIGIDBODY__