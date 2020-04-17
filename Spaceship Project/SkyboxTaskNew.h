#pragma once
#include "Tasks/ObjectRotator.h"
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Meshes/MeshSphere.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Light.h"

#include "Spaceship Project/SkyboxTaskNew/Skybox.h"
#include "Tasks/Task.h"
#include "Spaceship Project/SkyboxTaskNew/CameraControllerNew.h"
#include "Spaceship Project/PlanetMaterial.h"


/**
* @brief Shows how to write bumped material.
* Key code is situated in the class MaterialBumpedSpecular.
*/
class SkyboxTaskNew: public Task
{
public:
	virtual ~SkyboxTaskNew() { }

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();
		this->scene = &scene;

		//Skybox
		TextureFilenames texture_filenames_test{
		"Space_down_test.jpg",
		"Space_up_test.jpg",
		"Space_left_test.jpg",
		"Space_right_test.jpg",
		"Space_front_test.jpg",
		"Space_back_test.jpg",
		};
		TextureFilenames texture_filenames{
		"Space_down.jpg",
		"Space_up.jpg",
		"Space_left.jpg",
		"Space_right.jpg",
		"Space_front.jpg",
		"Space_back.jpg",
		};

		TextureFilenames texture_space{
		"Space.jpg",
		"Space.jpg",
		"Space.jpg",
		"Space.jpg",
		"Space.jpg",
		"Space.jpg",
		};

		Skybox* SkyboxComponent = new Skybox(texture_space);
		{
			Object* SkyObject = new Object();
			SkyObject->m_pTransform = new Transform(0, 0, 0, 0, 0, 0, 1, 1, 1);
			SkyObject->AddComponent(SkyboxComponent);
			scene.AddObject(SkyObject);
			scene.SetSelectedObject(SkyObject);

		}

		Object* BodyObj = nullptr;
		{
			Camera* pCamera = new Camera();

			// Тело - у него родительский Transform. Rotation и Translation --> Должны вызывать Rotate и Translate у РОДИТЕЛЬСКОГО Transform
			Vector3 CamPos = Vector3(0.0f, 0.0f, 0.0f);//Vector3(0.0f, 0.5f, -5.0f);
			Vector3 CamScale = Vector3(20.0f, 10.0f, 0.0f);

			BodyObj = new Object();
			BodyObj->m_pTransform = new Transform(CamPos, CamScale);
			BodyObj->AddComponent(pCamera);

			CameraControllerNew * pCamCtrl = new CameraControllerNew(CamPos, CamScale);
			pCamCtrl->SetSkyboxComponent(SkyboxComponent);
			BodyObj->AddComponent(pCamCtrl);
			scene.SetCamera(pCamera);

		}

		Object * pObjSun = NULL;
		{
			Object * pObject = new Object();
			pObject->m_pMesh = new MeshSphere(30);//new MeshCube(3);
			pObject->m_pTransform = new Transform();

			pObject->m_pMaterial = new PlanetMaterial(
				Vector3(0, 0, 0),
				TEXTURE_FILTER_MODE_TRILINEAR,
				"ShaderEarth",
				"ShaderEarth",
				/*"Earth_Albedo.jpg"*/"sun.jpg"
			);

			pObject->AddComponent(new ObjectRotator(0, 45, 0));
			scene.AddObject(pObject);
			pObjSun = pObject;
		}

		// Object #2 - mercury
		/*Object * pObjMercury = NULL;
		{
			Object * pObject = new Object();
			pObject->m_pMesh = new MeshSphere(30);
			pObject->m_pTransform = new Transform(constants::sun_mercury_dist, 0, 0, 0, 0, 1, 0.5, 0.5, 0.5);
			pObject->m_pMaterial = new PlanetMaterial(
				Vector3(0, 0, 0),
				TEXTURE_FILTER_MODE_TRILINEAR,
				"ShaderEarth",
				"ShaderEarth",
				/*"Earth_Albedo.jpg""mercury.jpg"
			);
			pObject->AddComponent(new ObjectRotator(0, 100, 0));
			pObject->m_pTransform->SetParent(pObjSun->m_pTransform);
			scene.AddObject(pObject);
			pObjMercury = pObject;
		}*/

		
		unsigned char UP = 'w';
		unsigned char DOWN = 's';
		unsigned char LEFT = 'a';
		unsigned char RIGHT = 'd';
		unsigned char ACCELERATE = 'z';
		GL20Input::SetLetterKeyUp(UP);
		GL20Input::SetLetterKeyUp(DOWN);
		GL20Input::SetLetterKeyUp(LEFT);
		GL20Input::SetLetterKeyUp(RIGHT);
		GL20Input::SetLetterKeyUp(ACCELERATE);
	}

	virtual void Update()
	{
		//Vector3 CamPos = SceneUtils::GetEyePosition();
		//Object* SkyObj = this->scene->GetSelectedObject();
		//SkyObj->Update();
		
	}

private:
	Scene* scene = nullptr;
};
