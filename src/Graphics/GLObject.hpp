#pragma once

#include <GL/glew.h>

class GLObject
{
public:
	virtual ~GLObject();

	// We don't want GLObjects to be copied
	GLObject(const GLObject& copy) = delete;
	GLObject& operator= (const GLObject&) = delete;
protected:
	GLuint m_ID;

	GLObject();
};