#include "Audio.h"
#include "AxisIndicator.h"
#include "DirectXCommon.h"
#include "GameScene.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "WinApp.h"
#include "TitleScene.h"
#include "GameScene2.h"

GameScene* gameScene = nullptr;
GameScene2* gameScene2 = nullptr;
TitleScene* titleScene = nullptr;

void ChangeScene();

void UpdateScene();

void DrawScene();

enum class Scene
{
	kUnknown = 0,
	kTitle,
	kGame,
	kGame2,
};

Scene scene = Scene::kUnknown;


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;
	AxisIndicator* axisIndicator = nullptr;
	PrimitiveDrawer* primitiveDrawer = nullptr;

	
	// ゲームウィンドウの作成
	win = WinApp::GetInstance();
	win->CreateGameWindow(L"GC2A_05_ジュットハイマー_ダニエル_AL3");

	// DirectX初期化処理
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(win);

#pragma region 汎用機能初期化
	// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	imguiManager->Initialize(win, dxCommon);

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();

	// オーディオの初期化
	audio = Audio::GetInstance();
	audio->Initialize();

	// テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize(dxCommon->GetDevice());
	TextureManager::Load("white1x1.png");

	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 3Dモデル静的初期化
	Model::StaticInitialize();

	// 軸方向表示初期化
	axisIndicator = AxisIndicator::GetInstance();
	axisIndicator->Initialize();

	primitiveDrawer = PrimitiveDrawer::GetInstance();
	primitiveDrawer->Initialize();
#pragma endregion

	// ゲームシーンの初期化
	scene = Scene::kGame;

	gameScene = new GameScene();
	gameScene->Initialize();

	gameScene2 = new GameScene2();
	gameScene2->Initialize();
	
	titleScene = new TitleScene();
	titleScene->Initialize();

	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		// ImGui受付開始
		imguiManager->Begin();
		// 入力関連の毎フレーム処理
		input->Update();
		// ゲームシーンの毎フレーム処理
		//gameScene->Update();
		// ゲームタイトルの毎フレーム処理
		//titleScene->Update();

		ChangeScene();

		UpdateScene();
		// 軸表示の更新
		axisIndicator->Update();
		// ImGui受付終了
		imguiManager->End();

		// 描画開始
		dxCommon->PreDraw();
		// ゲームシーンの描画
		//gameScene->Draw();
		// ゲームタイトルの描画
		//titleScene->Draw();
		
		DrawScene();

		// 軸表示の描画
		axisIndicator->Draw();
		// プリミティブ描画のリセット
		primitiveDrawer->Reset();
		// ImGui描画
		imguiManager->Draw();
		// 描画終了
		dxCommon->PostDraw();
	}

	// 各種解放
	delete gameScene;
	delete gameScene2;
	delete titleScene;
	// 3Dモデル解放
	Model::StaticFinalize();
	audio->Finalize();
	// ImGui解放
	imguiManager->Finalize();

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();

	return 0;
}

void ChangeScene()
{
	switch (scene)
	{
	case Scene::kUnknown:
		break;
	case Scene::kTitle:
		if (titleScene->GetIsFinished()) 
		{
			scene = Scene::kGame;
			delete titleScene;
			titleScene = nullptr;
			gameScene = new GameScene;
			gameScene->Initialize();
		}
		break;
	case Scene::kGame:
		if (gameScene->GetIsFinished()) 
		{
			
			scene = Scene::kGame;
			delete gameScene;
			gameScene = nullptr;
			gameScene = new GameScene;
			gameScene->Initialize();
			//titleScene = new TitleScene;
			//titleScene->Initialize();
		}

		if (gameScene->GetGoToNextStage()) 
		{
			scene = Scene::kGame2;
			delete gameScene;
			gameScene = nullptr;
			gameScene2 = new GameScene2;
			gameScene2->Initialize();
			/*scene = Scene::kGame2;
			delete gameScene;
			gameScene = nullptr;
			gameScene2 = new GameScene2;
			gameScene2->Initialize();*/
		}

		break;

	case Scene::kGame2:
		if (gameScene2->GetIsFinished())
		{

			scene = Scene::kGame2;
			delete gameScene2;
			gameScene2 = nullptr;
			gameScene2 = new GameScene2;
			gameScene2->Initialize();
		}

		break;
	default:
		break;
	}
}

void UpdateScene()
{
	switch (scene)
	{
	case Scene::kUnknown:
		break;
	case Scene::kTitle:
		titleScene->Update();
		break;
	case Scene::kGame:
		gameScene->Update();
		break;
	case Scene::kGame2:
		gameScene2->Update();
		break;
	default:
		break;
	}
}

void DrawScene()
{
	switch (scene)
	{
	case Scene::kUnknown:
		break;
	case Scene::kTitle:
		titleScene->Draw();
		break;
	case Scene::kGame:
		gameScene->Draw();
		break;
	case Scene::kGame2:
		gameScene2->Draw();
	default:
		break;
	}
}
