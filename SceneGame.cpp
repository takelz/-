
#include"SceneGame.h"

#include"Dxg2d\input.h"
#include"Dxg2d\sound.h"
#include"SceneManager.h"
#include"Dxg2d\Camera.h"
#include"DestroyParticleEmitter.h"
#include"Fade.h"
#include"PauseScreen.h"
#include"GameManager.h"


void SceneGame::Init() {
	Camera::Instance()->pos.x = Camera::Instance()->pos.y = 0;	// カメラ位置リセット
	//Fade::Instance()->StartFadeIn();
	PauseScreen::Instance()->Init();	// ポーズ処理の初期化

	bg.Init();
	player.Init();
	goalPoint.Init();
	groundManager.Init();
	playerDamageEffect.Init();

	dbgEnemyManager.Init();
	E_normalManager.Init();
	E_shieldManager.Init();
	E_togeManager.Init();
	E_objTogeManager.Init();

	font.Init();
	blockRotateManager.Init();
	uiLife.Init();
	uiScore.Init();
	uiCombo.Init();
	tutorialManager.Init();

	DestroyParticleEmitter::Instance()->Init();
	GameManager::Instance()->isGameOver = false;
	GameManager::Instance()->isGameClear = false;
	GameManager::Instance()->faded = false;
	
	StopSound();
	PlaySound(SOUND_BGM_GAME);
}

void SceneGame::Update() {
	bg.Update();
	if (!PauseScreen::Instance()->GetPauseState()) {	// ポーズ中は下の処理は行わない
		playerDamageEffect.Update();
		player.Update();
		groundManager.Update();


		dbgEnemyManager.Update();
		E_normalManager.Update();
		E_shieldManager.Update();
		E_togeManager.Update();
		E_objTogeManager.Update();

		blockRotateManager.Update();

		uiLife.Update();
		uiScore.Update();
		uiCombo.Update();
		goalPoint.Update();
		tutorialManager.Update();

		DestroyParticleEmitter::Instance()->Update();
	}
	PauseScreen::Instance()->Update();		// Drawはメインのフェードの後に
	GameManager::Instance()->GameUpdate();	
	Camera::Instance()->ShakeUpdate();
}

void SceneGame::Draw() {
	bg.Draw();
	goalPoint.Draw();


	E_objTogeManager.Draw();
	groundManager.Draw();


	dbgEnemyManager.Draw();
	E_normalManager.Draw();
	E_shieldManager.Draw();
	E_togeManager.Draw();
	blockRotateManager.Draw();
	DestroyParticleEmitter::Instance()->Draw();

	player.Draw();

	if (!PauseScreen::Instance()->GetPauseState()) {	// ポーズ中ならUIは表示しない
		font.Draw();

		playerDamageEffect.Draw();
		uiLife.Draw();
		uiScore.Draw();
		uiCombo.Draw();
		tutorialManager.Draw();
	}
}

void SceneGame::Uninit() {	

	delete this;
}

