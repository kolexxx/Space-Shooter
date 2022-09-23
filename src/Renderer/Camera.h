#include <glm/glm.hpp>

namespace Camera
{
	void ComputeMatrixFromInput();
	const glm::mat4& GetView();
	const glm::mat4& GetProjection();
	const glm::mat4& GetViewProjection();
}