#include <QubitPCH.h>
#include "Qubit/Platform/Renderer/Utility/Framebuffer.h"

namespace Qubit {
	Framebuffer::Framebuffer(const FramebufferSpecification& spec) : m_Specification(spec){
		Create();
	}
	Framebuffer::Framebuffer(const FramebufferSpecification&& spec) : m_Specification(spec) {
		Create();
	}
	
	void Framebuffer::Create() {
		glGenTextures(1, &m_TextureID);
		glGenRenderbuffers(1, &m_RenderbufferID);
		glGenFramebuffers(1, &m_FramebufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);

		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Specification.width, m_Specification.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureID, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindRenderbuffer(GL_RENDERBUFFER, m_RenderbufferID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Specification.width, m_Specification.height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderbufferID);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			Log::printError("Framebuffer is not complete!", Log::getCoreLogger());

		glViewport(0, 0, m_Specification.width, m_Specification.height);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	Framebuffer::~Framebuffer() {
		glDeleteFramebuffers(1, &m_FramebufferID);
		glDeleteBuffers(1, &m_TextureID);
		glDeleteRenderbuffers(1, &m_RenderbufferID);
	}

	void Framebuffer::Bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);
		glEnable(GL_DEPTH_TEST);
	}

	void Framebuffer::ResetFramebuffer(const FramebufferSpecification& spec) {
		glDeleteFramebuffers(1, &m_FramebufferID);
		glDeleteTextures(1, &m_TextureID);
		glDeleteRenderbuffers(1, &m_RenderbufferID);


		m_Specification = spec;
		glGenTextures(1, &m_TextureID);
		glGenRenderbuffers(1, &m_RenderbufferID);
		glGenFramebuffers(1, &m_FramebufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);

		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Specification.width, m_Specification.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureID, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindRenderbuffer(GL_RENDERBUFFER, m_RenderbufferID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Specification.width, m_Specification.height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderbufferID);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			Log::printError("Framebuffer is not complete!", Log::getCoreLogger());

		glViewport(0, 0, m_Specification.width, m_Specification.height);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::ResetFramebuffer(const FramebufferSpecification&& spec) {
		glDeleteTextures(1, &m_TextureID);
		glDeleteRenderbuffers(1, &m_RenderbufferID);
		glDeleteFramebuffers(1, &m_FramebufferID);



		m_Specification = spec;
		glGenTextures(1, &m_TextureID);
		glGenRenderbuffers(1, &m_RenderbufferID);
		glGenFramebuffers(1, &m_FramebufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);

		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Specification.width, m_Specification.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureID, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindRenderbuffer(GL_RENDERBUFFER, m_RenderbufferID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Specification.width, m_Specification.height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderbufferID);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			Log::printError("Framebuffer is not complete!", Log::getCoreLogger());

		glViewport(0, 0, m_Specification.width, m_Specification.height);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::UnBind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST);
	}

}