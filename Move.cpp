
#include"Move.h"

#define PI (3.1415f)

bool Move::SearchTarget(D3DXVECTOR2 basePos,D3DXVECTOR2 targetPos, float distanceX,float distanceY) {
	if (fabs(basePos.x - targetPos.x) < distanceX && fabs(basePos.y - targetPos.y) < distanceY)	return true;
	else return false;
}

bool Move::SearchDirectTargetX(D3DXVECTOR2 basePos, D3DXVECTOR2 targetPos) {
	if (0 > basePos.x - targetPos.x) return true;
	else return false;

}

bool Move::SearchDirectTargetY(D3DXVECTOR2 basePos, D3DXVECTOR2 targetPos) {
	if (0 > basePos.y - targetPos.y) return true;
	else return false;

}

bool Move::DistancePosition(D3DXVECTOR2 basePos, D3DXVECTOR2 targetPos,float distance) {
	if ((targetPos.x - basePos.x) * (targetPos.x - basePos.x) + (targetPos.y - basePos.y ) * (targetPos.y - basePos.y ) 
		<= (distance * distance)) return true;
	else return false;
}

D3DXVECTOR2 Move::VectorDirection(D3DXVECTOR2 basePos, D3DXVECTOR2 targetPos) {
	D3DXVECTOR2 returnStruct;
	returnStruct.x = targetPos.x - basePos.x;
	returnStruct.y = targetPos.y - basePos.y;

	float length = sqrtf(returnStruct.x * returnStruct.x + returnStruct.y * returnStruct.y);
	returnStruct.x = returnStruct.x / length;
	returnStruct.y = returnStruct.y / length;
	
	return returnStruct;
}

bool Move::SignLoop(float *num, int speed,float range) {
	signAngle += speed;
	
	*num = sinf(signAngle * PI  / 180) * range;

	return true;
}

bool Move::SignLoopB(float *num, int speed, float range) {
	signAngleB += speed;

	*num = sinf(signAngleB * PI / 180) * range;

	return true;
}

float Move::AngleVector(D3DXVECTOR2 vec) {
	float angle;
	angle = acosf(vec.x / sqrtf(vec.x*vec.x + vec.y*vec.y));
	angle = angle * 180.0f / PI;
	if (vec.y < 0) angle = 360.0f - angle;

	return angle;
}

void Move::ColorBright(unsigned char *color,float *num,const int speed,const float range){
	SignLoop(num, speed, range);
	*color = (unsigned char)((255 - range - 1) - *num);
}

