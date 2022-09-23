#pragma once

#include <glm/glm.hpp>

#include "Texture.h"

namespace Renderer
{
	void Init();
	void Shutdown();

	void BeginBatch();
	void EndBatch();
	void Flush();

	void DrawTriangle( const glm::vec2& a, const glm::vec2& b, const glm::vec2& c, const glm::vec3& color );
	void DrawQuad( const glm::vec2& position, const glm::vec2& size, const glm::vec3& color );
	void DrawQuad( const glm::vec2& position, const glm::vec2& size, const Texture& texture );
}