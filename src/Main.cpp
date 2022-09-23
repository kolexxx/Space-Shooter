#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer/Renderer.h"
#include "SpaceShooter.h"

void APIENTRY DebugOutputCallback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam )
{
	printf( "OpenGL Debug Output message : " );

	if ( source == GL_DEBUG_SOURCE_API_ARB )					printf( "Source : API; " );
	else if ( source == GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB )	printf( "Source : WINDOW_SYSTEM; " );
	else if ( source == GL_DEBUG_SOURCE_SHADER_COMPILER_ARB )	printf( "Source : SHADER_COMPILER; " );
	else if ( source == GL_DEBUG_SOURCE_THIRD_PARTY_ARB )		printf( "Source : THIRD_PARTY; " );
	else if ( source == GL_DEBUG_SOURCE_APPLICATION_ARB )		printf( "Source : APPLICATION; " );
	else if ( source == GL_DEBUG_SOURCE_OTHER_ARB )			printf( "Source : OTHER; " );

	if ( type == GL_DEBUG_TYPE_ERROR_ARB )						printf( "Type : ERROR; " );
	else if ( type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB )	printf( "Type : DEPRECATED_BEHAVIOR; " );
	else if ( type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB )	printf( "Type : UNDEFINED_BEHAVIOR; " );
	else if ( type == GL_DEBUG_TYPE_PORTABILITY_ARB )			printf( "Type : PORTABILITY; " );
	else if ( type == GL_DEBUG_TYPE_PERFORMANCE_ARB )			printf( "Type : PERFORMANCE; " );
	else if ( type == GL_DEBUG_TYPE_OTHER_ARB )				printf( "Type : OTHER; " );

	if ( severity == GL_DEBUG_SEVERITY_HIGH_ARB )				printf( "Severity : HIGH; " );
	else if ( severity == GL_DEBUG_SEVERITY_MEDIUM_ARB )		printf( "Severity : MEDIUM; " );
	else if ( severity == GL_DEBUG_SEVERITY_LOW_ARB )			printf( "Severity : LOW; " );

	// You can set a breakpoint here ! Your debugger will stop the program,
	// and the callstack will immediately show you the offending call.
	printf( "Message : %s\n", message );
}

GLFWwindow* window;

int main( void )
{
	glewExperimental = true;
	/* Initialize GLFW */
	if ( !glfwInit() )
		return -1;

	glfwWindowHint( GLFW_SAMPLES, 4 );
	glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE ); // To make MacOS happy; should not be needed
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, 1 );

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow( 1024, 768, "Space Shooter", nullptr, nullptr );
	if ( window == nullptr )
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent( window );
	glfwSwapInterval( 0 );

	/* Initialize GLEW */
	if ( glewInit() != GLEW_OK )
	{
		glfwTerminate();
		return -1;
	}

	if ( GLEW_ARB_debug_output )
	{
		glDebugMessageCallbackARB( &DebugOutputCallback, nullptr );
		glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB );
	}

	glfwSetInputMode( window, GLFW_STICKY_KEYS, GL_TRUE );
	glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_NORMAL );

	Renderer::Init();

	glfwSetTime( 0 );
	const auto updateCap = 1.0f / 10.0f;
	auto lastTime = Time::Now(), unprocessedTime = 0.0f, lastTick = Time::Now(), second = 0.0f;
	auto frames = 0;
	auto render = false;

	/* Loop until the user closes the window */
	while ( !glfwWindowShouldClose( window ) )
	{
		if ( second >= 1.0f )
		{
			printf( "TPS: %d\n", frames );
			second = 0;
			frames = 0;
		}

		auto currTime = Time::Now();
		auto elapsedTime = currTime - lastTime;
		second += elapsedTime;
		unprocessedTime += elapsedTime;
		lastTime = currTime;

		Input::Build();

		while ( unprocessedTime >= updateCap )
		{
			Time::s_delta = Time::Now() - lastTick;
			Time::s_tick++;
			lastTick = Time::Now();
			render = true;
			frames++;
			unprocessedTime -= updateCap;

			for ( auto& entity : Entity::All )
				entity->Tick();
		}

		if ( !render )
			continue;

		Renderer::BeginBatch();

		for ( auto& entity : Entity::All )
			entity->Frame();

		Renderer::EndBatch();
		Renderer::Flush();
	}

	Renderer::Shutdown();
	glfwTerminate();

	return 0;
}