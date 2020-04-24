#include "MaterialCutoutUnlitTexture.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"
#include "GraphicsEngine/Internal/GraphicsDevice.h"


MaterialCutoutUnlitTexture::MaterialCutoutUnlitTexture(TextureFilterMode filterMode)
{
	m_renderQueue = RenderQueue::TRANSPARENT_CUTOUT;

	m_vsFileName = "ShaderCutoutUnlitTexture";
	m_psFileName = "ShaderCutoutUnlitTexture";

	m_pTexture1 = NULL;
	m_filterMode = filterMode;
}

MaterialCutoutUnlitTexture::MaterialCutoutUnlitTexture(Texture2D * pTexture)
{
	m_renderQueue = RenderQueue::TRANSPARENT_CUTOUT;

	m_vsFileName = "ShaderCutoutUnlitTexture";
	m_psFileName = "ShaderCutoutUnlitTexture";

	m_pTexture1 = pTexture;
}

void MaterialCutoutUnlitTexture::Init()
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

void MaterialCutoutUnlitTexture::Deinit()
{
	if (NULL != m_pTexture1)
	{
		delete m_pTexture1;
		m_pTexture1 = NULL;
	}

	Material::Deinit();
}

void MaterialCutoutUnlitTexture::SetMaterial(const Object * pObject)
{
	
	//graphics_device.SetZWrite(false);
	//GraphicsDevice::SetZWrite(false);

	const Matrix4x4 & matWorld	= SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4 & matView	= SceneUtils::GetMatrixView();
	const Matrix4x4 & matProj	= SceneUtils::GetMatrixProj();
	
	const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);

	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		SetVertexShaderVector4("constColor", Vector4(1, 1, 1, 1));
		SetVertexShaderEnd();

		SetPixelShaderBegin();
		SetPixelShaderTexture2d("texture1", m_pTexture1);
		SetPixelShaderEnd();
	}
	SetMaterialEnd();

	// TODO: Запоминать режим, который был установлен до данной строки
	GraphicsDevice::SetCullMode( CULL_DISABLED );
}

void MaterialCutoutUnlitTexture::ResetMaterial()
{
	Material::ResetMaterial();

	// TODO: Нужно восстанавливать тот режим, который был ранее
	GraphicsDevice::SetCullMode(CULL_BACK);

	//graphics_device.SetZWrite(true);
}
