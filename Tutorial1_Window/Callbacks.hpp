// std
#include<sstream>

// O3GL
#include "O3GL/Utils.hpp"

#define NAME_LENGTH 24
#define INFO_LENGTH 12

//
class CallbackMessage
{
public:
	int life;

	CallbackMessage() : life(0) {}

	void Active()
	{
		life = 5;
	}

	virtual std::string Print() const = 0;

	void Draw(float& wx, float& wy, float lineHeight = 0.06f)
	{
		if (life > 0)
		{
			O3GL::Text(wx, wy, 0.0f, Print(), 1.0f, 0.0f, 0.0f, 1.0f);
			life--;
		}
		else
		{
			O3GL::Text(wx, wy, 0.0f, Print(), 0.0f, 0.0f, 0.0f, 1.0f);
		}
		wy += lineHeight;
	}
};

class DisplayCallbackMessage : public CallbackMessage
{
public:
	DisplayCallbackMessage() : CallbackMessage() {}

	virtual std::string Print() const
	{
		std::stringstream ss;
		ss << std::right << std::setw(NAME_LENGTH) << "Display";
		ss << ":";
		return ss.str();
	}
};

class OverlayDisplayCallbackMessage : public CallbackMessage
{
public:
	OverlayDisplayCallbackMessage() : CallbackMessage() {}

	virtual std::string Print() const
	{
		std::stringstream ss;
		ss << std::right << std::setw(NAME_LENGTH) << "OverlayDisplay";
		ss << ":";
		return ss.str();
	}
};

class ReshapeCallbackMessage : public CallbackMessage
{
public:
	int width;
	int height;

	ReshapeCallbackMessage() : CallbackMessage(), width(0), height(0) {}

	virtual std::string Print() const
	{
		std::stringstream ss;
		ss << std::right << std::setw(NAME_LENGTH) << "Reshape";
		ss << ":";
		ss << std::right << std::setw(INFO_LENGTH) << "width";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << width;
		ss << std::right << std::setw(INFO_LENGTH) << "height";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << height;
		return ss.str();
	}
};

class KeyboardCallbackMessage : public CallbackMessage
{
public:
	unsigned char key;
	int x;
	int y;

	KeyboardCallbackMessage() : CallbackMessage(), key(0), x(0), y(0) {}

	virtual std::string Print() const
	{
		std::stringstream ss;
		ss << std::right << std::setw(NAME_LENGTH) << "Keyboard";
		ss << ":";
		ss << std::right << std::setw(INFO_LENGTH) << "key";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << key;
		ss << std::right << std::setw(INFO_LENGTH) << "x";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << x;
		ss << std::right << std::setw(INFO_LENGTH) << "y";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << y;
		return ss.str();
	}
};

class KeyboardUpCallbackMessage : public KeyboardCallbackMessage
{
public:
	KeyboardUpCallbackMessage() : KeyboardCallbackMessage() {}

	virtual std::string Print() const
	{
		std::stringstream ss;
		ss << std::right << std::setw(NAME_LENGTH) << "KeyboardUp";
		ss << ":";
		ss << std::right << std::setw(INFO_LENGTH) << "key";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << key;
		ss << std::right << std::setw(INFO_LENGTH) << "x";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << x;
		ss << std::right << std::setw(INFO_LENGTH) << "y";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << y;
		return ss.str();
	}
};

class SpecialCallbackMessage : public CallbackMessage
{
public:
	int key;
	int x;
	int y;

	SpecialCallbackMessage() : CallbackMessage(), key(0), x(0), y(0) {}

	std::string KeyStr() const
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

	virtual std::string Print() const
	{
		std::stringstream ss;
		ss << std::right << std::setw(NAME_LENGTH) << "Special";
		ss << ":";
		ss << std::right << std::setw(INFO_LENGTH) << "key";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << KeyStr();
		ss << std::right << std::setw(INFO_LENGTH) << "x";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << x;
		ss << std::right << std::setw(INFO_LENGTH) << "y";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << y;
		return ss.str();
	}
};

class SpecialUpCallbackMessage : public SpecialCallbackMessage
{
public:
	SpecialUpCallbackMessage() : SpecialCallbackMessage() {}

	virtual std::string Print() const
	{
		std::stringstream ss;
		ss << std::right << std::setw(NAME_LENGTH) << "SpecialUp";
		ss << ":";
		ss << std::right << std::setw(INFO_LENGTH) << "key";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << KeyStr();
		ss << std::right << std::setw(INFO_LENGTH) << "x";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << x;
		ss << std::right << std::setw(INFO_LENGTH) << "y";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << y;
		return ss.str();
	}
};

class MouseCallbackMessage : public CallbackMessage
{
public:
	int button;
	int state;
	int x;
	int y;

	MouseCallbackMessage() : CallbackMessage(), button(0), state(0), x(0), y(0) {}

