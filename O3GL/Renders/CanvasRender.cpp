// std
#include <sstream>

// O3GL
#include "O3GL/Core/Window.hpp"
#include "O3GL/Renders/CanvasRender.hpp"

// 
namespace O3GL
{
	//
	void CanvasRender::SetupEvent()
	{
		samplers["plane_nearest"] = Sampler();
		samplers["plane_bilinear"] = Sampler();
		samplers["plane_trilinear"] = Sampler();
		samplers["plane_anisotropy"] = Sampler();

		samplers["cube_nearest"] = Sampler();
		samplers["cube_bilinear"] = Sampler();
		samplers["cube_trilinear"] = Sampler();
		samplers["cube_anisotropy"] = Sampler();

		samplers["equirectangular_nearest"] = Sampler();
		samplers["equirectangular_bilinear"] = Sampler();
		samplers["equirectangular_trilinear"] = Sampler();
		samplers["equirectangular_anisotropy"] = Sampler();

		samplers["mercator_nearest"] = Sampler();
		samplers["mercator_bilinear"] = Sampler();
		samplers["mercator_trilinear"] = Sampler();
		samplers["mercator_anisotropy"] = Sampler();

		buffers["canvas_pos"] = Buffer();
		buffers["canvas_index"] = Buffer();

		vertexArrays["canvas"] = VertexArray();

		shaderSources["canvas_vert"] = ShaderSource();
		shaderSources["canvas_geom"] = ShaderSource();
		shaderSources["canvas_frag"] = ShaderSource();

		shaders["canvas_vert"] = Shader(GL_VERTEX_SHADER);
		shaders["canvas_geom"] = Shader(GL_GEOMETRY_SHADER);
		shaders["canvas_frag"] = Shader(GL_FRAGMENT_SHADER);

		programs["canvas"] = Program();

		if (!windowMode)
			frameBuffers["canvas"] = FrameBuffer();
	}

	void CanvasRender::InitSamplersEvent()
	{
		GLfloat maxNumSamples;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &maxNumSamples);

