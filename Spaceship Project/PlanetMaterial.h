#pragma once
#include "GraphicsEngine/Materials/Material.h"


/**
* @brief Unlit material class doesn't take into account light sources. Draws the object in one color.
* It's for rendering the object without lightning (even light sources exist in a scene).
* For more details, see class Material.
*/
class PlanetMaterial : public Material
{
public:
	/**
	* @brief Constructs the object.
	* @param [in] color Color of the object.
	*/

	//Добавил конструктор
	PlanetMaterial(const PlanetMaterial&) = delete;
	PlanetMaterial
	(
		const Vector3 & color, 
		const TextureFilterMode filter_mode, 
		const std::string& v_shader_name,
		const std::string& p_shader_name,
		const std::string& texture_jpg_filename,
		const std::string& normal_map_jpg_filename = ""
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
	
	Vector4 m_color;
	Texture2D *	PlanetTexture = nullptr;
	TextureFilterMode FilterMode;
	std::string texture_jpg_filename = "";
	std::string normal_map_jpg_filename = "";
};

