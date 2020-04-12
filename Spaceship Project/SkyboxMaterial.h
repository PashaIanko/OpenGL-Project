#pragma once
#include "GraphicsEngine/Materials/Material.h"
#include "Spaceship Project/TextureFilenames.h" 


/**
* @brief Unlit material class doesn't take into account light sources. Draws the object in one color.
* It's for rendering the object without lightning (even light sources exist in a scene).
* For more details, see class Material.
*/
class SkyboxMaterial : public Material
{
public:
	/**
	* @brief Constructs the object.
	* @param [in] color Color of the object.
	*/

	//Добавил конструктор
	SkyboxMaterial(const SkyboxMaterial&) = delete;
	SkyboxMaterial
	(
		const Vector3 & color,
		const TextureFilterMode filter_mode,
		const std::string& v_shader_name,
		const std::string& p_shader_name,
		const std::string& texture_jpg_filename
	);

	SkyboxMaterial
	(
		const Vector3 & color,
		const TextureFilterMode filter_mode,
		const std::string& v_shader_name,
		const std::string& p_shader_name,
		const std::string& texture_jpg_filename,
		const TextureFilenames& filenames_pack
	);

	/**
	* @brief Initialize the material and necessary data here.
	*/
	virtual void Init();

	/**
	* @brief Deinitialize the material and necessary data here.
	*/
	virtual void Deinit();

	/**
	* @brief Pass all necessary for rendering data to vertex and pixel shaders (is called before rendering).
	* @param [in] pObject Pointer to an object that is being rendered now.
	*/
	virtual void SetMaterial(const Object * pObject);



private:

	/**
	* @brief The color of the object.
	* This material draws the object in one color.
	*/
	void init_cube_textures();

	Vector4 m_color;
	Texture2D *	PlanetTexture = nullptr;
	TextureFilterMode FilterMode;
	std::string texture_jpg_filename = "";

	/*std::string TextureBottomFilename = "";
	std::string TextureUpFilename = "";
	std::string TextureLeftFilename = "";
	std::string TextureRightFilename = "";
	std::string TextureFrontFilename = "";
	std::string TextureBackFilename = "";*/

	TextureFilenames filenames;

	Texture2D *	TextureBottom = nullptr;
	Texture2D *	TextureUp = nullptr;
	Texture2D *	TextureLeft = nullptr;
	Texture2D *	TextureRight = nullptr;
	Texture2D *	TextureFront = nullptr;
	Texture2D *	TextureBack = nullptr;

};

