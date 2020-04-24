
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"
#include "GraphicsEngine/Internal/GraphicsDevice.h"
#include "Spaceship Project/TransparentTask/MaterialPartTransparent.h"
#include "GraphicsEngine/Materials/Material.h"
#include "GraphicsEngine/Time.h"


MaterialPartTransparent::MaterialPartTransparent(TextureFilterMode filterMode)
{
	m_renderQueue = RenderQueue::TRANSPARENT_; // RenderQueue::TRANSPARENT_CUTOUT;

	m_vsFileName = "ShaderTransparent";
	m_psFileName = "ShaderTransparent";

	m_pTexture1 = NULL;
	m_filterMode = filterMode;
}

MaterialPartTransparent::MaterialPartTransparent(Texture2D * pTexture)
{
	m_renderQueue = RenderQueue::TRANSPARENT_;//RenderQueue::TRANSPARENT;

	m_vsFileName = "ShaderTransparent";
	m_psFileName = "ShaderTransparent";

	m_pTexture1 = pTexture;
}

void MaterialPartTransparent::Init()
{
	Material::Init();

	if (NULL == m_pTexture1)
	{
		//m_pTexture1 = new Texture2D("sand.jpg");
		m_pTexture1 = new Texture2D("grass_bush.png");
		//m_pTexture1 = new Texture2D("Skybox1/front.jpg");

		m_pTexture1->SetFilterMode(m_filterMode);
		m_pTexture1->SetWrapMode(TEXTURE_WRAP_MODE_CLAMP);
	}
}

void MaterialPartTransparent::Deinit()
{
	if (NULL != m_pTexture1)
	{
		delete m_pTexture1;
		m_pTexture1 = NULL;
	}

	Material::Deinit();
}

void MaterialPartTransparent::SetMaterial(const Object * pObject)
{
	
	//graphics_device.SetZWrite(false);
	//GraphicsDevice::SetZWrite(true);

	const Matrix4x4 & matWorld	= SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4 & matView	= SceneUtils::GetMatrixView();
	const Matrix4x4 & matProj	= SceneUtils::GetMatrixProj();
	
	const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);
	double transparency = Math::Abs(Math::Sin(Time::GetTime()));
	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		SetVertexShaderVector4("constColor", Vector4(1, 1, 1, 0.5));
		SetVertexShaderVector4("MaterialTransparency", Vector4(1.0, 1.0, 1.0, transparency));
		SetVertexShaderEnd();

		SetPixelShaderBegin();
		SetPixelShaderTexture2d("texture1", m_pTexture1);
		SetPixelShaderEnd();
	}
	SetMaterialEnd();

	// TODO: Запоминать режим, который был установлен до данной строки
	
	GraphicsDevice::SetCullMode( CULL_DISABLED );

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MaterialPartTransparent::ResetMaterial()
{
	Material::ResetMaterial();

	// TODO: Нужно восстанавливать тот режим, который был ранее
	//GraphicsDevice::SetZWrite(false);
	glDisable(GL_BLEND);
	GraphicsDevice::SetCullMode(CULL_BACK);
}
