#pragma once

// O3GL
#include "O3GL/Utils.hpp"
#include "O3GL/Buffer.hpp"
#include "O3GL/VertexArray.hpp"
#include "O3GL/Shader.hpp"
#include "O3GL/Program.hpp"
#include "O3GL/Sampler.hpp"
#include "O3GL/Texture.hpp"
#include "O3GL/Window.hpp"

//
namespace O3GL
{
	// Simply Print FrameCounter
	template<int key>
	class DrawPrimitive : public Window<key>
	{
	public:
		DrawPrimitive(const std::string& name, int x, int y, int width, int height);
		DrawPrimitive(int window, int x, int y, int width, int height);

	public:
		virtual void InitGLStatusEvent() const;

	public:
		virtual void DisplayEvent();
		virtual void TimerEvent(int value);

	protected:
		PTR<Program> program;

		PTR<Buffer> posBuffer;
		PTR<Buffer> normalBuffer;
		PTR<Buffer> uvBuffer;
		PTR<Buffer> indexBuffer;
		PTR<VertexArray> vertexArray;

		PTR<Sampler> sampler;
		PTR<Texture> texture;

		Mat44 viewing;
		Mat44 modelling;
		Mat44 projection;

	protected:
		Shader CreateVertexShader() const;
		Shader CreateFragmentShader() const;
		void InitProgram();
		void InitBuffer();
		void InitVertexArray();
		void InitTexture();
	};

	//
	template<int key>
	DrawPrimitive<key>::DrawPrimitive(const std::string& name, int x, int y, int width, int height) :
		Window<key>(name, GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH, x, y, width, height, 33)
	{
		InitProgram();
		InitBuffer();
		InitVertexArray();
		InitTexture();

		// Init uniforms
		viewing = glm::lookAt(Vec3(0.f, 0.f, 0.f), Vec3(0.f, 0.f, -1.f), Vec3(0.f, 1.f, 0.f));
		modelling = glm::translate(glm::identity<Mat44>(), Vec3(0.f, 0.f, -2.f));
		projection = glm::perspective(glm::radians(60.0f), ((R32)GetInfo<int>(GLUT_WINDOW_WIDTH)) / ((R32)GetInfo<int>(GLUT_WINDOW_HEIGHT)), 0.1f, 100.0f);
		program->Uniform<GLfloat, 4, 4>("u_modelView", viewing * modelling);
		program->Uniform<GLfloat, 4, 4>("u_projection", projection);
		program->Uniform<GLuint, 1>("u_mode", (GLuint)0);
	}

	template<int key>
	DrawPrimitive<key>::DrawPrimitive(int window, int x, int y, int width, int height) :
		Window<key>(window, x, y, width, height, 33)
	{
		InitProgram();
		InitBuffer();
		InitVertexArray();
		InitTexture();

		// Init uniforms
		viewing = glm::lookAt(Vec3(0.f, 0.f, 0.f), Vec3(0.f, 0.f, -1.f), Vec3(0.f, 1.f, 0.f));
		modelling = glm::translate(glm::identity<Mat44>(), Vec3(0.f, 0.f, -2.f));
		projection = glm::perspective(glm::radians(60.0f), ((R32)GetInfo<int>(GLUT_WINDOW_WIDTH)) / ((R32)GetInfo<int>(GLUT_WINDOW_HEIGHT)), 0.1f, 100.0f);
		program->Uniform<GLfloat, 4, 4>("u_modelView", viewing * modelling);
		program->Uniform<GLfloat, 4, 4>("u_projection", projection);
		program->Uniform<GLuint, 1>("u_mode", (GLuint)0);
	}

	template<int key>
	void DrawPrimitive<key>::InitGLStatusEvent() const
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
	void DrawPrimitive<key>::DisplayEvent()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw
		program->Begin();
		vertexArray->Begin();
		texture->Begin(*sampler);

