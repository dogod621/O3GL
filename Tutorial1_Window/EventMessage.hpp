// std
#include<sstream>

// O3GL
#include "O3GL/Utils.hpp"

//
namespace O3GL
{
	//
	class EventMessage
	{
	public:
		int life;

		EventMessage() : life(0) {}

		void Active()
		{
			life = 5;
		}

		virtual std::string PrintName() const = 0;
		virtual std::string PrintFormat() const { return ""; }
		virtual std::string PrintValue() const { return ""; }

		void Draw(float wx, float wy);
	};

	class DisplayEventMessage : public EventMessage
	{
	public:
		DisplayEventMessage() : EventMessage() {}

		virtual std::string PrintName() const
		{
			return "Display Event";
		}
	};

	class OverlayDisplayEventMessage : public EventMessage
	{
	public:
		OverlayDisplayEventMessage() : EventMessage() {}

		virtual std::string PrintName() const
		{
			return "OverlayDisplay Event";
		}
	};

	class ReshapeEventMessage : public EventMessage
	{
	public:
		int width;
		int height;

		ReshapeEventMessage() : EventMessage(), width(0), height(0) {}

		virtual std::string PrintName() const
		{
			return "Reshape Event";
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

	class KeyboardEventMessage : public EventMessage
	{
	public:
		unsigned char key;
		int x;
		int y;

		KeyboardEventMessage() : EventMessage(), key(0), x(0), y(0) {}

		std::string KeyStr() const
		{
			if (key >= 32 && key <= 126)
				return std::string{ (char)key };
			else
				return std::to_string(int(key));
		}

		virtual std::string PrintName() const
		{
			return "Keyboard Event";
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

	class KeyboardUpEventMessage : public KeyboardEventMessage
	{
	public:
		KeyboardUpEventMessage() : KeyboardEventMessage() {}

		virtual std::string PrintName() const
		{
			return "KeyboardUp Event";
		}
	};

	class SpecialEventMessage : public EventMessage
	{
	public:
		int key;
		int x;
		int y;

		SpecialEventMessage() : EventMessage(), key(0), x(0), y(0) {}

		std::string KeyStr() const;

		virtual std::string PrintName() const
		{
			return "Special Event";
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

	class SpecialUpEventMessage : public SpecialEventMessage
	{
	public:
		SpecialUpEventMessage() : SpecialEventMessage() {}

		virtual std::string PrintName() const
		{
			return "SpecialUp Event";
		}
	};

	class MouseEventMessage : public EventMessage
	{
	public:
		int button;
		int state;
		int x;
		int y;

		MouseEventMessage() : EventMessage(), button(0), state(0), x(0), y(0) {}

		std::string ButtonStr() const;

		std::string StateStr() const;

		virtual std::string PrintName() const
		{
			return "Mouse Event";
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

	class MotionEventMessage : public EventMessage
	{
	public:
		int x;
		int y;

		MotionEventMessage() : EventMessage(), x(0), y(0) {}

		virtual std::string PrintName() const
		{
			return "Motion Event";
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

	class PassiveMotionEventMessage : public MotionEventMessage
	{
	public:
		PassiveMotionEventMessage() : MotionEventMessage() {}

		virtual std::string PrintName() const
		{
			return "PassiveMotion Event";
		}
	};

	class VisibilityEventMessage : public EventMessage
	{
	public:
		int state;

		VisibilityEventMessage() : EventMessage(), state(0) {}

		std::string StateStr() const;

		virtual std::string PrintName() const
		{
			return "Visibility Event";
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

	class EntryEventMessage : public EventMessage
	{
	public:
		int state;

		EntryEventMessage() : EventMessage(), state(0) {}

		std::string StateStr() const;

		virtual std::string PrintName() const
		{
			return "Entry Event";
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

	class CloseEventMessage : public EventMessage
	{
	public:
		CloseEventMessage() : EventMessage() {}

		virtual std::string PrintName() const
		{
			return "Close Event";
		}
	};

	class TimerEventMessage : public EventMessage
	{
	public:
		int value;

		TimerEventMessage() : EventMessage(), value(0) {}

		virtual std::string PrintName() const
		{
			return "Timer Event";
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