	std::string ButtonStr() const
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON: return "LEFT";
		case GLUT_MIDDLE_BUTTON: return "MIDDLE";
		case GLUT_RIGHT_BUTTON: return "RIGHT";
		default: return std::to_string(button);
		}
	}

	std::string StateStr() const
	{
		switch (state)
		{
		case GLUT_DOWN: return "DOWN";
		case GLUT_UP: return "UP";
		default: return std::to_string(state);
		}
	}

	virtual std::string Print() const
	{
		std::stringstream ss;
		ss << std::right << std::setw(NAME_LENGTH) << "Mouse";
		ss << ":";
		ss << std::right << std::setw(INFO_LENGTH) << "button";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << ButtonStr();
		ss << std::right << std::setw(INFO_LENGTH) << "state";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << StateStr();
		ss << std::right << std::setw(INFO_LENGTH) << "x";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << x;
		ss << std::right << std::setw(INFO_LENGTH) << "y";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << y;
		return ss.str();
	}
};

class MotionCallbackMessage : public CallbackMessage
{
public:
	int x;
	int y;

	MotionCallbackMessage() : CallbackMessage(), x(0), y(0) {}

	virtual std::string Print() const
	{
		std::stringstream ss;
		ss << std::right << std::setw(NAME_LENGTH) << "Motion";
		ss << ":";
		ss << std::right << std::setw(INFO_LENGTH) << "x";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << x;
		ss << std::right << std::setw(INFO_LENGTH) << "y";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << y;
		return ss.str();
	}
};

class PassiveMotionCallbackMessage : public MotionCallbackMessage
{
public:
	PassiveMotionCallbackMessage() : MotionCallbackMessage() {}

	virtual std::string Print() const
	{
		std::stringstream ss;
		ss << std::right << std::setw(NAME_LENGTH) << "PassiveMotion";
		ss << ":";
		ss << std::right << std::setw(INFO_LENGTH) << "x";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << x;
		ss << std::right << std::setw(INFO_LENGTH) << "y";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << y;
		return ss.str();
	}
};

class VisibilityCallbackMessage : public CallbackMessage
{
public:
	int state;

	VisibilityCallbackMessage() : CallbackMessage(), state(0) {}

	std::string StateStr() const
	{
		switch (state)
		{
		case GLUT_NOT_VISIBLE: return "NOT_VISIBLE";
		case GLUT_VISIBLE: return "VISIBLE";
		default: return std::to_string(state);
		}
	}

	virtual std::string Print() const
	{
		std::stringstream ss;
		ss << std::right << std::setw(NAME_LENGTH) << "Visibility";
		ss << ":";
		ss << std::right << std::setw(INFO_LENGTH) << "state";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << StateStr();
		return ss.str();
	}
};

class EntryCallbackMessage : public CallbackMessage
{
public:
	int state;

	EntryCallbackMessage() : CallbackMessage(), state(0) {}

	std::string StateStr() const
	{
		switch (state)
		{
		case GLUT_LEFT: return "LEFT";
		case GLUT_ENTERED: return "ENTERED";
		default: return std::to_string(state);
		}
	}

	virtual std::string Print() const
	{
		std::stringstream ss;
		ss << std::right << std::setw(NAME_LENGTH) << "Entry";
		ss << ":";
		ss << std::right << std::setw(INFO_LENGTH) << "state";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << StateStr();
		return ss.str();
	}
};

class CloseCallbackMessage : public CallbackMessage
{
public:
	CloseCallbackMessage() : CallbackMessage() {}

	virtual std::string Print() const
	{
		std::stringstream ss;
		ss << std::right << std::setw(NAME_LENGTH) << "Close";
		ss << ":";
		return ss.str();
	}
};

class TimerCallbackMessage : public CallbackMessage
{
public:
	int value;

	TimerCallbackMessage() : CallbackMessage(), value(0) {}

	virtual std::string Print() const
	{
		std::stringstream ss;
		ss << std::right << std::setw(NAME_LENGTH) << "Timer";
		ss << ":";
		ss << std::right << std::setw(INFO_LENGTH) << "value";
		ss << "-";
		ss << std::left << std::setw(INFO_LENGTH) << value;
		return ss.str();
	}
};

//
static DisplayCallbackMessage displayCallbackMessage;
static OverlayDisplayCallbackMessage overlayDisplayCallbackMessage;
static ReshapeCallbackMessage reshapeCallbackMessage;
static KeyboardCallbackMessage keyboardCallbackMessage;
static KeyboardUpCallbackMessage keyboardUpCallbackMessage;
static SpecialCallbackMessage specialCallbackMessage;
static SpecialUpCallbackMessage specialUpCallbackMessage;
static MouseCallbackMessage mouseCallbackMessage;
static MotionCallbackMessage motionCallbackMessage;
static PassiveMotionCallbackMessage passiveMotionCallbackMessage;
static VisibilityCallbackMessage visibilityCallbackMessage;
static EntryCallbackMessage entryCallbackMessage;
static CloseCallbackMessage closeCallbackMessage;
static TimerCallbackMessage timerCallbackMessage;

//
void DisplayCallback();

void OverlayDisplayCallback();

void ReshapeCallback(int width, int height);

void KeyboardCallback(unsigned char key, int x, int y);

void KeyboardUpCallback(unsigned char key, int x, int y);

void SpecialCallback(int key, int x, int y);

void SpecialUpCallback(int key, int x, int y);

void MouseCallback(int button, int state, int x, int y);

void MotionCallback(int x, int y);

void PassiveMotionCallback(int x, int y);

void VisibilityCallback(int state);

void EntryCallback(int state);

void CloseCallback();

void TimerCallback(int value);