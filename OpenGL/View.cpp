#include "View.h"

#include <iostream>
#include <string>

View::View() :
	m_pWindow( NULL ),
	m_bInitialized( false )
{}

View::~View()
{
}

void
View::InitGL()
{
	if ( IsInitialized() ) return;
	if ( !glfwInit() ) return;

	int						iWindowWidth = 640;
	int						iWindowHeight = 480;

	std::string				zWindowTitle = "GLFW: OpenGL Test";

	m_pWindow = glfwCreateWindow( iWindowWidth, iWindowHeight, zWindowTitle.c_str(), NULL, NULL );

	if ( !m_pWindow )
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent( m_pWindow );

	// Must be done after context is created:
	if ( glewInit() != GLEW_OK ) {
		std::cout << "Glew init failed.\n";
		return;
	}

	std::cout << glGetString( GL_VERSION ) << std::endl;

	m_bInitialized = true;
}

void
View::UpdateLoopGL()
{
	while ( !glfwWindowShouldClose( m_pWindow ) )
	{
		glClear( GL_COLOR_BUFFER_BIT );

		// Modern OpenGL
		// Currently bound to 'buffer' so will draw that:
		glDrawArrays( GL_TRIANGLES, 0, 3 );

		// Index buffer:
		//glDrawElements(GL_TRIANGLES, 3, )

		glfwSwapBuffers( m_pWindow );

		glfwPollEvents();
	}
}

void
View::FiniGL()
{
	if ( !IsInitialized() ) return;

	glfwTerminate();
}
