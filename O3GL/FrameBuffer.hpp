#pragma once

// std
#include <map>

// O3GL
#include "Utils.hpp"
#include "Texture.hpp"

// 
namespace O3GL
{
	//
	class _FrameBuffer : public Object
	{
	public:
		_FrameBuffer() : Object(glCreateFramebuffer(), glDeleteFramebuffers) {}

	public:
		inline std::map<GLenum, Texture>& ColorAttachments() { return colorAttachments; }
		inline std::map<GLenum, Texture>& DepthAttachments() { return depthAttachments; }
		inline const std::map<GLenum, Texture>& ColorAttachments() const { return colorAttachments; }
		inline const std::map<GLenum, Texture>& DepthAttachments() const { return depthAttachments; }

	public:
		void Begin() const;

		static void End();

		template<class T>
		T GetInfo(GLenum pname) const;

		template<class T>
		void SetInfo(GLenum pname, T params) const;

		void AttachToColor(GLenum attachment, const Texture& texture);

		void AttachToDepth(const Texture& texture);

		Texture GetColorAttachment(GLenum attachment) const;

		Texture GetDepthAttachment(GLenum attachment) const;

		void DrawBuffer(GLenum attachment) const;

		void DrawBuffer(const std::vector<GLenum>& attachments) const;

	public:
		template<>
		GLint GetInfo<GLint>(GLenum pname) const;

		template<>
		void SetInfo<GLint>(GLenum pname, GLint params) const;

	protected:
		std::map<GLenum, Texture> colorAttachments;
		std::map<GLenum, Texture> depthAttachments;
	};

	//
	class FrameBuffer : public Handle<_FrameBuffer>
	{
	public:
		FrameBuffer() : Handle<_FrameBuffer>(new _FrameBuffer()) {}
	};

	//
	template<>
	GLint _FrameBuffer::GetInfo<GLint>(GLenum pname) const
	{
		GLint ri(0);
		glGetNamedFramebufferParameteriv(*this, pname, &ri);
		GL_CHECK_ERROR;
		return ri;
	}

	template<>
	void _FrameBuffer::SetInfo<GLint>(GLenum pname, GLint params) const
	{
		glNamedFramebufferParameteri(*this, pname, params);
		GL_CHECK_ERROR;
	}
};