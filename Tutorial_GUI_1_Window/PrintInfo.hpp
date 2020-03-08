#pragma once

// O3GL
#include "O3GL/Utils.hpp"
#include "O3GL/Window.hpp"

//
namespace O3GL
{
	// Simply Print FrameCounter
	template<int key>
	class PrintFrameCounter : public Window<key>
	{
	public:
		PrintFrameCounter(const std::string& name, int x, int y, int width, int height) :
			Window<key>(name, GLUT_DOUBLE | GLUT_RGBA, x, y, width, height, 33), frameCounter(0)
		{}

		PrintFrameCounter(int window, int x, int y, int width, int height) :
			Window<key>(window, x, y, width, height, 33), frameCounter(0)
		{}

	public:
		virtual void InitGLStatusEvent() const;

	public:
		virtual void DisplayEvent();
		virtual void TimerEvent(int value);

	public:
		unsigned int frameCounter;
	};

	// Simply Print OpenGL Version
	template<int key>
	class PrintGLVersion : public PrintFrameCounter<key>
	{
	public:
		PrintGLVersion(const std::string& name, int x, int y, int width, int height) :
			PrintFrameCounter<key>(name, x, y, width, height)
		{}

		PrintGLVersion(int window, int x, int y, int width, int height) :
			PrintFrameCounter<key>(window, x, y, width, height)
		{}

	public:
		virtual void DisplayEvent();
	};
};

namespace O3GL
{
	//
	template<int key>
	void PrintFrameCounter<key>::InitGLStatusEvent() const
	{
		glClearColor(1.0, 1.0, 1.0, 0.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	}

	template<int key>
	void PrintFrameCounter<key>::DisplayEvent()
	{
		// Clear backbuffer
		glClear(GL_COLOR_BUFFER_BIT);

		//
		float lineHeight = 0.06f;
		float wx = -1.0f;
		float wy = -1.0f;

		Text(wx, wy, 0.0f, "This is the " + std::to_string(frameCounter) + "-th frame", 1.0f, 0.0f, 0.0f, 1.0f);

		// Swap buffers
		glutSwapBuffers();
	}

	template<int key>
	void PrintFrameCounter<key>::TimerEvent(int value)
	{
		frameCounter++;
		glutPostRedisplay();
	}

	//
	template<int key>
	void PrintGLVersion<key>::DisplayEvent()
	{
		// Clear backbuffer
		glClear(GL_COLOR_BUFFER_BIT);

		//
		float lineHeight = 0.06f;
		float wx = -1.0f;
		float wy = -1.0f;

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
		wy += lineHeight;

		Text(wx, wy, 0.0f, "This is the " + std::to_string(frameCounter) + "-th frame", 1.0f, 0.0f, 0.0f, 1.0f);

		// Swap buffers
		glutSwapBuffers();
	}
};