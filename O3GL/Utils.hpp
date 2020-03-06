#pragma once

// std
#include <iostream>
#include <iomanip>
#include <string>
#include <exception>
#include <memory>
#include <mutex>
#include <random>

// c++
#include <cmath>

// GL
#include "GL/glew.h"
#include "GL/freeglut.h"
#define GLM_FORCE_RADIANS
#include "glm/ext.hpp"

// MACROS
#define FG_R std::string("\033[31m") // red
#define FG_G std::string("\033[32m") // green
#define FG_Y std::string("\033[33m") // yellow
#define FG_B std::string("\033[34m") // blue
#define FG_M std::string("\033[35m") // magenta
#define FG_C std::string("\033[36m") // cyan
#define FG_W std::string("\033[37m") // white
#define FG_N std::string("\033[39m")
#define BG_R std::string("\033[41m")
#define BG_G std::string("\033[42m")
#define BG_Y std::string("\033[43m")
#define BG_B std::string("\033[44m")
#define BG_M std::string("\033[45m")
#define BG_C std::string("\033[46m") 
#define BG_W std::string("\033[47m") 
#define BG_N std::string("\033[49m")

#define INFO_MESSAGE(file, line, func, message) (FG_W + std::string(message) + FG_N + " " + FG_G + std::string(file) + FG_N + " " + FG_B + std::to_string(line) + FG_N + " " + FG_C + std::string(func) + FG_N + ".").c_str()
#define WARNING_MESSAGE(file, line, func, message) (BG_Y + FG_W + std::string(message) + FG_N + " " + FG_G + std::string(file) + FG_N + " " + FG_B + std::to_string(line) + FG_N + " " + FG_C + std::string(func) + FG_N + "." + BG_N).c_str()
#define ERROR_MESSAGE(file, line, func, message) (BG_R + FG_W + std::string(message) + FG_N + " " + FG_G + std::string(file) + FG_N + " " + FG_B + std::to_string(line) + FG_N + " " + FG_C + std::string(func) + FG_N + "." + BG_N).c_str()

#define CONCATENATE_DETAIL(x, y) x##y
#define CONCATENATE(x, y) CONCATENATE_DETAIL(x, y)

#define M_E_f			CONCATENATE(M_E,f)
#define M_LOG2E_f		CONCATENATE(M_LOG2E,f)
#define M_LOG10E_f		CONCATENATE(M_LOG10E,f)
#define M_LN2_f			CONCATENATE(M_LN2,f)
#define M_LN10_f		CONCATENATE(M_LN10,f)
#define M_PI_f			CONCATENATE(M_PI,f)
#define M_PI_2_f		CONCATENATE(M_PI_2,f)
#define M_PI_4_f		CONCATENATE(M_PI_4,f)
#define M_1_PI_f		CONCATENATE(M_1_PI,f)
#define M_2_PI_f		CONCATENATE(M_2_PI,f)
#define M_2_SQRTPI_f	CONCATENATE(M_2_SQRTPI,f)
#define M_SQRT2_f		CONCATENATE(M_SQRT2,f)
#define M_SQRT1_2_f		CONCATENATE(M_SQRT1_2,f)

#define THROW_EXCEPTION(message) {throw O3GL::Exception(__FILE__, __LINE__, __FUNCTION__, message);}
#define PRINT_ERROR(message) {std::lock_guard<std::mutex> guard(O3GL::Global::lock);std::cout << ERROR_MESSAGE(__FILE__, __LINE__, __FUNCTION__, message) << std::endl;}
#define PRINT_WARNING(message) {std::lock_guard<std::mutex> guard(O3GL::Global::lock);std::cout << WARNING_MESSAGE(__FILE__, __LINE__, __FUNCTION__, message) << std::endl;}
#define PRINT_INFO(message) {std::lock_guard<std::mutex> guard(O3GL::Global::lock);std::cerr << INFO_MESSAGE(__FILE__, __LINE__, __FUNCTION__, message) << std::endl;}
#define ASSERT(condition, msg) if ( !(condition) ) THROW_EXCEPTION(msg);
#define VALID_FLOAT(v) !(std::isnan(v) || std::isinf(v))
#define CLAMP(x, l, h) std::min(std::max(x, l), h)

#define GL_CHECK_ERROR \
{\
	GLenum errCode = glGetError();\
	if (errCode != GL_NO_ERROR)\
	{\
		const GLubyte *errString;\
		errString = gluErrorString(errCode);\
		THROW_EXCEPTION("GL error: " + std::string((char*)errString));\
	}\
}\

// O3GL
namespace O3GL
{
	template<class T>
	using PTR = std::shared_ptr<T>;

	template<class T>
	using CONST_PTR = std::shared_ptr<const T>;

	using Flag = unsigned int;
	using R32 = float;
	using R64 = double;

	using I8 = char;
	using I16 = short int;
	using I32 = int;
	using I64 = long long int;

