#pragma once

// O3GL
#include "O3GL/Utils.hpp"

// 
namespace O3GL
{
	//
	class Sampler : public GLHandle
	{
	public:
		Sampler() : GLHandle(new GLObject(glCreateSampler(), glDeleteSamplers)) {}

	public:
		template<class T>
		T GetInfo(GLenum pname) const;

		template<class T>
		void SetInfo(GLenum pname, T params) const;

	public:
		template<>
		GLfloat GetInfo<GLfloat>(GLenum pname) const;

		template<>
		GLint GetInfo<GLint>(GLenum pname) const;

		template<>
		void SetInfo<GLfloat>(GLenum pname, GLfloat params) const;

		template<>
		void SetInfo<GLint>(GLenum pname, GLint params) const;
	};

	//
	template<>
	GLfloat Sampler::GetInfo<GLfloat>(GLenum pname) const
	{
		GLfloat rf(0.f);
		glGetSamplerParameterfv(*this, pname, &rf);
		GL_CHECK_ERROR;
		return rf;
	}

	template<>
	GLint Sampler::GetInfo<GLint>(GLenum pname) const
	{
		GLint ri(0);
		glGetSamplerParameteriv(*this, pname, &ri);
		GL_CHECK_ERROR;
		return ri;
	}

	template<>
	void Sampler::SetInfo<GLfloat>(GLenum pname, GLfloat params) const
	{
		glSamplerParameterf(*this, pname, params);
		GL_CHECK_ERROR;
	}

	template<>
	void Sampler::SetInfo<GLint>(GLenum pname, GLint params) const
	{
		glSamplerParameteri(*this, pname, params);
		GL_CHECK_ERROR;
	}
};

