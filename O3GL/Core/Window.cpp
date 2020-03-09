// O3GL
#include "O3GL/Core/Window.hpp"

//
namespace O3GL
{
	Message::operator std::string()
	{
		return NameStr() + ": [" + FormatStr() + " - " + ValueStr() + "], [timeElapsed - " + std::to_string(timeElapsed) + "]";
	}

	std::string Keyboard::KeyStr(unsigned char key)
	{
		if (key >= 32 && key <= 126)
			return std::string{ (char)key };
		else
			return std::to_string(int(key));
	}

	std::string Special::KeyStr(Key key)
	{
		switch (key)
		{
		case Key::F1: return "F1";
		case Key::F2: return "F2";
		case Key::F3: return "F3";
		case Key::F4: return "F4";
		case Key::F5: return "F5";
		case Key::F6: return "F6";
		case Key::F7: return "F7";
		case Key::F8: return "F8";
		case Key::F9: return "F9";
		case Key::F10: return "F10";
		case Key::F11: return "F11";
		case Key::F12: return "F12";
		case Key::LEFT: return "LEFT";
		case Key::UP: return "UP";
		case Key::RIGHT: return "RIGHT";
		case Key::DOWN: return "DOWN";
		case Key::PAGE_UP: return "PAGE_UP";
		case Key::PAGE_DOWN: return "PAGE_DOWN";
		case Key::HOME: return "HOME";
		case Key::END: return "END";
		case Key::INSERT: return "INSERT";
		default: return std::to_string(key);
		}
	}

	std::string Mouse::ButtonStr(Button button)
	{
		switch (button)
		{
		case Button::LEFT: return "LEFT";
		case Button::MIDDLE: return "MIDDLE";
		case Button::RIGHT: return "RIGHT";
		default: return std::to_string(button);
		}
	}

	std::string Mouse::StateStr(State state)
	{
		switch (state)
		{
		case State::DOWN: return "DOWN";
		case State::UP: return "UP";
		default: return std::to_string(state);
		}
	}

	std::string Visibility::StateStr(State state)
	{
		switch (state)
		{
		case State::NOT_VISIBLE: return "NOT_VISIBLE";
		case State::VISIBLE: return "VISIBLE";
		default: return std::to_string(state);
		}
	}

	std::string Entry::StateStr(State state)
	{
		switch (state)
		{
		case State::LEFT: return "LEFT";
		case State::ENTERED: return "ENTERED";
		default: return std::to_string(state);
		}
	}

	void EnterMainLoop()
	{
		glutMainLoop();
	}

	void LeaveMainLoop()
	{
		glutLeaveMainLoop();
	}

	int CurrentWindowWidth()
	{
		return glutGet(GLUT_WINDOW_WIDTH);
	}

	int CurrentWindowHeight()
	{
		return glutGet(GLUT_WINDOW_HEIGHT);
	}

	bool WindowBase::init = false;
};