#include "Input.hpp"

#include <GLFW/glfw3.h>

extern GLFWwindow* window;

bool Input::Pressed(char key)
{
	return s_pressed[key];
}

bool Input::Down(char key)
{
	return s_down[key];
}

bool Input::Released(char key)
{
	return s_released[key];
}

void Input::Build()
{
	for (char c = 0; c <= 'Z'; c++)
	{
		s_pressed[c] = !s_down[c] && glfwGetKey(window, c) == GLFW_PRESS;
		auto wasDown = s_down[c];
		s_down[c] = glfwGetKey(window, c) == GLFW_PRESS;
		s_released[c] = wasDown && !s_down[c];
	}
}

std::array<bool, 91> Input::s_pressed{};
std::array<bool, 91> Input::s_down{};
std::array<bool, 91> Input::s_released{};