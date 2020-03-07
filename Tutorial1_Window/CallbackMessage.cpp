//O3GL
#include "CallbackMessage.hpp"

//
namespace O3GL
{
	void CallbackMessage::Draw(float wx, float wy)
	{
		if (life > 0)
		{
			Text(wx, wy, 0.0f, PrintName() + "[" + PrintFormat() + "] - " + PrintValue(), 1.0f, 0.0f, 0.0f, 1.0f);
			life--;
		}
		else
		{
			Text(wx, wy, 0.0f, PrintName() + "[" + PrintFormat() + "] - " + PrintValue(), 0.0f, 0.0f, 0.0f, 1.0f);
		}
	}

	std::string SpecialCallbackMessage::KeyStr() const
	{
		switch (key)
		{
		case GLUT_KEY_F1: return "F1";
		case GLUT_KEY_F2: return "F2";
		case GLUT_KEY_F3: return "F3";
		case GLUT_KEY_F4: return "F4";
		case GLUT_KEY_F5: return "F5";
		case GLUT_KEY_F6: return "F6";
		case GLUT_KEY_F7: return "F7";
		case GLUT_KEY_F8: return "F8";
		case GLUT_KEY_F9: return "F9";
		case GLUT_KEY_F10: return "F10";
		case GLUT_KEY_F11: return "F11";
		case GLUT_KEY_F12: return "F12";
		case GLUT_KEY_LEFT: return "LEFT";
		case GLUT_KEY_UP: return "UP";
		case GLUT_KEY_RIGHT: return "RIGHT";
		case GLUT_KEY_DOWN: return "DOWN";
		case GLUT_KEY_PAGE_UP: return "PAGE_UP";
		case GLUT_KEY_PAGE_DOWN: return "PAGE_DOWN";
		case GLUT_KEY_HOME: return "HOME";
		case GLUT_KEY_END: return "END";
		case GLUT_KEY_INSERT: return "INSERT";
		default: return std::to_string(key);
		}
	}

	std::string MouseCallbackMessage::ButtonStr() const
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON: return "LEFT";
		case GLUT_MIDDLE_BUTTON: return "MIDDLE";
		case GLUT_RIGHT_BUTTON: return "RIGHT";
		default: return std::to_string(button);
		}
	}

	std::string MouseCallbackMessage::StateStr() const
	{
		switch (state)
		{
		case GLUT_DOWN: return "DOWN";
		case GLUT_UP: return "UP";
		default: return std::to_string(state);
		}
	}

	std::string VisibilityCallbackMessage::StateStr() const
	{
		switch (state)
		{
		case GLUT_NOT_VISIBLE: return "NOT_VISIBLE";
		case GLUT_VISIBLE: return "VISIBLE";
		default: return std::to_string(state);
		}
	}

	std::string EntryCallbackMessage::StateStr() const
	{
		switch (state)
		{
		case GLUT_LEFT: return "LEFT";
		case GLUT_ENTERED: return "ENTERED";
		default: return std::to_string(state);
		}
	}
};