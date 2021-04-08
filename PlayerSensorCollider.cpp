
#include"PlayerSensorCollider.h"

#define FILENAME "data/texture/circle1.png"

void GroundedCollider::Init() {
	collision.Register(&transform, TAG_NOT, C_TYPE_SQUARE);
	collision.SetNotCollideTag(TAG_PLAYER);
	collision.trigger = true;
	sprite.Load(FILENAME);
	sprite.color.b = sprite.color.r = 0;
	transform.size.x = transform.size.y = 15.0f * 0.7f;
	isGround = false;
	isJumped = true;
}



void GroundedCollider::Update() {
	if(collision.OnCollide(TAG_GROUND)){
		isGround = true;
		isJumped = false;
	} else {
		isGround = false;
	}

	transform.TransformToSprite(&sprite);
	sprite.Update();
}

void GroundedCollider::Draw() {
	//sprite.Draw();
}

