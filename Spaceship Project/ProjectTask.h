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

	/*virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();

		// Camera

		{
			Camera* pCamera = new Camera();

			// Тело - у него родительский Transform. Rotation и Translation --> Должны вызывать Rotate и Translate у РОДИТЕЛЬСКОГО Transform
			Vector3 CamPos = Vector3(0.0f, 0.0f, 0.0f);//Vector3(0.0f, 0.5f, -5.0f);
			Vector3 CamScale = Vector3(20.0f, 10.0f, 0.0f);

			Object* BodyObj = new Object();
			BodyObj->m_pTransform = new Transform(CamPos, CamScale);
			BodyObj->AddComponent(pCamera);

			// Rotation Controller - Класс, наследованный от Object, Будет контроллировать вращение вокруг
			// определённой оси
			RotationController* RotationY = new RotationController(false, true, false);
			RotationY->m_pTransform = new Transform(CamPos, CamScale);
			RotationY->m_pTransform->SetParent(BodyObj->m_pTransform);

			RotationController* RotationX = new RotationController(true, false, false);
			RotationX->m_pTransform = new Transform(CamPos, CamScale);
			RotationX->m_pTransform->SetParent(BodyObj->m_pTransform);


			CameraController * pCamCtrl = new CameraController(CamPos, CamScale);
			// Вся работа по вращению - в функциях Camera Controller'a поэтому добавил ему агрегацию Rotation Controller' ов
			pCamCtrl->setRotationXController(RotationX);
			pCamCtrl->setRotationYController(RotationY);

			BodyObj->AddComponent(pCamCtrl);
			scene.SetCamera(pCamera);

		}

		// Object #1 - Road with 3 textures
		{
			Object * pObject1 = new Object();

			pObject1->m_pTransform = new Transform(0.0, -0.3, 0, 0, 0, 0, 1, 1, 10);
			pObject1->m_pMesh = new MeshQuad();
			pObject1->m_pMaterial = new MaterialUnlit(Vector3(0.5, 0.5, 0.5), TEXTURE_FILTER_MODE_TRILINEAR);

			scene.AddObject(pObject1);
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
		//GL20Input::SetMouseButtonsEvent(0, 0, 0, 0);



	}

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();

		// Camera
		{
			Object * pCameraObj = new Object();
			pCameraObj->m_pTransform = new Transform(Vector3(0, 1.5, -3), Vector3(20.0f, 0.0f, 0.0f));
			Camera * pCamera = new Camera();
			pCamera->SetFovY(90);
			pCamera->SetNearPlane(0.01f);
			pCamera->SetFarPlane(100);
			pCameraObj->AddComponent(pCamera);
			pCameraObj->AddComponent(new CameraController());

			scene.SetCamera(pCamera);
		}

		// Object # 1 - Cube (is morphed to sphere)
		{
			Object * pObject = new Object();
			pObject->m_pTransform = new Transform(Vector3(-1.5, 0, 0), Vector3(0, 30, 0));
			pObject->m_pMesh = new MeshCube(10);
			pObject->m_pMaterial = new CubeMaterialUnlitSimple();//new MaterialUnlitSimple();

			scene.AddObject(pObject);
		}

		// Object #2 - Cylinder (is twisted)
		{
			Object * pObject = new Object();
			pObject->m_pTransform = new Transform(Vector3(1.5, 0, 0), Vector3(0, 30, 0));
			pObject->m_pMesh = new MeshCylinder(20);
			pObject->m_pMaterial = new CylinderMaterialUnlitSimple();//new MaterialUnlitSimple();

			scene.AddObject(pObject);
		}
	}
	*/

virtual void Init()
{
	Scene & scene = Application::Instance().GetScene();

	// Camera
	{
		Object * pCameraObj = new Object();
		pCameraObj->m_pTransform = new Transform(Vector3(0, 2, -10), Vector3(20.0f, 0.0f, 0.0f));
		Camera * pCamera = new Camera();
		pCamera->SetFovY(90);// угол обзова
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

