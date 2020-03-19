#pragma once

// O3GL
#include "O3GL/Renders/CanvasRender.hpp"

// 
namespace O3GL
{
	//
	class DisplayRender : public CanvasRender
	{
	protected:
		virtual void InitTexturesEvent();
		virtual void InitFragmentShaderHeadersEvent();
		virtual void InitProgramParametersEvent() const;
		virtual void InitFrameBuffersEvent();

	protected:
		virtual void KeyboardEvent(const Keyboard::Message& m);

	public:
		DisplayRender() :
			CanvasRender(),
			enableLayer(false),
			dispalyLayer(0),
			numLayer(0)
		{}

		DisplayRender(GLint canvasWidth, GLint canvasHeight) :
			CanvasRender(canvasWidth, canvasHeight),
			enableLayer(false),
			dispalyLayer(0),
			numLayer(0)
		{
			textures["canvas"] = PTR<Texture>(new Texture(GL_TEXTURE_2D));
		}

	public:
		void SetEnableLayer(bool enableLayer) const
		{
			*((bool*)&this->enableLayer) = enableLayer;
		}

		void SetDispalyLayer(GLint dispalyLayer) const
		{
			*((GLint*)&this->dispalyLayer) = dispalyLayer;
		}

		void SetNumLayer(GLint numLayer) const
		{
			*((GLint*)&this->numLayer) = numLayer;
		}

	protected:
		const bool enableLayer;
		const GLint dispalyLayer; // only for GL_TEXTURE_2D_ARRAY & GL_TEXTURE_CUBE_MAP_ARRAY input
		const GLint numLayer; // only for GL_TEXTURE_2D_ARRAY & GL_TEXTURE_CUBE_MAP_ARRAY input
	};

	//
	class TextureDisplayRender : public DisplayRender
	{
	public:
		enum Channel : GLuint
		{
			RED = 0,
			GREEN = 1,
			BLUE = 2,
			ALPHA = 3,
			RGB = 4,
			RGBA = 5
		};

		enum Mode : GLuint
		{
			COLOR = 0,
			INTENSITY = 1,
			DISTANCE = 2,
			VECTOR = 3
		};

	protected:
		virtual void InitFragmentShaderHeadersEvent();
		virtual void InitFragmentShaderMainsEvent();

		virtual void PreDrawEvent() const;
		virtual void PostDrawEvent() const;

	protected:
		void TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RED__mode_COLOR();
		void TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_GREEN__mode_COLOR();
		void TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_BLUE__mode_COLOR();
		void TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_ALPHA__mode_COLOR();
		void TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RGB__mode_COLOR();
		void TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RGBA__mode_COLOR();

		void TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RED__mode_INTENSITY();
		void TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_GREEN__mode_INTENSITY();
		void TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_BLUE__mode_INTENSITY();
		void TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_ALPHA__mode_INTENSITY();
		void TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RGB__mode_INTENSITY();
		void TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RGBA__mode_INTENSITY();

		void TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RED__mode_DISTANCE();
		void TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_GREEN__mode_DISTANCE();
		void TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_BLUE__mode_DISTANCE();

		void TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RGB__mode_VECTOR();

	public:
		TextureDisplayRender(const CONST_PTR<Texture>& colorTexture, Channel channel, Mode mode) :
			DisplayRender(), colorSampler(), colorTexture(colorTexture), channel(channel), mode(mode)
		{
			Setup();
		}

		TextureDisplayRender(
			GLint canvasWidth, GLint canvasHeight,
			const CONST_PTR<Texture>& colorTexture, Channel channel, Mode mode) :
			DisplayRender(canvasWidth, canvasHeight), colorSampler(), colorTexture(colorTexture), channel(channel), mode(mode)
		{
			Setup();
		}

	protected:
		void Setup();

	protected:
		CONST_PTR<Sampler> colorSampler;
		CONST_PTR<Texture> colorTexture;

		const Channel channel;
		const Mode mode;
	};

	//
	class AnaglyphDisplayRender : public DisplayRender
	{
	protected:
		virtual void InitFragmentShaderHeadersEvent();
		virtual void InitFragmentShaderMainsEvent();

		virtual void PreDrawEvent() const;
		virtual void PostDrawEvent() const;

	public:
		AnaglyphDisplayRender(const CONST_PTR<Texture>& leftColorTexture, const CONST_PTR<Texture>& rightColorTexture) :
			DisplayRender(), leftColorSampler(), rightColorSampler(), leftColorTexture(leftColorTexture), rightColorTexture(rightColorTexture),
			leftOnly(false)
		{
			Setup();
		}

		AnaglyphDisplayRender(
			GLint canvasWidth, GLint canvasHeight,
			const CONST_PTR<Texture>& leftColorTexture, const CONST_PTR<Texture>& rightColorTexture) :
			DisplayRender(canvasWidth, canvasHeight), leftColorSampler(), rightColorSampler(), leftColorTexture(leftColorTexture), rightColorTexture(rightColorTexture),
			leftOnly(false)
		{
			Setup();
		}

		AnaglyphDisplayRender(const CONST_PTR<Texture>& colorTexture) :
			DisplayRender(), leftColorSampler(), rightColorSampler(), leftColorTexture(leftColorTexture), rightColorTexture(),
			leftOnly(true)
		{
			Setup();
		}

		AnaglyphDisplayRender(
			GLint canvasWidth, GLint canvasHeight,
			const CONST_PTR<Texture>& lcolorTexture) :
			DisplayRender(canvasWidth, canvasHeight), leftColorSampler(), rightColorSampler(), leftColorTexture(leftColorTexture), rightColorTexture(),
			leftOnly(true)
		{
			Setup();
		}

	protected:
		void Setup();

	protected:
		const bool leftOnly;
		CONST_PTR<Sampler> leftColorSampler;
		CONST_PTR<Sampler> rightColorSampler;
		CONST_PTR<Texture> leftColorTexture;
		CONST_PTR<Texture> rightColorTexture;
	};
};