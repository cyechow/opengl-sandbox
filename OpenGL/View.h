#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "DrawableBase.h"

#include <vector>

class View {

public:
	View();
	virtual ~View(); 

	bool									IsInitialized()							{ return m_bInitialized; }

	void									InitGL();
	void									UpdateLoopGL();
	void									FiniGL();

	void									ForEveryDrawable();

private:
	GLFWwindow*								m_pWindow;
	bool									m_bInitialized;

	std::vector<DrawableBase>				m_aDrawables;
};
