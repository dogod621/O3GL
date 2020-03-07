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
		virtual void InitGLStatusCallback() const
		{

		}

	public:
		virtual void DisplayCallback()
		{
			// Swap buffers
			glutSwapBuffers();
		}

		virtual void OverlayDisplayCallback()
		{

		}

		virtual void ReshapeCallback(int width, int height)
		{

		}

		virtual void KeyboardCallback(unsigned char key, int x, int y)
		{
			switch (key)
			{
			case 27:
				glutLeaveMainLoop();
				break;
			}
		}

		virtual void KeyboardUpCallback(unsigned char key, int x, int y)
		{

		}

		virtual void SpecialCallback(int key, int x, int y)
		{

		}

		virtual void SpecialUpCallback(int key, int x, int y)
		{

		}

		virtual void MouseCallback(int button, int state, int x, int y)
		{

		}

		virtual void MotionCallback(int x, int y)
		{

		}

		virtual void PassiveMotionCallback(int x, int y)
		{

		}

		virtual void VisibilityCallback(int state)
		{

		}

		virtual void EntryCallback(int state)
		{

		}

		virtual void CloseCallback()
		{

		}

		virtual void TimerCallback(int value)
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