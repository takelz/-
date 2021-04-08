#ifndef __DESTROYPARTICLE__
#define __DESTROYPARTICLE__

#include"main.h"
#include"Dxg2d\GameObj.h"

class DestroyParticle :public GameObj{
public:
	void Init();
	void Update();
	void Draw();
	void Create(float posX, float posY,float accX,float accY);
	bool exist;
private:
	bool loadedSprite;	

};


#endif // !__DESTROYPARTICLE__
