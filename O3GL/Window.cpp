// O3GL
#include "O3GL/Window.hpp"

//
namespace O3GL
{
	void EnterMainLoop()
	{
		glutMainLoop();
	}

	void LeaveMainLoop()
	{
		glutLeaveMainLoop();
	}

	bool _WindowBase::init = false;
};