#include "VisCallbacks.hpp"

//
namespace O3GL
{
	//
	void _VisCallbacks::InitGLStatusCallback() const
	{
		glEnable(GL_DEPTH_TEST);
		glClearColor(1.0, 1.0, 1.0, 0.0);
		glClearDepth(1.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	}

	void _VisCallbacks::DisplayCallback()
	{
		displayCallbackMessage.Active();

		// Clear backbuffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//
		float lineHeight = 0.06f;
		float wx = -1.0f;
		float wy = -1.0f;

		Text(wx, wy, 0.0f, "\t\t" + std::string((char*)glGetString(GL_EXTENSIONS)), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;
		Text(wx, wy, 0.0f, "GL_EXTENSIONS: ", 0.0f, 1.0f, 0.0f, 1.0f);
		wy += lineHeight;

		Text(wx, wy, 0.0f, "\t\t" + std::string((char*)glGetString(GL_RENDERER)), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;
		Text(wx, wy, 0.0f, "GL_RENDERER: ", 0.0f, 1.0f, 0.0f, 1.0f);
		wy += lineHeight;

		Text(wx, wy, 0.0f, "\t\t" + std::string((char*)glGetString(GL_VENDOR)), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;
		Text(wx, wy, 0.0f, "GL_VENDOR: ", 0.0f, 1.0f, 0.0f, 1.0f);
		wy += lineHeight;

		Text(wx, wy, 0.0f, "\t\t" + std::string((char*)glGetString(GL_SHADING_LANGUAGE_VERSION)), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;
		Text(wx, wy, 0.0f, "GL_SHADING_LANGUAGE_VERSION: ", 0.0f, 1.0f, 0.0f, 1.0f);
		wy += lineHeight;

		Text(wx, wy, 0.0f, "\t\t" + std::string((char*)glGetString(GL_VERSION)), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;
		Text(wx, wy, 0.0f, "GL_VERSION: ", 0.0f, 1.0f, 0.0f, 1.0f);
		wy += lineHeight;
		wy += lineHeight;
		wy += lineHeight;

		//
		displayCallbackMessage.Draw(wx, wy);
		wy += lineHeight;
		overlayDisplayCallbackMessage.Draw(wx, wy);
		wy += lineHeight;
		reshapeCallbackMessage.Draw(wx, wy);
		wy += lineHeight;
		keyboardCallbackMessage.Draw(wx, wy);
		wy += lineHeight;
		keyboardUpCallbackMessage.Draw(wx, wy);
		wy += lineHeight;
		specialCallbackMessage.Draw(wx, wy);
		wy += lineHeight;
		specialUpCallbackMessage.Draw(wx, wy);
		wy += lineHeight;
		mouseCallbackMessage.Draw(wx, wy);
		wy += lineHeight;
		motionCallbackMessage.Draw(wx, wy);
		wy += lineHeight;
		passiveMotionCallbackMessage.Draw(wx, wy);
		wy += lineHeight;
		visibilityCallbackMessage.Draw(wx, wy);
		wy += lineHeight;
		entryCallbackMessage.Draw(wx, wy);
		wy += lineHeight;
		closeCallbackMessage.Draw(wx, wy);
		wy += lineHeight;
		timerCallbackMessage.Draw(wx, wy);

		// Swap buffers
		glutSwapBuffers();
	}

	void _VisCallbacks::OverlayDisplayCallback()
	{
		overlayDisplayCallbackMessage.Active();
	}

	void _VisCallbacks::ReshapeCallback(int width, int height)
	{
		reshapeCallbackMessage.Active();
		reshapeCallbackMessage.width = width;
		reshapeCallbackMessage.height = height;
	}

	void _VisCallbacks::KeyboardCallback(unsigned char key, int x, int y)
	{
		keyboardCallbackMessage.Active();
		keyboardCallbackMessage.key = key;
		keyboardCallbackMessage.x = x;
		keyboardCallbackMessage.y = y;

		switch (key)
		{
		case 27:
			glutLeaveMainLoop();
			break;
		}
	}

	void _VisCallbacks::KeyboardUpCallback(unsigned char key, int x, int y)
	{
		keyboardUpCallbackMessage.Active();
		keyboardUpCallbackMessage.key = key;
		keyboardUpCallbackMessage.x = x;
		keyboardUpCallbackMessage.y = y;
	}

	void _VisCallbacks::SpecialCallback(int key, int x, int y)
	{
		specialCallbackMessage.Active();
		specialCallbackMessage.key = key;
		specialCallbackMessage.x = x;
		specialCallbackMessage.y = y;
	}

	void _VisCallbacks::SpecialUpCallback(int key, int x, int y)
	{
		specialUpCallbackMessage.Active();
		specialUpCallbackMessage.key = key;
		specialUpCallbackMessage.x = x;
		specialUpCallbackMessage.y = y;
	}

	void _VisCallbacks::MouseCallback(int button, int state, int x, int y)
	{
		mouseCallbackMessage.Active();
		mouseCallbackMessage.button = button;
		mouseCallbackMessage.state = state;
		mouseCallbackMessage.x = x;
		mouseCallbackMessage.y = y;
	}

	void _VisCallbacks::MotionCallback(int x, int y)
	{
		motionCallbackMessage.Active();
		motionCallbackMessage.x = x;
		motionCallbackMessage.y = y;
	}

	void _VisCallbacks::PassiveMotionCallback(int x, int y)
	{
		passiveMotionCallbackMessage.Active();
		passiveMotionCallbackMessage.x = x;
		passiveMotionCallbackMessage.y = y;
	}

	void _VisCallbacks::VisibilityCallback(int state)
	{
		visibilityCallbackMessage.Active();
		visibilityCallbackMessage.state = state;
	}

	void _VisCallbacks::EntryCallback(int state)
	{
		entryCallbackMessage.Active();
		entryCallbackMessage.state = state;
	}

	void _VisCallbacks::CloseCallback()
	{
		closeCallbackMessage.Active();
	}

	void _VisCallbacks::TimerCallback(int value)
	{
		timerCallbackMessage.Active();
		timerCallbackMessage.value = value;

		glutPostRedisplay();
	}
};