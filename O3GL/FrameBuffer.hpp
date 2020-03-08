#pragma once

// std
#include <vector>
#include <map>

// O3GL
#include "O3GL/Utils.hpp"
#include "O3GL/Texture.hpp"

// 
namespace O3GL
{
	//
	class FrameBuffer : public GLHandle
	{
	public:
		FrameBuffer() : GLHandle(new GLObject(glCreateFramebuffer(), glDeleteFramebuffers)) {}

	public:
		void Begin() const;

		void End() const;

		template<class T>
		T GetInfo(GLenum pname) const;

		template<class T>
		void SetInfo(GLenum pname, T params) const;

		template<class T>
		T GetInfo(GLenum attachment, GLenum pname) const;

		void Attach(GLenum attachment, const Texture& texture, GLint level = 0);

		void DrawBuffer(GLenum attachment) const;

		void DrawBuffer(const std::vector<GLenum>& attachments) const;

		std::string AttachmentInformation() const;

	public:
		template<>
		GLint GetInfo<GLint>(GLenum pname) const;

		template<>
		void SetInfo<GLint>(GLenum pname, GLint params) const;

		template<>
		GLint GetInfo<GLint>(GLenum attachment, GLenum pname) const;

	protected:
		static std::vector<GLuint> bindStack;
	};

	//
	template<>
	GLint FrameBuffer::GetInfo<GLint>(GLenum pname) const
	{
		GLint ri(0);
		glGetNamedFramebufferParameteriv(*this, pname, &ri);
		GL_CHECK_ERROR;
		return ri;
	}

	template<>
	void FrameBuffer::SetInfo<GLint>(GLenum pname, GLint params) const
	{
		glNamedFramebufferParameteri(*this, pname, params);
		GL_CHECK_ERROR;
	}

	template<>
	GLint FrameBuffer::GetInfo<GLint>(GLenum attachment, GLenum pname) const
	{
		GLint ri(0);
		glGetNamedFramebufferAttachmentParameteriv(*this, attachment, pname, &ri);
		GL_CHECK_ERROR;
		return ri;
	}
};