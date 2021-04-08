//�����I�u�W�F�N�g�̃G�f�B�b�g���[�h���̋���
//

#ifndef __OBJEDITMODE__
#define __OBJEDITMODE__

#include"Dxg2d\GameObj.h"




class ObjEditMode{

public:
	void EditObject(Transform *transform,bool *exist,Manager managerNum, int objNum);


private:
	void MoveObj(Transform *transform);
	void DestroyObj(Transform *transform, bool *exist);
	void RotateObj(Transform *transform);
	void SaveCsv(Transform *transform,Manager managerNum,int objNum);			// �Z�[�u
	void AdjustPos(D3DXVECTOR2 *pos);								// 10�{���ɂȂ�悤��
	bool CollideClick(Transform *transform,D3DXVECTOR2 mousePos);	// �J�[�\�����G��Ă���Ƃ�(�I�u�W�F�N�g�͉~�Ŕ�����Ƃ�)

	//�����������ϐ�����������
	bool leaveThis;				// ���̃I�u�W�F�N�g���N���b�N����Ă��邩
	D3DXVECTOR2 oldMousePos;	

};







#endif