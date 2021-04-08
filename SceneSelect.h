#ifndef __SCENESELECT__
#define __SCENESELECT__


#include"SceneBase.h"
#include"BackGround.h"
#include"Dxg2d\Font.h"
#include"UIsystem.h"
#include"SelectSystem.h"
#include"BackGround.h"



class SceneSelect :public SceneBase {
public:
	void Init();
	void Update();
	void Draw();
	void Uninit();
private:

	SelectSystem selectSystem;
	BackGround bg;
	UIsystem uiSystem;

};

#endif