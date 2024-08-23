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
#include "Parachute.h"
#include "Wind.h"

#define NOMINMAX




/// <summary>
/// ゲームシーン
/// </summary>
class GameScene2 {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene2();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene2();

	void PlayerStartPos();

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

	void WarningTriangle();

	void StageClearCamera();

	void UsingParachute();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void GenerateBlocks();

	bool GetIsDead() const { return isDead_; };

	bool GetIsFinished() const { return finished_; };

	bool GetStageClear() const { return stageClear_; };

	bool GetGoToNextStage() const { return goToNextStage_; };

	bool GetCheckpointReached() const { return checkPointReached; };

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	uint32_t textureHandle_ = 0;
	Sprite* sprite_ = nullptr;
	Model* playerModel_ = nullptr;
	Model* enemyModel_ = nullptr;
	Model* deathparticleModel_ = nullptr;
	Model* goalModel_ = nullptr;
	Model* clearTextModel_ = nullptr;
	Model* spikeModel_ = nullptr;
	Model* parachuteModel_ = nullptr;
	Model* windModel_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
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
	Rect cameraRange = { 168.0f,28.5f,0.0f,16.0f + 167.0f };
	float topStartCameraPos = 16.0f + 167.0f;
	Enemy* enemy_ = nullptr;
	std::list<Enemy*> enemies_;
	std::list<Spikes*> spikes_;
	std::list<Wind*> winds_;
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
	Vector3 goalCameraPos = { 0,0,-40.0f - 160.0f };
	ClearText* stageClearText_ = nullptr;
	static inline const float maxCameraRangeTop = 22.0f + 161.0f;
	static inline const float minCameraRangeTop = 0.0f;
	Spikes* spike_ = nullptr;
	Parachute* parachute_ = nullptr;
	Wind* wind_ = nullptr;
	//Enemy spawn position
	uint32_t enemySpawnX[MAXENEMIES] = { 20 , 30, 60, 40 };
	uint32_t enemySpawnY[MAXENEMIES] = { 18, 14, 12, 5 };

	//Spike spawn position
	uint32_t spikeSpawnX[MAXSPIKES2] = {};
	uint32_t spikeSpawnY[MAXSPIKES2] = {};

	float windSpawnX[MAXWINDS] = { 95.0f, 95.0f,95.0f,95.0f,95.0f };
	float windSpawnY[MAXWINDS] = { -45.0f,-4.0f, 50.0f, 100.0f,150.0f };



	//get new range of camera max/min every time we touch ground
	float newLandPositionY = 0.0f;

	Vector3 parachutePosition;
	Vector3 playerPosition;
	Vector3 playerSpawnPos;
	bool inWind = false;
	bool stopUpCamera = false;
	bool warningStart = false;
	int warningTimer = 1;
	int warningLoops = 0;
	bool checkPointReached = false;

	SpikeSpawnConfig configs[MAXSPIKES2] = {
	{0, 8, 8, 9, 1, 1},      // First range: X = 8 + i, Y = 9 + i
	{8, 23, 18, 19, -1, 1},  // Second range: X = 26 - i, Y = 11 + i
	{23, 27, 1, 38, 1, 0},   // Third range: X = 1 + (i - 23), Y = 38
	{27, 31, 5, 42, 1, 0},   // Fourth range: X = 5 + (i - 27), Y = 42
	{31, 35, 15, 42, 1, 0},  // Fifth range: X = 15 + (i - 31), Y = 42
	{35, 39, 1, 47, 1, 0},   // Sixth range: X = 1 + (i - 35), Y = 47
	{39, 43, 9, 47, 1, 0},   // Seventh range: X = 9 + (i - 39), Y = 47
	{43, 47, 5, 52, 1, 0},   // Eighth range: X = 5 + (i - 43), Y = 52
	{47, 51, 15, 52, 1, 0},  // Ninth range: X = 15 + (i - 47), Y = 52
	{51, 54, 3, 65, 1, 0},   // Tenth range: X = 3 + (i - 51), Y = 65
	{54, 57, 3, 66, 1, 0},   // Eleventh range: X = 3 + (i - 54), Y = 66
	{57, 60, 3, 71, 1, 0},   // Twelfth range: X = 3 + (i - 57), Y = 71
	{60, 63, 3, 72, 1, 0},   // Thirteenth range: X = 3 + (i - 60), Y = 72
	{63, 66, 3, 77, 1, 0},   // Fourteenth range: X = 3 + (i - 63), Y = 77
	{66, 69, 3, 78, 1, 0},   // Fifteenth range: X = 3 + (i - 66), Y = 78
	{69, 72, 3, 83, 1, 0},   // Sixteenth range: X = 3 + (i - 69), Y = 83
	{72, 75, 3, 84, 1, 0},    // Seventeenth range: X = 3 + (i - 72), Y = 84
	{75, 87, 43, 1, 1, 0},    // Seventeenth range: X = 3 + (i - 72), Y = 84
	{87, 89, 63, 60, 1, 0},    // Seventeenth range: X = 3 + (i - 72), Y = 84
	{89, 91, 63, 61, 1, 0},    // Seventeenth range: X = 3 + (i - 72), Y = 84
	{91, 93, 63, 50, 1, 0},    // Seventeenth range: X = 3 + (i - 72), Y = 84
	{93, 95, 63, 51, 1, 0},    // Seventeenth range: X = 3 + (i - 72), Y = 84
	{95, 97, 63, 40, 1, 0},    // Seventeenth range: X = 3 + (i - 72), Y = 84
	{97, 99, 63, 41, 1, 0},    // Seventeenth range: X = 3 + (i - 72), Y = 84
	{99, 115, 43, 6, 0, 1},    // Seventeenth range: X = 3 + (i - 72), Y = 84
	{115, 120, 56, 12, 0, 7},    // Seventeenth range: X = 3 + (i - 72), Y = 84
	{120, 157, 56, 48, 1, 0},    // Seventeenth range: X = 3 + (i - 72), Y = 84
	{157, MAXSPIKES2, 62, 55, 1, 0},    // Seventeenth range: X = 3 + (i - 72), Y = 84
	};



	/// <summary>
	/// ゲームシーン用
	/// </summary>

};