	using UI8 = unsigned char;
	using UI16 = unsigned short int;
	using UI32 = unsigned int;
	using UI64 = unsigned long long int;

	template<class T, int N >
	using _Vec = glm::vec<N, T, glm::defaultp>;

	template<class T, int R, int C >
	using _Mat = glm::mat<R, C, T, glm::defaultp>;

	using Vec2 = _Vec<R32, 2>;
	using Vec3 = _Vec<R32, 3>;
	using Vec4 = _Vec<R32, 4>;

	using Vec2d = _Vec<R64, 2>;
	using Vec3d = _Vec<R64, 3>;
	using Vec4d = _Vec<R64, 4>;

	using Vec2i = _Vec<I32, 2>;
	using Vec3i = _Vec<I32, 3>;
	using Vec4i = _Vec<I32, 4>;

	using Vec2ui = _Vec<UI32, 2>;
	using Vec3ui = _Vec<UI32, 3>;
	using Vec4ui = _Vec<UI32, 4>;

	using Mat22 = _Mat<R32, 2, 2>;
	using Mat23 = _Mat<R32, 2, 3>;
	using Mat24 = _Mat<R32, 2, 4>;
	using Mat32 = _Mat<R32, 3, 2>;
	using Mat33 = _Mat<R32, 3, 3>;
	using Mat34 = _Mat<R32, 3, 4>;
	using Mat42 = _Mat<R32, 4, 2>;
	using Mat43 = _Mat<R32, 4, 3>;
	using Mat44 = _Mat<R32, 4, 4>;

	using Mat22d = _Mat<R64, 2, 2>;
	using Mat23d = _Mat<R64, 2, 3>;
	using Mat24d = _Mat<R64, 2, 4>;
	using Mat32d = _Mat<R64, 3, 2>;
	using Mat33d = _Mat<R64, 3, 3>;
	using Mat34d = _Mat<R64, 3, 4>;
	using Mat42d = _Mat<R64, 4, 2>;
	using Mat43d = _Mat<R64, 4, 3>;
	using Mat44d = _Mat<R64, 4, 4>;

	using Mat22i = _Mat<I32, 2, 2>;
	using Mat23i = _Mat<I32, 2, 3>;
	using Mat24i = _Mat<I32, 2, 4>;
	using Mat32i = _Mat<I32, 3, 2>;
	using Mat33i = _Mat<I32, 3, 3>;
	using Mat34i = _Mat<I32, 3, 4>;
	using Mat42i = _Mat<I32, 4, 2>;
	using Mat43i = _Mat<I32, 4, 3>;
	using Mat44i = _Mat<I32, 4, 4>;

	using Mat22ui = _Mat<UI32, 2, 2>;
	using Mat23ui = _Mat<UI32, 2, 3>;
	using Mat24ui = _Mat<UI32, 2, 4>;
	using Mat32ui = _Mat<UI32, 3, 2>;
	using Mat33ui = _Mat<UI32, 3, 3>;
	using Mat34ui = _Mat<UI32, 3, 4>;
	using Mat42ui = _Mat<UI32, 4, 2>;
	using Mat43ui = _Mat<UI32, 4, 3>;
	using Mat44ui = _Mat<UI32, 4, 4>;

	class Global
	{
	public:
		static std::mutex lock;
	};

	class Exception : public std::exception
	{
	protected:
		std::string message;

	public:
		Exception(const char* file, int line, const char* func, const std::string& message_)
			: std::exception()
		{
			message = ERROR_MESSAGE(file, line, func, message_);
		}
		const char* what() const { return message.c_str(); }
	};

	class Random
	{
	public:
		template<class T>
		static inline T UniformReal();

		template<class T>
		static inline T UniformInt();

		template<class T>
		static inline T UniformReal(T minV, T maxV);

		template<class T>
		static inline T UniformInt(T minV, T maxV);

	protected:
		static std::random_device randomDevice;
		static std::mt19937_64 generator;
		static std::uniform_real_distribution<R32> uniR32;
		static std::uniform_real_distribution<R64> uniR64;
		static std::uniform_int_distribution<I16> uniI16;
		static std::uniform_int_distribution<I32> uniI32;
		static std::uniform_int_distribution<I64> uniI64;
		static std::uniform_int_distribution<UI16> uniUI16;
		static std::uniform_int_distribution<UI32> uniUI32;
		static std::uniform_int_distribution<UI64> uniUI64;
	};

	// Draw Text
	void Text(float x, float y, float z, std::string str, GLfloat r = 1.f, GLfloat g = 1.f, GLfloat b = 1.f, GLfloat a = 1.f);

	// Common GL Create and Delete object function
	typedef void(*Create) (GLsizei, GLuint*);
	typedef void(*Delete1) (GLuint);
	typedef void(*Delete2) (GLsizei, const GLuint*);

	//
	GLuint glCreateBuffer();
	GLuint glCreateVertexArray();
	GLuint glCreateSampler();
	GLuint glCreateTexture(GLenum target);
	GLuint glCreateFramebuffer();

