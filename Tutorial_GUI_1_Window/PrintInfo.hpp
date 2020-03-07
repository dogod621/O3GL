#pragma once

// O3GL
#include "O3GL/Utils.hpp"
#include "O3GL/Window.hpp"

//
namespace O3GL
{
	// Simply Print FrameCounter
	template<int key>
	class _PrintFrameCounter : public _Window<key>
	{
	public:
		_PrintFrameCounter(const std::string& name, int x, int y, int width, int height) :
			_Window<key>(name, GLUT_DOUBLE | GLUT_RGBA, x, y, width, height, 33), frameCounter(0)
		{}

		_PrintFrameCounter(int window, int x, int y, int width, int height) :
			_Window<key>(window, x, y, width, height, 33), frameCounter(0)
		{}

	public:
		virtual void InitGLStatusEvent() const;

	public:
		virtual void DisplayEvent();
		virtual void TimerEvent(int value);

	public:
		unsigned int frameCounter;
	};

	template<int key>
	class PrintFrameCounter : public GLUTHandle<_PrintFrameCounter<key>>
	{
	public:
		PrintFrameCounter(const std::string& name, int x, int y, int width, int height) :
			GLUTHandle<_PrintFrameCounter<key>>(new _PrintFrameCounter<key>(name, x, y, width, height)) {}

		PrintFrameCounter(int window, int x, int y, int width, int height) :
			GLUTHandle<_PrintFrameCounter<key>>(new _PrintFrameCounter<key>(window, x, y, width, height)) {}
	};

	// Simply Print OpenGL Version
	template<int key>
	class _PrintGLVersion : public _PrintFrameCounter<key>
	{
	public:
		_PrintGLVersion(const std::string& name, int x, int y, int width, int height) :
			_PrintFrameCounter<key>(name, x, y, width, height)
		{}

		_PrintGLVersion(int window, int x, int y, int width, int height) :
			_PrintFrameCounter<key>(window, x, y, width, height)
		{}

	public:
		virtual void DisplayEvent();
	};

	template<int key>
	class PrintGLVersion : public GLUTHandle<_PrintGLVersion<key>>
	{
	public:
		PrintGLVersion(const std::string& name, int x, int y, int width, int height) :
			GLUTHandle<_PrintGLVersion<key>>(new _PrintGLVersion<key>(name, x, y, width, height)) {}

		PrintGLVersion(int window, int x, int y, int width, int height) :
			GLUTHandle<_PrintGLVersion<key>>(new _PrintGLVersion<key>(window, x, y, width, height)) {}
	};
};

namespace O3GL
{
	//
	template<int key>
	void _PrintFrameCounter<key>::InitGLStatusEvent() const
	{
		glClearColor(1.0, 1.0, 1.0, 0.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	}

	template<int key>
	void _PrintFrameCounter<key>::DisplayEvent()
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
	void _PrintFrameCounter<key>::TimerEvent(int value)
	{
		frameCounter++;
		glutPostRedisplay();
	}

	//
	template<int key>
	void _PrintGLVersion<key>::DisplayEvent()
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