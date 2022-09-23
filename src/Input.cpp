#include "Input.h"

#include <GLFW/glfw3.h>

extern GLFWwindow* window;

bool Input::Pressed( char key )
{
	return s_Pressed[key];
}

bool Input::Down( char key )
{
	return s_Down[key];
}

bool Input::Released( char key )
{
	return s_Released[key];
}

void Input::Build()
{
	for ( char c = 0; c <= 'Z'; c++ )
	{
		s_Pressed[c] = !s_Down[c] && glfwGetKey( window, c ) == GLFW_PRESS;
		auto wasDown = s_Down[c];
		s_Down[c] = glfwGetKey( window, c ) == GLFW_PRESS;
		s_Released[c] = wasDown && !s_Down[c];
	}
}

std::array<bool, 91> Input::s_Pressed{};
std::array<bool, 91> Input::s_Down{};
std::array<bool, 91> Input::s_Released{};