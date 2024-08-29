#include "GameScene2.h"
#include "TextureManager.h"
#include <cassert>
#include "imgui.h"

GameScene2::GameScene2() {}

GameScene2::~GameScene2() {

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
	delete parachuteModel_;
	delete parachute_;
	delete windModel_;
	delete wind_;
	delete sprite_;
	delete checkpointModel_;
	delete checkpoint1_;
	delete parachuteTextModel_;
	delete parachuteTextModel2_;
	delete parachuteText_;
	delete parachuteText2_;

	for (Spikes* spike : spikes_)
	{
		delete spike;
	}
	spikes_.clear();

	for (Wind* wind : winds_) 
	{
		delete wind;
	}
	winds_.clear();
}

void GameScene2::PlayerStartPos()
{
	playerSpawnPos = mapChipField_->GetMapChipPositionByIndex(1, 3);
	//playerSpawnPos = mapChipField_->GetMapChipPositionByIndex(68, 5);
}

void GameScene2::PlayerCheckpoint1Pos()
{
	playerSpawnPos = mapChipField_->GetMapChipPositionByIndex(12, 98);
}

void GameScene2::PlayerCheckpoint2Pos()
{
	playerSpawnPos = mapChipField_->GetMapChipPositionByIndex(68, 5);
	//playerSpawnPos = mapChipField_->GetMapChipPositionByIndex(1, 3);
}

void GameScene2::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	viewProjection_ = new ViewProjection();
	viewProjection_->Initialize();
	modelBlock_ = Model::Create();

#pragma region audio

	audioHandle_ = audio_->LoadWave("Checkpoint.wav");
	audioHandle2_ = audio_->LoadWave("explosion.wav");
	audioHandle3_ = audio_->LoadWave("warning.wav");
	audioHandle4_ = audio_->LoadWave("test.m4a");
	playHandle = 1;
	playHandle2 = 1;
	playHandle3 = 1;
	playHandle4 = 1;

#pragma endregion

#pragma region skydome

	modelSkydome_ = Model::CreateFromOBJ("skydome", true); //find the model inside the skydome folder
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_, viewProjection_);


#pragma endregion

#pragma region MapChipField

	mapChipField_ = new MapChipField;
	mapChipField_->Initialize(100, 100); //HERE
	mapChipField_->ResetMapChipData();
	mapChipField_->LoadMapChipCsv("Resources/mapchip/blocks3.csv");
	GenerateBlocks();

#pragma endregion

#pragma region player

	playerModel_ = Model::CreateFromOBJ("player", true);
	player_ = new Player();
	//Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(2, 18);
	//playerPosition = mapChipField_->GetMapChipPositionByIndex(1, 3);
	playerPosition = playerSpawnPos;
	player_->Initialize(playerModel_, viewProjection_, playerPosition);
	player_->SetMapChipField(mapChipField_);

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

#pragma region GreyPauseVeil

	grey_ = new GreyPauseVeil();
	grey_->Initialize();

#pragma endregion

#pragma region goal

	goalModel_ = Model::CreateFromOBJ("goal", true);
	goal_ = new Goal();
	Vector3 doorPosition = mapChipField_->GetMapChipPositionByIndex(59, 60);
	goal_->Initialize(goalModel_, viewProjection_, doorPosition);
	goal_->SetMapChipField(mapChipField_);

#pragma endregion

#pragma region StageClearText

	clearTextModel_ = Model::CreateFromOBJ("cleartext", true);
	stageClearText_ = new ClearText();
	Vector3 clearPosition = mapChipField_->GetMapChipPositionByIndex((uint32_t)doorPosition.x, (uint32_t)doorPosition.y);
	//Vector3 clearPosition = mapChipField_->GetMapChipPositionByIndex(2, 18);
	stageClearText_->Initialize(clearTextModel_, viewProjection_, doorPosition + Vector3((int)-7, (int)6, 0));
	stageClearText_->SetMapChipField(mapChipField_);


