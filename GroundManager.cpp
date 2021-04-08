
#include"GroundManager.h"

void GroundManager::Init() {
	for (int i = 0; i < MAX_NORMALGROUND; i++) {
		ground[i].exist = false;
	}



}

void GroundManager::Create(float posX, float posY, float rotat,int num) {
	for (int i = 0; i < MAX_NORMALGROUND; i++) {
		if (ground[i].exist) continue;
		ground[i].Create(posX, posY, rotat,1,1,num);
		break;
	}
}


void GroundManager::Update() {
	for (int i = 0; i < MAX_NORMALGROUND; i++) {
		if (!ground[i].exist)continue;
		ground[i].Update();
	}
}

void GroundManager::EditUpdate() {
	for (int i = 0; i < MAX_NORMALGROUND; i++) {
		if (!ground[i].exist)continue;
		ground[i].EditUpdate();
	}


}


void GroundManager::Draw() {
	for (int i = 0; i < MAX_NORMALGROUND; i++) {
		if (!ground[i].exist) continue;
		ground[i].Draw();
	}

}


