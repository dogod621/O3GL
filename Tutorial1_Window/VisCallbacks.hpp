// std
#include<sstream>

// O3GL
#include "O3GL/Utils.hpp"
#include "O3GL/Window.hpp"
#include "CallbackMessage.hpp"

//
namespace O3GL
{
	//
	class _VisCallbacks : public _Window
	{
	public:
		_VisCallbacks(int x, int y, int width, int height) :
			_Window("VisCallbacks", GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH, x, y, width, height, 33)
		{}

	public:
		virtual void InitGLStatusCallback() const;

	public:
		virtual void DisplayCallback();
		virtual void OverlayDisplayCallback();
		virtual void ReshapeCallback(int width, int height);
		virtual void KeyboardCallback(unsigned char key, int x, int y);
		virtual void KeyboardUpCallback(unsigned char key, int x, int y);
		virtual void SpecialCallback(int key, int x, int y);
		virtual void SpecialUpCallback(int key, int x, int y);
		virtual void MouseCallback(int button, int state, int x, int y);
		virtual void MotionCallback(int x, int y);
		virtual void PassiveMotionCallback(int x, int y);
		virtual void VisibilityCallback(int state);
		virtual void EntryCallback(int state);
		virtual void CloseCallback();
		virtual void TimerCallback(int value);

	protected:
		DisplayCallbackMessage displayCallbackMessage;
		OverlayDisplayCallbackMessage overlayDisplayCallbackMessage;
		ReshapeCallbackMessage reshapeCallbackMessage;
		KeyboardCallbackMessage keyboardCallbackMessage;
		KeyboardUpCallbackMessage keyboardUpCallbackMessage;
		SpecialCallbackMessage specialCallbackMessage;
		SpecialUpCallbackMessage specialUpCallbackMessage;
		MouseCallbackMessage mouseCallbackMessage;
		MotionCallbackMessage motionCallbackMessage;
		PassiveMotionCallbackMessage passiveMotionCallbackMessage;
		VisibilityCallbackMessage visibilityCallbackMessage;
		EntryCallbackMessage entryCallbackMessage;
		CloseCallbackMessage closeCallbackMessage;
		TimerCallbackMessage timerCallbackMessage;
	};

	class VisCallbacks : public GLUTHandle<_VisCallbacks>
	{
	public:
		VisCallbacks(int x, int y, int width, int height) : GLUTHandle<_VisCallbacks>(new _VisCallbacks(x, y, width, height)) {}
	};
};