#pragma once

namespace Qubit {
	class OpenGLContext {
	public:
		OpenGLContext() = default;

		virtual void Initialize() = 0;
		virtual ~OpenGLContext() = default;
	};
}