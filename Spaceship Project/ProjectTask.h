#pragma once
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Meshes/MeshQuad.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Materials/MaterialUnlit.h"
#include "GraphicsEngine/Light.h"

#include "Tasks/Task.h"
#include "Tasks/CameraController.h"

#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20Input.h"
#include "GraphicsEngine/ClassesIanko/RotationController.h"
#include "GraphicsEngine/Meshes/MeshSphere.h"
#include "GraphicsEngine/Meshes/MeshCube.h"
#include "GraphicsEngine/ClassesIanko/MaterialEarth.h"
#include "GraphicsEngine/Materials/MaterialUnlitSimple.h"
#include "GraphicsEngine/../../Sources/Tasks/ObjectRotator.h"


/**
* @brief Shows how to process user's input (keyboard and mouse).
* Key code is situated in the classes CameraController, Input, IternalInput, WinInput, GL20Input.
*/
class ProjectTask : public Task
{
public:
	virtual ~ProjectTask() { }
	
virtual void Init()
{
	Scene & scene = Application::Instance().GetScene();

	// Camera
	{
		Object * pCameraObj = new Object();
		pCameraObj->m_pTransform = new Transform(Vector3(0, 2, -10), Vector3(20.0f, 0.0f, 0.0f));
		Camera * pCamera = new Camera();
		pCamera->SetFovY(90);// ףדמכ מבחמגא
		pCamera->SetNearPlane(0.01f);
		pCamera->SetFarPlane(100);
		pCameraObj->AddComponent(pCamera);

		scene.SetCamera(pCamera);
	}

	this->create_planets(scene);
	this->create_cube_map();
	
}
	
virtual void Update()
{

}
private:
	void create_planets(Scene&);
	void create_cube_map();
	
private:
	Camera* cam;
	
};

