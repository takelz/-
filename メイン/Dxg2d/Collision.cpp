

#include"Collision.h"
#include"input.h"
#include<deque>


#define MAX_SAVE_TRANS_STATE (1024)

#define NOT_COLLIDE_DIST (SCREEN_WIDTH + 100)	// 一定距離以上X軸が離れていればそのオブジェクト同士で判定はとらない

static std::deque<CollisionState> deqState;			// コライダ情報の保存用
static unsigned int curRegisterNum;					// 個別の登録番号
static COLL_CALC_ST saveState[MAX_SAVE_TRANS_STATE];// サーチした際の保存用
static int saveNum;									// いくつ保存したか
static CollCalcNum calcNum;							// GetCalcNum用

// 中身をすべて初期化
void ResetCollisionDeque() {
	for (unsigned int i = 0; i < deqState.size(); i++) {
		deqState.erase(deqState.begin() + i);
	}

}

Collision::Collision() {

}

// デストラクタ呼び出し時に個別番号で検索して自身を削除
Collision::~Collision() {
	for (unsigned int i = 0; i < deqState.size(); i++) {
		if (deqState[i].collNum == collRegisterNum) {
			deqState.erase(deqState.begin() + i);
		}
	}		
}

// コライダの登録
void Collision::Register(Transform *transform,TagName paramTagName,CollisionType collType) {
	collRegisterNum = curRegisterNum;
	curRegisterNum++;
	pCollTrans = transform;
	rigid.Init(pCollTrans);
	type = collType;
	tagName = paramTagName;
	GetCalcNum();

	deqState.emplace_back(transform, tagName,collRegisterNum,collType,notCollideTag,&editColl);
	for (int i = 0; i < MAX_NOTCOLL_NUM; i++) {
		notCollideTag[i] = TAG_MAX;
	}
}

//　計算用の値取得
CollCalcNum Collision::GetCalcNum() {
	calcNum.leftX	= pCollTrans->pos.x - pCollTrans->size.x / 2	+ editColl.left;
	calcNum.rightX	= pCollTrans->pos.x + pCollTrans->size.x / 2	+ editColl.right;
	calcNum.upY		= pCollTrans->pos.y - pCollTrans->size.y / 2	+ editColl.top;
	calcNum.downY	= pCollTrans->pos.y + pCollTrans->size.y / 2	+ editColl.bottom;
	calcNum.centerX = pCollTrans->pos.x								/*+ editColl.pos.x*/;	// バグのため調整は未使用
	calcNum.centerY = pCollTrans->pos.y								/*+ editColl.pos.y*/;
	calcNum.radiusX = pCollTrans->size.x / 2						+ editColl.radius;
	calcNum.radiusY = pCollTrans->size.y / 2						+ editColl.radius;
	calcNum.rotate	= pCollTrans->rotate;
	return calcNum;
}

void Collision::DeleteCollision() {
	for (unsigned int i = 0; i < deqState.size(); i++) {
		if (deqState[i].collNum == collRegisterNum)
			deqState.erase(deqState.begin() + i);
	}
}

// 指定したタグのコライダをすべて取得しその配列の先頭アドレスを返す
// コンテナを使った方がいいかも
COLL_CALC_ST* Collision::SeachState(TagName tagName) {
	saveNum = 0;

	for (unsigned int i = 0; i < deqState.size(); i++) {
		if (deqState[i].tagName == tagName && deqState[i].enable) {
			if (NOT_COLLIDE_DIST < abs(deqState[i].CalcPosNum().centerX - GetCalcNum().centerX)) continue;	// 双方が離れていれば判定しない
			// データをreturn用の構造体へ
			saveState[saveNum].num = deqState[i].CalcPosNum();
			saveState[saveNum].type = deqState[i].type;
			saveState[saveNum].trigger = deqState[i].trigger;
			saveState[saveNum].tag = deqState[i].tagName;
			for (int j = 0; j < MAX_NOTCOLL_NUM; j++) {		// 当たらないコライダコピー
				saveState[saveNum].notCollideTag[j] = deqState[i].notCollideTag[j];
			}

			saveNum++;
		}

	}
	return 	saveState;
}

