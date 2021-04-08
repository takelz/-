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

	//•Ï”

	bool exist;
	~Ground() {};
private:
	void SwitchObj();		// obj‚É‚æ‚Á‚Ä’n–Ê‚Ìí—Ş‚ğ•Ï‚¦‚é

	ObjEditMode edit;
	int objNum;


};

#endif