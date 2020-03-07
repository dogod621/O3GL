// std
#include<sstream>

// O3GL
#include "O3GL/Utils.hpp"

//
namespace O3GL
{
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

		virtual std::string PrintName() const = 0;
		virtual std::string PrintFormat() const { return ""; }
		virtual std::string PrintValue() const { return ""; }

		void Draw(float wx, float wy);
	};

	class DisplayCallbackMessage : public CallbackMessage
	{
	public:
		DisplayCallbackMessage() : CallbackMessage() {}

		virtual std::string PrintName() const
		{
			return "Display";
		}
	};

	class OverlayDisplayCallbackMessage : public CallbackMessage
	{
	public:
		OverlayDisplayCallbackMessage() : CallbackMessage() {}

		virtual std::string PrintName() const
		{
			return "OverlayDisplay";
		}
	};

	class ReshapeCallbackMessage : public CallbackMessage
	{
	public:
		int width;
		int height;

		ReshapeCallbackMessage() : CallbackMessage(), width(0), height(0) {}

		virtual std::string PrintName() const
		{
			return "Reshape";
		}

		virtual std::string PrintFormat() const
		{
			return "width, height";
		}

		virtual std::string PrintValue() const
		{
			std::stringstream ss;
			ss << width << ", " << height;
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

		std::string KeyStr() const
		{
			if (key >= 32 && key <= 126)
				return std::string{ (char)key };
			else
				return std::to_string(int(key));
		}

		virtual std::string PrintName() const
		{
			return "Keyboard";
		}

		virtual std::string PrintFormat() const
		{
			return "key, x, y";
		}

		virtual std::string PrintValue() const
		{
			std::stringstream ss;
			ss << KeyStr() << ", " << x << ", " << y;
			return ss.str();
		}
	};

	class KeyboardUpCallbackMessage : public KeyboardCallbackMessage
	{
	public:
		KeyboardUpCallbackMessage() : KeyboardCallbackMessage() {}

		virtual std::string PrintName() const
		{
			return "KeyboardUp";
		}
	};

	class SpecialCallbackMessage : public CallbackMessage
	{
	public:
		int key;
		int x;
		int y;

		SpecialCallbackMessage() : CallbackMessage(), key(0), x(0), y(0) {}

		std::string KeyStr() const;

		virtual std::string PrintName() const
		{
			return "Special";
		}

		virtual std::string PrintFormat() const
		{
			return "key, x, y";
		}

		virtual std::string PrintValue() const
		{
			std::stringstream ss;
			ss << KeyStr() << ", " << x << ", " << y;
			return ss.str();
		}
	};

	class SpecialUpCallbackMessage : public SpecialCallbackMessage
	{
	public:
		SpecialUpCallbackMessage() : SpecialCallbackMessage() {}

		virtual std::string PrintName() const
		{
			return "SpecialUp";
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

		std::string ButtonStr() const;

		std::string StateStr() const;

		virtual std::string PrintName() const
		{
			return "Mouse";
		}

		virtual std::string PrintFormat() const
		{
			return "button, state, x, y";
		}

		virtual std::string PrintValue() const
		{
			std::stringstream ss;
			ss << ButtonStr() << ", " << StateStr() << ", " << x << ", " << y;
			return ss.str();
		}
	};

	class MotionCallbackMessage : public CallbackMessage
	{
	public:
		int x;
		int y;

		MotionCallbackMessage() : CallbackMessage(), x(0), y(0) {}

		virtual std::string PrintName() const
		{
			return "Motion";
		}

		virtual std::string PrintFormat() const
		{
			return "x, y";
		}

		virtual std::string PrintValue() const
		{
			std::stringstream ss;
			ss << x << ", " << y;
			return ss.str();
		}
	};

	class PassiveMotionCallbackMessage : public MotionCallbackMessage
	{
	public:
		PassiveMotionCallbackMessage() : MotionCallbackMessage() {}

		virtual std::string PrintName() const
		{
			return "PassiveMotion";
		}
	};

	class VisibilityCallbackMessage : public CallbackMessage
	{
	public:
		int state;

		VisibilityCallbackMessage() : CallbackMessage(), state(0) {}

		std::string StateStr() const;

		virtual std::string PrintName() const
		{
			return "Visibility";
		}

		virtual std::string PrintFormat() const
		{
			return "state";
		}

		virtual std::string PrintValue() const
		{
			std::stringstream ss;
			ss << StateStr();
			return ss.str();
		}
	};

	class EntryCallbackMessage : public CallbackMessage
	{
	public:
		int state;

		EntryCallbackMessage() : CallbackMessage(), state(0) {}

		std::string StateStr() const;

		virtual std::string PrintName() const
		{
			return "Entry";
		}

		virtual std::string PrintFormat() const
		{
			return "state";
		}

		virtual std::string PrintValue() const
		{
			std::stringstream ss;
			ss << StateStr();
			return ss.str();
		}
	};

	class CloseCallbackMessage : public CallbackMessage
	{
	public:
		CloseCallbackMessage() : CallbackMessage() {}

		virtual std::string PrintName() const
		{
			return "Close";
		}
	};

	class TimerCallbackMessage : public CallbackMessage
	{
	public:
		int value;

		TimerCallbackMessage() : CallbackMessage(), value(0) {}

		virtual std::string PrintName() const
		{
			return "Timer";
		}

		virtual std::string PrintFormat() const
		{
			return "value";
		}

		virtual std::string PrintValue() const
		{
			std::stringstream ss;
			ss << value;
			return ss.str();
		}
	};
};