//
// �]�T����������Rush�n�̎d�l��Player�N���X����؂藣��
// 

#ifndef __PLAYER__
#define __PLAYER__

#include"main.h"
#include"Dxg2d/GameObj.h"
#include"PlayerManager.h"
#include"Move.h"
#include"HookShot.h"
#include"ObjEditMode.h"
#include"PlayerSensorCollider.h"

enum PlayerSprite {
	PLAYER_SPRITE_IDOL,
	PLAYER_SPRITE_MOVE,
	PLAYER_SPRITE_ATK,
	PLAYER_SPRITE_MAX,
};

//typedef struct {
//	int HP;
//
//}STATES;

class StopTimeGage :public GameObj{
public:
	void Init();
	void Update();
	void Draw();

	int currentGage;
	int maxGage;
private:

};


class Player:public GameObj{
public:
	void Init();
	void Update();
	void Draw();
	void EditUpdate();
	Player();

	//�����������ϐ�����������
	


private:

	void MovePos();


	void RushAttack();
	void Rush(D3DXVECTOR2 normDir);	
	void NextRush(D3DXVECTOR2 direction);
	void EndRush();
	
	void Damaged();
	
	void SelectSprite();
	void FollowCamera();					// �J�����̒ǔ�
	//�����������ϐ�����������
	
	Move move;
	HookShot hookShot;
	ObjEditMode edit;
	GroundedCollider groundedColl;	// �n�ʂ̐ݒu����
	StopTimeGage stopGage;

	// �A�j���[�V�����X�v���C�g
	Sprite *pCurSprite;		// ���ݎg���Ă���X�v���C�g
	Sprite moveSprite;
	Sprite atkSprite;
	Sprite atkEfectSprite;


	PlayerState state;	

	int rushTimeCnt;		// �ːi�̃J�E���g
	int stopCnt;			// �X�g�b�v
	int invisibleCnt;		// ���G����
	int notStopTime;		// �U���J�n���莞�ԃX�g�b�v���Ȃ��ϐ�
	float curDirect;		// ���݂ǂ���������Ă��邩�B1.0f�ŉE
	PlayerSprite spriteNum;	// 
	bool loadedStart;		// �X�^�[�g�n�_�̍��W��ǂݍ��񂾂�
	
	bool isJumped;		
	bool isDamaged;		

	//�X�e�[�^�X
	int HP;

};



#endif