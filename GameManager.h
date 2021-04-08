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

	void GameUpdate();		// ゲームシーンでのアップデート
	void GetRank(RANK *rank);	// ランクのスコアを保存


	int currentStage;		// 現在どのステージをプレイしているか、-1はゲーム中以外
	int saveScore;			// クリア時のスコア
	bool isGameOver;
	bool isGameClear;		
	bool faded;

private:

	GameManager(){};
	~GameManager(){};

};


#endif // !__GAMEMANAGER__
