#pragma once

// std
#include <vector>

// O3GL
#include "O3GL/Utils.hpp"
#include "O3GL/Shader.hpp"

//
namespace O3GL
{
	class Program : public GLHandle
	{
	public:
		Program() : GLHandle(new GLObject(glCreateProgram(), glDeleteProgram)) {}

	public:
		void Begin() const;

		void End() const;

		template<class T>
		T GetInfo(GLenum pname) const;

		std::tuple<GLenum, std::vector<GLbyte>> GetBinary() const;

		void LoadBinary(const std::tuple<GLenum, std::vector<GLbyte>>& binary) const;

		std::string GetLog() const;

		std::tuple<GLboolean, std::string> Validate() const;

		void AttachShader(const Shader& shader) const;

		void DetachShader(const Shader& shader) const;

		std::tuple<GLboolean, std::string> Link() const;

		void BindAttribLocation(GLuint index, const std::string& name) const;

		GLint GetAttribLocation(const std::string& name) const;

		GLint GetUniformLocation(const std::string& name) const;

		// Pass Var
		template<class GLType, int n		> void Uniform(GLint location, GLType v0															) const;
		template<class GLType, int n		> void Uniform(GLint location, GLType v0, GLType v1													) const;
		template<class GLType, int n		> void Uniform(GLint location, GLType v0, GLType v1, GLType v2										) const;
		template<class GLType, int n		> void Uniform(GLint location, GLType v0, GLType v1, GLType v2, GLType v3							) const;
		template<class GLType, int n		> void Uniform(GLint location, const Vec2& v														) const;
		template<class GLType, int n		> void Uniform(GLint location, const Vec3& v														) const;
		template<class GLType, int n		> void Uniform(GLint location, const Vec4& v														) const;	
		template<class GLType, int n		> void Uniform(GLint location, const Vec2i& v														) const;
		template<class GLType, int n		> void Uniform(GLint location, const Vec3i& v														) const;
		template<class GLType, int n		> void Uniform(GLint location, const Vec4i& v														) const;
		template<class GLType, int n		> void Uniform(GLint location, const Vec2ui& v														) const;
		template<class GLType, int n		> void Uniform(GLint location, const Vec3ui& v														) const;
		template<class GLType, int n		> void Uniform(GLint location, const Vec4ui& v														) const;

