// O3GL
#include "VertexArray.hpp"

// 
namespace O3GL
{
	void _VertexArray::Begin() const
	{
		glBindVertexArray(*this);
		GL_CHECK_ERROR;
	}

	void _VertexArray::End()
	{
		glBindVertexArray(0);
		GL_CHECK_ERROR;
	}

	void _VertexArray::EnableAttrib(GLuint attribindex) const
	{
		glEnableVertexArrayAttrib(*this, attribindex);
		GL_CHECK_ERROR;
	}

	void _VertexArray::AttribBinding(GLuint attribindex, GLuint bindingindex) const
	{
		glVertexArrayAttribBinding(*this, attribindex, bindingindex);
		GL_CHECK_ERROR;
	}

	void _VertexArray::AttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) const
	{
		glVertexArrayAttribFormat(*this, attribindex, size, type, normalized, relativeoffset);
		GL_CHECK_ERROR;
	}

	void _VertexArray::AttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) const
	{
		glVertexArrayAttribIFormat(*this, attribindex, size, type, relativeoffset);
		GL_CHECK_ERROR;
	}

	void _VertexArray::AttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) const
	{
		glVertexArrayAttribLFormat(*this, attribindex, size, type, relativeoffset);
		GL_CHECK_ERROR;
	}

	void _VertexArray::ElementBuffer(const Buffer& buffer) const
	{
		glVertexArrayElementBuffer(*this, buffer);
		GL_CHECK_ERROR;
	}
};