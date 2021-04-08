

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

#define SIZE (80.0f * 0.7f)			// �v���C���[�T�C�Y

#define MOVE_SPEED (1.5f)
#define JUMP_POWER (5.5f)

#define ADJ_COLL_RADIUS (-15.5f)
#define ADJ_COLL_POS_Y (13.0f)
#define ADJ_EFECT_POS_Y (13.0f)

#define MOVE_CAMERA_POSX (100)		// �J�����������o�����S�n���狗��
#define MOVE_CAMERA_POSY (100)
#define MOVE_ADJ_CAMERA_UNDER (75)

#define ATK_SPRITE_SIZE (1.65f)

#define NOT_STOP_TIME (45)			// �U���J�n��ǂꂮ�炢�o����������ł��邩
#define FADE_SPEED (50)				// �S�[����̃t�F�[�h

#define MAX_HP (5)

Player::Player() {

}


void Player::Init() {
	collision.editColl.radius = ADJ_COLL_RADIUS;		// �R���C�_�̑傫���A�ʒu�̒����̓X�v���C�g�𒼐ړ�����
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
	PlayerManager::Instance()->GetAttackedState();	// �U�����󂯂��������Z�b�g

	//�������R���|�[�l���g������
	groundedColl.Init();
	stopGage.Init();
	stopGage.maxGage = NOT_STOP_TIME;
}


