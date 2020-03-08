// O3GL
#include "O3GL/Core/VertexArray.hpp"

// 
namespace O3GL
{
	std::vector<GLuint> VertexArray::bindStack = std::vector<GLuint>();

	void VertexArray::Begin() const
	{
		bindStack.push_back(*this);
		glBindVertexArray(bindStack.back());
		GL_CHECK_ERROR;
	}

	void VertexArray::End() const
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
			glBindVertexArray(0);
		}
		else
		{
			glBindVertexArray(bindStack.back());
		}
		GL_CHECK_ERROR;
	}

	void VertexArray::EnableAttrib(GLuint attribindex) const
	{
		glEnableVertexArrayAttrib(*this, attribindex);
		GL_CHECK_ERROR;
	}

	void VertexArray::DisableAttrib(GLuint attribindex) const
	{
		glDisableVertexArrayAttrib(*this, attribindex);
		GL_CHECK_ERROR;
	}

	void VertexArray::AttribBinding(GLuint attribindex, GLuint bindingindex) const
	{
		glVertexArrayAttribBinding(*this, attribindex, bindingindex);
		GL_CHECK_ERROR;
	}

	void VertexArray::AttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) const
	{
		glVertexArrayAttribFormat(*this, attribindex, size, type, normalized, relativeoffset);
		GL_CHECK_ERROR;
	}

	void VertexArray::AttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) const
	{
		glVertexArrayAttribIFormat(*this, attribindex, size, type, relativeoffset);
		GL_CHECK_ERROR;
	}

	void VertexArray::AttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) const
	{
		glVertexArrayAttribLFormat(*this, attribindex, size, type, relativeoffset);
		GL_CHECK_ERROR;
	}

	void VertexArray::ElementBuffer(const Buffer& buffer) const
	{
		glVertexArrayElementBuffer(*this, buffer);
		GL_CHECK_ERROR;
	}
};