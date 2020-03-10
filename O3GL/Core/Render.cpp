// std
#include <sstream>

// O3GL
#include "O3GL/Core/Render.hpp"

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
		renders()
	{
	}

	void Render::Init()
	{
		//
		SetupEvent();

		//
		InitSamplersEvent();
		InitTexturesEvent();
		InitBuffersEvent();

		InitVertexShaderHeadersEvent();
		InitVertexShaderMainsEvent();

		InitGeometryShaderHeadersEvent();
		InitGeometryShaderMainsEvent();

		InitFragmentShaderHeadersEvent();
		InitFragmentShaderMainsEvent();

		InitShadersEvent();

		InitProgramsEvent();
		InitProgramParametersEvent();

		InitVertexArraysEvent();

		InitFrameBuffersEvent();
	}

	double Render::Draw() const
	{
		PreDrawEvent();

		// Compute time
		glFinish(); // Wait
		std::chrono::steady_clock::time_point timeStart = std::chrono::high_resolution_clock::now();

		OnDrawEvent();

		// Compute time
		glFinish(); // Wait
		std::chrono::steady_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> timeElapsed = timeEnd - timeStart;

		PostDrawEvent();

		return timeElapsed.count();
	}

	void Render::PrintShaderSources(const std::string& name) const
	{
		int count = 1;
		std::cout << std::setw(6) << "Name: " << name << std::endl;
		std::stringstream ss(shaders.at(name)->GetSource());
		std::string line;
		while (std::getline(ss, line, '\n'))
		{
			std::cout << std::setw(6) << count << ": " << line << std::endl;
			count++;
		}
	}
};