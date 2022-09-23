#include "Renderer.h"

#include "Camera.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"

struct Vertex
{
	glm::vec2 Position;
	glm::vec3 Color;
	glm::vec2 UV;
	float TextureID;
};

extern GLFWwindow* window;

static const unsigned int MaxVertices = 4000;
static const unsigned int MaxIndices = 6000;
static const unsigned int MaxTextures = 32;

namespace Renderer
{
	static Shader* shader;
	static GLuint vertexArray;
	static VertexBuffer* vertexBuffer;
	static IndexBuffer* indexBuffer;

	static Vertex* vertices = nullptr;
	static Vertex* verticesCurrPtr = nullptr;

	static unsigned short* indices = nullptr;
	static unsigned short* indicesCurrPtr = nullptr;

	void Init()
	{
		if ( shader != nullptr )
			return;

		glClearColor( 0.26f, 0.27f, 0.29f, 1.0f );

		shader = new Shader( "shaders/VertexShader.glsl", "shaders/FragmentShader.glsl" );

		glGenVertexArrays( 1, &vertexArray );
		glBindVertexArray( vertexArray );

		vertices = new Vertex[MaxVertices];
		indices = new unsigned short[MaxIndices];

		vertexBuffer = new VertexBuffer( MaxVertices * sizeof( Vertex ), nullptr, GL_DYNAMIC_DRAW );
		indexBuffer = new IndexBuffer( MaxIndices * sizeof( unsigned short ), nullptr, GL_DYNAMIC_DRAW );

		vertexBuffer->Bind();

		glEnableVertexArrayAttrib( vertexArray, 0 );
		glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void* ) offsetof( Vertex, Position ) );

		glEnableVertexArrayAttrib( vertexArray, 1 );
		glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void* ) offsetof( Vertex, Color ) );

		glEnableVertexArrayAttrib( vertexArray, 2 );
		glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void* ) offsetof( Vertex, UV ) );

		glEnableVertexArrayAttrib( vertexArray, 3 );
		glVertexAttribPointer( 3, 1, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void* ) offsetof( Vertex, TextureID ) );
	}

	void Shutdown()
	{
		delete shader;
		glDeleteVertexArrays( 1, &vertexArray );
		delete[] vertices;
		delete[] indices;
		delete vertexBuffer;
		delete indexBuffer;
	}

	void BeginBatch()
	{
		verticesCurrPtr = vertices;
		indicesCurrPtr = indices;
	}

	void EndBatch()
	{
		auto size = verticesCurrPtr - vertices;
		vertexBuffer->Bind();
		glBufferSubData( GL_ARRAY_BUFFER, 0, size * sizeof( Vertex ), vertices );

		size = indicesCurrPtr - indices;
		indexBuffer->Bind();
		glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, 0, size * sizeof( unsigned short ), indices );
	}

	void Flush()
	{
		glClear( GL_COLOR_BUFFER_BIT );

		shader->Use();
		shader->SetUniform1i( "u_Texture", 0 );
		shader->SetUniformMatrix4f( "u_Projection", Camera::GetProjection() );

		glBindVertexArray( vertexArray );
		auto count = indicesCurrPtr - indices;

		glDrawElements( GL_TRIANGLES, count, GL_UNSIGNED_SHORT, ( void* ) 0 );

		glfwSwapBuffers( window );

		glfwPollEvents();
	}

	void DrawTriangle( const glm::vec2& a, const glm::vec2& b, const glm::vec2& c, glm::vec3 color )
	{
		auto index = unsigned short( verticesCurrPtr - vertices );

		*verticesCurrPtr =
		{
			a,
			color,
			glm::vec2(),
			0.0f
		};
		verticesCurrPtr++;

		*verticesCurrPtr =
		{
			b,
			color,
			glm::vec2(),
			0.0f
		};
		verticesCurrPtr++;

		*verticesCurrPtr =
		{
			c,
			color,
			glm::vec2(),
			0.0f
		};
		verticesCurrPtr++;

		indicesCurrPtr[0] = index;
		indicesCurrPtr[1] = index + 1;
		indicesCurrPtr[2] = index + 2;

		indicesCurrPtr += 3;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="position">The center of the quad.</param>
	/// <param name="size"></param>
	/// <param name="color"></param>
	void DrawQuad( const glm::vec2& position, const glm::vec2& size, const glm::vec3& color )
	{
		auto index = unsigned short( verticesCurrPtr - vertices );
		auto halfWidth = size.x / 2.0f;
		auto halfHeight = size.y / 2.0f;

		*verticesCurrPtr =
		{
			glm::vec2( position.x - halfWidth, position.y - halfHeight ),
			color,
			glm::vec2(),
			0.0f
		};
		verticesCurrPtr++;

		*verticesCurrPtr =
		{
			glm::vec2( position.x + halfWidth, position.y - halfHeight ),
			color,
			glm::vec2(),
			0.0f
		};
		verticesCurrPtr++;

		*verticesCurrPtr =
		{
			glm::vec2( position.x + halfWidth, position.y + halfHeight ),
			color,
			glm::vec2(),
			0.0f
		};
		verticesCurrPtr++;

		*verticesCurrPtr =
		{
			glm::vec2( position.x - halfWidth, position.y + halfHeight ),
			color,
			glm::vec2(),
			0.0f
		};
		verticesCurrPtr++;

		indicesCurrPtr[0] = index;
		indicesCurrPtr[1] = index + 1;
		indicesCurrPtr[2] = index + 2;
		indicesCurrPtr[3] = index + 3;
		indicesCurrPtr[4] = index + 2;
		indicesCurrPtr[5] = index;

		indicesCurrPtr += 6;
	}

	void DrawQuad( const glm::vec2& position, const glm::vec2& size, const Texture& texture )
	{
		auto index = unsigned short( verticesCurrPtr - vertices );
		auto halfWidth = size.x / 2.0f;
		auto halfHeight = size.y / 2.0f;

		*verticesCurrPtr =
		{
			glm::vec2( position.x - halfWidth, position.y - halfHeight ),
			glm::vec3( 1.0f ),
			glm::vec2( 0.0f, 1.0f ),
			static_cast< float >( texture.Slot() )
		};
		verticesCurrPtr++;

		*verticesCurrPtr =
		{
			glm::vec2( position.x + halfWidth, position.y - halfHeight ),
			glm::vec3( 1.0f ),
			glm::vec2( 1.0f, 1.0f ),
			static_cast< float >( texture.Slot() )
		};
		verticesCurrPtr++;

		*verticesCurrPtr =
		{
			glm::vec2( position.x + halfWidth, position.y + halfHeight ),
			glm::vec3( 1.0f ),
			glm::vec2( 1.0f, 0.0f ),
			static_cast< float >( texture.Slot() )
		};
		verticesCurrPtr++;

		*verticesCurrPtr =
		{
			glm::vec2( position.x - halfWidth, position.y + halfHeight ),
			glm::vec3( 1.0f ),
			glm::vec2( 0.0f, 0.0f ),
			static_cast< float >( texture.Slot() )
		};
		verticesCurrPtr++;

		indicesCurrPtr[0] = index;
		indicesCurrPtr[1] = index + 1;
		indicesCurrPtr[2] = index + 2;
		indicesCurrPtr[3] = index + 3;
		indicesCurrPtr[4] = index + 2;
		indicesCurrPtr[5] = index;

		indicesCurrPtr += 6;
	}
}