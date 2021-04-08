//=============================================================================
//
// ���C������ [main.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_ 
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
//#include"Dxg2d\Sprite.h"


//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#if 1 // [������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C�� "�ɑΏۃ��C�u������ݒ肷��]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH (800+160)  	 	 	// �E�C���h�E�̕�
#define SCREEN_HEIGHT (600+120)  	 	 	// �E�C���h�E�̍���
#define SCREEN_CENTER_X (SCREEN_WIDTH / 2) // �E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2) // �E�C���h�E�̒��S�x���W

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) {if(x) x->Release(); x = NULL;}
#endif // !

//�����������Q�[���I�u�W�F�N�g�̃^�O�ݒ聁��������
enum TagName {
	//TAG_NOT = 0,	// �g��Ȃ�
	TAG_GROUND = 1,
	TAG_ENEMY,
	TAG_ENEMYB,
	TAG_PLAYER,
	TAG_GOAL,
	TAG_NOT,		// ������
	TAG_MAX,
};

// �t�������鎞�͉��ɒǉ����Ă����B
enum Manager {
	MANAGER_PLAYER,
	MANAGER_GROUND,
	MANAGER_BLOCKROTATE,
	MANAGER_DEBUGENEMY,
	MANAGER_ENEMYNORMAL,
	MANAGER_ENEMYSHIELD,
	MANAGER_ENEMYTOGE,
	MANAGER_OBJTOGE,
	MANAGER_GOAL,			// ����̓}�l�[�W���[�ł͂Ȃ�
	MANAGER_POP,
	MANAGER_MAX,
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
HWND GetHwnd();						// �E�B���h�E���擾
D3DXVECTOR2 GetMousePos();			// ��ʓ��̃}�E�X�̍��W(�J�����̍��W�͍l�����Ă��Ȃ�)
void SetOnDestBlend();				// ���Z�������I���A�g������Ō�ɂ��Ȃ炸�I�t�ɂ���
void SetOffDestBlend();				// ���Z�������I�t
void SetOnBlendOne();
void SetOffBlendOne();

bool IsOutScreen(D3DXVECTOR2 pos);	// �Ώۂ���ʔ͈͊O�ɂ��邩�ǂ���

// �}�l�[�W���[�̊��N���X
class BaseManager {

public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void EditUpdate() = 0;	// �X�e�[�W�G�f�B�b�g�p�X�V����
	virtual void Draw() = 0;
	//virtual void Uninit() = 0;

	virtual void Create(float posX, float posY, float rotate, int num) = 0;

private:
protected:


};

#endif // _MAIN_H_
