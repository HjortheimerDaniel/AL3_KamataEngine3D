#include "gameScene3.h"
#include "TextureManager.h"
#include <cassert>
#include "imgui.h"

GameScene3::GameScene3()
{
}

GameScene3::~GameScene3()
{
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
	delete viewProjection_;
	delete goal_;
	delete goalModel_;
	delete deathparticleModel_;
	delete clearTextModel_;
	delete spikeModel_;
	delete spike_;
	delete fade_;
	delete stageClearText_;

	for (Enemy* enemy : enemies_)
	{
		delete enemy;
	}
	enemies_.clear();

	for (Spikes* spike : spikes_)
	{
		delete spike;
	}
	spikes_.clear();

	delete reverseCube_;


	for (ReverseCubes* reversecube : reversedCubes_)
	{
		delete reversecube;
	}
	reversedCubes_.clear();
}

void GameScene3::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	viewProjection_ = new ViewProjection();
	viewProjection_->Initialize();
	modelBlock_ = Model::Create();

#pragma region audio

	audioHandle_ = audio_->LoadWave("powerUp.wav");
	audioHandle2_ = audio_->LoadWave("explosion.wav");
	audioHandle3_ = audio_->LoadWave("test.m4a");
	playHandle = 1;
	playHandle2 = 1;
	playHandle3 = 1;

#pragma endregion

#pragma region skydome
	modelSkydome_ = Model::CreateFromOBJ("skydome", true); //find the model inside the skydome folder
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_, viewProjection_);

	modelSkydome2_ = Model::CreateFromOBJ("skydomereverse", true); //find the model inside the skydome folder
	skydome2_ = new Skydome();
	skydome2_->Initialize(modelSkydome2_, viewProjection_);


#pragma endregion

#pragma region MapChipField

	mapChipField_ = new MapChipField;
	mapChipField_->Initialize(100, 100); //HERE
	mapChipField_->ResetMapChipData();
	mapChipField_->LoadMapChipCsv("Resources/mapchip/blocks4.csv");
	GenerateBlocks();

#pragma endregion

#pragma region player

	playerModel_ = Model::CreateFromOBJ("player", true);
	player_ = new Player();
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(1, 98);
	player_->Initialize(playerModel_, viewProjection_, playerPosition);
	player_->SetMapChipField(mapChipField_);

#pragma endregion

#pragma region Enemy

	enemyModel_ = Model::CreateFromOBJ("enemy", true);

	for (int32_t i = 0; i < MAXENEMIES; i++)
	{
		Enemy* newEnemy = new Enemy();
		Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(enemySpawnX[i], enemySpawnY[i]);
		newEnemy->Initialize(enemyModel_, viewProjection_, enemyPosition);
		enemies_.push_back(newEnemy);
		newEnemy->SetMapChipField(mapChipField_);

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

#pragma region Fade

	phase_ = Phase::kFadeIn;
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Status::FadeIn, duration_);

#pragma endregion

#pragma region goal

	goalModel_ = Model::CreateFromOBJ("goal", true);
	goal_ = new Goal();
	Vector3 doorPosition = mapChipField_->GetMapChipPositionByIndex(8, 7);
	goal_->Initialize(goalModel_, viewProjection_, doorPosition);
	goal_->SetMapChipField(mapChipField_);

#pragma endregion

#pragma region StageClearText

	clearTextModel_ = Model::CreateFromOBJ("cleartext", true);
	stageClearText_ = new ClearText();
	Vector3 clearPosition = mapChipField_->GetMapChipPositionByIndex((uint32_t)doorPosition.x, (uint32_t)doorPosition.y);
	stageClearText_->Initialize(clearTextModel_, viewProjection_, doorPosition + Vector3((int)-7, (int)6, 0));
	stageClearText_->SetMapChipField(mapChipField_);


#pragma endregion

