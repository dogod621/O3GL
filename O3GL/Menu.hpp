#pragma once

// std
#include <vector>

// O3GL
#include "O3GL/Utils.hpp"

// 
namespace O3GL
{
	//
	template<int key>
	class Menu;

	template<int key>
	class _Menu : public GLUTObject
	{
	public:
		_Menu() :
			GLUTObject(InitAndCreateMenu(), glutDestroyMenu)
		{
			instance = this;
		}

		~_Menu()
		{
			instance = nullptr;
		}

	public:
		void AddItem(const std::string& name, int value)
		{
			glutSetMenu(*this);
			glutAddMenuEntry(name.c_str(), value);
		}

		void AddMenu(const std::string& name, int menu)
		{
			glutSetMenu(*this);
			glutAddSubMenu(name.c_str(), menu);
		}

		void SetItem(int entry, const std::string& name, int value)
		{
			glutSetMenu(*this);
			glutChangeToMenuEntry(entry, entry[i].c_str(), value);
		}

		void SetMenu(int entry, const std::string& name, int menu)
		{
			glutSetMenu(*this);
			glutChangeToSubMenu(entry, entry[i].c_str(), menu);
		}

		void RemoveItem(int entry)
		{
			glutSetMenu(*this);
			glutRemoveMenuItem(entry);
		}

		void Attach(int window, int button)
		{
			glutSetMenu(*this);
			glutSetWindow(window);
			glutAttachMenu(button);
		}

		void Detach(int window, int button)
		{
			glutSetMenu(*this);
			glutSetWindow(window);
			glutAttachMenu(button);
		}

	public:
		virtual void ClickEvent(int option)
		{
		}

	protected:
		static int InitAndCreateMenu()
		{
			if (instance)
			{
				THROW_EXCEPTION("Menu key is already uesd");
			}
			else
			{
				return glutCreateMenu(ClickCallback);
			}
		}

		static void ClickCallback(int option)
		{
			if (instance)
			{
				instance->ClickEvent(option);
			}
		}

	protected:
		static _Menu* instance;
	};

	//
	template<int key>
	class Menu : public GLUTHandle<_Menu<key>>
	{
	public:
		Menu() : GLUTHandle<_Menu<key>>(new _Menu<key>()) {}
	};
};

namespace O3GL
{
	template<int key>
	_Menu<key>* _Menu<key>::instance = nullptr;
};