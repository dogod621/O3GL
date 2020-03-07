// std
#include<sstream>

// O3GL
#include "O3GL/Window.hpp"

//
namespace O3GL
{
	_Window* _Window::instance = nullptr;
	std::vector<int> _Window::bindStack = std::vector<int>();

	int InitAndCreateWindow(const std::string& name, unsigned int displayMode, int x, int y, int width, int height)
	{
		if (_Window::Instance())
		{
			THROW_EXCEPTION("Window is already created");
			glutInitDisplayMode(displayMode);
			glutInitWindowPosition(x, y);
			glutInitWindowSize(width, height);
			return glutCreateWindow(name.c_str());
		}
		else
		{
			int argc2 = 1;
			std::string s = "";
			std::vector<char*> argv{ &s[0] };
			glutInit(&argc2, &argv[0]);
			glutInitDisplayMode(displayMode);
			glutInitWindowPosition(x, y);
			glutInitWindowSize(width, height);
			int winID = glutCreateWindow(name.c_str());
			GLenum err = glewInit();
			if (err != GLEW_OK)
			{
				std::stringstream ss;
				std::cout << glewGetErrorString(err);
				THROW_EXCEPTION(ss.str());
			}
			_Window::BindStack()->push_back(winID);
			return winID;
		}
	}

	void DisplayCallback()
	{
		if (_Window::Instance())
		{
			_Window::Instance()->DisplayEvent();
		}
	}

	void OverlayDisplayCallback()
	{
		if (_Window::Instance())
		{
			_Window::Instance()->OverlayDisplayEvent();
		}
	}

	void ReshapeCallback(int width, int height)
	{
		if (_Window::Instance())
		{
			_Window::Instance()->ReshapeEvent(width, height);
		}
	}

	void KeyboardCallback(unsigned char key, int x, int y)
	{
		if (_Window::Instance())
		{
			_Window::Instance()->KeyboardEvent(key, x, y);
		}
	}

	void KeyboardUpCallback(unsigned char key, int x, int y)
	{
		if (_Window::Instance())
		{
			_Window::Instance()->KeyboardUpEvent(key, x, y);
		}
	}

	void SpecialCallback(int key, int x, int y)
	{
		if (_Window::Instance())
		{
			_Window::Instance()->SpecialEvent(key, x, y);
		}
	}

	void SpecialUpCallback(int key, int x, int y)
	{
		if (_Window::Instance())
		{
			_Window::Instance()->SpecialUpEvent(key, x, y);
		}
	}

	void MouseCallback(int button, int state, int x, int y)
	{
		if (_Window::Instance())
		{
			_Window::Instance()->MouseEvent(button, state, x, y);
		}
	}

	void MotionCallback(int x, int y)
	{
		if (_Window::Instance())
		{
			_Window::Instance()->MotionEvent(x, y);
		}
	}

	void PassiveMotionCallback(int x, int y)
	{
		if (_Window::Instance())
		{
			_Window::Instance()->PassiveMotionEvent(x, y);
		}
	}

	void VisibilityCallback(int state)
	{
		if (_Window::Instance())
		{
			_Window::Instance()->VisibilityEvent(state);
		}
	}

	void EntryCallback(int state)
	{
		if (_Window::Instance())
		{
			_Window::Instance()->EntryEvent(state);
		}
	}

	void CloseCallback()
	{
		if (_Window::Instance())
		{
			_Window::Instance()->CloseEvent();
		}
	}

	void TimerCallback(int value)
	{
		if (_Window::Instance())
		{
			_Window::Instance()->TimerEvent(value);
		}
		glutTimerFunc(_Window::Instance()->Tick(), TimerCallback, 0);
	}

	//
	_Window::_Window(const std::string& name, unsigned int displayMode, int x, int y, int width, int height, unsigned int tick) : GLUTObject(InitAndCreateWindow(name, displayMode, x, y, width, height), glutDestroyWindow), tick(tick)
	{
		instance = this;
	}

	_Window::~_Window()
	{
		instance = nullptr;
	}

	void _Window::Begin() const
	{
		bindStack.push_back(*this);
		glutSetWindow(bindStack.back());
	}

	void _Window::End() const
	{
		if (bindStack.empty())
		{
			THROW_EXCEPTION("Invalid End");
		}
		else if (bindStack.back() != int(*this))
		{
			THROW_EXCEPTION("Invalid End");
		}

		bindStack.pop_back();
		if (bindStack.empty())
		{
			THROW_EXCEPTION("This should not be happend");
		}
		else
		{
			glutSetWindow(bindStack.back());
		}
	}

	void _Window::Start() const
	{
		RegisterCallbackEvent();
		InitGLStatusEvent();
		glutMainLoop();
	}

	void _Window::RegisterCallbackEvent() const
	{
		Begin();
		glutDisplayFunc(DisplayCallback);
		glutOverlayDisplayFunc(OverlayDisplayCallback);
		glutReshapeFunc(ReshapeCallback);
		glutKeyboardFunc(KeyboardCallback);
		glutKeyboardUpFunc(KeyboardUpCallback);
		glutSpecialFunc(SpecialCallback);
		glutSpecialUpFunc(SpecialUpCallback);
		glutMouseFunc(MouseCallback);
		glutMotionFunc(MotionCallback);
		glutPassiveMotionFunc(PassiveMotionCallback);
		glutVisibilityFunc(VisibilityCallback);
		glutEntryFunc(EntryCallback);
		glutCloseFunc(CloseCallback);
		glutTimerFunc(tick, TimerCallback, 0);
		End();
	}
};
