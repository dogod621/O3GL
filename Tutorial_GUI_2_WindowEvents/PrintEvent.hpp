// O3GL
#include "O3GL/Utils.hpp"
#include "O3GL/Window.hpp"
#include "EventMessage.hpp"

//
namespace O3GL
{
	//
	template<int key>
	class _PrintEvent : public _Window<key>
	{
	public:
		_PrintEvent(const std::string& name, int x, int y, int width, int height) :
			_Window<key>(name, GLUT_DOUBLE | GLUT_RGBA, x, y, width, height, 33)
		{}

	public:
		virtual void InitGLStatusEvent() const;

	public:
		virtual void DisplayEvent();
		virtual void OverlayDisplayEvent();
		virtual void ReshapeEvent(int width, int height);
		virtual void KeyboardEvent(unsigned char key, int x, int y);
		virtual void KeyboardUpEvent(unsigned char key, int x, int y);
		virtual void SpecialEvent(int key, int x, int y);
		virtual void SpecialUpEvent(int key, int x, int y);
		virtual void MouseEvent(int button, int state, int x, int y);
		virtual void MotionEvent(int x, int y);
		virtual void PassiveMotionEvent(int x, int y);
		virtual void VisibilityEvent(int state);
		virtual void EntryEvent(int state);
		virtual void CloseEvent();
		virtual void TimerEvent(int value);

	protected:
		DisplayEventMessage displayEventMessage;
		OverlayDisplayEventMessage overlayDisplayEventMessage;
		ReshapeEventMessage reshapeEventMessage;
		KeyboardEventMessage keyboardEventMessage;
		KeyboardUpEventMessage keyboardUpEventMessage;
		SpecialEventMessage specialEventMessage;
		SpecialUpEventMessage specialUpEventMessage;
		MouseEventMessage mouseEventMessage;
		MotionEventMessage motionEventMessage;
		PassiveMotionEventMessage passiveMotionEventMessage;
		VisibilityEventMessage visibilityEventMessage;
		EntryEventMessage entryEventMessage;
		CloseEventMessage closeEventMessage;
		TimerEventMessage timerEventMessage;
	};

	template<int key>
	class PrintEvent : public GLUTHandle<_PrintEvent<key>>
	{
	public:
		PrintEvent(const std::string& name, int x, int y, int width, int height) :
			GLUTHandle<_PrintEvent<key>>(new _PrintEvent<key>(name, x, y, width, height)) {}
	};
};

namespace O3GL
{
	//
	template<int key>
	void _PrintEvent<key>::InitGLStatusEvent() const
	{
		glClearColor(1.0, 1.0, 1.0, 0.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	}

	template<int key>
	void _PrintEvent<key>::DisplayEvent()
	{
		displayEventMessage.Active();

		// Clear backbuffer
		glClear(GL_COLOR_BUFFER_BIT);

		//
		float lineHeight = 0.06f;
		float wx = -1.0f;
		float wy = -1.0f;

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

	template<int key>
	void _PrintEvent<key>::OverlayDisplayEvent()
	{
		overlayDisplayEventMessage.Active();
	}

	template<int key>
	void _PrintEvent<key>::ReshapeEvent(int width, int height)
	{
		reshapeEventMessage.Active();
		reshapeEventMessage.width = width;
		reshapeEventMessage.height = height;
	}

	template<int key>
	void _PrintEvent<key>::KeyboardEvent(unsigned char key, int x, int y)
	{
		keyboardEventMessage.Active();
		keyboardEventMessage.key = key;
		keyboardEventMessage.x = x;
		keyboardEventMessage.y = y;
	}

	template<int key>
	void _PrintEvent<key>::KeyboardUpEvent(unsigned char key, int x, int y)
	{
		keyboardUpEventMessage.Active();
		keyboardUpEventMessage.key = key;
		keyboardUpEventMessage.x = x;
		keyboardUpEventMessage.y = y;
	}

	template<int key>
	void _PrintEvent<key>::SpecialEvent(int key, int x, int y)
	{
		specialEventMessage.Active();
		specialEventMessage.key = key;
		specialEventMessage.x = x;
		specialEventMessage.y = y;
	}

	template<int key>
	void _PrintEvent<key>::SpecialUpEvent(int key, int x, int y)
	{
		specialUpEventMessage.Active();
		specialUpEventMessage.key = key;
		specialUpEventMessage.x = x;
		specialUpEventMessage.y = y;
	}

	template<int key>
	void _PrintEvent<key>::MouseEvent(int button, int state, int x, int y)
	{
		mouseEventMessage.Active();
		mouseEventMessage.button = button;
		mouseEventMessage.state = state;
		mouseEventMessage.x = x;
		mouseEventMessage.y = y;
	}

	template<int key>
	void _PrintEvent<key>::MotionEvent(int x, int y)
	{
		motionEventMessage.Active();
		motionEventMessage.x = x;
		motionEventMessage.y = y;
	}

	template<int key>
	void _PrintEvent<key>::PassiveMotionEvent(int x, int y)
	{
		passiveMotionEventMessage.Active();
		passiveMotionEventMessage.x = x;
		passiveMotionEventMessage.y = y;
	}

	template<int key>
	void _PrintEvent<key>::VisibilityEvent(int state)
	{
		visibilityEventMessage.Active();
		visibilityEventMessage.state = state;
	}

	template<int key>
	void _PrintEvent<key>::EntryEvent(int state)
	{
		entryEventMessage.Active();
		entryEventMessage.state = state;
	}

	template<int key>
	void _PrintEvent<key>::CloseEvent()
	{
		closeEventMessage.Active();
	}

	template<int key>
	void _PrintEvent<key>::TimerEvent(int value)
	{
		timerEventMessage.Active();
		timerEventMessage.value = value;

		glutPostRedisplay();
	}
};