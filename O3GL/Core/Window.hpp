#pragma once

// std
#include <vector>
#include <sstream>

namespace O3GL
{
	class Render;
}

// O3GL
#include "O3GL/Core/Utils.hpp"
#include "O3GL/Core/Render.hpp"

// 
namespace O3GL
{
	//
	struct Message
	{
		double timeElapsed;

		Message() : timeElapsed(0.0) {}

		void Restart() { timeElapsed = 0.0; };

		virtual std::string NameStr() const = 0;
		virtual std::string FormatStr() const { return ""; }
		virtual std::string ValueStr() const { return ""; }

		operator std::string();
	};

	namespace Display
	{
		struct Message : O3GL::Message
		{
			Message() : O3GL::Message() {}

			virtual std::string NameStr() const
			{
				return "Display Event";
			}
		};
	};

	namespace OverlayDisplay
	{
		struct Message : O3GL::Message
		{
			Message() : O3GL::Message() {}

			virtual std::string NameStr() const
			{
				return "OverlayDisplay Event";
			}
		};
	};

	namespace Reshape
	{
		struct Message : O3GL::Message
		{
			int width;
			int height;

			Message(int width = 0, int height = 0) : O3GL::Message(), width(width), height(height) {}

			virtual std::string NameStr() const
			{
				return "Reshape Event";
			}

			virtual std::string FormatStr() const
			{
				return "width, height";
			}

			virtual std::string ValueStr() const
			{
				std::stringstream ss;
				ss << width << ", " << height;
				return ss.str();
			}
		};
	};

	namespace Keyboard
	{
		std::string KeyStr(unsigned char key);

		struct Message : O3GL::Message
		{
			unsigned char key;
			int x;
			int y;

			Message(unsigned char key = 0, int x = 0, int y = 0) : O3GL::Message(), key(key), x(x), y(y) {}

			virtual std::string NameStr() const
			{
				return "Keyboard Event";
			}

			virtual std::string FormatStr() const
			{
				return "key, x, y";
			}

			virtual std::string ValueStr() const
			{
				std::stringstream ss;
				ss << KeyStr(key) << ", " << x << ", " << y;
				return ss.str();
			}
		};
	};

	namespace KeyboardUp
	{
		struct Message : Keyboard::Message
		{
			Message(unsigned char key = 0, int x = 0, int y = 0) : Keyboard::Message(key, x, y) {}

			virtual std::string NameStr() const
			{
				return "KeyboardUp Event";
			}
		};
	};

	namespace Special
	{
		enum Key : int
		{
			F1 = GLUT_KEY_F1,
			F2 = GLUT_KEY_F2,
			F3 = GLUT_KEY_F3,
			F4 = GLUT_KEY_F4,
			F5 = GLUT_KEY_F5,
			F6 = GLUT_KEY_F6,
			F7 = GLUT_KEY_F7,
			F8 = GLUT_KEY_F8,
			F9 = GLUT_KEY_F9,
			F10 = GLUT_KEY_F10,
			F11 = GLUT_KEY_F11,
			F12 = GLUT_KEY_F12,
			LEFT = GLUT_KEY_LEFT,
			UP = GLUT_KEY_UP,
			RIGHT = GLUT_KEY_RIGHT,
			DOWN = GLUT_KEY_DOWN,
			PAGE_UP = GLUT_KEY_PAGE_UP,
			PAGE_DOWN = GLUT_KEY_PAGE_DOWN,
			HOME = GLUT_KEY_HOME,
			END = GLUT_KEY_END,
			INSERT = GLUT_KEY_INSERT
		};

		std::string KeyStr(Key key);

		struct Message : O3GL::Message
		{
			Key key;
			int x;
			int y;

			Message(Key key = (Key)0, int x = 0, int y = 0) : O3GL::Message(), key(key), x(x), y(y) {}

			virtual std::string NameStr() const
			{
				return "Special Event";
			}

			virtual std::string FormatStr() const
			{
				return "key, x, y";
			}

			virtual std::string ValueStr() const
			{
				std::stringstream ss;
				ss << KeyStr(key) << ", " << x << ", " << y;
				return ss.str();
			}
		};
	};

	namespace SpecialUp
	{
		using Key = Special::Key;

		struct Message : Special::Message
		{
			Message(Key key = (Key)0, int x = 0, int y = 0) : Special::Message(key, x, y) {}

