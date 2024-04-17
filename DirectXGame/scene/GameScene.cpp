#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() {

	delete sprite_;
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("emil.jpg");
	//スプライトの生成
	sprite_ = Sprite::Create(textureHandle_, {500, 50});
	model_ = Model::Create();
	worldTransform_.Initialize();
	viewProjection_.Initialize();
	soundDataHandle_ = audio_->LoadWave("BGM/ToABorder.wav");
	//audio_->PlayWave(soundDataHandle_); //if you dont intend on stopping the music, you can use this
	voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);

	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);
	debugCamera_ = new DebugCamera(1280, 720);

	//show the axis
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
	
}

void GameScene::Update() {

	//スプライトの今の座標を取得
	Vector2 position = sprite_->GetPosition();
	//if (position.x <= 600) {

	//スプライトの移動

	position.x += 2.0f; 
	//}
	position.y += 1.0f;

	//移動した座標をスプライトに反映
	sprite_->SetPosition(position);
	
	if (input_->TriggerKey(DIK_SPACE)) { //Stop the music playing
		audio_->StopWave(voiceHandle_);
		//voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);
	}
	ImGui::Begin("Debug1");
	ImGui::Text("Kamata Tarou %d.%d.%d", 2050, 12, 31);
	ImGui::InputFloat3("InputFloat3", inputFloat3);
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f); //Can use slider to change the value, in this case between 0 and 1
	ImGui::ShowDemoWindow();
	ImGui::End();

	debugCamera_->Update();
	
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
	//sprite_->Draw(); //This must be written between PreDraw and PostDraw

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
	
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_); //this one made the model into a movable 3D object

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
	for (int i = 0; i < 20; i++)
	{
		PrimitiveDrawer::GetInstance()->DrawLine3d({ (float)i+10,0,0 }, { (float)i+10,10,0 }, { 1.0f,2.0f,0.0f,9.0f }); //The X and Y axis, it starts in the middle of the window? and the last Vector 4 is RGBA
	}
	for (int i = 0; i < 11; i++)
	{
		PrimitiveDrawer::GetInstance()->DrawLine3d({ 10,(float)i,0 }, { 29,(float)i,0 }, { 1.0f,2.0f,0.0f,9.0f }); 

	}


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
