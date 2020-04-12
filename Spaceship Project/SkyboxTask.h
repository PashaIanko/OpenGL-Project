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
	
		// Camera
		{
			Object * pCameraObj = new Object();
			pCameraObj->m_pTransform = new Transform( Vector3(0.0f, 0.0f,-1.5f),
				Vector3(0.0f, 0.0f, 0.0f));
			Camera * pCamera = new Camera();
			pCameraObj->AddComponent( pCamera );

			scene.SetCamera( pCamera );
		}

		// Object #1 - Earth
		{
			Object * pObject1 = new Object();

			pObject1->m_pMesh		= new MeshSphere(30);
			pObject1->m_pTransform	= new Transform(0,0,0, 0,0,0, 1,1,1);
			pObject1->m_pMaterial = new SkyboxMaterial(
				Vector3(0, 0, 0),
				TEXTURE_FILTER_MODE_TRILINEAR,
				"ShaderEarth",
				"ShaderEarth",
				"Earth_Albedo.jpg"
			);
			pObject1->AddComponent( new ObjectRotator(0, 30, 0) );
						
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
	}

	virtual void Update()
	{
		
	}
};
