#include "TriangleDrawable.h"

#include "GL/glew.h"

#include "ShaderUtils.h"

TriangleDrawable::TriangleDrawable() :
	BaseClass(),
	m_iPositionBuffer( 0 ),
	m_iColorBuffer( 0 )
{
}

TriangleDrawable::~TriangleDrawable()
{
}

void
TriangleDrawable::InitGL( const Point& A, const Point& B, const Point& C )
{
	// Generate buffers...

	// to hold position data:
	glGenBuffers( 1, &m_iPositionBuffer );

	// to hold colour data:
	glGenBuffers( 1, &m_iColorBuffer );

	// Select position buffer so that we can put data into it:
	glBindBuffer( GL_ARRAY_BUFFER, m_iPositionBuffer );

	float aPointData[6] = {
		A.X(), A.Y(),
		B.X(), B.Y(),
		C.X(), C.Y()
	};

	// Put data into the buffer, data meant for STATIC (won't be modified, used many times) DRAW:
	glBufferData( GL_ARRAY_BUFFER, 6 * sizeof( float ), aPointData, GL_STATIC_DRAW );
}

void
TriangleDrawable::UpdateGL()
{}

void
TriangleDrawable::FiniGL()
{
	if ( m_iPositionBuffer != 0 )
	{
		glDeleteBuffers( 1, &m_iPositionBuffer );
		m_iPositionBuffer = 0;
	}
	if ( m_iColorBuffer != 0 )
	{
		glDeleteBuffers( 1, &m_iColorBuffer );
		m_iColorBuffer = 0;
	}
}

void
TriangleDrawable::DrawGL()
{
	// Use the basic shader - draws as red.
	ShaderUtils::ShaderProgramSource shaderSource = ShaderUtils::S_ParseShader( "res/shaders/Basic.shader" );

	// Create shader from the shader source code:
	unsigned int shader = ShaderUtils::S_CreateShader( shaderSource.VertexSource, shaderSource.FragmentSource );

	// State machine - use this new shader program:
	glUseProgram( shader );

	// Select the position buffer
	glBindBuffer( GL_ARRAY_BUFFER, m_iPositionBuffer );

	// Tell OpenGL what the layout of buffer is:
	glEnableVertexArrayAttrib( 0, 0 );
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof( float ), 0 );

	// Draw
	glDrawArrays( GL_TRIANGLES, 0, 3 );

	// Cleanup
	glDeleteProgram( shader );
}
