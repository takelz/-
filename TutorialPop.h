

#include"main.h"
#include"Dxg2d\GameObj.h"
#include"ObjEditMode.h"
#include"Move.h"

enum {
	TUTO_POP_MOVE,	
	TUTO_POP_ATTACK,
	TUTO_POP_GAGE,
	TUTO_POP_HP,
	TUTO_POP_CHAIN,
	TUTO_POP_MAX,
};


class TutorialPop:public GameObj {
public:
	void Init();
	void Create(float posX, float posY, int paramObjNum);
	void Update();
	void EditUpdate();
	void Draw();

	bool exist;
private:
	Sprite secondSprite;	// ATTACKの補足説明
	Move move;
	int objNum;
	bool dispPop;

	ObjEditMode edit;
	bool editLoeaded;	// エディットモード用


};

