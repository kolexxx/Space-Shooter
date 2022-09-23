#include "Camera.h"

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

	float speed = 5.0f;

	void ComputeMatrixFromInput()
	{
		if ( glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS )
			Position.y += speed;
		if ( glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS )
			Position.y -= speed;
		if ( glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS )
			Position.x -= speed;
		if ( glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS )
			Position.x += speed;

		ViewMatrix = glm::inverse( glm::translate( glm::mat4( 1.0f ), Position ) ) *
			glm::rotate( glm::mat4( 1.0f ), glm::radians( 45.0f ), glm::vec3( 0, 0, 1 ) );

		ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}

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