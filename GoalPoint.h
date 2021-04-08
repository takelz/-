
#ifndef __GOALPOINT__
#define __GOALPOINT__

#include"Dxg2d\GameObj.h"
#include"ObjEditMode.h"
#include"Move.h"


class GoalPoint :public GameObj{
public:
	void Init();
	void Update();
	void EditUpdate();
	void Draw();
	void Create(float posX, float posY);

private:
	void Goaled();

	Move move;
	float colorNum;
	unsigned char spriteColor;
	ObjEditMode edit;
	bool isGoaled;
	bool exist;			// É_É~Å[
};


#endif // !__GOALPOINT__
