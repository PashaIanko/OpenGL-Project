#pragma once
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Camera.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Light.h"
#include "Spaceship Project/TransparentTask/MaterialCutoutUnlitTexture.h"
#include "GraphicsEngine/Meshes/MeshQuad.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/Transform.h"

#include "Tasks/Task.h"
#include "Tasks/ObjectRotator.h"
#include "Spaceship Project/TransparentTask/MaterialPartTransparent.h"


/**
* @brief Shows how to use Transparent Cutout objects.
* Key code is situated in the classes MaterialUnlitTextureCutout, GraphicsDevice.
*/
class TransparentTask: public Task
{
public:
	virtual ~TransparentTask() { }

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();
	
		// Camera
		{
			Object * pCameraObj = new Object();
			pCameraObj->m_pTransform = new Transform( Vector3(0, 0, -1), Vector3(0.0f, 0.0f, 0.0f));
			Camera * pCamera = new Camera();
			pCamera->SetFovY(90);
			pCamera->SetNearPlane(0.01f);
			pCamera->SetFarPlane(100);
			pCameraObj->AddComponent( pCamera );
			pCameraObj->AddComponent( new CameraController );

			scene.SetCamera( pCamera );
		}

		Mesh * pMeshQuad = new MeshQuad();
		Mesh * pMeshCube = new MeshCube(3);

		Texture2D * grassTexture;
		{
			grassTexture = new Texture2D("grass_bush.png");
			grassTexture->SetFilterMode(TEXTURE_FILTER_MODE_TRILINEAR);
			grassTexture->SetWrapMode(TEXTURE_WRAP_MODE_CLAMP);
		}
		
		Texture2D * windowTexture;
		{
			windowTexture = new Texture2D("window.png");
			windowTexture->SetFilterMode(TEXTURE_FILTER_MODE_TRILINEAR);
			windowTexture->SetWrapMode(TEXTURE_WRAP_MODE_CLAMP);
		}

		/*
		
		Вывести все непрозрачные объекты.
		Отсортировать прозрачные объекты по удалению.
		Нарисовать прозрачные объекты в отсортированном порядке.
		
		*/

		int n = 20;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				// Object - Quad with GRASS
				Object * pObj1 = NULL;
				{
					Object * pObject = new Object();
					//pObject->m_pMesh		= new MeshQuad();
					pObject->m_pMesh		= pMeshQuad;
					pObject->m_pTransform	= new Transform(Vector3(-n * 0.5 + i, 0, -n * 0.5 + j), Vector3(-90, 0, 0), Vector3(1, 1, 1));
					pObject->m_pMaterial	= new MaterialCutoutUnlitTexture(grassTexture);

					scene.AddObject( pObject );

					pObj1 = pObject;
				}

				// Object - Cube
				Object * pObj3 = NULL;
				{
					Object * pObject = new Object();
					pObject->m_pMesh		= pMeshCube;
					pObject->m_pTransform	= new Transform(Vector3(-n * 0.5 + i + 0.5, -0.5, -n * 0.5 + j + 0.5), Vector3(-90, 0, 0), Vector3(0.3, 0.3, 0.3));
					pObject->m_pMaterial	= new MaterialUnlitSimple();

					scene.AddObject( pObject );

					pObj3 = pObject;
				}
			}
		}


		n = 10;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{

				// Object - Quad with WINDOW
				Object * pObj2 = NULL;
				{
					Object * pObject = new Object();
					pObject->m_pMesh = pMeshQuad;
					pObject->m_pTransform = new Transform(Vector3(-n * 0.5 + i, 0, -n * 0.8 + j), Vector3(-90, 0, 0), Vector3(1, 1, 1));
					pObject->m_pMaterial = new MaterialPartTransparent(windowTexture);

					scene.AddObject(pObject);

					pObj2 = pObject;
				}

			}
		}

		// FPS counter
		{
			Object * pObject = new Object();
			pObject->m_pTransform	= new Transform();
			pObject->AddComponent( new FpsCounter() );

			scene.AddObject( pObject );
		}
	}

	virtual void Update()
	{
		
	}
};
