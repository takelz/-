// シーン管理
//
// wiiではnewが使えないのでnewを使わない方法でシーン遷移を行うが
// こっちでは普通の方法でシーン遷移を行う

//#define _USE_SYSTEM_FOR_WII		// wii開発用定義

#ifndef __SCENEMANAGER__
#define __SCENEMANAGER__

#include"main.h"
#include"SceneGame.h"
#include"SceneSelect.h"
#include"SceneTitle.h"
#include"SceneEdit.h"
#include"SceneOver.h"
#include"StageGenerate.h"
#include"SceneClear.h"



enum SceneNum {
	SCENE_TITLE = 1,
	SCENE_SELECT,
	SCENE_GAME,
	SCENE_CLEAR,
	SCENE_OVER,
	SCENE_EDIT,
	SCENE_MAX
};

class SceneManager {
public:
	static SceneManager *Instance() {
		static SceneManager sceneManager;
		return &sceneManager;
	}
	static void Delete() {
		delete Instance();
	}

#ifdef _USE_SYSTEM_FOR_WII

#else


#endif
	void ChangeScene(SceneNum sceneNum);	// シーン切替を命令

	void Init();
	void Update();
	void Draw();
	void SceneTrance();						// 実際にシーン切替。アップデートが全部終わった直後に切り替え
	void Repeat();

	StageNum stageNum;						// ステージ番号
private:	


	SceneNum setScene;						// どのシーンを命令したか
	SceneNum currentScene;
	StageGenerate stageGenerate;


#ifdef _USE_SYSTEM_FOR_WII

#else
	SceneBase *pScene;

#endif // 	
};



#endif // !__SCENEMANAGER__
