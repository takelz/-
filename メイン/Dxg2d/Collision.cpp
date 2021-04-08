

#include"Collision.h"
#include"input.h"
#include<deque>


#define MAX_SAVE_TRANS_STATE (1024)

#define NOT_COLLIDE_DIST (SCREEN_WIDTH + 100)	// ��苗���ȏ�X��������Ă���΂��̃I�u�W�F�N�g���m�Ŕ���͂Ƃ�Ȃ�

static std::deque<CollisionState> deqState;			// �R���C�_���̕ۑ��p
static unsigned int curRegisterNum;					// �ʂ̓o�^�ԍ�
static COLL_CALC_ST saveState[MAX_SAVE_TRANS_STATE];// �T�[�`�����ۂ̕ۑ��p
static int saveNum;									// �����ۑ�������
static CollCalcNum calcNum;							// GetCalcNum�p

// ���g�����ׂď�����
void ResetCollisionDeque() {
	for (unsigned int i = 0; i < deqState.size(); i++) {
		deqState.erase(deqState.begin() + i);
	}

}

Collision::Collision() {

}

// �f�X�g���N�^�Ăяo�����Ɍʔԍ��Ō������Ď��g���폜
Collision::~Collision() {
	for (unsigned int i = 0; i < deqState.size(); i++) {
		if (deqState[i].collNum == collRegisterNum) {
			deqState.erase(deqState.begin() + i);
		}
	}		
}

// �R���C�_�̓o�^
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

