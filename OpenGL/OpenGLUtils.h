#pragma once
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak();

#ifdef _DEBUG
	#define GLCall(x) S_GLClearError();\
		x;\
		ASSERT(S_GLLogCall(#x, __FILE__, __LINE__))
#else
	#define GLCall(x) x
#endif // DEBUG

static void S_GLClearError() {
	while ( glGetError() != GL_NO_ERROR );
}

static bool S_GLLogCall( const char* acFunction, const char* acFile, int iLine ) {
	bool bHasError = false;
	while ( GLenum error = glGetError() )
	{
		std::cout << "[OpenGL Error] (" << error << "): " << acFile << " " << acFile << ": " << iLine << std::endl;
		bHasError = true;
	}

	return !bHasError;
}
