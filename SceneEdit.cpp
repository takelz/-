
#include"SceneEdit.h"
#include"Dxg2d\input.h"
#include"Dxg2d\Camera.h"
#include"UIsystem.h"


#define SAVE_STAGEFILE_0 "data/stage/output_stagedata.csv"

#define FILENAME_BUTTON "data/texture/UI/button.png"
#define BUTTON_U (2)
#define BUTTON_V (1)
#define BUTTON_SIZE (20)


#define MANAGER_NUM_FONT_POS_X (70)
#define MANAGER_NUM_FONT_POS_Y (10)
#define MANAGER_NUM_FONT_SIZE (10)


using namespace std;

static ofstream file;
static bool pushSaved;

void StartSave();
void EndSave();

void SceneEdit::Init() {
	bg.Init();
	player.Init();
	goalPoint.Init();

	groundManager.Init();
	dbgEnemyManager.Init();
	E_normalManager.Init();
	E_shieldManager.Init();
	E_togeManager.Init();
	E_objTogeManager.Init();

	blockRotateManager.Init();
	tutorialManager.Init();

	objPmButton.Init();
	objPmButton.ThrowNum(&objNum);
	objPmButton.SetPos(MANAGER_NUM_FONT_POS_X +80, MANAGER_NUM_FONT_POS_Y*3);
	managerPmButton.Init();
	managerPmButton.ThrowNum(&managerIntNum);
	managerPmButton.SetPos(MANAGER_NUM_FONT_POS_X + 80, MANAGER_NUM_FONT_POS_Y);

	font.Init();
}

void SceneEdit::Update() {

	Create();

	StartSave();

	bg.Update();
	player.EditUpdate();
	goalPoint.EditUpdate();

	groundManager.EditUpdate();
	dbgEnemyManager.EditUpdate();
	E_normalManager.EditUpdate();
	E_shieldManager.EditUpdate();
	E_objTogeManager.EditUpdate();
	E_togeManager.EditUpdate();
	blockRotateManager.EditUpdate();

	tutorialManager.EditUpdate();

	EndSave();

	objPmButton.Update();
	managerPmButton.Update();
	managerNum = (Manager)managerIntNum;	// 更新
	DispNum();
	font.Update();
}

void SceneEdit::Draw() {
	bg.Draw();
	player.Draw();
	goalPoint.Draw();

	groundManager.Draw();
	dbgEnemyManager.Draw();
	E_normalManager.Draw();
	E_shieldManager.Draw();
	E_objTogeManager.Draw();
	E_togeManager.Draw();

	blockRotateManager.Draw();

	tutorialManager.Draw();

	objPmButton.Draw();
	managerPmButton.Draw();
	font.Draw();
}

void SceneEdit::Uninit() {


}

void SceneEdit::Create() {
	PARAMETER param;
	if (DIGetKeyTrigger(DIK_G)) {
		param.managerNum = managerNum;
		param.num = objNum;
		param.posX = GetMousePos().x - Camera::Instance()->pos.x;
		param.posY = GetMousePos().y - Camera::Instance()->pos.y;
		param.rotate = 0;
		generate.GenerateObj(param, this);
	}
}

void StartSave() {
	if (DIGetKeyTrigger(DIK_H)) {	// ボタン押したらこのループの間はセーブモード
		pushSaved = true;

		file.open(SAVE_STAGEFILE_0, ios::trunc);	// 同名のファイルがあったらそれを上書き
		if (!file) {
			MessageBox(NULL, "セーブファイルが開けませんでした", "エラー", MB_OK);
		}
	}
}

void EndSave() {
	if (pushSaved) {
		pushSaved = false;
		MessageBox(NULL, "セーブが完了しました", "セーブ", MB_OK);

		file.close();
	}
}

ofstream* GetSaveFile() {
	return &file;
}


void SceneEdit::DispNum() {
	//UIsystem uiSystem;
	string disp;
	char input[MAX_DISP_CHAR];
	disp = "ManagerNum:";
	disp = disp + std::to_string(managerNum);
	std::char_traits<char>::copy(input, disp.c_str(), disp.length() + 1);
	font.SetColor(0, 0, 0);
	font.InputChar(input, MANAGER_NUM_FONT_POS_X, MANAGER_NUM_FONT_POS_Y, MANAGER_NUM_FONT_SIZE, MANAGER_NUM_FONT_SIZE * 2);
	
	disp = "ObjNum:";
	disp = disp + std::to_string(objNum);
	std::char_traits<char>::copy(input, disp.c_str(), disp.length() + 1);
	font.SetColor(0, 0, 0);
	font.InputChar(input, MANAGER_NUM_FONT_POS_X +20, MANAGER_NUM_FONT_POS_Y*3, MANAGER_NUM_FONT_SIZE, MANAGER_NUM_FONT_SIZE * 2);


}

//＝＝＝＝＝EditUI＝＝＝＝＝

void PM_Button::Init() {
	sprite.Load(FILENAME_BUTTON, 0, BUTTON_U, BUTTON_V);
	sprite.size.x = sprite.size.y = BUTTON_SIZE;
	sprite.pos.x = 0;
	sprite.pos.y = 0;
	secondPos = sprite.pos;
	secondPos.x += sprite.size.x;
}

void PM_Button::Update() {	// 左がプラス、右がマイナス
	UIsystem uiSystem;

	if (uiSystem.Button(sprite.pos, sprite.size)) {
		if (DIGetMouseTrigger(DIK_LEFT_CLICK)) {
			*pNum += 1;
		}
	}
	
	
	if (uiSystem.Button(secondPos, sprite.size)) {
		if (DIGetMouseTrigger(DIK_LEFT_CLICK)) {
			*pNum -= 1;
		}
	}

	sprite.Update();

}

void PM_Button::Draw() {
	D3DXVECTOR2 savePos;

	sprite.SetUV(2, 1);		// +の表示
	sprite.Draw();			
	savePos = sprite.pos;

	sprite.SetUV(2, 1);		// -の表示
	sprite.pos = secondPos;
	sprite.Draw();
	sprite.pos = savePos;	// 二つ目表示したらもとに戻す
}

void PM_Button::ThrowNum(int *num) {
	pNum = num;
}

void PM_Button::SetPos(float posX,float posY) {
	sprite.pos.x = posX;
	sprite.pos.y = posY;
	secondPos = sprite.pos;
	secondPos.x += sprite.size.x;

}


bool GetPushedSave() {
	return pushSaved;
}
