#pragma once
#include "glad/glad.h"
#include "stb_image/stb_image.h"
#include "Qubit/Platform/Renderer/Utility/Shader.h"
#include <deque>

namespace Qubit {
	enum texturelaunch{
		async,
		mainthread,
		onthreadcallback
	};

	class Texture{
	public:
		Texture(const Qubit::texturelaunch& launch, const std::string& path, const std::string& type, const std::string& name);
		Texture(const Texture& texture);
		//Used to initialize all of the OpenGL texture buffers on the main context
		void Initialize();
		void BindTexture();
		void UnBindTexture();
		void EnableTexture(Shader& shader, std::string& name, int pos );
		void DisableTexture();
		void DeleteTexture();
		unsigned int getTextureID();

		std::string GetPath() const { return m_Path; }
		std::string GetType() const { return m_Type; }
		std::string GetName() const { return m_Name; }

		~Texture() = default;
		static std::unordered_map<std::string, std::shared_ptr<Texture>> s_TextureAtlas;
		static std::deque<std::shared_ptr<Texture>> s_Callbacks;
		static std::mutex s_Mute;
		uint32_t m_TextureUnit;
	private:
		void LoadTexture();

		static std::string s_LastLoadedTexture;

		stbi_uc* data;
		unsigned int textureID = 0;
		int m_Width, m_Height, m_nrChannel;
		std::string m_Path, m_Type, m_Name;
		float* pointerToTextureCoords;
	};
}