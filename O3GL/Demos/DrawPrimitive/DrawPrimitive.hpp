#pragma once

// O3GL
#include "O3GL/Core/Render.hpp"
#include "O3GL/Core/Window.hpp"
#include "O3GL/Core/Menu.hpp"

//
namespace O3GL
{
	// Simply Draw a Quad
	class QuadRender : public Render
	{
	public:
		enum Mode : GLuint
		{
			TEXTURE = 0,
			NORMAL = 1,
			POSITION = 2,
			UV = 3,
			NONE = 4
		};

	protected:
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

	protected:
		virtual void PreDrawEvent() const;
		virtual void OnDrawEvent() const;
		virtual void PostDrawEvent() const;

	protected:
		virtual void ReshapeEvent(const Reshape::Message& m);
		virtual void SpecialEvent(const Special::Message& m);
		virtual void TimerEvent(const Timer::Message& m);

	public:
		QuadRender();

		Mat44 GetViewing() const { return viewing; }
		Mat44 GetModelling() const { return modelling; }
		Mat44 GetProjection() const { return projection; }
		Mode GetMode() const { return mode; }

		void SetViewing(const Mat44& m) { viewing = m; InitProgramParametersEvent(); }
		void SetModelling(const Mat44& m) { modelling = m; InitProgramParametersEvent(); }
		void SetProjection(const Mat44& m) { projection = m; InitProgramParametersEvent(); }
		void SetMode(Mode m) { mode = m; InitProgramParametersEvent(); }

	protected:
		Mat44 viewing;
		Mat44 modelling;
		Mat44 projection;
		Mode mode;
		double t;
	};

	template<int key>
	class DrawPrimitiveWindow : public Window<key>
	{
	public:
		DrawPrimitiveWindow(const std::string& name, int x, int y, int width, int height, unsigned int tick = 10) :
			Window<key>(name, GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH, x, y, width, height, tick)
		{
			renders["quad"] = PTR<Render>(new QuadRender());
		}

		DrawPrimitiveWindow(int window, int x, int y, int width, int height, unsigned int tick = 10) :
			Window<key>(window, x, y, width, height, tick)
		{
			renders["quad"] = PTR<Render>(new QuadRender());
		}

	protected:
		virtual void InitGLStatusEvent() const;

	public:
		virtual void DisplayEvent(const Display::Message& m);
		virtual void TimerEvent(const Timer::Message& m);
	};

	//
	template<int key>
	void DrawPrimitiveWindow<key>::InitGLStatusEvent() const
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);

		glDepthFunc(GL_LEQUAL);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glShadeModel(GL_SMOOTH);

		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClearDepth(1.0);
	}

	template<int key>
	void DrawPrimitiveWindow<key>::DisplayEvent(const Display::Message& m)
	{
		// Draw
		double costTime = renders["quad"]->Draw();

		float lineHeight = 0.06f;
		float wx = -1.0f;
		float wy = -1.0f;

		Text(wx, wy, 0.0f, "Tick elapsed: " + std::to_string(tickElapsed) + " ms", 1.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;
		Text(wx, wy, 0.0f, "Draw cost: " + std::to_string(costTime) + " ms", 0.0f, 1.0f, 0.0f, 1.0f);

		// Swap buffers
		glutSwapBuffers();
	}

	template<int key>
	void DrawPrimitiveWindow<key>::TimerEvent(const Timer::Message& m)
	{
		glutPostRedisplay();
	}
};