#pragma once

// O3GL
#include "O3GL/Render.hpp"

// 
namespace O3GL
{
	//
	class CanvasRender : public Render
	{
	public:
		virtual std::string Name() const { return "CanvasRender"; }

	protected:
		const GLint canvasWidth;
		const GLint canvasHeight;
		const bool windowMode;

	public:
		virtual void InitSetupEvent();
		virtual void InitSamplersEvent();
		virtual void InitBuffersEvent();
		virtual void InitVertexArraysEvent();
		virtual void InitVertexShaderHeadersEvent();
		virtual void InitVertexShaderMainsEvent();
		virtual void InitFragmentShaderHeadersEvent();
		virtual void InitFragmentShaderMainsEvent();
		virtual void InitShadersEvent();
		virtual void InitProgramsEvent();
		virtual void InitProgramParametersEvent() const;

		virtual void PreDrawEvent() const;
		virtual void OnDrawEvent() const;
		virtual void PostDrawEvent() const;
		virtual void LaunchEvent() const;

	public:
		virtual void DrawInfo(float& wx, float& wy, float lineHeight = 0.06f) const;

		virtual GLint CanvasWidth() const;
		virtual GLint CanvasHeight() const;

	public:
		CanvasRender() :
			Render(),
			canvasWidth(0), canvasHeight(0),
			windowMode(true)
		{}

		CanvasRender(
			GLint canvasWidth, GLint canvasHeight) :
			Render(),
			canvasWidth(canvasWidth), canvasHeight(canvasHeight),
			windowMode(false)
		{}
	};
};