#pragma once
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Meshes/MeshObjFile.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "Spaceship Project/RocketMeshTask/RocketMaterial.h"
#include "GraphicsEngine/Light.h"

#include "Tasks/Task.h"
#include "Tasks/ObjectRotator.h"


/**
* @brief Shows how to load mesh from obj-file.
* Key code is situated in the class MeshObjFile.
*/
class RocketMeshTask: public Task
{
public:
	virtual ~RocketMeshTask() { }

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();
	
		// Camera
		{
			Object * pCameraObj = new Object();
			pCameraObj->m_pTransform = new Transform( Vector3(0.0f, 0.0f, -10.0f),
				Vector3(20.0f, 0.0f, 0.0f));
			Camera * pCamera = new Camera();
			pCameraObj->AddComponent( pCamera );
			//pCameraObj->AddComponent(new ObjectRotator(0, 45, 0));

			scene.SetCamera( pCamera );
		}

		
		{
			Object * pObject1 = new Object();
			pObject1->m_pMesh = new MeshObjFile("Rocket.obj");
			
			const double scale = 0.01;
			pObject1->m_pTransform	= new Transform(0,-2,-4, 0,0,0, scale,scale,scale);
			pObject1->m_pMaterial = new RocketMaterial(); 
			pObject1->AddComponent( new ObjectRotator(0,45,0) );
						
			scene.AddObject( pObject1 );
		}

		// Lightsource #1 - Directional
		{
			Light * pLight = new Light(LIGHT_DIRECTIONAL);
			pLight->SetColor(1, 0, 0);
			pLight->SetIntensity(1);

			Object * pLightObject = new Object();
			pLightObject->m_pTransform = new Transform(100, 0, 0, 45, 90, 0, 1, 1, 1);
			pLightObject->AddComponent(pLight);

			scene.AddLight(pLight);
		}

		{
			Light * pLight = new Light(LIGHT_SPOT);

			pLight->SetColor(1, 1, 1);
			pLight->SetIntensity(1);

			Object * pLightObject = new Object();
			pLightObject->m_pTransform = new Transform(0, 0, -3, 0, 30, 0, 1, 1, 1);//new Transform(-5, 3, 0, 85, 0, 0, 1, 1, 1);
			//pLightObject->m_pTransform->SetParent(spotlight_center->m_pTransform);

			pLightObject->AddComponent(pLight);
			scene.AddLight(pLight);
		}
	}

	virtual void Update()
	{
		
	}
};
