#pragma once
#include "GraphicsEngine/Materials/Material.h"


// Рассчитывает только компоненту diffuse от всех источников света
class RocketMaterial : public Material
{
public:
	RocketMaterial();

	virtual void Init();
	virtual void Deinit();
	
	virtual void SetMaterial(const Object * pObject);
};