			virtual std::string NameStr() const
			{
				return "SpecialUp Event";
			}
		};
	};

	namespace Mouse
	{
		enum Button : int
		{
			LEFT = GLUT_LEFT_BUTTON,
			MIDDLE = GLUT_MIDDLE_BUTTON,
			RIGHT = GLUT_RIGHT_BUTTON
		};

		enum State : int
		{
			DOWN = GLUT_DOWN,
			UP = GLUT_UP
		};

		std::string ButtonStr(Button button);

		std::string StateStr(State state);

		struct Message : O3GL::Message
		{
			Button button;
			State state;
			int x;
			int y;

			Message(Button button = (Button)0, State state = (State)0, int x = 0, int y = 0) : O3GL::Message(), button(button), state(state), x(x), y(y) {}

			virtual std::string NameStr() const
			{
				return "Mouse Event";
			}

			virtual std::string FormatStr() const
			{
				return "button, state, x, y";
			}

			virtual std::string ValueStr() const
			{
				std::stringstream ss;
				ss << ButtonStr(button) << ", " << StateStr(state) << ", " << x << ", " << y;
				return ss.str();
			}
		};
	};

	namespace Motion
	{
		struct Message : O3GL::Message
		{
			int x;
			int y;

			Message(int x = 0, int y = 0) : O3GL::Message(), x(x), y(y) {}

			virtual std::string NameStr() const
			{
				return "Motion Event";
			}

			virtual std::string FormatStr() const
			{
				return "x, y";
			}

			virtual std::string ValueStr() const
			{
				std::stringstream ss;
				ss << x << ", " << y;
				return ss.str();
			}
		};
	};

	namespace PassiveMotion
	{
		struct Message : Motion::Message
		{
			Message(int x = 0, int y = 0) : Motion::Message(x, y) {}

			virtual std::string NameStr() const
			{
				return "PassiveMotion Event";
			}
		};
	};

	namespace Visibility
	{
		enum State : int
		{
			NOT_VISIBLE = GLUT_NOT_VISIBLE,
			VISIBLE = GLUT_VISIBLE
		};

		std::string StateStr(State state);

		struct Message : O3GL::Message
		{
			State state;

			Message(State state = (State)0) : O3GL::Message(), state(state) {}

			virtual std::string NameStr() const
			{
				return "Visibility Event";
			}

			virtual std::string FormatStr() const
			{
				return "state";
			}

			virtual std::string ValueStr() const
			{
				return StateStr(state);
			}
		};
	};

	namespace Entry
	{
		enum State : int
		{
			LEFT = GLUT_LEFT,
			ENTERED = GLUT_ENTERED
		};

		std::string StateStr(State state);

		struct Message : O3GL::Message
		{
			State state;

			Message(State state = (State)0) : O3GL::Message(), state(state) {}

			virtual std::string NameStr() const
			{
				return "Entry Event";
			}

			virtual std::string FormatStr() const
			{
				return "state";
			}

			virtual std::string ValueStr() const
			{
				return StateStr(state);
			}
		};
	};

	namespace Close
	{
		struct Message : O3GL::Message
		{
			Message() : O3GL::Message() {}

			virtual std::string NameStr() const
			{
				return "Close Event";
			}
		};
	};

	namespace Timer
	{
		struct Message : O3GL::Message
		{
			int value;

			Message() : O3GL::Message(), value(0) {}

			virtual std::string NameStr() const
			{
				return "Timer Event";
			}

			virtual std::string FormatStr() const
			{
				return "value";
			}

			virtual std::string ValueStr() const
			{
				std::stringstream ss;
				ss << value;
				return ss.str();
			}
		};
	};

	//
	void EnterMainLoop();
	void LeaveMainLoop();
	int CurrentWindowWidth();
	int CurrentWindowHeight();

	//
	class WindowBase
	{
	public:
		WindowBase() : renders() {}

	protected:
		virtual void InitGLStatusEvent() const {}

