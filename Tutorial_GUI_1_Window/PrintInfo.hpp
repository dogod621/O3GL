// O3GL
#include "O3GL/Utils.hpp"
#include "O3GL/Window.hpp"

//
namespace O3GL
{
	//
	template<int key>
	class _PrintInfo : public _Window<key>
	{
	public:
		_PrintInfo(int x, int y, int width, int height) :
			_Window<key>("PrintInfo", GLUT_DOUBLE | GLUT_RGBA, x, y, width, height, 33), frameCounter(0)
		{}

	public:
		virtual void InitGLStatusEvent() const;

	public:
		virtual void DisplayEvent();
		virtual void TimerEvent(int value);

	protected:
		unsigned int frameCounter;
	};

	template<int key>
	class PrintInfo : public GLUTHandle<_PrintInfo<key>>
	{
	public:
		PrintInfo(int x, int y, int width, int height) : GLUTHandle<_PrintInfo<key>>(new _PrintInfo<key>(x, y, width, height)) {}
	};
};

namespace O3GL
{
	//
	template<int key>
	void _PrintInfo<key>::InitGLStatusEvent() const
	{
		glClearColor(1.0, 1.0, 1.0, 0.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	}

	template<int key>
	void _PrintInfo<key>::DisplayEvent()
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

	template<int key>
	void _PrintInfo<key>::TimerEvent(int value)
	{
		frameCounter++;

		glutPostRedisplay();
	}
};