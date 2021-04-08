// フォント表示
// 現状一列のみ表示可能
//

#ifndef __FONT__
#define __FONT__

#include"../main.h"
#include"Sprite.h"

#define MAX_FONTCHARACTER (32)	// 一度に表示できる文字の塊
#define MAX_DISP_CHAR (32)		// 表示できる文字の最大値

#define STD_CHAR_SIZE_X (25)
#define STD_CHAR_SIZE_Y (40)


// 出力するための文字データの保存クラス
class FontCharacter {
public:
	void CreateCharacter(char *input, float paramPosX, float paramPosY, float paramSizeX, float paramSizeY, Color paramColor);

	char dispChar[MAX_DISP_CHAR];
	int characterMax;
	float posX;
	float posY;
	float sizeX;
	float sizeY;
	Color color;
	bool exist;
private:




};

// 文字を出力するクラス
class Font {
public:

	void Init();
	void Update();
	void Draw();


	void InputChar(char *input, float paramPosX, float paramPosY);
	void InputChar(char *input, float paramPosX, float paramPosY,float paramSizeX,float paramSizeY);

	void SetColor(unsigned char r, unsigned char g, unsigned char b);
	void SetAlpha(unsigned char alpha);

	
private:
	void CalcCharCode(char code,int *numU,int *numV);		// 入力された文字からコードを計算、UV座標を検出する
	Sprite *SelectSprite(int *numV);							// 計算されたV座標からどの画像を使うか決める

	FontCharacter fontChar[MAX_FONTCHARACTER];
	Sprite number;		// 数字、記号
	Sprite alphabet;	// 大文字、小文字、記号
	Sprite hiragana;	
	Sprite katakana;

	D3DXVECTOR2 pos;
	unsigned char setColorR;
	unsigned char setColorG;
	unsigned char setColorB;
	unsigned char setColorA;


	int maxChar;
};



#endif // !__FONT__