	protected:
		virtual void DisplayEvent(const Display::Message& m) {}
		virtual void OverlayDisplayEvent(const OverlayDisplay::Message& m) {}
		virtual void ReshapeEvent(const Reshape::Message& m) {}
		virtual void KeyboardEvent(const Keyboard::Message& m) {}
		virtual void KeyboardUpEvent(const KeyboardUp::Message& m) {}
		virtual void SpecialEvent(const Special::Message& m) {}
		virtual void SpecialUpEvent(const SpecialUp::Message& m) {}
		virtual void MouseEvent(const Mouse::Message& m) {}
		virtual void MotionEvent(const Motion::Message& m) {}
		virtual void PassiveMotionEvent(const PassiveMotion::Message& m) {}
		virtual void VisibilityEvent(const Visibility::Message& m) {}
		virtual void EntryEvent(const Entry::Message& m) {}
		virtual void CloseEvent(const Close::Message& m) {}
		virtual void TimerEvent(const Timer::Message& m) {}

	protected:
		static bool init;

		Display::Message latestDisplayMessage;
		OverlayDisplay::Message latestOverlayDisplayMessage;
		Reshape::Message latestReshapeMessage;
		Keyboard::Message latestKeyboardMessage;
		KeyboardUp::Message latestKeyboardUpMessage;
		Special::Message latestSpecialMessage;
		SpecialUp::Message latestSpecialUpMessage;
		Mouse::Message latestMouseMessage;
		Motion::Message latestMotionMessage;
		PassiveMotion::Message latestPassiveMotionMessage;
		Visibility::Message latestVisibilityMessage;
		Entry::Message latestEntryMessage;
		Close::Message latestCloseMessage;
		Timer::Message latestTimerMessage;

	protected:
		std::map<std::string, PTR<Render>> renders;

	public:
		PTR<Render> GetRender(const std::string& name)
		{
			return renders.at(name);
		}

		CONST_PTR<Render> GetRender(const std::string& name) const
		{
			return renders.at(name);
		}

		void SetRender(const std::string& name, PTR<Render> v)
		{
			renders["name"] = v;
		}

		void RemoveRender(const std::string& name)
		{
			renders.erase("name");
		}
	};

	//
	template<int key>
	class Window : public GLUTHandle, public WindowBase
	{
	public:
		Window(const std::string& name, unsigned int displayMode, int x, int y, int width, int height, unsigned int tick = 10);
		Window(int window, int x, int y, int width, int height, unsigned int tick = 10);
		~Window();

	public:
		void Init();

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

		template<class T>
		T GetInfo(GLenum state) const;

		void EnterGameMode(const std::string& gameMode);
		void LeaveGameMode();

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

	protected:
		unsigned int tick;
		bool firstTick;
		std::chrono::steady_clock::time_point timeStamp;
		double tickElapsed;
		bool subWindow;
		static Window* instance;
		int copyWinID;
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
		tickElapsed(0.0),
		subWindow(false),
		copyWinID(0)
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
		tickElapsed(0.0),
		subWindow(true),
		copyWinID(0)
	{
		instance = this;
	}

	template<int key>
	Window<key>::~Window()
	{
		instance = nullptr;
	}

	template<int key>
	void Window<key>::Init()
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
		for (std::map<std::string, PTR<Render>>::iterator it = instance->renders.begin(); it != instance->renders.end(); ++it)
		{
			it->second->Init();
		}
	}

	template<int key>
	void Window<key>::EnterGameMode(const std::string& gameMode)
	{
		glutSetWindow(*this);
		if (glutGameModeGet(GLUT_GAME_MODE_ACTIVE) == 0)
		{
			glutGameModeString(gameMode.c_str());
			if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
			{
				copyWinID = int(*this);
				(*(*this))._SetID(glutEnterGameMode());
			}
			else
			{
				THROW_EXCEPTION("GameMode: " + gameMode + " is not available");
			}
			Init();
		}
	}

