#include "../Headers/Camera.h"
#include "../Headers/Globals.h"

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

using namespace glm;

#include <iostream>
#include "../Headers/Globals.h"

extern GLFWwindow* window;

Camera::Camera()
: m_movementSpeed(3.0f),
m_rotationSpeed(0.005f),
m_fov(45.0f),
m_position(5.0, 5.0, 5.00),
m_horizontalAngle(glm::pi<float>()),
m_verticalAngle(-1.0f),
m_lastMousePosX(Globals::screenWidth / 2),
m_lastMousePosY(Globals::screenHeight / 2),
m_souldUpdateCameraInitialPos(true)
{
}

Camera::~Camera()
{
}

void Camera::ScrollFunction(GLFWwindow *, double _x, double _y)
{
	Camera::GetInstance()->CalculateMove( _x,  _y);
}

void Camera::CalculateMove(double _x, double _y)
{
	// glfwGetTime is called only once, the first time this function is called
		static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = 0.0169f;// float(currentTime - lastTime);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(m_horizontalAngle - 3.14f / 2.0f),
		0,
		cos(m_horizontalAngle - 3.14f / 2.0f)
		);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(m_verticalAngle) * sin(m_horizontalAngle),
		sin(m_verticalAngle),
		cos(m_verticalAngle) * cos(m_horizontalAngle)
		);

	// Up vector
	glm::vec3 up = glm::cross(right, direction);

	// Move forward
	if (_y > 0) 
	{
		glm::vec3 tmp = direction * deltaTime * (m_movementSpeed * 3.0f);
		m_position += direction * deltaTime * (m_movementSpeed * 3.0f);
	}
	else
	{
		m_position -= direction * deltaTime * (m_movementSpeed * 3.0f);
	}

	float FoV = m_fov;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

					  // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	m_projectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 3000.0f);
	// Camera matrix
	m_viewMatrix = glm::lookAt(
		m_position,           // Camera is here
		m_position + direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
		);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}

void Camera::UpdateMoveAndRotation()
{
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = 0.0169f;// float(currentTime - lastTime);

	

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(m_verticalAngle) * sin(m_horizontalAngle),
		sin(m_verticalAngle),
		cos(m_verticalAngle) * cos(m_horizontalAngle)
		);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(m_horizontalAngle - glm::pi<float>() / 2.0f),
		0,
		cos(m_horizontalAngle - glm::pi<float>() / 2.0f)
		);

	// Forward vector
	glm::vec3 forward = glm::vec3(
		0,
		0,
		sin(m_horizontalAngle - glm::pi<float>() / 2.0f)
		);

	// Up vector
	glm::vec3 up = glm::cross(right, direction);

	// Move forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		m_position -= forward * deltaTime * m_movementSpeed;
		//m_position.z = m_position.z <= -10.0 ? -10.0f : m_position.z;
	}
	// Move backwards
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		m_position += forward * deltaTime * m_movementSpeed;
		//m_position.z = m_position.z >= 10.0 ? 10.0f : m_position.z;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		m_position += right * deltaTime * m_movementSpeed;
		//m_position.x = m_position.x >= 5.0 ? 5.0f : m_position.x;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		m_position -= right * deltaTime * m_movementSpeed;
		//m_position.x = m_position.x <= -7.0 ? -7.0f : m_position.x;
	}

	// Get mouse position
	double xpos, ypos;
	
	// Rotate left
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
	
		if (m_souldUpdateCameraInitialPos)
		{
			glfwGetCursorPos(window, &xpos, &ypos);
			m_lastMousePosX = xpos;
			m_lastMousePosY = ypos;
			m_souldUpdateCameraInitialPos = false;
		}
		else
		{
			glfwGetCursorPos(window, &xpos, &ypos);
		}

		// Compute new orientation
		m_horizontalAngle += m_rotationSpeed *float(m_lastMousePosX - xpos);
		m_verticalAngle += m_rotationSpeed *float(m_lastMousePosY - ypos);
		
		m_lastMousePosX = xpos;
		m_lastMousePosY = ypos;
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		m_souldUpdateCameraInitialPos = true;
	}


	float FoV = glm::pi<float>() / 2.5f;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

						   // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	//m_projectionMatrix = glm::perspective(FoV, 16.0f / 9.0f, 0.1f, 100.0f);
	m_projectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);



	glm::vec3 tmp = m_position + direction;
	// Camera matrix
	m_viewMatrix = glm::lookAt(
		m_position,           // Camera is here
		m_position + direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
		);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}

const glm::mat4 & Camera::GetWorldMatrix() const
{
	return m_worldMatrix;
}

const glm::mat4 & Camera::GetViewMatrix() const
{
	return m_viewMatrix;
}

const glm::mat4 & Camera::GetProjectionMatrix() const
{
	return m_projectionMatrix;
}
