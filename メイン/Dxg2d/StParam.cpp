// ���wii�J���p
//

#include"StParam.h"

// �^�C�}�[�B�w�莞�ԃX�g�b�v�B�X�g�b�v���I�������true��Ԃ�
bool StopTime(int *counter, int STOP_FRAME) {

	if (*counter < 0) *counter = 0;	// 1�ȉ��Ȃ�0�ɂ��ăX�^�[�g

	if (STOP_FRAME > *counter) {
		*counter += 1;
		return false;
	} else {
		*counter = 0;
		return true;
	}

}



