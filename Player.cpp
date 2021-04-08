

#include"Player.h"
#include"Dxg2d\input.h"
#include"Dxg2d\Camera.h"
#include"Dxg2d\sound.h"
#include"SceneManager.h"
#include"GameManager.h"

#define	MOVE_FILE "data/texture/player/playermove2.png"
#define IDOL_FILE "data/texture/player/playeridol.png"
#define ATK_FILE "data/texture/player/player_atk.png"
#define ATKEFECT_FILE "data/texture/player/player_atkefect.png"
#define U (4)
#define V (4)

#define GAGE_FILE "data/texture/square.bmp"

#define SIZE (80.0f * 0.7f)			// プレイヤーサイズ

#define MOVE_SPEED (1.5f)
#define JUMP_POWER (5.5f)

#define ADJ_COLL_RADIUS (-15.5f)
#define ADJ_COLL_POS_Y (13.0f)
#define ADJ_EFECT_POS_Y (13.0f)

#define MOVE_CAMERA_POSX (100)		// カメラが動き出す中心地から距離
#define MOVE_CAMERA_POSY (100)
#define MOVE_ADJ_CAMERA_UNDER (75)

#define ATK_SPRITE_SIZE (1.65f)

#define NOT_STOP_TIME (45)			// 攻撃開始後どれぐらい経ったら解除できるか
#define FADE_SPEED (50)				// ゴール後のフェード

#define MAX_HP (5)

Player::Player() {

}


void Player::Init() {
	collision.editColl.radius = ADJ_COLL_RADIUS;		// コライダの大きさ、位置の調整はスプライトを直接動かす
	collision.Register(&transform, TAG_PLAYER, C_TYPE_CIRCLE);
	collision.trigger = false;
	collision.rigid.useGravity = true;
	//collision.SetNotCollideTag(TAG_ENEMY)

	sprite.Load(IDOL_FILE, 12, U, V);
	moveSprite.Load(MOVE_FILE, 2, U, V);
	atkSprite.Load(ATK_FILE);
	atkEfectSprite.Load(ATKEFECT_FILE);
	sprite.useAnim = true;
	moveSprite.useAnim = true;

	transform.size.y = transform.size.x = SIZE;
	loadedStart = false;
	
	state = PLAYER_NORMAL;
	spriteNum = PLAYER_SPRITE_IDOL;
	PlayerManager::Instance()->attackSuccess = false;
	PlayerManager::Instance()->ResetRushCount();

	HP = MAX_HP;
	PlayerManager::Instance()->GetAttackedState();	// 攻撃を受けた情報をリセット

	//＝＝＝コンポーネント＝＝＝
	groundedColl.Init();
	stopGage.Init();
	stopGage.maxGage = NOT_STOP_TIME;
}


void Player::Update() {
	float saveAtkEfectRotate;

	if (!loadedStart) {		// 最初のループでスタート地点を読み込む
		transform.pos = PlayerManager::Instance()->startPos;
		loadedStart = true;
	}
	SelectSprite();

	MovePos();
	RushAttack();
	Damaged();

	hookShot.Hook(transform.pos, &collision.rigid.velocity);	

	if (isDamaged) pCurSprite->color.a = 128;
	else pCurSprite->color.a = 255;

	saveAtkEfectRotate = move.AngleVector(collision.rigid.velocity);		// ベクトルから攻撃エフェクト画像の角度を決める


	collision.OnCollide(TAG_GROUND);
	
	PlayerManager::Instance()->playerHP = HP;
	PlayerManager::Instance()->state = state;		
	PlayerManager::Instance()->pos = transform.pos;
	collision.rigid.UpdatePos();

	//スプライトアップデート
	transform.TransformToSprite(pCurSprite);
	transform.TransformToSprite(&atkEfectSprite);
	pCurSprite->pos.y -= ADJ_COLL_POS_Y;
	pCurSprite->Update();

	atkEfectSprite.rotate = saveAtkEfectRotate;
	atkEfectSprite.Update();

	if (GameManager::Instance()->isGameClear) {
		state = PLAYER_NORMAL; 
		pCurSprite->color.a = 0;
	} else {
		FollowCamera();
	}

	//＝＝＝コンポーネント＝＝＝
	groundedColl.AttachChild(&transform, 0,20/2);	// 地面の判定
	groundedColl.Update();	
	stopGage.currentGage = notStopTime;				// ストップゲージのカウント	
	stopGage.AttachChild(&transform, 0, -SIZE + 12);
	stopGage.Update();
}

