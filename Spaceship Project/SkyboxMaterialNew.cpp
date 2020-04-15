#include "GraphicsEngine/ClassesIanko/MaterialEarth.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"
#include "Spaceship Project/SkyboxTaskNew/SkyboxMaterialNew.h"




SkyboxMaterialNew::SkyboxMaterialNew(
	const Vector3 & color,
	const TextureFilterMode filter_mode,
	const std::string & v_shader_filename,
	const std::string & p_shader_filename,
	const std::string& texture_jpg_filename_
	) :
	m_color(color, 1), FilterMode(filter_mode), texture_jpg_filename(texture_jpg_filename_)
{
	m_vsFileName = v_shader_filename;
	m_psFileName = p_shader_filename;
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
	// Заполняем матрицы World, View, Proj
	const Matrix4x4 & matWorld = SceneUtils::GetMatrixWorld(pObject);
	const Matrix4x4 & matView = SceneUtils::GetMatrixView();
	const Matrix4x4 & matProj = SceneUtils::GetMatrixProj();

	const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);

	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		SetVertexShaderVector4("constColor", m_color);

		//Passing textures
		SetPixelShaderTexture2d("Texture", Texture);

		
		//Passing Cube Textures
		/*SetPixelShaderTexture2d("TextureUp", this->TextureUp);
		SetPixelShaderTexture2d("TextureBottom", this->TextureBottom);
		SetPixelShaderTexture2d("TextureLeft", this->TextureLeft);
		SetPixelShaderTexture2d("TextureRight", this->TextureRight);
		SetPixelShaderTexture2d("TextureFront", this->TextureFront);
		SetPixelShaderTexture2d("TextureBack", this->TextureBack);*/

		

		SetVertexShaderEnd();
		SetPixelShaderBegin();
		SetPixelShaderEnd();
	}
	SetMaterialEnd();
}