	//
	class GLObject
	{
	public:
		GLObject(GLuint id, Delete1 delete1);
		GLObject(GLuint id, Delete2 delete2);
		~GLObject() noexcept(false);
		operator const GLuint() const { return id; }

	protected:
		bool begin;
		GLuint id;
		Delete1 delete1;
		Delete2 delete2;
	};

	template<class T>
	class GLHandle
	{
	public:
		GLHandle(T* t = nullptr) : obj(t) {};
		T* operator ->() { return obj.get(); }
		const T* operator ->() const { return obj.get(); }
		operator const GLuint() const { return GLuint(*obj); }

	protected:
		PTR<T> obj;
	};

	// Template Definitions
	template<class T, int N>
	std::ostream& operator << (std::ostream& out, const _Vec<T, N>& v)
	{
		out << "Vec<" << std::setw(2) << N << ">: [";
		for (int i = 0; i < N; ++i)
			out << std::setprecision(5) << std::setw(8) << v[i];
		out << "]" << std::endl;
		return out;
	}

	template<class T, int R, int C >
	std::ostream& operator << (std::ostream& out, const _Mat<T, R, C>& m)
	{
		out << "Mat<" << std::setw(2) << R << ", " << std::setw(2) << C << ">: [" << std::endl;
		for (int i = 0; i < R; ++i)
		{
			for (int j = 0; j < C; ++j)
				out << std::setprecision(5) << std::setw(8) << m[i][j];
			out << std::endl;
		}
		out << "]" << std::endl;
		return out;
	}

	template<>
	static inline R32 Random::UniformReal<R32>()
	{
		return uniR32(generator);
	}

	template<>
	static inline R64 Random::UniformReal<R64>()
	{
		return uniR64(generator);
	}

	template<>
	static inline I16 Random::UniformInt<I16>()
	{
		return uniI16(generator);
	}

	template<>
	static inline I32 Random::UniformInt<I32>()
	{
		return uniI32(generator);
	}

	template<>
	static inline I64 Random::UniformInt<I64>()
	{
		return uniI64(generator);
	}

	template<>
	static inline UI16 Random::UniformInt<UI16>()
	{
		return uniUI16(generator);
	}

	template<>
	static inline UI32 Random::UniformInt<UI32>()
	{
		return uniUI32(generator);
	}

	template<>
	static inline UI64 Random::UniformInt<UI64>()
	{
		return uniUI64(generator);
	}

	template<>
	static inline Vec2 Random::UniformReal<Vec2>()
	{
		return Vec2(uniR32(generator), uniR32(generator));
	}

	template<>
	static inline Vec3 Random::UniformReal<Vec3>()
	{
		return Vec3(uniR32(generator), uniR32(generator), uniR32(generator));
	}

	template<>
	static inline Vec4 Random::UniformReal<Vec4>()
	{
		return Vec4(uniR32(generator), uniR32(generator), uniR32(generator), uniR32(generator));
	}

	template<>
	static inline Vec2d Random::UniformReal<Vec2d>()
	{
		return Vec2d(uniR64(generator), uniR64(generator));
	}

	template<>
	static inline Vec3d Random::UniformReal<Vec3d>()
	{
		return Vec3d(uniR64(generator), uniR64(generator), uniR64(generator));
	}

	template<>
	static inline Vec4d Random::UniformReal<Vec4d>()
	{
		return Vec4d(uniR64(generator), uniR64(generator), uniR64(generator), uniR64(generator));
	}

	template<>
	static inline Vec2i Random::UniformInt<Vec2i>()
	{
		return Vec2i(uniI32(generator), uniI32(generator));
	}

	template<>
	static inline Vec3i Random::UniformInt<Vec3i>()
	{
		return Vec3i(uniI32(generator), uniI32(generator), uniI32(generator));
	}

	template<>
	static inline Vec4i Random::UniformInt<Vec4i>()
	{
		return Vec4i(uniI32(generator), uniI32(generator), uniI32(generator), uniI32(generator));
	}

	template<>
	static inline Vec2ui Random::UniformInt<Vec2ui>()
	{
		return Vec2ui(uniUI32(generator), uniUI32(generator));
	}

	template<>
	static inline Vec3ui Random::UniformInt<Vec3ui>()
	{
		return Vec3ui(uniUI32(generator), uniUI32(generator), uniUI32(generator));
	}

	template<>
	static inline Vec4ui Random::UniformInt<Vec4ui>()
	{
		return Vec4ui(uniUI32(generator), uniUI32(generator), uniUI32(generator), uniUI32(generator));
	}

	template<class T>
	static inline T Random::UniformReal(T minV, T maxV)
	{
		std::uniform_real_distribution<T> uniR(minV, maxV);
		return uniR(generator);
	}

	template<class T>
	static inline T Random::UniformInt(T minV, T maxV)
	{
		std::uniform_int_distribution<T> uniI(minV, maxV);
		return uniI(generator);
	}
};
