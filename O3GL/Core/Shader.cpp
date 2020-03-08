// std
#include <fstream>

// O3GL
#include "O3GL/Core/Shader.hpp"

// 
namespace O3GL
{
	std::string Shader::GetLog() const
	{
		std::string log(GetInfo<GLint>(GL_INFO_LOG_LENGTH), NULL);
		GLsizei loadSize(0);
		glGetShaderInfoLog(*this, (GLsizei)log.size(), &loadSize, &log[0]);
		GL_CHECK_ERROR;
		return log;
	}

	std::string Shader::GetSource() const
	{
		std::string ss(GetInfo<GLint>(GL_SHADER_SOURCE_LENGTH), NULL);
		GLsizei loadSize(0);
		glGetShaderSource(*this, (GLsizei)ss.size(), &loadSize, &ss[0]);
		GL_CHECK_ERROR;
		return ss;
	}

	void Shader::Source(const ShaderSource& srcs) const
	{
		std::vector<GLint> length;
		std::vector<const GLchar*> srcsPtr;
		length.resize(srcs.size());
		srcsPtr.resize(srcs.size());
		for (int i = 0; i < srcs.size(); ++i)
		{
			length[i] = (GLint)srcs[i].size();
			srcsPtr[i] = srcs[i].c_str();
		}
		glShaderSource(*this, (GLsizei)srcs.size(), &srcsPtr[0], &length[0]);
		GL_CHECK_ERROR;
	}

	void Shader::Source(const std::string& src) const
	{
		std::vector<GLint> length;
		std::vector<const GLchar*> srcsPtr;
		length.resize(1);
		srcsPtr.resize(1);
		length[0] = (GLint)src.size();
		srcsPtr[0] = src.c_str();
		glShaderSource(*this, 1, &srcsPtr[0], &length[0]);
		GL_CHECK_ERROR;
	}

	void Shader::SourceFile(const std::vector<std::string>& fileNames) const
	{
		ShaderSource srcs(fileNames.size());
		for (std::size_t i = 0; i < fileNames.size(); ++i)
		{
			std::ifstream file;
			file.open(fileNames[i], std::ios::in | std::ios::ate);
			if (!file.is_open())
			{
				file.close();
				THROW_EXCEPTION("File: " + fileNames[i] + " cannot be opened.");
			}
			srcs[i].resize((std::size_t)file.tellg());
			file.seekg(0, std::ios::beg);
			file.read(&srcs[i][0], srcs[i].size());
			file.close();
		}
		Source(srcs);
	}

	void Shader::SourceFile(const std::string& fileName) const
	{
		std::ifstream file;
		file.open(fileName, std::ios::in | std::ios::ate);
		if (!file.is_open())
		{
			file.close();
			THROW_EXCEPTION("File: " + fileName + " cannot be opened.");
		}
		std::string src((std::size_t)file.tellg(), NULL);
		file.seekg(0, std::ios::beg);
		file.read(&src[0], src.size());
		file.close();
		Source(src);
	}

	std::tuple<GLboolean, std::string> Shader::Compile() const
	{
		glCompileShader(*this);
		GL_CHECK_ERROR;
		return std::make_tuple(GetInfo<GLboolean>(GL_COMPILE_STATUS), GetLog());
	}
};