		program->Uniform<GLint, 1>("u_tex", (GLint)texture->Unit());
		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, NULL);

		texture->End();
		vertexArray->End();
		program->End();

		// Swap buffers
		glutSwapBuffers();
	}

	template<int key>
	void DrawPrimitive<key>::TimerEvent(int value)
	{
		glutPostRedisplay();
	}

	template<int key>
	Shader DrawPrimitive<key>::CreateVertexShader() const
	{
		Shader vertexShader(GL_VERTEX_SHADER);

		vertexShader.Source(R"(
#version 460 core

uniform mat4 u_modelView;
uniform mat4 u_projection;

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_uv;

out vec4 v_pos;
out vec4 v_normal;
out vec2 v_uv;

void main(void)
{
	v_pos		= u_modelView * vec4(a_pos, 1);
	v_normal	= u_modelView * vec4(normalize(a_normal), 0);
	v_uv		= a_uv;
	gl_Position	= u_projection * v_pos;
})");

		GLboolean success;
		std::string log;
		std::tie(success, log) = vertexShader.Compile();
		if (!success)
			THROW_EXCEPTION("Shader compile fail: " + log);

		return vertexShader;
	}

	template<int key>
	Shader DrawPrimitive<key>::CreateFragmentShader() const
	{
		Shader fragmentShader(GL_FRAGMENT_SHADER);

		fragmentShader.Source(R"(
#version 460 core

uniform sampler2D u_tex;
uniform uint u_mode;

in vec4 v_pos;
in vec4 v_normal;
in vec2 v_uv;

layout(location = 0) out vec4 f_color;

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
})");

		GLboolean success;
		std::string log;
		std::tie(success, log) = fragmentShader.Compile();
		if (!success)
			THROW_EXCEPTION("Shader compile fail: " + log);

		return fragmentShader;
	}

	template<int key>
	void DrawPrimitive<key>::InitProgram()
	{
		program = PTR<Program>(new Program());

		Shader vertexShader = CreateVertexShader();
		Shader fragmentShader = CreateFragmentShader();

		program->AttachShader(vertexShader);
		program->AttachShader(fragmentShader);

		GLboolean success;
		std::string log;
		std::tie(success, log) = program->Link();
		if (!success)
			THROW_EXCEPTION("Program link fail - " + log);

		program->DetachShader(vertexShader);
		program->DetachShader(fragmentShader);
	}

	template<int key>
	void DrawPrimitive<key>::InitBuffer()
	{
		posBuffer = PTR<Buffer>(new Buffer());
		normalBuffer = PTR<Buffer>(new Buffer());
		uvBuffer = PTR<Buffer>(new Buffer());
		indexBuffer = PTR<Buffer>(new Buffer());

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

		posBuffer->Data(posData, GL_STATIC_DRAW);
		normalBuffer->Data(normalData, GL_STATIC_DRAW);
		uvBuffer->Data(uvData, GL_STATIC_DRAW);
		indexBuffer->Data(indexData, GL_STATIC_DRAW);
	}

	template<int key>
	void DrawPrimitive<key>::InitVertexArray()
	{
		vertexArray = PTR<VertexArray>(new VertexArray());

		// Set pos
		{
			GLint attribLocation = program->GetAttribLocation("a_pos");
			GLuint bindingIndex = 0;

			vertexArray->EnableAttrib(attribLocation);
			vertexArray->VertexBuffer<GLfloat>(bindingIndex, (*posBuffer), 0, 3);
			vertexArray->AttribBinding(attribLocation, bindingIndex);
			vertexArray->AttribFormat(attribLocation, 3, GL_FLOAT, GL_FALSE, 0);
		}

		// Set normal
		{
			GLint attribLocation = program->GetAttribLocation("a_normal");
			GLuint bindingIndex = 1;

			vertexArray->EnableAttrib(attribLocation);
			vertexArray->VertexBuffer<GLfloat>(bindingIndex, *normalBuffer, 0, 3);
			vertexArray->AttribBinding(attribLocation, bindingIndex);
			vertexArray->AttribFormat(attribLocation, 3, GL_FLOAT, GL_FALSE, 0);
		}

		// Set uv
		{
			GLint attribLocation = program->GetAttribLocation("a_uv");
			GLuint bindingIndex = 2;

			vertexArray->EnableAttrib(attribLocation);
			vertexArray->VertexBuffer<GLfloat>(bindingIndex, *uvBuffer, 0, 2);
			vertexArray->AttribBinding(attribLocation, bindingIndex);
			vertexArray->AttribFormat(attribLocation, 2, GL_FLOAT, GL_FALSE, 0);
		}

		// Set index
		vertexArray->ElementBuffer(*indexBuffer);
	}

	template<int key>
	void DrawPrimitive<key>::InitTexture()
	{
		texture = PTR<Texture>(new Texture(GL_TEXTURE_2D));
		sampler = PTR<Sampler>(new Sampler());

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
		texture->Image2D(GL_TEXTURE_2D, 0, GL_RGBA, texW, texH, GL_RGBA, GL_UNSIGNED_BYTE, texData.data());

		sampler->SetInfo<GLint>(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		sampler->SetInfo<GLint>(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		sampler->SetInfo<GLint>(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		sampler->SetInfo<GLint>(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
};