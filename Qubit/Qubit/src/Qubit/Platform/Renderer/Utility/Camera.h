#pragma once
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utility>

namespace Qubit {
	enum mouseButton {
		panButtonDown,
		rotateButtonDown,
		none
	};

	class Camera {
	public:
		Camera(glm::vec3 cameraStartPos, glm::vec3 lookAt, float startZoom, float zoomMax);
		//mouseMoveEvent(QubitEvent e);
		//mouseButtonEvent(QubitEvent e);
		//mouseScrollMoved(QubitEvent e)

		//void mouseMovement(QubitEvent &e);
		//void mouseButtonInput(QubitEvent &e);

		void mouseMovement(double xpos, double ypos);
		void mouseButtonInput(double mousePressedX, double mousePressedY);
		void updateCameraVectors();
		void cameraReset();
		void updateViewMatrix();
		void processZoom(float yOffset);
		void setMouseButton(mouseButton& button) { mouseDown = button; }
		void setMouseButton(mouseButton&& button) { mouseDown = button; }

		glm::vec3 cameraPos;
		glm::vec3 translatePos;
		glm::vec3 rotYAxis;
		glm::vec3 cameraFront;
		glm::vec3 cameraRight;
		glm::vec3 cameraUp;
		glm::vec3 lookAtPoint;
		glm::mat4 view;

		float speed, scaleValue, zoom, zoomMax;
		unsigned int multiplier;
	private:
		mouseButton mouseDown = mouseButton::none;

		float currentSpeed;
		
		Qubit::pair<float, float> mousePressedPos;
		Qubit::pair<float, float> mouseSlope;

		glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
		float yaw, pitch, deltaTime;
	};
}