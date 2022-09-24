#pragma once

#include "GLObject.h"

class IndexBuffer : public GLObject
{
public:
	IndexBuffer( GLsizeiptr size, const void* data, GLenum usage = GL_STATIC_DRAW );
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
};