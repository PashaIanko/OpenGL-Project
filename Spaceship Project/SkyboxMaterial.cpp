#include "GraphicsEngine/ClassesIanko/MaterialEarth.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"
#include "Spaceship Project/SkyboxMaterial.h"



SkyboxMaterial::SkyboxMaterial(
	const Vector3 & color,
	const TextureFilterMode filter_mode,
	const std::string& v_shader_filename,
	const std::string& p_shader_filename,
	const std::string& texture_jpg_filename_
)
	: m_color(color, 1), FilterMode(filter_mode), texture_jpg_filename(texture_jpg_filename_)
{
	m_vsFileName = v_shader_filename;
	m_psFileName = p_shader_filename;

}

SkyboxMaterial::SkyboxMaterial(
	const Vector3 & color, 
	const TextureFilterMode filter_mode, 
	const std::string & v_shader_filename, 
	const std::string & p_shader_filename,
	const std::string& texture_jpg_filename_,
	const TextureFilenames & filenames_pack):
	m_color(color, 1), FilterMode(filter_mode), texture_jpg_filename(texture_jpg_filename_), filenames(filenames_pack)
{
	m_vsFileName = v_shader_filename;
	m_psFileName = p_shader_filename;
}

// TODO: Реализовать переключение Graphics API при нажатии на кнопки (1 - DirectX 11, 2 - OpenGL 2.0, 9 - DirectX 9)
// и отладить на этом механизм использования функций Init() и Deinit()
void SkyboxMaterial::Init()
{
	Material::Init();

	// TODO: Нужно при компиляции скопировать папку с шейдерами
	// Google it: "visual studio during build copy files into application folder"

	PlanetTexture = new Texture2D(this->texture_jpg_filename.c_str());//Texture2D("ChessBoard.png"); // текстура песка
	PlanetTexture->SetFilterMode(FilterMode);

	init_cube_textures();

	
}

void SkyboxMaterial::Deinit()
{
	delete PlanetTexture;
	PlanetTexture = NULL;
	Material::Deinit();
}

void SkyboxMaterial::SetMaterial(const Object * pObject)
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
		SetPixelShaderTexture2d("textureEarth", PlanetTexture);

		SetPixelShaderTexture2d("TextureSpaceUp", TextureUp);
		SetPixelShaderTexture2d("TextureSpaceBottom", TextureBottom);
		SetPixelShaderTexture2d("TextureSpaceLeft", TextureLeft);
		SetPixelShaderTexture2d("TextureSpaceRight", TextureRight);
		SetPixelShaderTexture2d("TextureSpaceFront", TextureFront);
		SetPixelShaderTexture2d("TextureSpaceBack", TextureBack);

		
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

void SkyboxMaterial::init_cube_textures() {

	TextureBottom = new Texture2D(this->filenames.bottom.c_str());//Texture2D("ChessBoard.png"); // текстура песка
	TextureBottom->SetFilterMode(FilterMode);

	TextureUp = new Texture2D(this->filenames.up.c_str());
	TextureBottom->SetFilterMode(FilterMode);

	TextureLeft = new Texture2D(this->filenames.left.c_str());
	TextureLeft->SetFilterMode(FilterMode);

	TextureRight = new Texture2D(this->filenames.right.c_str());
	TextureRight->SetFilterMode(FilterMode);

	TextureFront = new Texture2D(this->filenames.front.c_str());
	TextureFront->SetFilterMode(FilterMode);

	TextureBack = new Texture2D(this->filenames.back.c_str());
	TextureBack->SetFilterMode(FilterMode);
}
