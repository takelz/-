//
//�O���t�@�C�����琔�l��ǂݍ��݃X�e�[�W�𐶐�

#ifndef __STAGEGENERATE__
#define __STAGEGENERATE__

//#include"BlockRotateManager.h"
//#include"DebugEnemyManager.h"
//#include"EnemyNormalManager.h"
//#include"EnemyShieldManager.h"
//#include"GroundManager.h"
#include"SceneGame.h"


enum StageNum {
	STAGE_0 = 0,	// 0�͊�{�g��Ȃ�
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_5,
	STAGE_6,
	STAGE_MAX,
};


typedef struct {
		int managerNum;
		float posX;
		float posY;
		float rotate;
		int num;
}PARAMETER;

class SceneEdit;

class StageGenerate {

private:

//	void GenerateObj(PARAMETER param, SceneEdit *scene);	// �X�e�[�W����

public:
	void GenerateObj(PARAMETER param,SceneGame *scene);	// �X�e�[�W����
	void GenerateObj(PARAMETER param, SceneEdit *scene);
	void LoadStage(StageNum num, SceneGame *scene);	// �O���t�@�C������ǂݍ���


};

#endif // !__STAGEGENERATE__
