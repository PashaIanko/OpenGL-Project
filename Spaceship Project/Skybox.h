#pragma once
#include "Tasks/ObjectRotator.h"
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Meshes/MeshSphere.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Light.h"

//#include "Spaceship Project/TextureFilenames.h"
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
			Object * pObject = new Object();
			pObject->m_pMesh = new MeshQuad();
			pObject->m_pTransform = new Transform(0, 0, dist_from_center, -90, 0, 0, cube_size, cube_size, cube_size);
			pObject->m_pMaterial = new SkyboxMaterialNew(
				Vector3(0, 0, 0),
				TEXTURE_FILTER_MODE_TRILINEAR,
				"ShaderSkyboxNew",
				"ShaderSkyboxNew",
				texture_filenames.front
			);
			scene.AddObject(pObject);
		}

		//Back
		{
			Object * pObject = new Object();
			pObject->m_pMesh = new MeshQuad();
			pObject->m_pTransform = new Transform(0, 0, -dist_from_center, 90, 0, 0, cube_size, cube_size, cube_size);
			pObject->m_pMaterial = new SkyboxMaterialNew(
				Vector3(0, 0, 0),
				TEXTURE_FILTER_MODE_TRILINEAR,
				"ShaderSkyboxNew",
				"ShaderSkyboxNew",
				texture_filenames.back
			);
			scene.AddObject(pObject);
		}

		//left
		{
			Object * pObject = new Object();
			pObject->m_pMesh = new MeshQuad();
			pObject->m_pTransform = new Transform(-dist_from_center, 0, 0, 0, 0, -90, cube_size, cube_size, cube_size);
			pObject->m_pMaterial = new SkyboxMaterialNew(
				Vector3(0, 0, 0),
				TEXTURE_FILTER_MODE_TRILINEAR,
				"ShaderSkyboxNew",
				"ShaderSkyboxNew",
				texture_filenames.left
			);
			scene.AddObject(pObject);
		}

		////right
		{
			Object * pObject = new Object();
			pObject->m_pMesh = new MeshQuad();
			pObject->m_pTransform = new Transform(dist_from_center, 0, 0, 0, 0, 90, cube_size, cube_size, cube_size);
			pObject->m_pMaterial = new SkyboxMaterialNew(
				Vector3(0, 0, 0),
				TEXTURE_FILTER_MODE_TRILINEAR,
				"ShaderSkyboxNew",
				"ShaderSkyboxNew",
				texture_filenames.right
			);
			scene.AddObject(pObject);
		}

		//top
		{
			Object * pObject = new Object();
			pObject->m_pMesh = new MeshQuad();
			pObject->m_pTransform = new Transform(0, dist_from_center, 0, 0, 0, 180, cube_size, cube_size, cube_size);
			pObject->m_pMaterial = new SkyboxMaterialNew(
				Vector3(0, 0, 0),
				TEXTURE_FILTER_MODE_TRILINEAR,
				"ShaderSkyboxNew",
				"ShaderSkyboxNew",
				texture_filenames.up
			);
			scene.AddObject(pObject);
		}

		////bottom
		{
			Object * pObject = new Object();
			pObject->m_pMesh = new MeshQuad();
			pObject->m_pTransform = new Transform(0, -dist_from_center, 0, 0, 0, 0, cube_size, cube_size, cube_size);
			pObject->m_pMaterial = new SkyboxMaterialNew(
				Vector3(0, 0, 0),
				TEXTURE_FILTER_MODE_TRILINEAR,
				"ShaderSkyboxNew",
				"ShaderSkyboxNew",
				texture_filenames.bottom
			);
			scene.AddObject(pObject);
		}



	}

private:
	TextureFilenames texture_filenames{};
};