#include"Font.h"

#define FILE_NUM "data/font/font_number3.png"
#define FILE_NUM_U (16)
#define FILE_NUM_V (2)

#define FILE_ALPHA "data/font/font_alphabet3.png"
#define FILE_ALPHA_U (16)
#define FILE_ALPHA_V (4)




void Font::Init() {
	number.Load(FILE_NUM, 0, FILE_NUM_U, FILE_NUM_V);
	alphabet.Load(FILE_ALPHA, 0,FILE_ALPHA_U, FILE_ALPHA_V);
	
}
 
void Font::Update() {

}

void Font::Draw() {
	int		numU,numV;		// 受け取り用変数
	Sprite *sprite;			// 受け取り用変数
	float offsetPos;



	for (int i = 0; i < MAX_FONTCHARACTER; i++) {
		if (!fontChar[i].exist) continue;


		for (int   num = 0; num < fontChar[i].characterMax; num++) {


			CalcCharCode(fontChar[i].dispChar[num], &numU, &numV);

			sprite = SelectSprite(&numV);		// V座標からどの画像を使うか判別し、対応した数分数値をずらす
			
			// 色の変更
			sprite->color = fontChar[i].color;

			offsetPos = (fontChar[i].sizeX * (fontChar[i].characterMax));
			sprite->pos.x = fontChar[i].posX + num * fontChar[i].sizeX - (offsetPos - offsetPos * 0.5f) + fontChar[i].sizeX;
			sprite->pos.y = fontChar[i].posY;
			sprite->SetUV(numU, numV);
			sprite->size.x = fontChar[i].sizeX;
			sprite->size.y = fontChar[i].sizeY;
			
			sprite->Update();
			sprite->Draw();

			sprite->color.r = sprite->color.g = sprite->color.b = sprite->color.a = 255;	// 元に戻す
		}

	}
	// 終わったらもとに戻す
	setColorR = setColorG = setColorB = setColorA = 255;

	for (int i = 0; i < MAX_FONTCHARACTER; i++) {
		fontChar[i].exist = false;
	}
}


void Font::InputChar(char *input, float paramPosX, float paramPosY) {

	InputChar(input, paramPosX, paramPosY,STD_CHAR_SIZE_X,STD_CHAR_SIZE_Y);
}

void Font::InputChar(char *input, float paramPosX, float paramPosY, float paramSizeX, float paramSizeY) {
	Color color;
	color.r = setColorR;
	color.g = setColorG;
	color.b = setColorB;
	color.a = setColorA;

	for (int i = 0; i < MAX_FONTCHARACTER; i++) {
		if (fontChar[i].exist) continue;
		fontChar[i].CreateCharacter(input, paramPosX, paramPosY,paramSizeX,paramSizeY, color);
		break;
	}
	// 終わったらもとに戻す
	setColorR = setColorG = setColorB = setColorA = 255;
}

void Font::SetColor(unsigned char r, unsigned char g, unsigned char b) {
	setColorR = r;
	setColorG = g;
	setColorB = b;

}
void Font::SetAlpha(unsigned char a) {
	setColorA = a;
}


void Font::CalcCharCode(char code,int *numU,int *numV) {
	*numU = code & 0x0F;	// 下位4ビット抽出
	*numV = code & 0xF0;	// 上位4ビット抽出
	*numV = *numV >> 4;		// 上位4ビットが一桁目に来るように左4ビットシフト
	*numU += 1;				// ずれの調整
}

Sprite* Font::SelectSprite(int *numV) {
	if (2 <= *numV && *numV < 4) {
		*numV -= FILE_NUM_V - 1;
		return &number;	// 2~3なら番号
	}
	if (4 <= *numV && *numV < 8) {
		*numV -= FILE_ALPHA_V - 1;
		return &alphabet;	// 4~8ならアルファベット
	}

	return &alphabet;		// どれもヒットしなかったらalphabetを返す

}


//＝＝＝＝＝FontCharacterクラス＝＝＝＝＝

void FontCharacter::CreateCharacter(char *input, float paramPosX, float paramPosY,float paramSizeX,float paramSizeY,Color paramColor) {

	for (int i = 0; i < MAX_DISP_CHAR; i++) {
		if (input[i] == '\0') {					// null文字なら終わる
			characterMax = i;				// 終わるときに最大文字数保存
			break;
		}
		dispChar[i] = input[i];
	}
	posX = paramPosX;
	posY = paramPosY;
	sizeX = paramSizeX;
	sizeY = paramSizeY;
	color = paramColor;
	exist = true;

}

