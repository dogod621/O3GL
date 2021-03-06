#pragma once

namespace O3GL
{
	struct Message;

	namespace Display
	{
		struct Message;
	};

	namespace OverlayDisplay
	{
		struct Message;
	};

	namespace Reshape
	{
		struct Message;
	};

	namespace Keyboard
	{
		struct Message;
	};

	namespace KeyboardUp
	{
		struct Message;
	};

	namespace Special
	{
		struct Message;
	};

	namespace SpecialUp
	{
		struct Message;
	};

	namespace Mouse
	{
		struct Message;
	};

	namespace Motion
	{
		struct Message;
	};

	namespace PassiveMotion
	{
		struct Message;
	};

	namespace Visibility
	{
		struct Message;
	};

	namespace Entry
	{
		struct Message;
	};

	namespace Close
	{
		struct Message;
	};

	namespace Timer
	{
		struct Message;
	};
}

// O3GL
#include "O3GL/Core/Utils.hpp"
#include "O3GL/Core/Buffer.hpp"
#include "O3GL/Core/VertexArray.hpp"
#include "O3GL/Core/Shader.hpp"
#include "O3GL/Core/Program.hpp"
#include "O3GL/Core/Sampler.hpp"
#include "O3GL/Core/Texture.hpp"
#include "O3GL/Core/FrameBuffer.hpp"
#include "O3GL/Core/Window.hpp"

// 
namespace O3GL
{
	//
	class Render
	{
	protected:
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

	protected:
		virtual void PreDrawEvent() const {}
		virtual void OnDrawEvent() const {}
		virtual void PostDrawEvent() const {}

	protected:
		virtual void DisplayEvent(const Display::Message& m) {}
		virtual void OverlayDisplayEvent(const OverlayDisplay::Message& m) {}
		virtual void ReshapeEvent(const Reshape::Message& m) {}
		virtual void KeyboardEvent(const Keyboard::Message& m) {}
		virtual void KeyboardUpEvent(const KeyboardUp::Message& m) {}
		virtual void SpecialEvent(const Special::Message& m) {}
		virtual void SpecialUpEvent(const SpecialUp::Message& m) {}
		virtual void MouseEvent(const Mouse::Message& m) {}
		virtual void MotionEvent(const Motion::Message& m) {}
		virtual void PassiveMotionEvent(const PassiveMotion::Message& m) {}
		virtual void VisibilityEvent(const Visibility::Message& m) {}
		virtual void EntryEvent(const Entry::Message& m) {}
		virtual void CloseEvent(const Close::Message& m) {}
		virtual void TimerEvent(const Timer::Message& m) {}

	public:
		Render();

	public:
		void Init();
		double Draw() const;
		void PrintShaderSources(const std::string& name) const;
		void UpdateProgramParameters()
		{
			InitProgramParametersEvent();
		}
		
		void DisplayCallback(const Display::Message& m);
		void OverlayDisplayCallback(const OverlayDisplay::Message& m);
		void ReshapeCallback(const Reshape::Message& m);
		void KeyboardCallback(const Keyboard::Message& m);
		void KeyboardUpCallback(const KeyboardUp::Message& m);
		void SpecialCallback(const Special::Message& m);
		void SpecialUpCallback(const SpecialUp::Message& m);
		void MouseCallback(const Mouse::Message& m);
		void MotionCallback(const Motion::Message& m);
		void PassiveMotionCallback(const PassiveMotion::Message& m);
		void VisibilityCallback(const Visibility::Message& m);
		void EntryCallback(const Entry::Message& m);
		void CloseCallback(const Close::Message& m);
		void TimerCallback(const Timer::Message& m);

	protected:
		std::map<std::string, PTR<Sampler		>> samplers;
		std::map<std::string, PTR<Texture		>> textures;
		std::map<std::string, PTR<Buffer		>> buffers;
		std::map<std::string, PTR<VertexArray	>> vertexArrays;
		std::map<std::string, PTR<ShaderSource	>> shaderSources;
		std::map<std::string, PTR<Shader		>> shaders;
		std::map<std::string, PTR<Program		>> programs;
		std::map<std::string, PTR<FrameBuffer	>> frameBuffers;
		std::map<std::string, PTR<Render		>> addPreprocessRenders;
		std::map<std::string, PTR<Render		>> preprocessRenders;
		std::map<std::string, PTR<Render		>> addPostprocessRenders;
		std::map<std::string, PTR<Render		>> postprocessRenders;

	public:
		PTR<Sampler> GetSampler(const std::string& name)
		{
			return samplers.at(name);
		}

		PTR<Texture> GetTexture(const std::string& name)
		{
			return textures.at(name);
		}

		PTR<Buffer> GetBuffer(const std::string& name)
		{
			return buffers.at(name);
		}

