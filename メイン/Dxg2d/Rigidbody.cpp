
#include"Rigidbody.h"


#define GRAVITY_VALUE (0.248f)

void Rigidbody::UpdatePos(){



	if (useGravity) 
		velocity.y += GRAVITY_VALUE;



	vector.x += velocity.x;
	vector.y += velocity.y;

	pTransform->pos.x += vector.x;
	pTransform->pos.y += vector.y;
	
	//RewindPos();	



	// 座標を保存
	oldPos.x = pTransform->pos.x;
	oldPos.y = pTransform->pos.y;

	oldVector = vector;			// 次のフレームで使うためのベクトルを保存
	vector.x = vector.y = 0;	// 移動量リセット
	//onCollide = false;
}

void Rigidbody::RewindPos() {
	if (!onCollide) return;

}

bool Rigidbody::OnCollidePointCircle(D3DXVECTOR2 vecPtCircle,D3DXVECTOR2 target,float radius,D3DXVECTOR2 vecAB,float vecAB_Len){
	float vecPtCir_Len;
	vecPtCir_Len = sqrtf(vecPtCircle.x * vecPtCircle.x + vecPtCircle.y*vecPtCircle.y);

	vecPtCircle.x = vecPtCircle.x / vecPtCir_Len;
	vecPtCircle.y = vecPtCircle.y / vecPtCir_Len;

	D3DXVECTOR2 normAB;
	normAB.x = vecAB.x / vecAB_Len;
	normAB.y = vecAB.y / vecAB_Len;	// 正規化

	if (normAB.x - vecPtCircle.x >= 0.1f && normAB.y - vecPtCircle.y >= 0.1f) {
		pTransform->pos.x = target.x + vecPtCircle.x * radius;
		pTransform->pos.y = target.y + vecPtCircle.y * radius;
		// 反射はなし
		return true;
	} else { 
		return false; 
	}
	
}

void Rigidbody::OnCollideSquareCircle(D3DXVECTOR2 target, D3DXVECTOR2 lineAB, float lengthAB, D3DXVECTOR2 circlePos, float circleRadius) {
	D3DXVECTOR2 normLine;
	D3DXVECTOR2 normalVec;	// 法線
	float lengthNorm, lengthPoint;

	normLine.x = lineAB.x / lengthAB;
	normLine.y = lineAB.y / lengthAB;
	normalVec.x = normLine.y;
	normalVec.y = -normLine.x;
	normLine.x = -normalVec.x * circleRadius;
	normLine.y = -normalVec.y * circleRadius;
	lengthNorm = -(target.x * normalVec.x + target.y * normalVec.y);
	lengthPoint = -(normalVec.x * circlePos.x + normalVec.y * circlePos.y + lengthNorm) / (normalVec.x * normLine.x + normalVec.y * normLine.y);

	D3DXVECTOR2 clossPoint;	// 交点
	clossPoint.x = circlePos.x + lengthPoint * normLine.x;
	clossPoint.y = circlePos.y + lengthPoint * normLine.y;


	pTransform->pos.x = clossPoint.x + circleRadius * normalVec.x;
	pTransform->pos.y = clossPoint.y + circleRadius * normalVec.y;
	

	if (useReflect) {
		reflected = true;
		ReflectVector(normalVec);
		return;
	}
	
	// 斜面の処理
	// 法線が右
	if ((0.8f < normalVec.x) && (0 > vector.x || 0 > velocity.x)) {
		vector.x = 0;
		velocity.x = 0;
	}
	// 法線が左
	if ((-0.8f > normalVec.x ) && (0 < vector.x || 0 < velocity.y)) {
		//vector.x = 0;
		//velocity.x = 0;
	}
	// 法線が上(地面)
	if (-0.5f > normalVec.y && (0 < vector.y || 0 < velocity.y)) {
		vector.y = 0.0f;
		velocity.y = 0;
	}
	// 法線が下(上の壁)
	if (0.5f < normalVec.y && (0 > vector.y || 0 > velocity.y)) {
		vector.y = 0.5f;
		velocity.y = 0;
	}
	
}

void Rigidbody::OnCollideCircle(D3DXVECTOR2 baseCircle,float baseRadius,D3DXVECTOR2 targetCircle,float targetRadius) {
	float lenX = targetCircle.x - baseCircle.x;
	float lenY = targetCircle.y - baseCircle.y;

	float length;
	float distance;

	length = sqrtf(lenX * lenX + lenY * lenY);
	distance = (baseRadius + targetRadius) - length;

	if (length > 0)  length = 1 / length;
	float svX, svY;
	svX = lenX;
	svY = lenY;
	lenX *= length;
	lenY *= length;

	//distance /= 2.0f;

	pTransform->pos.x -= lenX * distance;
	pTransform->pos.y -= lenY * distance;

	if (useReflect) {
		// 反射ベクトル
		lenX = targetCircle.x - baseCircle.x;
		lenY = targetCircle.y - baseCircle.y;
		length = sqrtf(lenX * lenX + lenY * lenY);

		D3DXVECTOR2 normVec;
		normVec.x = lenX / length;
		normVec.y = lenY / length;


		float work = -(normVec.x * velocity.x + normVec.y * velocity.y) / (normVec.x * normVec.x + normVec.y * normVec.y);
		velocity.x = velocity.x + work * normVec.x * 2.0f;
		velocity.y = velocity.y + work * normVec.y * 2.0f;
	} else {
		lenX = targetCircle.x - baseCircle.x;
		lenY = targetCircle.y - baseCircle.y;
		length = sqrtf(lenX * lenX + lenY * lenY);

		D3DXVECTOR2 normVec;
		normVec.x = lenX / length;
		normVec.y = lenY / length;

		if (0.78f < normVec.y && 0 < velocity.y) {	// 上に載っている場合下へのベクトルを0に
			velocity.y = 0.0f;
			vector.y = 0.0f;
		} 
		//else if (0 < vector.y || 0 < velocity) {	
		//	velocity.y = 0.0f;
		//	vector.y = 0.0f;
		
		//}


		// 当たった角度によってベクトルを減らす
		//D3DXVECTOR2 normXY;
		//normXY.x = (collCalc->num.centerX - GetCalcNum().centerX) / length;
		//normXY.y = (collCalc->num.centerY - GetCalcNum().centerY) / length;

		//if (0 < normXY.y) {
		//	rigid.vector.y = 0;
		//	rigid.velocity.y = 0;
		//}

	}
}


// 引数は法線ベクトル
void Rigidbody::ReflectVector(D3DXVECTOR2 normalVec) {
	float work = -(normalVec.x * velocity.x + normalVec.y * velocity.y) / (normalVec.x * normalVec.x + normalVec.y * normalVec.y);
	velocity.x = velocity.x + work * normalVec.x * 2.0f;
	velocity.y = velocity.y + work  * normalVec.y * 2.0f;
}

void Rigidbody::ResetVelocity() {
	velocity.x = velocity.y = 0.0f;
}

// アドレスを保存
void Rigidbody::Init(Transform *paramTransform) {
	pTransform = paramTransform;
}




