// 主にwii開発用
//

#include"StParam.h"

// タイマー。指定時間ストップ。ストップが終わったらtrueを返す
bool StopTime(int *counter, int STOP_FRAME) {

	if (*counter < 0) *counter = 0;	// 1以下なら0にしてスタート

	if (STOP_FRAME > *counter) {
		*counter += 1;
		return false;
	} else {
		*counter = 0;
		return true;
	}

}



