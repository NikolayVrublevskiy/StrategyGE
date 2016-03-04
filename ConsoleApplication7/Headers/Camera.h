#pragma once
#include "../Utils/utilsMath.h"
#include "ISingleton.h"

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera : public ISingleton<Camera>
{
	friend class ISingleton<Camera>;

public:

	Camera();
	~Camera();

	void UpdateMoveAndRotation();

	void static ScrollFunction(GLFWwindow *, double, double);
	void CalculateMove(double _x, double _y);


	const glm::mat4 & GetWorldMatrix() const;
	const glm::mat4 & GetViewMatrix() const;
	const glm::mat4 & GetProjectionMatrix() const;

private:
public:
	glm::vec3 m_position;
	float m_movementSpeed;
	float m_rotationSpeed;

	glm::mat4 m_worldMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

	GLfloat m_fov;

	GLfloat m_horizontalAngle;
	GLfloat m_verticalAngle;

	double m_lastMousePosX;
	double m_lastMousePosY;
	bool m_souldUpdateCameraInitialPos;
};