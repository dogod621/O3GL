#pragma once

// std
#include <vector>
#include <sstream>

// O3GL
#include "O3GL/Utils.hpp"

// 
namespace O3GL
{
	//
	void EnterMainLoop();
	void LeaveMainLoop();

	//
	class _WindowBase
	{
	public:
		_WindowBase() {}

	protected:
		static bool init;
	};

	//
	template<int key>
	class _Window : public GLUTObject, public _WindowBase
	{
	public:
		_Window(const std::string& name, unsigned int displayMode, int x, int y, int width, int height, unsigned int tick);
		_Window(int window, int x, int y, int width, int height, unsigned int tick);
		~_Window();

	public:
		void Init() const;

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
		static int InitAndCreateWindow(const std::string& name, unsigned int displayMode, int x, int y, int width, int height);
		static int InitAndCreateSubWindow(int window, int x, int y, int width, int height);

		static void DisplayCallback();
		static void OverlayDisplayCallback();
		static void ReshapeCallback(int width, int height);
		static void KeyboardCallback(unsigned char key, int x, int y);
		static void KeyboardUpCallback(unsigned char key, int x, int y);
		static void SpecialCallback(int key, int x, int y);
		static void SpecialUpCallback(int key, int x, int y);
		static void MouseCallback(int button, int state, int x, int y);
		static void MotionCallback(int x, int y);
		static void PassiveMotionCallback(int x, int y);
		static void VisibilityCallback(int state);
		static void EntryCallback(int state);
		static void CloseCallback();
		static void TimerCallback(int value);

	protected:
		unsigned int tick;
		bool subWindow;
		static _Window* instance;
	};

	//
	template<int key>
	class Window : public GLUTHandle<_Window<key>>
	{
	public:
		Window(const std::string& name, unsigned int displayMode, int x, int y, int width, int height, unsigned int tick) : GLUTHandle<_Window<key>>(new _Window<key>(name, displayMode, x, y, width, height, tick)) {}
		Window(int window, int x, int y, int width, int height, unsigned int tick) : GLUTHandle<_Window<key>>(new _Window<key>(window, x, y, width, height, tick)) {}
	};
};

namespace O3GL
{
	template<int key>
	_Window<key>* _Window<key>::instance = nullptr;

	//
	template<int key>
	_Window<key>::_Window(const std::string& name, unsigned int displayMode, int x, int y, int width, int height, unsigned int tick) :
		GLUTObject(InitAndCreateWindow(name, displayMode, x, y, width, height), glutDestroyWindow),
		_WindowBase(),
		tick(tick),
		subWindow(false)
	{
		instance = this;
	}

	template<int key>
	_Window<key>::_Window(int window, int x, int y, int width, int height, unsigned int tick) :
		GLUTObject(InitAndCreateSubWindow(window, x, y, width, height), glutDestroyWindow),
		_WindowBase(),
		tick(tick),
		subWindow(true)
	{
		instance = this;
	}

	template<int key>
	_Window<key>::~_Window()
	{
		instance = nullptr;
	}

	template<int key>
	void _Window<key>::Init() const
	{
		glutSetWindow(*this);
		glutDisplayFunc(_Window<key>::DisplayCallback);
		glutOverlayDisplayFunc(_Window<key>::OverlayDisplayCallback);
		glutReshapeFunc(_Window<key>::ReshapeCallback);
		glutKeyboardFunc(_Window<key>::KeyboardCallback);
		glutKeyboardUpFunc(_Window<key>::KeyboardUpCallback);
		glutSpecialFunc(_Window<key>::SpecialCallback);
		glutSpecialUpFunc(_Window<key>::SpecialUpCallback);
		glutMouseFunc(_Window<key>::MouseCallback);
		glutMotionFunc(_Window<key>::MotionCallback);
		glutPassiveMotionFunc(_Window<key>::PassiveMotionCallback);
		glutVisibilityFunc(_Window<key>::VisibilityCallback);
		glutEntryFunc(_Window<key>::EntryCallback);
		glutCloseFunc(_Window<key>::CloseCallback);
		glutTimerFunc(tick, _Window<key>::TimerCallback, 0);
		InitGLStatusEvent();
	}

	template<int key>
	void _Window<key>::InitGLStatusEvent() const
	{

	}

	template<int key>
	void _Window<key>::DisplayEvent()
	{
		// Swap buffers
		glutSwapBuffers();
	}

