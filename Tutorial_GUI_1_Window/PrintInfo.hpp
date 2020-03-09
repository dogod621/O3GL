#pragma once

// O3GL
#include "O3GL/Core/Utils.hpp"
#include "O3GL/Core/Window.hpp"

//
namespace O3GL
{
	// Simply Print FrameCounter
	template<int key>
	class PrintFrameCounterWindow : public Window<key>
	{
	public:
		PrintFrameCounterWindow(const std::string& name, int x, int y, int width, int height, unsigned int tick = 10) :
			Window<key>(name, GLUT_DOUBLE | GLUT_RGBA, x, y, width, height, tick), frameCounter(0)
		{}

		PrintFrameCounterWindow(int window, int x, int y, int width, int height, unsigned int tick = 10) :
			Window<key>(window, x, y, width, height, tick), frameCounter(0)
		{}

	public:
		virtual void InitGLStatusEvent() const;

	public:
		virtual void DisplayEvent(const Display::Message& m);
		virtual void TimerEvent(const Timer::Message& m);

	public:
		unsigned int frameCounter;
	};

	// Simply Print OpenGL Version
	template<int key>
	class PrintGLVersionWindow : public PrintFrameCounterWindow<key>
	{
	public:
		PrintGLVersionWindow(const std::string& name, int x, int y, int width, int height, unsigned int tick) :
			PrintFrameCounterWindow<key>(name, x, y, width, height, tick)
		{}

		PrintGLVersionWindow(int window, int x, int y, int width, int height, unsigned int tick) :
			PrintFrameCounterWindow<key>(window, x, y, width, height, tick)
		{}

	public:
		virtual void DisplayEvent(const Display::Message& m);
	};
};

namespace O3GL
{
	//
	template<int key>
	void PrintFrameCounterWindow<key>::InitGLStatusEvent() const
	{
		glClearColor(1.0, 1.0, 1.0, 0.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	}

	template<int key>
	void PrintFrameCounterWindow<key>::DisplayEvent(const Display::Message& m)
	{
		// Clear backbuffer
		glClear(GL_COLOR_BUFFER_BIT);

		//
		float lineHeight = 0.06f;
		float wx = -1.0f;
		float wy = -1.0f;

		Text(wx, wy, 0.0f, "Tick elapsed: " + std::to_string(tickElapsed) + " ms", 1.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;
		Text(wx, wy, 0.0f, "This is the " + std::to_string(frameCounter) + "-th frame", 1.0f, 0.0f, 0.0f, 1.0f);

		// Swap buffers
		glutSwapBuffers();
	}

	template<int key>
	void PrintFrameCounterWindow<key>::TimerEvent(const Timer::Message& m)
	{
		frameCounter++;
		glutPostRedisplay();
	}

	//
	template<int key>
	void PrintGLVersionWindow<key>::DisplayEvent(const Display::Message& m)
	{
		// Clear backbuffer
		glClear(GL_COLOR_BUFFER_BIT);

		//
		float lineHeight = 0.06f;
		float wx = -1.0f;
		float wy = -1.0f;

		Text(wx, wy, 0.0f, "Tick elapsed: " + std::to_string(tickElapsed) + " ms", 1.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;
		Text(wx, wy, 0.0f, "This is the " + std::to_string(frameCounter) + "-th frame", 1.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;

		Text(wx, wy, 0.0f, "\t\t" + std::string((char*)glGetString(GL_EXTENSIONS)), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;
		Text(wx, wy, 0.0f, "GL_EXTENSIONS: ", 0.0f, 1.0f, 0.0f, 1.0f);
		wy += lineHeight;

		Text(wx, wy, 0.0f, "\t\t" + std::string((char*)glGetString(GL_RENDERER)), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;
		Text(wx, wy, 0.0f, "GL_RENDERER: ", 0.0f, 1.0f, 0.0f, 1.0f);
		wy += lineHeight;

		Text(wx, wy, 0.0f, "\t\t" + std::string((char*)glGetString(GL_VENDOR)), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;
		Text(wx, wy, 0.0f, "GL_VENDOR: ", 0.0f, 1.0f, 0.0f, 1.0f);
		wy += lineHeight;

		Text(wx, wy, 0.0f, "\t\t" + std::string((char*)glGetString(GL_SHADING_LANGUAGE_VERSION)), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;
		Text(wx, wy, 0.0f, "GL_SHADING_LANGUAGE_VERSION: ", 0.0f, 1.0f, 0.0f, 1.0f);
		wy += lineHeight;

		Text(wx, wy, 0.0f, "\t\t" + std::string((char*)glGetString(GL_VERSION)), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;
		Text(wx, wy, 0.0f, "GL_VERSION: ", 0.0f, 1.0f, 0.0f, 1.0f);

		// Swap buffers
		glutSwapBuffers();
	}
};