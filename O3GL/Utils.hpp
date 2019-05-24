#pragma once

// std
#include <iostream>
#include <iomanip>
#include <string>
#include <exception>
#include <memory>

// c++
#include <cassert>

// GL
#include <GL/glew.h>
#include "GL/freeglut.h"

// O3GL 
#include "Math.hpp"

//
namespace O3GL
{
	// Exception
	class Exception : public std::exception
	{
	protected:
		std::string file;
		int line;
		std::string msg;

	public:
		Exception(const std::string& file, int line, const std::string& msg) : file(file), line(line), msg(msg) {}
		virtual const char* what() const throw() { return ("Exception at: " + file + ", " + std::to_string(line) + " - " + msg).c_str(); }
	};
};

#define EXCEPTION(msg) throw O3GL::Exception(std::string(__FILE__), __LINE__, std::string(msg));
#define ASSERT(condition, msg) if ( !(condition) ) EXCEPTION(msg);
#define VALID_FLOAT(v) !(std::isnan(v) || std::isinf(v))
#define CLAMP(x, l, h) std::min(std::max(x, l), h)
#define GL_CHECK_ERROR \
{\
	GLenum errCode = glGetError();\
	if (errCode != GL_NO_ERROR)\
	{\
		const GLubyte *errString;\
		errString = gluErrorString(errCode);\
		EXCEPTION("GL error: " + std::string((char*)errString));\
	}\
}\

namespace O3GL
{
	// Draw Text
	void Text(float x, float y, std::string str, GLfloat r = 1.f, GLfloat g = 1.f, GLfloat b = 1.f, GLfloat a = 1.f);

	// Common GL Create and Delete object function
	typedef void(*Create) (GLsizei, GLuint*);
	typedef void(*Delete1) (GLuint);
	typedef void(*Delete2) (GLsizei, const GLuint*);

	//
	GLuint glCreateBuffer();
	GLuint glCreateVertexArray();
	GLuint glCreateTexture(GLenum target);
	GLuint glCreateFramebuffer();

	//
	class Object
	{
	public:
		Object(GLuint id, Delete1 delete1);
		Object(GLuint id, Delete2 delete2);
		~Object();
		operator const GLuint() const { return id; }

	protected:
		GLuint id;
		Delete1 delete1;
		Delete2 delete2;
	};

	template<class T>
	class Handle
	{
	public:
		Handle(T* t = nullptr) : obj(t) {};
		T* operator ->() { return obj.get{} }
		const T* operator ->() const { return obj.get{} }
		operator const GLuint() const { return GLuint(*obj); }

	protected:
		std::shared_ptr<T> obj;
	};
};