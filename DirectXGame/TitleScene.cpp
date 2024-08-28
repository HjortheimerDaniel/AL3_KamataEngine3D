#include "TitleScene.h"
#include "TextureManager.h"
#include "imgui.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	delete titlePlayer_;
	delete viewProjection_;
	delete titleText_;
	delete fade_;
}

void TitleScene::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	viewProjection_ = new ViewProjection();
	viewProjection_->Initialize();
	viewProjection_->translation_ = {0,0,-100};
	viewProjection_->UpdateViewMatrix();
	viewProjection_->UpdateProjectionMatrix();
	viewProjection_->TransferMatrix();


	playerModel_ = Model::CreateFromOBJ("player", true);
	titlePlayer_ = new TitlePlayer();
	Vector3 playerPosition = { 1.0f, -5.0f, 1.0f };
	titlePlayer_->Initialize(playerModel_, viewProjection_, playerPosition, true, false, false);

	titlePlayer2_ = new TitlePlayer();
	Vector3 playerPosition2 = { 0.0f, 15.0f, 1.0f };
	titlePlayer2_->Initialize(playerModel_, viewProjection_, playerPosition2, false, true, false);

	titlePlayer3_ = new TitlePlayer();
	Vector3 playerPosition3 = { 0.0f, -25.0f, 1.0f };
	titlePlayer3_->Initialize(playerModel_, viewProjection_, playerPosition3, false, false, true);

	textModel_ = Model::CreateFromOBJ("titleMapchip", true);
	titleText_ = new TitleText();
	Vector3 textPosition = { -30.0f, 3.0f, 1.0f };
	titleText_->Initialize(textModel_, viewProjection_, textPosition, true);
	
	textModel2_ = Model::CreateFromOBJ("title3DLand", true);
	titleText2_ = new TitleText();
	Vector3 textPosition2 = { 0.0f, 3.0f, 1.0f };
	titleText2_->Initialize(textModel2_, viewProjection_, textPosition2,true);

	textModel3_ = Model::CreateFromOBJ("controlstext", true);
	titleText3_ = new TitleText();
	Vector3 textPosition3 = { -16.0f, 30.0f, 1.0f };
	titleText3_->Initialize(textModel3_, viewProjection_, textPosition3,false);

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Status::FadeIn, duration_);

	modelSkydome_ = Model::CreateFromOBJ("skydome", true); //find the model inside the skydome folder
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_, viewProjection_);
}

void TitleScene::Update()
{
	ImGui::Begin("clicks");
	ImGui::Text("%d", clicks_);
	ImGui::End();
	fade_->Update();
	skydome_->Update();
	switch (clicks_)
	{
	case 0:
		titlePlayer_->Update();
		titleText_->Update();
		titleText2_->Update();
		break;
	case 1:
		titlePlayer2_->Update();
		titlePlayer3_->Update();
		titleText3_->Update();
		break;

	default:
		break;
	}
	if (Input::GetInstance()->TriggerKey(DIK_SPACE) && fade_->IsFinished()) 
	{
		clicks_ ++;
	}

	if (clicks_ == 2 && Input::GetInstance()->TriggerKey(DIK_SPACE))
	{
		fade_->Start(Status::FadeOut, duration_);
	}

	if (fade_->IsFinished() && clicks_ == 2) {
		finished_ = true;
	}
}

void TitleScene::Draw()
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
	switch (clicks_)
	{
	case 0: 
		titlePlayer_->Draw();
		titleText_->Draw();
		titleText2_->Draw();
		break;
	case 1:
		titlePlayer2_->Draw();
		titlePlayer3_->Draw();
		titleText3_->Draw();
	default:
		break;
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
