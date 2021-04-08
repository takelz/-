#include"Sprite.h"


#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_DIFFUSE)

static float workX;
static float workY;
static float workSin;
static float workCos;


Sprite::Sprite() {
	InitVertex();
	useAnim = false;
	rotate = 0.0f;
	pos.x = pos.y = 0.0f;
	size.x = size.y = 10.0f;
	scale.x = scale.y = 1.0f;
	color.r = color.g = color.b = color.a = 255;
}

Sprite::~Sprite() {
	if (pTexture) {
		pTexture->Release();
		pTexture = NULL;
	}
}


void Sprite::InitVertex() {
	vertex[0] = { { SCREEN_CENTER_X,	SCREEN_CENTER_Y,	0.0f }, 1.0f,D3DCOLOR_ARGB(255,255,255,255),	0.0f,0.0f };
	vertex[1] = { { SCREEN_CENTER_X,	SCREEN_CENTER_Y,	0.0f },	1.0f,D3DCOLOR_ARGB(255,255,255,255),	1.0f,0.0f };
	vertex[2] = { { SCREEN_CENTER_X,	SCREEN_CENTER_Y,	0.0f },	1.0f,D3DCOLOR_ARGB(255,255,255,255),	0.0f,1.0f };
	vertex[3] = { { SCREEN_CENTER_X,	SCREEN_CENTER_Y,	0.0f },	1.0f,D3DCOLOR_ARGB(255,255,255,255),	1.0f,1.0f };
}


void Sprite::Load(LPCSTR fileName,int spdCount,int u,int v) {

	LPDIRECT3DDEVICE9 pDevice;
	HRESULT hr;


	pDevice = GetDevice();
	//�e�N�X�`���ǂݍ���
	hr = D3DXCreateTextureFromFile(pDevice, fileName, &pTexture);

	//�G���[�`�F�b�N
	if (FAILED(hr)) {
		pTexture = NULL;
		MessageBox(NULL, "�e�N�X�`���ǂݍ��ݎ��s", fileName, MB_OK);
	}

	anim.Init(spdCount, u, v);
	
}


void Sprite::Load(LPCSTR fileName) {
	Load(fileName,1,1,1);

}



void Sprite::Update() {
	anim.Update(useAnim);

	// �摜�̔��]

	// �A�j���[�V�����g���ꍇ
	//if (useAnim) {
		if (reverseX) {
			vertex[0].u = anim.vertexU[1];
			vertex[1].u = anim.vertexU[0];
			vertex[2].u = anim.vertexU[3];
			vertex[3].u = anim.vertexU[2];
		} else {
			vertex[0].u = anim.vertexU[0];
			vertex[1].u = anim.vertexU[1];
			vertex[2].u = anim.vertexU[2];
			vertex[3].u = anim.vertexU[3];
		}

		if (reverseY) {
			vertex[0].v = anim.vertexV[0];
			vertex[1].v = anim.vertexV[1];
			vertex[2].v = anim.vertexV[2];
			vertex[3].v = anim.vertexV[3];
		} else {
			vertex[0].v = anim.vertexV[1];
			vertex[1].v = anim.vertexV[0];
			vertex[2].v = anim.vertexV[3];
			vertex[3].v = anim.vertexV[2];
		}


}


//�����`�揈������
void Sprite::Draw() {
	if (IsOutScreen(pos)) return;	// ��ʊO�Ȃ�`�悵�Ȃ�
	workSin = sinf(D3DXToRadian(rotate));
	workCos = cosf(D3DXToRadian(rotate));

	// ���W
	for (int i = 0; i < 4; i++) {
		workX = ((i & 1)  * size.x - size.x / 2 ) * scale.x;
		workY = ((i >> 1) * size.y - size.y / 2 ) * scale.y;
		vertex[i].pos.x = pos.x + workX * workCos - workY * workSin;
		vertex[i].pos.y = pos.y + workX * workSin + workY * workCos;

		// �F�w��
		vertex[i].diffuse = D3DCOLOR_ARGB(color.a,color.r, color.g, color.b);
	}
	

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�����ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, pTexture);
	//�|���S���`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(vertex[0]));

}

//�����I����������
void Sprite::Uninit() {
	

	//�e�N�X�`���̉��
	if (pTexture) {
		pTexture->Release();
		pTexture = NULL;
	}

}

void Sprite::SetUV(int u,int v) {
	anim.currentU = u;
	anim.currentV = v;
}