void Player::Update() {
	float saveAtkEfectRotate;

	if (!loadedStart) {		// �ŏ��̃��[�v�ŃX�^�[�g�n�_��ǂݍ���
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

	saveAtkEfectRotate = move.AngleVector(collision.rigid.velocity);		// �x�N�g������U���G�t�F�N�g�摜�̊p�x�����߂�


	collision.OnCollide(TAG_GROUND);
	
	PlayerManager::Instance()->playerHP = HP;
	PlayerManager::Instance()->state = state;		
	PlayerManager::Instance()->pos = transform.pos;
	collision.rigid.UpdatePos();

	//�X�v���C�g�A�b�v�f�[�g
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

	//�������R���|�[�l���g������
	groundedColl.AttachChild(&transform, 0,20/2);	// �n�ʂ̔���
	groundedColl.Update();	
	stopGage.currentGage = notStopTime;				// �X�g�b�v�Q�[�W�̃J�E���g	
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

	if (state == PLAYER_ATACK && !PlayerManager::Instance()->attackSuccess) {	// �U������Ԃ��U���ɐ������ăX�g�b�v���Ă��Ȃ��Ƃ�

		atkEfectSprite.size.x *= ATK_SPRITE_SIZE;
		atkEfectSprite.size.y *= ATK_SPRITE_SIZE;
		atkEfectSprite.Draw();
	}
	pCurSprite->Draw();

	groundedColl.Draw();

	if(!PlayerManager::Instance()->attackSuccess)	// �U�������Ȃ�\�����Ȃ�
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

// ��������������������������������������������������������
// ���������������������������ړ���������������������������

void Player::MovePos() {
	if (state == PLAYER_ATACK || PlayerManager::Instance()->attackSuccess) return;		// �U�����Ȃ�ړ��̓��͂��󂯕t���Ȃ�
	
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

	if ((DIGetKeyTrigger(DIK_W))&& !groundedColl.isJumped) {		// �{�^�����A�W�����v�t���O������Ă��Ȃ��Ȃ�
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

// ��������������������������������������������������������
// �������������������������_���[�W������������������������

void Player::Damaged() {
	const int INVISIBLE_TIME = 90;
	
	D3DXVECTOR2 knockBack;

	// �_���[�W����Ɠ����Ƀm�b�N�o�b�N�̒l���擾
	if (PlayerManager::Instance()->GetAttackedState(&knockBack) && !isDamaged) {
		isDamaged = true;
		HP -= 1;	
		state = PLAYER_DAMAGED;
		PlaySound(SOUND_DAMAGE);
	}

	if (!isDamaged) return;		// �_���[�W�󂯂ĂȂ��Ȃ炱�̐揈�����Ȃ�
	
	// �_���[�W�I������
	if (StopTime(&invisibleCnt, INVISIBLE_TIME)) {
		if (state != PLAYER_ATACK) {	// �o�O�h�~
			state = PLAYER_NORMAL;
		}
		isDamaged = false;
	}

	// �v���C���[�����񂾏ꍇ
	if (HP <= 0) {
		GameManager::Instance()->isGameOver = true;
		state = PLAYER_NORMAL;
	}
	
}




// ��������������������������������������������������������
// �������������������������󒆍U��������������������������


void Player::RushAttack() {
	D3DXVECTOR2 rushDirection;	// �L�[���͂ɂ���ĕ����w��
	D3DXVECTOR2 playerScrPos;	// �v���C���[�̃X�N���[�����W
	POINT lpPoint;

	rushDirection.x = rushDirection.y = 0.0f;

	// �}�E�X���W�擾
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
		// �W�����v
		if (DIGetKeyTrigger(DIK_W) || DIGetMouseTrigger(DIK_RIGHT_CLICK)) {		//
			if (notStopTime < 0) {					
				collision.rigid.velocity.y = -5.0f;
				isJumped = true;
			}
		}

	}
	if (0 <= notStopTime)notStopTime--;

	EndRush();		// �ˌ��̏I������

}

void Player::Rush(D3DXVECTOR2 normDir) {
	const float SPEED = 8.0f;

	collision.rigid.velocity.x = normDir.x * SPEED;
	collision.rigid.velocity.y = normDir.y * SPEED;

	collision.rigid.useGravity = false;
	collision.rigid.useReflect = true;

	rushTimeCnt = 0;	// �J�E���^�����Z�b�g���Ă���
	stopCnt = 0;
	notStopTime = NOT_STOP_TIME;

	state = PLAYER_ATACK;
	PlaySound(SOUND_ATTACKSTART);
	//PlayerManager::Instance()->CountUpRush();	// �ˌ��񐔃J�E���g
}


void Player::NextRush(D3DXVECTOR2 direction) {
	const int END_TIME = 90;

	if (!PlayerManager::Instance()->attackSuccess) return;	// �U���ɐ��������Ȃ玟��

	collision.rigid.ResetVelocity();	// �G�ɓ��������瑬�x��0��
	
	if (DIGetMouseTrigger(DIK_LEFT_CLICK)) {
		Rush(direction);		// �ːi
		PlayerManager::Instance()->attackSuccess = false;
		rushTimeCnt = 0;		// �J�E���^�����Z�b�g���Ă���
		stopCnt = 0;
	}
	if (StopTime(&stopCnt, END_TIME)){		// �J�E���g���ԏI�������I��
		PlayerManager::Instance()->attackSuccess = false;
		state = PLAYER_NORMAL;
		PlayerManager::Instance()->ResetRushCount();
		collision.rigid.velocity.y = 0.0f;
		collision.rigid.useReflect = false;
		collision.rigid.useGravity = true;
	}
}


void Player::EndRush() {
	const int END_TIME = 600;	// 600�t���[���Œ�~

		if(state == PLAYER_NORMAL) return;

	if (StopTime(&rushTimeCnt, END_TIME) || state == PLAYER_DAMAGED || isJumped) {

		state = PLAYER_NORMAL;
		if (!isJumped) collision.rigid.velocity.y = 0.0f;	// �W�����v�Ŏ~�߂��Ȃ瑬�x��0�ɂ��Ȃ�
		collision.rigid.useReflect = false;
		collision.rigid.useGravity = true;
		isJumped = false;
		PlayerManager::Instance()->attackSuccess = false;
		PlayerManager::Instance()->ResetRushCount();

	}
}


//����������Gage�N���X����������

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









/*�}�E�X
	//POINT lpPoint;

	//GetCursorPos(&lpPoint);
	//ScreenToClient(GetHwnd(), &lpPoint);
*/