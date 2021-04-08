
#include"ObjEditMode.h"
#include"SceneEdit.h"
#include"main.h"
#include"Dxg2d\Camera.h"
#include"Dxg2d\input.h"
#include<string>
#include<fstream>
#include<sstream>



static bool isClick;	// クリック中は他の物をつかめない

void ObjEditMode::EditObject(Transform *transform,bool *exist,Manager managerNum,int objNum) {
	MoveObj(transform);
	DestroyObj(transform,exist);
	RotateObj(transform);
	SaveCsv(transform, managerNum, objNum);
}

void ObjEditMode::MoveObj(Transform *transform) {
	D3DXVECTOR2 mousePos = GetMousePos();

	if (CollideClick(transform,mousePos)) {
		if ((DIGetMouseButton(DIK_LEFT_CLICK) && !isClick )|| leaveThis) {	// 他のオブジェクトがクリックされているなら処理しない(自身がクリックされているなら例外)
			isClick = true;
			leaveThis = true;

			// 代入
			transform->pos.x = mousePos.x - Camera::Instance()->pos.x;
			transform->pos.y = mousePos.y - Camera::Instance()->pos.y;

			AdjustPos(&transform->pos);
		}
	}
	if (DIGetMouseRelease(DIK_LEFT_CLICK)) {	// ボタン離すまでは他をつかめない
		isClick = false;
		leaveThis = false;
	}
}

void ObjEditMode::RotateObj(Transform *transform) {
	if (CollideClick(transform, GetMousePos())) {
		if (DIGetKeyTrigger(DIK_C)) {				// ボタンで角度リセット
			transform->rotate = 0.0f;
		}
		if (DIGetKeyTrigger(DIK_V)) {				// ボタンで角度45°追加
			transform->rotate += 45.0f;
		}
		if (DIGetMouseButton(DIK_RIGHT_CLICK)) {	// 右クリックしながら左右移動で角度調整
			transform->rotate += oldMousePos.x - GetMousePos().x;
		}

	}
	oldMousePos = GetMousePos();

}

void ObjEditMode::DestroyObj(Transform *transform,bool *exist) {
	if (CollideClick(transform, GetMousePos())) {
		if(DIGetKeyTrigger(DIK_Z)){
			*exist = false;
		}
	}
}

void ObjEditMode::SaveCsv(Transform *transform, Manager managerNum,int objNum) {
	if (!GetPushedSave()) return;
	*GetSaveFile() << managerNum << "," << transform->pos.x << "," << transform->pos.y << "," <<
					transform->rotate << "," << objNum << ",\n";


}


bool ObjEditMode::CollideClick(Transform *transform, D3DXVECTOR2 mousePos) {
	float smallSize;
	mousePos.x -= Camera::Instance()->pos.x;
	mousePos.y -= Camera::Instance()->pos.y;

	// 小さいサイズを基準に
	if (transform->size.x > transform->size.y) smallSize = transform->size.y;
	else smallSize = transform->size.x / 2;// クリックできる範囲をサイズの半分に

	if ((transform->pos.x - mousePos.x) * (transform->pos.x - mousePos.x) + (transform->pos.y - mousePos.y) *  (transform->pos.y - mousePos.y) <= smallSize * smallSize) {
		return true;
	} else {
		return false;
	}

}

void ObjEditMode::AdjustPos(D3DXVECTOR2 *pos) {
	int adjPosX = (int)pos->x;	// キャストで小数点切り捨て
	int adjPosY = (int)pos->y;
	int minusX,minusY;			// 一桁目を引く
	minusX = adjPosX % 10;
	minusY = adjPosY % 10;

	pos->x = adjPosX - (float)minusX;
	pos->y = adjPosY - (float)minusY;

}