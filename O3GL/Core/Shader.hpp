#pragma once

// std
#include <tuple>
#include <vector>

// O3GL
#include "O3GL/Core/Utils.hpp"

// 
namespace O3GL
{
	using ShaderSource = std::vector<std::string>;

	class Shader : public GLHandle
	{
	public:
		Shader(GLenum type = GL_VERTEX_SHADER) : GLHandle(new GLObject(glCreateShader(type), glDeleteShader)), type(type) {}

	public:
		inline const GLenum& Type() const { return type; }

	public:
		template<class T> T GetInfo(GLenum pname) const;

		std::string GetLog() const;

		std::string GetSource() const;

		void Source(const ShaderSource& srcs) const;

		void Source(const std::string& src) const;

		void SourceFile(const std::vector<std::string>& fileNames) const;

		void SourceFile(const std::string& fileName) const;

		std::tuple<GLboolean, std::string> Compile() const;

	public:
		template<>
		GLint GetInfo<GLint>(GLenum pname) const;

		template<>
		GLboolean GetInfo<GLboolean>(GLenum pname) const;

	protected:
		GLenum type;
	};

	//
	template<>
	GLint Shader::GetInfo<GLint>(GLenum pname) const
	{
		GLint ri(0);
		glGetShaderiv(*this, pname, &ri);
		GL_CHECK_ERROR;
		return ri;
	}

	template<>
	GLboolean Shader::GetInfo<GLboolean>(GLenum pname) const
	{
		return (GLboolean)GetInfo<GLint>(pname);
	}
};