		PTR<VertexArray> GetVertexArray(const std::string& name)
		{
			return vertexArrays.at(name);
		}

		PTR<ShaderSource> GetShaderSource(const std::string& name)
		{
			return shaderSources.at(name);
		}

		PTR<Shader> GetShader(const std::string& name)
		{
			return shaders.at(name);
		}

		PTR<Program> GetProgram(const std::string& name)
		{
			return programs.at(name);
		}

		PTR<FrameBuffer> GetFrameBuffer(const std::string& name)
		{
			return frameBuffers.at(name);
		}

		PTR<Render> GetPreprocessRender(const std::string& name)
		{
			return preprocessRenders.at(name);
		}

		PTR<Render> GetPostprocessRender(const std::string& name)
		{
			return postprocessRenders.at(name);
		}

		PTR<Render> GetAddPreprocessRender(const std::string& name)
		{
			return addPreprocessRenders.at(name);
		}

		PTR<Render> GetAddPostprocessRender(const std::string& name)
		{
			return addPostprocessRenders.at(name);
		}

		CONST_PTR<Sampler> GetSampler(const std::string& name) const
		{
			return samplers.at(name);
		}

		CONST_PTR<Texture> GetTexture(const std::string& name) const
		{
			return textures.at(name);
		}

		CONST_PTR<Buffer> GetBuffer(const std::string& name) const
		{
			return buffers.at(name);
		}

		CONST_PTR<VertexArray> GetVertexArray(const std::string& name) const
		{
			return vertexArrays.at(name);
		}

		CONST_PTR<ShaderSource> GetShaderSource(const std::string& name) const
		{
			return shaderSources.at(name);
		}

		CONST_PTR<Shader> GetShader(const std::string& name) const
		{
			return shaders.at(name);
		}

		CONST_PTR<Program> GetProgram(const std::string& name) const
		{
			return programs.at(name);
		}

		CONST_PTR<FrameBuffer> GetFrameBuffer(const std::string& name) const
		{
			return frameBuffers.at(name);
		}

		CONST_PTR<Render> GetPreprocessRender(const std::string& name) const
		{
			return preprocessRenders.at(name);
		}

		CONST_PTR<Render> GetPostprocessRender(const std::string& name) const
		{
			return postprocessRenders.at(name);
		}

		CONST_PTR<Render> GetAddPreprocessRender(const std::string& name) const
		{
			return addPreprocessRenders.at(name);
		}

		CONST_PTR<Render> GetAddPostprocessRender(const std::string& name) const
		{
			return addPostprocessRenders.at(name);
		}

		void SetSampler(const std::string& name, PTR<Sampler> v)
		{
			samplers[name] = v;
		}

		void SetTexture(const std::string& name, PTR<Texture> v)
		{
			textures[name] = v;
		}

		void SetBuffer(const std::string& name, PTR<Buffer> v)
		{
			buffers[name] = v;
		}

		void SetVertexArray(const std::string& name, PTR<VertexArray> v)
		{
			vertexArrays[name] = v;
		}

		void SetShaderSource(const std::string& name, PTR<ShaderSource> v)
		{
			shaderSources[name] = v;
		}

		void SetShader(const std::string& name, PTR<Shader> v)
		{
			shaders[name] = v;
		}

		void SetProgram(const std::string& name, PTR<Program> v)
		{
			programs[name] = v;
		}

		void SetFrameBuffer(const std::string& name, PTR<FrameBuffer> v)
		{
			frameBuffers[name] = v;
		}

		void SetPreprocessRender(const std::string& name, PTR<Render> v)
		{
			preprocessRenders[name] = v;
		}

		void SetPostprocessRender(const std::string& name, PTR<Render> v)
		{
			postprocessRenders[name] = v;
		}

		void AddPreprocessRender(const std::string& name, PTR<Render> v)
		{
			addPreprocessRenders[name] = v;
		}

		void AddPostprocessRender(const std::string& name, PTR<Render> v)
		{
			addPostprocessRenders[name] = v;
		}

		void RemoveTexture(const std::string& name)
		{
			textures.erase(name);
		}

		void RemoveBuffer(const std::string& name)
		{
			buffers.erase(name);
		}

		void RemoveVertexArray(const std::string& name)
		{
			vertexArrays.erase(name);
		}

		void RemoveShaderSource(const std::string& name)
		{
			shaderSources.erase(name);
		}

		void RemoveShader(const std::string& name)
		{
			shaders.erase(name);
		}

		void RemoveProgram(const std::string& name)
		{
			programs.erase(name);
		}

		void RemoveFrameBuffer(const std::string& name)
		{
			frameBuffers.erase(name);
		}

		void RemovePreprocessRender(const std::string& name)
		{
			addPreprocessRenders.erase(name);
		}

		void RemovePostprocessRender(const std::string& name)
		{
			addPostprocessRenders.erase(name);
		}
	};
};