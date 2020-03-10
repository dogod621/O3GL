// O3GL
#include "O3GL/Renders/DispalyRender.hpp"

// 
namespace O3GL
{
	//
	void DisplayRender::InitFragmentShaderHeadersEvent()
	{
		CanvasRender::InitFragmentShaderHeadersEvent();

		//
		if (enableLayer)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform int u_dispalyLayer;
				)");
		}
	}

	void DisplayRender::InitProgramParametersEvent() const
	{
		CanvasRender::InitProgramParametersEvent();

		//
		if (enableLayer)
		{
			programs.at("canvas")->Uniform<GLint, 1>("u_dispalyLayer", dispalyLayer);
		}
	}

	void DisplayRender::KeyboardEvent(const Keyboard::Message& m)
	{
		bool r = false;

		switch (m.key)
		{
		case 'N':
		case 'n':
			if (enableLayer)
			{
				SetDispalyLayer((dispalyLayer + 1) % numLayer);
				InitProgramParametersEvent();
				r = true;
			}
			break;
		}

		//
		CanvasRender::KeyboardEvent(m);
	}

	//
	void TextureDisplayRender::SetupEvent()
	{
		DisplayRender::SetupEvent();

		//
		switch (mode)
		{
		case Mode::COLOR:
			break;
		case Mode::INTENSITY:
			break;
		case Mode::DISTANCE:
			switch (channel)
			{
			case Channel::ALPHA:
				THROW_EXCEPTION("Alpha channel can not be displayed as distance");
				break;
			case Channel::RGB:
				THROW_EXCEPTION("RGB channel can not be displayed as distance");
				break;
			case Channel::RGBA:
				THROW_EXCEPTION("RGBA channel can not be displayed as distance");
				break;
			}
			break;
		case Mode::VECTOR:
			switch (channel)
			{
			case Channel::RGB:
				break;
			default:
				THROW_EXCEPTION("Only RGB channel can be displayed as vector");
				break;
			}
			break;
		default:
			THROW_EXCEPTION("mode is not supported");
			break;
		}

		switch (colorTexture->Target())
		{
		case GL_TEXTURE_2D:
		case GL_TEXTURE_2D_ARRAY:
			colorSampler = samplers["plane_trilinear"];
			break;

		case GL_TEXTURE_CUBE_MAP:
		case GL_TEXTURE_CUBE_MAP_ARRAY:
			colorSampler = samplers["cube_trilinear"];
			break;

		default:
			THROW_EXCEPTION("colorTexture->Target(): " + std::to_string(colorTexture->Target()) + " is not supported");
			break;
		}

		switch (colorTexture->Target())
		{
		case GL_TEXTURE_2D_ARRAY:
			SetEnableLayer(true);
			SetNumLayer(colorTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH));
			break;

		case GL_TEXTURE_CUBE_MAP_ARRAY:
			SetEnableLayer(true);
			SetNumLayer(colorTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) / 6);
			break;
		}
	}

	void TextureDisplayRender::InitFragmentShaderHeadersEvent()
	{
		DisplayRender::InitFragmentShaderHeadersEvent();

		//
		switch (colorTexture->Target())
		{
		case GL_TEXTURE_2D:
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2D u_color;
				)");
			break;

		case GL_TEXTURE_2D_ARRAY:
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_color;
				)");
			break;

		case GL_TEXTURE_CUBE_MAP:
			shaderSources["canvas_frag"]->push_back(R"(
uniform samplerCube u_color;
				)");
			break;

		case GL_TEXTURE_CUBE_MAP_ARRAY:
			shaderSources["canvas_frag"]->push_back(R"(
uniform samplerCubeArray u_color;
				)");
			break;

		default:
			THROW_EXCEPTION("colorTexture->Target(): " + std::to_string(colorTexture->Target()) + " is not supported");
			break;
		}

		switch (mode)
		{
		case Mode::COLOR:
			switch (channel)
			{
			case Channel::RED:
				TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RED__mode_COLOR();
				break;
			case Channel::GREEN:
				TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_GREEN__mode_COLOR();
				break;
			case Channel::BLUE:
				TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_BLUE__mode_COLOR();
				break;
			case Channel::ALPHA:
				TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_ALPHA__mode_COLOR();
				break;
			case Channel::RGB:
				TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RGB__mode_COLOR();
				break;
			case Channel::RGBA:
				TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RGBA__mode_COLOR();
				break;
			}
			break;

		case Mode::INTENSITY:
			switch (channel)
			{
			case Channel::RED:
				TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RED__mode_INTENSITY();
				break;
			case Channel::GREEN:
				TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_GREEN__mode_INTENSITY();
				break;
			case Channel::BLUE:
				TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_BLUE__mode_INTENSITY();
				break;
			case Channel::ALPHA:
				TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_ALPHA__mode_INTENSITY();
				break;
			case Channel::RGB:
				TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RGB__mode_INTENSITY();
				break;
			case Channel::RGBA:
				TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RGBA__mode_INTENSITY();
				break;
			}
			break;
		case Mode::DISTANCE:
			switch (channel)
			{
			case Channel::RED:
				TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RED__mode_DISTANCE();
				break;
			case Channel::GREEN:
				TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_GREEN__mode_DISTANCE();
				break;
			case Channel::BLUE:
				TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_BLUE__mode_DISTANCE();
				break;
			}
			break;
		case Mode::VECTOR:
			switch (channel)
			{
			case Channel::RGB:
				TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RGB__mode_VECTOR();
				break;
			}
			break;
		default:
			THROW_EXCEPTION("mode is not supported");
			break;
		}
	}

	void TextureDisplayRender::InitFragmentShaderMainsEvent()
	{
		//
		switch (colorTexture->Target())
		{
		case GL_TEXTURE_2D:
			shaderSources["canvas_frag"]->push_back(R"(
void main(void)
{
	vec2 uv = gl_FragCoord.xy / vec2(u_canvasWidth, u_canvasHeight);
	gl_FragColor = Output(texture(u_color, uv));
}
				)");
			break;

		case GL_TEXTURE_2D_ARRAY:
			shaderSources["canvas_frag"]->push_back(R"(
void main(void)
{
	vec3 uvi = vec3(gl_FragCoord.xy / vec2(u_canvasWidth, u_canvasHeight), u_dispalyLayer);
	gl_FragColor = Output(texture(u_color, uvi));
}
				)");
			break;

		case GL_TEXTURE_CUBE_MAP:
			shaderSources["canvas_frag"]->push_back(R"(
void main(void)
{
	vec2 uv = gl_FragCoord.xy / vec2(u_canvasWidth, u_canvasHeight);
	vec3 view = EquirectangularUV_To_Dir(uv);
	gl_FragColor = Output(texture(u_color, view));
}
				)");
			break;

		case GL_TEXTURE_CUBE_MAP_ARRAY:
			shaderSources["canvas_frag"]->push_back(R"(
void main(void)
{
	vec2 uv = gl_FragCoord.xy / vec2(u_canvasWidth, u_canvasHeight);
	vec4 viewi = vec4(EquirectangularUV_To_Dir(uv), u_dispalyLayer);
	gl_FragColor = Output(texture(u_color, viewi));
}
				)");
			break;

		default:
			THROW_EXCEPTION("colorTexture->Target(): " + std::to_string(colorTexture->Target()) + " is not supported");
			break;
		}
	}

	void TextureDisplayRender::PreDrawEvent() const
	{
		DisplayRender::PreDrawEvent();

		//
		colorTexture->Begin(*colorSampler);
		programs.at("canvas")->Uniform<GLint, 1>("u_color", (GLint)colorTexture->Unit());
	}

	void TextureDisplayRender::PostDrawEvent() const
	{
		colorTexture->End();

		//
		DisplayRender::PostDrawEvent();
	}

	void TextureDisplayRender::TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RED__mode_COLOR()
	{
		shaderSources["canvas_frag"]->push_back(R"(
vec4 Output(vec4 rgba)
{
	return vec4(rgba.r, 0.0f, 0.0f, 1.0f);
}
			)");
	}
	void TextureDisplayRender::TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_GREEN__mode_COLOR()
	{
		shaderSources["canvas_frag"]->push_back(R"(
vec4 Output(vec4 rgba)
{
	return vec4(0.0f, rgba.g, 0.0f, 1.0f);
}
			)");
	}
	void TextureDisplayRender::TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_BLUE__mode_COLOR()
	{
		shaderSources["canvas_frag"]->push_back(R"(
vec4 Output(vec4 rgba)
{
	return vec4(0.0f, 0.0f, rgba.b, 1.0f);
}
			)");
	}
	void TextureDisplayRender::TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_ALPHA__mode_COLOR()
	{
		shaderSources["canvas_frag"]->push_back(R"(
vec4 Output(vec4 rgba)
{
	return vec4(0.0f, 0.0f, 0.0f, rgba.a);
}
			)");
	}
	void TextureDisplayRender::TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RGB__mode_COLOR()
	{
		shaderSources["canvas_frag"]->push_back(R"(
vec4 Output(vec4 rgba)
{
	return vec4(rgba.rgb, 1.0f);
}
			)");
	}
	void TextureDisplayRender::TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RGBA__mode_COLOR()
	{
		shaderSources["canvas_frag"]->push_back(R"(
vec4 Output(vec4 rgba)
{
	return rgba;
}
			)");
	}

	void TextureDisplayRender::TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RED__mode_INTENSITY()
	{
		shaderSources["canvas_frag"]->push_back(R"(
vec4 Output(vec4 rgba)
{
	return vec4(vec3(rgba.r), 1.0f);
}
			)");
	}
	void TextureDisplayRender::TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_GREEN__mode_INTENSITY()
	{
		shaderSources["canvas_frag"]->push_back(R"(
vec4 Output(vec4 rgba)
{
	return vec4(vec3(rgba.g), 1.0f);
}
			)");
	}
	void TextureDisplayRender::TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_BLUE__mode_INTENSITY()
	{
		shaderSources["canvas_frag"]->push_back(R"(
vec4 Output(vec4 rgba)
{
	return vec4(vec3(rgba.b), 1.0f);
}
			)");
	}
	void TextureDisplayRender::TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_ALPHA__mode_INTENSITY()
	{
		shaderSources["canvas_frag"]->push_back(R"(
vec4 Output(vec4 rgba)
{
	return vec4(vec3(rgba.a), 1.0f);
}
			)");
	}
	void TextureDisplayRender::TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RGB__mode_INTENSITY()
	{
		shaderSources["canvas_frag"]->push_back(R"(
vec4 Output(vec4 rgba)
{
	return vec4(vec3(dot(rgba.rgb, vec3(0.299f, 0.587f, 0.114f))), 1.0f);
}
			)");
	}
	void TextureDisplayRender::TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RGBA__mode_INTENSITY()
	{
		TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RGB__mode_INTENSITY();
	}

	void TextureDisplayRender::TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RED__mode_DISTANCE()
	{
		shaderSources["canvas_frag"]->push_back(R"(
vec4 Output(vec4 rgba)
{
	int d = int(abs(rgba.r) * 1000.0f);
	return vec4(
		float((d / (256 * 256)) % 256) / 255.f, 
		float((d / 256) % 256) / 255.f,
		float((d) % 256) / 255.f,
		1.0f);
}
			)");
	}
	void TextureDisplayRender::TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_GREEN__mode_DISTANCE()
	{
		shaderSources["canvas_frag"]->push_back(R"(
vec4 Output(vec4 rgba)
{
	int d = int(abs(rgba.g) * 1000.0f);
	return vec4(
		float((d / (256 * 256)) % 256) / 255.f, 
		float((d / 256) % 256) / 255.f,
		float((d) % 256) / 255.f,
		1.0f);
}
			)");
	}
	void TextureDisplayRender::TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_BLUE__mode_DISTANCE()
	{
		shaderSources["canvas_frag"]->push_back(R"(
vec4 Output(vec4 rgba)
{
	int d = int(abs(rgba.b) * 1000.0f);
	return vec4(
		float((d / (256 * 256)) % 256) / 255.f, 
		float((d / 256) % 256) / 255.f,
		float((d) % 256) / 255.f,
		1.0f);
}
			)");
	}

	void TextureDisplayRender::TextureDisplayRender_InitFragmentShaderHeadersEvent__channel_RGB__mode_VECTOR()
	{
		shaderSources["canvas_frag"]->push_back(R"(
vec4 Output(vec4 rgba)
{
	return vec4((normalize(rgba.xyz) + 1.0f) * 0.5f, 1.0f);
}
			)");
	}

	//
	void AnaglyphDisplayRender::SetupEvent()
	{
		DisplayRender::SetupEvent();

		//
		if (leftColorTexture->Target() != rightColorTexture->Target())
		{
			THROW_EXCEPTION("leftColorTexture->Target(): " + std::to_string(leftColorTexture->Target()) + " is not as same  as rightColorTexture->Target() : " + std::to_string(rightColorTexture->Target()));
		}

		switch (leftColorTexture->Target())
		{
		case GL_TEXTURE_2D:
		case GL_TEXTURE_2D_ARRAY:
			leftColorSampler = samplers["plane_trilinear"];
			rightColorSampler = samplers["plane_trilinear"];
			break;

		case GL_TEXTURE_CUBE_MAP:
		case GL_TEXTURE_CUBE_MAP_ARRAY:
			leftColorSampler = samplers["cube_trilinear"];
			rightColorSampler = samplers["cube_trilinear"];
			break;

		default:
			THROW_EXCEPTION("leftColorTexture->Target(): " + std::to_string(leftColorTexture->Target()) + " is not supported");
			break;
		}

		switch (leftColorTexture->Target())
		{
		case GL_TEXTURE_2D_ARRAY:
			SetEnableLayer(true);
			SetNumLayer(leftColorTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH));
			break;

		case GL_TEXTURE_CUBE_MAP_ARRAY:
			SetEnableLayer(true);
			SetNumLayer(leftColorTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) / 6);
			break;
		}
	}

	void AnaglyphDisplayRender::InitFragmentShaderHeadersEvent()
	{
		DisplayRender::InitFragmentShaderHeadersEvent();

		//
		switch (leftColorTexture->Target())
		{
		case GL_TEXTURE_2D:
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2D u_leftColor;
uniform sampler2D u_rightColor;
				)");
			break;

		case GL_TEXTURE_2D_ARRAY:
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_leftColor;
uniform sampler2DArray u_rightColor;
				)");
			break;

		case GL_TEXTURE_CUBE_MAP:
			shaderSources["canvas_frag"]->push_back(R"(
uniform samplerCube u_leftColor;
uniform samplerCube u_rightColor;
				)");
			break;

		case GL_TEXTURE_CUBE_MAP_ARRAY:
			shaderSources["canvas_frag"]->push_back(R"(
uniform samplerCubeArray u_leftColor;
uniform samplerCubeArray u_rightColor;
				)");
			break;

		default:
			THROW_EXCEPTION("leftColorTexture->Target(): " + std::to_string(leftColorTexture->Target()) + " is not supported");
			break;
		}
	}

	void AnaglyphDisplayRender::InitFragmentShaderMainsEvent()
	{
		switch (leftColorTexture->Target())
		{
		case GL_TEXTURE_2D:
			shaderSources["canvas_frag"]->push_back(R"(
void main(void)
{
	vec2 uv = gl_FragCoord.xy / vec2(u_canvasWidth, u_canvasHeight);
	vec4 left = texture(u_leftColor, uv);
	vec4 right = texture(u_rightColor, uv);
	gl_FragColor = vec4(left.r, right.g, right.b, 1.0f);
}
				)");
			break;

		case GL_TEXTURE_2D_ARRAY:
			shaderSources["canvas_frag"]->push_back(R"(
void main(void)
{
	vec3 uvi = vec3(gl_FragCoord.xy / vec2(u_canvasWidth, u_canvasHeight), u_dispalyLayer);
	vec4 left = texture(u_leftColor, uvi);
	vec4 right = texture(u_rightColor, uvi);
	gl_FragColor = vec4(left.r, right.g, right.b, 1.0f);
}
				)");
			break;

		case GL_TEXTURE_CUBE_MAP:
			shaderSources["canvas_frag"]->push_back(R"(
void main(void)
{
	vec2 uv = gl_FragCoord.xy / vec2(u_canvasWidth, u_canvasHeight);
	vec3 view = EquirectangularUV_To_Dir(uv);
	vec4 left = texture(u_leftColor, view);
	vec4 right = texture(u_rightColor, view);
	gl_FragColor = vec4(left.r, right.g, right.b, 1.0f);
}
				)");
			break;

		case GL_TEXTURE_CUBE_MAP_ARRAY:
			shaderSources["canvas_frag"]->push_back(R"(
void main(void)
{
	vec2 uv = gl_FragCoord.xy / vec2(u_canvasWidth, u_canvasHeight);
	vec4 viewi = vec4(EquirectangularUV_To_Dir(uv), u_dispalyLayer);
	vec4 left = texture(u_leftColor, viewi);
	vec4 right = texture(u_rightColor, viewi);
	gl_FragColor = vec4(left.r, right.g, right.b, 1.0f);
}
				)");
			break;

		default:
			THROW_EXCEPTION("leftColorTexture->Target(): " + std::to_string(leftColorTexture->Target()) + " is not supported");
			break;
		}
	}

	void AnaglyphDisplayRender::PreDrawEvent() const
	{
		DisplayRender::PreDrawEvent();

		//
		leftColorTexture->Begin(*leftColorSampler);
		programs.at("canvas")->Uniform<GLint, 1>("u_leftColor", (GLint)leftColorTexture->Unit());

		rightColorTexture->Begin(*rightColorSampler);
		programs.at("canvas")->Uniform<GLint, 1>("u_rightColor", (GLint)rightColorTexture->Unit());
	}

	void AnaglyphDisplayRender::PostDrawEvent() const
	{
		rightColorTexture->End();
		leftColorTexture->End();

		//
		DisplayRender::PostDrawEvent();
	}
};