#pragma region Spikes

	spikeModel_ = Model::CreateFromOBJ("spike", true);
	for (uint32_t i = 0; i < MAXSPIKES; i++)
	{
		Spikes* newSpike = new Spikes();
		Vector3 spikePosition = mapChipField_->GetMapChipPositionByIndex(spikeSpawnX[i], spikeSpawnY[i]);
		newSpike->Initialize(spikeModel_, viewProjection_, spikePosition);
		spikes_.push_back(newSpike);
		newSpike->SetMapChipField(mapChipField_);
		switch (i)
		{
		case 0:
			newSpike->SetStruct(SpikesStruct::Active);
			break;
		case 1:
			newSpike->SetStruct(SpikesStruct::Inactive);
			break;
		case 2:
			newSpike->SetStruct(SpikesStruct::Active);
			break;
		default:
			break;
		}
	}



#pragma endregion

#pragma region ReverseCubes

	

	for (int32_t i = 0; i < MAXREVERSECUBES; i++)
	{
		ReverseCubes* newReverseCubes = new ReverseCubes();
		Vector3 reverseBlockPosition = mapChipField_->GetMapChipPositionByIndex(reverseCubeSpawnX[i], reverseCubeSpawnY[i]);
		newReverseCubes->Initialize(viewProjection_, reverseBlockPosition, isReversedBlock[i]);
		reversedCubes_.push_back(newReverseCubes);
		newReverseCubes->SetMapChipField(mapChipField_);

	}


#pragma endregion

}

void GameScene3::Update() {
	
	ChangePhase();
	switch (phase_)
	{

#pragma region FadeIn

	case Phase::kFadeIn:

		fade_->Update();
		player_->Update();
		skydome_->Update();
		MoveCameraHorizontally();
		cameraController_->Update();
		goal_->Update();
		for (Enemy* enemy : enemies_) { //create new Enemy enemy 
			enemy->Update();

		}
		IsEnemyCloseToPlayer();


		for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) { //everything this is inside worldTransformBlocks_ gets copied into worldTransformBlockLine, and every time a new thing goes inside we go inside the for function and then repeat
			for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

				if (!worldTransformBlock) { //if there is a block here
					continue; //keep going
				}
				worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);
				worldTransformBlock->TransferMatrix();
			}
		}
		viewProjection_->matView = cameraController_->GetViewProjection().matView;
		viewProjection_->matProjection = cameraController_->GetViewProjection().matProjection;
		viewProjection_->TransferMatrix(); //this function keeps check of the movement of your objects. If this isnt written the object wont move
		break;
#pragma endregion

#pragma region Play

	case Phase::kPlay:

		ReverseCamera();
		if (playerCanMove) 
		{
			player_->Update();
			player_->Movement();

		}
		if (!IsChanged) 
		{
			skydome_->Update();
		}
		else 
		{
			skydome2_->Update();

		}
		skydome_->Update();
		MoveCameraHorizontally();
		goal_->Update();
		for (Enemy* enemy : enemies_) { //create new Enemy enemy 
			enemy->Update();
		}
		for (Spikes* spike : spikes_) { //create new Enemy enemy 
			spike->Update();
			spike->SpikeTimer();
		}
		for (ReverseCubes* reverseCube : reversedCubes_) { //create new Enemy enemy 
			reverseCube->Update();
		}
		CheckAllCollisions();
		IsEnemyCloseToPlayer();

		for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) { //everything this is inside worldTransformBlocks_ gets copied into worldTransformBlockLine, and every time a new thing goes inside we go inside the for function and then repeat
			for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

				if (!worldTransformBlock) { //if there is a block here
					continue; //keep going
				}
				worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);
				worldTransformBlock->TransferMatrix();
			}
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


		break;

#pragma endregion

#pragma region Death
	case Phase::kDeath:
		skydome_->Update();
		goal_->Update();
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

#pragma region StageClear

	case Phase::kStageClear:

		StageClearCamera();

		fade_->Update();
		skydome_->Update();
		goal_->Update();
		for (Enemy* enemy : enemies_) { //create new Enemy enemy 
			enemy->Update();
		}
		stageClearText_->Update();
		TransitionScene();
		viewProjection_->matView = cameraController_->GetViewProjection().matView;
		viewProjection_->matProjection = cameraController_->GetViewProjection().matProjection;
		viewProjection_->TransferMatrix();
		break;

