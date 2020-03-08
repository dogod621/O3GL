#pragma once

// std
#include <vector>

// O3GL
#include "O3GL/Utils.hpp"
#include "O3GL/Window.hpp"

// 
namespace O3GL
{
	//
	class MenuBase
	{
	public:
		MenuBase() {}

	public:
		virtual void ClickEvent(int option) {}
	};

	template<int key>
	class Menu : public GLUTHandle, public MenuBase
	{
	public:
		Menu();
		~Menu();

	public:
		void AddItem(const std::string& name, int value);
		void AddMenu(const std::string& name, int menu);
		void SetItem(int entry, const std::string& name, int value);
		void SetMenu(int entry, const std::string& name, int menu);
		void RemoveItem(int entry);
		void Attach(int window, int button);
		void Detach(int window, int button);

	protected:
		static int InitAndCreateMenu();
		static void ClickCallback(int option);

	protected:
		static Menu* instance;
	};

	//
	template<int key>
	Menu<key>* Menu<key>::instance = nullptr;

	template<int key>
	Menu<key>::Menu() :
		GLUTHandle(new GLUTObject(InitAndCreateMenu(), glutDestroyMenu)),
		MenuBase()
	{
		instance = this;
	}

	template<int key>
	Menu<key>::~Menu()
	{
		instance = nullptr;
	}

	template<int key>
	void Menu<key>::AddItem(const std::string& name, int value)
	{
		glutSetMenu(*this);
		glutAddMenuEntry(name.c_str(), value);
	}

	template<int key>
	void Menu<key>::AddMenu(const std::string& name, int menu)
	{
		glutSetMenu(*this);
		glutAddSubMenu(name.c_str(), menu);
	}

	template<int key>
	void Menu<key>::SetItem(int entry, const std::string& name, int value)
	{
		glutSetMenu(*this);
		glutChangeToMenuEntry(entry, entry[i].c_str(), value);
	}

	template<int key>
	void Menu<key>::SetMenu(int entry, const std::string& name, int menu)
	{
		glutSetMenu(*this);
		glutChangeToSubMenu(entry, entry[i].c_str(), menu);
	}

	template<int key>
	void Menu<key>::RemoveItem(int entry)
	{
		glutSetMenu(*this);
		glutRemoveMenuItem(entry);
	}

	template<int key>
	void Menu<key>::Attach(int window, int button)
	{
		glutSetMenu(*this);
		glutSetWindow(window);
		glutAttachMenu(button);
	}

	template<int key>
	void Menu<key>::Detach(int window, int button)
	{
		glutSetMenu(*this);
		glutSetWindow(window);
		glutAttachMenu(button);
	}

	template<int key>
	int Menu<key>::InitAndCreateMenu()
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

	template<int key>
	void Menu<key>::ClickCallback(int option)
	{
		if (instance)
		{
			instance->ClickEvent(option);
		}
	}
};