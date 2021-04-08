//
//�V���O���g��
//

#ifndef __PLAYERMANAGER__
#define __PLAYERMANAGER__

#include"main.h"
#include"Dxg2d/GameObj.h"


enum  PlayerState {
	PLAYER_NORMAL,		
	PLAYER_ATACK,		// �󒆓ːi���
	PLAYER_DAMAGED,		// ��_���[�W��
	PLAYER_STATE_MAX,
};



class PlayerManager{
public:
	static PlayerManager *Instance() {
		static PlayerManager playerManager;
		return &playerManager;
	}
	static void Delete() {
		delete Instance();
	}



	// �v���C���[�֗^����U�����
	void SetAtackedEnemy(D3DXVECTOR2 paramKnockBack);
	// �v���C���[�֗^����U�����
	void SetAtackedEnemy();

	// �v���C���[�����炤�U�����B�U��������������true��Ԃ�
	bool GetAttackedState(D3DXVECTOR2 *paramKnockBack);

	// �v���C���[�����炤�U�����B�U��������������true��Ԃ�
	bool GetAttackedState();

	// �ˌ��񐔂̎擾�B0�͓ˌ����ĂȂ�
	int GetRushCount();

	// �ˌ��񐔂𑝂₷
	void CountUpRush();
	// �ˌ��񐔃��Z�b�g�B0��
	void ResetRushCount();

	// �t�b�N�V���b�g�̊J�n
	void StartHook(D3DXVECTOR2 posision);

	// �G�������v���C���[�̓ˌ��U�����󂯂���
	void SendRushSuccess();

	// �v���C���[���擾����X�^�[�g�|�W�V����
	D3DXVECTOR2 GetStartPos();


	//�����������ϐ�����������

	PlayerState state;
	D3DXVECTOR2 pos;	
	bool attackSuccess;		// �ːi�U��������������
	D3DXVECTOR2 hookPoint;
	D3DXVECTOR2 startPos;	// �X�^�[�g
	bool hookOn;
	bool enemyAtacked;		// �G���U���������ǂ����B�v���C���[�͂���ɒ��ڃA�N�Z�X���Ȃ�����
	int playerHP;

private:

	PlayerManager() {};
	~PlayerManager() {};



	D3DXVECTOR2 knockBack;	// �m�b�N�o�b�N�̃x�N�g��
	int rushCount;			// ���݂̓ˌ���

};

#endif