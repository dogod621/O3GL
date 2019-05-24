#pragma once

// O3GL
#include "Utils.hpp"

// 
namespace O3GL
{
	//
	class _Buffer : public Object
	{
	public:
		_Buffer() : Object(glCreateBuffer(), glDeleteBuffers) {}

		template<class T>
		T GetInfo(GLenum pname) const;

		template<class T>
		void Data(const std::vector<T>& data, GLenum usage) const;

		template<class T>
		void Data(const std::size_t& size, GLenum usage) const;

		template<class T>
		void SubData(std::size_t offset, const std::vector<T>& data) const;

		template<class T>
		std::vector<T> GetSubData(std::size_t offset, std::size_t size) const;

		template<class T>
		T* Map(GLenum access) const;

		GLboolean Unmap() const;

		template<class T>
		T* MapRange(std::size_t offset, std::size_t length, GLbitfield access) const;

		template<class T>
		void FlushMapRange(std::size_t offset, std::size_t length, GLbitfield access) const;

	public:
		template<>
		GLint GetInfo<GLint>(GLenum pname) const;

		template<>
		GLint64 GetInfo<GLint64>(GLenum pname) const;
	};

	//
	class Buffer : public Handle<_Buffer>
	{
	public:
		Buffer() : Handle<_Buffer>(new _Buffer()) {}
	};

	//
	template<>
	GLint _Buffer::GetInfo<GLint>(GLenum pname) const
	{
		GLint ri(0);
		glGetNamedBufferParameteriv(*this, pname, &ri);
		GL_CHECK_ERROR;
		return ri;
	}

	template<>
	GLint64 _Buffer::GetInfo<GLint64>(GLenum pname) const
	{
		GLint64 ri(0);
		glGetNamedBufferParameteri64v(*this, pname, &ri);
		GL_CHECK_ERROR;
		return ri;
	}

	template<class T>
	void _Buffer::Data(const std::vector<T>& data, GLenum usage) const
	{
		glNamedBufferData(*this, data.size() * sizeof(T), (const void *)&data[0], usage);
		GL_CHECK_ERROR;
	}

	template<class T>
	void _Buffer::Data(const std::size_t& size, GLenum usage) const
	{
		glNamedBufferData(*this, size * sizeof(T), 0, usage);
		GL_CHECK_ERROR;
	}

	template<class T>
	void _Buffer::SubData(std::size_t offset, const std::vector<T>& data) const
	{
		glNamedBufferSubData(*this, offset * sizeof(T), data.size() * sizeof(T), (const void *)&data[0]);
		GL_CHECK_ERROR;
	}

	template<class T>
	std::vector<T> _Buffer::GetSubData(std::size_t offset, std::size_t size) const
	{
		std::vector<T> data;
		data.resize(size);
		glGetNamedBufferSubData(*this, offset * sizeof(T), data.size() * sizeof(T), (void *)&data[0]);
		GL_CHECK_ERROR;
		return data;
	}

	template<class T>
	T* _Buffer::Map(GLenum access) const
	{
		void* rp = glMapNamedBuffer(*this, access);
		GL_CHECK_ERROR;
		return (T*)rp;
	}

	template<class T>
	T* _Buffer::MapRange(std::size_t offset, std::size_t length, GLbitfield access) const
	{
		void* rp = glMapNamedBufferRange(*this, offset * sizeof(T), length * sizeof(T), access);
		GL_CHECK_ERROR;
		return rp;
	}

	template<class T>
	void _Buffer::FlushMapRange(std::size_t offset, std::size_t length, GLbitfield access) const
	{
		glFlushMappedNamedBufferRange(*this, offset * sizeof(T), length * sizeof(T));
		GL_CHECK_ERROR;
	}
};