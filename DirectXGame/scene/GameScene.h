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
	/// 描画
	/// </summary>
	void Draw();

	void GenerateBlocks();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	uint32_t textureHandle_ = 0;
	Model* playerModel_ = nullptr;
	ViewProjection *viewProjection_ = nullptr;
	//WorldTransform worldTransform_;
	Player* player_ = nullptr;
	Skydome* skydome_ = nullptr;
	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;
	//std::vector<WorldTransform*>worldTransformBlocks_;
	std::vector<std::vector<WorldTransform*>>worldTransformBlocks_;
	Model* modelBlock_ = nullptr;
	Model* modelSkydome_ = nullptr;
	MapChipField* mapChipField_ = nullptr;
	CameraController* cameraController_ = nullptr;
	Rect cameraRange = { 168.0f,28.5f,0,16 };
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
};
