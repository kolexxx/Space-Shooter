#include "GLObject.h"

GLObject::GLObject() : m_ID( 0 ) {}

GLObject::operator GLuint() const
{
	return m_ID;
}