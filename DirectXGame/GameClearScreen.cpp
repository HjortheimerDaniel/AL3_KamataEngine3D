#include "GameClearScreen.h"

GameClearScreen::GameClearScreen()
{
}

GameClearScreen::~GameClearScreen()
{
	delete titlePlayer_;
	delete viewProjection_;
	delete clearText_;
	delete fade_;
	delete firework_;
	for (GameClearText* titleText_ : gameClearTexts)
	{
		delete titleText_;
	}
	gameClearTexts.clear();

	for (Fireworks* firework : fireworks)
	{
		delete firework;
	}
	fireworks.clear();
}

void GameClearScreen::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	viewProjection_ = new ViewProjection();
	viewProjection_->Initialize();
	viewProjection_->translation_ = { 0,0,-100 };
	viewProjection_->UpdateViewMatrix();
	viewProjection_->UpdateProjectionMatrix();
	viewProjection_->TransferMatrix();


	playerModel_ = Model::CreateFromOBJ("player", true);
	titlePlayer_ = new TitlePlayer();
	Vector3 playerPosition = { 1.0f, -5.0f, 1.0f };
	titlePlayer_->Initialize(playerModel_, viewProjection_, playerPosition);

	for (int32_t i = 0; i < MAXTHANKYOU; i++)
	{
		GameClearText* newClearText_ = new GameClearText();
		Vector3 textPos = textPos_[i];
		newClearText_->Initialize(textModel[i], viewProjection_, textPos, startPos[i], startUpdate[i], amplitude[i]);
		gameClearTexts.push_back(newClearText_);
	}

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Status::FadeIn, duration_);

	fireworksModel_ = Model::CreateFromOBJ("fireworks", true);
	for (uint32_t i = 0; i < MAXFIREWORKS; i++)
	{
		Fireworks* newFireworks_ = new Fireworks();
		Vector3 fireWorksPosition = fireworksPos_[i];
		newFireworks_->Initialize(fireworksModel_, viewProjection_, fireWorksPosition, fireworksColor[i],startFireworkUpdate[i]);
		fireworks.push_back(newFireworks_);

	}
	
	modelSkydome_ = Model::CreateFromOBJ("skydome", true); //find the model inside the skydome folder
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_, viewProjection_);
}

void GameClearScreen::Update()
{
	fade_->Update();
	titlePlayer_->Update();
	for (Fireworks* firework : fireworks)
	{

		firework->Update();
	}
	
	for (GameClearText* titleText_ : gameClearTexts)
	{
		titleText_->Update();
	}

	if (Input::GetInstance()->PushKey(DIK_SPACE) && fade_->IsFinished())
	{
		clicks_ = 1;
		fade_->Start(Status::FadeOut, duration_);
	}

	if (fade_->IsFinished() && clicks_ != 0) {
		finished_ = true;
	}

	skydome_->Update();
}

void GameClearScreen::Draw()
{
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
	titlePlayer_->Draw();
	for (Fireworks* firework : fireworks)
	{
		firework->Draw();
	}
	for (GameClearText* titleText_ : gameClearTexts)
	{
		titleText_->Draw();
	}
	// 3Dオブジェクト描画後処理

	skydome_->Draw();

	fade_->Draw();

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
}
