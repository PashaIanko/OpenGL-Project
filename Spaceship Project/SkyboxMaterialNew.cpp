#include "GraphicsEngine/ClassesIanko/MaterialEarth.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"
#include "Spaceship Project/SkyboxTaskNew/SkyboxMaterialNew.h"
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20GraphicsDevice.h"




SkyboxMaterialNew::SkyboxMaterialNew(
	const Vector3 & color,
	const TextureFilterMode filter_mode,
	const std::string & v_shader_filename,
	const std::string & p_shader_filename,
	const std::string& texture_jpg_filename_,
	const int render_queue
	) :
	m_color(color, 1), FilterMode(filter_mode), texture_jpg_filename(texture_jpg_filename_)
{
	m_vsFileName = v_shader_filename;
	m_psFileName = p_shader_filename;
	m_renderQueue = render_queue;
}

// TODO: Реализовать переключение Graphics API при нажатии на кнопки (1 - DirectX 11, 2 - OpenGL 2.0, 9 - DirectX 9)
// и отладить на этом механизм использования функций Init() и Deinit()
void SkyboxMaterialNew::Init()
{
	Material::Init();

	// TODO: Нужно при компиляции скопировать папку с шейдерами
	// Google it: "visual studio during build copy files into application folder"

	Texture = new Texture2D(this->texture_jpg_filename.c_str());//Texture2D("ChessBoard.png"); // текстура песка
	Texture->SetFilterMode(FilterMode);


	
}

void SkyboxMaterialNew::Deinit()
{
	delete Texture;
	Texture = NULL;
	Material::Deinit();
}

void SkyboxMaterialNew::SetMaterial(const Object * pObject)
{
	// С z-buffer ом работаем
	graphics_device.SetZWrite(false);
	
	
	// Заполняем матрицы World, View, Proj
	const Matrix4x4 & matWorld = SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4 & matView = SceneUtils::GetMatrixView();
	const Matrix4x4 & matProj = SceneUtils::GetMatrixProj();

	const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);

	SetMaterialBegin();
	{

		//GraphicsDevice::SetZWrite(false);


		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		SetVertexShaderVector4("constColor", m_color);

		//Passing textures
		SetPixelShaderTexture2d("Texture", Texture);
				
		SetVertexShaderEnd();
		SetPixelShaderBegin();
		SetPixelShaderEnd();
	}
	SetMaterialEnd();
}

void SkyboxMaterialNew::ResetMaterial(){
	Material::ResetMaterial();
	graphics_device.SetZWrite(true);
}