#pragma endregion

#pragma region FadeOut

	case Phase::kFadeOut:
		fade_->Update();
		skydome_->Update();
		goal_->Update();

		viewProjection_->matView = cameraController_->GetViewProjection().matView;
		viewProjection_->matProjection = cameraController_->GetViewProjection().matProjection;
		viewProjection_->TransferMatrix(); //this function keeps check of the movement of your objects. If this isnt written the object wont move

		break;

#pragma endregion

	default:
		break;
	}


}

void GameScene3::CheckAllCollisions()
{
#pragma region player enemy

	AABB aabb1, aabb2;

	aabb1 = player_->GetAABB();

	for (Enemy* enemy : enemies_)
	{
		if (!enemy->GetIsDead())
		{
			aabb2 = enemy->GetAABB();

			if (IsCollision(aabb1, aabb2))
			{
				player_->OnCollision(enemy_);
				enemy_->OnCollision(player_);

			}

			if (IsStompCollision(aabb1, aabb2) && !player_->GetOnGround())
			{
				player_->StompCollision(enemy_);
				enemy->StompCollision(player_);
				if (audio_->IsPlaying(playHandle) == 0 && playHandle == 1)
				{
					playHandle = audio_->PlayWave(audioHandle_, false, 0.1f);
				}
				playHandle = 1;
			}
		}
	}
#pragma endregion

#pragma region player goal

	AABB aabb3 = goal_->GetAABB();

	if (IsCollision(aabb1, aabb3))
	{
		player_->OnCollisionGoal(goal_);
		goal_->OnCollision(player_);
		stageClear_ = true;
		if (audio_->IsPlaying(playHandle3) == 0 && playHandle3 == 1)
		{
			playHandle3 = audio_->PlayWave(audioHandle3_, false, 0.5f);
		}
	}

#pragma endregion


#pragma region player spike

	for (Spikes* spike : spikes_)
	{
		AABB aabb4 = spike->GetAABB();

		if (IsCollision(aabb1, aabb4) && spike->GetStruct() == SpikesStruct::Active)
		{
			player_->OnCollision(enemy_);
		}
	}

#pragma endregion


#pragma region player reversecubes

	for (ReverseCubes* reversecube : reversedCubes_)
	{
		AABB aabb5 = reversecube->GetAABB();

		if (IsCollision(aabb1, aabb5))
		{
			player_->OnCollision(reversecube);
		}

	}

#pragma endregion

}

bool GameScene3::IsCollision(const AABB& aabb1, const AABB& aabb2)
{
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z))
	{
		return true;
	}

	return false;
}

bool GameScene3::IsStompCollision(const AABB& aabb1, const AABB& aabb2)
{
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y - aabb2.max.y <= stompDistance && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z))
	{
		return true;
	}

	return false;
}

void GameScene3::IsEnemyCloseToPlayer()
{
	for (Enemy* enemy : enemies_)
	{
		if (enemy->GetWorldPosition().x - player_->GetWorldPosition().x <= activateEnemyDistance)
		{
			enemy->SetCanMove(true);
		}
	}
}

void GameScene3::ReverseCamera()
{
	if (Input::GetInstance()->TriggerKey(DIK_SPACE) && !IsChanged && changeTimer >= 10)
	{
		changeTimer = 0;
		player_->SetReversed(true);
		IsChanged = true;
		cameraController_->SetIsReversed(true);
		cameraController_->SetTargetOffset({ 0.0f, 0.0f, 40.0f });

	}

	if (Input::GetInstance()->TriggerKey(DIK_SPACE) && IsChanged &&  changeTimer >= 10)
	{
		changeTimer = 0;
		player_->SetReversed(false);
		IsChanged = false;
		cameraController_->SetIsReversed(false);
		cameraController_->SetTargetOffset({ 0.0f, 0.0f, -40.0f });

	}



	if (changeTimer < 20) 
	{
		changeTimer++;

	}
	if (changeTimer >= 20) 
	{
		changeTimer = 20;

	}

	if (changeTimer == 20) 
	{
		playerCanMove = true;
	}
	else 
	{
		playerCanMove = false;

	}
	
}

