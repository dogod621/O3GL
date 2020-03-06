#pragma once

// std
#include <tuple>
#include <vector>

// O3GL
#include "O3GL/Utils.hpp"

// 
namespace O3GL
{
	class _Shader : public GLObject
	{
	public:
		_Shader(GLenum type = GL_VERTEX_SHADER) : GLObject(glCreateShader(type), glDeleteShader), type(type) {}

	public:
		inline const GLenum& Type() const { return type; }

	public:
		template<class T> T GetInfo(GLenum pname) const;

		std::string GetLog() const;

		std::string GetSource() const;

		void Source(const std::vector<std::string>& srcs) const;

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
	class Shader : public GLHandle<_Shader>
	{
	public:
		Shader(GLenum type = GL_VERTEX_SHADER) : GLHandle<_Shader>(new _Shader(type)) {}
	};

	//
	template<>
	GLint _Shader::GetInfo<GLint>(GLenum pname) const
	{
		GLint ri(0);
		glGetShaderiv(*this, pname, &ri);
		GL_CHECK_ERROR;
		return ri;
	}

	template<>
	GLboolean _Shader::GetInfo<GLboolean>(GLenum pname) const
	{
		return (GLboolean)GetInfo<GLint>(pname);
	}
};