	template<int key>
	void _Window<key>::OverlayDisplayEvent()
	{

	}

	template<int key>
	void _Window<key>::ReshapeEvent(int width, int height)
	{

	}

	template<int key>
	void _Window<key>::KeyboardEvent(unsigned char key, int x, int y)
	{

	}

	template<int key>
	void _Window<key>::KeyboardUpEvent(unsigned char key, int x, int y)
	{

	}

	template<int key>
	void _Window<key>::SpecialEvent(int key, int x, int y)
	{

	}

	template<int key>
	void _Window<key>::SpecialUpEvent(int key, int x, int y)
	{

	}

	template<int key>
	void _Window<key>::MouseEvent(int button, int state, int x, int y)
	{

	}

	template<int key>
	void _Window<key>::MotionEvent(int x, int y)
	{

	}

	template<int key>
	void _Window<key>::PassiveMotionEvent(int x, int y)
	{

	}

	template<int key>
	void _Window<key>::VisibilityEvent(int state)
	{

	}

	template<int key>
	void _Window<key>::EntryEvent(int state)
	{

	}

	template<int key>
	void _Window<key>::CloseEvent()
	{

	}

	template<int key>
	void _Window<key>::TimerEvent(int value)
	{
		glutPostRedisplay();
	}

	template<int key>
	int _Window<key>::InitAndCreateWindow(const std::string& name, unsigned int displayMode, int x, int y, int width, int height)
	{
		if (instance)
		{
			THROW_EXCEPTION("Window key is already uesd");
		}
		else
		{
			if (!init)
			{
				int argc2 = 1;
				std::string s = "";
				std::vector<char*> argv{ &s[0] };
				glutInit(&argc2, &argv[0]);
			}
			glutInitDisplayMode(displayMode);
			glutInitWindowPosition(x, y);
			glutInitWindowSize(width, height);
			int winID = glutCreateWindow(name.c_str());
			if (!init)
			{
				GLenum err = glewInit();
				if (err != GLEW_OK)
				{
					std::stringstream ss;
					std::cout << glewGetErrorString(err);
					THROW_EXCEPTION(ss.str());
				}
				init = true;
			}
			return winID;
		}
	}

	template<int key>
	int _Window<key>::InitAndCreateSubWindow(int window, int x, int y, int width, int height)
	{
		if (instance)
		{
			THROW_EXCEPTION("Window key is already uesd");
		}
		else
		{
			if (!init)
			{
				THROW_EXCEPTION("Window is not init!?");
			}
			return glutCreateSubWindow(window, x, y, width, height);
		}
	}

	template<int key>
	void _Window<key>::DisplayCallback()
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->DisplayEvent();
		}
	}

	template<int key>
	void _Window<key>::OverlayDisplayCallback()
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->OverlayDisplayEvent();
		}
	}

	template<int key>
	void _Window<key>::ReshapeCallback(int width, int height)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->ReshapeEvent(width, height);
		}
	}

	template<int key>
	void _Window<key>::KeyboardCallback(unsigned char key, int x, int y)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->KeyboardEvent(key, x, y);
		}
	}

	template<int key>
	void _Window<key>::KeyboardUpCallback(unsigned char key, int x, int y)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->KeyboardUpEvent(key, x, y);
		}
	}

	template<int key>
	void _Window<key>::SpecialCallback(int key, int x, int y)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->SpecialEvent(key, x, y);
		}
	}

	template<int key>
	void _Window<key>::SpecialUpCallback(int key, int x, int y)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->SpecialUpEvent(key, x, y);
		}
	}

	template<int key>
	void _Window<key>::MouseCallback(int button, int state, int x, int y)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->MouseEvent(button, state, x, y);
		}
	}

	template<int key>
	void _Window<key>::MotionCallback(int x, int y)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->MotionEvent(x, y);
		}
	}

	template<int key>
	void _Window<key>::PassiveMotionCallback(int x, int y)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->PassiveMotionEvent(x, y);
		}
	}

	template<int key>
	void _Window<key>::VisibilityCallback(int state)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->VisibilityEvent(state);
		}
	}

	template<int key>
	void _Window<key>::EntryCallback(int state)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->EntryEvent(state);
		}
	}

	template<int key>
	void _Window<key>::CloseCallback()
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->CloseEvent();
		}
	}

	template<int key>
	void _Window<key>::TimerCallback(int value)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->TimerEvent(value);
			glutTimerFunc(instance->tick, TimerCallback, 0);
		}
	}
};