// O3GL
#include "Buffer.hpp"

//
namespace O3GL
{
	GLboolean _Buffer::Unmap() const
	{
		GLboolean rb = glUnmapNamedBuffer(*this);
		GL_CHECK_ERROR;
		return rb;
	}
};
