#pragma once
#include <glad/glad.h>

namespace Qubit {
	struct FramebufferSpecification {
		float width, height;

	};

	class Framebuffer {
	public:
		Framebuffer() = default;
		Framebuffer(const FramebufferSpecification& spec);
		Framebuffer(const FramebufferSpecification&& spec);
		~Framebuffer();

		unsigned int GetFramebufferImage() const { return m_TextureID;  }

		void Bind();
		void UnBind();

		void ResetFramebuffer(const FramebufferSpecification& spec);
		void ResetFramebuffer(const FramebufferSpecification&& spec);
		FramebufferSpecification m_Specification;
	private:
		void Create();

		unsigned int m_FramebufferID, m_FramebufferResizeID, m_TextureID, m_RenderbufferID;
	};
}