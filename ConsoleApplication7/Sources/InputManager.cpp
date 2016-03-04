#include "../Headers/InputManager.h"
#include "../Headers/Camera.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::KeyPressed(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
	/*if (_action == GLFW_PRESS || _action == GLFW_REPEAT)
	{
		switch (_key)
		{
			case GLFW_KEY_W:
				Camera::GetInstance()->Move(Camera::MOVE_DIRECTION::FORWARD);
				break;
			case GLFW_KEY_A:
				Camera::GetInstance()->Move(Camera::MOVE_DIRECTION::LEFT);
				break;
			case GLFW_KEY_S:
				Camera::GetInstance()->Move(Camera::MOVE_DIRECTION::BACKWARD);
				break;
			case GLFW_KEY_D:
				Camera::GetInstance()->Move(Camera::MOVE_DIRECTION::RIGHT);
				break;
			case GLFW_KEY_UP:
				Camera::GetInstance()->Rotate(Camera::ROTATION_DIRECTION::UP);
				break;
			case GLFW_KEY_LEFT:
				Camera::GetInstance()->Rotate(Camera::ROTATION_DIRECTION::LEFT);
				break;
			case GLFW_KEY_DOWN:
				Camera::GetInstance()->Rotate(Camera::ROTATION_DIRECTION::DOWN);
				break;
			case GLFW_KEY_RIGHT:
				Camera::GetInstance()->Rotate(Camera::ROTATION_DIRECTION::RIGHT);
				break;
		}
	}*/
}
