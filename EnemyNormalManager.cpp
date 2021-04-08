
#include"EnemyNormalManager.h"

void EnemyNormalManager::Init() {
	for (int i = 0; i < MAX_NORMALENEMY; i++) {
		enemy[i].exist = false;
	}

}

void EnemyNormalManager::Create(float posX, float posY, float rotate,int num) {
	for (int i = 0; i < MAX_NORMALENEMY; i++) {
		if (enemy[i].exist) continue;
		enemy[i].Create(posX, posY, rotate,num);
		break;
	}
}


void EnemyNormalManager::Update() {
	for (int i = 0; i < MAX_NORMALENEMY; i++) {
		if (!enemy[i].exist)continue;
		enemy[i].Update();
	}


}

void EnemyNormalManager::EditUpdate() {
	for (int i = 0; i < MAX_NORMALENEMY; i++) {
		if (!enemy[i].exist)continue;
		enemy[i].EditUpdate();
	}


}


void EnemyNormalManager::Draw() {
	for (int i = 0; i < MAX_NORMALENEMY; i++) {
		if (!enemy[i].exist) continue;
		enemy[i].Draw();
	}

}


