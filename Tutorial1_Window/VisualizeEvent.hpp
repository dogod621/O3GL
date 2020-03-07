// std
#include<sstream>

// O3GL
#include "O3GL/Utils.hpp"
#include "O3GL/Window.hpp"
#include "EventMessage.hpp"

//
namespace O3GL
{
	//
	class _VisualizeEvent : public _Window
	{
	public:
		_VisualizeEvent(int x, int y, int width, int height) :
			_Window("VisualizeEvent", GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH, x, y, width, height, 33)
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

	class VisualizeEvent : public GLUTHandle<_VisualizeEvent>
	{
	public:
		VisualizeEvent(int x, int y, int width, int height) : GLUTHandle<_VisualizeEvent>(new _VisualizeEvent(x, y, width, height)) {}
	};
};