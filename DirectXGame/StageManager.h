#pragma once
#include "TitleScene.h"
#include "GameScene2.h"
#include "GameScene.h"

class StageManager
{
public:

	~StageManager();

	void Initialize();

	void Update();

	void ChangeScene();

	void UpdateScene();

	void DrawScene();

private:

	Scene scene = Scene::kUnknown;
	GameScene* gameScene = nullptr;
	GameScene2* gameScene2 = nullptr;
	TitleScene* titleScene = nullptr;
	bool checkpoint1 = false;
	bool checkpoint2 = false;
};

