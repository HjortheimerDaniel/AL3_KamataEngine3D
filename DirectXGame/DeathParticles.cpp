#include "DeathParticles.h"
#include "imgui.h"


DeathParticles::DeathParticles()
{
}

DeathParticles::~DeathParticles()
{
}

void DeathParticles::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position)
{
	assert(model);
	model_ = model;
	//textureHandle_ = textureHandle; 
	viewProjection_ = viewProjection;
	for (auto& worldTransform : worldTransforms_ )
	{

		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}
	worldTransformParticles_.resize(kNumParticles);
	
	
	for (uint32_t j = 0; j < kNumParticles; j++)
	{
		WorldTransform* worldTransform = new WorldTransform();
		worldTransform->Initialize();
		worldTransform->translation_ = position; // Set initial position
		worldTransformParticles_[j] = worldTransform;
	}
	

}

void DeathParticles::Update()
{
	for (WorldTransform* worldTransformDP : worldTransformParticles_) { //everything this is inside worldTransformParticles_ gets copied into worldTransformBlockLine, and every time a new thing goes inside we go inside the for function and then repeat

			worldTransformDP->matWorld_ = MakeAffineMatrix(worldTransformDP->scale_, worldTransformDP->rotation_, worldTransformDP->translation_);
			worldTransformDP->TransferMatrix();
			worldTransformDP->UpdateMatrix();
	}

	ImGui::Begin("Window");
	ImGui::Text("size %d", worldTransformParticles_.size());
	ImGui::End();
}

void DeathParticles::Draw()
{
	for (WorldTransform* worldTransformDP : worldTransformParticles_) {

			model_->Draw(*worldTransformDP, *viewProjection_);
		
	}
}
