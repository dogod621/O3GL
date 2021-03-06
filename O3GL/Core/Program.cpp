// O3GL
#include "O3GL/Core/Program.hpp"

// 
namespace O3GL
{
	std::vector<GLuint> Program::bindStack = std::vector<GLuint>();

	void Program::Begin() const
	{
		bindStack.push_back(*this);
		glUseProgram(bindStack.back());
		GL_CHECK_ERROR;
	}

	void Program::End() const
	{
		if (bindStack.empty())
		{
			THROW_EXCEPTION("Invalid End");
		}
		else if (bindStack.back() != GLuint(*this))
		{
			THROW_EXCEPTION("Invalid End");
		}

		bindStack.pop_back();
		if (bindStack.empty())
		{
			glUseProgram(0);
		}
		else
		{
			glUseProgram(bindStack.back());
		}
		GL_CHECK_ERROR;
	}

	std::tuple<GLenum, std::vector<GLbyte>> Program::GetBinary() const
	{
		std::vector<GLbyte> buffer;
		buffer.resize(GetInfo<GLint>(GL_PROGRAM_BINARY_LENGTH));
		GLsizei loadSize(0);
		GLenum format(0);
		glGetProgramBinary(*this, (GLsizei)buffer.size(), &loadSize, &format, (void*)&buffer[0]);
		GL_CHECK_ERROR;
		return std::make_tuple(format, buffer);
	}

	void Program::LoadBinary(const std::tuple<GLenum, std::vector<GLbyte>>& binary) const
	{
		GLenum format(0);
		std::vector<GLbyte> buffer;
		std::tie(format, buffer) = binary;

		glProgramBinary(*this, format, (const void*)(&buffer[0]), (GLsizei)buffer.size());
		GL_CHECK_ERROR;
	}

	std::string Program::GetLog() const
	{
		std::string log(GetInfo<GLint>(GL_INFO_LOG_LENGTH), NULL);
		GLsizei loadSize(0);
		glGetProgramInfoLog(*this, (GLsizei)log.size(), &loadSize, &log[0]);
		GL_CHECK_ERROR;
		return log;
	}

	std::tuple<GLboolean, std::string> Program::Validate() const
	{
		glValidateProgram(*this);
		GL_CHECK_ERROR;
		return std::make_tuple(GetInfo<GLboolean>(GL_VALIDATE_STATUS), GetLog());
	}

	void Program::AttachShader(const Shader& shader) const
	{
		glAttachShader(*this, shader);
		GL_CHECK_ERROR;
	}

	void Program::DetachShader(const Shader& shader) const
	{
		glDetachShader(*this, shader);
		GL_CHECK_ERROR;
	}

	std::tuple<GLboolean, std::string> Program::Link() const
	{
		glLinkProgram(*this);
		GL_CHECK_ERROR;
		return std::make_tuple(GetInfo<GLboolean>(GL_LINK_STATUS), GetLog());
	}

	void Program::BindAttribLocation(GLuint index, const std::string& name) const
	{
		glBindAttribLocation(*this, index, name.c_str());
		GL_CHECK_ERROR;
	}

	GLint Program::GetAttribLocation(const std::string& name) const
	{
		GLint ri = glGetAttribLocation(*this, name.c_str());
		GL_CHECK_ERROR;
		return ri;
	}

	GLint Program::GetUniformLocation(const std::string& name) const
	{
		GLint location = glGetUniformLocation(*this, name.c_str());
		GL_CHECK_ERROR;
		return location;
	}
};