#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/Input.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Time.h"
#include "GraphicsEngine/Vector3.h"

#include "GraphicsEngine/SceneUtils.h"
#include "GraphicsEngine/ClassesIanko/RotationController.h"


class CameraControllerNew : public Component
{
	Vector3 mousePos;
	Vector3 mousePosPrev;

public:
	CameraControllerNew()
	{
		mousePos = Vector3::Zero();
		mousePosPrev = Vector3::Zero();

		ParentTransform = new Transform();
	}
	CameraControllerNew(Vector3 CamPos, Vector3 CamScale)
	{
		mousePos = Vector3::Zero();
		mousePosPrev = Vector3::Zero();

		ParentTransform = new Transform();// Transform(CamPos, CamScale);
	}

	virtual ~CameraControllerNew() {}

	void SetSkyboxComponent(Skybox* skybox_ptr_) {
		skybox_ptr = skybox_ptr_;
	}

	virtual void Update()
	{
		Transform * pTransform = m_pObject->m_pTransform; // Здесь мы получили именно Body Object Transform если верно понимаю
		
		pTransform->SetParent(ParentTransform);
		// Camera Translation
		{
			Vector3 forward = pTransform->GetForward();
			Vector3 right = pTransform->GetRight();
			Vector3 left = -right;
			double dt = Time::GetDeltaTime();

			double speed = 1.0;
			Vector3 direction;

			if (Input::GetKey(KEY_CODE_W) || Input::GetKey(KEY_CODE_UP_ARROW))
			{
				direction += forward;
			}
			if (Input::GetKey(KEY_CODE_D) || Input::GetKey(KEY_CODE_RIGHT_ARROW))
			{
				direction += right;
			}
			if (Input::GetKey(KEY_CODE_A) || Input::GetKey(KEY_CODE_LEFT_ARROW))
			{
				direction += left;
			}
			if (Input::GetKey(KEY_CODE_S))// || Input::GetKey(KEY_CODE_DOWN_ARROW))
			{
				direction -= forward;
			}
			if (Input::GetKey(KEY_CODE_Z))// || Input::GetKey(KEY_CODE_DOWN_ARROW))
			{
				speed += 5;
			}

			// TODO : Task08
			//pTransform->Translate( speed * dt * direction );
			ParentTransform->Translate(speed * dt * direction);

			// У компоненты Skybox, все 6 граней так же транслируем
			skybox_ptr->Translate(speed * dt * direction);
		}
		

		// Camera Rotation
		{
			mousePos = Input::GetMousePosition();

			double dx = mousePos.x - mousePosPrev.x;
			double dy = mousePos.y - mousePosPrev.y;
			// TODO : Task08

			if (Input::GetMouseButton(0)) {
				/*Логика такая - получили вектор (dx dy) на вращение. И мы должны разделить ответственность
				за вращение по разным осям. В конструкторе Task 08 Можете видеть, Camera связана
				с HeadObj - т.е. с Rotation Controller, ответственн за вращение вокруг Y.
				У HeadObj есть родитель - Body Obj, он же - Rotation Controller, ответств. за вращение вокруг X
				И сейчас я пытаюсь передать отдельно (dy 0 0) и (0 dx 0) на эти контроллеры. */


				double sensitivity = 0.5f;
				ParentTransform->Rotate(0, dx*sensitivity, 0.00);
				pTransform->Rotate(dy*sensitivity, 0.0f, 0.00);

			}
			mousePosPrev = mousePos;
		}
	}



public:
	void setCam(Camera* ptr) {
		this->cam = ptr;
	}

	void setRotationXController(RotationController* ptr) {
		RotationXController = ptr;
	}
	void setRotationYController(RotationController* ptr) {
		RotationYController = ptr;
	}


private:
	Camera* cam = nullptr;
	RotationController* RotationXController = nullptr;
	RotationController* RotationYController = nullptr;
	Transform* ParentTransform = nullptr;

	Skybox* skybox_ptr = nullptr;

};
