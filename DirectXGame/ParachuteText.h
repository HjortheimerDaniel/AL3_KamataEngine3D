#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "cassert"

class MapChipField;

class ParachuteText
{
public:

	ParachuteText();

	~ParachuteText();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; };

	void SetShowText(bool showText) { showText_ = showText; };

	bool GetShowText() { return showText_; };

	void Update();

	void Draw();

private:

	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	MapChipField* mapChipField_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;
	static inline const float textSize = 3.0f;
	bool showText_ = false;

};

