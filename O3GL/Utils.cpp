// O3GL
#include "Utils.hpp"

// 
namespace O3GL
{
	void Text(float x, float y, std::string str, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
	{
		glColor4f(r, g, b, a);

		glRasterPos2f(x, y);
		for (int i = 0; i < str.size(); i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);

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

	Object::Object(GLuint id, Delete1 delete1) : id(id), delete1(delete1), delete2(nullptr)
	{
		GL_CHECK_ERROR;
	}

	Object::Object(GLuint id, Delete2 delete2) : id(id), delete1(nullptr), delete2(delete2)
	{
		GL_CHECK_ERROR;
	}

	Object::~Object()
	{
		if (delete1)
			delete1(id);
		else
			delete2(1, &id);

		GL_CHECK_ERROR;
		id = 0;
	}
};
