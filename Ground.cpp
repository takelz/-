//objNum
//0　256サイズ
//1　128サイズ
//2　64サイズ
//
#include"Ground.h"
#include"ObjEditMode.h"
#define FILENAME "data/texture/stage/blocks2.png"
#define BLOCKS_U (4)
#define BLOCKS_V (4)
#define SIZE_X (250)
#define SIZE_Y (250)



void Ground::Init() {
	collision.Register(&transform, TAG_GROUND, C_TYPE_SQUARE);
	sprite.Load(FILENAME,0,BLOCKS_U,BLOCKS_V);
	SwitchObj();
}

void Ground::Create(float posX, float posY, float rotate,int numU,int numV,int num) {

	transform.pos.x = posX;
	transform.pos.y = posY;
	transform.size.x = SIZE_X;
	transform.size.y = SIZE_Y;
	transform.rotate = rotate;
	sprite.SetUV(numU, numV);
	objNum = num;
	exist = true;
	Init();
}



void Ground::Update() {
	sprite.SetUV(2, 1);
	transform.TransformToSprite(&sprite);
	sprite.Update();
}

void Ground::EditUpdate() {
	edit.EditObject(&transform,&exist,MANAGER_GROUND, objNum);
	transform.TransformToSprite(&sprite);
	sprite.Update();
}


void Ground::Draw() {
	sprite.Draw();
}


void Ground::SwitchObj() {
	switch (objNum) {
		case 0:
			break;
		case 1:
			transform.size.x = SIZE_X / 2;
			transform.size.y = SIZE_Y / 2;
			break;
		case 2:
			transform.size.x = SIZE_X / 4;
			transform.size.y = SIZE_Y / 4;
			break;
	}
}

