
#include"EnemyShieldManager.h"

void EnemyShieldManager::Init() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		enemy[i].exist = false;
	}
}

void EnemyShieldManager::Create(float posX, float posY, float rotate,int num) {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (enemy[i].exist) continue;
		enemy[i].Create(posX, posY, rotate,num);
		break;
	}
}


void EnemyShieldManager::Update() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[i].exist)continue;
		enemy[i].Update();
	}
}

void EnemyShieldManager::EditUpdate() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[i].exist)continue;
		enemy[i].EditUpdate();
	}
}



void EnemyShieldManager::Draw() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[i].exist) continue;
		enemy[i].Draw();
	}

}