void GameScene3::ChangePhase()
{
	switch (phase_)
	{
	case Phase::kFadeIn:
		if (fade_->IsFinished())
		{
			phase_ = Phase::kPlay;
		}
		break;
	case Phase::kPlay:
		if (player_->GetIsDead())
		{
			if (audio_->IsPlaying(playHandle2) == 0 && playHandle2 == 1)
			{
				playHandle2 = audio_->PlayWave(audioHandle2_, false, 0.1f);
			}
			phase_ = Phase::kDeath;
			const Vector3& deathParticlePosition = player_->GetWorldPosition();
			deathParticles_->Initialize(deathparticleModel_, viewProjection_, deathParticlePosition);

		}

		if (stageClear_)
		{
			phase_ = Phase::kStageClear;
		}

		break;
	case Phase::kDeath:
		if (deathParticles_ && deathParticles_->GetIsFinished())
		{
			fade_->Start(Status::FadeOut, duration_);
			phase_ = Phase::kFadeOut;
		}
		break;
	case Phase::kStageClear:
		if (isSceneTransitioning)
		{
			fade_->Start(Status::FadeOut, duration_);
			phase_ = Phase::kFadeOut;
		}
		break;

	case Phase::kFadeOut:
		if (fade_->IsFinished() && !stageClear_)
		{
			finished_ = true;
		}

		if (fade_->IsFinished() && stageClear_)
		{
			goToNextStage_ = true;
		}

		break;
	default:
		break;
	}

}

void GameScene3::MoveCameraHorizontally()
{
	if (player_->GetWorldTransform().translation_.y > 23.0f)
	{
		cameraRange.top = player_->GetWorldPosition().y - 9.0f;
	}
	else
	{
		cameraRange.top = 15.0f;
	}

	cameraController_->SetMoveableArea(cameraRange);
	cameraController_->Update();
}

void GameScene3::StageClearCamera()
{
	if (goalCameraPos.z < -20.0f)
	{
		goalCameraPos.z += 3.2f;
	}
	if (!player_->GetOnGround()) {
		goalCameraPos.y = goal_->GetWorldPosition().y / 75.0f;
	}
	else
	{
		goalCameraPos.y = goal_->GetWorldPosition().y / 35.0f;

	}
	cameraController_->SetStageClearCamera(true);
	cameraController_->SetTargetOffset({ 2,goalCameraPos.y,goalCameraPos.z });
	cameraController_->Update();
}

void GameScene3::TransitionScene()
{
	sceneTransitionTimer++;

	if (sceneTransitionTimer >= 130)
	{
		isSceneTransitioning = true;
		sceneTransitionTimer = 130;
	}
}

void GameScene3::Draw() {

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

	switch (phase_)
	{

#pragma region FadeIn

	case Phase::kFadeIn:
		player_->Draw();
		for (Enemy* enemy : enemies_) {
			enemy->Draw();
		}
		skydome_->Draw();
		for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
			for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
				if (!worldTransformBlock)
					continue;
				if (worldTransformBlock->translation_.x - player_->GetWorldTransform().translation_.x >= -60 && worldTransformBlock->translation_.x - player_->GetWorldTransform().translation_.x < 60 &&
					worldTransformBlock->translation_.y - player_->GetWorldTransform().translation_.y <= 50 && worldTransformBlock->translation_.y - player_->GetWorldTransform().translation_.y >= -40)
				{
					modelBlock_->Draw(*worldTransformBlock, *viewProjection_);
				}
			}
		}
		goal_->Draw();
		fade_->Draw();

		break;

#pragma endregion