	template<int key>
	void Window<key>::LeaveGameMode()
	{
		glutSetWindow(*this);
		if (glutGameModeGet(GLUT_GAME_MODE_ACTIVE) != 0)
		{
			glutLeaveGameMode();
			(*(*this))._SetID(copyWinID);
			copyWinID = 0;
		}
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
			int winID = glutCreateSubWindow(window, x, y, width, height);
			return winID;
		}
	}

	template<int key>
	void Window<key>::DisplayCallback()
	{
		if (instance)
		{
			glutSetWindow(*instance);
			for (std::map<std::string, PTR<Render>>::iterator it = instance->renders.begin(); it != instance->renders.end(); ++it)
			{
				it->second->DisplayCallback(instance->latestDisplayMessage);
			}
			instance->DisplayEvent(instance->latestDisplayMessage);
			instance->latestDisplayMessage.Restart();
		}
	}

	template<int key>
	void Window<key>::OverlayDisplayCallback()
	{
		if (instance)
		{
			glutSetWindow(*instance);
			for (std::map<std::string, PTR<Render>>::iterator it = instance->renders.begin(); it != instance->renders.end(); ++it)
			{
				it->second->OverlayDisplayCallback(instance->latestOverlayDisplayMessage);
			}
			instance->OverlayDisplayEvent(instance->latestOverlayDisplayMessage);
			instance->latestOverlayDisplayMessage.Restart();
		}
	}

	template<int key>
	void Window<key>::ReshapeCallback(int width, int height)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->latestReshapeMessage.width = width;
			instance->latestReshapeMessage.height = height;
			for (std::map<std::string, PTR<Render>>::iterator it = instance->renders.begin(); it != instance->renders.end(); ++it)
			{
				it->second->ReshapeCallback(instance->latestReshapeMessage);
			}
			instance->ReshapeEvent(instance->latestReshapeMessage);
			instance->latestReshapeMessage.Restart();
		}
	}

	template<int key>
	void Window<key>::KeyboardCallback(unsigned char key, int x, int y)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->latestKeyboardMessage.key = key;
			instance->latestKeyboardMessage.x = x;
			instance->latestKeyboardMessage.y = y;
			for (std::map<std::string, PTR<Render>>::iterator it = instance->renders.begin(); it != instance->renders.end(); ++it)
			{
				it->second->KeyboardCallback(instance->latestKeyboardMessage);
			}
			instance->KeyboardEvent(instance->latestKeyboardMessage);
			instance->latestKeyboardMessage.Restart();
		}
	}

	template<int key>
	void Window<key>::KeyboardUpCallback(unsigned char key, int x, int y)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->latestKeyboardUpMessage.key = key;
			instance->latestKeyboardUpMessage.x = x;
			instance->latestKeyboardUpMessage.y = y;
			for (std::map<std::string, PTR<Render>>::iterator it = instance->renders.begin(); it != instance->renders.end(); ++it)
			{
				it->second->KeyboardUpCallback(instance->latestKeyboardUpMessage);
			}
			instance->KeyboardUpEvent(instance->latestKeyboardUpMessage);
			instance->latestKeyboardUpMessage.Restart();
		}
	}

	template<int key>
	void Window<key>::SpecialCallback(int key, int x, int y)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->latestSpecialMessage.key = (Special::Key)key;
			instance->latestSpecialMessage.x = x;
			instance->latestSpecialMessage.y = y;
			for (std::map<std::string, PTR<Render>>::iterator it = instance->renders.begin(); it != instance->renders.end(); ++it)
			{
				it->second->SpecialCallback(instance->latestSpecialMessage);
			}
			instance->SpecialEvent(instance->latestSpecialMessage);
			instance->latestSpecialMessage.Restart();
		}
	}

	template<int key>
	void Window<key>::SpecialUpCallback(int key, int x, int y)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->latestSpecialUpMessage.key = (Special::Key)key;
			instance->latestSpecialUpMessage.x = x;
			instance->latestSpecialUpMessage.y = y;
			for (std::map<std::string, PTR<Render>>::iterator it = instance->renders.begin(); it != instance->renders.end(); ++it)
			{
				it->second->SpecialUpCallback(instance->latestSpecialUpMessage);
			}
			instance->SpecialUpEvent(instance->latestSpecialUpMessage);
			instance->latestSpecialUpMessage.Restart();
		}
	}

	template<int key>
	void Window<key>::MouseCallback(int button, int state, int x, int y)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->latestMouseMessage.button = (Mouse::Button)button;
			instance->latestMouseMessage.state = (Mouse::State)state;
			instance->latestMouseMessage.x = x;
			instance->latestMouseMessage.y = y;
			for (std::map<std::string, PTR<Render>>::iterator it = instance->renders.begin(); it != instance->renders.end(); ++it)
			{
				it->second->MouseCallback(instance->latestMouseMessage);
			}
			instance->MouseEvent(instance->latestMouseMessage);
			instance->latestMouseMessage.Restart();
		}
	}

	template<int key>
	void Window<key>::MotionCallback(int x, int y)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->latestMotionMessage.x = x;
			instance->latestMotionMessage.y = y;
			for (std::map<std::string, PTR<Render>>::iterator it = instance->renders.begin(); it != instance->renders.end(); ++it)
			{
				it->second->MotionCallback(instance->latestMotionMessage);
			}
			instance->MotionEvent(instance->latestMotionMessage);
			instance->latestMotionMessage.Restart();
		}
	}

	template<int key>
	void Window<key>::PassiveMotionCallback(int x, int y)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->latestPassiveMotionMessage.x = x;
			instance->latestPassiveMotionMessage.y = y;
			for (std::map<std::string, PTR<Render>>::iterator it = instance->renders.begin(); it != instance->renders.end(); ++it)
			{
				it->second->PassiveMotionCallback(instance->latestPassiveMotionMessage);
			}
			instance->PassiveMotionEvent(instance->latestPassiveMotionMessage);
			instance->latestPassiveMotionMessage.Restart();
		}
	}

	template<int key>
	void Window<key>::VisibilityCallback(int state)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->latestVisibilityMessage.state = (Visibility::State)state;
			for (std::map<std::string, PTR<Render>>::iterator it = instance->renders.begin(); it != instance->renders.end(); ++it)
			{
				it->second->VisibilityCallback(instance->latestVisibilityMessage);
			}
			instance->VisibilityEvent(instance->latestVisibilityMessage);
			instance->latestVisibilityMessage.Restart();
		}
	}

	template<int key>
	void Window<key>::EntryCallback(int state)
	{
		if (instance)
		{
			glutSetWindow(*instance);
			instance->latestEntryMessage.state = (Entry::State)state;
			for (std::map<std::string, PTR<Render>>::iterator it = instance->renders.begin(); it != instance->renders.end(); ++it)
			{
				it->second->EntryCallback(instance->latestEntryMessage);
			}
			instance->EntryEvent(instance->latestEntryMessage);
			instance->latestEntryMessage.Restart();
		}
	}

	template<int key>
	void Window<key>::CloseCallback()
	{
		if (instance)
		{
			glutSetWindow(*instance);
			for (std::map<std::string, PTR<Render>>::iterator it = instance->renders.begin(); it != instance->renders.end(); ++it)
			{
				it->second->CloseCallback(instance->latestCloseMessage);
			}
			instance->CloseEvent(instance->latestCloseMessage);
			instance->latestCloseMessage.Restart();
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
				instance->tickElapsed = 0.0;
				instance->firstTick = false;
			}
			else
			{
				std::chrono::steady_clock::time_point timeStamp2 = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double, std::milli> timeElapsed = timeStamp2 - instance->timeStamp;
				instance->tickElapsed = timeElapsed.count();
				instance->timeStamp = timeStamp2;
			}

			instance->latestDisplayMessage.timeElapsed += instance->tickElapsed;
			instance->latestOverlayDisplayMessage.timeElapsed += instance->tickElapsed;
			instance->latestReshapeMessage.timeElapsed += instance->tickElapsed;
			instance->latestKeyboardMessage.timeElapsed += instance->tickElapsed;
			instance->latestKeyboardUpMessage.timeElapsed += instance->tickElapsed;
			instance->latestSpecialMessage.timeElapsed += instance->tickElapsed;
			instance->latestSpecialUpMessage.timeElapsed += instance->tickElapsed;
			instance->latestMouseMessage.timeElapsed += instance->tickElapsed;
			instance->latestMotionMessage.timeElapsed += instance->tickElapsed;
			instance->latestPassiveMotionMessage.timeElapsed += instance->tickElapsed;
			instance->latestVisibilityMessage.timeElapsed += instance->tickElapsed;
			instance->latestEntryMessage.timeElapsed += instance->tickElapsed;
			instance->latestCloseMessage.timeElapsed += instance->tickElapsed;
			instance->latestTimerMessage.timeElapsed += instance->tickElapsed;

			instance->latestTimerMessage.value = value;
			for (std::map<std::string, PTR<Render>>::iterator it = instance->renders.begin(); it != instance->renders.end(); ++it)
			{
				it->second->TimerCallback(instance->latestTimerMessage);
			}
			instance->TimerEvent(instance->latestTimerMessage);
			instance->latestTimerMessage.Restart();

			glutTimerFunc(instance->tick, TimerCallback, 0);
		}
	}
};