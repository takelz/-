// �V�[���Ǘ�
//
// wii�ł�new���g���Ȃ��̂�new���g��Ȃ����@�ŃV�[���J�ڂ��s����
// �������ł͕��ʂ̕��@�ŃV�[���J�ڂ��s��

//#define _USE_SYSTEM_FOR_WII		// wii�J���p��`

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
	void ChangeScene(SceneNum sceneNum);	// �V�[���ؑւ𖽗�

	void Init();
	void Update();
	void Draw();
	void SceneTrance();						// ���ۂɃV�[���ؑցB�A�b�v�f�[�g���S���I���������ɐ؂�ւ�
	void Repeat();

	StageNum stageNum;						// �X�e�[�W�ԍ�
private:	


	SceneNum setScene;						// �ǂ̃V�[���𖽗߂�����
	SceneNum currentScene;
	StageGenerate stageGenerate;


#ifdef _USE_SYSTEM_FOR_WII

#else
	SceneBase *pScene;

#endif // 	
};



#endif // !__SCENEMANAGER__
