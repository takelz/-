	
#ifndef __SCENEGAME__
#define __SCENEGAME__

#include<iostream>
#include"SceneBase.h"
#include"BackGround.h"
#include"Player.h"
#include"GroundManager.h"
#include"DebugEnemyManager.h"
#include"EnemyNormalManager.h"
#include"Dxg2d\Font.h"
#include"EnemyShieldManager.h"
#include"BlockRotateManager.h"
#include"EnemyTogeManager.h"
#include"EnemyObjTogeManager.h"
#include"GoalPoint.h"
#include"PlayerDamageEffect.h"
#include"TutorialPopManager.h"

#include"UILife.h"
#include"UIScore.h"
#include"UICombo.h"



class SceneGame :public SceneBase {

public:
	void Init();
	void Update();
	void Draw();
	void Uninit();

	GroundManager groundManager;
	DebugEnemyManager dbgEnemyManager;
	
	EnemyNormalManager E_normalManager;
	EnemyShieldManager E_shieldManager;
	EnemyTogeManager E_togeManager;
	EnemyObjTogeManager E_objTogeManager;

	BlockRotateManager blockRotateManager;

	TutorialPopManager tutorialManager;

	GoalPoint goalPoint;
	
private:
	// マネージャーじゃないのはこっちに
	BackGround bg;
	Player player;
	PlayerDamageEffect playerDamageEffect;
	UILife uiLife;
	UIScore uiScore;
	UICombo uiCombo;

	Font font;


};

#endif // !__SCENEGAME__
