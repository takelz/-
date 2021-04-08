//スプライト表示 
// 
// 2018/07/24	完成

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

	Color operator =(unsigned char clr) {	// アルファ値以外を一括で変える
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

//＝＝＝＝＝クラス＝＝＝＝＝

class SpriteAnim {
public:
	void Init(int spdCount, int u, int v);
	void Update(bool anim);	// アニメーション使うならtrue
	bool GetEndAnim();		// アニメーションのループの最後になったらtrueを返す
	
	int currentU, currentV;
	float vertexU[4];
	float vertexV[4];

private:
	int spriteU, spriteV;
	int frameCount;		// 次のフレームに行くまでの時間カウント
	int curImageX;		// 現在どの画像を表示しているか
	int curImageY;
	int timeNextFrame;	// どのぐらいのカウントで次のフレームへ移行するか
	bool endAnim;		// アニメーションの終了
	bool roopAnim;		// アニメーションをループさせるか

}; 



class Sprite {
public:
	//＝＝＝＝＝変数＝＝＝＝＝
	
	SpriteAnim anim;
	D3DXVECTOR2 size;
	D3DXVECTOR2 pos;
	D3DXVECTOR2 scale;
	Color color;
	float rotate;
	bool reverseX;
	bool reverseY;
	bool useAnim;


	// コンストラクタ、デストラクタ
	Sprite();
	~Sprite();

	//＝＝＝＝＝関数＝＝＝＝＝＝

	void Load(LPCSTR fileName,int spdCount, int u, int v);
	void Load(LPCSTR fileName);
	void Update();
	void Draw();
	void Uninit();
	void SetUV(int u, int v);

private:
	//＝＝＝＝＝変数＝＝＝＝＝

	LPDIRECT3DTEXTURE9 pTexture;
	VERTEX_2D vertex[4];


	//＝＝＝＝＝関数＝＝＝＝＝

	void InitVertex();
};


#endif // !__SPRITE__
