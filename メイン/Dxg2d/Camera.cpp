
#include"Camera.h"

#define MAX_SHAKE (10.0f)
#define STOP_SPEED (0.4f)		// �~�܂鑬��
#define PI (3.1415f)

void Camera::ShakeUpdate() {
	if (shakeRange < 0.1f) return;

	signAngle += shakeRange;

	shakeNum = sinf(-PI/2 + signAngle * PI / 180) * 10;


	shakeOffset.x = (shakeNum - shakeNum/2) +  shakeNum * 0.02f;
	shakeOffset.y = (shakeNum - shakeNum/2) +  shakeNum * 0.02f;

	if (0 < shakeRange) {
		shakeRange -= STOP_SPEED;
	} else {
		if (fabsf(shakeOffset.x) > 0.1f && fabsf(shakeOffset.y) > 0.1f) {	// �����T�C���g�I������Ƃ��J�����̏����l���痣��Ă����ꍇ���Ƃɖ߂�܂ŃT�C�����~�߂Ȃ�
			shakeRange = 0.5f;
		} else {
			shakeRange = 0;
			shakeOffset.x = 0;
			shakeOffset.y = 0;
		}
	}
}

void Camera::Shake() {
	shakeRange = MAX_SHAKE;
}

