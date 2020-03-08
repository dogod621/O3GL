// O3GL
#include "DrawPrimitive.hpp"

//
namespace O3GL
{
	//
	void QuadRender::SetupEvent()
	{
		Render::SetupEvent();

		//
		samplers["bilinear"] = Sampler();
		textures["color"] = Texture();

		buffers["quad_pos"] = Buffer();
		buffers["quad_normal"] = Buffer();
		buffers["quad_uv"] = Buffer();
		buffers["quad_index"] = Buffer();

		vertexArrays["quad"] = VertexArray();

		shaderSources["unlit_vert"] = ShaderSource();
		shaderSources["unlit_geom"] = ShaderSource();
		shaderSources["unlit_frag"] = ShaderSource();

		shaders["unlit_vert"] = Shader(GL_VERTEX_SHADER);
		shaders["unlit_geom"] = Shader(GL_GEOMETRY_SHADER);
		shaders["unlit_frag"] = Shader(GL_FRAGMENT_SHADER);

		programs["unlit"] = Program();
	}

	void QuadRender::InitSamplersEvent()
	{
		Render::InitSamplersEvent();

		//
		samplers["bilinear"].SetInfo<GLint>(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		samplers["bilinear"].SetInfo<GLint>(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		samplers["bilinear"].SetInfo<GLint>(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		samplers["bilinear"].SetInfo<GLint>(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void QuadRender::InitTexturesEvent()
	{
		Render::InitTexturesEvent();

		//
		GLsizei texW = 256u;
		GLsizei texH = 256u;

		std::vector<UI8> texData(texW * texH * 4u);
		GLsizei c = 0u;
		for (GLsizei h = 0; h < texH; ++h)
		{
			for (GLsizei w = 0; w < texW; ++w)
			{
				texData[c + 0u] = w % 256u;
				texData[c + 1u] = h % 256u;
				texData[c + 2u] = 0u;
				texData[c + 3u] = 255u;
				c += 4u;
			}
		}
		textures["color"].Image2D(GL_TEXTURE_2D, 0, GL_RGBA, texW, texH, GL_RGBA, GL_UNSIGNED_BYTE, texData.data());
	}

	void QuadRender::InitBuffersEvent()
	{
		Render::InitBuffersEvent();

		//
		std::vector<R32> posData = {
			0.f, 0.f, 0.f,
			1.f, 0.f, 0.f,
			1.f, 1.f, 0.f,
			0.f, 1.f, 0.f };
		std::vector<R32> normalData = {
			0.f, 0.f, 1.f,
			0.f, 0.f, 1.f,
			0.f, 0.f, 1.f,
			0.f, 0.f, 1.f };
		std::vector<R32> uvData = {
			0.f, 0.f,
			1.f, 0.f,
			1.f, 1.f,
			0.f, 1.f };
		std::vector<UI32> indexData = { 0,1,2,3 };

		buffers["quad_pos"].Data(posData, GL_STATIC_DRAW);
		buffers["quad_normal"].Data(normalData, GL_STATIC_DRAW);
		buffers["quad_uv"].Data(uvData, GL_STATIC_DRAW);
		buffers["quad_index"].Data(indexData, GL_STATIC_DRAW);
	}

	void QuadRender::InitVertexShaderHeadersEvent()
	{
		Render::InitVertexShaderHeadersEvent();

		//
		shaderSources["unlit_vert"].push_back(R"(
#version 460 core

uniform mat4 u_modelView;
uniform mat4 u_projection;

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_uv;

out vec4 v_pos;
out vec4 v_normal;
out vec2 v_uv;
				)");
	}

	void QuadRender::InitVertexShaderMainsEvent()
	{
		shaderSources["unlit_vert"].push_back(R"(
void main(void)
{
	v_pos		= u_modelView * vec4(a_pos, 1);
	v_normal	= u_modelView * vec4(normalize(a_normal), 0);
	v_uv		= a_uv;
	gl_Position	= u_projection * v_pos;
}
				)");
	}

	void QuadRender::InitGeometryShaderHeadersEvent()
	{
		Render::InitGeometryShaderHeadersEvent();

		//
	}

	void QuadRender::InitGeometryShaderMainsEvent()
	{

	}

	void QuadRender::InitFragmentShaderHeadersEvent()
	{
		Render::InitFragmentShaderHeadersEvent();

		//
		shaderSources["unlit_frag"].push_back(R"(
#version 460 core

uniform sampler2D u_tex;
uniform uint u_mode;

in vec4 v_pos;
in vec4 v_normal;
in vec2 v_uv;

layout(location = 0) out vec4 f_color;
				)");
	}

	void QuadRender::InitFragmentShaderMainsEvent()
	{
		shaderSources["unlit_frag"].push_back(R"(
void main(void)
{
	vec3 normal = normalize(v_normal.xyz);

	if(u_mode == 0)
		f_color = texture(u_tex, v_uv);
	else if (u_mode == 1)
		f_color = vec4((normal + 1.0f) * 0.5f, 1.0f);
	else if (u_mode == 2)
		f_color = vec4((v_pos.xyz + 1.0f) * 0.5f, 1.0f);
	else if (u_mode == 3)
		f_color = vec4(v_uv, 0.0f, 1.0f);
	else
		f_color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}
				)");
	}

	void QuadRender::InitShadersEvent()
	{
		Render::InitShadersEvent();

		//
		shaders["unlit_vert"].Source(shaderSources["unlit_vert"]);
		{
			GLboolean success;
			std::string log;
			std::tie(success, log) = shaders["unlit_vert"].Compile();
			if (!success)
			{
				PrintShaderSources("unlit_vert");
				THROW_EXCEPTION("unlit_vert compile fail: " + log);
			}
		}

		if (shaderSources["unlit_geom"].size() > 0)
		{
			shaders["unlit_geom"].Source(shaderSources["unlit_geom"]);
			GLboolean success;
			std::string log;
			std::tie(success, log) = shaders["unlit_geom"].Compile();
			if (!success)
			{
				PrintShaderSources("unlit_geom");
				THROW_EXCEPTION("unlit_geom compile fail: " + log);
			}
		}

		shaders["unlit_frag"].Source(shaderSources["unlit_frag"]);
		{
			GLboolean success;
			std::string log;
			std::tie(success, log) = shaders["unlit_frag"].Compile();
			if (!success)
			{
				PrintShaderSources("unlit_frag");
				THROW_EXCEPTION("unlit_frag compile fail: " + log);
			}
		}
	}

	void QuadRender::InitProgramsEvent()
	{
		Render::InitProgramsEvent();

		//
		programs["unlit"].AttachShader(shaders["unlit_vert"]);
		if (shaderSources["unlit_geom"].size() > 0)
			programs["unlit"].AttachShader(shaders["unlit_geom"]);
		programs["unlit"].AttachShader(shaders["unlit_frag"]);

		GLboolean success;
		std::string log;
		std::tie(success, log) = programs["unlit"].Link();
		if (!success)
			THROW_EXCEPTION("unlit link fail - " + log);

		programs["unlit"].DetachShader(shaders["unlit_vert"]);
		if (shaderSources["unlit_geom"].size() > 0)
			programs["unlit"].DetachShader(shaders["unlit_geom"]);
		programs["unlit"].DetachShader(shaders["unlit_frag"]);
	}

	void QuadRender::InitProgramParametersEvent() const
	{
		Render::InitProgramParametersEvent();

		//
		programs.at("unlit").Uniform<GLfloat, 4, 4>("u_modelView", viewing * modelling);
		programs.at("unlit").Uniform<GLfloat, 4, 4>("u_projection", projection);
		programs.at("unlit").Uniform<GLuint, 1>("u_mode", (GLuint)0);
	}

	void QuadRender::InitVertexArraysEvent()
	{
		Render::InitVertexArraysEvent();

		//
		// Set pos
		{
			GLint attribLocation = programs["unlit"].GetAttribLocation("a_pos");
			GLuint bindingIndex = 0;

			vertexArrays["quad"].EnableAttrib(attribLocation);
			vertexArrays["quad"].VertexBuffer<GLfloat>(bindingIndex, buffers["quad_pos"], 0, 3);
			vertexArrays["quad"].AttribBinding(attribLocation, bindingIndex);
			vertexArrays["quad"].AttribFormat(attribLocation, 3, GL_FLOAT, GL_FALSE, 0);
		}

		// Set normal
		{
			GLint attribLocation = programs["unlit"].GetAttribLocation("a_normal");
			GLuint bindingIndex = 1;

			vertexArrays["quad"].EnableAttrib(attribLocation);
			vertexArrays["quad"].VertexBuffer<GLfloat>(bindingIndex, buffers["quad_normal"], 0, 3);
			vertexArrays["quad"].AttribBinding(attribLocation, bindingIndex);
			vertexArrays["quad"].AttribFormat(attribLocation, 3, GL_FLOAT, GL_FALSE, 0);
		}

		// Set uv
		{
			GLint attribLocation = programs["unlit"].GetAttribLocation("a_uv");
			GLuint bindingIndex = 2;

			vertexArrays["quad"].EnableAttrib(attribLocation);
			vertexArrays["quad"].VertexBuffer<GLfloat>(bindingIndex, buffers["quad_uv"], 0, 2);
			vertexArrays["quad"].AttribBinding(attribLocation, bindingIndex);
			vertexArrays["quad"].AttribFormat(attribLocation, 2, GL_FLOAT, GL_FALSE, 0);
		}

		// Set index
		vertexArrays["quad"].ElementBuffer(buffers["quad_index"]);
	}

	void QuadRender::InitFrameBuffersEvent()
	{
	}

	void QuadRender::PreDrawEvent() const
	{
		Render::PreDrawEvent();

		//
		programs.at("unlit").Begin();
		vertexArrays.at("quad").Begin();
		textures.at("color").Begin(samplers.at("bilinear"));
		programs.at("unlit").Uniform<GLint, 1>("u_tex", (GLint)textures.at("color").Unit());
	}

	void QuadRender::OnDrawEvent() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, CurrentWindowWidth(), CurrentWindowHeight());

		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, NULL);
	}

	void QuadRender::PostDrawEvent() const
	{
		textures.at("color").End();
		vertexArrays.at("quad").End();
		programs.at("unlit").End();

		//
		Render::PostDrawEvent();
	}
};