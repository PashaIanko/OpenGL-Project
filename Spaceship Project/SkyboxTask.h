#pragma once
#include "Tasks/ObjectRotator.h"
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Meshes/MeshSphere.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Light.h"

#include "Spaceship Project/SkyboxMaterial.h"

#include "Tasks/Task.h"


/**
* @brief Shows how to write bumped material.
* Key code is situated in the class MaterialBumpedSpecular.
*/
class SkyboxTask: public Task
{
public:
	virtual ~SkyboxTask() { }

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();
	
		// Camera - Предыдущий код
		/*{
			Object * pCameraObj = new Object();
			pCameraObj->m_pTransform = new Transform( Vector3(0.0f, 0.0f,-2.5f),
				Vector3(0.0f, 0.0f, 0.0f));
			Camera * pCamera = new Camera();
			pCameraObj->AddComponent( pCamera );

			scene.SetCamera( pCamera );
		}*/

		{
			Camera* pCamera = new Camera();

			// Тело - у него родительский Transform. Rotation и Translation --> Должны вызывать Rotate и Translate у РОДИТЕЛЬСКОГО Transform
			Vector3 CamPos = Vector3(0.0f, 0.0f, 0.0f);//Vector3(0.0f, 0.5f, -5.0f);
			Vector3 CamScale = Vector3(20.0f, 10.0f, 0.0f);

			Object* BodyObj = new Object();
			BodyObj->m_pTransform = new Transform(CamPos, CamScale);
			BodyObj->AddComponent(pCamera);

			CameraController * pCamCtrl = new CameraController(CamPos, CamScale);
			BodyObj->AddComponent(pCamCtrl);
			scene.SetCamera(pCamera);

		}

		// Object #1 - Cube Map
		{
			Object * pObject1 = new Object();

			pObject1->m_pMesh = new MeshCube();// MeshSphere(30);
			const int universe_scale = -3;
			pObject1->m_pTransform	= new Transform(0,0,0, 0,0,0, universe_scale, universe_scale, universe_scale);
			
			TextureFilenames texture_filenames{
			"Space_down.jpg",
			"Space_up.jpg",
			"Space_left.jpg",
			"Space_right.jpg",
			"Space_front.jpg",
			"Space_back.jpg",
			};
			TextureFilenames texture_filenames_test{
			"Space_down_test.jpg",
			"Space_up_test.jpg",
			"Space_left_test.jpg",
			"Space_right_test.jpg",
			"Space_front_test.jpg",
			"Space_back_test.jpg",
			};
			pObject1->m_pMaterial = new SkyboxMaterial(
				Vector3(0, 0, 0),
				TEXTURE_FILTER_MODE_TRILINEAR,
				"ShaderCube",
				"ShaderCube",
				"Earth_Albedo.jpg",
				/*texture_filenames*/ texture_filenames_test
			);
			//pObject1->AddComponent( new ObjectRotator(0, 80, 0) );
						
			scene.AddObject( pObject1 );
		}

		// Light source #1 - Directional
		{
			Light * pLight = new Light(LIGHT_DIRECTIONAL);
			pLight->SetColor(1,1,1);
			pLight->SetIntensity(2);

			Object * pLightObject = new Object();
			pLightObject->m_pTransform	= new Transform(1,0,0, 60,-45,0, 1,1,1);
			pLightObject->AddComponent(pLight);
			pLightObject->AddComponent( new ObjectRotator(0.3f,0,0) );

			scene.AddLight(pLight);
		}

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
		
	}
};
