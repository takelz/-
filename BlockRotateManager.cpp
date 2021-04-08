
#include"BlockRotateManager.h"

void BlockRotateManager::Init() {
	for (int i = 0; i < MAX_GROUND; i++) {
		block[i].exist = false;
	}
}

void BlockRotateManager::Create(float posX, float posY, float rotat,int num) {
	for (int i = 0; i < MAX_GROUND; i++) {
		if (block[i].exist) continue;
		block[i].Create(posX, posY, rotat,3,1,num);
		break;
	}
}


void BlockRotateManager::Update() {
	for (int i = 0; i < MAX_GROUND; i++) {
		if (!block[i].exist)continue;
		block[i].Update();
	}
}

void BlockRotateManager::EditUpdate() {
	for (int i = 0; i < MAX_GROUND; i++) {
		if (!block[i].exist)continue;
		block[i].EditUpdate();
	}
}



void BlockRotateManager::Draw() {
	for (int i = 0; i < MAX_GROUND; i++) {
		if (!block[i].exist) continue;
		block[i].Draw();
	}

}




