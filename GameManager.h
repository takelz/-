#ifndef __GAMEMANAGER__
#define __GAMEMANAGER__

class RANK;

class GameManager {
public:
	static GameManager *Instance() {
		static GameManager gameManager;
		return &gameManager;
	}
	static void Delete() {
		delete Instance();
	}

	void GameUpdate();		// �Q�[���V�[���ł̃A�b�v�f�[�g
	void GetRank(RANK *rank);	// �����N�̃X�R�A��ۑ�


	int currentStage;		// ���݂ǂ̃X�e�[�W���v���C���Ă��邩�A-1�̓Q�[�����ȊO
	int saveScore;			// �N���A���̃X�R�A
	bool isGameOver;
	bool isGameClear;		
	bool faded;

private:

	GameManager(){};
	~GameManager(){};

};


#endif // !__GAMEMANAGER__
