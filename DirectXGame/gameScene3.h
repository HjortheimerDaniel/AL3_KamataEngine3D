#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include <vector>
#include "OwnMath.h"
#include "DebugCamera.h"
#include "Skydome.h"
#include "MapChipField.h"
#include "CameraController.h"
#include "Enemy.h"
#include "DeathParticles.h"
#include "Fade.h"
#include "Goal.h"
#include "struct.h"
#include "ClearText.h"
#include "Spikes.h"
#include "ReverseCubes.h"
#include "Checkpoint.h"
#include "Spring.h"

#define NOMINMAX


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene3 {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene3();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene3();

	void PlayerStartPos();

	void PlayerCheckpoint1Pos();

	void PlayerCheckpoint2Pos();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// Collision between player and objects
	/// </summary>
	void CheckAllCollisions();

	bool IsCollision(const AABB& aabb1, const AABB& aabb2);

	bool IsStompCollision(const AABB& aabb1, const AABB& aabb2);

	void IsEnemyCloseToPlayer();

	void ReverseCamera();

	void ChangePhase();

	void MoveCameraHorizontally();

	void StageClearCamera();

	void TransitionScene();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void GenerateBlocks();

	bool GetIsDead() const { return isDead_; };

	bool GetIsFinished() const { return finished_; };

	bool GetStageClear() const { return stageClear_; };

	bool GetCheckpoint2Reached() const { return checkPoint2Reached_; };

	bool GetCheckpoint1Reached() const { return checkPoint1Reached_; };

	bool GetGoToNextStage() const { return goToNextStage_; };

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	uint32_t textureHandle_ = 0;
	uint32_t audioHandle_ = 0;
	uint32_t audioHandle2_ = 0;
	uint32_t audioHandle3_ = 0;
	uint32_t playHandle = {};
	uint32_t playHandle2 = {};
	uint32_t playHandle3 = {};
	Model* playerModel_ = nullptr;
	Model* enemyModel_ = nullptr;
	Model* deathparticleModel_ = nullptr;
	Model* goalModel_ = nullptr;
	Model* clearTextModel_ = nullptr;
	Model* spikeModel_ = nullptr;
	Model* springModel_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	Player* player_ = nullptr;
	Skydome* skydome_ = nullptr;
	Skydome* skydome2_ = nullptr;
	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;
	std::vector<std::vector<WorldTransform*>>worldTransformBlocks_;
	//std::vector<std::vector<WorldTransform*>>worldTransformDeathParticles_;
	Model* modelBlock_ = nullptr;
	Model* modelSkydome_ = nullptr;
	Model* modelSkydome2_ = nullptr;
	MapChipField* mapChipField_ = nullptr;
	MapChipField* mapChipField2_ = nullptr;
	CameraController* cameraController_ = nullptr;
	Rect cameraRange = { 168.0f,28.5f,0.0f,16.0f + 160.0f };
	Enemy* enemy_ = nullptr;
	std::list<Enemy*> enemies_;
	std::list<Spikes*> spikes_;
	std::list<ReverseCubes*> reversedCubes_;
	std::list<Spring*> springs_;
	DeathParticles* deathParticles_ = nullptr;
	Phase phase_;
	ReverseCubes* reverseCube_ = nullptr;
	bool isDead_ = false;
	bool finished_ = false;
	Fade* fade_ = nullptr;
	float duration_ = 1.0f;
	float stompDistance = 0.9f;
	float activateEnemyDistance = 48.0f;
	Goal* goal_ = nullptr;
	bool stageClear_ = false;
	bool goToNextStage_ = false;
	Vector3 goalCameraPos = { 0,0,-40.0f - 160.0f };
	ClearText* stageClearText_ = nullptr;
	static inline const float maxCameraRangeTop = 22.0f + 160.0f;
	static inline const float minCameraRangeTop = 16.0f + 160.0f;
	Spikes* spike_ = nullptr;
	Spring* spring_ = nullptr;
	bool IsChanged = false;
	int changeTimer = 20;

	//Enemy spawn position
	uint32_t enemySpawnX[MAXENEMIES] = { 20 , 30, 60, 40 };
	uint32_t enemySpawnY[MAXENEMIES] = { 18, 14, 12, 5 };

	//Spike spawn position
	uint32_t spikeSpawnX[MAXSPIKES] = { 45, 48, 51 };
	uint32_t spikeSpawnY[MAXSPIKES] = { 6, 6, 6 };

	uint32_t reverseCubeSpawnX[MAXREVERSECUBES] = 
	{ 
		6, 12, 6, 6, 6,
		12, 12, 12, 22,
		25, 28, 31, 44 ,45,
		46, 47, 48, 46, 53,
		53, 54, 52, 51, 50,
		55, 55, 55,
	};
	uint32_t reverseCubeSpawnY[MAXREVERSECUBES] = 
	{ 
		95, 95, 96, 97,
		98, 96, 97, 98,
		98, 98, 98, 98,
		86, 86, 86, 86,
		86, 97, 83, 72, 72,
		72, 72, 72, 69, 68,
		67,
	};

	uint32_t springPosX[MAXSPRINGS] = { 46, 53 };
	uint32_t springPosY[MAXSPRINGS] = {98, 84};
	
	bool reverseCubeActive[MAXREVERSECUBES] = 
	{ true, false, true, true, true, false,
	  false,false, false, true, false, true,
	  true,true,true,true,true, false, false,
	  true, true, true, true, true, false,
	  false, false,
	};

	bool isReversedBlock[MAXREVERSECUBES] = 
	{ true, false, true, true,
	  true,false,false,false,
	  false, true, false, true,
	  true,true,true,true,true,
	  false,false, true, true,
	  true, true, true, false,
		false, false,
	};

	uint32_t sceneTransitionTimer = 0;
	bool isSceneTransitioning = false;
	bool playerCanMove;

	Model* checkpointModel_ = nullptr;
	Checkpoint* checkpoint1_ = nullptr;
	Checkpoint* checkpoint2_ = nullptr;
	bool checkPoint2Reached_ = false;
	bool checkPoint1Reached_ = false;
	bool touchedSpring = false;

	Vector3 playerPosition;
	Vector3 playerSpawnPos;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

};


