// std
#include <algorithm>

// O3GL
#include "O3GL/Texture.hpp"

// 
namespace O3GL
{
	bool _Texture::initUnits = false;
	std::vector<GLuint> _Texture::units = std::vector<GLuint>();

	_Texture::_Texture(GLenum target) : GLObject(glCreateTexture(target), glDeleteTextures), target(target), unitID(0)
	{
		if (!initUnits)
		{
			GLint n;
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &n);
			units.resize((std::size_t)n);

			GLuint k = 0;
			for (std::vector<GLuint>::iterator i = units.begin(); i != units.end(); ++i)
			{
				*i = k;
				k++;
			}
			std::make_heap(units.begin(), units.end(), std::greater<GLuint>{});
			initUnits = true;
		}
	}

	void _Texture::Begin() const
	{
		if (begin)
		{
			THROW_EXCEPTION("Call Begin without End");
		}
		{
			std::pop_heap(units.begin(), units.end(), std::greater<GLuint>{});
			*(GLuint*)(&unitID) = units.back();
			units.pop_back();
			glBindTextureUnit(unitID, *this);
		}
		*(bool*)(&begin) = true;
		GL_CHECK_ERROR;
	}

	void _Texture::Begin(const Sampler& sampler) const
	{
		if (begin)
		{
			THROW_EXCEPTION("Call Begin without End");
		}
		{
			std::pop_heap(units.begin(), units.end(), std::greater<GLuint>{});
			*(GLuint*)(&unitID) = units.back();
			units.pop_back();
			glBindTextureUnit(unitID, *this);
			glBindSampler(unitID, sampler);
		}
		*(bool*)(&begin) = true;
		GL_CHECK_ERROR;
	}

	void _Texture::End() const
	{
		if (!begin)
		{
			THROW_EXCEPTION("Call End without Begin");
		}
		{
			glBindTextureUnit(unitID, 0);
			glBindSampler(unitID, 0);
			units.push_back(unitID);
			std::push_heap(units.begin(), units.end(), std::greater<GLuint>{});
			(*(GLuint*)&unitID) = 0;
		}
		*(bool*)(&begin) = false;
		GL_CHECK_ERROR;
	}

	void _Texture::Storage1D(GLint levels, GLint internalformat, GLsizei width) const
	{
		glTextureStorage1D(*this, levels, internalformat, width);
		GL_CHECK_ERROR;
	}

	void _Texture::Storage2D(GLint levels, GLint internalformat, GLsizei width, GLsizei height) const
	{
		glTextureStorage2D(*this, levels, internalformat, width, height);
		GL_CHECK_ERROR;
	}

	void _Texture::Storage3D(GLint levels, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth) const
	{
		glTextureStorage3D(*this, levels, internalformat, width, height, depth);
		GL_CHECK_ERROR;
	}

	void _Texture::SubImage1D(GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid* data) const
	{
		glTextureSubImage1D(*this, level, xoffset, width, format, type, data);
		GL_CHECK_ERROR;
	}

	void _Texture::SubImage2D(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* data) const
	{
		glTextureSubImage2D(*this, level, xoffset, yoffset, width, height, format, type, data);
		GL_CHECK_ERROR;
	}

	void _Texture::SubImage3D(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid* data) const
	{
		glTextureSubImage3D(*this, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);
		GL_CHECK_ERROR;
	}

	void _Texture::Image1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid* data) const
	{
		glBindTexture(this->target, *this);
		glTexImage1D(target, level, internalformat, width, 0, format, type, data);
		glBindTexture(this->target, 0);
		GL_CHECK_ERROR;
	}

	void _Texture::Image2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* data) const
	{
		glBindTexture(this->target, *this);
		glTexImage2D(target, level, internalformat, width, height, 0, format, type, data);
		glBindTexture(this->target, 0);
		GL_CHECK_ERROR;
	}

	void _Texture::Image3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid* data) const
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