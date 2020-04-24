#pragma once
#include "GraphicsEngine/Materials/Material.h"
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20GraphicsDevice.h"
#include "GraphicsEngine/Texture2D.h"


class MaterialPartTransparent : public Material
{
public:
	MaterialPartTransparent(TextureFilterMode filterMode);
	MaterialPartTransparent(Texture2D * pTexture);

	virtual void Init();
	virtual void Deinit();
	
	virtual void SetMaterial(const Object * pObject);
	virtual void ResetMaterial();

private:
	Texture2D *	m_pTexture1;
	TextureFilterMode m_filterMode;
	GL20GraphicsDevice graphics_device{};
};
