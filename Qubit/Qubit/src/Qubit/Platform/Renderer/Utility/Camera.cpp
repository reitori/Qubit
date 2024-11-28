#include <QubitPCH.h>
#include "Qubit/Platform/Renderer/Utility/camera.h"

namespace Qubit {
	Camera::Camera(glm::vec3 cameraStartPos = glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3 cameraFrontOf = glm::vec3(0.0f, 0.0f, -1.0f), float startZoom = 1.0f, float maxZoom = 100.0f) : cameraFront(cameraFrontOf), cameraPos(cameraStartPos), zoom(startZoom), zoomMax(maxZoom) {
		yaw = -90.0f;
		pitch = 0.0f;
		rotYAxis = glm::normalize(glm::cross(cameraFront, worldUp));
		view = glm::mat4(1.0f);
		lookAtPoint = glm::vec3(0.0f, 0.0f, 0.0f);
		updateCameraVectors();
	}

	void Camera::mouseMovement(double xpos, double ypos) {
		mouseSlope.x = mousePressedPos.x - xpos;
		mouseSlope.y = mousePressedPos.y - ypos;
		mousePressedPos.x = xpos;
		mousePressedPos.y = ypos;
		switch (mouseDown) {
		case panButtonDown:
			cameraRight *= 15 * mouseSlope.x;
			cameraUp *= 15 * -mouseSlope.y;
			cameraPos += speed * (cameraUp + cameraRight);
			lookAtPoint = zoom * cameraFront + cameraPos;
			updateCameraVectors();
			break;

		case rotateButtonDown:
			float s = -(150 * speed);
			yaw += s * mouseSlope.x;
			pitch += s * mouseSlope.y;

			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;

			cameraPos += glm::vec3((-cos(glm::radians(yaw)) * cos(glm::radians(pitch)) * zoom) - cameraPos.x, (sin(glm::radians(pitch)) * zoom) - cameraPos.y, (-sin(glm::radians(yaw)) * cos(glm::radians(pitch)) * zoom) - cameraPos.z);

			cameraFront = glm::normalize(lookAtPoint - cameraPos);
			updateCameraVectors();
			break;
		}
	}



	void Camera::mouseButtonInput(double mousePressedX, double mousePressedY) {
		mousePressedPos.x = (float)mousePressedX;
		mousePressedPos.y = (float)mousePressedY;
	}

	void Camera::cameraReset() {
		cameraPos = glm::vec3(0.0f, 0.0f, -5.0f);
		lookAtPoint = glm::vec3(0.0f, 0.0f, -5.0f);
	}

	void Camera::updateViewMatrix() {
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}

	void Camera::updateCameraVectors() {
		cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
		cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
	}

	void Camera::processZoom(float yOffset) {
		zoom -= (float)yOffset;
		if (zoom < 1.0f) {
			zoom = 1.0f;
		}
		if (zoom > zoomMax) {
			zoom = zoomMax;
		}

		cameraPos = -cameraFront * zoom;
		updateCameraVectors();
	}
}