#pragma region Play
	case Phase::kPlay:
		player_->Draw();
		for (Enemy* enemy : enemies_) {
			enemy->Draw();
		}
		for (Spikes* spike : spikes_)
		{
			if (spike->GetWorldPosition().x - player_->GetWorldTransform().translation_.x >= -60 && spike->GetWorldPosition().x - player_->GetWorldTransform().translation_.x < 60 &&
				spike->GetWorldPosition().y - player_->GetWorldTransform().translation_.y <= 50 && spike->GetWorldPosition().y - player_->GetWorldTransform().translation_.y >= -40)
			{
				spike->Draw();
			}
		}
		
		for (ReverseCubes* reverseCube : reversedCubes_) { //create new Enemy enemy 
			if (reverseCube->GetIsReversed() && !IsChanged)
			{
				reverseCube->Draw();
			}
			else if (!reverseCube->GetIsReversed() && IsChanged) 
			{
				reverseCube->Draw();
			}
		}
		if (!IsChanged)
		{
			skydome_->Draw();
		}
		else
		{
			skydome2_->Draw();

		}
		//skydome_->Draw();
		goal_->Draw();
		for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
			for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
				if (!worldTransformBlock)
					continue;
				if (worldTransformBlock->translation_.x - player_->GetWorldTransform().translation_.x >= -60 && worldTransformBlock->translation_.x - player_->GetWorldTransform().translation_.x < 60 &&
					worldTransformBlock->translation_.y - player_->GetWorldTransform().translation_.y <= 50 && worldTransformBlock->translation_.y - player_->GetWorldTransform().translation_.y >= -40)
				{
					modelBlock_->Draw(*worldTransformBlock, *viewProjection_);
				}
			}
		}

		break;
#pragma endregion

#pragma region Death

	case Phase::kDeath:
		for (Enemy* enemy : enemies_) {
			enemy->Draw();
		}
		deathParticles_->Draw();
		skydome_->Draw();
		goal_->Draw();
		for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
			for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
				if (!worldTransformBlock)
					continue;
				if (worldTransformBlock->translation_.x - player_->GetWorldTransform().translation_.x >= -60 && worldTransformBlock->translation_.x - player_->GetWorldTransform().translation_.x < 60 &&
					worldTransformBlock->translation_.y - player_->GetWorldTransform().translation_.y <= 50 && worldTransformBlock->translation_.y - player_->GetWorldTransform().translation_.y >= -40)
				{
					modelBlock_->Draw(*worldTransformBlock, *viewProjection_);
				}
			}
		}
		for (Spikes* spike : spikes_)
		{
			if (spike->GetWorldPosition().x - player_->GetWorldTransform().translation_.x >= -60 && spike->GetWorldPosition().x - player_->GetWorldTransform().translation_.x < 60 &&
				spike->GetWorldPosition().y - player_->GetWorldTransform().translation_.y <= 50 && spike->GetWorldPosition().y - player_->GetWorldTransform().translation_.y >= -40)
			{
				spike->Draw();
			}
		}
		break;

#pragma endregion

#pragma region StageClear

	case Phase::kStageClear:

		player_->Draw();
		skydome_->Draw();
		goal_->Draw();
		stageClearText_->Draw();
		fade_->Draw();
		break;

#pragma endregion

#pragma region FadeOut

	case Phase::kFadeOut:
		skydome_->Draw();
		stageClearText_->Draw();
		if (isSceneTransitioning)
		{
			goal_->Draw();
		}

		fade_->Draw();

		break;

#pragma endregion

	default:
		break;
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

void GameScene3::GenerateBlocks()
{
	uint32_t numBlockVertical = mapChipField_->GetNumBlockVertical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	worldTransformBlocks_.resize(numBlockVertical);

	for (uint32_t i = 0; i < numBlockVertical; i++) {
		worldTransformBlocks_[i].resize(numBlockHorizontal);

		for (uint32_t j = 0; j < numBlockHorizontal; j++)
		{
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) { //if there is a block here
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}

