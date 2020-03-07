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

	void _DisplayCallback()
	{
		if (_Window::Instance())
		{
			_Window::Instance()->DisplayCallback();
		}
	}

	void _OverlayDisplayCallback()
	{
		if (_Window::Instance())
		{
			_Window::Instance()->OverlayDisplayCallback();
		}
	}

	void _ReshapeCallback(int width, int height)
	{
		if (_Window::Instance())
		{
			_Window::Instance()->ReshapeCallback(width, height);
		}
	}

	void _KeyboardCallback(unsigned char key, int x, int y)
	{
		if (_Window::Instance())
		{
			_Window::Instance()->KeyboardCallback(key, x, y);
		}
	}

	void _KeyboardUpCallback(unsigned char key, int x, int y)
	{
		if (_Window::Instance())
		{
			_Window::Instance()->KeyboardUpCallback(key, x, y);
		}
	}

	void _SpecialCallback(int key, int x, int y)
	{
		if (_Window::Instance())
		{
			_Window::Instance()->SpecialCallback(key, x, y);
		}
	}

	void _SpecialUpCallback(int key, int x, int y)
	{
		if (_Window::Instance())
		{
			_Window::Instance()->SpecialUpCallback(key, x, y);
		}
	}

	void _MouseCallback(int button, int state, int x, int y)
	{
		if (_Window::Instance())
		{
			_Window::Instance()->MouseCallback(button, state, x, y);
		}
	}

	void _MotionCallback(int x, int y)
	{
		if (_Window::Instance())
		{
			_Window::Instance()->MotionCallback(x, y);
		}
	}

	void _PassiveMotionCallback(int x, int y)
	{
		if (_Window::Instance())
		{
			_Window::Instance()->PassiveMotionCallback(x, y);
		}
	}

	void _VisibilityCallback(int state)
	{
		if (_Window::Instance())
		{
			_Window::Instance()->VisibilityCallback(state);
		}
	}

	void _EntryCallback(int state)
	{
		if (_Window::Instance())
		{
			_Window::Instance()->EntryCallback(state);
		}
	}

	void _CloseCallback()
	{
		if (_Window::Instance())
		{
			_Window::Instance()->CloseCallback();
		}
	}

	void _TimerCallback(int value)
	{
		if (_Window::Instance())
		{
			_Window::Instance()->TimerCallback(value);
		}
		glutTimerFunc(_Window::Instance()->Tick(), _TimerCallback, 0);
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
		Begin();
		InitGLStatusCallback();
		glutDisplayFunc(_DisplayCallback);
		glutOverlayDisplayFunc(_OverlayDisplayCallback);
		glutReshapeFunc(_ReshapeCallback);
		glutKeyboardFunc(_KeyboardCallback);
		glutKeyboardUpFunc(_KeyboardUpCallback);
		glutSpecialFunc(_SpecialCallback);
		glutSpecialUpFunc(_SpecialUpCallback);
		glutMouseFunc(_MouseCallback);
		glutMotionFunc(_MotionCallback);
		glutPassiveMotionFunc(_PassiveMotionCallback);
		glutVisibilityFunc(_VisibilityCallback);
		glutEntryFunc(_EntryCallback);
		glutCloseFunc(_CloseCallback);
		glutTimerFunc(tick, _TimerCallback, 0);
		End();

		glutMainLoop();
	}
};
