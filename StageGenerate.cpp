
#include"StageGenerate.h"
#include<fstream>
#include<sstream>
#include<string>
#include"SceneEdit.h"

//#define STAGEFILE_0 "data/stage/output_stagedata.csv"	// �e�X�g�p��
#define STAGEFILE_0 "data/stage/stage00.csv"	// �e�X�g�p��

#define STAGEFILE_1 "data/stage/stage01.csv"
#define STAGEFILE_2 "data/stage/stage02.csv"
#define STAGEFILE_3 "data/stage/stage03.csv"
#define STAGEFILE_4 "data/stage/stage04.csv"
#define STAGEFILE_5 "data/stage/stage05.csv"
#define STAGEFILE_6 "data/stage/stage06.csv"


// �ǂݍ��ݎ��̔��ʔԍ�
enum {	
	SWITCH_MANAGER_NUM = 0,
	SWITCH_POS_X,
	SWITCH_POS_Y,
	SWITCH_ROTATE,
	SWITCH_NUM,
	SWITCH_MAX,
};


using namespace std;

void StageGenerate::LoadStage(StageNum num, SceneGame *scene) {
	string str;
	string stageStr;
	istringstream iStrStr;
	int column = 0;			// ��
	PARAMETER param;		// �z�u����ۂ̒l�i�[�p

	switch (num) {
		case STAGE_0:
			stageStr = STAGEFILE_0;
			break;
		case STAGE_1:
			stageStr = STAGEFILE_1;
			break;
		case STAGE_2:
			stageStr = STAGEFILE_2;
			break;
		case STAGE_3:
			stageStr = STAGEFILE_3;
			break;
		case STAGE_4:
			stageStr = STAGEFILE_4;
			break;
		case STAGE_5:
			stageStr = STAGEFILE_5;
			break;
		case STAGE_6:
			stageStr = STAGEFILE_6;
			break;
	}
	ifstream file(stageStr);
	
	if (file.fail()) {	// �G���[�`�F�b�N
		MessageBox(NULL, "�X�e�[�W�t�@�C���ǂݍ��݂Ɏ��s�B\n�|�[�Y�{�^���������Ė߂��Ă�������", "error", MB_OK);
		return;
	}

	// �J���}�ŋ�؂�ꂽ�Ԃ��ЂƂ܂Ƃ߂ɓǂݍ���
	while (getline(file, str, ',')) {
		iStrStr = istringstream(str);
		//�����t�@�C���ǂݍ��݁���
		//������(�l��0~4)�A
		//obj�}�l�[�W���ԍ�(int)�A���WX(float)�A���WY(float)�A�p�x(float)�A��ޔԍ�(int)��5��

		switch (column) {
			case SWITCH_MANAGER_NUM:
				iStrStr >> param.managerNum;
				break;
			case SWITCH_POS_X:
				iStrStr >> param.posX;
				break;
			case SWITCH_POS_Y:
				iStrStr >> param.posY;
				break;
			case SWITCH_ROTATE:
				iStrStr >> param.rotate;
				break;
			case SWITCH_NUM:
				iStrStr >> param.num;
				break;
		}
		column++;
		if (column < SWITCH_MAX) continue;	// �l��������ĂȂ��Ȃ炱���ŃX�g�b�v���Ď��̃��[�v��	
		// �l����������炻������Ƃɐ���
		column = 0;
		GenerateObj(param,scene);
	}

}

void StageGenerate::GenerateObj(PARAMETER param,SceneGame *scene) {
	switch (param.managerNum) {
		case MANAGER_PLAYER:
			PlayerManager::Instance()->startPos.x = param.posX;
			PlayerManager::Instance()->startPos.y = param.posY;
			break;
		case MANAGER_GROUND:
			scene->groundManager.Create(param.posX,param.posY,param.rotate,param.num);
			break;
		case MANAGER_BLOCKROTATE:
			scene->blockRotateManager.Create(param.posX, param.posY, param.rotate, param.num);
			break;
		case MANAGER_DEBUGENEMY:
			scene->dbgEnemyManager.Create(param.posX, param.posY, param.rotate, param.num);
			break;
		case MANAGER_ENEMYNORMAL:
			scene->E_normalManager.Create(param.posX, param.posY, param.rotate, param.num);
			break;		
		case MANAGER_ENEMYSHIELD:
			scene->E_shieldManager.Create(param.posX, param.posY, param.rotate, param.num);
			break;
		case MANAGER_ENEMYTOGE:
			scene->E_togeManager.Create(param.posX, param.posY, param.rotate, param.num);
			break;
		case MANAGER_OBJTOGE:
			scene->E_objTogeManager.Create(param.posX, param.posY, param.rotate, param.num);
			break;
		case MANAGER_GOAL:
			scene->goalPoint.Create(param.posX, param.posY);
			break;
		case MANAGER_POP:
			scene->tutorialManager.Create(param.posX, param.posY, param.rotate, param.num);
			break;
	}
}

void StageGenerate::GenerateObj(PARAMETER param, SceneEdit *scene) {
	switch (param.managerNum) {
		case MANAGER_GROUND:
			scene->groundManager.Create(param.posX, param.posY, param.rotate, param.num);
			break;
		case MANAGER_BLOCKROTATE:
			scene->blockRotateManager.Create(param.posX, param.posY, param.rotate, param.num);
			break;
		case MANAGER_DEBUGENEMY:
			scene->dbgEnemyManager.Create(param.posX, param.posY, param.rotate, param.num);
			break;
		case MANAGER_ENEMYNORMAL:
			scene->E_normalManager.Create(param.posX, param.posY, param.rotate, param.num);
			break;
		case MANAGER_ENEMYSHIELD:
			scene->E_shieldManager.Create(param.posX, param.posY, param.rotate, param.num);
			break;
		case MANAGER_ENEMYTOGE:
			scene->E_togeManager.Create(param.posX, param.posY, param.rotate, param.num);
			break;
		case MANAGER_OBJTOGE:
			scene->E_objTogeManager.Create(param.posX, param.posY, param.rotate, param.num);
			break;
		case MANAGER_GOAL:
			scene->goalPoint.Create(param.posX, param.posY);
			break;
		case MANAGER_POP:
			scene->tutorialManager.Create(param.posX, param.posY, param.rotate, param.num);
			break;
	}
}

