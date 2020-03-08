#pragma once

// O3GL
#include "O3GL/Core/Render.hpp"
#include "O3GL/Core/Window.hpp"

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
			modelling(glm::translate(glm::identity<Mat44>(), Vec3(0.f, 0.f, -4.f))),
			projection(glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 100.0f)),
			mode(Mode::TEXTURE)
		{}

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
		virtual void ReshapeEvent(int width, int height);
		virtual void KeyboardEvent(unsigned char key, int x, int y);
		virtual void TimerEvent(int value);

	protected:
		QuadRender quadRender;
		double t;
	};

	//
	template<int key>
	DrawPrimitiveWindow<key>::DrawPrimitiveWindow(const std::string& name, int x, int y, int width, int height) :
		Window<key>(name, GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH, x, y, width, height, 33), quadRender(), t(0.0)
	{
		quadRender.Init();
		quadRender.PrintShaderSources("unlit_vert");
		quadRender.PrintShaderSources("unlit_frag");
	}

	template<int key>
	DrawPrimitiveWindow<key>::DrawPrimitiveWindow(int window, int x, int y, int width, int height) :
		Window<key>(window, x, y, width, height, 33), quadRender(), t(0.0)
	{
		quadRender.Init();
		quadRender.PrintShaderSources("unlit_vert");
		quadRender.PrintShaderSources("unlit_frag");
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
	void DrawPrimitiveWindow<key>::ReshapeEvent(int width, int height)
	{
		quadRender.SetProjection(glm::perspective(glm::radians(60.0f), (float)(width) / (float)(height), 0.1f, 100.0f));
	}

	template<int key>
	void DrawPrimitiveWindow<key>::KeyboardEvent(unsigned char key, int x, int y)
	{
		switch (key)
		{
		case '1':
			quadRender.SetMode(QuadRender::Mode::TEXTURE);
			break;
		case '2':
			quadRender.SetMode(QuadRender::Mode::NORMAL);
			break;
		case '3':
			quadRender.SetMode(QuadRender::Mode::POSITION);
			break;
		case '4':
			quadRender.SetMode(QuadRender::Mode::UV);
			break;
		default:
			quadRender.SetMode(QuadRender::Mode::NONE);
			break;
		}
	}

	template<int key>
	void DrawPrimitiveWindow<key>::TimerEvent(int value)
	{
		t += timeElapsed;
		float tx = (float)std::sin(t / 600.0);
		float ty = (float)std::cos(t / 600.0);

		quadRender.SetModelling(glm::translate(glm::identity<Mat44>(), Vec3(tx, ty, -4.f)));

		glutPostRedisplay();
	}
};