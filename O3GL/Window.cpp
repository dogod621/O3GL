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

	bool WindowBase::init = false;

	void WindowBase::InitGLStatusEvent() const
	{

	}

	void WindowBase::DisplayEvent()
	{
		// Swap buffers
		glutSwapBuffers();
	}

	void WindowBase::OverlayDisplayEvent()
	{

	}

	void WindowBase::ReshapeEvent(int width, int height)
	{

	}

	void WindowBase::KeyboardEvent(unsigned char key, int x, int y)
	{

	}

	void WindowBase::KeyboardUpEvent(unsigned char key, int x, int y)
	{

	}

	void WindowBase::SpecialEvent(int key, int x, int y)
	{

	}

	void WindowBase::SpecialUpEvent(int key, int x, int y)
	{

	}

	void WindowBase::MouseEvent(int button, int state, int x, int y)
	{

	}

	void WindowBase::MotionEvent(int x, int y)
	{

	}

	void WindowBase::PassiveMotionEvent(int x, int y)
	{

	}

	void WindowBase::VisibilityEvent(int state)
	{

	}

	void WindowBase::EntryEvent(int state)
	{

	}

	void WindowBase::CloseEvent()
	{

	}

	void WindowBase::TimerEvent(int value)
	{
		glutPostRedisplay();
	}
};