#pragma endregion

#pragma region Spikes

	
	for (const auto& config : configs) {
		for (int i = config.loopStartX; i < config.loodEndX; i++) {
			spikeSpawnX[i] = config.baseX + (i - config.loopStartX) * config.incrementX;
			spikeSpawnY[i] = config.baseY + (i - config.loopStartX) * config.incrementY;
		}
	}
	spikeModel_ = Model::CreateFromOBJ("spike", true);
	for (uint32_t i = 0; i < MAXSPIKES2; i++)
	{
		Spikes* newSpike = new Spikes();
		Vector3 spikePosition = mapChipField_->GetMapChipPositionByIndex(spikeSpawnX[i], spikeSpawnY[i]);
		newSpike->Initialize(spikeModel_, viewProjection_, spikePosition);
		spikes_.push_back(newSpike);
		newSpike->SetMapChipField(mapChipField_);
		if (i >= 51 && i < 54) 
		{
			newSpike->SetMove(true);
			newSpike->SetAmplitude(16.0f);
			newSpike->SetStartPosition(18.0f + (i -51));
		}
		if (i >= 54 && i< 57)
		{
			newSpike->SetMove(true);
			newSpike->SetAmplitude(16.0f);
			newSpike->SetRotateUpsideDown(true);
			newSpike->SetStartPosition(18.0f + (i - 54));
		}
		if (i >= 57 && i < 60)
		{
			newSpike->SetMove(true);
			newSpike->SetAmplitude(-16.0f);
			newSpike->SetStartPosition(18.0f + (i - 57));
		}
		if (i >= 60 && i < 63)
		{
			newSpike->SetMove(true);
			newSpike->SetRotateUpsideDown(true);
			newSpike->SetAmplitude(-16.0f);
			newSpike->SetStartPosition(18.0f + (i - 60));
		}
		if (i >= 63 && i < 66)
		{
			newSpike->SetMove(true);
			newSpike->SetAmplitude(16.0f);
			newSpike->SetStartPosition(18.0f + (i - 63));
		}
		if (i >= 66 && i < 69)
		{
			newSpike->SetMove(true);
			newSpike->SetAmplitude(16.0f);
			newSpike->SetRotateUpsideDown(true);
			newSpike->SetStartPosition(18.0f + (i - 66));
		}
		if (i >= 69 && i < 72)
		{
			newSpike->SetMove(true);
			newSpike->SetAmplitude(-16.0f);
			newSpike->SetStartPosition(18.0f + (i - 69));
		}
		if (i >= 72 && i < 75)
		{
			newSpike->SetMove(true);
			newSpike->SetRotateUpsideDown(true);
			newSpike->SetAmplitude(-16.0f);
			newSpike->SetStartPosition(18.0f + (i - 72));
		}
		if (i >= 75 && i < 87) 
		{
			newSpike->SetRotateUpsideDown(true);
		}
		if (i >= 87 && i < 89) 
		{
			newSpike->SetMove(true);
			newSpike->SetAmplitude(-9.5f);
			newSpike->SetStartPosition(97.0f + (i - 87));
		}
		if (i >= 89 && i < 91) 
		{
			newSpike->SetMove(true);
			newSpike->SetRotateUpsideDown(true);
			newSpike->SetAmplitude(-9.5f);
			newSpike->SetStartPosition(97.0f + (i - 89));
		}
		if (i >= 91 && i < 93)
		{
			newSpike->SetMove(true);
			newSpike->SetAmplitude(9.5f);
			newSpike->SetStartPosition(97.0f + (i - 91));
		}
		if (i >= 93 && i < 95)
		{
			newSpike->SetMove(true);
			newSpike->SetRotateUpsideDown(true);
			newSpike->SetAmplitude(9.5f);
			newSpike->SetStartPosition(97.0f + (i - 93));
		}
		if (i >= 95 && i < 97)
		{
			newSpike->SetMove(true);
			newSpike->SetAmplitude(-9.5f);
			newSpike->SetStartPosition(97.0f + (i - 95));
		}
		if (i >= 97 && i < 99)
		{
			newSpike->SetMove(true);
			newSpike->SetRotateUpsideDown(true);
			newSpike->SetAmplitude(-9.5f);
			newSpike->SetStartPosition(97.0f + (i - 97));
		}
		if (i >= 99 && i < 115) 
		{
			newSpike->SetRotateRight(true);
			newSpike->SetMayMove(true);
			newSpike->SetMaxDistance(108.0f);
			newSpike->SetSpeed(0.8f);
			newSpike->SetRotation(1.5f);
		}
		if (i >= 115 && i < 120) 
		{
			newSpike->SetRotateRight(true);
			newSpike->SetUsesTimer(true);
			newSpike->SetMaxDistance(196.0f);
			newSpike->SetSpeed(1.2f);
			newSpike->SetRotation(1.5f);
		}
		if (i >= 120 && i < MAXSPIKES2) 
		{
			newSpike->SetUsesSpikeTimer(true);
			newSpike->SetStruct(SpikesStruct::Active);
		}
	}
	
