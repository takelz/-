
#ifndef __SCENEEDIT__
#define __SCENEEDIT__

#include"SceneBase.h"
#include"BackGround.h"
#include"Player.h"
#include"GroundManager.h"
#include"DebugEnemyManager.h"
#include"EnemyNormalManager.h"
#include"Dxg2d\Font.h"
#include"EnemyShieldManager.h"
#include"BlockRotateManager.h"
#include"StageGenerate.h"
#include<string>
#include<fstream>
#include<sstream>


class PM_Button :GameObj{	// バグで+-正しく表示されない
public:
	void Init();
	void Update();
	void Draw();

	void ThrowNum(int *num);// ＋ーしたい番号を投げる
	void SetPos(float posX, float posY);
private:

	D3DXVECTOR2 secondPos;	// 二つ目(マイナス)の位置
	int *pNum;

};

class SceneEdit :public SceneGame {

public:
	void Init();
	void Update();
	void Draw();
	void Uninit();

	//GroundManager groundManager;
	//DebugEnemyManager dbgEnemyManager;
	//EnemyNormalManager E_normalManager;
	//EnemyShieldManager E_shieldManager;
	//BlockRotateManager blockRotateManager;

private:
	void Create();
	void DispNum();

	//＝＝＝＝＝変数＝＝＝＝＝

	StageGenerate generate;
	Font font;	
	PM_Button objPmButton;		// +-ボタン
	PM_Button managerPmButton;	// +-ボタン

	BackGround bg;
	Player player;


	Manager managerNum;	
	int managerIntNum;	// 値変化用
	int objNum;

};

using namespace std;

bool GetPushedSave();	// セーブモードかを取得
ofstream *GetSaveFile();	// ファイル取得

#endif // !__SCENEGAME__
