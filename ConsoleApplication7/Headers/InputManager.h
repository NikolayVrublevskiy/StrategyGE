#pragma once
#include "ISingleton.h"
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>


class InputManager : public ISingleton<InputManager>
{
	friend class ISingleton<InputManager>;

public:
	InputManager();
	~InputManager();

	void KeyPressed(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
};