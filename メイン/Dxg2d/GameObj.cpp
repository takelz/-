
#include"GameObj.h"

void GameObj::AttachChild(Transform *parentTransform) {
	D3DXVECTOR2 offsetPos;
	offsetPos.x = offsetPos.y = 0.0f;
	AttachChild(parentTransform, offsetPos);
}

void GameObj::AttachChild(Transform *parentTransform, float offsetX, float offsetY) {
	D3DXVECTOR2 pos;
	pos.x = offsetX;
	pos.y = offsetY;
	AttachChild(parentTransform, pos);
}

void GameObj::AttachChild(Transform *parentTransform, D3DXVECTOR2 offsetPos) {
	transform.pos.x = parentTransform->pos.x + offsetPos.x;
	transform.pos.y = parentTransform->pos.y + offsetPos.y;
	//transform.rotate = parentTransform->rotate;
}





