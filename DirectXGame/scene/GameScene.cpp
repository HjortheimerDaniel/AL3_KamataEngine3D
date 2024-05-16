#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {

	delete playerModel_;
	delete player_;
	delete skydome_;
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();
	delete modelBlock_;
	delete debugCamera_;
	delete modelSkydome_;
	delete mapChipField_;

}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	//textureHandle_ = TextureManager::Load("emil.jpg");
	//model_->Create();
	viewProjection_ = new ViewProjection();
	//worldTransform_.Initialize();
	viewProjection_->Initialize();
	modelBlock_ = Model::Create();
	
#pragma region skydome
	modelSkydome_ = Model::CreateFromOBJ("skydome", true); //find the model inside the skydome folder
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_, viewProjection_);


#pragma endregion

#pragma region player
	playerModel_ = Model::CreateFromOBJ("player", true);
	player_ = new Player();
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(1, 18);
	player_->Initialize(playerModel_, viewProjection_, playerPosition);


#pragma endregion
	
	
	debugCamera_ = new DebugCamera(1280, 720);
	debugCamera_->SetFarZ(2000);

	mapChipField_ = new MapChipField;
	mapChipField_->ResetMapChipData();
	mapChipField_->LoadMapChipCsv("Resources/mapchip/blocks.csv");
	GenerateBlocks();
}

void GameScene::Update() {

	player_->Update();
	skydome_->Update();
	
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) { //everything this is inside worldTransformBlocks_ gets copied into worldTransformBlockLine, and every time a new thing goes inside we go inside the for function and then repeat
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			
			if (!worldTransformBlock) { //if there is a block here
				continue; //keep going
			}
			worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);
			worldTransformBlock->TransferMatrix();
			
		}
	}
	
	//debugCamera_->Update();

#ifdef _DEBUG
	/*if (input_->TriggerKey(DIK_SPACE) && !isDebugCameraActive_) {
		isDebugCameraActive_ = true;
	}
	else if (input_->TriggerKey(DIK_SPACE) && isDebugCameraActive_) {
		isDebugCameraActive_ = false;

	}*/
	if (input_->TriggerKey(DIK_BACK)) 
	{
		isDebugCameraActive_ ^= true; //same as above
	}


#endif // _DEBUG

	if (isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_->matView = debugCamera_->GetViewProjection().matView;
		viewProjection_->matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_->TransferMatrix(); //this function keeps check of the movement of your objects. If this isnt written the object wont move
	}
	else {
		viewProjection_->UpdateMatrix();
	}
	
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	
	
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	player_->Draw();
	skydome_->Draw();
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			modelBlock_->Draw(*worldTransformBlock, *viewProjection_);
		}
	}
	
	

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::GenerateBlocks()
{
	
	uint32_t numBlockVertical = mapChipField_->GetNumBlockVertical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	worldTransformBlocks_.resize(numBlockVertical);
	

	for (uint32_t i = 0; i < numBlockVertical; i++) {
		worldTransformBlocks_[i].resize(numBlockHorizontal);

		for (uint32_t j = 0; j < numBlockHorizontal; j++)
		{
			if (mapChipField_->GetMapChipTypeByIndex(j,i) == MapChipType::kBlock) { //if there is a block here
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j,i);
			}
			
		}
	}

}
