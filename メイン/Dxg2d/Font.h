// �t�H���g�\��
// ������̂ݕ\���\
//

#ifndef __FONT__
#define __FONT__

#include"../main.h"
#include"Sprite.h"

#define MAX_FONTCHARACTER (32)	// ��x�ɕ\���ł��镶���̉�
#define MAX_DISP_CHAR (32)		// �\���ł��镶���̍ő�l

#define STD_CHAR_SIZE_X (25)
#define STD_CHAR_SIZE_Y (40)


// �o�͂��邽�߂̕����f�[�^�̕ۑ��N���X
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

// �������o�͂���N���X
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
	void CalcCharCode(char code,int *numU,int *numV);		// ���͂��ꂽ��������R�[�h���v�Z�AUV���W�����o����
	Sprite *SelectSprite(int *numV);							// �v�Z���ꂽV���W����ǂ̉摜���g�������߂�

	FontCharacter fontChar[MAX_FONTCHARACTER];
	Sprite number;		// �����A�L��
	Sprite alphabet;	// �啶���A�������A�L��
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
