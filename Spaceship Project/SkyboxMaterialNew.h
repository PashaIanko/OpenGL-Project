#pragma once
#include "GraphicsEngine/Materials/Material.h"
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20GraphicsDevice.h"

/**
* @brief Unlit material class doesn't take into account light sources. Draws the object in one color.
* It's for rendering the object without lightning (even light sources exist in a scene).
* For more details, see class Material.
*/
class SkyboxMaterialNew : public Material
{
public:
	/**
	* @brief Constructs the object.
	* @param [in] color Color of the object.
	*/

	//Добавил конструктор
	SkyboxMaterialNew(const SkyboxMaterialNew&) = delete;
	SkyboxMaterialNew
	(
		const Vector3 & color,
		const TextureFilterMode filter_mode,
		const std::string& v_shader_name,
		const std::string& p_shader_name,
		const std::string& texture_jpg_filename,
		const int render_queue
		
		// Необходимо render queue указать
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

	virtual void ResetMaterial() override; 


private:

	/**
	* @brief The color of the object.
	* This material draws the object in one color.
	*/
	Vector4 m_color;
	Texture2D *	Texture = nullptr;
	TextureFilterMode FilterMode;
	std::string texture_jpg_filename = "";
	GL20GraphicsDevice graphics_device{};

};

