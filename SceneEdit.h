
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


class PM_Button :GameObj{	// �o�O��+-�������\������Ȃ�
public:
	void Init();
	void Update();
	void Draw();

	void ThrowNum(int *num);// �{�[�������ԍ��𓊂���
	void SetPos(float posX, float posY);
private:

	D3DXVECTOR2 secondPos;	// ���(�}�C�i�X)�̈ʒu
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

	//�����������ϐ�����������

	StageGenerate generate;
	Font font;	
	PM_Button objPmButton;		// +-�{�^��
	PM_Button managerPmButton;	// +-�{�^��

	BackGround bg;
	Player player;


	Manager managerNum;	
	int managerIntNum;	// �l�ω��p
	int objNum;

};

using namespace std;

bool GetPushedSave();	// �Z�[�u���[�h�����擾
ofstream *GetSaveFile();	// �t�@�C���擾

#endif // !__SCENEGAME__
