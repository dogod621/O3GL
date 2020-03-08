// std
#include <sstream>

// O3GL
#include "O3GL/Render.hpp"

//
namespace O3GL
{
	//
	Render::Render() :
		samplers(),
		textures(),
		buffers(),
		vertexArrays(),
		shaderSources(),
		shaders(),
		programs(),
		frameBuffers(),

		costTimeMS(0.0)
	{
	}

	void Render::Init()
	{
		InitSetupEvent();
		UpdateEvent();

		InitSamplersEvent();
		InitTexturesEvent();
		InitBuffersEvent();
		InitVertexArraysEvent();

		InitVertexShaderHeadersEvent();
		InitVertexShaderMainsEvent();

		InitGeometryShaderHeadersEvent();
		InitGeometryShaderMainsEvent();

		InitFragmentShaderHeadersEvent();
		InitFragmentShaderMainsEvent();

		InitShadersEvent();

		InitProgramsEvent();
		InitProgramParametersEvent();

		InitFrameBuffersEvent();
	}

	void Render::Draw() const
	{
		PreDrawEvent();
		OnDrawEvent();
		PostDrawEvent();
	}

	void Render::PrintShaderSources(const std::string& name) const
	{
		int count = 1;
		std::cout << std::setw(6) << "Name: " << name << std::endl;
		std::stringstream ss(shaders.at(name).GetSource());
		std::string line;
		while (std::getline(ss, line, '\n'))
		{
			std::cout << std::setw(6) << count << ": " << line << std::endl;
			count++;
		}
	}
};