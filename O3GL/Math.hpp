#pragma once

// std
#include <iostream>
#include <iomanip>
#include <random>

// c++
#ifndef _USE_MATH_DEFINES
	#define _USE_MATH_DEFINES
#endif
#include <cmath>

// GL
#include <glm/ext.hpp> 

// 
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

namespace O3GL
{
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

	// Rand
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
};

//
template<class T, int N>
std::ostream & operator << (std::ostream &out, const O3GL::_Vec<T, N> &v)
{
	out << "Vec<" << std::setw(2) << N << ">: [";
	for (int i = 0; i < N; ++i)
		out << std::setprecision(5) << std::setw(8) << v[i];
	out << "]" << std::endl;
	return out;
}

template<class T, int R, int C >
std::ostream & operator << (std::ostream &out, const O3GL::_Mat<T, R, C> &m)
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

namespace O3GL
{
	template<>
	static inline R32 Random::UniformReal<R32>()
	{
		return uniR32(generator);
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
	static inline R64 Random::UniformReal<R64>()
	{
		return uniR64(generator);
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

	template<>
	static inline UI64 Random::UniformInt<UI64>()
	{
		return uniUI64(generator);
	}

	template<class T>
	static inline T Random::UniformReal(T minV, T maxV)
	{
		std::uniform_real_distribution<T> uniR (minV, maxV);
		return uniR(generator);
	}

	template<class T>
	static inline T Random::UniformInt(T minV, T maxV)
	{
		std::uniform_int_distribution<T> uniI(minV, maxV);
		return uniI(generator);
	}
};

