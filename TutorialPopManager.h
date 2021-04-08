// ”ÍˆÍ“à‚É‚¢‚é‚ÆTUTORIAL‚ª•\¦‚³‚ê‚é
// 	TUTO_POP_MOVE,		objNum‚Í‚±‚Ì‡”Ô
//	TUTO_POP_ATTACK,
//	TUTO_POP_GAGE,
//	TUTO_POP_HP,
//	TUTO_POP_CHAIN,
//
//

#include"main.h"
#include"TutorialPop.h"


class TutorialPopManager :public BaseManager {
public:
	void Init();
	void Create(float posX,float poxY,float rotate,int objNum);
	void Update();
	void EditUpdate();
	void Draw();

private:
	TutorialPop pop[TUTO_POP_MAX];

};

