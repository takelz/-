

#ifndef __DESTROYPARTICLEEMITTER__
#define __DESTROYPARTICLEEMITTER__

#include"main.h"
#include"Dxg2d\GameObj.h"
#include"DestroyParticle.h"

#define MAX_DEST_PARTICLE (64)

class DestroyParticleEmitter {
public:
	static DestroyParticleEmitter *Instance() {
		static DestroyParticleEmitter playerManager;
		return &playerManager;
	}
	static void Delete() {
		delete Instance();
	}


	void Init();
	void Update();
	void Draw();
	void Emission(float posX, float posY);
private:
	DestroyParticle destParticle[MAX_DEST_PARTICLE];

};


#endif // !__DESTROYPARTICLE__
