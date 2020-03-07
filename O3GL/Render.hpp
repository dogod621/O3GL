#pragma once

// O3GL
#include "O3GL/Utils.hpp"
#include "O3GL/Buffer.hpp"
#include "O3GL/VertexArray.hpp"
#include "O3GL/Shader.hpp"
#include "O3GL/Program.hpp"
#include "O3GL/Sampler.hpp"
#include "O3GL/Texture.hpp"
#include "O3GL/FrameBuffer.hpp"

// 
namespace O3GL
{
	//
	class Render
	{
	public:
		virtual std::string Name() const { return "Render"; }

	public:
		using ShaderSource = std::vector<std::string>;

		using Samplers = std::map<std::string, Sampler>;
		using Textures = std::map<std::string, Texture>;
		using Buffers = std::map<std::string, Buffer>;
		using VertexArrays = std::map<std::string, VertexArray>;
		using ShaderSources = std::map<std::string, ShaderSource>;
		using Shaders = std::map<std::string, Shader>;
		using Programs = std::map<std::string, Program>;
		using FrameBuffers = std::map<std::string, FrameBuffer>;

	protected:
		double costTimeMS;

	public:
		Samplers		samplers;
		Textures		textures;
		Buffers			buffers;
		VertexArrays	vertexArrays;
		ShaderSources	shaderSources;
		Shaders			shaders;
		Programs		programs;
		FrameBuffers	frameBuffers;

	public:
		virtual void Init(); // inherit accumulate
		virtual void Draw() const;

	public:
		virtual void InitSetupEvent() {} // inherit accumulate
		virtual void InitSamplersEvent() {} // inherit accumulate
		virtual void InitTexturesEvent() {} // inherit accumulate
		virtual void InitBuffersEvent() {} // inherit accumulate
		virtual void InitVertexArraysEvent() {} // inherit accumulate
		virtual void InitVertexShaderHeadersEvent() {} // inherit accumulate
		virtual void InitVertexShaderMainsEvent() {}
		virtual void InitGeometryShaderHeadersEvent() {} // inherit accumulate
		virtual void InitGeometryShaderMainsEvent() {}
		virtual void InitFragmentShaderHeadersEvent() {} // inherit accumulate
		virtual void InitFragmentShaderMainsEvent() {}
		virtual void InitShadersEvent() {} // inherit accumulate
		virtual void InitProgramsEvent() {} // inherit accumulate
		virtual void InitProgramParametersEvent() const {} // inherit accumulate
		virtual void InitFrameBuffersEvent() {} // inherit accumulate

		virtual void PreDrawEvent() const {} // inherit accumulate
		virtual void OnDrawEvent() const {}
		virtual void PostDrawEvent() const {} // inherit accumulate
		virtual void LaunchEvent() const { *(double*)(&costTimeMS) = 0.0; }

		// inherit accumulate
		virtual void UpdateEvent() {}
		virtual bool KeyboardEvent(unsigned char key, int x, int y) { return false; }
		virtual bool KeyboardUpEvent(unsigned char key, int x, int y) { return false; }
		virtual bool SpecialEvent(int key, int x, int y) { return false; }
		virtual bool SpecialUpEvent(int key, int x, int y) { return false; }
		virtual bool MouseEvent(int button, int state, int x, int y) { return false; }
		virtual bool MotionEvent(int x, int y) { return false; }
		virtual bool PassiveMotionEvent(int x, int y) { return false; }

	public:
		void PrintShaderSources(const std::string& name) const;
		virtual void DrawInfo(float& wx, float& wy, float lineHeight = 0.06f) const;
		virtual void DrawName(float& wx, float& wy, float lineHeight = 0.06f) const;

	public:
		Render();
	};
};