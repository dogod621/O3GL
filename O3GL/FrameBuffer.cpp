// std
#include <sstream>

// O3GL
#include "O3GL/FrameBuffer.hpp"

// 
namespace O3GL
{
	std::vector<GLuint> _FrameBuffer::bindStack = std::vector<GLuint>();

	void _FrameBuffer::Begin() const
	{
		bindStack.push_back(*this);
		glBindFramebuffer(GL_FRAMEBUFFER, bindStack.back());
		GL_CHECK_ERROR;
	}

	void _FrameBuffer::End() const
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
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		else
		{
			glBindFramebuffer(GL_FRAMEBUFFER, bindStack.back());
		}
		GL_CHECK_ERROR;
	}

	void _FrameBuffer::Attach(GLenum attachment, const Texture& texture, GLint level)
	{
		glNamedFramebufferTexture(*this, attachment, texture, level);

		if (glCheckNamedFramebufferStatus(*this, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			THROW_EXCEPTION("FrameBuffer cannot be created.");

		GL_CHECK_ERROR;
	}

	void _FrameBuffer::DrawBuffer(GLenum attachment) const
	{
		glNamedFramebufferDrawBuffer(*this, attachment);
		GL_CHECK_ERROR;
	}

	void _FrameBuffer::DrawBuffer(const std::vector<GLenum>& attachments) const
	{
		GLint n = 0;
		glGetIntegerv(GL_MAX_DRAW_BUFFERS, &n);

		if (n < attachments.size())
			THROW_EXCEPTION("Number of attachments is larger than GL_MAX_DRAW_BUFFERS");

		glNamedFramebufferDrawBuffers(*this, (GLsizei)attachments.size(), &attachments[0]);
		GL_CHECK_ERROR;
	}

	std::string _FrameBuffer::AttachmentInformation() const
	{
		std::stringstream ss;

		GLint n = 0;
		glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &n);

		for (GLint i = 0; i < n; ++i)
		{
			GLint type = GetInfo<GLint>(GL_COLOR_ATTACHMENT0 + i, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE);

			switch (type)
			{
			case GL_NONE:
				break;

			case GL_FRAMEBUFFER_DEFAULT:
				ss << "F" << i << ": ";
				break;

			case GL_TEXTURE:
				ss << "T" << i << ": ";
				break;

			case GL_RENDERBUFFER:
				ss << "R" << i << ": ";
				break;

			default:
				THROW_EXCEPTION("Unknown attachment type");
				break;
			}

			switch (type)
			{
			case GL_NONE:
				break;

			default:
			{
				GLint rs = GetInfo<GLint>(GL_COLOR_ATTACHMENT0 + i, GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE);
				GLint gs = GetInfo<GLint>(GL_COLOR_ATTACHMENT0 + i, GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE);
				GLint bs = GetInfo<GLint>(GL_COLOR_ATTACHMENT0 + i, GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE);
				GLint as = GetInfo<GLint>(GL_COLOR_ATTACHMENT0 + i, GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE);
				if (rs > 0) ss << "R" << rs;
				if (gs > 0) ss << "G" << gs;
				if (bs > 0) ss << "B" << bs;
				if (as > 0) ss << "A" << as;
				ss << " ";
			}
			break;
			}
		}

		//
		{
			GLint type = GetInfo<GLint>(GL_DEPTH_ATTACHMENT, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE);

			switch (type)
			{
			case GL_NONE:
				break;

			case GL_FRAMEBUFFER_DEFAULT:
				ss << "F" << ": ";
				break;

			case GL_TEXTURE:
				ss << "T" << ": ";
				break;

			case GL_RENDERBUFFER:
				ss << "R" << ": ";
				break;

			default:
				THROW_EXCEPTION("Unknown attachment type");
				break;
			}

			switch (type)
			{
			case GL_NONE:
				break;

			default:
			{
				GLint ds = GetInfo<GLint>(GL_DEPTH_ATTACHMENT, GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE);
				if (ds > 0) ss << "D" << ds << " ";
			}
			break;
			}
		}

		//
		{
			GLint type = GetInfo<GLint>(GL_STENCIL_ATTACHMENT, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE);

			switch (type)
			{
			case GL_NONE:
				break;

			case GL_FRAMEBUFFER_DEFAULT:
				ss << "F" << ": ";
				break;

			case GL_TEXTURE:
				ss << "T" << ": ";
				break;

			case GL_RENDERBUFFER:
				ss << "R" << ": ";
				break;

			default:
				THROW_EXCEPTION("Unknown attachment type");
				break;
			}

			switch (type)
			{
			case GL_NONE:
				break;

			default:
			{
				GLint ts = GetInfo<GLint>(GL_STENCIL_ATTACHMENT, GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE);
				if (ts > 0) ss << "S" << ts << " ";
			}
			break;
			}
		}

		return ss.str();
	}
};