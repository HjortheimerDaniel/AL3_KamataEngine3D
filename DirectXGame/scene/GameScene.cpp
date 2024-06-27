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
	delete cameraController_;
	delete enemy_;
	delete deathParticles_;

	for ( Enemy* enemy : enemies_)
	{
		delete enemy;
	}
	enemies_.clear();

	
	//for (DeathParticles* deathParticles : deathP_)
	//{
	//	delete deathParticles;
	//}
	//deathP_.clear();
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
	phase_ = Phase::kPlay;
	
#pragma region skydome
	modelSkydome_ = Model::CreateFromOBJ("skydome", true); //find the model inside the skydome folder
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_, viewProjection_);


#pragma endregion

#pragma region MapChipField

	mapChipField_ = new MapChipField;
	mapChipField_->Initialize(); //HERE
	mapChipField_->ResetMapChipData();
	mapChipField_->LoadMapChipCsv("Resources/mapchip/blocks.csv");
	GenerateBlocks();

#pragma endregion

#pragma region player

	playerModel_ = Model::CreateFromOBJ("player", true);
	player_ = new Player();
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(2, 18);
	player_->Initialize(playerModel_, viewProjection_, playerPosition);
	player_->SetMapChipField(mapChipField_);

#pragma endregion
	
#pragma region Enemy

	enemyModel_ = Model::CreateFromOBJ("enemycolor", true);
	//enemy_ = new Enemy();
	//Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(20, 18);
	//enemy_->Initialize(enemyModel_, viewProjection_, enemyPosition);
	//enemy_->SetMapChipField(mapChipField_);

	for (int32_t i = 0; i < MAXENEMIES; i++)
	{
		Enemy* newEnemy = new Enemy();
		Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(20 + (5 * i) , 18 - i);
		newEnemy->Initialize(enemyModel_, viewProjection_, enemyPosition);
		enemies_.push_back(newEnemy);
		
	}

#pragma endregion

#pragma region CameraController

	cameraController_ = new CameraController();
	cameraController_->Initialize();
	cameraController_->SetTarget(player_); //follow the player
	cameraController_->Reset();
	cameraController_->SetMoveableArea(cameraRange);

#pragma endregion

#pragma region DebugCamera

	debugCamera_ = new DebugCamera(1280, 720);
	debugCamera_->SetFarZ(2000);

#pragma endregion

#pragma region DeathParticles
	deathparticleModel_ = Model::CreateFromOBJ("deathparticle", true);
	deathParticles_ = new DeathParticles();
	deathParticles_->Initialize(deathparticleModel_, viewProjection_, playerPosition);
	
#pragma endregion

}

void GameScene::Update() {

	switch (phase_)	
	{

	#pragma region Play

	case Phase::kPlay:
		player_->Update();

		skydome_->Update();

		cameraController_->Update();

		for (Enemy* enemy : enemies_) { //create new Enemy enemy 
			enemy->Update();
		}

		CheckAllCollisions();

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
			viewProjection_->matView = cameraController_->GetViewProjection().matView;
			viewProjection_->matProjection = cameraController_->GetViewProjection().matProjection;
			viewProjection_->TransferMatrix(); //this function keeps check of the movement of your objects. If this isnt written the object wont move
		}


		break;

#pragma endregion

	#pragma region Death
	case Phase::kDeath:

		skydome_->Update();
		for (Enemy* enemy : enemies_) { //create new Enemy enemy 
			enemy->Update();
		}
		if (deathParticles_)
		{
			deathParticles_->Update();
		}

		#ifdef _DEBUG
		
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
			viewProjection_->matView = cameraController_->GetViewProjection().matView;
			viewProjection_->matProjection = cameraController_->GetViewProjection().matProjection;
			viewProjection_->TransferMatrix(); //this function keeps check of the movement of your objects. If this isnt written the object wont move
		}

		for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) { //everything this is inside worldTransformBlocks_ gets copied into worldTransformBlockLine, and every time a new thing goes inside we go inside the for function and then repeat
			for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

				if (!worldTransformBlock) { //if there is a block here
					continue; //keep going
				}
				worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);
				worldTransformBlock->TransferMatrix();
			}
		}

		break;

		#pragma endregion

	default:
		break;
	}

	


	
	


}

void GameScene::CheckAllCollisions()
{
#pragma region player enemy

	AABB aabb1, aabb2;

	aabb1 = player_->GetAABB();

	for (Enemy* enemy: enemies_)
	{
		aabb2 = enemy->GetAABB();

		if (IsCollision(aabb1, aabb2))
		{
			player_->OnCollision(enemy_);
			enemy_->OnCollision(player_);
		}
	}
#pragma endregion

}

bool GameScene::IsCollision(const AABB& aabb1, const AABB& aabb2)
{
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z))
	{
		return true;
	}

	return false;
}

void GameScene::ChangePhase()
{

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
	for (Enemy* enemy : enemies_) {
		enemy->Draw();
	}

		deathParticles_->Draw();
	//if (deathParticles_)
	//{
	//}

	//enemy_->Draw();
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
