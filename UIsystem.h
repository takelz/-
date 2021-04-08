#ifndef __UISYSTEM__
#define __UISYSTEM__

#include"main.h"

class UIsystem {
public:
	bool Button(D3DXVECTOR2 pos,D3DXVECTOR2 size);	// マウスと重なっていたらtrueを返す

	bool FadeOutAllUI(unsigned char *changeNum);				// 全体のUIをゆっくり消す。aに代入する変数を用意する。消え終わったらtrueを返す
	void StartFadeOut();							// FadeOutAllUIを起動する
	bool FadeInAllUI(unsigned char *changeNum);				// 全体のUIをゆっくり表示。aに代入する変数を用意する。表示が終わったらtrueを返す
	void StartFadeIn();							// FadeInAllUIを起動する


private:
	bool isFadeOut;
	bool isFadeIn;

};


#endif // !__UISYSTEM__
