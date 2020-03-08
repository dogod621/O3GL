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
		QuadRender() :
			viewing(glm::lookAt(Vec3(0.f, 0.f, 0.f), Vec3(0.f, 0.f, -1.f), Vec3(0.f, 1.f, 0.f))),
			modelling(glm::translate(glm::identity<Mat44>(), Vec3(0.f, 0.f, -2.f))),
			projection(glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 100.0f))
		{}

		Mat44 Viewing() const { return viewing; }
		Mat44 Modelling() const { return modelling; }
		Mat44 Projection() const { return projection; }

		void SetViewing(const Mat44& m) { viewing = m; InitProgramParametersEvent(); }
		void SetModelling(const Mat44& m) { modelling = m; InitProgramParametersEvent(); }
		void SetProjection(const Mat44& m) { projection = m; InitProgramParametersEvent(); }

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
		virtual void ReshapeEvent(int width, int height)
		{
			quadRender.SetProjection(glm::perspective(glm::radians(60.0f), (float)(width) / (float)(height), 0.1f, 100.0f));
		}

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

		Text(wx, wy, 0.0f, "Time elapsed: " + std::to_string(timeElapsed) + " ms", 1.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;
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