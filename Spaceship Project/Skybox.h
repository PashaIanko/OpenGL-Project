#pragma once
#include "Tasks/ObjectRotator.h"
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Meshes/MeshSphere.h"
#include "GraphicsEngine/Meshes/MeshQuad.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Light.h"

#include "Spaceship Project/SkyboxTaskNew/SkyboxMaterialNew.h"
#include "Tasks/Task.h"


/**
* @brief Shows how to write bumped material.
* Key code is situated in the class MaterialBumpedSpecular.
*/
class Skybox : public Component {

public:
	Skybox() {

	}
	Skybox(const struct TextureFilenames& texture_filenames_){
		texture_filenames = texture_filenames_;
	}
	virtual ~Skybox() {

	}
	virtual void Init(Object* pObject) {
		m_pObject = pObject;
		Scene& scene = Application::Instance().GetScene();

		//Skybox - filepaths are in private fiels

		
		const double cube_size = 3;

		//dist from cube center to sides
		const double dist_from_center = cube_size / 2.0f;

		//Front
		{
			front = new Object();
			//front 
			front->m_pMesh = new MeshQuad();
			front->m_pTransform = new Transform(0, 0, dist_from_center, -90, 0, 0, cube_size, cube_size, cube_size);
			front->m_pMaterial = new SkyboxMaterialNew(
				Vector3(0, 0, 0),
				TEXTURE_FILTER_MODE_TRILINEAR,
				"ShaderSkyboxNew",
				"ShaderSkyboxNew",
				texture_filenames.front,
				RenderQueue::SKYBOX
			);
			scene.AddObject(front);
		}

		//Back
		{
			back = new Object();
			back->m_pMesh = new MeshQuad();
			back->m_pTransform = new Transform(0, 0, -dist_from_center, 90, 0, 0, cube_size, cube_size, cube_size);
			back->m_pMaterial = new SkyboxMaterialNew(
				Vector3(0, 0, 0),
				TEXTURE_FILTER_MODE_TRILINEAR,
				"ShaderSkyboxNew",
				"ShaderSkyboxNew",
				texture_filenames.back,
				RenderQueue::SKYBOX
			);
			scene.AddObject(back);
		}

		//left
		{
			left = new Object();
			left->m_pMesh = new MeshQuad();
			left->m_pTransform = new Transform(-dist_from_center, 0, 0, 0, 0, -90, cube_size, cube_size, cube_size);
			left->m_pMaterial = new SkyboxMaterialNew(
				Vector3(0, 0, 0),
				TEXTURE_FILTER_MODE_TRILINEAR,
				"ShaderSkyboxNew",
				"ShaderSkyboxNew",
				texture_filenames.left,
				RenderQueue::SKYBOX
			);
			scene.AddObject(left);
		}

		////right
		{
			right = new Object();
			right->m_pMesh = new MeshQuad();
			right->m_pTransform = new Transform(dist_from_center, 0, 0, 0, 0, 90, cube_size, cube_size, cube_size);
			right->m_pMaterial = new SkyboxMaterialNew(
				Vector3(0, 0, 0),
				TEXTURE_FILTER_MODE_TRILINEAR,
				"ShaderSkyboxNew",
				"ShaderSkyboxNew",
				texture_filenames.right,
				RenderQueue::SKYBOX
			);
			scene.AddObject(right);
		}

		//top
		{
			up = new Object();
			up->m_pMesh = new MeshQuad();
			up->m_pTransform = new Transform(0, dist_from_center, 0, 0, 0, 180, cube_size, cube_size, cube_size);
			up->m_pMaterial = new SkyboxMaterialNew(
				Vector3(0, 0, 0),
				TEXTURE_FILTER_MODE_TRILINEAR,
				"ShaderSkyboxNew",
				"ShaderSkyboxNew",
				texture_filenames.up,
				RenderQueue::SKYBOX
			);
			scene.AddObject(up);
		}

		////bottom
		{
			bottom = new Object();
			bottom->m_pMesh = new MeshQuad();
			bottom->m_pTransform = new Transform(0, -dist_from_center, 0, 0, 0, 0, cube_size, cube_size, cube_size);
			bottom->m_pMaterial = new SkyboxMaterialNew(
				Vector3(0, 0, 0),
				TEXTURE_FILTER_MODE_TRILINEAR,
				"ShaderSkyboxNew",
				"ShaderSkyboxNew",
				texture_filenames.bottom,
				RenderQueue::SKYBOX
			);
			scene.AddObject(bottom);
		}



	}

	void Translate(Vector3 vec)
	{
		up->m_pTransform->Translate(vec);
		bottom->m_pTransform->Translate(vec);
		left->m_pTransform->Translate(vec);
		right->m_pTransform->Translate(vec);
		front->m_pTransform->Translate(vec);
		back->m_pTransform->Translate(vec);
	}

private:
	TextureFilenames texture_filenames{};

	Object* up = nullptr;
	Object* bottom = nullptr;
	Object* left = nullptr;
	Object* right = nullptr;
	Object* back = nullptr;
	Object* front = nullptr;
};