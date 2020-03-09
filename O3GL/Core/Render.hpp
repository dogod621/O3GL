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
		virtual void SetupEvent() {}

	public:
		virtual void InitSamplersEvent() {}
		virtual void InitTexturesEvent() {}
		virtual void InitBuffersEvent() {}
		virtual void InitVertexShaderHeadersEvent() {}
		virtual void InitVertexShaderMainsEvent() {}
		virtual void InitGeometryShaderHeadersEvent() {}
		virtual void InitGeometryShaderMainsEvent() {}
		virtual void InitFragmentShaderHeadersEvent() {}
		virtual void InitFragmentShaderMainsEvent() {}
		virtual void InitShadersEvent() {}
		virtual void InitProgramsEvent() {}
		virtual void InitProgramParametersEvent() const {}
		virtual void InitVertexArraysEvent() {}
		virtual void InitFrameBuffersEvent() {}

	public:
		virtual void PreDrawEvent() const {}
		virtual void OnDrawEvent() const {}
		virtual void PostDrawEvent() const {}

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