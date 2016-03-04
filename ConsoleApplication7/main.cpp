// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include "Utils/Shader.h"
#include "Headers/Globals.h"
#include "Headers/Model3D.h"
#include "Headers/Element2D.h"
#include "Headers/InputManager.h"
#include "Headers/Camera.h"
#include "Utils/utilsMath.h"
#include "Headers/Font.h"
#include "Headers/Map.h"

#include "DEBUG_MODEL.h"

#include <iostream>
#include <vector>

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")

Model3D model;
Element2D MainMenu;
Element2D PlayButton;
Element2D ExitButton;
Element2D GamePanel;
Map map;
glm::mat4 world;
Font font;

Element2D circle;
Element2D line;
Element2D grid;

std::vector<DEBUG_Model3D> toDraw;

// For FPS computation
double lastTime = glfwGetTime();
int nbFrames = 0;
char text[256];

void printFPS()
{
	// FPS speed
	double currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1sec ago
										 // printf and reset
		sprintf_s(text, "%i fps : %.0f", nbFrames, lastTime);
		nbFrames = 0;
		lastTime += 1.0;
	}
	font.PrintText(text, 0, 570, 25);

	model.IncreaseXCoord(0.01);
	model.IncreaseYCoord(0.012);
}

void Draw()
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//circle.DrawCircle(model.GetXCoord(), model.GetYCoord());
	//line.DrawLine();
	grid.DrawGrid();
	printFPS();
	model.Draw();
	map.Draw();
	/*for (auto & elem : toDraw)
	{
		elem.Draw();
	}
	GamePanel.Draw();*/
	
	

	glDisable(GL_BLEND);

	int core = glGetError();

	// Swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();

	
}

void intersect(vec3 fr_0, vec3 fr_1, vec3 fr_2, vec3 &target)
{

	float fn00 = fr_1.length();
	float fn01 = dot(fr_1, fr_2);
	float fn11 = fr_2.length();
	float det = fn00*fn11 - fn01*fn01;


	float invdet = 1.0 / det;

	float fc0 = (fn11 * 100.0 + fn01 * 0) * invdet;
	float fc1 = (fn00 * 0 + fn01 * 100.0) * invdet;

	vec3 o = cross(fr_1, fr_2);

	vec3 o2 = fr_1* vec3(fc0) + fr_2*vec3(fc1);

	int asdxcvcx = 123;

	float t2 = dot(fr_0, o);
	float t = -(dot(fr_0, o2) + 100.0) / t2;

	target = o2 + (o * t);
}

bool IsClickOnModel(float x, float y)
{
	if (  abs(model.GetXCoord() - x) < 0.2 && abs(model.GetYCoord() - y) < 0.2)
	{
		return true;
	}

	return false;
}

