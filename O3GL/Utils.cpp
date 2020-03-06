// O3GL
#include "O3GL/Utils.hpp"

// 
namespace O3GL
{
	std::mutex Global::lock;

	std::random_device Random::randomDevice;
	std::mt19937_64 Random::generator(randomDevice());
	std::uniform_real_distribution<R32> Random::uniR32(0.f, 1.f);
	std::uniform_real_distribution<R64> Random::uniR64(0.0, 1.0);
	std::uniform_int_distribution<I16> Random::uniI16(std::numeric_limits<I16>::min(), std::numeric_limits<I16>::max());
	std::uniform_int_distribution<I32> Random::uniI32(std::numeric_limits<I32>::min(), std::numeric_limits<I32>::max());
	std::uniform_int_distribution<I64> Random::uniI64(std::numeric_limits<I64>::min(), std::numeric_limits<I64>::max());
	std::uniform_int_distribution<UI16> Random::uniUI16(std::numeric_limits<UI16>::min(), std::numeric_limits<UI16>::max());
	std::uniform_int_distribution<UI32> Random::uniUI32(std::numeric_limits<UI32>::min(), std::numeric_limits<UI32>::max());
	std::uniform_int_distribution<UI64> Random::uniUI64(std::numeric_limits<UI64>::min(), std::numeric_limits<UI64>::max());

	void Text(float x, float y, float z, std::string str, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
	{
		glPushAttrib(GL_CURRENT_BIT);

		glColor4f(r, g, b, a);

		glRasterPos3f(x, y, z);
		for (int i = 0; i < str.size(); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);

		glPopAttrib();

		GL_CHECK_ERROR;
	}

	GLuint glCreateBuffer()
	{
		GLuint id;
		glCreateBuffers(1, &id);
		return id;
	}

	GLuint glCreateVertexArray()
	{
		GLuint id;
		glCreateVertexArrays(1, &id);
		return id;
	}

	GLuint glCreateSampler()
	{
		GLuint id;
		glCreateSamplers(1, &id);
		return id;
	}

	GLuint glCreateTexture(GLenum target)
	{
		GLuint id;
		glCreateTextures(target, 1, &id);
		return id;
	}

	GLuint glCreateFramebuffer()
	{
		GLuint id;
		glCreateFramebuffers(1, &id);
		return id;
	}

	GLObject::GLObject(GLuint id, Delete1 delete1) : id(id), delete1(delete1), delete2(nullptr), begin(false)
	{
		GL_CHECK_ERROR;
	}

	GLObject::GLObject(GLuint id, Delete2 delete2) : id(id), delete1(nullptr), delete2(delete2), begin(false)
	{
		GL_CHECK_ERROR;
	}

	GLObject::~GLObject() noexcept(false)
	{
		if (delete1)
			delete1(id);
		else
			delete2(1, &id);

		GL_CHECK_ERROR;
		id = 0;
	}
};
