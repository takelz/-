
#include"ObjEditMode.h"
#include"SceneEdit.h"
#include"main.h"
#include"Dxg2d\Camera.h"
#include"Dxg2d\input.h"
#include<string>
#include<fstream>
#include<sstream>



static bool isClick;	// �N���b�N���͑��̕������߂Ȃ�

void ObjEditMode::EditObject(Transform *transform,bool *exist,Manager managerNum,int objNum) {
	MoveObj(transform);
	DestroyObj(transform,exist);
	RotateObj(transform);
	SaveCsv(transform, managerNum, objNum);
}

void ObjEditMode::MoveObj(Transform *transform) {
	D3DXVECTOR2 mousePos = GetMousePos();

	if (CollideClick(transform,mousePos)) {
		if ((DIGetMouseButton(DIK_LEFT_CLICK) && !isClick )|| leaveThis) {	// ���̃I�u�W�F�N�g���N���b�N����Ă���Ȃ珈�����Ȃ�(���g���N���b�N����Ă���Ȃ��O)
			isClick = true;
			leaveThis = true;

			// ���
			transform->pos.x = mousePos.x - Camera::Instance()->pos.x;
			transform->pos.y = mousePos.y - Camera::Instance()->pos.y;

			AdjustPos(&transform->pos);
		}
	}
	if (DIGetMouseRelease(DIK_LEFT_CLICK)) {	// �{�^�������܂ł͑������߂Ȃ�
		isClick = false;
		leaveThis = false;
	}
}

void ObjEditMode::RotateObj(Transform *transform) {
	if (CollideClick(transform, GetMousePos())) {
		if (DIGetKeyTrigger(DIK_C)) {				// �{�^���Ŋp�x���Z�b�g
			transform->rotate = 0.0f;
		}
		if (DIGetKeyTrigger(DIK_V)) {				// �{�^���Ŋp�x45���ǉ�
			transform->rotate += 45.0f;
		}
		if (DIGetMouseButton(DIK_RIGHT_CLICK)) {	// �E�N���b�N���Ȃ��獶�E�ړ��Ŋp�x����
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

	// �������T�C�Y�����
	if (transform->size.x > transform->size.y) smallSize = transform->size.y;
	else smallSize = transform->size.x / 2;// �N���b�N�ł���͈͂��T�C�Y�̔�����

	if ((transform->pos.x - mousePos.x) * (transform->pos.x - mousePos.x) + (transform->pos.y - mousePos.y) *  (transform->pos.y - mousePos.y) <= smallSize * smallSize) {
		return true;
	} else {
		return false;
	}

}

void ObjEditMode::AdjustPos(D3DXVECTOR2 *pos) {
	int adjPosX = (int)pos->x;	// �L���X�g�ŏ����_�؂�̂�
	int adjPosY = (int)pos->y;
	int minusX,minusY;			// �ꌅ�ڂ�����
	minusX = adjPosX % 10;
	minusY = adjPosY % 10;

	pos->x = adjPosX - (float)minusX;
	pos->y = adjPosY - (float)minusY;

}