#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class ShaderUtils {

public:
	struct ShaderProgramSource {
		std::string VertexSource;
		std::string FragmentSource;
	};

	static ShaderProgramSource S_ParseShader( const std::string& zFilepath ) {
		std::ifstream iStream( zFilepath );

		enum class ShaderType {
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		std::string zLine;
		std::stringstream ss[2];
		ShaderType iShaderType = ShaderType::NONE;
		while ( getline( iStream, zLine ) )
		{
			if ( zLine.find("#shader") != std::string::npos )
			{
				if ( zLine.find("vertex") != std::string::npos ) {
					iShaderType = ShaderType::VERTEX;
				}
				else if ( zLine.find("fragment") != std::string::npos ) {
					iShaderType = ShaderType::FRAGMENT;
				}
			}
			else if ( iShaderType != ShaderType::NONE ) {
				ss[(int)iShaderType] << zLine << '\n';
			}
		}

		return { ss[0].str(), ss[1].str() };
	}

	static unsigned int S_CompileShader( unsigned int type, const std::string& zShaderSource )
	{
		unsigned int id = glCreateShader( type );

		const char* cSource = zShaderSource.c_str();
		glShaderSource( id, 1, &cSource, nullptr );
		glCompileShader( id );

		// TODO: Error handling
		int result;
		glGetShaderiv( id, GL_COMPILE_STATUS, &result );
		if ( result == GL_FALSE )
		{
			int length;
			glGetShaderiv( id, GL_INFO_LOG_LENGTH, &length );
			char* message = (char*)_malloca( length * sizeof( char ) ); // allocate on stack dynamically
			glGetShaderInfoLog( id, length, &length, message );

			std::cout << "Failed to compile " << ( type == GL_VERTEX_SHADER ? "texture" : "fragment" ) << " shader." << std::endl;
			std::cout << message << std::endl;

			glDeleteShader( id );
			return 0;
		}

		return id;
	}

	static unsigned int S_CreateShader( const std::string& vertexShader, const std::string& fragmentShader )
	{
		unsigned int program = glCreateProgram();
		unsigned int vs = S_CompileShader( GL_VERTEX_SHADER, vertexShader );
		unsigned int fs = S_CompileShader( GL_FRAGMENT_SHADER, fragmentShader );

		glAttachShader( program, vs );
		glAttachShader( program, fs );
		glLinkProgram( program );
		glValidateProgram( program );

		glDeleteShader( vs );
		glDeleteShader( fs );

		return program;
	}

};
