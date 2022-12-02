#include "Time.hpp"

#include "GLFW/glfw3.h"

float Time::Delta()
{
	return s_delta;
}

float Time::Now()
{
	return glfwGetTime();
}

unsigned int Time::Tick()
{
	return s_tick;
}

float Time::s_delta = 0.0f;

unsigned int Time::s_tick = 0;