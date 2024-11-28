#include <QubitPCH.h>
#include "Qubit/Platform/Renderer/Utility/Texture.h"

namespace Qubit {

	std::unordered_map<std::string, std::shared_ptr<Texture>> Texture::s_TextureAtlas;
	std::deque<std::shared_ptr<Texture>> Texture::s_Callbacks;
	std::mutex Texture::s_Mute;
	
	void Texture::Initialize(){

		//Checks to make sure that this Texture is the only instance being put onto the TextureAtlas
		//This could honestly be unecessary but I don't want to risk any errors. Efficiency impact would be negligible.
		if (s_TextureAtlas.find(this->m_Name) != s_TextureAtlas.end())
			return;

		if (this->data) {
			GLenum internalFormat = 0;
			GLenum dataFormat = 0;

			switch (this->m_nrChannel)
			{
			case 4:
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
				break;

			case 3:
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
				break;
			case 2:
				internalFormat = GL_RG8;
				dataFormat = GL_RG;
				break;
			case 1:
				internalFormat = GL_R8;
				dataFormat = GL_RED;
				break;
			}

			glGenTextures(1, &this->textureID);
			glBindTexture(GL_TEXTURE_2D, this->textureID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, this->m_Width, this->m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, this->data);

		}

		else {
			Qubit::Log::printWarning("Texture failed to load", Qubit::Log::getCoreLogger());
		}

		stbi_image_free(this->data);
		glBindTexture(GL_TEXTURE_2D, 0);
		s_TextureAtlas.emplace(this->m_Name, this);
	}

	void Texture::LoadTexture() {
		std::lock_guard<std::mutex> lock(s_Mute);
		stbi_set_flip_vertically_on_load(true);
		data = stbi_load(m_Path.c_str(), &m_Width, &m_Height, &m_nrChannel, 0);

		s_Callbacks.emplace_back(this);
	}

	Texture::Texture(const Qubit::texturelaunch& launch, const std::string& path, const std::string& type, const std::string& name) : m_Path(path), m_Type(type), m_Name(name) {
		if (s_TextureAtlas.find(name) != s_TextureAtlas.end()) {
			std::shared_ptr<Texture> texture = std::shared_ptr<Texture>(s_TextureAtlas.at(name));
			this->data = texture->data;
			this->textureID = texture->textureID;
			this->m_Width = texture->m_Width;
			this->m_Height = texture->m_Height;
			this->m_nrChannel = texture->m_nrChannel;
			this->m_Path = texture->m_Path;
			this->m_Type = texture->m_Type;
			this->m_Name = texture->m_Name;
			this->m_TextureUnit = texture->m_TextureUnit;
		}

		else {
			switch (launch) {
			case(Qubit::texturelaunch::async):
				std::async(std::launch::async, &Texture::LoadTexture, this);
				break;

			case(Qubit::texturelaunch::mainthread):
				stbi_set_flip_vertically_on_load(true);
				data = stbi_load(m_Path.c_str(), &m_Width, &m_Height, &m_nrChannel, 0);
				Initialize();
				break;

				//If an async operation is already running
				//Useful in Model.h/cpp
			case(Qubit::texturelaunch::onthreadcallback):
				std::lock_guard<std::mutex> lock(s_Mute);
				stbi_set_flip_vertically_on_load(true);
				data = stbi_load(m_Path.c_str(), &m_Width, &m_Height, &m_nrChannel, 0);
				s_Callbacks.emplace_back(this);
				break;
			}
		}
	}

	Texture::Texture(const Texture& texture) {
		this->data = texture.data;
		this->textureID = texture.textureID;
		this->m_Width = texture.m_Width;
		this->m_Height = texture.m_Height;
		this->m_nrChannel = texture.m_nrChannel; 
		this->m_Path = texture.m_Path;
		this->m_Type = texture.m_Type;
		this->m_Name = texture.m_Name;
		this->m_TextureUnit = texture.m_TextureUnit;
	}
	
	void Texture::BindTexture() {
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	void Texture::UnBindTexture() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::EnableTexture(Shader& shader, std::string& name, int pos) {
			glActiveTexture(GL_TEXTURE0 + pos);
			glBindTexture(GL_TEXTURE_2D, textureID);

			shader.SetInt(name, pos);
			glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::DisableTexture() {
		glBindTexture(GL_TEXTURE_2D, textureID);
		glActiveTexture(GL_TEXTURE0 + m_TextureUnit);
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	unsigned int Texture::getTextureID() {
		return textureID;
	}

	//Only for deconstructing TextureAtlas textures
	//Wrapping glDeleteTextures in each constructor can result into unwanted deletion of the openGL texture
	void Texture::DeleteTexture() {
		glDeleteTextures(1, &textureID);
		this->~Texture();
	}
}