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
	class ModeMenu : public Menu<key>
	{
	public:
		ModeMenu(PTR<QuadRender> quadRender) :
			Menu(),
			quadRender(quadRender)
		{
			AddItem("Display Texture", (int)QuadRender::Mode::TEXTURE);
			AddItem("Display Normal", (int)QuadRender::Mode::NORMAL);
			AddItem("Display Position", (int)QuadRender::Mode::POSITION);
			AddItem("Display UV", (int)QuadRender::Mode::UV);
		}

	public:
		virtual void ClickEvent(int option)
		{
			quadRender->SetMode(QuadRender::Mode(option));
		}

	protected:
		PTR<QuadRender> quadRender;;
	};

	template<int key>
	class DrawPrimitiveWindow : public Window<key>
	{
	public:
		DrawPrimitiveWindow(PTR<QuadRender> quadRender, const std::string& name, int x, int y, int width, int height, unsigned int tick = 10) :
			Window<key>(name, GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH, x, y, width, height, tick), quadRender(quadRender), t(0.0)
		{
		}

		DrawPrimitiveWindow(PTR<QuadRender> quadRender, int window, int x, int y, int width, int height, unsigned int tick = 10) :
			Window<key>(window, x, y, width, height, tick), quadRender(quadRender), t(0.0)
		{
		}

	public:
		virtual void InitGLStatusEvent() const;

	public:
		virtual void DisplayEvent();
		virtual void ReshapeEvent(int width, int height);
		virtual void TimerEvent(int value);

	protected:
		PTR<QuadRender> quadRender;
		double t;
	};

	//
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
		double costTime = quadRender->Draw();

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
		quadRender->SetProjection(glm::perspective(glm::radians(60.0f), (float)(width) / (float)(height), 0.1f, 100.0f));
	}

	template<int key>
	void DrawPrimitiveWindow<key>::TimerEvent(int value)
	{
		t += timeElapsed;
		float angle = (float)(t / 600.0);
		quadRender->SetModelling(glm::rotate(glm::translate(glm::identity<Mat44>(), Vec3(std::sin(angle), std::cos(angle), -4.f)), angle, glm::vec3(1.0, 0.0, 0.0)));

		glutPostRedisplay();
	}
};