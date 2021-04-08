
#ifndef __MOVE__
#define __MOVE__

#include"main.h"

class Move {
public:

	// 指定した座標と目標の座標と距離を渡して距離を求める。指定して距離以内ならtrueを返す
	bool SearchTarget(D3DXVECTOR2 basePos,D3DXVECTOR2 targetPos,float distanceX,float distanceY);

	// 目標の座標が指定した座標の右側の場合trueを返す
	bool SearchDirectTargetX(D3DXVECTOR2 basePos, D3DXVECTOR2 targetPos);

	// 目標の座標が指定した座標の下側の場合trueを返す
	bool SearchDirectTargetY(D3DXVECTOR2 basePos, D3DXVECTOR2 targetPos);

	// 二点間のxy座標の距離を求め、指定距離内ならtrueを返す
	bool DistancePosition(D3DXVECTOR2 basePos, D3DXVECTOR2 targetPos,float distance);

	// basePosからみてtargetPosがどの方向にあるかを正規化されたベクトルで返す
	D3DXVECTOR2 VectorDirection(D3DXVECTOR2 basePos, D3DXVECTOR2 targetPos);

	// 値をsign波を使って変えていく
	bool SignLoop(float *num,int speed,float range);

	// singloopと一緒、二種類使いたい場合
	bool SignLoopB(float *num, int speed, float range);

	// ベクトルから角度を求める
	float AngleVector(D3DXVECTOR2 vec);

	// 色の点滅(ゆっくり)
	void ColorBright(unsigned char *color, float *num, const int speed, const float range);


private:
	int signAngle;
	int signAngleB;
};




#endif // !__MOVE__
