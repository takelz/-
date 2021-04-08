//書くオブジェクトのエディットモード時の挙動
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
	void SaveCsv(Transform *transform,Manager managerNum,int objNum);			// セーブ
	void AdjustPos(D3DXVECTOR2 *pos);								// 10倍数になるように
	bool CollideClick(Transform *transform,D3DXVECTOR2 mousePos);	// カーソルが触れているとき(オブジェクトは円で判定をとる)

	//＝＝＝＝＝変数＝＝＝＝＝
	bool leaveThis;				// このオブジェクトがクリックされているか
	D3DXVECTOR2 oldMousePos;	

};







#endif