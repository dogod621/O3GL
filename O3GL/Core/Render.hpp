#pragma once

// O3GL
#include "O3GL/Core/Utils.hpp"
#include "O3GL/Core/Buffer.hpp"
#include "O3GL/Core/VertexArray.hpp"
#include "O3GL/Core/Shader.hpp"
#include "O3GL/Core/Program.hpp"
#include "O3GL/Core/Sampler.hpp"
#include "O3GL/Core/Texture.hpp"
#include "O3GL/Core/FrameBuffer.hpp"

// 
namespace O3GL
{
	//
	class Render
	{
	public:
		virtual void SetupEvent() {} // inherit accumulate

	public:
		virtual void InitSamplersEvent() {} // inherit accumulate
		virtual void InitTexturesEvent() {} // inherit accumulate
		virtual void InitBuffersEvent() {} // inherit accumulate
		virtual void InitVertexShaderHeadersEvent() {} // inherit accumulate
		virtual void InitVertexShaderMainsEvent() {}
		virtual void InitGeometryShaderHeadersEvent() {} // inherit accumulate
		virtual void InitGeometryShaderMainsEvent() {}
		virtual void InitFragmentShaderHeadersEvent() {} // inherit accumulate
		virtual void InitFragmentShaderMainsEvent() {}
		virtual void InitShadersEvent() {} // inherit accumulate
		virtual void InitProgramsEvent() {} // inherit accumulate
		virtual void InitProgramParametersEvent() const {} // inherit accumulate
		virtual void InitVertexArraysEvent() {} // inherit accumulate
		virtual void InitFrameBuffersEvent() {} // inherit accumulate

	public:
		virtual void PreDrawEvent() const {} // inherit accumulate
		virtual void OnDrawEvent() const {}
		virtual void PostDrawEvent() const {} // inherit accumulate

	public:
		Render();

	public:
		void Init();
		double Draw() const;
		void PrintShaderSources(const std::string& name) const;

	protected:
		std::map<std::string, Sampler		> samplers;
		std::map<std::string, Texture		> textures;
		std::map<std::string, Buffer		> buffers;
		std::map<std::string, VertexArray	> vertexArrays;
		std::map<std::string, ShaderSource	> shaderSources;
		std::map<std::string, Shader		> shaders;
		std::map<std::string, Program		> programs;
		std::map<std::string, FrameBuffer	> frameBuffers;
	};
};