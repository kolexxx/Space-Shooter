#include "Camera.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

extern GLFWwindow* window;

namespace Camera
{
	static glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
	static glm::mat4 ViewMatrix;
	static glm::mat4 ProjectionMatrix = glm::ortho( -1024.0f / 2.0f, 1024.0f / 2.0f, -768.0f / 2.0f, 768.0f / 2.0f );
	static glm::mat4 ViewProjectionMatrix;

	const glm::mat4& GetView()
	{
		return ViewMatrix;
	}

	const glm::mat4& GetProjection()
	{
		return ProjectionMatrix;
	}

	const glm::mat4& GetViewProjection()
	{
		return ViewProjectionMatrix;
	}
}