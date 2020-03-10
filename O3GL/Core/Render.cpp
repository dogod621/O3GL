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
		for (std::map<std::string, PTR<Render>>::iterator it = renders.begin(); it != renders.end(); ++it)
		{
			it->second->Init();
		}

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

	void Render::DisplayCallback(const Display::Message& m)
	{
		for (std::map<std::string, PTR<Render>>::iterator it = renders.begin(); it != renders.end(); ++it)
		{
			it->second->DisplayCallback(m);
		}
		DisplayEvent(m);
	}

	void Render::OverlayDisplayCallback(const OverlayDisplay::Message& m)
	{
		for (std::map<std::string, PTR<Render>>::iterator it = renders.begin(); it != renders.end(); ++it)
		{
			it->second->OverlayDisplayCallback(m);
		}
		OverlayDisplayEvent(m);
	}

	void Render::ReshapeCallback(const Reshape::Message& m)
	{
		for (std::map<std::string, PTR<Render>>::iterator it = renders.begin(); it != renders.end(); ++it)
		{
			it->second->ReshapeCallback(m);
		}
		ReshapeEvent(m);
	}

	void Render::KeyboardCallback(const Keyboard::Message& m)
	{
		for (std::map<std::string, PTR<Render>>::iterator it = renders.begin(); it != renders.end(); ++it)
		{
			it->second->KeyboardCallback(m);
		}
		KeyboardEvent(m);
	}

	void Render::KeyboardUpCallback(const KeyboardUp::Message& m)
	{
		for (std::map<std::string, PTR<Render>>::iterator it = renders.begin(); it != renders.end(); ++it)
		{
			it->second->KeyboardUpCallback(m);
		}
		KeyboardUpEvent(m);
	}

	void Render::SpecialCallback(const Special::Message& m)
	{
		for (std::map<std::string, PTR<Render>>::iterator it = renders.begin(); it != renders.end(); ++it)
		{
			it->second->SpecialCallback(m);
		}
		SpecialEvent(m);
	}

	void Render::SpecialUpCallback(const SpecialUp::Message& m)
	{
		for (std::map<std::string, PTR<Render>>::iterator it = renders.begin(); it != renders.end(); ++it)
		{
			it->second->SpecialUpCallback(m);
		}
		SpecialUpEvent(m);
	}

	void Render::MouseCallback(const Mouse::Message& m)
	{
		for (std::map<std::string, PTR<Render>>::iterator it = renders.begin(); it != renders.end(); ++it)
		{
			it->second->MouseCallback(m);
		}
		MouseEvent(m);
	}

	void Render::MotionCallback(const Motion::Message& m)
	{
		for (std::map<std::string, PTR<Render>>::iterator it = renders.begin(); it != renders.end(); ++it)
		{
			it->second->MotionCallback(m);
		}
		MotionEvent(m);
	}

	void Render::PassiveMotionCallback(const PassiveMotion::Message& m)
	{
		for (std::map<std::string, PTR<Render>>::iterator it = renders.begin(); it != renders.end(); ++it)
		{
			it->second->PassiveMotionCallback(m);
		}
		PassiveMotionEvent(m);
	}

	void Render::VisibilityCallback(const Visibility::Message& m)
	{
		for (std::map<std::string, PTR<Render>>::iterator it = renders.begin(); it != renders.end(); ++it)
		{
			it->second->VisibilityCallback(m);
		}
		VisibilityEvent(m);
	}

	void Render::EntryCallback(const Entry::Message& m)
	{
		for (std::map<std::string, PTR<Render>>::iterator it = renders.begin(); it != renders.end(); ++it)
		{
			it->second->EntryCallback(m);
		}
		EntryEvent(m);
	}

	void Render::CloseCallback(const Close::Message& m)
	{
		for (std::map<std::string, PTR<Render>>::iterator it = renders.begin(); it != renders.end(); ++it)
		{
			it->second->CloseCallback(m);
		}
		CloseEvent(m);
	}

	void Render::TimerCallback(const Timer::Message& m)
	{
		for (std::map<std::string, PTR<Render>>::iterator it = renders.begin(); it != renders.end(); ++it)
		{
			it->second->TimerCallback(m);
		}
		TimerEvent(m);
	}
};