void func(GLFWwindow* _window, int _key, int _action, int _mods)
{
	//InputManager::GetInstance()->KeyPressed(_window, _key, _scancode, _action, _mods);
	if (_key == GLFW_MOUSE_BUTTON_RIGHT && _action == GLFW_PRESS)
	{
#pragma region asd
		DEBUG_Model3D mod2;

		Camera * cam = Camera::GetInstance();


		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		float x1 = -1 + ((xpos / Globals::screenWidth) * 2.0);
		float y1 = -1 + ((ypos / Globals::screenHeight) * 2.0);

		float x = (xpos / Globals::screenWidth);
		float y = (ypos / Globals::screenHeight);

		vec3 direction(
			cos(cam->m_verticalAngle) * sin(cam->m_horizontalAngle),
			sin(cam->m_verticalAngle),
			cos(cam->m_verticalAngle) * cos(cam->m_horizontalAngle)
			);



		mat4 proj = cam->m_projectionMatrix;
		mat4 modl = cam->m_viewMatrix;
		float   proj2[16];
		//float   modl[16];
		//float   clip[16];

		glGetFloatv(GL_PROJECTION_MATRIX, proj2);
		//glGetFloatv(GL_MODELVIEW_MATRIX, modl);

		mat4 clip2 = proj * modl;
		mat4 clip = proj * modl * world;


		mat4 frustum;
		mat4 frustum2;

		//left
		frustum(0) = clip(3) + clip(0);
		frustum(1) = clip(7) + clip(4);
		frustum(2) = clip(11) + clip(8);
		frustum(3) = clip(15) + clip(12);

		float l = frustum[0].length();
		frustum(0) /= l;
		frustum(1) /= l;
		frustum(2) /= l;
		frustum(3) /= l;

		//right
		frustum(12) = clip(3) - clip(0);
		frustum(13) = clip(7) - clip(4);
		frustum(14) = clip(11) - clip(8);
		frustum(15) = clip(15) - clip(12);

		l = frustum[3].length();
		frustum(12) /= l;
		frustum(13) /= l;
		frustum(14) /= l;
		frustum(15) /= l;
		/*frustum(12) /= l;
		frustum(13) /= -l;
		frustum(14) = frustum(2);
		frustum(15) /= -l;*/

		//far
		frustum(4) = clip(3) - clip(2);
		frustum(5) = clip(7) - clip(6);
		frustum(6) = clip(11) - clip(10);
		frustum(7) = clip(15) - clip(14);

		 l = frustum[1].length();
		frustum(4) /= l;
		frustum(5) /= l;
		frustum(6) /= l;
		frustum(7) /= l;

		//top
		frustum(8) = clip(3) - clip(1);
		frustum(9) = clip(7) - clip(5);
		frustum(10) = clip(11) - clip(9);
		frustum(11) = clip(15) - clip(13);

		 l = frustum[2].length();
		frustum(8) /= l;
		frustum(9) /= l;
		frustum(10) /= l;
		frustum(11) /= l;

		//bot
		frustum2(0) = clip(3) + clip(1);
		frustum2(1) = clip(7) + clip(5);
		frustum2(2) = clip(11) + clip(9);
		frustum2(3) = clip(15) + clip(13);

		l = frustum2[0].length();
		frustum2(0) /= l;
		frustum2(1) /= l;
		frustum2(2) /= l;
		frustum2(3) /= l;

		vec3 fr_0 = vec3(frustum[0]); // left
		vec3 fr_1 = vec3(frustum[1]); // far
		vec3 fr_2 = vec3(frustum[2]); // top
		vec3 fr_3 = vec3(frustum[3]); // right
		vec3 fr_4 = vec3(frustum2[0]); // bot

		vec3 farLeftUp, tmp1, tmp2;
		intersect(fr_0, fr_1, fr_2, farLeftUp);
		intersect(fr_3, fr_1, fr_2, tmp1);
		intersect(fr_0, fr_1, fr_4, tmp2);

		vec3 lefttotopright = tmp1 - farLeftUp;
		vec3 uptodown = tmp2 - farLeftUp;

		vec3 end = farLeftUp + (lefttotopright * x) + (uptodown * y);

		vec3 start = cam->m_position +(lefttotopright * (x - 0.5f)) + (uptodown * (y - 0.5f));
		
		vec3 dir = start - end;

		//vec3 tmp = (vec3(x *10,0.0, y) * cam->m_position);
		//vec3 tmp2 = (1.0f * cam->m_position);

		//float qwe = tmp2.z + (tmp.z / 1.2) * 0.9;

		float sdf = vec3(cam->m_position + direction).length();
		vec3 er = ((cam->m_position + direction) / sdf);
#pragma endregion asd

		

		//vec3 X = vec3(tmp13.x/ (-1.34)/*tmp2.x + (tmp.x/(cam->m_position.x / cam->m_position.y)) * 0.9*/, cam->m_position.y, cam->m_position.z); //+ vec3((cam->m_position.y * 0.65) * tmp13.x, 0.0, (cam->m_position.z * 0.9) * tmp13.y);
		vec3 X = cam->m_position;//vec3(cam->m_position.x+ (cam->m_position.x + ((end.x - start.x) * x1)), cam->m_position.y,cam->m_position.z);// cam->m_position.z + (cam->m_position.y / 1.2085f) * y)/*vec3(x, 0.0f, 0.0)*/;
		vec3 Y = cam->m_position + direction;

		/*vec3 A(1.0, 0.0, 1.0);
		vec3 B(1.0, 0.0, 2.0);
		vec3 C(3.0, 0.0, 4.0);*/

		vec3 A(1.0, 0.0, 1.0);
		vec3 B(1.0, 0.0, 2.0);
		vec3 C(3.0, 0.0, 4.0);

		vec3 N = cross(B - A, C - A);
		
		vec3 V = A - X;

		float d = dot(N, V);
		vec3 W = Y - X;

		float e = dot(N, W);

		vec3 result = X + W * (d / e);

		if (IsClickOnModel(result.x, result.z))
		{
			circle.SetIsInited(true);
		}
		else
		{
			circle.SetIsInited(true);
		}

//		int a = 123;

		//double xpos, ypos;
		//glfwGetCursorPos(window, &xpos, &ypos);

		//float x = -1 + ((xpos / Globals::screenWidth) * 2.0);
		//float y = -1 + ((ypos / Globals::screenHeight) * 2.0);

		//DEBUG_Model3D mod;
		//DEBUG_Model3D mod2;
		//Camera * cam = Camera::GetInstance();

		//glm::vec3 tmp1 = cam->m_position;

		//float off = (cam->m_position.y / glm::tan(cam->m_verticalAngle));
		//if( y < 0.0)
		//	off -= (off * y) * 1.25;
		//else
		//	off -= (off * y);

		//auto adas = (Camera::GetInstance()->GetProjectionMatrix() * Camera::GetInstance()->GetViewMatrix() * world);

		////auto tmp12 = (Camera::GetInstance()->GetProjectionMatrix() * Camera::GetInstance()->GetViewMatrix() * world) * glm::vec4(0.0, 0.0, 0.0, 1.0);
		//auto tmp13 = (Camera::GetInstance()->GetProjectionMatrix() * Camera::GetInstance()->GetViewMatrix() * world) * glm::vec4(x, y, 0.0, 1.0);
		//auto tmp14 = (Camera::GetInstance()->GetProjectionMatrix() * Camera::GetInstance()->GetViewMatrix() * world) * glm::vec4(0.0, 0.0, 0.0, 1.0);
		//auto tmp15 = tmp14 - tmp13;
		////auto tmp13 = (Camera::GetInstance()->GetProjectionMatrix() * Camera::GetInstance()->GetViewMatrix() * world) * glm::vec4((xpos / Globals::screenWidth), (ypos / Globals::screenHeight), 0.0, 1.0);
		////auto tmp14 = tmp12 - tmp13;
		///*auto tmp13 = (Camera::GetInstance()->GetProjectionMatrix() * Camera::GetInstance()->GetViewMatrix() * world) * glm::vec4(tmp1.x, 3.0, tmp1.z + off, 1.0);
		//auto tmp14 = (Camera::GetInstance()->GetProjectionMatrix() * Camera::GetInstance()->GetViewMatrix() * world) * glm::vec4(tmp1.x + 10.1, 3.0, tmp1.z + off, 1.0);*/

		//glm::vec3 center(tmp1.x - tmp15.x * 3.25, 0.0, tmp1.z + off);
		////glm::vec3 offset(center.x *x, 0.0, center.z  -( off* y));
		////glm::vec3 result(center.x + offset.x, 0.0, center.z + offset.z);
		//glm::vec3 result(center.x, 0.0, center.z);

		//auto v1 = (Camera::GetInstance()->GetProjectionMatrix() * Camera::GetInstance()->GetViewMatrix() * world) * glm::vec4(x, 0.0, y, 1.0);
		//auto v2 = (Camera::GetInstance()->GetProjectionMatrix() * Camera::GetInstance()->GetViewMatrix() * world) * glm::vec4(x, 3.0, y, 1.0);
		//auto v3 = (Camera::GetInstance()->GetProjectionMatrix() * Camera::GetInstance()->GetViewMatrix() * world) * glm::vec4(x + 0.1, 3.0, y, 1.0);

		//mod2.Init(glm::vec3(result.x, 0.0, result.z), glm::vec3(result.x, 3.0, result.z), glm::vec3(result.x +0.1, 3.0, result.z), "Resources/Textures/Map.tga", "Shaders/3DDebugModelShader.vs", "Shaders/3DDebugModelShader.fs");
		//mod2.Init(glm::vec3(result.x, 0.0, 0.0), glm::vec3(result.x, result.y, 3.0), glm::vec3(result.x + 0.1, result.y + 0.1, 3.0), "Resources/Textures/Map.tga", "Shaders/3DDebugModelShader.vs", "Shaders/3DDebugModelShader.fs");
		////mod2.Init(glm::vec3(tmp12.x, tmp12.y, tmp12.z), glm::vec3(tmp13.x, tmp13.y, tmp13.z), glm::vec3(tmp14.x, tmp14.y, tmp14.z), "Resources/Textures/Map.tga", "Shaders/3DDebugModelShader.vs", "Shaders/3DDebugModelShader.fs");
		//mod2.Init(v1, v2, v3, "Resources/Textures/Map.tga", "Shaders/3DDebugModelShader.vs", "Shaders/3DDebugModelShader.fs");
		//toDraw.push_back(mod);
		//toDraw.push_back(mod2);
	}
}

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(Globals::screenWidth, Globals::screenHeight, "Tutorial 02 - Red triangle", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//glfwSetKeyCallback(window, &func);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);

	glfwSetScrollCallback(window, &(Camera::ScrollFunction));
	glfwSetMouseButtonCallback(window, &func);

	world = glm::mat4(1.0);

	font.Init("Resources/Fonts/Holstein.DDS", "Shaders/TextShader.vs", "Shaders/TextShader.fs");
	GamePanel.Init("Resources/Models/GamePanel.nfg", "Resources/Textures/GamePanel.tga", "Shaders/2DElementShader.vs", "Shaders/2DElementShader.fs");
	
	map.Init(10, 10, "Resources/Models/Map.nfg", "Resources/Textures/Map.tga", "Shaders/3DSimpleModelShader.vs", "Shaders/3DSimpleModelShader.fs");
	
	model.Init("Resources/Models/Woman1.nfg", "Resources/Textures/Woman1.tga", "Shaders/3DSimpleModelShader.vs", "Shaders/3DSimpleModelShader.fs");

	circle.InitCircle("Shaders/Simple2DElementShader.vs", "Shaders/Simple2DElementShader.fs");

	line.InitLine("Shaders/Simple2DElementShader.vs", "Shaders/Simple2DElementShader.fs");

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			/*DEBUG_Model3D mod2;
			Cell tmp = map.GetCells().at(i).at(j);
			mod2.Init(glm::vec3(tmp.GetXCoord(), 0.0, tmp.GetYCoord()), glm::vec3(tmp.GetXCoord(), 1.0, tmp.GetYCoord()), glm::vec3(tmp.GetXCoord() + 0.1, 1.0, tmp.GetYCoord()), "Resources/Textures/Map.tga", "Shaders/3DDebugModelShader.vs", "Shaders/3DDebugModelShader.fs");
			toDraw.push_back(mod2);*/
		}
	}

	grid.InitGrid(map.GetCells(), "Shaders/Simple2DElementShader.vs", "Shaders/Simple2DElementShader.fs");
	
	sprintf_s(text, "%i fps", 0);

	do {

		Camera::GetInstance()->UpdateMoveAndRotation();
		Draw();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

