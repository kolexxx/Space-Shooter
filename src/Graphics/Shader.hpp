#pragma once

#include "GLObject.hpp"

#include <glm/glm.hpp>

#include<string>
#include<unordered_map>

class Shader : public GLObject
{
public:
	Shader( const std::string& vertexShaderPath, const std::string& fragmentShaderPath );
	~Shader();

	void Use() const;

	void SetUniform1f( const GLchar* name, GLfloat value );
	void SetUniform1fv( const GLchar* name, GLsizei count, const GLfloat* value );
	void SetUniform1i( const GLchar* name, GLint value );
	void SetUniform1ui( const GLchar* name, GLuint value );
	void SetUniform1iv( const GLchar* name, GLsizei count, const GLint* value );
	void SetUniform2f( const GLchar* name, const glm::vec2& vector );
	void SetUniform3f( const GLchar* name, const glm::vec3& vector );
	void SetUniform4f( const GLchar* name, const glm::vec4& vector );
	void SetUniformMatrix4f( const GLchar* name, const glm::mat4& value );
private:
	GLuint CompileShader( const std::string& path, GLenum type );
	GLint GetUniformLocation( const GLchar* name );

	std::unordered_map<std::string, GLint> m_UniformLocations;
};