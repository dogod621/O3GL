#pragma once

// std
#include <vector>
#include <sstream>

// O3GL
#include "O3GL/Core/Utils.hpp"

// 
namespace O3GL
{
	//
	void EnterMainLoop();
	void LeaveMainLoop();
	int CurrentWindowWidth();
	int CurrentWindowHeight();


	//
	class WindowBase
	{
	public:
		WindowBase() {}

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
		static bool init;
	};

	//
	template<int key>
	class Window : public GLUTHandle, public WindowBase
	{
	public:
		Window(const std::string& name, unsigned int displayMode, int x, int y, int width, int height, unsigned int tick);
		Window(int window, int x, int y, int width, int height, unsigned int tick);
		~Window();

	public:
		void Init() const;

		template<class T>
		T GetInfo(GLenum state) const;

	public:
		template<>
		int GetInfo<int>(GLenum state) const
		{
			glutSetWindow(*this);
			return glutGet(state);
		}

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
		bool firstTick;
		std::chrono::steady_clock::time_point timeStamp;
		double timeElapsed;
		bool subWindow;
		static Window* instance;
	};

	//
	template<int key>
	Window<key>* Window<key>::instance = nullptr;

	template<int key>
	Window<key>::Window(const std::string& name, unsigned int displayMode, int x, int y, int width, int height, unsigned int tick) :
		GLUTHandle(new GLUTObject(InitAndCreateWindow(name, displayMode, x, y, width, height), glutDestroyWindow)),
		WindowBase(),
		tick(tick),
		firstTick(true),
		timeStamp(),
		timeElapsed(0.0),
		subWindow(false)
	{
		instance = this;
	}

	template<int key>
	Window<key>::Window(int window, int x, int y, int width, int height, unsigned int tick) :
		GLUTHandle(new GLUTObject(InitAndCreateSubWindow(window, x, y, width, height), glutDestroyWindow)),
		WindowBase(),
		tick(tick),
		firstTick(true),
		timeStamp(),
		timeElapsed(0.0),
		subWindow(true)
	{
		instance = this;
	}

	template<int key>
	Window<key>::~Window()
	{
		instance = nullptr;
	}

	template<int key>
	void Window<key>::Init() const
	{
		glutSetWindow(*this);
		glutDisplayFunc(Window<key>::DisplayCallback);
		glutOverlayDisplayFunc(Window<key>::OverlayDisplayCallback);
		glutReshapeFunc(Window<key>::ReshapeCallback);
		glutKeyboardFunc(Window<key>::KeyboardCallback);
		glutKeyboardUpFunc(Window<key>::KeyboardUpCallback);
		glutSpecialFunc(Window<key>::SpecialCallback);
		glutSpecialUpFunc(Window<key>::SpecialUpCallback);
		glutMouseFunc(Window<key>::MouseCallback);
		glutMotionFunc(Window<key>::MotionCallback);
		glutPassiveMotionFunc(Window<key>::PassiveMotionCallback);
		glutVisibilityFunc(Window<key>::VisibilityCallback);
		glutEntryFunc(Window<key>::EntryCallback);
		glutCloseFunc(Window<key>::CloseCallback);
		glutTimerFunc(tick, Window<key>::TimerCallback, 0);
		InitGLStatusEvent();
	}

	template<int key>
	int Window<key>::InitAndCreateWindow(const std::string& name, unsigned int displayMode, int x, int y, int width, int height)
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
	int Window<key>::InitAndCreateSubWindow(int window, int x, int y, int width, int height)
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
	void Window<key>::DisplayCallback()
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->DisplayEvent();
		}
	}

	template<int key>
	void Window<key>::OverlayDisplayCallback()
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->OverlayDisplayEvent();
		}
	}

	template<int key>
	void Window<key>::ReshapeCallback(int width, int height)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->ReshapeEvent(width, height);
		}
	}

	template<int key>
	void Window<key>::KeyboardCallback(unsigned char key, int x, int y)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->KeyboardEvent(key, x, y);
		}
	}

	template<int key>
	void Window<key>::KeyboardUpCallback(unsigned char key, int x, int y)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->KeyboardUpEvent(key, x, y);
		}
	}

	template<int key>
	void Window<key>::SpecialCallback(int key, int x, int y)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->SpecialEvent(key, x, y);
		}
	}

	template<int key>
	void Window<key>::SpecialUpCallback(int key, int x, int y)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->SpecialUpEvent(key, x, y);
		}
	}

	template<int key>
	void Window<key>::MouseCallback(int button, int state, int x, int y)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->MouseEvent(button, state, x, y);
		}
	}

	template<int key>
	void Window<key>::MotionCallback(int x, int y)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->MotionEvent(x, y);
		}
	}

	template<int key>
	void Window<key>::PassiveMotionCallback(int x, int y)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->PassiveMotionEvent(x, y);
		}
	}

	template<int key>
	void Window<key>::VisibilityCallback(int state)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->VisibilityEvent(state);
		}
	}

	template<int key>
	void Window<key>::EntryCallback(int state)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->EntryEvent(state);
		}
	}

	template<int key>
	void Window<key>::CloseCallback()
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->CloseEvent();
		}
	}

	template<int key>
	void Window<key>::TimerCallback(int value)
	{
		if (instance)
		{
			glutSetWindow(*instance);

			if (instance->firstTick)
			{
				instance->timeStamp = std::chrono::high_resolution_clock::now();
				instance->timeElapsed = 0.0;
				instance->firstTick = false;
			}
			else
			{
				std::chrono::steady_clock::time_point timeStamp2 = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double, std::milli> _timeElapsed = timeStamp2 - instance->timeStamp;
				instance->timeElapsed = _timeElapsed.count();
				instance->timeStamp = timeStamp2;
			}

			instance->TimerEvent(value);
			glutTimerFunc(instance->tick, TimerCallback, 0);
		}
	}
};