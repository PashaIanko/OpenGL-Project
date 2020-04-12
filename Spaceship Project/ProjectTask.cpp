#include "ProjectTask.h"

#include "Spaceship Project/PlanetMaterial.h"
#include "../../GraphicsEngine/SDKs//OpenGL/include/GL/glew.h"

namespace constants {
	const double sun_mercury_dist = 3.0;
	const double sun_venus_dist = 4.5;
}

void ProjectTask::create_planets(Scene & scene) {
	//Object #1 - Cube (Sun)
	Object * pObjSun = NULL;
	{
		Object * pObject = new Object();
		pObject->m_pMesh = new MeshSphere(30);//new MeshCube(3);
		pObject->m_pTransform = new Transform();
		
		pObject->m_pMaterial = new PlanetMaterial(
			Vector3(0,0,0), 
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
	Object * pObjMercury = NULL;
	{
		Object * pObject = new Object();
		pObject->m_pMesh = new MeshSphere(30);
		pObject->m_pTransform = new Transform(constants::sun_mercury_dist, 0, 0, 0, 0, 1, 0.5, 0.5, 0.5);
		pObject->m_pMaterial = new PlanetMaterial(
			Vector3(0, 0, 0),
			TEXTURE_FILTER_MODE_TRILINEAR,
			"ShaderEarth",
			"ShaderEarth",
			/*"Earth_Albedo.jpg"*/"mercury.jpg"
		);
		pObject->AddComponent(new ObjectRotator(0, 100, 0));
		pObject->m_pTransform->SetParent(pObjSun->m_pTransform);
		scene.AddObject(pObject);
		pObjMercury = pObject;
	}

	// Object #3 - Venus
	Object * pObjVenus = NULL;
	{
		Object * pObject = new Object();
		pObject->m_pMesh = new MeshSphere(30);
		pObject->m_pTransform = new Transform(constants::sun_venus_dist, 0, 0, 0, 20, 20, 0.5, 0.5, 0.5);
		pObject->m_pMaterial = new PlanetMaterial(
			Vector3(0, 0, 0),
			TEXTURE_FILTER_MODE_TRILINEAR,
			"ShaderEarth",
			"ShaderEarth",
			/*"Earth_Albedo.jpg"*/"venus.jpg"
		);
		pObject->AddComponent(new ObjectRotator(10, 100, 0));
		pObject->m_pTransform->SetParent(pObjSun->m_pTransform);
		scene.AddObject(pObject);
		pObjVenus = pObject;
	}

	// Object #2 - Cube (Earth)
	Object * pObj2 = NULL;
	{
		Object * pObject = new Object();
		pObject->m_pMesh = new MeshCube(3);
		pObject->m_pTransform = new Transform(7, 0, 0, 0, 0, 23, 1, 1, 1);
		pObject->m_pMaterial = new MaterialUnlitSimple();
		pObject->AddComponent(new ObjectRotator(0, 100, 0));

		pObject->m_pTransform->SetParent(pObjSun->m_pTransform);

		scene.AddObject(pObject);

		pObj2 = pObject;
	}

	// Object #3 - Cube (Moon)
	{
		Object * pObject = new Object();
		pObject->m_pMesh = new MeshCube(4);
		pObject->m_pTransform = new Transform(3, 0, 0);
		pObject->m_pMaterial = new MaterialUnlitSimple();
		pObject->AddComponent(new ObjectRotator(0, 360, 0));

		pObject->m_pTransform->SetParent(pObj2->m_pTransform);

		scene.AddObject(pObject);
	}
}

void ProjectTask::create_cube_map() {
	//unsigned int textureID;
	//glGenTextures(1, &textureID);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
}
