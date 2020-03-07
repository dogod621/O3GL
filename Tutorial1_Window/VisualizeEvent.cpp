#include "VisualizeEvent.hpp"

//
namespace O3GL
{
	//
	void _VisualizeEvent::InitGLStatusEvent() const
	{
		glEnable(GL_DEPTH_TEST);
		glClearColor(1.0, 1.0, 1.0, 0.0);
		glClearDepth(1.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	}

	void _VisualizeEvent::DisplayEvent()
	{
		displayEventMessage.Active();

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
		displayEventMessage.Draw(wx, wy);
		wy += lineHeight;
		overlayDisplayEventMessage.Draw(wx, wy);
		wy += lineHeight;
		reshapeEventMessage.Draw(wx, wy);
		wy += lineHeight;
		keyboardEventMessage.Draw(wx, wy);
		wy += lineHeight;
		keyboardUpEventMessage.Draw(wx, wy);
		wy += lineHeight;
		specialEventMessage.Draw(wx, wy);
		wy += lineHeight;
		specialUpEventMessage.Draw(wx, wy);
		wy += lineHeight;
		mouseEventMessage.Draw(wx, wy);
		wy += lineHeight;
		motionEventMessage.Draw(wx, wy);
		wy += lineHeight;
		passiveMotionEventMessage.Draw(wx, wy);
		wy += lineHeight;
		visibilityEventMessage.Draw(wx, wy);
		wy += lineHeight;
		entryEventMessage.Draw(wx, wy);
		wy += lineHeight;
		closeEventMessage.Draw(wx, wy);
		wy += lineHeight;
		timerEventMessage.Draw(wx, wy);

		// Swap buffers
		glutSwapBuffers();
	}

	void _VisualizeEvent::OverlayDisplayEvent()
	{
		overlayDisplayEventMessage.Active();
	}

	void _VisualizeEvent::ReshapeEvent(int width, int height)
	{
		reshapeEventMessage.Active();
		reshapeEventMessage.width = width;
		reshapeEventMessage.height = height;
	}

	void _VisualizeEvent::KeyboardEvent(unsigned char key, int x, int y)
	{
		keyboardEventMessage.Active();
		keyboardEventMessage.key = key;
		keyboardEventMessage.x = x;
		keyboardEventMessage.y = y;

		switch (key)
		{
		case 27:
			glutLeaveMainLoop();
			break;
		}
	}

	void _VisualizeEvent::KeyboardUpEvent(unsigned char key, int x, int y)
	{
		keyboardUpEventMessage.Active();
		keyboardUpEventMessage.key = key;
		keyboardUpEventMessage.x = x;
		keyboardUpEventMessage.y = y;
	}

	void _VisualizeEvent::SpecialEvent(int key, int x, int y)
	{
		specialEventMessage.Active();
		specialEventMessage.key = key;
		specialEventMessage.x = x;
		specialEventMessage.y = y;
	}

	void _VisualizeEvent::SpecialUpEvent(int key, int x, int y)
	{
		specialUpEventMessage.Active();
		specialUpEventMessage.key = key;
		specialUpEventMessage.x = x;
		specialUpEventMessage.y = y;
	}

	void _VisualizeEvent::MouseEvent(int button, int state, int x, int y)
	{
		mouseEventMessage.Active();
		mouseEventMessage.button = button;
		mouseEventMessage.state = state;
		mouseEventMessage.x = x;
		mouseEventMessage.y = y;
	}

	void _VisualizeEvent::MotionEvent(int x, int y)
	{
		motionEventMessage.Active();
		motionEventMessage.x = x;
		motionEventMessage.y = y;
	}

	void _VisualizeEvent::PassiveMotionEvent(int x, int y)
	{
		passiveMotionEventMessage.Active();
		passiveMotionEventMessage.x = x;
		passiveMotionEventMessage.y = y;
	}

	void _VisualizeEvent::VisibilityEvent(int state)
	{
		visibilityEventMessage.Active();
		visibilityEventMessage.state = state;
	}

	void _VisualizeEvent::EntryEvent(int state)
	{
		entryEventMessage.Active();
		entryEventMessage.state = state;
	}

	void _VisualizeEvent::CloseEvent()
	{
		closeEventMessage.Active();
	}

	void _VisualizeEvent::TimerEvent(int value)
	{
		timerEventMessage.Active();
		timerEventMessage.value = value;

		glutPostRedisplay();
	}
};