// タグの変更
void Collision::SetTag(TagName tagName) {
	for (unsigned int i = 0; i < deqState.size(); i++) {
		if (deqState[i].collNum == collRegisterNum) {
			deqState[i].tagName = tagName;
		}
	}
}

// 有効化
void Collision::SetEnable(bool enable) {
	for (unsigned int i = 0; i < deqState.size(); i++) {
		if (deqState[i].collNum == collRegisterNum) {
			deqState[i].enable = enable;
		}
	}
}

// 貫通するかどうか
void Collision::SetTrigger(bool trigger) {
	for (unsigned int i = 0; i < deqState.size(); i++) {
		if (deqState[i].collNum == collRegisterNum) {
			deqState[i].trigger = trigger;
		}
	}
}


// 衝突判定
bool Collision::OnCollide(TagName targetTag) {

	COLL_CALC_ST *collCalc = SeachState(targetTag);
	bool returnNum = false;

	// 登録してないほうの(本体)構造体を作って渡す
	COLL_CALC_ST baseCollCalc;
	baseCollCalc.num = GetCalcNum();
	baseCollCalc.trigger = trigger;
	baseCollCalc.tag = tagName;
	for (int i = 0; i < MAX_NOTCOLL_NUM; i++) {
		baseCollCalc.notCollideTag[i] = notCollideTag[i];
	}

	//char str[256];
	//int a = (int)target.size.x;
	//wsprintf(str, "num:%d\n",a);
	//MessageBox(NULL, str, "tex", MB_OK);
	
	// コライダのタイプによって振り分ける
	for (int i = 0; i < saveNum; i++) {
		if (collCalc[i].type == C_TYPE_SQUARE && type == C_TYPE_SQUARE) {	// 四角同士
			if (Square(&collCalc[i])) returnNum = true;
		}
		if (collCalc[i].type == C_TYPE_CIRCLE && type == C_TYPE_CIRCLE) {	// 円同士
			if (Circle(&collCalc[i])) returnNum = true;
		}
		if (collCalc[i].type == C_TYPE_CIRCLE && type == C_TYPE_SQUARE) {	// 本体が四角、相手が丸
			if (SquareCircle(&baseCollCalc,&collCalc[i])) returnNum = true;
			baseCollCalc.num = GetCalcNum();		// バク防止、値を更新
		}
		if (collCalc[i].type == C_TYPE_SQUARE && type == C_TYPE_CIRCLE) {	// 上の逆
			if (SquareCircle(&collCalc[i],&baseCollCalc)) returnNum = true;
			else returnNum = false;
			baseCollCalc.num = GetCalcNum();		// バク防止、値を更新
		}


	}


	return returnNum;
}

LINEPOINT CalcPointRotate(float ptX,float ptY,float cpX,float cpY ,float deg) {
	LINEPOINT point;


	point.x = (cpX - ptX)*cosf(D3DXToRadian(deg)) - (cpY - ptY)*sinf(D3DXToRadian(deg)) + cpX;
	point.y = (cpX - ptX)*sinf(D3DXToRadian(deg)) + (cpY - ptY)*cosf(D3DXToRadian(deg)) + cpY;
	//point.x = ptX;
	//point.y = ptY;

	return point;
}

// そのラインが交差してるか
bool Collision::LineCollide(LINEPOINT pointA,LINEPOINT pointB ,LINEPOINT targetA,LINEPOINT targetB) {

	float lineA;
	float lineB;
	lineA = (pointA.x - pointB.x)*(targetA.y - pointA.y) + (pointA.y - pointB.y)*(pointA.x - targetA.x);
	lineB = (pointA.x - pointB.x)*(targetB.y - pointA.y) + (pointA.y - pointB.y)*(pointA.x - targetB.x);

	if (lineA * lineB < 0 || lineA == 0 || lineB == 0)
		return true;
	else
		return false;

}


