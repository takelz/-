
#include"EnemyObjTogeManager.h"
/**/
void EnemyObjTogeManager::Init() {
	for (int i = 0; i < MAX_TOGEENEMY; i++) {
		enemy[i].exist = false;
	}
}

void EnemyObjTogeManager::Create(float posX, float posY, float rotate, int num) {
	for (int i = 0; i < MAX_TOGEENEMY; i++) {
		if (enemy[i].exist) continue;
		enemy[i].Create(posX, posY, rotate, num);
		break;
	}
}


void EnemyObjTogeManager::Update() {
	for (int i = 0; i < MAX_TOGEENEMY; i++) {
		if (!enemy[i].exist)continue;
		enemy[i].Update();
	}


}

void EnemyObjTogeManager::EditUpdate() {
	for (int i = 0; i < MAX_TOGEENEMY; i++) {
		if (!enemy[i].exist)continue;
		enemy[i].EditUpdate();
	}


}


void EnemyObjTogeManager::Draw() {
	for (int i = 0; i < MAX_TOGEENEMY; i++) {
		if (!enemy[i].exist) continue;
		enemy[i].Draw();
	}

}

