// O3GL
#include "O3GL/Buffer.hpp"

//
namespace O3GL
{
	GLboolean Buffer::Unmap() const
	{
		GLboolean rb = glUnmapNamedBuffer(*this);
		GL_CHECK_ERROR;
		return rb;
	}
};
