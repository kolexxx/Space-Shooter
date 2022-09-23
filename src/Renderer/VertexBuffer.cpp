#include "VertexBuffer.h"

VertexBuffer::VertexBuffer( GLsizeiptr size, const void* data, GLenum usage )
{
	glGenBuffers( 1, &m_ID );
	glBindBuffer( GL_ARRAY_BUFFER, m_ID );
	glBufferData( GL_ARRAY_BUFFER, size, data, usage );
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers( 1, &m_ID );
}

void VertexBuffer::Bind() const
{
	glBindBuffer( GL_ARRAY_BUFFER, m_ID );
}

void VertexBuffer::Unbind() const
{
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}