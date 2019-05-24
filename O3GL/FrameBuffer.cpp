// O3GL
#include "FrameBuffer.hpp"

// 
namespace O3GL
{
	void _FrameBuffer::Begin() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, *this);
		GL_CHECK_ERROR;
	}

	void _FrameBuffer::End()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		GL_CHECK_ERROR;
	}

	void _FrameBuffer::AttachToColor(GLenum attachment, const Texture& texture)
	{
		glNamedFramebufferTexture(*this, attachment, texture, 0);

		if (glCheckNamedFramebufferStatus(*this, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			EXCEPTION("FrameBuffer cannot be created.");

		GL_CHECK_ERROR;
		colorAttachments[attachment] = texture;
	}

	void _FrameBuffer::AttachToDepth(const Texture& texture)
	{
		glNamedFramebufferTexture(*this, GL_DEPTH_ATTACHMENT, texture, 0);

		if (glCheckNamedFramebufferStatus(*this, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			EXCEPTION("FrameBuffer cannot be created.");

		GL_CHECK_ERROR;
		depthAttachments[GL_DEPTH_ATTACHMENT] = texture;
	}

	Texture _FrameBuffer::GetColorAttachment(GLenum attachment) const
	{
		return colorAttachments.at(attachment);
	}

	Texture _FrameBuffer::GetDepthAttachment(GLenum attachment) const
	{
		return depthAttachments.at(attachment);
	}

	void _FrameBuffer::DrawBuffer(GLenum attachment) const
	{
		glNamedFramebufferDrawBuffer(*this, attachment);
		GL_CHECK_ERROR;
	}

	void _FrameBuffer::DrawBuffer(const std::vector<GLenum>& attachments) const
	{
		glNamedFramebufferDrawBuffers(*this, (GLsizei)attachments.size(), &attachments[0]);
		GL_CHECK_ERROR;
	}
};