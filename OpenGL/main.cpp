#include <iostream>
#include <string>
#include <vector>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "ShaderUtils.h"

#include "Point.h"
#include "Rectangle.h"

#include "TriangleDrawable.h"
#include "RectangleDrawable.h"

int main()
{
	std::cout << "Opening GLFW window...\n";

	GLFWwindow* pWindow;

	if ( !glfwInit() ) return -1;

	int						iWindowWidth = 640;
	int						iWindowHeight = 480;

	std::string				zWindowTitle = "GLFW: OpenGL Test";

	pWindow = glfwCreateWindow( iWindowWidth, iWindowHeight, zWindowTitle.c_str(), NULL, NULL );

	if ( !pWindow )
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent( pWindow );

	// Must be done after context is created:
	if ( glewInit() != GLEW_OK ) {
		std::cout << "Glew init failed.\n";
		return -1;
	}

	std::cout << glGetString( GL_VERSION ) << std::endl;

	// TriangleDrawable::InitGL

	Point A1( -1.0, -1.0, 0 );
	Point B1( -0.5, -1.0, 0 );
	Point C1( -1.0,  0.0, 0 );

	Point A2(  1.0,  1.0, 0 );
	Point B2(  1.0,  0.0, 0 );
	Point C2(  1.0,  0.0, 0 );

	//std::cout << "Point A: (" << A1.X() << "," << A1.Y() << "," << A1.Z() << ")\n";
	//std::cout << "Point B: (" << B1.X() << "," << B1.Y() << "," << B1.Z() << ")\n";
	//std::cout << "Point C: (" << C1.X() << "," << C1.Y() << "," << C1.Z() << ")\n";

	std::vector<DrawableBase*> apDrawables;

	// Create drawables that will take care of the OpenGL calls to render the object into the window:
	// InitGL will generate buffers and push data into it.
	TriangleDrawable* pTriangleUpper = new TriangleDrawable();
	pTriangleUpper->InitGL( A1, B1, C1 );
	apDrawables.push_back( pTriangleUpper );

	TriangleDrawable* pTriangleLower = new TriangleDrawable();
	pTriangleLower->InitGL( A2, B2, C2 );
	apDrawables.push_back( pTriangleLower );

	RectangleDrawable* pRectangleDrawable = new RectangleDrawable();
	pRectangleDrawable->InitGL( Rectangle( {
		Point( -0.5, -0.5, 0 ),
		Point(  0.5, -0.5, 0 ),
		Point(  0.5,  0.5, 0 ),
		Point( -0.5,  0.5, 0 )
		} ) );
	apDrawables.push_back( pRectangleDrawable );

	// Triangle:
	//float positions[] = {
	//	A1.X(), A1.Y(),
	//	B1.X(), B1.Y(),
	//	C1.X(), C1.Y(),

	//	A2.X(), A2.Y(),
	//	B2.X(), B2.Y(),
	//	C2.X(), C2.Y()
	//};

	//// Generate buffer (to hold data):
	//unsigned int buffer;
	//glGenBuffers( 1, &buffer );

	//// Select buffer:
	//glBindBuffer( GL_ARRAY_BUFFER, buffer );

	//// Put data into the buffer, data meant for STATIC (won't be modified, used many times) DRAW:
	//glBufferData( GL_ARRAY_BUFFER, 6 * 2 * sizeof( float ), positions, GL_STATIC_DRAW );

	//// Bind to no buffer:
	//// glBindBuffer( GL_ARRAY_BUFFER, 0 );

	//// Tell OpenGL what the layout of buffer is:
	//glEnableVertexArrayAttrib( 0, 0 );
	//glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof( float ), 0 );

	// TriangleDrawable::DrawGL
	// Vertex shader is called before fragment shader.

	// Vertex shader is called once per vertex passed in - e.g. 3 for each vertex in a triangle - to determine the position of each vertex on the screen.

	// Can pass information from vertex to fragment shader, things that can be calculated in vertex shader should be done so there.
	// Lighting information makes sense in the fragment shader.

	// Rasterized - drawn onto our screen. Fragment shader is called once per pixel, to decide the colour of the pixel so that it can get shaded in the right colour.

	//ShaderUtils::ShaderProgramSource shaderSource = ShaderUtils::S_ParseShader( "res/shaders/Basic.shader" );

	//std::cout << shaderSource.VertexSource << std::endl;
	//std::cout << shaderSource.FragmentSource << std::endl;

	//unsigned int shader = ShaderUtils::S_CreateShader( shaderSource.VertexSource, shaderSource.FragmentSource );
	//glUseProgram( shader );

	while ( !glfwWindowShouldClose( pWindow ) )
	{
		glClear( GL_COLOR_BUFFER_BIT );

		/* Legacy OpenGL code
		glBegin( GL_TRIANGLES );

		glVertex2f( -0.5f, -0.5f );
		glVertex2f(  0,     0.5f );
		glVertex2f(  0.5f, -0.5f );

		glEnd();
		*/

		// Modern OpenGL
		// Currently bound to 'buffer' so will draw that:
		//glDrawArrays( GL_TRIANGLES, 0, 3 * 2 );

		for ( DrawableBase* pDrawable : apDrawables )
		{
			pDrawable->DrawGL();
		}
		// Index buffer:
		//glDrawElements(GL_TRIANGLES, 3, )

		glfwSwapBuffers( pWindow );

		glfwPollEvents();
	}

	for ( DrawableBase* pDrawable : apDrawables )
	{
		pDrawable->FiniGL();
	}

	//glDeleteProgram( shader );

	std::cout << "Terminating GLFW...\n";
	glfwTerminate();
	std::cout << "Terminated GLFW...\n";

	return 0;
}