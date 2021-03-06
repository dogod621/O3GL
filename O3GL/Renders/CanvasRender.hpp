#pragma once

// O3GL
#include "O3GL/Core/Render.hpp"

// 
namespace O3GL
{
	//
	class CanvasRender : public Render
	{
	protected:
		virtual void InitSamplersEvent();
		virtual void InitBuffersEvent();
		virtual void InitVertexShaderHeadersEvent();
		virtual void InitVertexShaderMainsEvent();
		virtual void InitFragmentShaderHeadersEvent();
		virtual void InitFragmentShaderMainsEvent();
		virtual void InitShadersEvent();
		virtual void InitProgramsEvent();
		virtual void InitProgramParametersEvent() const;
		virtual void InitVertexArraysEvent();

	protected:
		virtual void PreDrawEvent() const;
		virtual void OnDrawEvent() const;
		virtual void PostDrawEvent() const;

	public:
		CanvasRender() :
			Render(),
			canvasWidth(0), canvasHeight(0),
			windowMode(true)
		{
			Setup();
		}

		CanvasRender(
			GLint canvasWidth, GLint canvasHeight) :
			Render(),
			canvasWidth(canvasWidth), canvasHeight(canvasHeight),
			windowMode(false)
		{
			Setup();
		}

	protected:
		void Setup();

	protected:
		const GLint canvasWidth;
		const GLint canvasHeight;
		const bool windowMode;

	public:
		GLint CanvasWidth() const;
		GLint CanvasHeight() const;
	};
};