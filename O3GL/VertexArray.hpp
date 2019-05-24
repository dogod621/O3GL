#pragma once

// O3GL
#include "Utils.hpp"
#include "Buffer.hpp"

// 
namespace O3GL
{
	class _VertexArray : public Object
	{
	public:
		_VertexArray() : Object(glCreateVertexArray(), glDeleteVertexArrays) {}

	public:
		void Begin() const;

		static void End();

		void EnableAttrib(GLuint attribindex) const;

		template<class T>
		void VertexBuffer(GLuint bindingindex, GLuint buffer, std::size_t offset, std::size_t stride) const;

		void AttribBinding(GLuint attribindex, GLuint bindingindex) const;

		void AttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) const;

		void AttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) const;

		void AttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) const;

		void ElementBuffer(const Buffer& buffer) const;
	};

	//
	class VertexArray : public Handle<_VertexArray>
	{
	public:
		VertexArray() : Handle<_VertexArray>(new _VertexArray()) {}
	};

	//
	template<class T>
	void _VertexArray::VertexBuffer(GLuint bindingindex, GLuint buffer, std::size_t offset, std::size_t stride) const
	{
		glVertexArrayVertexBuffer(*this, bindingindex, buffer, (GLintptr)(offset * sizeof(T)), (GLsizei)(stride * sizeof(T)));
		GL_CHECK_ERROR;
	}
};