#pragma endregion

#pragma region Parachute

	parachuteModel_ = Model::CreateFromOBJ("parachute", true);
	parachute_ = new Parachute();
	parachutePosition = playerPosition;
	parachute_->Initialize(parachuteModel_, viewProjection_, parachutePosition);

#pragma endregion 

#pragma region Wind

	windModel_ = Model::CreateFromOBJ("wind", true);
	for (uint32_t i = 0; i < MAXWINDS; i++)
	{
		Wind* newWinds = new Wind();
		Vector3 windPosition = { windSpawnX[i],windSpawnY[i],0.0f};
		newWinds->Initialize(windModel_, viewProjection_, windPosition);
		winds_.push_back(newWinds);

	}
	//Vector3 windPosition = mapChipField_->GetMapChipPositionByIndex((uint32_t)47, (uint32_t)99);


#pragma endregion

#pragma region WarningSprite

	textureHandle_ = TextureManager::Load("warning.png");
	sprite_ = Sprite::Create(textureHandle_, { 600, 300 });
	sprite_->SetSize({100,100});

#pragma endregion

#pragma region Checkpoint

	checkpointModel_ = Model::CreateFromOBJ("checkpoint", true);
	checkpoint1_ = new Checkpoint();
	Vector3 checkpointPosition = mapChipField_->GetMapChipPositionByIndex(64, 4);
	checkpoint1_->Initialize(checkpointModel_, viewProjection_, checkpointPosition);
	checkpoint1_->SetMapChipField(mapChipField_);
	
	checkpoint2_ = new Checkpoint();
	Vector3 checkpoint2Position = mapChipField_->GetMapChipPositionByIndex(10, 97);
	checkpoint2_->Initialize(checkpointModel_, viewProjection_, checkpoint2Position);
	checkpoint2_->SetMapChipField(mapChipField_);

#pragma endregion

#pragma region Parachutetext

	parachuteTextModel_ = Model::CreateFromOBJ("paratext", true);
	parachuteText_ = new ParachuteText();
	Vector3 parachuteTextPosition = mapChipField_->GetMapChipPositionByIndex((uint32_t)7, (uint32_t)6);
	parachuteText_->Initialize(parachuteTextModel_, viewProjection_, parachuteTextPosition);
	parachuteText_->SetMapChipField(mapChipField_);
	parachuteText_->SetShowText(true);

	parachuteTextModel2_ = Model::CreateFromOBJ("paratext2", true);
	parachuteText2_ = new ParachuteText();
	Vector3 parachuteTextPosition2 = mapChipField_->GetMapChipPositionByIndex((uint32_t)7, (uint32_t)5);
	parachuteText2_->Initialize(parachuteTextModel2_, viewProjection_, parachuteTextPosition2);
	parachuteText2_->SetMapChipField(mapChipField_);
	parachuteText2_->SetShowText(false);