bool Collision::Square(COLL_CALC_ST *collCalc) {
	//if (GetCalcNum().leftX   < collCalc->num.rightX  && GetCalcNum().rightX > collCalc->num.leftX
	//	&& GetCalcNum().upY < collCalc->num.downY && GetCalcNum().downY > collCalc->num.upY) {

	//	return true;
	//}

	// (vx2-vx1)*(yp-vy1) - (xp-vx1)*(vy2-vy1)
	LINEPOINT point[4];
	LINEPOINT target[4];
	

	// rotateが0の時、左上から時計回りに。角度計算してから構造体へ
	point[0] = CalcPointRotate(GetCalcNum().leftX, GetCalcNum().upY, GetCalcNum().centerX, GetCalcNum().centerY, pCollTrans->rotate);
	point[1] = CalcPointRotate(GetCalcNum().rightX, GetCalcNum().upY, GetCalcNum().centerX, GetCalcNum().centerY, pCollTrans->rotate);
	point[2] = CalcPointRotate(GetCalcNum().rightX, GetCalcNum().downY, GetCalcNum().centerX, GetCalcNum().centerY, pCollTrans->rotate);
	point[3] = CalcPointRotate(GetCalcNum().leftX, GetCalcNum().downY, GetCalcNum().centerX, GetCalcNum().centerY, pCollTrans->rotate);

	target[0] = CalcPointRotate(collCalc->num.leftX, collCalc->num.upY, collCalc->num.centerX, collCalc->num.centerY, collCalc->num.rotate);
	target[1] = CalcPointRotate(collCalc->num.rightX, collCalc->num.upY, collCalc->num.centerX, collCalc->num.centerY, collCalc->num.rotate);
	target[2] = CalcPointRotate(collCalc->num.rightX, collCalc->num.downY, collCalc->num.centerX, collCalc->num.centerY, collCalc->num.rotate);
	target[3] = CalcPointRotate(collCalc->num.leftX, collCalc->num.downY, collCalc->num.centerX, collCalc->num.centerY, collCalc->num.rotate);
	
	bool resultA, resultB;

	// 判定をとる矩形
	for (int loopP = 0; loopP < 4; loopP++) {
		int loopNeP = 0;
		loopNeP = loopP + 1;
		if (3 < loopNeP)loopNeP = 0;

		// 当たる相手
		for (int loopT = 0; loopT < 4; loopT++) {
			int loopNeT = 0;
			loopNeT = loopT + 1;
			if (3 < loopNeT)loopNeT = 0;

			resultA = LineCollide(point[loopP], point[loopNeP], target[loopT], target[loopNeT]);
			resultB = LineCollide(target[loopT], target[loopNeT],point[loopP], point[loopNeP]);

			if (resultA && resultB) {
				//if (!trigger || !collCalc->trigger) rigid.OnCollide();

				return true;
			}
		}
	}

		
	return false;
}


bool Collision::Circle(COLL_CALC_ST *collCalc) {
	
	if ((GetCalcNum().centerX - collCalc->num.centerX) * (GetCalcNum().centerX - collCalc->num.centerX)
		+ (GetCalcNum().centerY - collCalc->num.centerY) * (GetCalcNum().centerY - collCalc->num.centerY)
		 <= (GetCalcNum().radiusX + collCalc->num.radiusX) * (GetCalcNum().radiusX + collCalc->num.radiusX)) {

		D3DXVECTOR2 baseCircle;		
		D3DXVECTOR2 targetCircle;	// 相手

		baseCircle.x = GetCalcNum().centerX;
		baseCircle.y = GetCalcNum().centerY;
		targetCircle.x = collCalc->num.centerX;
		targetCircle.y = collCalc->num.centerY;

		if((!trigger && !collCalc->trigger) &&	
			(!CheckNotCollideTag(notCollideTag,collCalc->tag) && !CheckNotCollideTag(collCalc->notCollideTag,tagName)))			// お互いに貫通を拒否しているかの確認
			rigid.OnCollideCircle(baseCircle, GetCalcNum().radiusX, targetCircle, collCalc->num.radiusX);

		return true;
	}

	return false;
}


