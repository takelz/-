
#include"CollisionState.h"


CollisionState::CollisionState() {
	enable = false;
}

CollisionState::CollisionState(Transform *paramTransform, TagName paramTagName, int registerNum,CollisionType paramType,TagName *notCollArray, EDITCOLLIDER *editColl) {
	pTransform = paramTransform;
	tagName = paramTagName;
	collNum = registerNum;
	type = paramType;
	editCollider = editColl;

	for (int i = 0; i < MAX_NOTCOLL_NUM; i++) {	 // 配列コピー
		notCollideTag = notCollArray;
	}
	trigger = false;
	enable = true;
}

CollCalcNum CollisionState::CalcPosNum() {
	cPos.leftX	= pTransform->pos.x - pTransform->size.x / 2	+ editCollider->left;
	cPos.rightX = pTransform->pos.x + pTransform->size.x / 2	+ editCollider->right;
	cPos.upY	= pTransform->pos.y - pTransform->size.y / 2	+ editCollider->top;
	cPos.downY	= pTransform->pos.y + pTransform->size.y / 2	+ editCollider->bottom;
	cPos.centerX = pTransform->pos.x							/*+ editCollider->pos.x*/;
	cPos.centerY = pTransform->pos.y							/*+ editCollider->pos.y*/;
	cPos.radiusX = pTransform->size.x / 2						+ editCollider->radius;
	cPos.radiusY = pTransform->size.y / 2						+ editCollider->radius;
	cPos.rotate = pTransform->rotate;
	
	return cPos;
}
