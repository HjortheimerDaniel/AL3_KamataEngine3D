#include "StageManager.h"
#include "ImGuiManager.h"

StageManager::~StageManager()
{
	delete gameScene;
	delete gameScene2;
	delete titleScene;
	delete gameClearScreen;
}

void StageManager::Initialize()
{
	audio_ = Audio::GetInstance();

#pragma region audio

	audioHandle_ = audio_->LoadWave("Quiet_Intention.mp3");
	playHandle = 1;

#pragma endregion

	scene = Scene::kGame;

	gameScene = new GameScene();
	gameScene->Initialize();

	gameScene2 = new GameScene2();
	gameScene2->PlayerStartPos();
	gameScene2->Initialize();

	titleScene = new TitleScene();
	titleScene->Initialize();

	gameClearScreen = new GameClearScreen();
	gameClearScreen->Initialize();
}

void StageManager::Update()
{
	if (audio_->IsPlaying(playHandle) == 0 && playHandle == 1)
	{
		playHandle = audio_->PlayWave(audioHandle_, true, 0.7f);
	}
	if(scene == Scene::kGame2)
	{
		ConstantThingies();
	}
	ChangeScene();
	UpdateScene();
}

void StageManager::ConstantThingies()
{
	if (gameScene2->GetCheckpoint2Reached())
	{
		checkpoint2 = true;
	}
	if (gameScene2->GetCheckpoint1Reached())
	{
		checkpoint1 = true;
	}
	if (gameScene2->GetShownText())
	{
		shownParachuteText = true;
	}
	gameScene2->SetShownText(shownParachuteText);
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
			if (checkpoint2)
			{
				gameScene2->PlayerCheckpoint2Pos();
			}
			else if(checkpoint1 && !checkpoint2)
			{
				gameScene2->PlayerCheckpoint1Pos();
			}
			else 
			{
				gameScene2->PlayerStartPos();
			}
			gameScene2->Initialize();
		}
		if (gameScene2->GetGoToNextStage()) 
		{
			scene = Scene::kGameClear;
			delete gameScene2;
			gameScene2 = nullptr;
			gameClearScreen = new GameClearScreen;
			gameClearScreen->Initialize();
		}

		break;
	case Scene::kGameClear:


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
	case Scene::kGameClear:
		gameClearScreen->Update();
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
		break;
	case Scene::kGameClear:
		gameClearScreen->Draw();
	default:
		break;
	}
}


