#include "WorldTransform.h"

void WorldTransform::UpdateMatrix()
{
	//combine scale, rotation and translation
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);
	
	TransferMatrix();
}
