#pragma once

// O3GL
#include "Utils.hpp"

// 
namespace O3GL
{
	//
	class _Texture : public Object
	{
	public:
		_Texture(GLenum target = GL_TEXTURE_2D) : Object(glCreateTexture(target), glDeleteTextures), target(target) {}

	public:
		inline const GLenum& Target() const { return target; }

	public:
		void Begin(GLuint unit) const;

		static void End(GLuint unit);

		template<class T>
		T GetInfo(GLenum pname) const;

		template<class T>
		void SetInfo(GLenum pname, T params) const;

		void Image1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid * data = NULL) const;

		void Image2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * data = NULL) const;

		void Image3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * data = NULL) const;

		void GenMipmaps() const;

	public:
		template<>
		GLfloat GetInfo<GLfloat>(GLenum pname) const;

		template<>
		GLint GetInfo<GLint>(GLenum pname) const;

		template<>
		void SetInfo<GLfloat>(GLenum pname, GLfloat params) const;

		template<>
		void SetInfo<GLint>(GLenum pname, GLint params) const;

	protected:
		GLenum target;
	};

	//
	class Texture : public Handle<_Texture>
	{
	public:
		Texture(GLenum target = GL_TEXTURE_2D) : Handle<_Texture>(new _Texture(target)) {}
	};

	//
	template<>
	GLfloat _Texture::GetInfo<GLfloat>(GLenum pname) const
	{
		GLfloat rf(0.f);
		glGetTextureParameterfv(*this, pname, &rf);
		GL_CHECK_ERROR;
		return rf;
	}

	template<>
	GLint _Texture::GetInfo<GLint>(GLenum pname) const
	{
		GLint ri(0);
		glGetTextureParameteriv(*this, pname, &ri);
		GL_CHECK_ERROR;
		return ri;
	}

	template<>
	void _Texture::SetInfo<GLfloat>(GLenum pname, GLfloat params) const
	{
		glTextureParameterf(*this, pname, params);
		GL_CHECK_ERROR;
	}

	template<>
	void _Texture::SetInfo<GLint>(GLenum pname, GLint params) const
	{
		glTextureParameteri(*this, pname, params);
		GL_CHECK_ERROR;
	}
};

