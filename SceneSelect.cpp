#include"SceneSelect.h"
#include"Dxg2d\input.h"





void SceneSelect::Init() {
	bg.Init();
	selectSystem.Init();

}
void SceneSelect::Update() {
	bg.Update();
	selectSystem.Update();
	MagicEmitter::Instance()->Generate();
	MagicEmitter::Instance()->Update();

}
void SceneSelect::Draw() {
	bg.Draw();
	MagicEmitter::Instance()->Draw();
	
	selectSystem.Draw();
}

void SceneSelect::Uninit() {
	delete this;
}