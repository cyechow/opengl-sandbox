#include "RectangleDrawable.h"

#include "GL/glew.h"

#include "ShaderUtils.h"

RectangleDrawable::RectangleDrawable() :
	BaseClass(),
	m_iPositionDataBuffer( 0 ),
	m_iPositionIndexBuffer( 0 ),
	m_iColorBuffer( 0 )
{
}

RectangleDrawable::~RectangleDrawable()
{
}

void RectangleDrawable::InitGL( const Rectangle& rectGeometry )
{
	// Generate buffers...

	// to hold position data:
	glGenBuffers( 1, &m_iPositionDataBuffer );

	// to hold position indexing:
	glGenBuffers( 1, &m_iPositionIndexBuffer );

	// to hold colour data:
	glGenBuffers( 1, &m_iColorBuffer );

	// Set up data...
	// Array containing the vertices data:
	float aPointData[] = {
		rectGeometry.GetPointAtIndex( 0 ).X(), rectGeometry.GetPointAtIndex( 0 ).Y(),
		rectGeometry.GetPointAtIndex( 1 ).X(), rectGeometry.GetPointAtIndex( 1 ).Y(),
		rectGeometry.GetPointAtIndex( 2 ).X(), rectGeometry.GetPointAtIndex( 2 ).Y(),
		rectGeometry.GetPointAtIndex( 3 ).X(), rectGeometry.GetPointAtIndex( 3 ).Y()
	};

	// Index buffer to indicate how to render the square with triangles without redundant points:
	unsigned int aIndices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	// Set data into buffers...
	// Select position buffer so that we can put data into it:
	glBindBuffer( GL_ARRAY_BUFFER, m_iPositionDataBuffer );

	// Put data into the buffer, data meant for STATIC (won't be modified, used many times) DRAW.
	// 6 * 2 because a rectangle will have 2 triangles (3 vertices each with 2 values per vertex):
	glBufferData( GL_ARRAY_BUFFER, 6 * 2 * sizeof( float ), aPointData, GL_STATIC_DRAW );

	// Select index buffer to put data into it:
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_iPositionIndexBuffer );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof( unsigned int ), aIndices, GL_STATIC_DRAW );
}

void
RectangleDrawable::DrawGL()
{
	// Use the basic shader - draws as red.
	ShaderUtils::ShaderProgramSource shaderSource = ShaderUtils::S_ParseShader( "res/shaders/Basic.shader" );

	// Create shader from the shader source code:
	unsigned int shader = ShaderUtils::S_CreateShader( shaderSource.VertexSource, shaderSource.FragmentSource );

	// State machine - use this new shader program:
	glUseProgram( shader );

	// Select the position buffer
	glBindBuffer( GL_ARRAY_BUFFER, m_iPositionDataBuffer );

	// Select the index buffer
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_iPositionIndexBuffer );

	// Tell OpenGL what the layout of buffer is:
	glEnableVertexArrayAttrib( 0, 0 );
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof( float ), 0 );

	// Draw - we're drawing the index buffer instead of the vertex, it has 6 indices:
	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr );

	// Cleanup
	glDeleteProgram( shader );
}

void
RectangleDrawable::FiniGL()
{
	if ( m_iPositionDataBuffer != 0 )
	{
		glDeleteBuffers( 1, &m_iPositionDataBuffer );
		m_iPositionDataBuffer = 0;
	}
	if ( m_iColorBuffer != 0 )
	{
		glDeleteBuffers( 1, &m_iColorBuffer );
		m_iColorBuffer = 0;
	}
}
