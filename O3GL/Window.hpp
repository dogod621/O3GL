#pragma once

// O3GL
#include "O3GL/Utils.hpp"

// 
namespace O3GL
{
	//
	class _Window : public GLUTObject
	{
	public:
		_Window(const std::string& name, unsigned int displayMode, int x, int y, int width, int height, unsigned int tick);
		~_Window();

	public:
		void Begin() const;
		void End() const;

	public:
		virtual void Start() const;

	public:
		virtual void RegisterCallbackEvent() const;

		virtual void InitGLStatusEvent() const
		{

		}

	public:
		virtual void DisplayEvent()
		{
			// Swap buffers
			glutSwapBuffers();
		}

		virtual void OverlayDisplayEvent()
		{

		}

		virtual void ReshapeEvent(int width, int height)
		{

		}

		virtual void KeyboardEvent(unsigned char key, int x, int y)
		{
			switch (key)
			{
			case 27:
				glutLeaveMainLoop();
				break;
			}
		}

		virtual void KeyboardUpEvent(unsigned char key, int x, int y)
		{

		}

		virtual void SpecialEvent(int key, int x, int y)
		{

		}

		virtual void SpecialUpEvent(int key, int x, int y)
		{

		}

		virtual void MouseEvent(int button, int state, int x, int y)
		{

		}

		virtual void MotionEvent(int x, int y)
		{

		}

		virtual void PassiveMotionEvent(int x, int y)
		{

		}

		virtual void VisibilityEvent(int state)
		{

		}

		virtual void EntryEvent(int state)
		{

		}

		virtual void CloseEvent()
		{

		}

		virtual void TimerEvent(int value)
		{
			glutPostRedisplay();
		}

	public:
		unsigned int Tick() const
		{
			return tick;
		}

		static _Window* Instance()
		{
			return instance;
		}

		static std::vector<int>* BindStack()
		{
			return &bindStack;
		}

	protected:
		unsigned int tick;

		static _Window* instance;
		static std::vector<int> bindStack;
	};

	//
	class Window : public GLUTHandle<_Window>
	{
	public:
		Window(const std::string& name, unsigned int displayMode, int x, int y, int width, int height, unsigned int tick) : GLUTHandle<_Window>(new _Window(name, displayMode, x, y, width, height, tick)) {}
	};
};