		template<class GLType, int n		> void Uniform(const std::string &name, GLType v0													) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), v0						); GL_CHECK_ERROR; }
		template<class GLType, int n		> void Uniform(const std::string &name, GLType v0, GLType v1										) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), v0, v1					); GL_CHECK_ERROR; }
		template<class GLType, int n		> void Uniform(const std::string &name, GLType v0, GLType v1, GLType v2								) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), v0, v1, v2				); GL_CHECK_ERROR; }
		template<class GLType, int n		> void Uniform(const std::string &name, GLType v0, GLType v1, GLType v2, GLType v3					) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), v0, v1, v3				); GL_CHECK_ERROR; }
		template<class GLType, int n		> void Uniform(const std::string &name, const Vec2& v												) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int n		> void Uniform(const std::string &name, const Vec3& v												) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int n		> void Uniform(const std::string &name, const Vec4& v												) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int n		> void Uniform(const std::string &name, const Vec2i& v												) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int n		> void Uniform(const std::string &name, const Vec3i& v												) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int n		> void Uniform(const std::string &name, const Vec4i& v												) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int n		> void Uniform(const std::string &name, const Vec2ui& v												) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int n		> void Uniform(const std::string &name, const Vec3ui& v												) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int n		> void Uniform(const std::string &name, const Vec4ui& v												) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }


		// Pass Arr
		template<class GLType, int n		> void Uniform(GLint location, const GLType *value													) const;
		template<class GLType, int n		> void Uniform(GLint location, GLsizei count, const GLType *value									) const;	
		template<class GLType, int n		> void Uniform(GLint location, const std::vector<Vec2>& v											) const;
		template<class GLType, int n		> void Uniform(GLint location, const std::vector<Vec3>& v											) const;
		template<class GLType, int n		> void Uniform(GLint location, const std::vector<Vec4>& v											) const;
		template<class GLType, int n		> void Uniform(GLint location, const std::vector<Vec2i>& v											) const;
		template<class GLType, int n		> void Uniform(GLint location, const std::vector<Vec3i>& v											) const;
		template<class GLType, int n		> void Uniform(GLint location, const std::vector<Vec4i>& v											) const;
		template<class GLType, int n		> void Uniform(GLint location, const std::vector<Vec2ui>& v											) const;
		template<class GLType, int n		> void Uniform(GLint location, const std::vector<Vec3ui>& v											) const;
		template<class GLType, int n		> void Uniform(GLint location, const std::vector<Vec4ui>& v											) const;

		template<class GLType, int n		> void Uniform(const std::string &name, const GLType *value											) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), value					); GL_CHECK_ERROR; }
		template<class GLType, int n		> void Uniform(const std::string &name, GLsizei count, const GLType *value							) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), count, value			); GL_CHECK_ERROR; }
		template<class GLType, int n		> void Uniform(const std::string &name, const std::vector<Vec2>& v									) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int n		> void Uniform(const std::string &name, const std::vector<Vec3>& v									) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int n		> void Uniform(const std::string &name, const std::vector<Vec4>& v									) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int n		> void Uniform(const std::string &name, const std::vector<Vec2i>& v									) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int n		> void Uniform(const std::string &name, const std::vector<Vec3i>& v									) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int n		> void Uniform(const std::string &name, const std::vector<Vec4i>& v									) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int n		> void Uniform(const std::string &name, const std::vector<Vec2ui>& v								) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int n		> void Uniform(const std::string &name, const std::vector<Vec3ui>& v								) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int n		> void Uniform(const std::string &name, const std::vector<Vec4ui>& v								) const { Uniform<GLType, n		>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }


		// Pass MatArr
		template<class GLType, int r, int c	> void Uniform(GLint location, const GLType *value													) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, GLsizei count, const GLType *value									) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, GLsizei count, GLboolean transpose, const GLType *value				) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const Mat22& v														) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const Mat23& v														) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const Mat24& v														) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const Mat32& v														) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const Mat33& v														) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const Mat34& v														) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const Mat42& v														) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const Mat43& v														) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const Mat44& v														) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const Mat22& v, GLboolean transpose									) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const Mat23& v, GLboolean transpose									) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const Mat24& v, GLboolean transpose									) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const Mat32& v, GLboolean transpose									) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const Mat33& v, GLboolean transpose									) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const Mat34& v, GLboolean transpose									) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const Mat42& v, GLboolean transpose									) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const Mat43& v, GLboolean transpose									) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const Mat44& v, GLboolean transpose									) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const std::vector<Mat22>& v											) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const std::vector<Mat23>& v											) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const std::vector<Mat24>& v											) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const std::vector<Mat32>& v											) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const std::vector<Mat33>& v											) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const std::vector<Mat34>& v											) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const std::vector<Mat42>& v											) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const std::vector<Mat43>& v											) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const std::vector<Mat44>& v											) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const std::vector<Mat22>& v, GLboolean transpose						) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const std::vector<Mat23>& v, GLboolean transpose						) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const std::vector<Mat24>& v, GLboolean transpose						) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const std::vector<Mat32>& v, GLboolean transpose						) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const std::vector<Mat33>& v, GLboolean transpose						) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const std::vector<Mat34>& v, GLboolean transpose						) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const std::vector<Mat42>& v, GLboolean transpose						) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const std::vector<Mat43>& v, GLboolean transpose						) const;
		template<class GLType, int r, int c	> void Uniform(GLint location, const std::vector<Mat44>& v, GLboolean transpose						) const;

		template<class GLType, int r, int c	> void Uniform(const std::string &name, const GLType *value											) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), value					); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, GLsizei count, const GLType *value							) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), count, value			); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, GLsizei count, GLboolean transpose, const GLType *value		) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), count, transpose, value	); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const Mat22& v												) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const Mat23& v												) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const Mat24& v												) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const Mat32& v												) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const Mat33& v												) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const Mat34& v												) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const Mat42& v												) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const Mat43& v												) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const Mat44& v												) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const Mat22& v, GLboolean transpose							) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v, transpose			); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const Mat23& v, GLboolean transpose							) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v, transpose			); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const Mat24& v, GLboolean transpose							) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v, transpose			); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const Mat32& v, GLboolean transpose							) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v, transpose			); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const Mat33& v, GLboolean transpose							) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v, transpose			); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const Mat34& v, GLboolean transpose							) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v, transpose			); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const Mat42& v, GLboolean transpose							) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v, transpose			); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const Mat43& v, GLboolean transpose							) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v, transpose			); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const Mat44& v, GLboolean transpose							) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v, transpose			); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const std::vector<Mat22>& v									) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const std::vector<Mat23>& v									) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const std::vector<Mat24>& v									) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const std::vector<Mat32>& v									) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const std::vector<Mat33>& v									) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const std::vector<Mat34>& v									) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const std::vector<Mat42>& v									) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const std::vector<Mat43>& v									) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const std::vector<Mat44>& v									) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v						); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const std::vector<Mat22>& v, GLboolean transpose			) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v, transpose			); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const std::vector<Mat23>& v, GLboolean transpose			) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v, transpose			); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const std::vector<Mat24>& v, GLboolean transpose			) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v, transpose			); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const std::vector<Mat32>& v, GLboolean transpose			) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v, transpose			); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const std::vector<Mat33>& v, GLboolean transpose			) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v, transpose			); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const std::vector<Mat34>& v, GLboolean transpose			) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v, transpose			); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const std::vector<Mat42>& v, GLboolean transpose			) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v, transpose			); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const std::vector<Mat43>& v, GLboolean transpose			) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v, transpose			); GL_CHECK_ERROR; }
		template<class GLType, int r, int c	> void Uniform(const std::string &name, const std::vector<Mat44>& v, GLboolean transpose			) const { Uniform<GLType, r, c	>(GetUniformLocation(name.c_str()), v, transpose			); GL_CHECK_ERROR; }
	
	public:
		template<>
		GLint GetInfo<GLint>(GLenum pname) const;

		template<>
		GLboolean GetInfo<GLboolean>(GLenum pname) const;


		// Pass Var
		// Pass Var		-		GLfloat
		// Pass Var		-		GLfloat	, 1
		template<> void Uniform<GLfloat	, 1		>(GLint location, GLfloat v0												) const { glProgramUniform1f			(*this, location, v0										); GL_CHECK_ERROR; }
		
		// Pass Var		-		GLfloat	, 2
		template<> void Uniform<GLfloat	, 2		>(GLint location, GLfloat v0, GLfloat v1									) const { glProgramUniform2f			(*this, location, v0, v1									); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 2		>(GLint location, const Vec2& v												) const { glProgramUniform2f			(*this, location, v[0], v[1]								); GL_CHECK_ERROR; }
		
		// Pass Var		-		GLfloat	, 3
		template<> void Uniform<GLfloat	, 3		>(GLint location, GLfloat v0, GLfloat v1, GLfloat v2						) const { glProgramUniform3f			(*this, location, v0, v1, v2								); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 3		>(GLint location, const Vec3& v												) const { glProgramUniform3f			(*this, location, v[0], v[1], v[2]							); GL_CHECK_ERROR; }
		
		// Pass Var		-		GLfloat	, 4
		template<> void Uniform<GLfloat	, 4		>(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3			) const { glProgramUniform4f			(*this, location, v0, v1, v2, v3							); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 4		>(GLint location, const Vec4& v												) const { glProgramUniform4f			(*this, location, v[0], v[1], v[2], v[3]					); GL_CHECK_ERROR; }
		
		// Pass Var		-		GLint
		// Pass Var		-		GLint	, 1
		template<> void Uniform<GLint	, 1		>(GLint location, GLint v0													) const { glProgramUniform1i			(*this, location, v0										); GL_CHECK_ERROR; }
		
		// Pass Var		-		GLint	, 2
		template<> void Uniform<GLint	, 2		>(GLint location, GLint v0, GLint v1										) const { glProgramUniform2i			(*this, location, v0, v1									); GL_CHECK_ERROR; }
		template<> void Uniform<GLint	, 2		>(GLint location, const Vec2i& v											) const { glProgramUniform2i			(*this, location, v[0], v[1]								); GL_CHECK_ERROR; }
		
		// Pass Var		-		GLint	, 3
		template<> void Uniform<GLint	, 3		>(GLint location, GLint v0, GLint v1, GLint v2								) const { glProgramUniform3i			(*this, location, v0, v1, v2								); GL_CHECK_ERROR; }
		template<> void Uniform<GLint	, 3		>(GLint location, const Vec3i& v											) const { glProgramUniform3i			(*this, location, v[0], v[1], v[2]							); GL_CHECK_ERROR; }
		
		// Pass Var		-		GLint	, 4
		template<> void Uniform<GLint	, 4		>(GLint location, GLint v0, GLint v1, GLint v2, GLint v3					) const { glProgramUniform4i			(*this, location, v0, v1, v2, v3							); GL_CHECK_ERROR; }
		template<> void Uniform<GLint	, 4		>(GLint location, const Vec4i& v											) const { glProgramUniform4i			(*this, location, v[0], v[1], v[2], v[3]					); GL_CHECK_ERROR; }
		
		// Pass Var		-		GLuint
		// Pass Var		-		GLuint	, 1
		template<> void Uniform<GLuint	, 1		>(GLint location, GLuint v0													) const { glProgramUniform1ui			(*this, location, v0										); GL_CHECK_ERROR; }
		
		// Pass Var		-		GLuint	, 2
		template<> void Uniform<GLuint	, 2		>(GLint location, GLuint v0, GLuint v1										) const { glProgramUniform2ui			(*this, location, v0, v1									); GL_CHECK_ERROR; }
		template<> void Uniform<GLuint	, 2		>(GLint location, const Vec2ui& v											) const { glProgramUniform2ui			(*this, location, v[0], v[1]								); GL_CHECK_ERROR; }
		
		// Pass Var		-		GLuint	, 3
		template<> void Uniform<GLuint	, 3		>(GLint location, GLuint v0, GLuint v1, GLuint v2							) const { glProgramUniform3ui			(*this, location, v0, v1, v2								); GL_CHECK_ERROR; }
		template<> void Uniform<GLuint	, 3		>(GLint location, const Vec3ui& v											) const { glProgramUniform3ui			(*this, location, v[0], v[1], v[2]							); GL_CHECK_ERROR; }
		
		// Pass Var		-		GLuint	, 4
		template<> void Uniform<GLuint	, 4		>(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3				) const { glProgramUniform4ui			(*this, location, v0, v1, v2, v3							); GL_CHECK_ERROR; }
		template<> void Uniform<GLuint	, 4		>(GLint location, const Vec4ui& v											) const { glProgramUniform4ui			(*this, location, v[0], v[1], v[2], v[3]					); GL_CHECK_ERROR; }
		
		// Pass Arr
		// Pass Arr		-		GLfloat
		// Pass Arr		-		GLfloat	, 1
		template<> void Uniform<GLfloat	, 1		>(GLint location, const GLfloat *value										) const { glProgramUniform1fv			(*this, location, 1, value									); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 1		>(GLint location, GLsizei count, const GLfloat *value						) const { glProgramUniform1fv			(*this, location, count, value								); GL_CHECK_ERROR; }
		
		// Pass Arr		-		GLfloat	, 2
		template<> void Uniform<GLfloat	, 2		>(GLint location, const GLfloat *value										) const { glProgramUniform2fv			(*this, location, 1, value									); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 2		>(GLint location, GLsizei count, const GLfloat *value						) const { glProgramUniform2fv			(*this, location, count, value								); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 2		>(GLint location, const std::vector<Vec2>& v								) const { glProgramUniform2fv			(*this, location, (GLsizei)v.size(), &v[0][0]				); GL_CHECK_ERROR; }
		
		// Pass Arr		-		GLfloat	, 3
		template<> void Uniform<GLfloat	, 3		>(GLint location, const GLfloat *value										) const { glProgramUniform3fv			(*this, location, 1, value									); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 3		>(GLint location, GLsizei count, const GLfloat *value						) const { glProgramUniform3fv			(*this, location, count, value								); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 3		>(GLint location, const std::vector<Vec3>& v								) const { glProgramUniform3fv			(*this, location, (GLsizei)v.size(), &v[0][0]				); GL_CHECK_ERROR; }
		
		// Pass Arr		-		GLfloat	, 4
		template<> void Uniform<GLfloat	, 4		>(GLint location, const GLfloat *value										) const { glProgramUniform4fv			(*this, location, 1, value									); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 4		>(GLint location, GLsizei count, const GLfloat *value						) const { glProgramUniform4fv			(*this, location, count, value								); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 4		>(GLint location, const std::vector<Vec4>& v								) const { glProgramUniform4fv			(*this, location, (GLsizei)v.size(), &v[0][0]				); GL_CHECK_ERROR; }
		
		// Pass Arr		-		GLint
		// Pass Arr		-		GLint	, 1
		template<> void Uniform<GLint	, 1		>(GLint location, const GLint *value										) const { glProgramUniform1iv			(*this, location, 1, value									); GL_CHECK_ERROR; }
		template<> void Uniform<GLint	, 1		>(GLint location, GLsizei count, const GLint *value							) const { glProgramUniform1iv			(*this, location, count, value								); GL_CHECK_ERROR; }
		

		// Pass Arr		-		GLint	, 2
		template<> void Uniform<GLint	, 2		>(GLint location, const GLint *value										) const { glProgramUniform2iv			(*this, location, 1, value									); GL_CHECK_ERROR; }
		template<> void Uniform<GLint	, 2		>(GLint location, GLsizei count, const GLint *value							) const { glProgramUniform2iv			(*this, location, count, value								); GL_CHECK_ERROR; }
		template<> void Uniform<GLint	, 2		>(GLint location, const std::vector<Vec2i>& v								) const { glProgramUniform2iv			(*this, location, (GLsizei)v.size(), &v[0][0]				); GL_CHECK_ERROR; }
		

		// Pass Arr		-		GLint	, 3
		template<> void Uniform<GLint	, 3		>(GLint location, const GLint *value										) const { glProgramUniform3iv			(*this, location, 1, value									); GL_CHECK_ERROR; }
		template<> void Uniform<GLint	, 3		>(GLint location, GLsizei count, const GLint *value							) const { glProgramUniform3iv			(*this, location, count, value								); GL_CHECK_ERROR; }
		template<> void Uniform<GLint	, 3		>(GLint location, const std::vector<Vec3i>& v								) const { glProgramUniform3iv			(*this, location, (GLsizei)v.size(), &v[0][0]				); GL_CHECK_ERROR; }
		

		// Pass Arr		-		GLint	, 4
		template<> void Uniform<GLint	, 4		>(GLint location, const GLint *value										) const { glProgramUniform4iv			(*this, location, 1, value									); GL_CHECK_ERROR; }
		template<> void Uniform<GLint	, 4		>(GLint location, GLsizei count, const GLint *value							) const { glProgramUniform4iv			(*this, location, count, value								); GL_CHECK_ERROR; }
		template<> void Uniform<GLint	, 4		>(GLint location, const std::vector<Vec4i>& v								) const { glProgramUniform4iv			(*this, location, (GLsizei)v.size(), &v[0][0]				); GL_CHECK_ERROR; }
		
		// Pass Arr		-		GLuint
		// Pass Arr		-		GLuint	, 1
		template<> void Uniform<GLuint	, 1		>(GLint location, const GLuint *value										) const { glProgramUniform1uiv			(*this, location, 1, value									); GL_CHECK_ERROR; }
		template<> void Uniform<GLuint	, 1		>(GLint location, GLsizei count, const GLuint *value						) const { glProgramUniform1uiv			(*this, location, count, value								); GL_CHECK_ERROR; }
		
		// Pass Arr		-		GLuint	, 2
		template<> void Uniform<GLuint	, 2		>(GLint location, const GLuint *value										) const { glProgramUniform2uiv			(*this, location, 1, value									); GL_CHECK_ERROR; }
		template<> void Uniform<GLuint	, 2		>(GLint location, GLsizei count, const GLuint *value						) const { glProgramUniform2uiv			(*this, location, count, value								); GL_CHECK_ERROR; }
		template<> void Uniform<GLuint	, 2		>(GLint location, const std::vector<Vec2ui>& v								) const { glProgramUniform2uiv			(*this, location, (GLsizei)v.size(), &v[0][0]				); GL_CHECK_ERROR; }
		
		// Pass Arr		-		GLuint	, 3
		template<> void Uniform<GLuint	, 3		>(GLint location, const GLuint *value										) const { glProgramUniform3uiv			(*this, location, 1, value									); GL_CHECK_ERROR; }
		template<> void Uniform<GLuint	, 3		>(GLint location, GLsizei count, const GLuint *value						) const { glProgramUniform3uiv			(*this, location, count, value								); GL_CHECK_ERROR; }
		template<> void Uniform<GLuint	, 3		>(GLint location, const std::vector<Vec3ui>& v								) const { glProgramUniform3uiv			(*this, location, (GLsizei)v.size(), &v[0][0]				); GL_CHECK_ERROR; }
		
		// Pass Arr		-		GLuint	, 4
		template<> void Uniform<GLuint	, 4		>(GLint location, const GLuint *value										) const { glProgramUniform4uiv			(*this, location, 1, value									); GL_CHECK_ERROR; }
		template<> void Uniform<GLuint	, 4		>(GLint location, GLsizei count, const GLuint *value						) const { glProgramUniform4uiv			(*this, location, count, value								); GL_CHECK_ERROR; }
		template<> void Uniform<GLuint	, 4		>(GLint location, const std::vector<Vec4ui>& v								) const { glProgramUniform4uiv			(*this, location, (GLsizei)v.size(), &v[0][0]				); GL_CHECK_ERROR; }

		// Pass MatArr
		// Pass MatArr	-		GLfloat
		// Pass MatArr	-		GLfloat	, 2, 2
		template<> void Uniform<GLfloat	, 2, 2	>(GLint location, const GLfloat *value										) const { glProgramUniformMatrix2fv		(*this, location, 1, GL_FALSE, value						); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 2, 2	>(GLint location, GLsizei count, const GLfloat *value						) const { glProgramUniformMatrix2fv		(*this, location, count, GL_FALSE, value					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 2, 2	>(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value	) const { glProgramUniformMatrix2fv		(*this, location, count, transpose, value					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 2, 2	>(GLint location, const Mat22& v											) const { glProgramUniformMatrix2fv		(*this, location, 1, GL_FALSE, &v[0][0]						); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 2, 2	>(GLint location, const Mat22& v, GLboolean transpose						) const { glProgramUniformMatrix2fv		(*this, location, 1, transpose, &v[0][0]					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 2, 2	>(GLint location, const std::vector<Mat22>& v								) const { glProgramUniformMatrix2fv		(*this, location, (GLsizei)v.size(), GL_FALSE, &v[0][0][0]	); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 2, 2	>(GLint location, const std::vector<Mat22>& v, GLboolean transpose			) const { glProgramUniformMatrix2fv		(*this, location, (GLsizei)v.size(), transpose, &v[0][0][0]	); GL_CHECK_ERROR; }
		
		// Pass MatArr	-		GLfloat	, 2, 3
		template<> void Uniform<GLfloat	, 2, 3	>(GLint location, const GLfloat *value										) const { glProgramUniformMatrix2x3fv	(*this, location, 1, GL_FALSE, value						); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 2, 3	>(GLint location, GLsizei count, const GLfloat *value						) const { glProgramUniformMatrix2x3fv	(*this, location, count, GL_FALSE, value					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 2, 3	>(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value	) const { glProgramUniformMatrix2x3fv	(*this, location, count, transpose, value					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 2, 3	>(GLint location, const Mat23& v											) const { glProgramUniformMatrix2x3fv	(*this, location, 1, GL_FALSE, &v[0][0]						); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 2, 3	>(GLint location, const Mat23& v, GLboolean transpose						) const { glProgramUniformMatrix2x3fv	(*this, location, 1, transpose, &v[0][0]					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 2, 3	>(GLint location, const std::vector<Mat23>& v								) const { glProgramUniformMatrix2x3fv	(*this, location, (GLsizei)v.size(), GL_FALSE, &v[0][0][0]	); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 2, 3	>(GLint location, const std::vector<Mat23>& v, GLboolean transpose			) const { glProgramUniformMatrix2x3fv	(*this, location, (GLsizei)v.size(), transpose, &v[0][0][0]	); GL_CHECK_ERROR; }
		
		// Pass MatArr	-		GLfloat	, 2, 4
		template<> void Uniform<GLfloat	, 2, 4	>(GLint location, const GLfloat *value										) const { glProgramUniformMatrix2x4fv	(*this, location, 1, GL_FALSE, value						); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 2, 4	>(GLint location, GLsizei count, const GLfloat *value						) const { glProgramUniformMatrix2x4fv	(*this, location, count, GL_FALSE, value					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 2, 4	>(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value	) const { glProgramUniformMatrix2x4fv	(*this, location, count, transpose, value					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 2, 4	>(GLint location, const Mat24& v											) const { glProgramUniformMatrix2x4fv	(*this, location, 1, GL_FALSE, &v[0][0]						); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 2, 4	>(GLint location, const Mat24& v, GLboolean transpose						) const { glProgramUniformMatrix2x4fv	(*this, location, 1, transpose, &v[0][0]					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 2, 4	>(GLint location, const std::vector<Mat24>& v								) const { glProgramUniformMatrix2x4fv	(*this, location, (GLsizei)v.size(), GL_FALSE, &v[0][0][0]	); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 2, 4	>(GLint location, const std::vector<Mat24>& v, GLboolean transpose			) const { glProgramUniformMatrix2x4fv	(*this, location, (GLsizei)v.size(), transpose, &v[0][0][0]	); GL_CHECK_ERROR; }
		
		// Pass MatArr	-		GLfloat	, 3, 2
		template<> void Uniform<GLfloat	, 3, 2	>(GLint location, const GLfloat *value										) const { glProgramUniformMatrix3x2fv	(*this, location, 1, GL_FALSE, value						); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 3, 2	>(GLint location, GLsizei count, const GLfloat *value						) const { glProgramUniformMatrix3x2fv	(*this, location, count, GL_FALSE, value					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 3, 2	>(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value	) const { glProgramUniformMatrix3x2fv	(*this, location, count, transpose, value					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 3, 2	>(GLint location, const Mat32& v											) const { glProgramUniformMatrix3x2fv	(*this, location, 1, GL_FALSE, &v[0][0]						); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 3, 2	>(GLint location, const Mat32& v, GLboolean transpose						) const { glProgramUniformMatrix3x2fv	(*this, location, 1, transpose, &v[0][0]					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 3, 2	>(GLint location, const std::vector<Mat32>& v								) const { glProgramUniformMatrix3x2fv	(*this, location, (GLsizei)v.size(), GL_FALSE, &v[0][0][0]	); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 3, 2	>(GLint location, const std::vector<Mat32>& v, GLboolean transpose			) const { glProgramUniformMatrix3x2fv	(*this, location, (GLsizei)v.size(), transpose, &v[0][0][0]	); GL_CHECK_ERROR; }
		
		// Pass MatArr	-		GLfloat	, 3, 3
		template<> void Uniform<GLfloat	, 3, 3	>(GLint location, const GLfloat *value										) const { glProgramUniformMatrix3fv		(*this, location, 1, GL_FALSE, value						); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 3, 3	>(GLint location, GLsizei count, const GLfloat *value						) const { glProgramUniformMatrix3fv		(*this, location, count, GL_FALSE, value					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 3, 3	>(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value	) const { glProgramUniformMatrix3fv		(*this, location, count, transpose, value					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 3, 3	>(GLint location, const Mat33& v											) const { glProgramUniformMatrix3fv		(*this, location, 1, GL_FALSE, &v[0][0]						); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 3, 3	>(GLint location, const Mat33& v, GLboolean transpose						) const { glProgramUniformMatrix3fv		(*this, location, 1, transpose, &v[0][0]					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 3, 3	>(GLint location, const std::vector<Mat33>& v								) const { glProgramUniformMatrix3fv		(*this, location, (GLsizei)v.size(), GL_FALSE, &v[0][0][0]	); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 3, 3	>(GLint location, const std::vector<Mat33>& v, GLboolean transpose			) const { glProgramUniformMatrix3fv		(*this, location, (GLsizei)v.size(), transpose, &v[0][0][0]	); GL_CHECK_ERROR; }
		
		// Pass MatArr	-		GLfloat	, 3, 4
		template<> void Uniform<GLfloat	, 3, 4	>(GLint location, const GLfloat *value										) const { glProgramUniformMatrix3x4fv	(*this, location, 1, GL_FALSE, value						); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 3, 4	>(GLint location, GLsizei count, const GLfloat *value						) const { glProgramUniformMatrix3x4fv	(*this, location, count, GL_FALSE, value					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 3, 4	>(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value	) const { glProgramUniformMatrix3x4fv	(*this, location, count, transpose, value					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 3, 4	>(GLint location, const Mat34& v											) const { glProgramUniformMatrix3x4fv	(*this, location, 1, GL_FALSE, &v[0][0]						); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 3, 4	>(GLint location, const Mat34& v, GLboolean transpose						) const { glProgramUniformMatrix3x4fv	(*this, location, 1, transpose, &v[0][0]					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 3, 4	>(GLint location, const std::vector<Mat34>& v								) const { glProgramUniformMatrix3x4fv	(*this, location, (GLsizei)v.size(), GL_FALSE, &v[0][0][0]	); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 3, 4	>(GLint location, const std::vector<Mat34>& v, GLboolean transpose			) const { glProgramUniformMatrix3x4fv	(*this, location, (GLsizei)v.size(), transpose, &v[0][0][0]	); GL_CHECK_ERROR; }
		
		// Pass MatArr	-		GLfloat	, 4, 2
		template<> void Uniform<GLfloat	, 4, 2	>(GLint location, const GLfloat *value										) const { glProgramUniformMatrix4x2fv	(*this, location, 1, GL_FALSE, value						); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 4, 2	>(GLint location, GLsizei count, const GLfloat *value						) const { glProgramUniformMatrix4x2fv	(*this, location, count, GL_FALSE, value					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 4, 2	>(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value	) const { glProgramUniformMatrix4x2fv	(*this, location, count, transpose, value					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 4, 2	>(GLint location, const Mat42& v											) const { glProgramUniformMatrix4x2fv	(*this, location, 1, GL_FALSE, &v[0][0]						); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 4, 2	>(GLint location, const Mat42& v, GLboolean transpose						) const { glProgramUniformMatrix4x2fv	(*this, location, 1, transpose, &v[0][0]					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 4, 2	>(GLint location, const std::vector<Mat42>& v								) const { glProgramUniformMatrix4x2fv	(*this, location, (GLsizei)v.size(), GL_FALSE, &v[0][0][0]	); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 4, 2	>(GLint location, const std::vector<Mat42>& v, GLboolean transpose			) const { glProgramUniformMatrix4x2fv	(*this, location, (GLsizei)v.size(), transpose, &v[0][0][0]	); GL_CHECK_ERROR; }
		
		// Pass MatArr	-		GLfloat	, 4, 3
		template<> void Uniform<GLfloat	, 4, 3	>(GLint location, const GLfloat *value										) const { glProgramUniformMatrix4x3fv	(*this, location, 1, GL_FALSE, value						); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 4, 3	>(GLint location, GLsizei count, const GLfloat *value						) const { glProgramUniformMatrix4x3fv	(*this, location, count, GL_FALSE, value					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 4, 3	>(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value	) const { glProgramUniformMatrix4x3fv	(*this, location, count, transpose, value					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 4, 3	>(GLint location, const Mat43& v											) const { glProgramUniformMatrix4x3fv	(*this, location, 1, GL_FALSE, &v[0][0]						); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 4, 3	>(GLint location, const Mat43& v, GLboolean transpose						) const { glProgramUniformMatrix4x3fv	(*this, location, 1, transpose, &v[0][0]					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 4, 3	>(GLint location, const std::vector<Mat43>& v								) const { glProgramUniformMatrix4x3fv	(*this, location, (GLsizei)v.size(), GL_FALSE, &v[0][0][0]	); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 4, 3	>(GLint location, const std::vector<Mat43>& v, GLboolean transpose			) const { glProgramUniformMatrix4x3fv	(*this, location, (GLsizei)v.size(), transpose, &v[0][0][0]	); GL_CHECK_ERROR; }
		
		// Pass MatArr	-		GLfloat	, 4, 4
		template<> void Uniform<GLfloat	, 4, 4	>(GLint location, const GLfloat *value										) const { glProgramUniformMatrix4fv		(*this, location, 1, GL_FALSE, value						); GL_CHECK_ERROR; }		
		template<> void Uniform<GLfloat	, 4, 4	>(GLint location, GLsizei count, const GLfloat *value						) const { glProgramUniformMatrix4fv		(*this, location, count, GL_FALSE, value					); GL_CHECK_ERROR; }	
		template<> void Uniform<GLfloat	, 4, 4	>(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value	) const { glProgramUniformMatrix4fv		(*this, location, count, transpose, value					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 4, 4	>(GLint location, const Mat44& v											) const { glProgramUniformMatrix4fv		(*this, location, 1, GL_FALSE, &v[0][0]						); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 4, 4	>(GLint location, const Mat44& v, GLboolean transpose						) const { glProgramUniformMatrix4fv		(*this, location, 1, transpose, &v[0][0]					); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 4, 4	>(GLint location, const std::vector<Mat44>& v								) const { glProgramUniformMatrix4fv		(*this, location, (GLsizei)v.size(), GL_FALSE, &v[0][0][0]	); GL_CHECK_ERROR; }
		template<> void Uniform<GLfloat	, 4, 4	>(GLint location, const std::vector<Mat44>& v, GLboolean transpose			) const { glProgramUniformMatrix4fv		(*this, location, (GLsizei)v.size(), transpose, &v[0][0][0]	); GL_CHECK_ERROR; }

	protected:
		static std::vector<GLuint> bindStack;
	};

	//
	template<>
	GLint Program::GetInfo<GLint>(GLenum pname) const
	{
		GLint ri(0);
		glGetProgramiv(*this, pname, &ri);
		GL_CHECK_ERROR;
		return ri;
	}

	template<>
	GLboolean Program::GetInfo<GLboolean>(GLenum pname) const
	{
		return (GLboolean)GetInfo<GLint>(pname);
	}
};