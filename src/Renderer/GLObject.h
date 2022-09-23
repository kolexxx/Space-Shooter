#pragma once

#include <GL/glew.h>

class GLObject
{
public:
	GLObject( const GLObject& copy ) = delete;

	operator GLuint() const;
	GLObject& operator= ( const GLObject& ) = delete;
protected:
	GLuint m_ID;

	GLObject();
};