//�@�v�Z�p�̒l�擾
CollCalcNum Collision::GetCalcNum() {
	calcNum.leftX	= pCollTrans->pos.x - pCollTrans->size.x / 2	+ editColl.left;
	calcNum.rightX	= pCollTrans->pos.x + pCollTrans->size.x / 2	+ editColl.right;
	calcNum.upY		= pCollTrans->pos.y - pCollTrans->size.y / 2	+ editColl.top;
	calcNum.downY	= pCollTrans->pos.y + pCollTrans->size.y / 2	+ editColl.bottom;
	calcNum.centerX = pCollTrans->pos.x								/*+ editColl.pos.x*/;	// �o�O�̂��ߒ����͖��g�p
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

// �w�肵���^�O�̃R���C�_�����ׂĎ擾�����̔z��̐擪�A�h���X��Ԃ�
// �R���e�i���g����������������
COLL_CALC_ST* Collision::SeachState(TagName tagName) {
	saveNum = 0;

	for (unsigned int i = 0; i < deqState.size(); i++) {
		if (deqState[i].tagName == tagName && deqState[i].enable) {
			if (NOT_COLLIDE_DIST < abs(deqState[i].CalcPosNum().centerX - GetCalcNum().centerX)) continue;	// �o��������Ă���Δ��肵�Ȃ�
			// �f�[�^��return�p�̍\���̂�
			saveState[saveNum].num = deqState[i].CalcPosNum();
			saveState[saveNum].type = deqState[i].type;
			saveState[saveNum].trigger = deqState[i].trigger;
			saveState[saveNum].tag = deqState[i].tagName;
			for (int j = 0; j < MAX_NOTCOLL_NUM; j++) {		// ������Ȃ��R���C�_�R�s�[
				saveState[saveNum].notCollideTag[j] = deqState[i].notCollideTag[j];
			}

			saveNum++;
		}

	}
	return 	saveState;
}

// �^�O�̕ύX
void Collision::SetTag(TagName tagName) {
	for (unsigned int i = 0; i < deqState.size(); i++) {
		if (deqState[i].collNum == collRegisterNum) {
			deqState[i].tagName = tagName;
		}
	}
}

// �L����
void Collision::SetEnable(bool enable) {
	for (unsigned int i = 0; i < deqState.size(); i++) {
		if (deqState[i].collNum == collRegisterNum) {
			deqState[i].enable = enable;
		}
	}
}

// �ђʂ��邩�ǂ���
void Collision::SetTrigger(bool trigger) {
	for (unsigned int i = 0; i < deqState.size(); i++) {
		if (deqState[i].collNum == collRegisterNum) {
			deqState[i].trigger = trigger;
		}
	}
}


// �Փ˔���
bool Collision::OnCollide(TagName targetTag) {

	COLL_CALC_ST *collCalc = SeachState(targetTag);
	bool returnNum = false;

	// �o�^���ĂȂ��ق���(�{��)�\���̂�����ēn��
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
	
	// �R���C�_�̃^�C�v�ɂ���ĐU�蕪����
	for (int i = 0; i < saveNum; i++) {
		if (collCalc[i].type == C_TYPE_SQUARE && type == C_TYPE_SQUARE) {	// �l�p���m
			if (Square(&collCalc[i])) returnNum = true;
		}
		if (collCalc[i].type == C_TYPE_CIRCLE && type == C_TYPE_CIRCLE) {	// �~���m
			if (Circle(&collCalc[i])) returnNum = true;
		}
		if (collCalc[i].type == C_TYPE_CIRCLE && type == C_TYPE_SQUARE) {	// �{�̂��l�p�A���肪��
			if (SquareCircle(&baseCollCalc,&collCalc[i])) returnNum = true;
			baseCollCalc.num = GetCalcNum();		// �o�N�h�~�A�l���X�V
		}
		if (collCalc[i].type == C_TYPE_SQUARE && type == C_TYPE_CIRCLE) {	// ��̋t
			if (SquareCircle(&collCalc[i],&baseCollCalc)) returnNum = true;
			else returnNum = false;
			baseCollCalc.num = GetCalcNum();		// �o�N�h�~�A�l���X�V
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

// ���̃��C�����������Ă邩
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
	

	// rotate��0�̎��A���ォ�玞�v���ɁB�p�x�v�Z���Ă���\���̂�
	point[0] = CalcPointRotate(GetCalcNum().leftX, GetCalcNum().upY, GetCalcNum().centerX, GetCalcNum().centerY, pCollTrans->rotate);
	point[1] = CalcPointRotate(GetCalcNum().rightX, GetCalcNum().upY, GetCalcNum().centerX, GetCalcNum().centerY, pCollTrans->rotate);
	point[2] = CalcPointRotate(GetCalcNum().rightX, GetCalcNum().downY, GetCalcNum().centerX, GetCalcNum().centerY, pCollTrans->rotate);
	point[3] = CalcPointRotate(GetCalcNum().leftX, GetCalcNum().downY, GetCalcNum().centerX, GetCalcNum().centerY, pCollTrans->rotate);

	target[0] = CalcPointRotate(collCalc->num.leftX, collCalc->num.upY, collCalc->num.centerX, collCalc->num.centerY, collCalc->num.rotate);
	target[1] = CalcPointRotate(collCalc->num.rightX, collCalc->num.upY, collCalc->num.centerX, collCalc->num.centerY, collCalc->num.rotate);
	target[2] = CalcPointRotate(collCalc->num.rightX, collCalc->num.downY, collCalc->num.centerX, collCalc->num.centerY, collCalc->num.rotate);
	target[3] = CalcPointRotate(collCalc->num.leftX, collCalc->num.downY, collCalc->num.centerX, collCalc->num.centerY, collCalc->num.rotate);
	
	bool resultA, resultB;

	// ������Ƃ��`
	for (int loopP = 0; loopP < 4; loopP++) {
		int loopNeP = 0;
		loopNeP = loopP + 1;
		if (3 < loopNeP)loopNeP = 0;

		// �����鑊��
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
		D3DXVECTOR2 targetCircle;	// ����

		baseCircle.x = GetCalcNum().centerX;
		baseCircle.y = GetCalcNum().centerY;
		targetCircle.x = collCalc->num.centerX;
		targetCircle.y = collCalc->num.centerY;

		if((!trigger && !collCalc->trigger) &&	
			(!CheckNotCollideTag(notCollideTag,collCalc->tag) && !CheckNotCollideTag(collCalc->notCollideTag,tagName)))			// ���݂��Ɋђʂ����ۂ��Ă��邩�̊m�F
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

	int nextCnt;	// ���cnt�ϐ���+1�̒l�ɂȂ�4�ɂȂ�����0��
	for (int cnt = 0; cnt < 4; cnt++) {
		nextCnt = cnt + 1;
		if (4 <= nextCnt) nextCnt = 0;

		vecAP.x = pCircle->num.centerX - target[cnt].x;
		vecAP.y = pCircle->num.centerY - target[cnt].y;

		vecBP.x = pCircle->num.centerX - target[nextCnt].x;
		vecBP.y = pCircle->num.centerY - target[nextCnt].y;

		vecAB.x = target[nextCnt].x - target[cnt].x;
		vecAB.y = target[nextCnt].y - target[cnt].y;
		
		// �e�x�N�g���̒���
		vecAP_Len = sqrtf(vecAP.x * vecAP.x + vecAP.y * vecAP.y);
		vecBP_Len = sqrtf(vecBP.x * vecBP.x + vecBP.y * vecBP.y);
		vecAB_Len = sqrtf(vecAB.x * vecAB.x + vecAB.y * vecAB.y);

		clossABAP = abs(vecAB.x * vecAP.y - vecAB.y * vecAP.x);	// �O��
		dotAPAB = D3DXVec2Dot(&vecAB, &vecAP);		// ����
		dotBPAB = D3DXVec2Dot(&vecAB, &vecBP);		// ����

		// ������~�̒��S�܂ł̋���
		distance = abs(clossABAP / vecAB_Len);

		// 
		if (distance <= pCircle->num.radiusX) {
			if (0.0f >= dotAPAB*dotBPAB) {
				// �����߂��̏���
				if ((!pSquare->trigger && !pCircle->trigger) &&
					(!CheckNotCollideTag(pSquare->notCollideTag, pCircle->tag) && !CheckNotCollideTag(pCircle->notCollideTag, pSquare->tag))) {			// ���݂��Ɋђʂ����ۂ��Ă��邩�̊m�F
					

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
				
				// �����߂��̏���
				if ((!pSquare->trigger && !pCircle->trigger) &&	
					(!CheckNotCollideTag(pSquare->notCollideTag, pCircle->tag) && !CheckNotCollideTag(pCircle->notCollideTag, pSquare->tag))) {			// ���݂��Ɋђʂ����ۂ��Ă��邩�̊m�F

				// �܂������̎n�_�ƏI�_�ɐG��Ă��邩�𔻒�
					D3DXVECTOR2 vecPtCircle;	// �~�Ɠ_�̃x�N�g��
					D3DXVECTOR2 tgt;

					vecPtCircle.x = pCircle->num.centerX - target[cnt].x;
					vecPtCircle.y = pCircle->num.centerY - target[cnt].y;
					tgt.x = target[cnt].x;
					tgt.y = target[cnt].y;


					// �~�Ǝn�_���G��Ă�����~�Ɠ_�̔����
					if (vecPtCircle.x * vecPtCircle.x + vecPtCircle.y*vecPtCircle.y < pCircle->num.radiusX*pCircle->num.radiusX) {

						if (rigid.OnCollidePointCircle(vecPtCircle, tgt, pCircle->num.radiusX, vecAB, vecAB_Len)) {
							return true;
						} else { continue; }
					}

					vecPtCircle.x = pCircle->num.centerX - target[nextCnt].x;
					vecPtCircle.y = pCircle->num.centerY - target[nextCnt].y;
					tgt.x = target[nextCnt].x;
					tgt.y = target[nextCnt].y;

					// �~�ƏI�_���G��Ă�����~�Ɠ_�̔����
					if (vecPtCircle.x * vecPtCircle.x + vecPtCircle.y*vecPtCircle.y < pCircle->num.radiusX*pCircle->num.radiusX) {

						if (rigid.OnCollidePointCircle(vecPtCircle, tgt, pCircle->num.radiusX, vecAB, vecAB_Len)) {
							return true;
						} else { continue; }

					}

					// ���_�ɓ������Ă��Ȃ�����������Ŕ���
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

// ��v����^�O��������true��Ԃ�
// false�Ȃ�ђʂ��Ȃ��ƌ��߂Ă���^�O�͂Ȃ��������Փ˂���
bool Collision::CheckNotCollideTag(TagName *baseTag, TagName targetTag) {
	for (int k = 0; k < MAX_NOTCOLL_NUM; k++) {
		if (baseTag[k] == 0) continue;	// 0�Ȃ�����Ă��Ȃ��Ƃ������ƂȂ̂ŃX�L�b�v
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
		notCollideTag[i] = TAG_MAX;	// �O�����Ė���
	}
}