#pragma endregion
	
}

void GameScene2::Update() {

	ChangePhase();
	switch (phase_)
	{

#pragma region FadeIn

	case Phase::kFadeIn:

		fade_->Update();
		player_->Update();
		skydome_->Update();
		cameraController_->Update();
		goal_->Update();
		MoveCameraHorizontally();
		if (parachuteText_->GetShowText())
		{
			parachuteText_->Update();
		}
		if (parachuteText2_->GetShowText())
		{
			parachuteText2_->Update();
		}
		ParachuteTextModelSwitch();
		grey_->Update();
		for (Wind* wind : winds_)
		{

			wind->Update();
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
		viewProjection_->matView = cameraController_->GetViewProjection().matView;
		viewProjection_->matProjection = cameraController_->GetViewProjection().matProjection;
		viewProjection_->TransferMatrix(); //this function keeps check of the movement of your objects. If this isnt written the object wont move
		break;
#pragma endregion

#pragma region Play

	case Phase::kPlay:

		player_->Update();
		player_->Movement();
		skydome_->Update();
		//fade_->SetCounter_(0.0f);
		MoveCameraHorizontally();
		goal_->Update();

		for (Spikes* spike : spikes_) { //create new Enemy enemy 

			spike->Update();
		}
		//parachute_->Update();
		//stageClearText_->Update();
		CheckAllCollisions();
		for (Wind* wind : winds_) 
		{

			wind->Update();
		}
		
		UsingParachute();
		WarningTriangle();
		checkpoint1_->Update();
		checkpoint2_->Update();
		
		if (!checkpoint2_->GetHasBeenTouchedPoint1() && !checkpoint1_->GetHasBeenTouched())
		{
			playHandle = 1;
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
		goal_->Update();

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
		//fade_->Update();

		break;

#pragma endregion

#pragma region StageClear

	case Phase::kStageClear:

		StageClearCamera();

		fade_->Update();
		skydome_->Update();
		goal_->Update();
		
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
		//for (Enemy* enemy : enemies_) { //create new Enemy enemy 
		//	enemy->Update();
		//}
		viewProjection_->matView = cameraController_->GetViewProjection().matView;
		viewProjection_->matProjection = cameraController_->GetViewProjection().matProjection;
		viewProjection_->TransferMatrix(); //this function keeps check of the movement of your objects. If this isnt written the object wont move

		break;

#pragma endregion

	default:
		break;
	}


}

void GameScene2::CheckAllCollisions()
{

	AABB aabb1;

	aabb1 = player_->GetAABB();
	
#pragma region player goal

	AABB aabb3 = goal_->GetAABB();

	if (IsCollision(aabb1, aabb3))
	{
		player_->OnCollisionGoal(goal_);
		goal_->OnCollision(player_);
		stageClear_ = true;
		if (audio_->IsPlaying(playHandle4) == 0 && playHandle4 == 1)
		{
			playHandle4 = audio_->PlayWave(audioHandle4_, false, 0.5f);
		}
	}

#pragma endregion


#pragma region player spike

	for (Spikes* spike : spikes_)
	{
		AABB aabb4 = spike->GetAABB();

		if (IsCollision(aabb1, aabb4) && spike->GetStruct() == SpikesStruct::Active)
		{
			player_->OnCollision(spike);
		}
	}

#pragma endregion

#pragma region player wind

	for (Wind* wind : winds_)
	{
		AABB aabb5 = wind->GetAABB();

		if (IsCollision(aabb1, aabb5) && parachute_->GetUsingParachute() && !player_->GetOnGround())
		{
			player_->OnCollision(wind_);
			inWind = true;

		}
	}
	

#pragma endregion

#pragma  region player checkpoint

	AABB aabb6 = checkpoint1_->GetAABB();

	if (IsCollision(aabb1, aabb6)) 
	{
		player_->OnCollision(checkpoint1_);
		checkpoint1_->OnCollision(player_);
		checkPoint2Reached_ = true;
		if (audio_->IsPlaying(playHandle) == 0 && playHandle == 1)
		{
			playHandle = audio_->PlayWave(audioHandle_, false, 0.1f);
		}
	}

	AABB aabb7 = checkpoint2_->GetAABB();

	if (IsCollision(aabb1, aabb7)) 
	{
		player_->OnCollision(checkpoint2_);
		checkpoint2_->OnCollisionFirst(player_);
		checkPoint1Reached_ = true;
		if (audio_->IsPlaying(playHandle) == 0 && playHandle == 1)
		{
			playHandle = audio_->PlayWave(audioHandle_, false, 0.1f);
		}
		
	}





#pragma endregion

}

bool GameScene2::IsCollision(const AABB& aabb1, const AABB& aabb2)
{
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z))
	{
		return true;
	}

	return false;
}

