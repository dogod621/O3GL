// O3GL
#include "Texture.hpp"

// 
namespace O3GL
{
	void _Texture::Begin(GLuint unit) const
	{
		glBindTextureUnit(unit, *this);
		GL_CHECK_ERROR;
	}

	void _Texture::End(GLuint unit)
	{
		glBindTextureUnit(unit, 0);
		GL_CHECK_ERROR;
	}

	void _Texture::Image1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid * data) const
	{
		glBindTexture(this->target, *this);
		glTexImage1D(target, level, internalformat, width, 0, format, type, data);
		glBindTexture(this->target, 0);
		GL_CHECK_ERROR;
	}

	void _Texture::Image2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * data) const
	{
		glBindTexture(this->target, *this);
		glTexImage2D(target, level, internalformat, width, height, 0, format, type, data);
		glBindTexture(this->target, 0);
		GL_CHECK_ERROR;
	}

	void _Texture::Image3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * data) const
	{
		glBindTexture(this->target, *this);
		glTexImage3D(target, level, internalformat, width, height, depth, 0, format, type, data);
		glBindTexture(this->target, 0);
		GL_CHECK_ERROR;
	}

	void _Texture::GenMipmaps() const
	{
		glGenerateTextureMipmap(*this);
		GL_CHECK_ERROR;
	}
};