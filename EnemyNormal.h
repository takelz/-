//�ړ��݂̂̓G
//����ȍs���͂��Ȃ�
//
//
#ifndef __NORMALENEMY__
#define __NORMALENEMY__

#include"main.h"
#include"Dxg2d/GameObj.h"
#include"Ground.h"
#include"Move.h"

class EnemyNormalEffect :public GameObj{
public:
	void Init(float sizeX,float sizeY);
	void Update();
	void Draw();
private:
	Move move;
	float colorNum;	// �F�ω��p
};


class EnemyNormal : public GameObj{
public:
	void Init();
	void Update();
	void Draw();
	void EditUpdate();
	void Create(float posX, float posY, float rotat,int num);

	//�����������ϐ�����������

	bool exist;

protected:

	// �v���C���[�Ɍ������Đi��
	void MoveToPlayer();

	// ���E���㉺��sign�g�ړ�
	void MoveLoop(bool isSIde,float speed,float range);

	// ���g���i�ޕ���������(�X�v���C�g�����E���])
	void FaceToMove();

	// type�ɂ�镪��
	void SelectMove();

	Move move;
	EnemyNormalEffect enemyEffect;
	ObjEditMode edit;
	//�����������ϐ�����������

	//�U�蕪��
	int typeNum;	
};

#endif