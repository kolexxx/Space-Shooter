#include "Shader.h"

#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader( const std::string& vertexShaderPath, const std::string& fragmentShaderPath )
{
	auto vertexShaderID = CompileShader( vertexShaderPath, GL_VERTEX_SHADER );
	auto fragmentShaderID = CompileShader( fragmentShaderPath, GL_FRAGMENT_SHADER );

	m_ID = glCreateProgram();
	glAttachShader( m_ID, vertexShaderID );
	glAttachShader( m_ID, fragmentShaderID );
	glLinkProgram( m_ID );

	auto infoLogLength = 0;
	glGetProgramiv( m_ID, GL_INFO_LOG_LENGTH, &infoLogLength );

	if ( infoLogLength > 0 )
	{
		auto* message = ( char* ) alloca( infoLogLength * sizeof( char ) );
		glGetProgramInfoLog( m_ID, infoLogLength, nullptr, message );
		printf( message );
	}

	glDetachShader( m_ID, vertexShaderID );
	glDetachShader( m_ID, fragmentShaderID );

	glDeleteShader( vertexShaderID );
	glDeleteShader( fragmentShaderID );
}

Shader::~Shader()
{
	glDeleteProgram( m_ID );
}

void Shader::Use() const
{
	glUseProgram( m_ID );
}

void Shader::SetUniform1f( const GLchar* name, GLfloat value )
{
	glUniform1f( GetUniformLocation( name ), value );
}

void Shader::SetUniform1fv( const GLchar* name, GLsizei count, const GLfloat* value )
{
	glUniform1fv( GetUniformLocation( name ), count, value );
}

void Shader::SetUniform1i( const GLchar* name, GLint value )
{
	glUniform1i( GetUniformLocation( name ), value );
}

void Shader::SetUniform1ui( const GLchar* name, GLuint value )
{
	glUniform1ui( GetUniformLocation( name ), value );
}

void Shader::SetUniform1iv( const GLchar* name, GLsizei count, const GLint* value )
{
	glUniform1iv( GetUniformLocation( name ), count, value );
}

void Shader::SetUniform2f( const GLchar* name, const glm::vec2& vector )
{
	glUniform2f( GetUniformLocation( name ), vector.x, vector.y );
}

void Shader::SetUniform3f( const GLchar* name, const glm::vec3& vector )
{
	glUniform3f( GetUniformLocation( name ), vector.x, vector.y, vector.z );
}

void Shader::SetUniform4f( const GLchar* name, const glm::vec4& vector )
{
	glUniform4f( GetUniformLocation( name ), vector.x, vector.y, vector.z, vector.w );
}

void Shader::SetUniformMatrix4f( const GLchar* name, const glm::mat4& matrix )
{
	glUniformMatrix4fv( GetUniformLocation( name ), 1, GL_FALSE, glm::value_ptr( matrix ) );
}

GLuint Shader::CompileShader( const std::string& path, GLenum type )
{
	std::ifstream ifStream( path, std::ios::in );

	if ( !ifStream.is_open() )
	{
		printf( "Couldn't open %s.", path.c_str() );
		return 0;
	}

	std::stringstream stringStream;
	stringStream << ifStream.rdbuf();
	auto code = stringStream.str();
	ifStream.close();

	auto ID = glCreateShader( type );
	const auto* source = code.c_str();

	glShaderSource( ID, 1, &source, nullptr );
	glCompileShader( ID );

	auto result = GL_FALSE;
	glGetShaderiv( ID, GL_COMPILE_STATUS, &result );

	if ( result == GL_FALSE )
	{
		auto infoLogLength = 0;
		glGetShaderiv( ID, GL_INFO_LOG_LENGTH, &infoLogLength );

		auto* message = ( char* ) alloca( infoLogLength * sizeof( char ) );
		glGetShaderInfoLog( ID, infoLogLength, nullptr, message );
		printf( message );

		return 0;
	}

	return ID;
}

GLint Shader::GetUniformLocation( const GLchar* name )
{
	auto locationSearch = m_UniformLocations.find( name );
	if ( locationSearch != m_UniformLocations.end() )
		return locationSearch->second;

	auto location = glGetUniformLocation( m_ID, name );
	m_UniformLocations[name] = location;

	return location;
}