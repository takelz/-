
#include"TutorialPopManager.h"


void TutorialPopManager::Init() {
	for (int i = 0; i < TUTO_POP_MAX; i++) {
		pop[i].exist = false;
	}
}

void TutorialPopManager::Create(float posX, float posY, float rotate,int num) {
	for (int i = 0; i < TUTO_POP_MAX; i++) {
		if (pop[i].exist) continue;
		pop[i].Create(posX, posY, num);
		break;
	}
}


void TutorialPopManager::Update() {
	for (int i = 0; i < TUTO_POP_MAX; i++) {
		if (!pop[i].exist)continue;
		pop[i].Update();
	}


}

void TutorialPopManager::EditUpdate() {
	for (int i = 0; i < TUTO_POP_MAX; i++) {
		if (!pop[i].exist)continue;
		pop[i].EditUpdate();
	}


}


void TutorialPopManager::Draw() {
	for (int i = 0; i < TUTO_POP_MAX; i++) {
		if (!pop[i].exist) continue;
		pop[i].Draw();
	}

}


