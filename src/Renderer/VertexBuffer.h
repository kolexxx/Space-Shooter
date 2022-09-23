#pragma once

#include "GLObject.h"

class VertexBuffer : GLObject
{
public:
	VertexBuffer( GLsizeiptr size, const void* data, GLenum usage = GL_STATIC_DRAW );
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};