void GameScene2::ChangePhase()
{
	switch (phase_)
	{
	case Phase::kFadeIn:
		if (fade_->IsFinished() && shownText_)
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

void GameScene2::MoveCameraHorizontally()
{
	
	//ImGui::Begin("Test");
	//ImGui::Text("Y %f", player_->GetWorldTransform().translation_.y);
	//ImGui::Text("X %f", player_->GetWorldTransform().translation_.x);
	//ImGui::End();
	if (!inWind) 
	{
		if (player_->GetWorldTransform().translation_.y > 23.0f)
		{
			cameraRange.top = player_->GetWorldPosition().y - 9.0f;
		}
		else
		{
			cameraRange.top = 15.0f;
		}
	}
	else 
	{
		float playerPositionY = player_->GetWorldTransform().translation_.y;

		if (parachute_->GetUsingParachute() && cameraRange.top < maxCameraRangeTop)
		{
			if (cameraRange.top < playerPositionY + 10.0f)
			{
				cameraRange.top += 0.5f;
			}

			if (cameraRange.top >= playerPositionY + 10.0f)
			{
				stopUpCamera = true;
			}
			else
			{
				stopUpCamera = false;
			}
		}

		if (stopUpCamera)
		{
			cameraRange.top = min(playerPositionY + 10.0f, maxCameraRangeTop);
		}
	}
	
	if (player_->GetOnGround()) 
	{
		inWind = false;
	}
	
	cameraController_->SetMoveableArea(cameraRange);

	cameraController_->Update();
}

void GameScene2::WarningTriangle()
{
	if(player_->GetWorldTransform().translation_.x >= 86.0f && player_->GetWorldTransform().translation_.x <= 108.0f && player_->GetWorldTransform().translation_.y >= 153)
	{
		warningStart = true;
	}
	if (warningStart && warningLoops < 3) 
	{
		warningTimer++;
	}
	if (warningTimer >= 40) 
	{
		warningTimer = 0;
		warningLoops++;
		playHandle3 = 1;
	}

	if (warningLoops >= 3) 
	{
		for (Spikes* spike : spikes_)
		{
			
			spike->SetMoveRight(true);
		}
	}

	if (warningTimer >= 20) 
	{
		if (audio_->IsPlaying(playHandle3) == 0 && playHandle3 == 1)
		{
			playHandle3 = audio_->PlayWave(audioHandle3_, false, 0.2f);
		}
	}
	
}

void GameScene2::StageClearCamera()
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

void GameScene2::TransitionScene()
{
	sceneTransitionTimer++;

	if (sceneTransitionTimer >= 130)
	{
		isSceneTransitioning = true;
		sceneTransitionTimer = 130;
	}
}

void GameScene2::UsingParachute()
{

	if (Input::GetInstance()->PushKey(DIK_SPACE) && !player_->GetOnGround())
	{
		parachute_->SetUsingParachute(true);
	
	}
	else 
	{
		player_->SetFallSpeed(0.3f);
		parachute_->SetUsingParachute(false);


	}

	if (parachute_->GetUsingParachute()) 
	{
		player_->SetFallSpeed(0.09f);
		parachutePosition = player_->GetWorldPosition() + Vector3(0.0f, 1.5f, 0.0f);
		parachute_->Initialize(parachuteModel_, viewProjection_, parachutePosition);
		parachute_->Update();
	}

}

void GameScene2::ParachuteTextModelSwitch()
{
	

	if (parachuteTextCount_ >= 0) 
	{
		parachuteText_->SetShowText(true);
		parachuteText2_->SetShowText(false);

	}
	if (parachuteTextCount_ >= 1)
	{
		parachuteText_->SetShowText(false);
		parachuteText2_->SetShowText(true);
		//parachuteTextCount_ = 0;

	}

	if (Input::GetInstance()->TriggerKey(DIK_RETURN) && parachuteTextCount_ == 0 || Input::GetInstance()->TriggerKey(DIK_SPACE) && parachuteTextCount_ == 0)
	{
		parachuteTextCount_ = 1;
		delayBetweenText_ = 1;
	}

	if (delayBetweenText_ >= 1 && delayBetweenText_ <= 29)
	{
		delayBetweenText_++;
	}

	if (Input::GetInstance()->TriggerKey(DIK_RETURN) && delayBetweenText_ >= 29 || Input::GetInstance()->TriggerKey(DIK_SPACE) && delayBetweenText_ >= 29)
	{
		parachuteTextCount_ = 2;
		shownText_ = true;
	}

}

void GameScene2::Draw() {

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

		skydome_->Draw();
		for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
			for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
				if (!worldTransformBlock)
					continue;
				if (worldTransformBlock->translation_.x - player_->GetWorldTransform().translation_.x >= -60 && worldTransformBlock->translation_.x - player_->GetWorldTransform().translation_.x < 60 &&
					worldTransformBlock->translation_.y - player_->GetWorldTransform().translation_.y <= 40 && worldTransformBlock->translation_.y - player_->GetWorldTransform().translation_.y >= -30)
				{
					modelBlock_->Draw(*worldTransformBlock, *viewProjection_);
				}
			}
		}

		for (Spikes* spike : spikes_)
		{
			if (spike->GetWorldPosition().x - player_->GetWorldTransform().translation_.x >= -60 && spike->GetWorldPosition().x - player_->GetWorldTransform().translation_.x < 60 &&
				spike->GetWorldPosition().y - player_->GetWorldTransform().translation_.y <= 40 && spike->GetWorldPosition().y - player_->GetWorldTransform().translation_.y >= -30)
			{
				//Put spike.Draw in here
				spike->Draw();
			}
		}

		for (Wind* wind : winds_)
		{
			wind->Draw();
		}
		goal_->Draw();
		if (parachuteText_->GetShowText() && !shownText_)
		{
			parachuteText_->Draw();
		}
		if (parachuteText2_->GetShowText() && !shownText_)
		{
			parachuteText2_->Draw();
		}
		if (!shownText_) 
		{
			grey_->Draw();
		}
		fade_->Draw();
		
		break;

#pragma endregion

#pragma region Play
	case Phase::kPlay:
		checkpoint1_->Draw();
		checkpoint2_->Draw();
		player_->Draw();

		for (Spikes* spike : spikes_)
		{
			if(spike->GetWorldPosition().x - player_->GetWorldTransform().translation_.x >= -60 && spike->GetWorldPosition().x - player_->GetWorldTransform().translation_.x < 60 && 
			   spike->GetWorldPosition().y - player_->GetWorldTransform().translation_.y <= 40 && spike->GetWorldPosition().y - player_->GetWorldTransform().translation_.y >= -30)
			{
				//Put spike.Draw in here
				spike->Draw();
			}
		}
		if (Input::GetInstance()->PushKey(DIK_SPACE) && !player_->GetOnGround())
		{
			parachute_->Draw();
		}
		skydome_->Draw();
		goal_->Draw();
		for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
			for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
				if (!worldTransformBlock)
					continue;
				if(worldTransformBlock->translation_.x - player_->GetWorldTransform().translation_.x >= -60 && worldTransformBlock->translation_.x - player_->GetWorldTransform().translation_.x < 60 &&
					worldTransformBlock->translation_.y - player_->GetWorldTransform().translation_.y <= 40 && worldTransformBlock->translation_.y - player_->GetWorldTransform().translation_.y >= -30)
				{
					modelBlock_->Draw(*worldTransformBlock, *viewProjection_);

				}
			}
		}
		for (Wind* wind : winds_)
		{
			wind->Draw();
		}
		
		//stageClearText_->Draw();

		break;
