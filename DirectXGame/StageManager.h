#pragma once
#include "TitleScene.h"
#include "GameScene2.h"
#include "GameScene3.h"
#include "GameScene.h"
#include "GameClearScreen.h"
#include "Audio.h"
#include "GreyPauseVeil.h"

class StageManager
{
public:

	~StageManager();

	void Initialize();

	void Update();

	void ConstantThingies();

	void ChangeScene();

	void Pause();

	void UpdateScene();

	void DrawScene();

private:

	Scene scene = Scene::kUnknown;
	GameScene* gameScene = nullptr;
	GameScene2* gameScene2 = nullptr;
	GameScene3* gameScene3 = nullptr;
	TitleScene* titleScene = nullptr;
	GreyPauseVeil* greyPauseVeil = nullptr;
	GameClearScreen* gameClearScreen = nullptr;
	bool checkpoint1 = false;
	bool checkpoint2 = false;
	bool shownParachuteText = false;
	uint32_t audioHandle_ = 0;
	uint32_t playHandle = {};
	Audio* audio_ = nullptr;
	bool isPaused = false;

};

