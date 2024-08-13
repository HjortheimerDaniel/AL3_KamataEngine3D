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

#define NOMINMAX


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

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

	void ChangePhase();

	void MoveCameraHorizontally();

	void StageClearCamera();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void GenerateBlocks();

	bool GetIsDead() const { return isDead_; };

	bool GetIsFinished() const { return finished_; };

	bool GetStageClear() const { return stageClear_; };

	bool GetGoToNextStage() const {return goToNextStage_;};

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	uint32_t textureHandle_ = 0;
	Model* playerModel_ = nullptr;
	Model* enemyModel_ = nullptr;
	Model* deathparticleModel_ = nullptr;
	Model* goalModel_ = nullptr;
	Model* clearTextModel_ = nullptr;
	ViewProjection *viewProjection_ = nullptr;
	Player* player_ = nullptr;
	Skydome* skydome_ = nullptr;
	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;
	std::vector<std::vector<WorldTransform*>>worldTransformBlocks_;
	//std::vector<std::vector<WorldTransform*>>worldTransformDeathParticles_;
	Model* modelBlock_ = nullptr;
	Model* modelSkydome_ = nullptr;
	MapChipField* mapChipField_ = nullptr;
	CameraController* cameraController_ = nullptr;
	Rect cameraRange = { 168.0f,28.5f,0.0f,16.0f};
	Enemy* enemy_ = nullptr;
	std::list<Enemy*> enemies_;
	DeathParticles* deathParticles_ = nullptr;
	Phase phase_;
	bool isDead_ = false;
	bool finished_ = false;
	Fade* fade_ = nullptr;
	float duration_ = 1.0f;
	float stompDistance = 0.9f;
	float activateEnemyDistance = 48.0f;
	Goal* goal_ = nullptr;
	bool stageClear_ = false;
	bool goToNextStage_ = false;
	Vector3 goalCameraPos = {0,0,-40.0f};
	ClearText* stageClearText_ = nullptr;
	static inline const float maxCameraRangeTop = 22.0f;
	static inline const float minCameraRangeTop = 16.0f;

	//Enemy spawn position
	uint32_t spawnX[MAXENEMIES] = { 20,30,60 };
	uint32_t spawnY[MAXENEMIES] = { 18,14,12 };
	

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
};
