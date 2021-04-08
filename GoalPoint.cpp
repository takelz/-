#include"GoalPoint.h"
#include"SceneManager.h"
#include"Fade.h"
#include"GameManager.h"
#include"Dxg2d\sound.h"

#define GOALFILE "data/texture/stage/door.png"
#define GOAL_SIZE_X (120)
#define GOAL_SIZE_Y (130)

#define BRIGHT_SPEED (3)
#define BRIGHT_RANGE (60)

#define SPRITE_COLOR (140)


void GoalPoint::Init() {
	collision.Register(&transform, TAG_GOAL, C_TYPE_SQUARE);
	collision.trigger = true;
	// ƒRƒ‰ƒCƒ_‚ð‹·‚­‚·‚é‚·‚é
	collision.editColl.bottom = -GOAL_SIZE_Y / 3;
	collision.editColl.top = -GOAL_SIZE_Y / 3;
	collision.editColl.left = GOAL_SIZE_X / 3;
	collision.editColl.right = -GOAL_SIZE_X / 3;


	transform.size.x = GOAL_SIZE_X;
	transform.size.y = GOAL_SIZE_Y;
	
	sprite.Load(GOALFILE);
	sprite.color.r = sprite.color.b = sprite.color.g = SPRITE_COLOR;
}

void GoalPoint::Create(float posX,float posY) {
	transform.pos.x = posX;
	transform.pos.y = posY;
}



void GoalPoint::Update() {
	Goaled();
	move.ColorBright(&spriteColor,&colorNum, BRIGHT_SPEED, BRIGHT_RANGE);
	sprite.color.r = sprite.color.b = sprite.color.g = spriteColor;

	collision.rigid.UpdatePos();
	transform.TransformToSprite(&sprite);
	sprite.Update();
}

void GoalPoint::EditUpdate() {
	edit.EditObject(&transform, &exist, MANAGER_GOAL, 0);
	transform.TransformToSprite(&sprite);
	sprite.Update();
}



void GoalPoint::Draw() {
	sprite.Draw();
}

void GoalPoint::Goaled() {
	if (isGoaled) {
		if (Fade::Instance()->GetFadeState(true)) {
			SceneManager::Instance()->ChangeScene(SCENE_CLEAR);
			Fade::Instance()->StartFadeIn();
			StopSound();
			PlaySound(SOUND_BGM_MENU);
		}
	}

	if (collision.OnCollide(TAG_PLAYER) && !isGoaled) {
		isGoaled = true;
		GameManager::Instance()->isGameClear = true;
		Fade::Instance()->StartFadeOut();
	}
}