		//
		samplers["plane_nearest"].SetInfo<GLint>(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		samplers["plane_nearest"].SetInfo<GLint>(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		samplers["plane_nearest"].SetInfo<GLint>(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		samplers["plane_nearest"].SetInfo<GLint>(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		samplers["plane_bilinear"].SetInfo<GLint>(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		samplers["plane_bilinear"].SetInfo<GLint>(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		samplers["plane_bilinear"].SetInfo<GLint>(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		samplers["plane_bilinear"].SetInfo<GLint>(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		samplers["plane_trilinear"].SetInfo<GLint>(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		samplers["plane_trilinear"].SetInfo<GLint>(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		samplers["plane_trilinear"].SetInfo<GLint>(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		samplers["plane_trilinear"].SetInfo<GLint>(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (ANISOTROPIC_FILTER_SAMPLES > 1.0f)
		{
			samplers["plane_anisotropy"].SetInfo<GLint>(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			samplers["plane_anisotropy"].SetInfo<GLint>(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			samplers["plane_anisotropy"].SetInfo<GLint>(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			samplers["plane_anisotropy"].SetInfo<GLint>(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			samplers["plane_anisotropy"].SetInfo<GLfloat>(GL_TEXTURE_MAX_ANISOTROPY, CLAMP(ANISOTROPIC_FILTER_SAMPLES, 1.0f, maxNumSamples));
		}
		else
		{
			samplers["plane_anisotropy"] = samplers["plane_trilinear"];
		}

		//
		samplers["cube_nearest"].SetInfo<GLint>(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		samplers["cube_nearest"].SetInfo<GLint>(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		samplers["cube_nearest"].SetInfo<GLint>(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		samplers["cube_nearest"].SetInfo<GLint>(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		samplers["cube_nearest"].SetInfo<GLint>(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		samplers["cube_bilinear"].SetInfo<GLint>(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		samplers["cube_bilinear"].SetInfo<GLint>(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		samplers["cube_bilinear"].SetInfo<GLint>(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		samplers["cube_bilinear"].SetInfo<GLint>(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		samplers["cube_bilinear"].SetInfo<GLint>(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		samplers["cube_trilinear"].SetInfo<GLint>(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		samplers["cube_trilinear"].SetInfo<GLint>(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		samplers["cube_trilinear"].SetInfo<GLint>(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		samplers["cube_trilinear"].SetInfo<GLint>(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		samplers["cube_trilinear"].SetInfo<GLint>(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (ANISOTROPIC_FILTER_SAMPLES > 1.0f)
		{
			samplers["cube_anisotropy"].SetInfo<GLint>(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			samplers["cube_anisotropy"].SetInfo<GLint>(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			samplers["cube_anisotropy"].SetInfo<GLint>(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			samplers["cube_anisotropy"].SetInfo<GLint>(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			samplers["cube_anisotropy"].SetInfo<GLint>(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			samplers["cube_anisotropy"].SetInfo<GLfloat>(GL_TEXTURE_MAX_ANISOTROPY, CLAMP(ANISOTROPIC_FILTER_SAMPLES, 1.0f, maxNumSamples));
		}
		else
		{
			samplers["cube_anisotropy"] = samplers["cube_trilinear"];
		}

		//
		samplers["equirectangular_nearest"].SetInfo<GLint>(GL_TEXTURE_WRAP_S, GL_REPEAT);
		samplers["equirectangular_nearest"].SetInfo<GLint>(GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		samplers["equirectangular_nearest"].SetInfo<GLint>(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		samplers["equirectangular_nearest"].SetInfo<GLint>(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		samplers["equirectangular_bilinear"].SetInfo<GLint>(GL_TEXTURE_WRAP_S, GL_REPEAT);
		samplers["equirectangular_bilinear"].SetInfo<GLint>(GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		samplers["equirectangular_bilinear"].SetInfo<GLint>(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		samplers["equirectangular_bilinear"].SetInfo<GLint>(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		samplers["equirectangular_trilinear"].SetInfo<GLint>(GL_TEXTURE_WRAP_S, GL_REPEAT);
		samplers["equirectangular_trilinear"].SetInfo<GLint>(GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		samplers["equirectangular_trilinear"].SetInfo<GLint>(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		samplers["equirectangular_trilinear"].SetInfo<GLint>(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (ANISOTROPIC_FILTER_SAMPLES > 1.0f)
		{
			samplers["equirectangular_anisotropy"].SetInfo<GLint>(GL_TEXTURE_WRAP_S, GL_REPEAT);
			samplers["equirectangular_anisotropy"].SetInfo<GLint>(GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
			samplers["equirectangular_anisotropy"].SetInfo<GLint>(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			samplers["equirectangular_anisotropy"].SetInfo<GLint>(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			samplers["equirectangular_anisotropy"].SetInfo<GLfloat>(GL_TEXTURE_MAX_ANISOTROPY, CLAMP(ANISOTROPIC_FILTER_SAMPLES, 1.0f, maxNumSamples));
		}
		else
		{
			samplers["equirectangular_anisotropy"] = samplers["equirectangular_trilinear"];
		}

		//
		samplers["mercator_nearest"].SetInfo<GLint>(GL_TEXTURE_WRAP_S, GL_REPEAT);
		samplers["mercator_nearest"].SetInfo<GLint>(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		samplers["mercator_nearest"].SetInfo<GLint>(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		samplers["mercator_nearest"].SetInfo<GLint>(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		samplers["mercator_bilinear"].SetInfo<GLint>(GL_TEXTURE_WRAP_S, GL_REPEAT);
		samplers["mercator_bilinear"].SetInfo<GLint>(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		samplers["mercator_bilinear"].SetInfo<GLint>(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		samplers["mercator_bilinear"].SetInfo<GLint>(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		samplers["mercator_trilinear"].SetInfo<GLint>(GL_TEXTURE_WRAP_S, GL_REPEAT);
		samplers["mercator_trilinear"].SetInfo<GLint>(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		samplers["mercator_trilinear"].SetInfo<GLint>(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		samplers["mercator_trilinear"].SetInfo<GLint>(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (ANISOTROPIC_FILTER_SAMPLES > 1.0f)
		{
			samplers["mercator_anisotropy"].SetInfo<GLint>(GL_TEXTURE_WRAP_S, GL_REPEAT);
			samplers["mercator_anisotropy"].SetInfo<GLint>(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			samplers["mercator_anisotropy"].SetInfo<GLint>(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			samplers["mercator_anisotropy"].SetInfo<GLint>(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			samplers["mercator_anisotropy"].SetInfo<GLfloat>(GL_TEXTURE_MAX_ANISOTROPY, CLAMP(ANISOTROPIC_FILTER_SAMPLES, 1.0f, maxNumSamples));
		}
		else
		{
			samplers["mercator_anisotropy"] = samplers["mercator_trilinear"];
		}
	}

	void CanvasRender::InitBuffersEvent()
	{
		std::vector<R32> posData = {
		-1.f, -1.f, 0.99999f,
		1.0f, -1.f, 0.99999f,
		1.0f, 1.0f, 0.99999f,
		-1.f, 1.0f, 0.99999f };
		std::vector<UI32> indexData = { 0,1,2,2,3,0 };

		buffers["canvas_pos"].Data(posData, GL_STATIC_DRAW);
		buffers["canvas_index"].Data(indexData, GL_STATIC_DRAW);
	}

	void CanvasRender::InitVertexShaderHeadersEvent()
	{
		shaderSources["canvas_vert"].push_back(R"(
#version 460 core

layout(location = 0) in vec3 a_pos;
			)");
	}

	void CanvasRender::InitVertexShaderMainsEvent()
	{
		shaderSources["canvas_vert"].push_back(R"(
void main(void)
{
	gl_Position	= vec4(a_pos, 1.0f);
}
			)");
	}

	void CanvasRender::InitFragmentShaderHeadersEvent()
	{
		shaderSources["canvas_frag"].push_back(R"(	
#version 460 core
//#extension GL_EXT_texture_array : enable

// Vars
#define M_PI				3.14159265359f // PI
#define M_PI_2				1.57079632679f // PI / 2
#define M_1_PI				0.31830988618f // 1 / PI
#define M_2_PI				0.63661977236f // 2 / PI
#define M_2PI				6.28318530718f // PI * 2
#define M_1_2PI				0.15915494309f // 1 / (2*PI)

#define M_N_PI				-3.14159265359f // -PI
#define M_N_PI_2			-1.57079632679f // -PI / 2
#define M_N_1_PI			-0.31830988618f // -1 / PI
#define M_N_2_PI			-0.63661977236f // -2 / PI
#define M_N_2PI				-6.28318530718f // -PI * 2
#define M_N_1_2PI			-0.15915494309f // -1 / (2*PI)

#define CAM_NEAR 0.1f
#define CAM_FAR 10.0f

uniform int u_canvasWidth;
uniform int u_canvasHeight;

// Utils
struct Ray3D
{
	vec3 o;
	vec3 d;
};

struct Ray2D
{
	vec2 o;
	vec2 d;
};

// Utils
vec2 EquirectangularUV_To_AE(vec2 uv)
{
	return (uv - 0.5f) * vec2(M_N_2PI, M_PI);
}

vec3 EquirectangularUV_To_Dir(vec2 uv)
{
	vec2 ae = (uv - 0.5f) * vec2(M_N_2PI, M_PI);
	vec2 s = sin(ae);
	vec2 c = cos(ae);
	return vec3(c.y * c.x, c.y * s.x, s.y);
}

vec2 MercatorUV_To_AE(vec2 uv)
{
	vec2 xy = (uv - 0.5f) * vec2(M_N_2PI, M_PI);
	xy.y = atan(sinh(xy.y));
	return xy;
}

vec3 MercatorUV_To_Dir(vec2 uv)
{
	vec2 ae = (uv - 0.5f) * vec2(M_N_2PI, M_PI);
	ae.y = atan(sinh(ae.y));
	vec2 s = sin(ae);
	vec2 c = cos(ae);
	return vec3(c.y * c.x, c.y * s.x, s.y);	
}

vec2 AE_To_EquirectangularUV(vec2 ae)
{
	return 0.5f + ae * vec2(M_N_1_2PI, M_1_PI);
}

vec2 AE_To_MercatorUV(vec2 ae)
{
	return 0.5f + vec2(ae.x, log(tan(ae.y)+1.0f/cos(ae.y))) * vec2(M_N_1_2PI, M_1_PI);
}

vec3 AE_To_Dir(vec2 ae)
{
	vec2 s = sin(ae);
	vec2 c = cos(ae);
	return vec3(c.y * c.x, c.y * s.x, s.y);
}					

vec2 Dir_To_AE(vec3 dir)
{
	return vec2(atan(dir.y, dir.x), asin(dir.z));
}

vec2 Dir_To_EquirectangularUV(vec3 dir)
{
	return 0.5f + vec2(atan(dir.y, dir.x), asin(dir.z)) * vec2(M_N_1_2PI, M_1_PI);
}

vec2 Dir_To_MercatorUV(vec3 dir)
{
	float temp = asin(dir.z);
	return 0.5f + vec2(atan(dir.y, dir.x), log(tan(temp)+1.0f/cos(temp))) * vec2(M_N_1_2PI, M_1_PI);
}

float RaycastSphere(float radius, Ray3D ray)
{
	float b = dot(ray.o, ray.d);
	float c = dot(ray.o,ray.o) - radius*radius;
	return sqrt(b*b - c) - b;
}

float RaycastSphere(float radius, Ray2D ray)
{
	float b = dot(ray.o, ray.d);
	float c = dot(ray.o,ray.o) - radius*radius;
	return sqrt(b*b - c) - b;
}
			)");
	}

	void CanvasRender::InitFragmentShaderMainsEvent()
	{
		shaderSources["canvas_frag"].push_back(R"(
void main(void)
{
	gl_FragColor  = vec4(1.0f, 0.0f, 1.0f, 1.0f);
}
			)");
	}

	void CanvasRender::InitShadersEvent()
	{
		shaders["canvas_vert"].Source(shaderSources["canvas_vert"]);
		{
			GLboolean success;
			std::string log;
			std::tie(success, log) = shaders["canvas_vert"].Compile();
			if (!success)
			{
				PrintShaderSources("canvas_vert");
				THROW_EXCEPTION("canvas_vert compile fail: " + log);
			}
		}

		if (shaderSources["canvas_geom"].size() > 0)
		{
			shaders["canvas_geom"].Source(shaderSources["canvas_geom"]);
			GLboolean success;
			std::string log;
			std::tie(success, log) = shaders["canvas_geom"].Compile();
			if (!success)
			{
				PrintShaderSources("canvas_geom");
				THROW_EXCEPTION("canvas_geom compile fail: " + log);
			}
		}

		shaders["canvas_frag"].Source(shaderSources["canvas_frag"]);
		{
			GLboolean success;
			std::string log;
			std::tie(success, log) = shaders["canvas_frag"].Compile();
			if (!success)
			{
				PrintShaderSources("canvas_frag");
				THROW_EXCEPTION("canvas_frag compile fail: " + log);
			}
		}
	}

	void CanvasRender::InitProgramsEvent()
	{
		programs["canvas"].AttachShader(shaders["canvas_vert"]);
		if (shaderSources["canvas_geom"].size() > 0)
			programs["canvas"].AttachShader(shaders["canvas_geom"]);
		programs["canvas"].AttachShader(shaders["canvas_frag"]);

		GLboolean success;
		std::string log;
		std::tie(success, log) = programs["canvas"].Link();
		if (!success)
			THROW_EXCEPTION("canvas link fail - " + log);

		programs["canvas"].DetachShader(shaders["canvas_vert"]);
		if (shaderSources["canvas_geom"].size() > 0)
			programs["canvas"].DetachShader(shaders["canvas_geom"]);
		programs["canvas"].DetachShader(shaders["canvas_frag"]);
	}

	void CanvasRender::InitProgramParametersEvent() const
	{
		programs.at("canvas").Uniform<GLint, 1>("u_canvasWidth", CanvasWidth());
		programs.at("canvas").Uniform<GLint, 1>("u_canvasHeight", CanvasHeight());
	}

	void CanvasRender::InitVertexArraysEvent()
	{
		// Set pos
		GLint attribLocation = 0;
		GLuint bindingIndex = 0;

		vertexArrays["canvas"].EnableAttrib(attribLocation);
		vertexArrays["canvas"].VertexBuffer<GLfloat>(bindingIndex, buffers["canvas_pos"], 0, 3);
		vertexArrays["canvas"].AttribBinding(attribLocation, bindingIndex);
		vertexArrays["canvas"].AttribFormat(attribLocation, 3, GL_FLOAT, GL_FALSE, 0);

		// Set index
		vertexArrays["canvas"].ElementBuffer(buffers["canvas_index"]);
	}

	void CanvasRender::PreDrawEvent() const
	{
		if (!windowMode)
			frameBuffers.at("canvas").Begin();

		programs.at("canvas").Begin();
		vertexArrays.at("canvas").Begin();
	}

	void CanvasRender::OnDrawEvent() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, CanvasWidth(), CanvasHeight());

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	}

	void CanvasRender::PostDrawEvent() const
	{
		vertexArrays.at("canvas").End();
		programs.at("canvas").End();

		if (!windowMode)
			frameBuffers.at("canvas").End();
	}

	GLint CanvasRender::CanvasWidth() const
	{
		if (windowMode)
			return CurrentWindowWidth();
		else
			return canvasWidth;
	}

	GLint CanvasRender::CanvasHeight() const
	{
		if (windowMode)
			return CurrentWindowHeight();
		else
			return canvasHeight;
	}
};