bool Collision::SquareCircle(COLL_CALC_ST *pSquare,COLL_CALC_ST *pCircle) {
	// 
	LINEPOINT target[4];

	target[0] = CalcPointRotate(pSquare->num.leftX, pSquare->num.upY, pSquare->num.centerX, pSquare->num.centerY, pSquare->num.rotate);
	target[1] = CalcPointRotate(pSquare->num.rightX, pSquare->num.upY, pSquare->num.centerX, pSquare->num.centerY, pSquare->num.rotate);
	target[2] = CalcPointRotate(pSquare->num.rightX, pSquare->num.downY, pSquare->num.centerX, pSquare->num.centerY, pSquare->num.rotate);
	target[3] = CalcPointRotate(pSquare->num.leftX, pSquare->num.downY, pSquare->num.centerX, pSquare->num.centerY, pSquare->num.rotate);
	
	// 

	//vecAP_Len = sqrtf((pCircle->num.centerX - target[0].x)*(pCircle->num.centerX - target[0].x) + (pCircle->num.centerY - target[0].y)*(pCircle->num.centerY - target[0].y));

	///////////////////
	//axLen = ap * inn * ab / abs(ab)
	D3DXVECTOR2 normVecAP, normVecAB, normVecBP;
	D3DXVECTOR2 vecAP;
	D3DXVECTOR2 vecAB;
	D3DXVECTOR2 vecBP;
	float vecAP_Len, vecAB_Len, vecBP_Len;
	D3DXVECTOR2 normAB,normAP;
	float dotAPAB,dotBPAB;
	float clossABAP;
	float distance;

	int nextCnt;	// 常にcnt変数の+1の値になる4になったら0に
	for (int cnt = 0; cnt < 4; cnt++) {
		nextCnt = cnt + 1;
		if (4 <= nextCnt) nextCnt = 0;

		vecAP.x = pCircle->num.centerX - target[cnt].x;
		vecAP.y = pCircle->num.centerY - target[cnt].y;

		vecBP.x = pCircle->num.centerX - target[nextCnt].x;
		vecBP.y = pCircle->num.centerY - target[nextCnt].y;

		vecAB.x = target[nextCnt].x - target[cnt].x;
		vecAB.y = target[nextCnt].y - target[cnt].y;
		
		// 各ベクトルの長さ
		vecAP_Len = sqrtf(vecAP.x * vecAP.x + vecAP.y * vecAP.y);
		vecBP_Len = sqrtf(vecBP.x * vecBP.x + vecBP.y * vecBP.y);
		vecAB_Len = sqrtf(vecAB.x * vecAB.x + vecAB.y * vecAB.y);

		clossABAP = abs(vecAB.x * vecAP.y - vecAB.y * vecAP.x);	// 外積
		dotAPAB = D3DXVec2Dot(&vecAB, &vecAP);		// 内積
		dotBPAB = D3DXVec2Dot(&vecAB, &vecBP);		// 内積

		// 線から円の中心までの距離
		distance = abs(clossABAP / vecAB_Len);

		// 
		if (distance <= pCircle->num.radiusX) {
			if (0.0f >= dotAPAB*dotBPAB) {
				// 押し戻しの処理
				if ((!pSquare->trigger && !pCircle->trigger) &&
					(!CheckNotCollideTag(pSquare->notCollideTag, pCircle->tag) && !CheckNotCollideTag(pCircle->notCollideTag, pSquare->tag))) {			// お互いに貫通を拒否しているかの確認
					

					D3DXVECTOR2 circlePos;
					D3DXVECTOR2 targetPos;
					circlePos.x = pCircle->num.centerX;
					circlePos.y = pCircle->num.centerY;
					targetPos.x = target[cnt].x;
					targetPos.y = target[cnt].y;
					rigid.OnCollideSquareCircle(targetPos, vecAB, vecAB_Len, circlePos, pCircle->num.radiusX);

				}
				// 
				return true;
			} else if (pCircle->num.radiusX > abs(vecAP_Len) || pCircle->num.radiusX > abs(vecBP_Len)) {
				
				// 押し戻しの処理
				if ((!pSquare->trigger && !pCircle->trigger) &&	
					(!CheckNotCollideTag(pSquare->notCollideTag, pCircle->tag) && !CheckNotCollideTag(pCircle->notCollideTag, pSquare->tag))) {			// お互いに貫通を拒否しているかの確認

				// まず線分の始点と終点に触れているかを判定
					D3DXVECTOR2 vecPtCircle;	// 円と点のベクトル
					D3DXVECTOR2 tgt;

					vecPtCircle.x = pCircle->num.centerX - target[cnt].x;
					vecPtCircle.y = pCircle->num.centerY - target[cnt].y;
					tgt.x = target[cnt].x;
					tgt.y = target[cnt].y;


					// 円と始点が触れていたら円と点の判定に
					if (vecPtCircle.x * vecPtCircle.x + vecPtCircle.y*vecPtCircle.y < pCircle->num.radiusX*pCircle->num.radiusX) {

						if (rigid.OnCollidePointCircle(vecPtCircle, tgt, pCircle->num.radiusX, vecAB, vecAB_Len)) {
							return true;
						} else { continue; }
					}

					vecPtCircle.x = pCircle->num.centerX - target[nextCnt].x;
					vecPtCircle.y = pCircle->num.centerY - target[nextCnt].y;
					tgt.x = target[nextCnt].x;
					tgt.y = target[nextCnt].y;

					// 円と終点が触れていたら円と点の判定に
					if (vecPtCircle.x * vecPtCircle.x + vecPtCircle.y*vecPtCircle.y < pCircle->num.radiusX*pCircle->num.radiusX) {

						if (rigid.OnCollidePointCircle(vecPtCircle, tgt, pCircle->num.radiusX, vecAB, vecAB_Len)) {
							return true;
						} else { continue; }

					}

					// 頂点に当たっていなかったら線分で判定
					D3DXVECTOR2 circlePos;
					D3DXVECTOR2 targetPos;
					circlePos.x = pCircle->num.centerX;
					circlePos.y = pCircle->num.centerY;
					targetPos.x = target[cnt].x;
					targetPos.y = target[cnt].y;
					rigid.OnCollideSquareCircle(targetPos, vecAB, vecAB_Len, circlePos, pCircle->num.radiusX);

					}
					return true;
			}
		}
	}

	return false;
}

// 一致するタグあったらtrueを返す
// falseなら貫通しないと決めているタグはない→無事衝突する
bool Collision::CheckNotCollideTag(TagName *baseTag, TagName targetTag) {
	for (int k = 0; k < MAX_NOTCOLL_NUM; k++) {
		if (baseTag[k] == 0) continue;	// 0なら入っていないということなのでスキップ
		if (baseTag[k] == targetTag) return true;
	}
	return false;

}

void Collision::SetNotCollideTag(TagName tag) {
	for (int i = 0; i < MAX_NOTCOLL_NUM; i++) {
		if (notCollideTag[i] != TAG_MAX) continue;
		notCollideTag[i] = tag;
	}
}

void Collision::DeleteNotCollideTag(TagName tag) {
	for (int i = 0; i < MAX_NOTCOLL_NUM; i++) {
		if (notCollideTag[i] != tag) continue;
		notCollideTag[i] = TAG_MAX;	// ０を入れて無に
	}
}



