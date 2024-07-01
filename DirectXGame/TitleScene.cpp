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
	Vector3 playerPosition = { 1.0f, 1.0f, 1.0f };
	titlePlayer_->Initialize(playerModel_, viewProjection_, playerPosition);

	textModel_ = Model::CreateFromOBJ("title", true);
	titleText_ = new TitleText();
	Vector3 textPosition = { 0.0f, 1.0f, 1.0f };
	titleText_->Initialize(textModel_, viewProjection_, playerPosition);


}

void TitleScene::Update()
{
	titlePlayer_->Update();
	titleText_->Update();
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
	//titlePlayer_->Draw();
	titleText_->Draw();
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
	
}
