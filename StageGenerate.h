//
//外部ファイルから数値を読み込みステージを生成

#ifndef __STAGEGENERATE__
#define __STAGEGENERATE__

//#include"BlockRotateManager.h"
//#include"DebugEnemyManager.h"
//#include"EnemyNormalManager.h"
//#include"EnemyShieldManager.h"
//#include"GroundManager.h"
#include"SceneGame.h"


enum StageNum {
	STAGE_0 = 0,	// 0は基本使わない
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

//	void GenerateObj(PARAMETER param, SceneEdit *scene);	// ステージ生成

public:
	void GenerateObj(PARAMETER param,SceneGame *scene);	// ステージ生成
	void GenerateObj(PARAMETER param, SceneEdit *scene);
	void LoadStage(StageNum num, SceneGame *scene);	// 外部ファイルから読み込み


};

#endif // !__STAGEGENERATE__
