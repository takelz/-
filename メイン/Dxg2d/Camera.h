//シングルトン
//
//カメラの処理
//オブジェクトの座標はカメラ座標からの相対距離
//
//～更新履歴～
//2018/07/24	完成
//

#ifndef __CAMERA__
#define __CAMERA__

#include"../main.h"
//#include"StParam.h"



class Camera {
public:
	static Camera *Instance() {
		static Camera camera;
		return &camera;
	}
	static void Delete() {
		delete Instance();
	}

	void ShakeUpdate();	// カメラ振動、常にアップデートに
	void Shake();		// カメラ振動の読み出し

	//＝＝＝＝＝変数＝＝＝＝＝
	D3DXVECTOR2 shakeOffset;	// 振動による座標ズレ
	D3DXVECTOR2 pos;
	
private:
	float shakeNum;
	float shakeRange;

	float signAngle;
	bool direction;		// 振動の向き

	Camera() {};
	~Camera() {};
};


#endif // !__TRANSFORM__
