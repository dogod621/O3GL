// std
#include <fstream>

// O3GL
#include "Shader.hpp"

// 
namespace O3GL
{
	std::string _Shader::GetLog() const
	{
		std::string log(GetInfo<GLint>(GL_INFO_LOG_LENGTH), NULL);
		GLsizei loadSize(0);
		glGetShaderInfoLog(*this, (GLsizei)log.size(), &loadSize, &log[0]);
		GL_CHECK_ERROR;
		return log;
	}

	void _Shader::Source(const std::vector<std::string>& strings) const
	{
		std::vector<GLint> length;
		std::vector<const GLchar *> stringsGL;
		length.resize(strings.size());
		stringsGL.resize(strings.size());
		for (int i = 0; i < strings.size(); ++i)
		{
			length[i] = (GLint)strings[i].size();
			stringsGL[i] = strings[i].c_str();
		}
		glShaderSource(*this, (GLsizei)strings.size(), &stringsGL[0], &length[0]);
		GL_CHECK_ERROR;
	}

	void _Shader::Source(const std::string& fileName) const
	{
		std::ifstream file;
		file.open(fileName, std::ios::in | std::ios::ate);
		if (!file.is_open())
		{
			file.close();
			EXCEPTION("File: " + fileName + " cannot be opened.");
		}

		std::string fileContent((std::size_t)file.tellg() + 1, NULL);
		file.seekg(0, std::ios::beg);
		file.read(&fileContent[0], fileContent.size() - 1);
		file.close();

		const GLchar * temp[1] = { fileContent.c_str() };
		glShaderSource(*this, 1, temp, NULL);

		GL_CHECK_ERROR;
	}

	std::tuple<GLboolean, std::string> _Shader::Compile() const
	{
		glCompileShader(*this);
		GL_CHECK_ERROR;
		return std::make_tuple(GetInfo<GLboolean>(GL_COMPILE_STATUS), GetLog());
	}
};

