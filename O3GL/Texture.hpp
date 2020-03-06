#pragma once

// std
#include <vector>

// O3GL
#include "O3GL/Utils.hpp"
#include "O3GL/Sampler.hpp"

// 
namespace O3GL
{
	//
	class _Texture : public GLObject
	{
	public:
		_Texture(GLenum target = GL_TEXTURE_2D);

	public:
		inline const GLenum& Target() const { return target; }
		inline const GLuint& Unit() const { return unitID; }

	public:
		void Begin() const;
		void Begin(const Sampler& sampler) const;

		void End() const;

		template<class T>
		T GetInfo(GLenum pname) const;

		template<class T>
		T GetInfo(GLint level, GLenum pname) const;

		template<class T>
		void SetInfo(GLenum pname, T params) const;

		void Storage1D(GLint levels, GLint internalformat, GLsizei width) const;

		void Storage2D(GLint levels, GLint internalformat, GLsizei width, GLsizei height) const;

		void Storage3D(GLint levels, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth) const;

		void SubImage1D(GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid* data = NULL) const;

		void SubImage2D(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* data = NULL) const;

		void SubImage3D(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid* data = NULL) const;

		void Image1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid* data = NULL) const;

		void Image2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* data = NULL) const;

		void Image3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid* data = NULL) const;

		void GenMipmaps() const;

	public:
		template<>
		GLfloat GetInfo<GLfloat>(GLenum pname) const;

		template<>
		GLint GetInfo<GLint>(GLenum pname) const;

		template<>
		GLfloat GetInfo<GLfloat>(GLint level, GLenum pname) const;

		template<>
		GLint GetInfo<GLint>(GLint level, GLenum pname) const;

		template<>
		void SetInfo<GLfloat>(GLenum pname, GLfloat params) const;

		template<>
		void SetInfo<GLint>(GLenum pname, GLint params) const;

	protected:
		GLenum target;
		GLuint unitID;
		static bool initUnits;
		static std::vector<GLuint> units;
	};

	//
	class Texture : public GLHandle<_Texture>
	{
	public:
		Texture(GLenum target = GL_TEXTURE_2D) : GLHandle<_Texture>(new _Texture(target)) {}
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
	GLfloat _Texture::GetInfo<GLfloat>(GLint level, GLenum pname) const
	{
		GLfloat rf(0.f);
		glGetTextureLevelParameterfv(*this, level, pname, &rf);
		GL_CHECK_ERROR;
		return rf;
	}

	template<>
	GLint _Texture::GetInfo<GLint>(GLint level, GLenum pname) const
	{
		GLint ri(0);
		glGetTextureLevelParameteriv(*this, level, pname, &ri);
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

