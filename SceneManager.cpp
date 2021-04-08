
#include"SceneManager.h"

void SceneManager::Init() {
#ifdef _USE_SYSTEM_FOR_WII
	switch (currentScene) {
		case SCENE_TITLE:
			break;
		case SCENE_SELECT:
			break;
		case SCENE_GAME:
			break;
		case SCENE_CLEAR:
			break;
		case SCENE_OVER:
			break;
	}
#else
	pScene->Init();
#endif
}



void SceneManager::Update() {
#ifdef _USE_SYSTEM_FOR_WII
	switch (currentScene) {
		case SCENE_TITLE:
			break;
		case SCENE_SELECT:
			break;
		case SCENE_GAME:
			break;
		case SCENE_CLEAR:
			break;
		case SCENE_OVER:
			break;
	}
#else
	pScene->Update();
	SceneTrance();
#endif
}


void SceneManager::Draw() {
#ifdef _USE_SYSTEM_FOR_WII
	switch (currentScene) {
		case SCENE_TITLE:
			break;
		case SCENE_SELECT:
			break;
		case SCENE_GAME:
			break;
		case SCENE_CLEAR:
			break;
		case SCENE_OVER:
			break;
	}
#else
	pScene->Draw();
#endif
}

void SceneManager::ChangeScene(SceneNum sceneNum) {
	setScene = sceneNum;
}

void SceneManager::Repeat() {	
	currentScene = SCENE_MAX;
}

void SceneManager::SceneTrance() {
	if (setScene == currentScene) return;	// 更新がなかったら処理しない
#ifdef _USE_SYSTEM_FOR_WII

	currentScene = sceneNum;

#else

	SceneGame *pGame;
	SceneEdit *pEdit;

	if (pScene != NULL) {	// なにか入っていたら消す
		pScene->Uninit();
		//delete pScene;
	}
	ResetCollisionDeque();	// コライダの保存を消去

	currentScene = setScene;

	switch (setScene) {
		case SCENE_TITLE:
			pScene = new SceneTitle();
			pScene->Init();
			break;
		case SCENE_SELECT:	
			pScene = new SceneSelect();
			pScene->Init();
			break;
		case SCENE_GAME:
			pGame = new SceneGame();
			pScene = pGame;
			pScene->Init();
			stageGenerate.LoadStage(stageNum, pGame);			// ここにステージ生成
			break;
		case SCENE_CLEAR:
			pScene = new SceneClear();
			pScene->Init();
			break;
		case SCENE_OVER:
			pScene = new SceneOver();
			pScene->Init();
			break;
		case SCENE_EDIT:
			if (MessageBox(NULL, "ステージデータをロードしますか?", "", MB_YESNO) == IDYES) {
				pEdit = new SceneEdit();
				pScene = pEdit;
				pScene->Init();
				stageGenerate.LoadStage(STAGE_0, pEdit);
				MessageBox(NULL, "ステージデータをロードしました", "", MB_OK);
			} else {
				pScene = new SceneEdit();
				pScene->Init();
			}
			break;
	}
	pScene->Update();

#endif
}
