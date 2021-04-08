#ifndef __GROUND__
#define __GROUND__

#include"main.h"
#include"Dxg2d/GameObj.h"
#include"ObjEditMode.h"

class Ground:public GameObj{
public:
	void Init();
	void Update();
	void Draw();

	void EditUpdate();
	void Create(float posX, float posY, float rotate, int numU, int numV,int num);

	//�����������ϐ�����������

	bool exist;
	~Ground() {};
private:
	void SwitchObj();		// obj�ɂ���Ēn�ʂ̎�ނ�ς���

	ObjEditMode edit;
	int objNum;


};

#endif