#pragma endregion

#pragma region Death

	case Phase::kDeath:
		checkpoint1_->Draw();
		checkpoint2_->Draw();
		deathParticles_->Draw();
		skydome_->Draw();
		goal_->Draw();
		for (Wind* wind : winds_)
		{
			wind->Draw();
		}
		for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
			for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
				if (!worldTransformBlock)
					continue;
				if (worldTransformBlock->translation_.x - player_->GetWorldTransform().translation_.x >= -60 && worldTransformBlock->translation_.x - player_->GetWorldTransform().translation_.x < 60 &&
					worldTransformBlock->translation_.y - player_->GetWorldTransform().translation_.y <= 40 && worldTransformBlock->translation_.y - player_->GetWorldTransform().translation_.y >= -30)
				{
					modelBlock_->Draw(*worldTransformBlock, *viewProjection_);
				}
			}
		}
		for (Spikes* spike : spikes_)
		{
			if (spike->GetWorldPosition().x - player_->GetWorldTransform().translation_.x >= -60 && spike->GetWorldPosition().x - player_->GetWorldTransform().translation_.x < 60 &&
				spike->GetWorldPosition().y - player_->GetWorldTransform().translation_.y <= 40 && spike->GetWorldPosition().y - player_->GetWorldTransform().translation_.y >= -30)
			{
				//Put spike.Draw in here
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
		if (isSceneTransitioning)
		{


			skydome_->Draw();
			goal_->Draw();

			stageClearText_->Draw();
		}
		else 
		{
			skydome_->Draw();
			for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
				for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
					if (!worldTransformBlock)
						continue;
					if (worldTransformBlock->translation_.x - player_->GetWorldTransform().translation_.x >= -60 && worldTransformBlock->translation_.x - player_->GetWorldTransform().translation_.x < 60 &&
						worldTransformBlock->translation_.y - player_->GetWorldTransform().translation_.y <= 40 && worldTransformBlock->translation_.y - player_->GetWorldTransform().translation_.y >= -30)
					{
						modelBlock_->Draw(*worldTransformBlock, *viewProjection_);
					}
				}
			}

			for (Spikes* spike : spikes_)
			{
				if (spike->GetWorldPosition().x - player_->GetWorldTransform().translation_.x >= -60 && spike->GetWorldPosition().x - player_->GetWorldTransform().translation_.x < 60 &&
					spike->GetWorldPosition().y - player_->GetWorldTransform().translation_.y <= 40 && spike->GetWorldPosition().y - player_->GetWorldTransform().translation_.y >= -30)
				{
					//Put spike.Draw in here
					spike->Draw();
				}
			}
			checkpoint1_->Draw();
			checkpoint2_->Draw();

			goal_->Draw();

			for (Wind* wind : winds_)
			{
				wind->Draw();
			}
		}
		fade_->Draw();

		break;

#pragma endregion

	default:
		break;
	}



	//if (deathParticles_)
	//{
	//}

	//enemy_->Draw();

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	if (warningTimer >= 20 && warningLoops < 3)
	{
		sprite_->Draw();
	}
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene2::GenerateBlocks()
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
