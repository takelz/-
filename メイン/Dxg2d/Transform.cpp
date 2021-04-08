

#include"Transform.h"
#include"Camera.h"
#include"input.h"

Transform::Transform() {
	pos.x = 0.0f;
	pos.y = 0.0f;
	size.x = size.y = 10.0f;
	scale.x = scale.y = 1.0f;
	rotate = 0;
}

void Transform::TransformToSprite(Sprite *sprite) {

	if (notScroll) {		// スクロールしない場合はカメラ位置を無視
		sprite->pos.x = pos.x;
		sprite->pos.y = pos.y;
	} else {
		sprite->pos.x = pos.x + Camera::Instance()->pos.x + Camera::Instance()->shakeOffset.x;
		sprite->pos.y = pos.y + Camera::Instance()->pos.y + Camera::Instance()->shakeOffset.y;
	}
	sprite->size.x = size.x;
	sprite->size.y = size.y;
	sprite->scale.x = scale.x;
	sprite->scale.y = scale.y;
	sprite->rotate = rotate;
}





