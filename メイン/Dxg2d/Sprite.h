//�X�v���C�g�\�� 
// 
// 2018/07/24	����

#ifndef __SPRITE__
#define __SPRITE__

#include"../main.h"
#include"StParam.h"
#include"SpriteAnim.h"

class Color {
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

	Color operator =(unsigned char clr) {	// �A���t�@�l�ȊO���ꊇ�ŕς���
		r = g = b = clr;
		return *this;
	}
};

typedef struct  {
	D3DVECTOR pos;
	float rhw;
	D3DCOLOR diffuse;
	float u, v;
}VERTEX_2D;

//�����������N���X����������

class SpriteAnim {
public:
	void Init(int spdCount, int u, int v);
	void Update(bool anim);	// �A�j���[�V�����g���Ȃ�true
	bool GetEndAnim();		// �A�j���[�V�����̃��[�v�̍Ō�ɂȂ�����true��Ԃ�
	
	int currentU, currentV;
	float vertexU[4];
	float vertexV[4];

private:
	int spriteU, spriteV;
	int frameCount;		// ���̃t���[���ɍs���܂ł̎��ԃJ�E���g
	int curImageX;		// ���݂ǂ̉摜��\�����Ă��邩
	int curImageY;
	int timeNextFrame;	// �ǂ̂��炢�̃J�E���g�Ŏ��̃t���[���ֈڍs���邩
	bool endAnim;		// �A�j���[�V�����̏I��
	bool roopAnim;		// �A�j���[�V���������[�v�����邩

}; 



class Sprite {
public:
	//�����������ϐ�����������
	
	SpriteAnim anim;
	D3DXVECTOR2 size;
	D3DXVECTOR2 pos;
	D3DXVECTOR2 scale;
	Color color;
	float rotate;
	bool reverseX;
	bool reverseY;
	bool useAnim;


	// �R���X�g���N�^�A�f�X�g���N�^
	Sprite();
	~Sprite();

	//�����������֐�������������

	void Load(LPCSTR fileName,int spdCount, int u, int v);
	void Load(LPCSTR fileName);
	void Update();
	void Draw();
	void Uninit();
	void SetUV(int u, int v);

private:
	//�����������ϐ�����������

	LPDIRECT3DTEXTURE9 pTexture;
	VERTEX_2D vertex[4];


	//�����������֐�����������

	void InitVertex();
};


#endif // !__SPRITE__
