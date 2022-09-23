#include "IndexBuffer.h"

IndexBuffer::IndexBuffer( GLsizeiptr size, const void* data, GLenum usage )
{
	glGenBuffers( 1, &m_ID );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ID );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, size, data, usage );
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers( 1, &m_ID );
}

void IndexBuffer::Bind() const
{
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ID );
}

void IndexBuffer::Unbind() const
{
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}
