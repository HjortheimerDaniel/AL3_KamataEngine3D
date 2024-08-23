#include "StageManager.h"
#include "ImGuiManager.h"

StageManager::~StageManager()
{
	delete gameScene;
	delete gameScene2;
	delete titleScene;
}

void StageManager::Initialize()
{
	scene = Scene::kGame2;

	gameScene = new GameScene();
	gameScene->Initialize();

	gameScene2 = new GameScene2();
	gameScene2->PlayerStartPos();
	gameScene2->Initialize();

	titleScene = new TitleScene();
	titleScene->Initialize();
}

void StageManager::Update()
{
	ImGui::Begin("bool");
	ImGui::Text("%d", checkpoint);
	ImGui::End();
	if (gameScene2->GetCheckpointReached()) 
	{
		checkpoint = true;
	}
	ChangeScene();
	UpdateScene();
}

void StageManager::ChangeScene()
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
			gameScene2->PlayerStartPos();
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
			if (checkpoint)
			{
				gameScene2->PlayerCheckpointPos();
			}
			else 
			{
				gameScene2->PlayerStartPos();
			}
			gameScene2->Initialize();
		}

		break;
	default:
		break;
	}
}

void StageManager::UpdateScene()
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

void StageManager::DrawScene()
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