void Player::EditUpdate() {
	int acc  = 0;
	if (DIGetKey(DIK_SPACE)) {
		acc = 3;
	}
	
	if (DIGetKey(DIK_A)) {
		Camera::Instance()->pos.x += 3 + acc;
	}
	if (DIGetKey(DIK_D)) {
		Camera::Instance()->pos.x -= 3 + acc;
	}
	if (DIGetKey(DIK_W)) {
		Camera::Instance()->pos.y += 3 + acc;
	}
	if (DIGetKey(DIK_S)) {
		Camera::Instance()->pos.y -= 3 + acc;
	}
	pCurSprite = &sprite;

	edit.EditObject(&transform, NULL, MANAGER_PLAYER, 0);
	transform.TransformToSprite(&sprite);
	sprite.Update();
}


void Player::Draw() {

	if (state == PLAYER_ATACK && !PlayerManager::Instance()->attackSuccess) {	// 攻撃中状態かつ攻撃に成功してストップしていないとき

		atkEfectSprite.size.x *= ATK_SPRITE_SIZE;
		atkEfectSprite.size.y *= ATK_SPRITE_SIZE;
		atkEfectSprite.Draw();
	}
	pCurSprite->Draw();

	groundedColl.Draw();

	if(!PlayerManager::Instance()->attackSuccess)	// 攻撃成功なら表示しない
		stopGage.Draw();
}

void Player::FollowCamera() {

	if (Camera::Instance()->pos.x + transform.pos.x < SCREEN_CENTER_X - MOVE_CAMERA_POSX) {
		Camera::Instance()->pos.x = -transform.pos.x + SCREEN_CENTER_X - MOVE_CAMERA_POSX;
	}
	if (Camera::Instance()->pos.x + transform.pos.x > MOVE_CAMERA_POSX + SCREEN_CENTER_X) {
		Camera::Instance()->pos.x = -transform.pos.x + MOVE_CAMERA_POSX + SCREEN_CENTER_X;
	}
	if (Camera::Instance()->pos.y + transform.pos.y < SCREEN_CENTER_Y - MOVE_CAMERA_POSY) {
		Camera::Instance()->pos.y = -transform.pos.y + SCREEN_CENTER_Y - MOVE_CAMERA_POSY;
	}							
	if (Camera::Instance()->pos.y + transform.pos.y > MOVE_CAMERA_POSY + SCREEN_CENTER_Y - MOVE_ADJ_CAMERA_UNDER) {
		Camera::Instance()->pos.y = -transform.pos.y + MOVE_CAMERA_POSY + SCREEN_CENTER_Y - MOVE_ADJ_CAMERA_UNDER;
	}

}

void Player::SelectSprite() {
	if (state == PLAYER_ATACK) spriteNum = PLAYER_SPRITE_ATK;

	switch (spriteNum) {
		case PLAYER_SPRITE_IDOL:
			pCurSprite = &sprite;
			break;
		case PLAYER_SPRITE_MOVE:
			pCurSprite = &moveSprite;
			break;
		case PLAYER_SPRITE_ATK:
			pCurSprite = &atkSprite;
			break;
	}
}

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ＝＝＝＝＝＝＝＝＝＝＝＝＝移動＝＝＝＝＝＝＝＝＝＝＝＝＝

void Player::MovePos() {
	if (state == PLAYER_ATACK || PlayerManager::Instance()->attackSuccess) return;		// 攻撃中なら移動の入力を受け付けない
	
	if (DIGetKey(DIK_A)) {
		collision.rigid.vector.x = -MOVE_SPEED;
		pCurSprite->reverseX = true;
		spriteNum = PLAYER_SPRITE_MOVE;
	} else if (DIGetKey(DIK_D)) {
		collision.rigid.vector.x = MOVE_SPEED;
		pCurSprite->reverseX = false;
		spriteNum = PLAYER_SPRITE_MOVE;
	} else {
		spriteNum = PLAYER_SPRITE_IDOL;
	}

	if ((DIGetKeyTrigger(DIK_W))&& !groundedColl.isJumped) {		// ボタンかつ、ジャンプフラグを消費していないなら
		collision.rigid.velocity.y = -JUMP_POWER;
		groundedColl.isJumped = true;
	}
	if (DIGetKey(DIK_T)) {
		collision.rigid.useReflect = true;
	} else {
		collision.rigid.useReflect = false;
		collision.rigid.velocity.x = 0.0f;
	}

}

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ＝＝＝＝＝＝＝＝＝＝＝＝ダメージ＝＝＝＝＝＝＝＝＝＝＝＝

void Player::Damaged() {
	const int INVISIBLE_TIME = 90;
	
	D3DXVECTOR2 knockBack;

	// ダメージ判定と同時にノックバックの値も取得
	if (PlayerManager::Instance()->GetAttackedState(&knockBack) && !isDamaged) {
		isDamaged = true;
		HP -= 1;	
		state = PLAYER_DAMAGED;
		PlaySound(SOUND_DAMAGE);
	}

	if (!isDamaged) return;		// ダメージ受けてないならこの先処理しない
	
	// ダメージ終了処理
	if (StopTime(&invisibleCnt, INVISIBLE_TIME)) {
		if (state != PLAYER_ATACK) {	// バグ防止
			state = PLAYER_NORMAL;
		}
		isDamaged = false;
	}

	// プレイヤーが死んだ場合
	if (HP <= 0) {
		GameManager::Instance()->isGameOver = true;
		state = PLAYER_NORMAL;
	}
	
}




// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ＝＝＝＝＝＝＝＝＝＝＝＝空中攻撃＝＝＝＝＝＝＝＝＝＝＝＝


void Player::RushAttack() {
	D3DXVECTOR2 rushDirection;	// キー入力によって方向指定
	D3DXVECTOR2 playerScrPos;	// プレイヤーのスクリーン座標
	POINT lpPoint;

	rushDirection.x = rushDirection.y = 0.0f;

	// マウス座標取得
	GetCursorPos(&lpPoint);
	ScreenToClient(GetHwnd(), &lpPoint);

	rushDirection.x = (float)lpPoint.x;
	rushDirection.y = (float)lpPoint.y;

	playerScrPos.x = transform.pos.x + Camera::Instance()->pos.x;
	playerScrPos.y = transform.pos.y + Camera::Instance()->pos.y;

	if (state == PLAYER_NORMAL) {
		if (DIGetMouseTrigger(DIK_LEFT_CLICK)) {
			Rush(move.VectorDirection(playerScrPos, rushDirection));
		}
	}
	if (state == PLAYER_ATACK) {

		NextRush(move.VectorDirection(playerScrPos,rushDirection));
		// ジャンプ
		if (DIGetKeyTrigger(DIK_W) || DIGetMouseTrigger(DIK_RIGHT_CLICK)) {		//
			if (notStopTime < 0) {					
				collision.rigid.velocity.y = -5.0f;
				isJumped = true;
			}
		}

	}
	if (0 <= notStopTime)notStopTime--;

	EndRush();		// 突撃の終了処理

}

void Player::Rush(D3DXVECTOR2 normDir) {
	const float SPEED = 8.0f;

	collision.rigid.velocity.x = normDir.x * SPEED;
	collision.rigid.velocity.y = normDir.y * SPEED;

	collision.rigid.useGravity = false;
	collision.rigid.useReflect = true;

	rushTimeCnt = 0;	// カウンタをリセットしておく
	stopCnt = 0;
	notStopTime = NOT_STOP_TIME;

	state = PLAYER_ATACK;
	PlaySound(SOUND_ATTACKSTART);
	//PlayerManager::Instance()->CountUpRush();	// 突撃回数カウント
}


void Player::NextRush(D3DXVECTOR2 direction) {
	const int END_TIME = 90;

	if (!PlayerManager::Instance()->attackSuccess) return;	// 攻撃に成功したなら次へ

	collision.rigid.ResetVelocity();	// 敵に当たったら速度を0に
	
	if (DIGetMouseTrigger(DIK_LEFT_CLICK)) {
		Rush(direction);		// 突進
		PlayerManager::Instance()->attackSuccess = false;
		rushTimeCnt = 0;		// カウンタをリセットしておく
		stopCnt = 0;
	}
	if (StopTime(&stopCnt, END_TIME)){		// カウント時間終わったら終了
		PlayerManager::Instance()->attackSuccess = false;
		state = PLAYER_NORMAL;
		PlayerManager::Instance()->ResetRushCount();
		collision.rigid.velocity.y = 0.0f;
		collision.rigid.useReflect = false;
		collision.rigid.useGravity = true;
	}
}


void Player::EndRush() {
	const int END_TIME = 600;	// 600フレームで停止

		if(state == PLAYER_NORMAL) return;

	if (StopTime(&rushTimeCnt, END_TIME) || state == PLAYER_DAMAGED || isJumped) {

		state = PLAYER_NORMAL;
		if (!isJumped) collision.rigid.velocity.y = 0.0f;	// ジャンプで止めたなら速度を0にしない
		collision.rigid.useReflect = false;
		collision.rigid.useGravity = true;
		isJumped = false;
		PlayerManager::Instance()->attackSuccess = false;
		PlayerManager::Instance()->ResetRushCount();

	}
}


//＝＝＝＝＝Gageクラス＝＝＝＝＝

void StopTimeGage::Init() {
	const int SIZE_Y = 10;

	sprite.Load(GAGE_FILE);
	transform.size.x = SIZE;
	transform.size.y = SIZE_Y;
}


void StopTimeGage::Update() {
	transform.size.x = SIZE * ((float)currentGage / maxGage);
	transform.TransformToSprite(&sprite);
	sprite.Update();
}


void StopTimeGage::Draw() {
	sprite.Draw();
}









/*マウス
	//POINT lpPoint;

	//GetCursorPos(&lpPoint);
	//ScreenToClient(GetHwnd(), &lpPoint);
*/