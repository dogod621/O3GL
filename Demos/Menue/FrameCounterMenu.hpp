#pragma once

// O3GL
#include "O3GL/Core/Menu.hpp"

//
namespace O3GL
{
	//
	template<int key>
	class ModifyFrameCounterMenu : public Menu<key>
	{
	public:
		enum Option : int
		{
			ADD_ONE = 1,
			ADD_TWO = 2,
			ADD_TEN = 3,
			SUB_ONE = 4,
			SUB_TWO = 5,
			SUB_TEN = 6,
			MUL_ONE = 7,
			MUL_TWO = 8,
			MUL_TEN = 9,
			DIV_ONE = 10,
			DIV_TWO = 11,
			DIV_TEN = 12
		};

	public:
		ModifyFrameCounterMenu(unsigned int* frameCounter) :
			Menu(),
			frameCounter(frameCounter)
		{
			AddItem("+1", Option::ADD_ONE);
			AddItem("+2", Option::ADD_TWO);
			AddItem("+10", Option::ADD_TEN);
			AddItem("-1", Option::SUB_ONE);
			AddItem("-2", Option::SUB_TWO);
			AddItem("-10", Option::SUB_TEN);
			AddItem("*1", Option::MUL_ONE);
			AddItem("*2", Option::MUL_TWO);
			AddItem("*10", Option::MUL_TEN);
			AddItem("/1", Option::DIV_ONE);
			AddItem("/2", Option::DIV_TWO);
			AddItem("/10", Option::DIV_TEN);
		}

	public:
		virtual void ClickEvent(int option)
		{
			switch (option)
			{
			case Option::ADD_ONE: *frameCounter += 1;break;
			case Option::ADD_TWO: *frameCounter += 2;break;
			case Option::ADD_TEN: *frameCounter += 10;break;
			case Option::SUB_ONE: *frameCounter -= 1;break;
			case Option::SUB_TWO: *frameCounter -= 2;break;
			case Option::SUB_TEN: *frameCounter -= 10;break;
			case Option::MUL_ONE: *frameCounter *= 1;break;
			case Option::MUL_TWO: *frameCounter *= 2;break;
			case Option::MUL_TEN: *frameCounter *= 10;break;
			case Option::DIV_ONE: *frameCounter /= 1;break;
			case Option::DIV_TWO: *frameCounter /= 2;break;
			case Option::DIV_TEN: *frameCounter /= 10;break;
			}
		}

	protected:
		unsigned int* frameCounter;
	};

	//
	template<int key>
	class FrameCounterMenu : public Menu<key>
	{
	public:
		enum Option : int
		{
			RESET = 1
		};

	public:
		FrameCounterMenu(unsigned int* frameCounter) :
			Menu(),
			frameCounter(frameCounter)
		{
			AddItem("Reset Frame Counter", Option::RESET);
		}

	public:
		virtual void ClickEvent(int option)
		{
			switch (option)
			{
			case Option::RESET: *frameCounter = 0;break;
			}
		}

	protected:
		unsigned int* frameCounter;
	};
};