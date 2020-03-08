#pragma once

// O3GL
#include "O3GL/Render.hpp"
#include "O3GL/Window.hpp"

//
namespace O3GL
{
	// Simply Draw a Quad
	class QuadRender : public Render
	{
	public:
		virtual void SetupEvent();
		virtual void UpdateEvent();

	public:
		virtual void InitSamplersEvent();
		virtual void InitTexturesEvent();
		virtual void InitBuffersEvent();
		virtual void InitVertexShaderHeadersEvent();
		virtual void InitVertexShaderMainsEvent();
		virtual void InitGeometryShaderHeadersEvent();
		virtual void InitGeometryShaderMainsEvent();
		virtual void InitFragmentShaderHeadersEvent();
		virtual void InitFragmentShaderMainsEvent();
		virtual void InitShadersEvent();
		virtual void InitProgramsEvent();
		virtual void InitProgramParametersEvent() const;
		virtual void InitVertexArraysEvent();
		virtual void InitFrameBuffersEvent();

	public:
		virtual void PreDrawEvent() const;
		virtual void OnDrawEvent() const;
		virtual void PostDrawEvent() const;

	public:
		QuadRender() : viewing(), modelling(), projection()
		{}

	protected:
		Mat44 viewing;
		Mat44 modelling;
		Mat44 projection;
	};

	template<int key>
	class DrawPrimitiveWindow : public Window<key>
	{
	public:
		DrawPrimitiveWindow(const std::string& name, int x, int y, int width, int height);
		DrawPrimitiveWindow(int window, int x, int y, int width, int height);

	public:
		virtual void InitGLStatusEvent() const;

	public:
		virtual void DisplayEvent();
		virtual void TimerEvent(int value);

	protected:
		QuadRender quadRender;
	};

	//
	template<int key>
	DrawPrimitiveWindow<key>::DrawPrimitiveWindow(const std::string& name, int x, int y, int width, int height) :
		Window<key>(name, GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH, x, y, width, height, 33), quadRender()
	{
		quadRender.Init();
	}

	template<int key>
	DrawPrimitiveWindow<key>::DrawPrimitiveWindow(int window, int x, int y, int width, int height) :
		Window<key>(window, x, y, width, height, 33), quadRender()
	{
		quadRender.Init();
	}

	template<int key>
	void DrawPrimitiveWindow<key>::InitGLStatusEvent() const
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);

		glDepthFunc(GL_LEQUAL);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glShadeModel(GL_SMOOTH);

		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClearDepth(1.0);
	}

	template<int key>
	void DrawPrimitiveWindow<key>::DisplayEvent()
	{
		// Draw
		double costTime = quadRender.Draw();

		float lineHeight = 0.06f;
		float wx = -1.0f;
		float wy = -1.0f;

		Text(wx, wy, 0.0f, "Draw cost: " + std::to_string(costTime) + " ms", 0.0f, 1.0f, 0.0f, 1.0f);

		// Swap buffers
		glutSwapBuffers();
	}

	template<int key>
	void DrawPrimitiveWindow<key>::TimerEvent(int value)
	{
		glutPostRedisplay();
	}
};