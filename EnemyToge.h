//�ړ��݂̂̓G
//����ȍs���͂��Ȃ�
//
//
#ifndef __ENEMYTOGE__
#define __ENEMYTOGE__
  
#include"main.h"
#include"EnemyNormal.h"
#include"Dxg2d/GameObj.h"
#include"Ground.h"
#include"Move.h"

class TogeObj :public GameObj {
public:
	void Init();
	void Update();
	void Draw();
	void Uninit();

	bool isToge;;		// ���ݍU����Ԃ�
private:

	Move move;

};


class EnemyToge : public EnemyNormal{
public:
	void Init();
	void Update();
	void Draw();
	void EditUpdate();

	void Create(float posX, float posY, float rotat,int num);

	//�����������ϐ�����������

	bool exist;

private:

	void SetupToge();

	//�����������ϐ�����������

	//�U�蕪��
	int typeNum;	
	ObjEditMode edit;
	Sprite spriteCloss;
	Sprite spriteEffect;

	TogeObj togeObj;
	
};





#endif