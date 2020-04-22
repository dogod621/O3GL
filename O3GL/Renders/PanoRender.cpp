// std
#include <sstream>

// O3GL
#include "O3GL/Renders/PanoRender.hpp"

// 
namespace O3GL
{
	void PanoRenderBase::InitGeometryShaderHeadersEvent()
	{
		CanvasRender::InitGeometryShaderHeadersEvent();

		//
		if (layers > 1)
		{
			shaderSources["canvas_geom"]->push_back(R"(
#version 460 core

				)");

			shaderSources["canvas_geom"]->push_back("layout(triangles, invocations = " + std::to_string(layers) + ") in;");

			shaderSources["canvas_geom"]->push_back(R"(

layout (triangle_strip, max_vertices = 3) out;
out int gl_Layer;
				)");
		}
	}

	void PanoRenderBase::InitGeometryShaderMainsEvent()
	{
		if (layers > 1)
		{
			shaderSources["canvas_geom"]->push_back(R"(
void main()
{
	gl_Layer = gl_InvocationID;

	gl_Position = gl_in[0].gl_Position;
	EmitVertex();

    gl_Position = gl_in[1].gl_Position;
	EmitVertex();

	gl_Position = gl_in[2].gl_Position;
	EmitVertex();

    EndPrimitive();
}
				)");
		}
	}

	void PanoRenderBase::InitFragmentShaderHeadersEvent()
	{
		CanvasRender::InitFragmentShaderHeadersEvent();

		//
		shaderSources["canvas_frag"]->push_back(R"(
uniform mat4 u_inProjTransformINV[)");

		shaderSources["canvas_frag"]->push_back(std::to_string(inProjTransform.size()) + "];");

		shaderSources["canvas_frag"]->push_back(R"(
uniform mat4 u_outProjTransform[)");

		shaderSources["canvas_frag"]->push_back(std::to_string(outProjTransform.size()) + "];");

		if (layers > 1)
		{
			shaderSources["canvas_frag"]->push_back(R"(
in int gl_Layer;
				)");
		}

		switch (rigMode)
		{
		case RigMode::MONO:
			switch (outProjMode)
			{
			case ProjectionMode::MULTI_PERSPECTIVE:
			case ProjectionMode::CUBEMAP:
			case ProjectionMode::JOSH1:
			case ProjectionMode::JOSH2:
			case ProjectionMode::JOSH3:
			case ProjectionMode::JOSH1_X:
				shaderSources["canvas_frag"]->push_back(R"(
int LayerID()
{
	return gl_Layer;
}
					)");
				break;
			}
			break;

		case RigMode::MULTI:
			shaderSources["canvas_frag"]->push_back(R"(
uniform int u_numRigCameras;

uniform mat4 u_rigW2V[)");

			shaderSources["canvas_frag"]->push_back(std::to_string(rigW2V.size()) + "];");

			shaderSources["canvas_frag"]->push_back(R"(
uniform mat4 u_rigV2W[)");

			shaderSources["canvas_frag"]->push_back(std::to_string(rigV2W.size()) + "];");

			switch (outProjMode)
			{
			case ProjectionMode::PERSPECTIVE:
			case ProjectionMode::EQUIRECTANGULAR:
			case ProjectionMode::MERCATOR:
				shaderSources["canvas_frag"]->push_back(R"(
int RigID()
{
	return gl_Layer;
}
					)");
				break;

			case ProjectionMode::MULTI_PERSPECTIVE:
			case ProjectionMode::JOSH1:
			case ProjectionMode::JOSH2:
			case ProjectionMode::JOSH3:
			case ProjectionMode::JOSH1_X:
				shaderSources["canvas_frag"]->push_back(R"(
int RigID()
{
	return gl_Layer % u_numRigCameras;
}

int LayerID()
{
	return gl_Layer / u_numRigCameras;
}
					)");
				break;

			case ProjectionMode::CUBEMAP:
				shaderSources["canvas_frag"]->push_back(R"(
int RigID()
{
	return gl_Layer / 6;
}

int LayerID()
{
	return gl_Layer % 6;
}
					)");
				break;
			}
			break;
		}

		//
		if (inProjCamera.size() > 0)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform uint u_numPanoProjectionCameras;

uniform mat4 u_inProjW2V[)");

			shaderSources["canvas_frag"]->push_back(std::to_string(inProjCamera.size()) + "];");

			//
			shaderSources["canvas_frag"]->push_back(R"(
uniform mat4 u_inProjW2C[)");

			shaderSources["canvas_frag"]->push_back(std::to_string(inProjCamera.size()) + "];");

			//
			shaderSources["canvas_frag"]->push_back(R"(
uniform mat4 u_inProjV2W[)");

			shaderSources["canvas_frag"]->push_back(std::to_string(inProjCamera.size()) + "];");

			//
			shaderSources["canvas_frag"]->push_back(R"(
uniform mat4 u_inProjC2W[)");

			shaderSources["canvas_frag"]->push_back(std::to_string(inProjCamera.size()) + "];");

			//
			shaderSources["canvas_frag"]->push_back(R"(
uniform float u_inProjCameraWeight[)");

			shaderSources["canvas_frag"]->push_back(std::to_string(inProjCameraWeight.size()) + "];");
		}

		//
		if (outProjCamera.size() > 0)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform uint u_numCanvasProjectionCameras;

uniform mat4 u_outProjW2V[)");

			shaderSources["canvas_frag"]->push_back(std::to_string(outProjCamera.size()) + "];");

			//
			shaderSources["canvas_frag"]->push_back(R"(
uniform mat4 u_outProjW2C[)");

			shaderSources["canvas_frag"]->push_back(std::to_string(outProjCamera.size()) + "];");

			//
			shaderSources["canvas_frag"]->push_back(R"(
uniform mat4 u_outProjV2W[)");

			shaderSources["canvas_frag"]->push_back(std::to_string(outProjCamera.size()) + "];");


			//
			shaderSources["canvas_frag"]->push_back(R"(
uniform mat4 u_outProjC2W[)");

			shaderSources["canvas_frag"]->push_back(std::to_string(outProjCamera.size()) + "];");
		}

		//
		switch (rigMode)
		{
		case RigMode::MONO:
			switch (inProjMode)
			{
			case ProjectionMode::PERSPECTIVE:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_PERSPECTIVE();
				break;

			case ProjectionMode::EQUIRECTANGULAR:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_EQUIRECTANGULAR();
				break;

			case ProjectionMode::MERCATOR:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_MERCATOR();
				break;

			case ProjectionMode::MULTI_PERSPECTIVE:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_MULTI_PERSPECTIVE();
				break;

			case ProjectionMode::CUBEMAP:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_CUBEMAP();
				break;

			case ProjectionMode::JOSH1:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_JOSH1();
				break;

			case ProjectionMode::JOSH2:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_JOSH2();
				break;

			case ProjectionMode::JOSH3:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_JOSH3();
				break;

			case ProjectionMode::JOSH1_X:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_JOSH1_X();
				break;

			default:
				THROW_EXCEPTION("inProjMode is not supported");
				break;
			}
			break;

		case RigMode::MULTI:
			switch (inProjMode)
			{
			case ProjectionMode::PERSPECTIVE:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_PERSPECTIVE();
				break;

			case ProjectionMode::EQUIRECTANGULAR:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_EQUIRECTANGULAR();
				break;

			case ProjectionMode::MERCATOR:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_MERCATOR();
				break;

			case ProjectionMode::MULTI_PERSPECTIVE:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_MULTI_PERSPECTIVE();
				break;

			case ProjectionMode::CUBEMAP:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_CUBEMAP();
				break;

			case ProjectionMode::JOSH1:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_JOSH1();
				break;

			case ProjectionMode::JOSH2:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_JOSH2();
				break;

			case ProjectionMode::JOSH3:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_JOSH3();
				break;

			case ProjectionMode::JOSH1_X:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_JOSH1_X();
				break;

			default:
				THROW_EXCEPTION("inProjMode is not supported");
				break;
			}
			break;

		default:
			THROW_EXCEPTION("rigMode is not supported");
			break;
		}

		//
		switch (rigMode)
		{
		case RigMode::MONO:
			switch (outProjMode)
			{
			case ProjectionMode::PERSPECTIVE:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_PERSPECTIVE();
				break;

			case ProjectionMode::EQUIRECTANGULAR:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_EQUIRECTANGULAR();
				break;

			case ProjectionMode::MERCATOR:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_MERCATOR();
				break;

			case ProjectionMode::MULTI_PERSPECTIVE:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_MULTI_PERSPECTIVE();
				break;

			case ProjectionMode::CUBEMAP:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_CUBEMAP();
				break;

			case ProjectionMode::JOSH1:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_JOSH1();
				break;

			case ProjectionMode::JOSH2:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_JOSH2();
				break;

			case ProjectionMode::JOSH3:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_JOSH3();
				break;

			case ProjectionMode::JOSH1_X:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_JOSH1_X();
				break;

			default:
				THROW_EXCEPTION("outProjMode is not supported");
				break;
			}
			break;

		case RigMode::MULTI:
			switch (outProjMode)
			{
			case ProjectionMode::PERSPECTIVE:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_PERSPECTIVE();
				break;

			case ProjectionMode::EQUIRECTANGULAR:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_EQUIRECTANGULAR();
				break;

			case ProjectionMode::MERCATOR:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_MERCATOR();
				break;

			case ProjectionMode::MULTI_PERSPECTIVE:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_MULTI_PERSPECTIVE();
				break;

			case ProjectionMode::CUBEMAP:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_CUBEMAP();
				break;

			case ProjectionMode::JOSH1:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_JOSH1();
				break;

			case ProjectionMode::JOSH2:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_JOSH2();
				break;

			case ProjectionMode::JOSH3:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_JOSH3();
				break;

			case ProjectionMode::JOSH1_X:
				PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_JOSH1_X();
				break;

			default:
				THROW_EXCEPTION("outProjMode is not supported");
				break;
			}
			break;

		default:
			THROW_EXCEPTION("rigMode is not supported");
			break;
		}
	}

	void PanoRenderBase::InitProgramParametersEvent() const
	{
		CanvasRender::InitProgramParametersEvent();

		//
		switch (inProjMode)
		{
		case ProjectionMode::JOSH1_X:
		{
			float cameraNear = 0.1f;
			float cameraFar = 10.0f;
			Mat44 perspective = glm::perspective(glm::radians(JOSH1_fovY), 1.0f, cameraNear, cameraFar);

			for (std::size_t i = 0; i < inProjCamera.size(); ++i)
			{
				(*(Camera*)(&inProjCamera[i])).projection = perspective;

				for (std::size_t i = 0; i < inProjCamera.size(); ++i)
				{
					Vec3 eye = inProjCamera[i].transform * Vec4(0.0f, 0.0f, 0.0f, 1.0f);
					Vec3 viewDir = inProjCamera[i].transform * Vec4(1.0f, 0.0f, 0.0f, 0.0f);
					Vec3 up = inProjCamera[i].transform * Vec4(0.0f, 0.0f, 1.0f, 0.0f);

					(*((Mat44*)&inProjW2V[i])) = glm::lookAt(eye, eye + viewDir, up);
					(*((Mat44*)&inProjW2C[i])) = inProjCamera[i].projection * inProjW2V[i];
					(*((Mat44*)&inProjV2W[i])) = glm::inverse(inProjW2V[i]);
					(*((Mat44*)&inProjC2W[i])) = glm::inverse(inProjW2C[i]);
					(*((GLfloat*)&inProjCameraWeight[i])) = 1.0f;
				}
			}
		}
		break;

		case ProjectionMode::JOSH3:
			programs.at("canvas")->Uniform<GLint, 1>("u_useCenterOnly", JOSH3_useCenterOnly);
			break;
		}

		switch (outProjMode)
		{
		case ProjectionMode::JOSH1_X:
		{
			float cameraNear = 0.1f;
			float cameraFar = 10.0f;
			Mat44 perspective = glm::perspective(glm::radians(JOSH1_fovY), 1.0f, cameraNear, cameraFar);

			for (std::size_t i = 0; i < outProjCamera.size(); ++i)
			{
				(*(Camera*)(&outProjCamera[i])).projection = perspective;

				for (std::size_t i = 0; i < outProjCamera.size(); ++i)
				{
					Vec3 eye = outProjCamera[i].transform * Vec4(0.0f, 0.0f, 0.0f, 1.0f);
					Vec3 viewDir = outProjCamera[i].transform * Vec4(1.0f, 0.0f, 0.0f, 0.0f);
					Vec3 up = outProjCamera[i].transform * Vec4(0.0f, 0.0f, 1.0f, 0.0f);

					(*((Mat44*)&outProjW2V[i])) = glm::lookAt(eye, eye + viewDir, up);
					(*((Mat44*)&outProjW2C[i])) = outProjCamera[i].projection * outProjW2V[i];
					(*((Mat44*)&outProjV2W[i])) = glm::inverse(outProjW2V[i]);
					(*((Mat44*)&outProjC2W[i])) = glm::inverse(outProjW2C[i]);
				}
			}
		}
		break;
		}

		//
		std::vector<Mat44> inProjTransformINV;
		inProjTransformINV.resize(inProjTransform.size());
		for (std::size_t i = 0; i < inProjTransform.size(); ++i)
		{
			inProjTransformINV[i] = glm::inverse(inProjTransform[i]);
		}

		programs.at("canvas")->Uniform<GLfloat, 4, 4>("u_inProjTransformINV", inProjTransformINV);
		programs.at("canvas")->Uniform<GLfloat, 4, 4>("u_outProjTransform", outProjTransform);

		switch (rigMode)
		{
		case RigMode::MULTI:
			programs.at("canvas")->Uniform<GLint, 1>("u_numRigCameras", (GLint)rigW2V.size());
			programs.at("canvas")->Uniform<GLfloat, 4, 4>("u_rigW2V", rigW2V);
			programs.at("canvas")->Uniform<GLfloat, 4, 4>("u_rigV2W", rigV2W);
			break;
		}

		if (inProjCamera.size() > 0)
		{
			programs.at("canvas")->Uniform<GLuint, 1>("u_numPanoProjectionCameras", (GLuint)inProjCamera.size());
			programs.at("canvas")->Uniform<GLfloat, 4, 4>("u_inProjW2C", inProjW2C);
			programs.at("canvas")->Uniform<GLfloat, 4, 4>("u_inProjW2V", inProjW2V);
			programs.at("canvas")->Uniform<GLfloat, 4, 4>("u_inProjV2W", inProjV2W);
			programs.at("canvas")->Uniform<GLfloat, 4, 4>("u_inProjC2W", inProjC2W);
			programs.at("canvas")->Uniform<GLfloat, 1>("u_inProjCameraWeight", inProjCameraWeight);
		}

		if (outProjCamera.size() > 0)
		{
			programs.at("canvas")->Uniform<GLuint, 1>("u_numCanvasProjectionCameras", (GLuint)outProjCamera.size());
			programs.at("canvas")->Uniform<GLfloat, 4, 4>("u_outProjW2V", outProjW2V);
			programs.at("canvas")->Uniform<GLfloat, 4, 4>("u_outProjW2C", outProjW2C);
			programs.at("canvas")->Uniform<GLfloat, 4, 4>("u_outProjV2W", outProjV2W);
			programs.at("canvas")->Uniform<GLfloat, 4, 4>("u_outProjC2W", outProjC2W);
		}
	}

	void PanoRenderBase::PreDrawEvent() const
	{
		CanvasRender::PreDrawEvent();

		//
		panoFieldTexture->Begin(*panoFieldSampler);
		programs.at("canvas")->Uniform<GLint, 1>("u_panoField", (GLint)panoFieldTexture->Unit());

		if (enableDepth)
		{
			panoDepthTexture->Begin(*panoDepthSampler);
			programs.at("canvas")->Uniform<GLint, 1>("u_panoDepth", (GLint)panoDepthTexture->Unit());
		}

		if (enableMask)
		{
			panoMaskTexture->Begin(*panoMaskSampler);
			programs.at("canvas")->Uniform<GLint, 1>("u_panoMask", (GLint)panoMaskTexture->Unit());
		}
	}

	void PanoRenderBase::PostDrawEvent() const
	{
		if (enableMask)
		{
			panoMaskTexture->End();
		}

		if (enableDepth)
		{
			panoDepthTexture->End();
		}
		panoFieldTexture->End();

		//
		CanvasRender::PostDrawEvent();
	}

	void PanoRenderBase::InitCamera_CUBEMAP(const std::vector<Camera>& cameras)
	{
		if (cameras.size() != 6)
			THROW_EXCEPTION("cameras.size() != 6");

		float cameraNear = 0.1f;
		float cameraFar = 10.0f;
		Mat44 perspective = glm::perspective(glm::radians(90.0f), 1.0f, cameraNear, cameraFar);

		for (std::size_t i = 0; i < cameras.size(); ++i)
		{
			(*(Camera*)(&cameras[i])).projection = perspective;
		}

		(*(Camera*)(&cameras[0])).transform = Mat44(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, -1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		(*(Camera*)(&cameras[1])).transform = Mat44(
			-1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		(*(Camera*)(&cameras[2])).transform = Mat44(
			0.0f, 1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		(*(Camera*)(&cameras[3])).transform = Mat44(
			0.0f, -1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, -1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		(*(Camera*)(&cameras[4])).transform = Mat44(
			0.0f, 0.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		(*(Camera*)(&cameras[5])).transform = Mat44(
			0.0f, 0.0f, -1.0f, 0.0f,
			-1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	void PanoRenderBase::InitCamera_JOSH1(const std::vector<Camera>& cameras, GLfloat fovY)
	{
		if (cameras.size() != 6)
			THROW_EXCEPTION("cameras.size() != 6");

		float cameraNear = 0.1f;
		float cameraFar = 10.0f;
		Mat44 perspective = glm::perspective(glm::radians(fovY), 1.0f, cameraNear, cameraFar);

		for (std::size_t i = 0; i < cameras.size(); ++i)
		{
			(*(Camera*)(&cameras[i])).projection = perspective;
		}

		(*(Camera*)(&cameras[0])).transform = Mat44(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		(*(Camera*)(&cameras[1])).transform = Mat44(
			-1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		(*(Camera*)(&cameras[2])).transform = Mat44(
			0.0f, 1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		(*(Camera*)(&cameras[3])).transform = Mat44(
			0.0f, -1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		(*(Camera*)(&cameras[4])).transform = Mat44(
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		(*(Camera*)(&cameras[5])).transform = Mat44(
			0.0f, 0.0f, -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	void PanoRenderBase::InitCamera_JOSH2(const std::vector<Camera>& cameras)
	{
		if (cameras.size() != 8)
			THROW_EXCEPTION("cameras.size() != 8");

		float cameraNear = 0.1f;
		float cameraFar = 10.0f;
		Mat44 perspective = glm::perspective(glm::radians(90.0f), 1.0f, cameraNear, cameraFar);

		for (std::size_t i = 0; i < cameras.size(); ++i)
		{
			(*(Camera*)(&cameras[i])).projection = perspective;
		}

		(*(Camera*)(&cameras[0])).transform = Mat44(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		(*(Camera*)(&cameras[1])).transform = Mat44(
			-1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		(*(Camera*)(&cameras[2])).transform = Mat44(
			0.0f, 1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		(*(Camera*)(&cameras[3])).transform = Mat44(
			0.0f, -1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		(*(Camera*)(&cameras[4])).transform = Mat44(
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		(*(Camera*)(&cameras[5])).transform = Mat44(
			0.0f, 0.0f, -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		(*(Camera*)(&cameras[6])).transform = Mat44(
			0.0f, 0.0f, 1.0f, 0.0f,
			-1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		(*(Camera*)(&cameras[7])).transform = Mat44(
			0.0f, 0.0f, -1.0f, 0.0f,
			-1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	void PanoRenderBase::InitCamera_JOSH3(const std::vector<Camera>& cameras)
	{
		if (cameras.size() != 2)
			THROW_EXCEPTION("cameras.size() != 2");

		float cameraNear = 0.1f;
		float cameraFar = 10.0f;
		Mat44 perspective = glm::perspective(glm::radians(90.0f), 1.0f, cameraNear, cameraFar);

		for (std::size_t i = 0; i < cameras.size(); ++i)
		{
			(*(Camera*)(&cameras[i])).projection = perspective;
		}

		(*(Camera*)(&cameras[0])).transform = Mat44(
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		(*(Camera*)(&cameras[1])).transform = Mat44(
			0.0f, 0.0f, -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_PERSPECTIVE()
	{
		shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2D u_panoField;

vec4 PanoField(vec3 dir)
{
	vec3 dir2 = (u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz;

	vec4 s = u_inProjW2C[0] * vec4(dir2, 1.0f);
	s /= s.w;
	vec3 uvi = (s.xyz + 1.0f)*0.5f;

	return mix( 
		vec4(255.0f, 255.0f, 255.0f, 1.0f), 
		texture(u_panoField, uvi.xy), 
		float(length(floor(uvi)) < 1.0f));
}
			)");

		if (enableDepth)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2D u_panoDepth;

float PanoDepth(vec3 dir)
{
	vec3 dir2 = (u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz;

	vec4 s = u_inProjW2C[0] * vec4(dir2, 1.0f);
	s /= s.w;
	vec3 uvi = (s.xyz + 1.0f)*0.5f;

	return mix( 
		0.0f, 
		texture(u_panoDepth, uvi.xy).r, 
		float(length(floor(uvi)) < 1.0f));
}
				)");
		}

		if (enableMask)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2D u_panoMask;

float PanoMask(vec3 dir)
{
	vec3 dir2 = (u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz;

	vec4 s = u_inProjW2C[0] * vec4(dir2, 1.0f);
	s /= s.w;
	vec3 uvi = (s.xyz + 1.0f)*0.5f;

	return mix( 
		0.0f, 
		texture(u_panoMask, uvi.xy).r, 
		float(length(floor(uvi)) < 1.0f));
}
				)");
		}
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_EQUIRECTANGULAR()
	{
		shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2D u_panoField;

vec4 PanoField(vec3 dir)
{
	return texture(u_panoField, Dir_To_EquirectangularUV((u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz));
}
			)");

		if (enableDepth)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2D u_panoDepth;

float PanoDepth(vec3 dir)
{
	return texture(u_panoDepth, Dir_To_EquirectangularUV((u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz)).r;
}
				)");
		}

		if (enableMask)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2D u_panoMask;

float PanoMask(vec3 dir)
{
	return texture(u_panoMask, Dir_To_EquirectangularUV((u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz)).r;
}
				)");
		}
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_MERCATOR()
	{
		shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2D u_panoField;

vec4 PanoField(vec3 dir)
{
	return texture(u_panoField, Dir_To_MercatorUV((u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz));
}
			)");

		if (enableDepth)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2D u_panoDepth;

float PanoDepth(vec3 dir)
{
	return texture(u_panoDepth, Dir_To_MercatorUV((u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz)).r;
}
				)");
		}

		if (enableMask)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2D u_panoMask;

float PanoMask(vec3 dir)
{
	return texture(u_panoMask, Dir_To_MercatorUV((u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz)).r;
}
				)");
		}
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_MULTI_PERSPECTIVE()
	{
		shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoField;

vec4 PanoField(vec3 dir)
{
	vec3 dir2 = (u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz;

	vec4 s;
	float weight = 0.0f;
	float weightSum = 0.0f;
	vec3 field = vec3(0.0f, 0.0f, 0.0f);
	vec3 center = normalize(vec3(0.0f, 0.0f, 0.5f));

	vec3 uvi;
	for(uint i = 0 ; i < u_numPanoProjectionCameras ; ++i)
	{
		s = u_inProjW2C[i] * vec4(dir2, 1.0f);
		s /= s.w;
		uvi = (s.xyz + 1.0f)*0.5f;
		if(length(floor(uvi)) < 1.0f)
		{
			weight = u_inProjCameraWeight[i] * dot(normalize(vec3(s.xy, 0.5f)), center);
			field += weight * texture(u_panoField, vec3(uvi.xy, i)).rgb;
			weightSum += weight;
		}
	}
	return vec4(field / weightSum, 1.0f);
}
			)");

		if (enableDepth)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoDepth;

float PanoDepth(vec3 dir)
{
	vec3 dir2 = (u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz;

	vec4 s;
	float weight = 0.0f;
	float weightSum = 0.0f;
	float depth = 0.0f;
	vec3 center = normalize(vec3(0.0f, 0.0f, 0.5f));

	vec3 uvi;
	for(uint i = 0 ; i < u_numPanoProjectionCameras ; ++i)
	{
		s = u_inProjW2C[i] * vec4(dir2, 1.0f);
		s /= s.w;
		uvi = (s.xyz + 1.0f)*0.5f;
		if((length(floor(uvi)) < 1.0f) )
		{
			weight = u_inProjCameraWeight[i] * dot(normalize(vec3(s.xy, 0.1f)), center);
			depth += weight * texture(u_panoDepth, vec3(uvi.xy, i)).r;
			weightSum += weight;
		}
	}
	return depth / weightSum;
}
				)");
		}

		if (enableMask)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoMask;

float PanoMask(vec3 dir)
{
	vec3 dir2 = (u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz;

	vec4 s;
	float weight = 0.0f;
	float weightSum = 0.0f;
	float depth = 0.0f;
	vec3 center = normalize(vec3(0.0f, 0.0f, 0.5f));

	vec3 uvi;
	for(uint i = 0 ; i < u_numPanoProjectionCameras ; ++i)
	{
		s = u_inProjW2C[i] * vec4(dir2, 1.0f);
		s /= s.w;
		uvi = (s.xyz + 1.0f)*0.5f;
		if((length(floor(uvi)) < 1.0f) )
		{
			weight = u_inProjCameraWeight[i] * dot(normalize(vec3(s.xy, 0.1f)), center);
			depth += weight * texture(u_panoMask, vec3(uvi.xy, i)).r;
			weightSum += weight;
		}
	}
	return depth / weightSum;
}
				)");
		}
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_CUBEMAP()
	{
		shaderSources["canvas_frag"]->push_back(R"(
uniform samplerCube u_panoField;

vec4 PanoField(vec3 dir)
{
	return texture(u_panoField, (u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz);
}
			)");

		if (enableDepth)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform samplerCube u_panoDepth;

float PanoDepth(vec3 dir)
{
	return texture(u_panoDepth, (u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz).r;
}
				)");
		}

		if (enableMask)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform samplerCube u_panoMask;

float PanoMask(vec3 dir)
{
	return texture(u_panoMask, (u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz).r;
}
				)");
		}
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_JOSH1()
	{
		shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoField;

vec3 Dir_To_JOSH1UVI(vec3 dir)
{
	float c0 = dir.x;
	float c1 = -dir.x;
	float c2 = dir.y;
	float c3 = -dir.y;
	float c4 = dir.z;
	float c5 = -dir.z;

	float m01 = float(c0 < c1);
	float m23 = float(c2 < c3);
	float m45 = float(c4 < c5);
	float c01 = mix(c0, c1, m01);
	float c23 = mix(c2, c3, m23);
	float c45 = mix(c4, c5, m45);
	float i01 = mix(0.0f, 1.0f, m01);
	float i23 = mix(2.0f, 3.0f, m23);
	float i45 = mix(4.0f, 5.0f, m45);

	float m0123 = float(c01 < c23);
	float c0123 = mix(c01, c23, m0123);
	float i0123 = mix(i01, i23, m0123);

	int face = int(round(mix(i0123, i45, float(c0123 < c45))));
	vec4 s = u_inProjW2C[face] * vec4(dir, 1.0f);
	s /= s.w;
	return vec3((s.xy + 1.0f)*0.5f, face);
}

vec4 PanoField(vec3 dir)
{
	return texture(u_panoField, Dir_To_JOSH1UVI((u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz));
}
			)");

		if (enableDepth)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoDepth;

float PanoDepth(vec3 dir)
{
	return texture(u_panoDepth, Dir_To_JOSH1UVI((u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz)).r;
}
				)");
		}

		if (enableMask)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoMask;

float PanoMask(vec3 dir)
{
	return texture(u_panoMask, Dir_To_JOSH1UVI((u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz)).r;
}
				)");
		}
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_JOSH2()
	{
		shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoField;

vec3 Dir_To_Josh2UVI(vec3 dir)
{
	float c0 = dir.x;
	float c1 = -dir.x;
	float c2 = dir.y;
	float c3 = -dir.y;
	float c4 = dir.z;
	float c5 = -dir.z;

	float m01 = float(c0 < c1);
	float m23 = float(c2 < c3);
	float m45 = float(c4 < c5);
	float c01 = mix(c0, c1, m01);
	float c23 = mix(c2, c3, m23);
	float c45 = mix(c4, c5, m45);
	float i01 = mix(0.0f, 1.0f, m01);
	float i23 = mix(2.0f, 3.0f, m23);
	float i45 = mix(4.0f, 5.0f, m45);

	float m0123 = float(c01 < c23);
	float c0123 = mix(c01, c23, m0123);
	float i0123 = mix(i01, i23, m0123);

	int face = int(round(mix(i0123, i45, float(c0123 < c45))));
	vec4 s = u_inProjW2C[face] * vec4(dir, 1.0f);
	s /= s.w;
	
	//
	vec2 faceUV = (s.xy + 1.0f)*0.5f;
	float temp;
	vec3 warpUVI;
	if(face == 0)
	{
		warpUVI = vec3(faceUV, 5);
	}
	else if (face == 1)
	{
		temp = faceUV.y * ((0.5f + (1.0f - faceUV.x)) * 2.0f) + faceUV.x;
		warpUVI = vec3(
			faceUV.x, 
			mod(temp, 1.0f), 
			mix(
				mix(3.0f, 7.0f, float(temp < 2.0f)), 
				11.0f, float(temp < 1.0f)));
	}
	else if (face == 2)
	{
		temp = faceUV.y * ((0.5f + (1.0f - faceUV.x)) * 2.0f) + faceUV.x;
		warpUVI = vec3(
			faceUV.x, 
			mod(temp, 1.0f), 
			mix(
				mix(0.0f, 4.0f, float(temp < 2.0f)), 
				8.0f, float(temp < 1.0f)));
	}
	else if (face == 3)
	{
		temp = faceUV.y * ((0.5f + faceUV.x) * 2.0f) + (1.0f - faceUV.x);
		warpUVI = vec3(
			faceUV.x, 
			mod(temp, 1.0f), 
			mix(
				mix(2.0f, 6.0f, float(temp < 2.0f)), 
				10.0f, float(temp < 1.0f)));
	}
	else if (face == 4)
	{
		temp = faceUV.x * ((0.5f + faceUV.y) * 2.0f) + (1.0f - faceUV.y);
		warpUVI = vec3(
			mod(temp, 1.0f), 
			faceUV.y, 
			mix(
				mix(2.0f, 1.0f, float(temp < 2.0f)), 
				0.0f, float(temp < 1.0f)));
	}
	else if (face == 5)
	{
		temp = faceUV.x * ((0.5f + ( 1.0f - faceUV.y) ) * 2.0f) + faceUV.y;
		warpUVI = vec3(
			mod(temp, 1.0f), 
			faceUV.y, 
			mix(
				mix(10.0f, 9.0f, float(temp < 2.0f)), 
				8.0f, float(temp < 1.0f)));
	}

	return warpUVI;
}

vec4 PanoField(vec3 dir)
{
	return texture(u_panoField, Dir_To_Josh2UVI((u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz));
}
			)");

		if (enableDepth)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoDepth;

float PanoDepth(vec3 dir)
{
	return texture(u_panoDepth, Dir_To_Josh2UVI((u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz)).r;
}
				)");
		}

		if (enableMask)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoMask;

float PanoMask(vec3 dir)
{
	return texture(u_panoMask, Dir_To_Josh2UVI((u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz)).r;
}
				)");
		}
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_JOSH3()
	{
		shaderSources["canvas_frag"]->push_back(R"(
#define M_MERCATOR_RANGE	2.32175078194f // Mercator Evaluation Range
#define M_JOSH3_Z0			0.72499943359f // np.cos(np.arctan(0.95)) // 0.86602540378f // cos(M_PI/6.0f)
#define M_JOSH3_Z1			0.74329414625f // 0.91715233568f // cos(0.5f * (M_PI - M_MERCATOR_RANGE))
#define M_JOSH3_ZS			26.6136783392f // 19.5591631097f // 1.0f / (M_JOSH3_Z1 - M_JOSH3_Z0)

uniform int u_useCenterOnly;
uniform sampler2DArray u_panoField;

vec4 PanoField(vec3 dir)
{
	vec3 dir2 = (u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz;

	vec2 uv = Dir_To_MercatorUV(dir2);
	int vi = clamp(int(uv.y * 2.0f), 0, 1);
	int ui = clamp(int(uv.x * 2.0f), 0, 1);
	vec3 uvi = vec3(uv * 2.0f - vec2(ui, vi), vi * 2 + ui);

	if(u_useCenterOnly > 0)
	{
		return texture(u_panoField, uvi);
	}
	else
	{
		if(dir2.z > M_JOSH3_Z0)
		{
			vec4 s = u_inProjW2C[0] * vec4(dir2, 1.0f);
			s /= s.w;

			return mix( 
				texture(u_panoField, uvi), 
				texture(u_panoField, vec3(s.xy, 4)), 
				clamp((dir2.z - M_JOSH3_Z0) * M_JOSH3_ZS, 0.0f, 1.0f));
		}
		else if (dir2.z < -M_JOSH3_Z0)
		{
			vec4 s = u_inProjW2C[1] * vec4(dir2, 1.0f);
			s /= s.w;

			return mix( 
				texture(u_panoField, uvi), 
				texture(u_panoField, vec3(s.xy, 5)), 
				clamp((-dir2.z - M_JOSH3_Z0) * M_JOSH3_ZS, 0.0f, 1.0f));
		}
		else
		{
			return texture(u_panoField, uvi);
		}
	}
}
			)");

		if (enableDepth)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoDepth;

float PanoDepth(vec3 dir)
{
	vec3 dir2 = (u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz;

	vec2 uv = Dir_To_MercatorUV(dir2);
	int vi = clamp(int(uv.y * 2.0f), 0, 1);
	int ui = clamp(int(uv.x * 2.0f), 0, 1);
	vec3 uvi = vec3(uv * 2.0f - vec2(ui, vi), vi * 2 + ui);

	if(u_useCenterOnly > 0)
	{
		return texture(u_panoDepth, uvi).r;
	}
	else
	{
		if(dir2.z > M_JOSH3_Z0)
		{
			vec4 s = u_inProjW2C[0] * vec4(dir2, 1.0f);
			s /= s.w;

			return mix( 
				texture(u_panoDepth, uvi).r, 
				texture(u_panoDepth, vec3(s.xy, 4)).r, 
				clamp((dir2.z - M_JOSH3_Z0) * M_JOSH3_ZS, 0.0f, 1.0f));
		}
		else if (dir2.z < -M_JOSH3_Z0)
		{
			vec4 s = u_inProjW2C[1] * vec4(dir2, 1.0f);
			s /= s.w;

			return mix( 
				texture(u_panoDepth, uvi).r, 
				texture(u_panoDepth, vec3(s.xy, 5)).r, 
				clamp((-dir2.z - M_JOSH3_Z0) * M_JOSH3_ZS, 0.0f, 1.0f));
		}
		else
		{
			return texture(u_panoDepth, uvi).r;
		}
	}
}
				)");
		}

		if (enableMask)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoMask;

float PanoMask(vec3 dir)
{
	vec3 dir2 = (u_inProjTransformINV[0] * vec4(dir, 0.0f)).xyz;

	vec2 uv = Dir_To_MercatorUV(dir2);
	int vi = clamp(int(uv.y * 2.0f), 0, 1);
	int ui = clamp(int(uv.x * 2.0f), 0, 1);
	vec3 uvi = vec3(uv * 2.0f - vec2(ui, vi), vi * 2 + ui);

	if(u_useCenterOnly > 0)
	{
		return texture(u_panoMask, uvi).r;
	}
	else
	{
		if(dir2.z > M_JOSH3_Z0)
		{
			vec4 s = u_inProjW2C[0] * vec4(dir2, 1.0f);
			s /= s.w;

			return mix( 
				texture(u_panoMask, uvi).r, 
				texture(u_panoMask, vec3(s.xy, 4)).r, 
				clamp((dir2.z - M_JOSH3_Z0) * M_JOSH3_ZS, 0.0f, 1.0f));
		}
		else if (dir2.z < -M_JOSH3_Z0)
		{
			vec4 s = u_inProjW2C[1] * vec4(dir2, 1.0f);
			s /= s.w;

			return mix( 
				texture(u_panoMask, uvi).r, 
				texture(u_panoMask, vec3(s.xy, 5)).r, 
				clamp((-dir2.z - M_JOSH3_Z0) * M_JOSH3_ZS, 0.0f, 1.0f));
		}
		else
		{
			return texture(u_panoMask, uvi).r;
		}
	}
}
				)");
		}
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_JOSH1_X()
	{
		PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_MULTI_PERSPECTIVE();
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_PERSPECTIVE()
	{
		shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoField;

vec4 PanoField(vec3 dir)
{
	vec3 dir2 = (u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz;

	vec4 s = u_inProjW2C[0] * vec4(dir2, 1.0f);
	s /= s.w;
	vec3 uvi = (s.xyz + 1.0f)*0.5f;

	return mix( 
		vec4(255.0f, 255.0f, 255.0f, 1.0f), 
		texture(u_panoField, vec3(uvi.xy, RigID())), 
		float(length(floor(uvi)) < 1.0f));
}
			)");

		if (enableDepth)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoDepth;

float PanoDepth(vec3 dir)
{
	vec3 dir2 = (u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz;

	vec4 s = u_inProjW2C[0] * vec4(dir2, 1.0f);
	s /= s.w;
	vec3 uvi = (s.xyz + 1.0f)*0.5f;

	return mix( 
		0.0f, 
		texture(u_panoDepth, vec3(uvi.xy, RigID())).r, 
		float(length(floor(uvi)) < 1.0f));
}
				)");
		}

		if (enableMask)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoMask;

float PanoMask(vec3 dir)
{
	vec3 dir2 = (u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz;

	vec4 s = u_inProjW2C[0] * vec4(dir2, 1.0f);
	s /= s.w;
	vec3 uvi = (s.xyz + 1.0f)*0.5f;

	return mix( 
		0.0f, 
		texture(u_panoMask, vec3(uvi.xy, RigID())).r, 
		float(length(floor(uvi)) < 1.0f));
}
				)");
		}
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_EQUIRECTANGULAR()
	{
		shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoField;

vec4 PanoField(vec3 dir)
{
	return texture(u_panoField, vec3(Dir_To_EquirectangularUV((u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz), RigID()));
}
			)");

		if (enableDepth)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoDepth;

float PanoDepth(vec3 dir)
{
	return texture(u_panoDepth, vec3(Dir_To_EquirectangularUV((u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz), RigID())).r;
}
				)");
		}

		if (enableMask)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoMask;

float PanoMask(vec3 dir)
{
	return texture(u_panoMask, vec3(Dir_To_EquirectangularUV((u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz), RigID())).r;
}
				)");
		}
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_MERCATOR()
	{
		shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoField;

vec4 PanoField(vec3 dir)
{
	return texture(u_panoField, vec3(Dir_To_MercatorUV((u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz), RigID()));
}
			)");

		if (enableDepth)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoDepth;

float PanoDepth(vec3 dir)
{
	return texture(u_panoDepth, vec3(Dir_To_MercatorUV((u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz), RigID())).r;
}
				)");
		}

		if (enableMask)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoMask;

float PanoMask(vec3 dir)
{
	return texture(u_panoMask, vec3(Dir_To_MercatorUV((u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz), RigID())).r;
}
				)");
		}
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_MULTI_PERSPECTIVE()
	{
		shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoField;

vec4 PanoField(vec3 dir)
{
	vec3 dir2 = (u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz;

	vec4 s;
	float weight = 0.0f;
	float weightSum = 0.0f;
	vec3 field = vec3(0.0f, 0.0f, 0.0f);
	vec3 center = normalize(vec3(0.0f, 0.0f, 0.5f));

	vec3 uvi;
	for(uint i = 0 ; i < u_numPanoProjectionCameras ; ++i)
	{
		s = u_inProjW2C[i] * vec4(dir2, 1.0f);
		s /= s.w;
		uvi = (s.xyz + 1.0f)*0.5f;
		if(length(floor(uvi)) < 1.0f)
		{
			weight = u_inProjCameraWeight[i] * dot(normalize(vec3(s.xy, 0.5f)), center);
			field += weight * texture(u_panoField, vec3(uvi.xy, i * u_numRigCameras + RigID())).rgb;
			weightSum += weight;
		}
	}
	return vec4(field / weightSum, 1.0f);
}
			)");

		if (enableDepth)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoDepth;

float PanoDepth(vec3 dir)
{
	vec3 dir2 = (u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz;

	vec4 s;
	float weight = 0.0f;
	float weightSum = 0.0f;
	float depth = 0.0f;
	vec3 center = normalize(vec3(0.0f, 0.0f, 0.5f));

	vec3 uvi;
	for(uint i = 0 ; i < u_numPanoProjectionCameras ; ++i)
	{
		s = u_inProjW2C[i] * vec4(dir2, 1.0f);
		s /= s.w;
		uvi = (s.xyz + 1.0f)*0.5f;
		if((length(floor(uvi)) < 1.0f) )
		{
			weight = u_inProjCameraWeight[i] * dot(normalize(vec3(s.xy, 0.1f)), center);
			depth += weight * texture(u_panoDepth, vec3(uvi.xy, i * u_numRigCameras + RigID())).r;
			weightSum += weight;
		}
	}
	return depth / weightSum;
}
				)");
		}

		if (enableMask)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoMask;

float PanoMask(vec3 dir)
{
	vec3 dir2 = (u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz;

	vec4 s;
	float weight = 0.0f;
	float weightSum = 0.0f;
	float depth = 0.0f;
	vec3 center = normalize(vec3(0.0f, 0.0f, 0.5f));

	vec3 uvi;
	for(uint i = 0 ; i < u_numPanoProjectionCameras ; ++i)
	{
		s = u_inProjW2C[i] * vec4(dir2, 1.0f);
		s /= s.w;
		uvi = (s.xyz + 1.0f)*0.5f;
		if((length(floor(uvi)) < 1.0f) )
		{
			weight = u_inProjCameraWeight[i] * dot(normalize(vec3(s.xy, 0.1f)), center);
			depth += weight * texture(sampler2DArray, vec3(uvi.xy, i * u_numRigCameras + RigID())).r;
			weightSum += weight;
		}
	}
	return depth / weightSum;
}
				)");
		}
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_CUBEMAP()
	{
		shaderSources["canvas_frag"]->push_back(R"(
uniform samplerCubeArray u_panoField;

vec4 PanoField(vec3 dir)
{
	return texture(u_panoField, vec4((u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz, RigID()));
}
			)");

		if (enableDepth)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform samplerCubeArray u_panoDepth;

float PanoDepth(vec3 dir)
{
	return texture(u_panoDepth, vec4((u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz, RigID())).r;
}
				)");
		}

		if (enableMask)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform samplerCubeArray u_panoMask;

float PanoMask(vec3 dir)
{
	return texture(u_panoMask, vec4((u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz, RigID())).r;
}
				)");
		}
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_JOSH1()
	{
		shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoField;

vec3 Dir_To_JOSH1UVI(vec3 dir)
{
	float c0 = dir.x;
	float c1 = -dir.x;
	float c2 = dir.y;
	float c3 = -dir.y;
	float c4 = dir.z;
	float c5 = -dir.z;

	float m01 = float(c0 < c1);
	float m23 = float(c2 < c3);
	float m45 = float(c4 < c5);
	float c01 = mix(c0, c1, m01);
	float c23 = mix(c2, c3, m23);
	float c45 = mix(c4, c5, m45);
	float i01 = mix(0.0f, 1.0f, m01);
	float i23 = mix(2.0f, 3.0f, m23);
	float i45 = mix(4.0f, 5.0f, m45);

	float m0123 = float(c01 < c23);
	float c0123 = mix(c01, c23, m0123);
	float i0123 = mix(i01, i23, m0123);

	int face = int(round(mix(i0123, i45, float(c0123 < c45))));
	vec4 s = u_inProjW2C[face] * vec4(dir, 1.0f);
	s /= s.w;
	return vec3((s.xy + 1.0f)*0.5f, face);
}

vec4 PanoField(vec3 dir)
{
	return texture(u_panoField, Dir_To_JOSH1UVI((u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz) * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID()));
}
			)");

		if (enableDepth)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoDepth;

float PanoDepth(vec3 dir)
{
	return texture(u_panoDepth, Dir_To_JOSH1UVI((u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz) * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID())).r;
}
				)");
		}

		if (enableMask)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoMask;

float PanoMask(vec3 dir)
{
	return texture(u_panoMask, Dir_To_JOSH1UVI((u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz) * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID())).r;
}
				)");
		}
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_JOSH2()
	{
		shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoField;

vec3 Dir_To_Josh2UVI(vec3 dir)
{
	float c0 = dir.x;
	float c1 = -dir.x;
	float c2 = dir.y;
	float c3 = -dir.y;
	float c4 = dir.z;
	float c5 = -dir.z;

	float m01 = float(c0 < c1);
	float m23 = float(c2 < c3);
	float m45 = float(c4 < c5);
	float c01 = mix(c0, c1, m01);
	float c23 = mix(c2, c3, m23);
	float c45 = mix(c4, c5, m45);
	float i01 = mix(0.0f, 1.0f, m01);
	float i23 = mix(2.0f, 3.0f, m23);
	float i45 = mix(4.0f, 5.0f, m45);

	float m0123 = float(c01 < c23);
	float c0123 = mix(c01, c23, m0123);
	float i0123 = mix(i01, i23, m0123);

	int face = int(round(mix(i0123, i45, float(c0123 < c45))));
	vec4 s = u_inProjW2C[face] * vec4(dir, 1.0f);
	s /= s.w;
	
	//
	vec2 faceUV = (s.xy + 1.0f)*0.5f;
	float temp;
	vec3 warpUVI;
	if(face == 0)
	{
		warpUVI = vec3(faceUV, 5);
	}
	else if (face == 1)
	{
		temp = faceUV.y * ((0.5f + (1.0f - faceUV.x)) * 2.0f) + faceUV.x;
		warpUVI = vec3(
			faceUV.x, 
			mod(temp, 1.0f), 
			mix(
				mix(3.0f, 7.0f, float(temp < 2.0f)), 
				11.0f, float(temp < 1.0f)));
	}
	else if (face == 2)
	{
		temp = faceUV.y * ((0.5f + (1.0f - faceUV.x)) * 2.0f) + faceUV.x;
		warpUVI = vec3(
			faceUV.x, 
			mod(temp, 1.0f), 
			mix(
				mix(0.0f, 4.0f, float(temp < 2.0f)), 
				8.0f, float(temp < 1.0f)));
	}
	else if (face == 3)
	{
		temp = faceUV.y * ((0.5f + faceUV.x) * 2.0f) + (1.0f - faceUV.x);
		warpUVI = vec3(
			faceUV.x, 
			mod(temp, 1.0f), 
			mix(
				mix(2.0f, 6.0f, float(temp < 2.0f)), 
				10.0f, float(temp < 1.0f)));
	}
	else if (face == 4)
	{
		temp = faceUV.x * ((0.5f + faceUV.y) * 2.0f) + (1.0f - faceUV.y);
		warpUVI = vec3(
			mod(temp, 1.0f), 
			faceUV.y, 
			mix(
				mix(2.0f, 1.0f, float(temp < 2.0f)), 
				0.0f, float(temp < 1.0f)));
	}
	else if (face == 5)
	{
		temp = faceUV.x * ((0.5f + ( 1.0f - faceUV.y) ) * 2.0f) + faceUV.y;
		warpUVI = vec3(
			mod(temp, 1.0f), 
			faceUV.y, 
			mix(
				mix(10.0f, 9.0f, float(temp < 2.0f)), 
				8.0f, float(temp < 1.0f)));
	}

	return warpUVI;
}

vec4 PanoField(vec3 dir)
{
	return texture(u_panoField, Dir_To_Josh2UVI((u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz) * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID()));
}
			)");

		if (enableDepth)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoDepth;


float PanoDepth(vec3 dir)
{
	return texture(u_panoDepth, Dir_To_Josh2UVI((u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz) * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID())).r;
}
				)");
		}

		if (enableMask)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoMask;

float PanoMask(vec3 dir)
{
	return texture(u_panoMask, Dir_To_Josh2UVI((u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz) * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID())).r;
}
				)");
		}
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_JOSH3()
	{
		shaderSources["canvas_frag"]->push_back(R"(
#define M_MERCATOR_RANGE	2.32175078194f // Mercator Evaluation Range
#define M_JOSH3_Z0			0.72499943359f // np.cos(np.arctan(0.95)) // 0.86602540378f // cos(M_PI/6.0f)
#define M_JOSH3_Z1			0.74329414625f // 0.91715233568f // cos(0.5f * (M_PI - M_MERCATOR_RANGE))
#define M_JOSH3_ZS			26.6136783392f // 19.5591631097f // 1.0f / (M_JOSH3_Z1 - M_JOSH3_Z0)

uniform int u_useCenterOnly;
uniform sampler2DArray u_panoField;

vec4 PanoField(vec3 dir)
{
	vec3 dir2 = (u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz;

	vec2 uv = Dir_To_MercatorUV(dir2);
	int vi = clamp(int(uv.y * 2.0f), 0, 1);
	int ui = clamp(int(uv.x * 2.0f), 0, 1);
	vec3 uvi = vec3(uv * 2.0f - vec2(ui, vi), vi * 2 + ui);

	if(u_useCenterOnly > 0)
	{
		return texture(u_panoField, uvi * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID()));
	}
	else
	{
		if(dir2.z > M_JOSH3_Z0)
		{
			vec4 s = u_inProjW2C[0] * vec4(dir2, 1.0f);
			s /= s.w;

			return mix( 
				texture(u_panoField, uvi * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID())), 
				texture(u_panoField, vec3(s.xy, 4) * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID())), 
				clamp((dir2.z - M_JOSH3_Z0) * M_JOSH3_ZS, 0.0f, 1.0f));
		}
		else if (dir2.z < -M_JOSH3_Z0)
		{
			vec4 s = u_inProjW2C[1] * vec4(dir2, 1.0f);
			s /= s.w;

			return mix( 
				texture(u_panoField, uvi * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID())), 
				texture(u_panoField, vec3(s.xy, 5) * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID())), 
				clamp((-dir2.z - M_JOSH3_Z0) * M_JOSH3_ZS, 0.0f, 1.0f));
		}
		else
		{
			return texture(u_panoField, uvi * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID()));
		}
	}
}
			)");

		if (enableDepth)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoDepth;


float PanoDepth(vec3 dir)
{
	vec3 dir2 = (u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz;

	vec2 uv = Dir_To_MercatorUV(dir2);
	int vi = clamp(int(uv.y * 2.0f), 0, 1);
	int ui = clamp(int(uv.x * 2.0f), 0, 1);
	vec3 uvi = vec3(uv * 2.0f - vec2(ui, vi), vi * 2 + ui);

	if(u_useCenterOnly > 0)
	{
		return texture(u_panoDepth, uvi * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID())).r;
	}
	else
	{
		if(dir2.z > M_JOSH3_Z0)
		{
			vec4 s = u_inProjW2C[0] * vec4(dir2, 1.0f);
			s /= s.w;

			return mix( 
				texture(u_panoDepth, uvi * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID())).r, 
				texture(u_panoDepth, vec3(s.xy, 4) * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID())).r, 
				clamp((dir2.z - M_JOSH3_Z0) * M_JOSH3_ZS, 0.0f, 1.0f));
		}
		else if (dir2.z < -M_JOSH3_Z0)
		{
			vec4 s = u_inProjW2C[1] * vec4(dir2, 1.0f);
			s /= s.w;

			return mix( 
				texture(u_panoDepth, uvi * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID())).r, 
				texture(u_panoDepth, vec3(s.xy, 5) * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID())).r, 
				clamp((-dir2.z - M_JOSH3_Z0) * M_JOSH3_ZS, 0.0f, 1.0f));
		}
		else
		{
			return texture(u_panoDepth, uvi * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID())).r;
		}
	}
}
				)");
		}

		if (enableMask)
		{
			shaderSources["canvas_frag"]->push_back(R"(
uniform sampler2DArray u_panoMask;

float PanoMask(vec3 dir)
{
	vec3 dir2 = (u_inProjTransformINV[RigID()] * vec4(dir, 0.0f)).xyz;

	vec2 uv = Dir_To_MercatorUV(dir2);
	int vi = clamp(int(uv.y * 2.0f), 0, 1);
	int ui = clamp(int(uv.x * 2.0f), 0, 1);
	vec3 uvi = vec3(uv * 2.0f - vec2(ui, vi), vi * 2 + ui);

	if(u_useCenterOnly > 0)
	{
		return texture(u_panoMask, uvi * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID())).r;
	}
	else
	{
		if(dir2.z > M_JOSH3_Z0)
		{
			vec4 s = u_inProjW2C[0] * vec4(dir2, 1.0f);
			s /= s.w;

			return mix( 
				texture(u_panoMask, uvi * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID())).r, 
				texture(u_panoMask, vec3(s.xy, 4) * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID())).r, 
				clamp((dir2.z - M_JOSH3_Z0) * M_JOSH3_ZS, 0.0f, 1.0f));
		}
		else if (dir2.z < -M_JOSH3_Z0)
		{
			vec4 s = u_inProjW2C[1] * vec4(dir2, 1.0f);
			s /= s.w;

			return mix( 
				texture(u_panoMask, uvi * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID())).r, 
				texture(u_panoMask, vec3(s.xy, 5) * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID())).r, 
				clamp((-dir2.z - M_JOSH3_Z0) * M_JOSH3_ZS, 0.0f, 1.0f));
		}
		else
		{
			return texture(u_panoMask, uvi * vec3(1, 1, u_numRigCameras) + vec3(0, 0, RigID())).r;
		}
	}
}
				)");
		}
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_JOSH1_X()
	{
		PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_MULTI_PERSPECTIVE();
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_PERSPECTIVE()
	{
		shaderSources["canvas_frag"]->push_back(R"(
Ray3D GetFragViewRay(vec2 fragUV)
{
	vec4 ndc = vec4(fragUV * 2.0f - 1.0f, 1.0f, 1.0f);
	vec4 clip = ndc * CAM_FAR; // -(-CAM_FAR)
	vec3 eye = (u_outProjTransform[0] * u_outProjV2W[0] * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
	return Ray3D(eye, normalize((u_outProjTransform[0] * u_outProjC2W[0] * clip).xyz - eye));
}
			)");
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_EQUIRECTANGULAR()
	{
		shaderSources["canvas_frag"]->push_back(R"(
Ray3D GetFragViewRay(vec2 fragUV)
{
	return Ray3D(
			(u_outProjTransform[0] * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz, 
			(u_outProjTransform[0] * vec4(EquirectangularUV_To_Dir(fragUV), 0.0f)).xyz);
}
			)");
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_MERCATOR()
	{
		shaderSources["canvas_frag"]->push_back(R"(
Ray3D GetFragViewRay(vec2 fragUV)
{
	return Ray3D(
			(u_outProjTransform[0] * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz, 
			(u_outProjTransform[0] * vec4(MercatorUV_To_Dir(fragUV), 0.0f)).xyz);
}
			)");
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_MULTI_PERSPECTIVE()
	{
		shaderSources["canvas_frag"]->push_back(R"(
Ray3D GetFragViewRay(vec2 fragUV)
{
	int layerID = LayerID();
	vec4 ndc = vec4(fragUV * 2.0f - 1.0f, 1.0f, 1.0f);
	vec4 clip = ndc * CAM_FAR; // -(-CAM_FAR)
	vec3 eye = (u_outProjTransform[0] * u_outProjV2W[layerID] * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
	return Ray3D(eye, normalize((u_outProjTransform[0] * u_outProjC2W[layerID] * clip).xyz - eye));
}
			)");
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_CUBEMAP()
	{
		PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_MULTI_PERSPECTIVE();
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_JOSH1()
	{
		PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_MULTI_PERSPECTIVE();
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_JOSH2()
	{
		shaderSources["canvas_frag"]->push_back(R"(
Ray3D GetFragViewRayFace(int id, vec2 faceUV)
{
	vec4 ndc = vec4(faceUV * 2.0f - 1.0f, 1.0f, 1.0f);
	vec4 clip = ndc * CAM_FAR; // -(-CAM_FAR)
	vec3 eye = (u_outProjTransform[0] * u_outProjV2W[id] * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
	return Ray3D(eye, normalize((u_outProjTransform[0] * u_outProjC2W[id] * clip).xyz - eye));
}

Ray3D GetFragViewRayFace0(vec2 warpUV)
{
	vec2 faceUV = warpUV;
	return GetFragViewRayFace(0, faceUV);
}

Ray3D GetFragViewRayFace1(vec2 warpUV)
{
	float scale = (0.5f + (1.0f - warpUV.x)) * 2.0f;
	vec2 faceUV = vec2(
		warpUV.x, 
		warpUV.y / scale);
	return GetFragViewRayFace(1, faceUV);
}

Ray3D GetFragViewRayFace2(vec2 warpUV)
{
	float scale = (0.5f + (1.0f - warpUV.x)) * 2.0f;
	vec2 faceUV = vec2(
		warpUV.x, 
		warpUV.y / scale);
	return GetFragViewRayFace(2, faceUV);
}

Ray3D GetFragViewRayFace3(vec2 warpUV)
{
	float scale = (0.5f + warpUV.x) * 2.0f;
	vec2 faceUV = vec2(
		warpUV.x, 
		warpUV.y / scale);
	return GetFragViewRayFace(3, faceUV);
}

Ray3D GetFragViewRayFace4(vec2 warpUV)
{
	float scale = (0.5f + warpUV.y) * 2.0f;
	vec2 faceUV = vec2(
		warpUV.x / scale,
		warpUV.y);
	return GetFragViewRayFace(4, faceUV);
}

Ray3D GetFragViewRayFace5(vec2 warpUV)
{
	float scale = (0.5f + ( 1.0f - warpUV.y) ) * 2.0f;
	vec2 faceUV = vec2(
		warpUV.x / scale,
		warpUV.y);
	return GetFragViewRayFace(5, faceUV);
}

Ray3D GetFragViewRayFace6(vec2 warpUV)
{
	float scale = (0.5f + warpUV.y) * 2.0f;
	vec2 faceUV = vec2(
		warpUV.x / scale,
		warpUV.y);
	return GetFragViewRayFace(6, faceUV);
}

Ray3D GetFragViewRayFace7(vec2 warpUV)
{
	float scale = (0.5f + ( 1.0f - warpUV.y) ) * 2.0f;
	vec2 faceUV = vec2(
		warpUV.x / scale,
		warpUV.y);
	return GetFragViewRayFace(7, faceUV);
}

Ray3D GetFragViewRay(vec2 fragUV)
{
	int layerID = LayerID();
	if(layerID == 0)
	{
		if((fragUV.x + fragUV.y) > 1.0f)
		{
			return GetFragViewRayFace4( fragUV + 
				vec2(0.0f - (1.0f - fragUV.y), 0.0f) );
		}
		else
		{
			return GetFragViewRayFace2( fragUV + 
				vec2( 0.0f, 2.0f - fragUV.x) );
		}
	}
	else if (layerID == 4)
	{
		{
			return GetFragViewRayFace2( fragUV + 
				vec2( 0.0f, 1.0f - fragUV.x) );
		}
	}
	else if (layerID == 8)
	{
		if(fragUV.y > fragUV.x)
		{
			return GetFragViewRayFace2( fragUV + 
				vec2( 0.0f, 0.0f - fragUV.x) );
		}
		else
		{
			return GetFragViewRayFace5( fragUV + 
				vec2( 0.0f - fragUV.y, 0.0f) );
		}
	} //---------------------------------------
	else if (layerID == 1)
	{
		{
			return GetFragViewRayFace4( fragUV + 
				vec2(1.0f - (1.0f - fragUV.y), 0.0f) );
		}
	}
	else if (layerID == 5)
	{
		{
			return GetFragViewRayFace0( fragUV );
		}
	}
	else if (layerID == 9)
	{
		{
			return GetFragViewRayFace5( fragUV + 
				vec2( 1.0f - fragUV.y, 0.0f) );
		}
	}//---------------------------------------
	else if (layerID == 2)
	{
		if(fragUV.y > fragUV.x)
		{
			return GetFragViewRayFace4( fragUV + 
				vec2(2.0f - (1.0f - fragUV.y), 0.0f) );
		}
		else
		{
			return GetFragViewRayFace3( fragUV + 
				vec2( 0.0f, 2.0f - (1.0f - fragUV.x) ) );
		}
	}
	else if (layerID == 6)
	{
		{
			return GetFragViewRayFace3( fragUV + 
				vec2( 0.0f, 1.0f - (1.0f - fragUV.x) ) );
		}
	}
	else if (layerID == 10)
	{
		if((fragUV.x + fragUV.y) >1.0f)
		{
			return GetFragViewRayFace3( fragUV + 
				vec2( 0.0f, 0.0f - (1.0f - fragUV.x) ) );
		}
		else
		{
			return GetFragViewRayFace5( fragUV + 
				vec2( 2.0f - fragUV.y, 0.0f) );
		}
	}//---------------------------------------
	else if (layerID == 3)
	{
		if((fragUV.x + fragUV.y) >1.0f)
		{
			return GetFragViewRayFace6( fragUV + 
				vec2( 0.0f - (1.0f - fragUV.y), 0.0f) );
		}
		else
		{
			return GetFragViewRayFace1( fragUV + 
				vec2( 0.0f, 2.0f - fragUV.x) );
		}
	}
	else if (layerID == 7)
	{
		{
			return GetFragViewRayFace1( fragUV + 
				vec2( 0.0f, 1.0f - fragUV.x) );
		}
	}
	else if (layerID == 11)
	{
		if(fragUV.y > fragUV.x)
		{
			return GetFragViewRayFace1( fragUV + 
				vec2( 0.0f, 0.0f - fragUV.x) );
		}
		else
		{
			return GetFragViewRayFace7( fragUV + 
				vec2( 0.0f - fragUV.y, 0.0f) );
		}
	}//---------------------------------------
	return Ray3D(vec3(0.0f), vec3(0.0f));
}
			)");
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_JOSH3()
	{
		shaderSources["canvas_frag"]->push_back(R"(
Ray3D GetFragViewRay(vec2 fragUV)
{
	int layerID = LayerID();

	if(layerID < 4)
	{
		int vi = layerID / 2;
		int ui = layerID % 2;
		vec3 uvi = vec3(fragUV * 2.0f - vec2(ui, vi), vi * 2 + ui);

		return Ray3D(
			(u_outProjTransform[0] * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz, 
			(u_outProjTransform[0] * vec4(MercatorUV_To_Dir((fragUV + vec2(ui, vi)) * 0.5f), 0.0f)).xyz);
	}
	else if (layerID == 4)
	{
		vec4 ndc = vec4(fragUV * 2.0f - 1.0f, 1.0f, 1.0f);
		vec4 clip = ndc * CAM_FAR; // -(-CAM_FAR)
		vec3 eye = (u_outProjTransform[0] * u_outProjV2W[0] * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
		return Ray3D(eye, normalize((u_outProjTransform[0] * u_outProjC2W[0] * clip).xyz - eye));
	}
	else
	{
		vec4 ndc = vec4(fragUV * 2.0f - 1.0f, 1.0f, 1.0f);
		vec4 clip = ndc * CAM_FAR; // -(-CAM_FAR)
		vec3 eye = (u_outProjTransform[0] * u_outProjV2W[1] * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
		return Ray3D(eye, normalize((u_outProjTransform[0] * u_outProjC2W[1] * clip).xyz - eye));
	}
}
			)");
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_JOSH1_X()
	{
		PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_MULTI_PERSPECTIVE();
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_PERSPECTIVE()
	{
		shaderSources["canvas_frag"]->push_back(R"(
Ray3D GetFragViewRay(vec2 fragUV)
{
	vec4 ndc = vec4(fragUV * 2.0f - 1.0f, 1.0f, 1.0f);
	vec4 clip = ndc * CAM_FAR; // -(-CAM_FAR)
	vec3 eye = (u_outProjTransform[RigID()] * u_outProjV2W[0] * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
	return Ray3D(eye, normalize((u_outProjTransform[RigID()] * u_outProjC2W[0] * clip).xyz - eye));
}
			)");
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_EQUIRECTANGULAR()
	{
		shaderSources["canvas_frag"]->push_back(R"(
Ray3D GetFragViewRay(vec2 fragUV)
{
	return Ray3D(
			(u_outProjTransform[RigID()] * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz, 
			(u_outProjTransform[RigID()] * vec4(EquirectangularUV_To_Dir(fragUV), 0.0f)).xyz);
}
			)");
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_MERCATOR()
	{
		shaderSources["canvas_frag"]->push_back(R"(
Ray3D GetFragViewRay(vec2 fragUV)
{
	return Ray3D(
			(u_outProjTransform[RigID()] * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz, 
			(u_outProjTransform[RigID()] * vec4(MercatorUV_To_Dir(fragUV), 0.0f)).xyz);
}
			)");
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_MULTI_PERSPECTIVE()
	{
		shaderSources["canvas_frag"]->push_back(R"(
Ray3D GetFragViewRay(vec2 fragUV)
{
	int layerID = LayerID();
	vec4 ndc = vec4(fragUV * 2.0f - 1.0f, 1.0f, 1.0f);
	vec4 clip = ndc * CAM_FAR; // -(-CAM_FAR)
	vec3 eye = (u_outProjTransform[RigID()] * u_outProjV2W[layerID] * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
	return Ray3D(eye, normalize((u_outProjTransform[RigID()] * u_outProjC2W[layerID] * clip).xyz - eye));
}
			)");
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_CUBEMAP()
	{
		shaderSources["canvas_frag"]->push_back(R"(
Ray3D GetFragViewRay(vec2 fragUV)
{
	int layerID = LayerID();
	vec4 ndc = vec4(fragUV * 2.0f - 1.0f, 1.0f, 1.0f);
	vec4 clip = ndc * CAM_FAR; // -(-CAM_FAR)
	vec3 eye = (u_outProjTransform[RigID()] * u_outProjV2W[layerID] * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
	return Ray3D(eye, normalize((u_outProjTransform[RigID()] * u_outProjC2W[layerID] * clip).xyz - eye));
}
			)");
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_JOSH1()
	{
		shaderSources["canvas_frag"]->push_back(R"(
Ray3D GetFragViewRay(vec2 fragUV)
{
	int layerID = LayerID();
	vec4 ndc = vec4(fragUV * 2.0f - 1.0f, 1.0f, 1.0f);
	vec4 clip = ndc * CAM_FAR; // -(-CAM_FAR)
	vec3 eye = (u_outProjTransform[RigID()] * u_outProjV2W[layerID] * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
	return Ray3D(eye, normalize((u_outProjTransform[RigID()] * u_outProjC2W[layerID] * clip).xyz - eye));
}
			)");
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_JOSH2()
	{
		shaderSources["canvas_frag"]->push_back(R"(
Ray3D GetFragViewRayFace(int id, vec2 faceUV)
{
	vec4 ndc = vec4(faceUV * 2.0f - 1.0f, 1.0f, 1.0f);
	vec4 clip = ndc * CAM_FAR; // -(-CAM_FAR)
	vec3 eye = (u_outProjTransform[RigID()] * u_outProjV2W[id] * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
	return Ray3D(eye, normalize((u_outProjTransform[RigID()] * u_outProjC2W[id] * clip).xyz - eye));
}

Ray3D GetFragViewRayFace0(vec2 warpUV)
{
	vec2 faceUV = warpUV;
	return GetFragViewRayFace(0, faceUV);
}

Ray3D GetFragViewRayFace1(vec2 warpUV)
{
	float scale = (0.5f + (1.0f - warpUV.x)) * 2.0f;
	vec2 faceUV = vec2(
		warpUV.x, 
		warpUV.y / scale);
	return GetFragViewRayFace(1, faceUV);
}

Ray3D GetFragViewRayFace2(vec2 warpUV)
{
	float scale = (0.5f + (1.0f - warpUV.x)) * 2.0f;
	vec2 faceUV = vec2(
		warpUV.x, 
		warpUV.y / scale);
	return GetFragViewRayFace(2, faceUV);
}

Ray3D GetFragViewRayFace3(vec2 warpUV)
{
	float scale = (0.5f + warpUV.x) * 2.0f;
	vec2 faceUV = vec2(
		warpUV.x, 
		warpUV.y / scale);
	return GetFragViewRayFace(3, faceUV);
}

Ray3D GetFragViewRayFace4(vec2 warpUV)
{
	float scale = (0.5f + warpUV.y) * 2.0f;
	vec2 faceUV = vec2(
		warpUV.x / scale,
		warpUV.y);
	return GetFragViewRayFace(4, faceUV);
}

Ray3D GetFragViewRayFace5(vec2 warpUV)
{
	float scale = (0.5f + ( 1.0f - warpUV.y) ) * 2.0f;
	vec2 faceUV = vec2(
		warpUV.x / scale,
		warpUV.y);
	return GetFragViewRayFace(5, faceUV);
}

Ray3D GetFragViewRayFace6(vec2 warpUV)
{
	float scale = (0.5f + warpUV.y) * 2.0f;
	vec2 faceUV = vec2(
		warpUV.x / scale,
		warpUV.y);
	return GetFragViewRayFace(6, faceUV);
}

Ray3D GetFragViewRayFace7(vec2 warpUV)
{
	float scale = (0.5f + ( 1.0f - warpUV.y) ) * 2.0f;
	vec2 faceUV = vec2(
		warpUV.x / scale,
		warpUV.y);
	return GetFragViewRayFace(7, faceUV);
}

Ray3D GetFragViewRay(vec2 fragUV)
{
	int layerID = LayerID();
	if(layerID == 0)
	{
		if((fragUV.x + fragUV.y) > 1.0f)
		{
			return GetFragViewRayFace4( fragUV + 
				vec2(0.0f - (1.0f - fragUV.y), 0.0f) );
		}
		else
		{
			return GetFragViewRayFace2( fragUV + 
				vec2( 0.0f, 2.0f - fragUV.x) );
		}
	}
	else if (layerID == 4)
	{
		{
			return GetFragViewRayFace2( fragUV + 
				vec2( 0.0f, 1.0f - fragUV.x) );
		}
	}
	else if (layerID == 8)
	{
		if(fragUV.y > fragUV.x)
		{
			return GetFragViewRayFace2( fragUV + 
				vec2( 0.0f, 0.0f - fragUV.x) );
		}
		else
		{
			return GetFragViewRayFace5( fragUV + 
				vec2( 0.0f - fragUV.y, 0.0f) );
		}
	} //---------------------------------------
	else if (layerID == 1)
	{
		{
			return GetFragViewRayFace4( fragUV + 
				vec2(1.0f - (1.0f - fragUV.y), 0.0f) );
		}
	}
	else if (layerID == 5)
	{
		{
			return GetFragViewRayFace0( fragUV );
		}
	}
	else if (layerID == 9)
	{
		{
			return GetFragViewRayFace5( fragUV + 
				vec2( 1.0f - fragUV.y, 0.0f) );
		}
	}//---------------------------------------
	else if (layerID == 2)
	{
		if(fragUV.y > fragUV.x)
		{
			return GetFragViewRayFace4( fragUV + 
				vec2(2.0f - (1.0f - fragUV.y), 0.0f) );
		}
		else
		{
			return GetFragViewRayFace3( fragUV + 
				vec2( 0.0f, 2.0f - (1.0f - fragUV.x) ) );
		}
	}
	else if (layerID == 6)
	{
		{
			return GetFragViewRayFace3( fragUV + 
				vec2( 0.0f, 1.0f - (1.0f - fragUV.x) ) );
		}
	}
	else if (layerID == 10)
	{
		if((fragUV.x + fragUV.y) >1.0f)
		{
			return GetFragViewRayFace3( fragUV + 
				vec2( 0.0f, 0.0f - (1.0f - fragUV.x) ) );
		}
		else
		{
			return GetFragViewRayFace5( fragUV + 
				vec2( 2.0f - fragUV.y, 0.0f) );
		}
	}//---------------------------------------
	else if (layerID == 3)
	{
		if((fragUV.x + fragUV.y) >1.0f)
		{
			return GetFragViewRayFace6( fragUV + 
				vec2( 0.0f - (1.0f - fragUV.y), 0.0f) );
		}
		else
		{
			return GetFragViewRayFace1( fragUV + 
				vec2( 0.0f, 2.0f - fragUV.x) );
		}
	}
	else if (layerID == 7)
	{
		{
			return GetFragViewRayFace1( fragUV + 
				vec2( 0.0f, 1.0f - fragUV.x) );
		}
	}
	else if (layerID == 11)
	{
		if(fragUV.y > fragUV.x)
		{
			return GetFragViewRayFace1( fragUV + 
				vec2( 0.0f, 0.0f - fragUV.x) );
		}
		else
		{
			return GetFragViewRayFace7( fragUV + 
				vec2( 0.0f - fragUV.y, 0.0f) );
		}
	}//---------------------------------------
	return Ray3D(vec3(0.0f), vec3(0.0f));
}
			)");
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_JOSH3()
	{
		shaderSources["canvas_frag"]->push_back(R"(
Ray3D GetFragViewRay(vec2 fragUV)
{
	int layerID = LayerID();

	if(layerID < 4)
	{
		int vi = layerID / 2;
		int ui = layerID % 2;
		vec3 uvi = vec3(fragUV * 2.0f - vec2(ui, vi), vi * 2 + ui);

		return Ray3D(
			(u_outProjTransform[RigID()] * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz, 
			(u_outProjTransform[RigID()] * vec4(MercatorUV_To_Dir((fragUV + vec2(ui, vi)) * 0.5f), 0.0f)).xyz);
	}
	else if (layerID == 4)
	{
		vec4 ndc = vec4(fragUV * 2.0f - 1.0f, 1.0f, 1.0f);
		vec4 clip = ndc * CAM_FAR; // -(-CAM_FAR)
		vec3 eye = (u_outProjTransform[RigID()] * u_outProjV2W[0] * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
		return Ray3D(eye, normalize((u_outProjTransform[RigID()] * u_outProjC2W[0] * clip).xyz - eye));
	}
	else
	{
		vec4 ndc = vec4(fragUV * 2.0f - 1.0f, 1.0f, 1.0f);
		vec4 clip = ndc * CAM_FAR; // -(-CAM_FAR)
		vec3 eye = (u_outProjTransform[RigID()] * u_outProjV2W[1] * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
		return Ray3D(eye, normalize((u_outProjTransform[RigID()] * u_outProjC2W[1] * clip).xyz - eye));
	}
}
			)");
	}

	void PanoRenderBase::PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_JOSH1_X()
	{
		shaderSources["canvas_frag"]->push_back(R"(
Ray3D GetFragViewRay(vec2 fragUV)
{
	int layerID = LayerID();
	vec4 ndc = vec4(fragUV * 2.0f - 1.0f, 1.0f, 1.0f);
	vec4 clip = ndc * CAM_FAR; // -(-CAM_FAR)
	vec3 eye = (u_outProjTransform[RigID()] * u_outProjV2W[layerID] * vec4(0.0f, 0.0f, 0.0f, 1.0f)).xyz;
	return Ray3D(eye, normalize((u_outProjTransform[RigID()] * u_outProjC2W[layerID] * clip).xyz - eye));
}
			)");
	}

	void PanoRenderBase::CreateTexture(const std::string& name)
	{
		switch (rigMode)
		{
		case RigMode::MONO:
			switch (outProjMode)
			{
			case ProjectionMode::PERSPECTIVE:
			case ProjectionMode::EQUIRECTANGULAR:
			case ProjectionMode::MERCATOR:
				textures[name] = PTR<Texture>(new Texture(GL_TEXTURE_2D));
				break;

			case ProjectionMode::MULTI_PERSPECTIVE:
			case ProjectionMode::JOSH1:
			case ProjectionMode::JOSH2:
			case ProjectionMode::JOSH3:
			case ProjectionMode::JOSH1_X:
				textures[name] = PTR<Texture>(new Texture(GL_TEXTURE_2D_ARRAY));
				break;

			case ProjectionMode::CUBEMAP:
				textures[name] = PTR<Texture>(new Texture(GL_TEXTURE_CUBE_MAP));
				break;

			default:
				THROW_EXCEPTION("outProjMode is not supported");
				break;
			}
			break;

		case RigMode::MULTI:
			switch (outProjMode)
			{
			case ProjectionMode::PERSPECTIVE:
			case ProjectionMode::EQUIRECTANGULAR:
			case ProjectionMode::MERCATOR:
			case ProjectionMode::MULTI_PERSPECTIVE:
			case ProjectionMode::JOSH1:
			case ProjectionMode::JOSH2:
			case ProjectionMode::JOSH3:
			case ProjectionMode::JOSH1_X:
				textures[name] = PTR<Texture>(new Texture(GL_TEXTURE_2D_ARRAY));
				break;

			case ProjectionMode::CUBEMAP:
				textures[name] = PTR<Texture>(new Texture(GL_TEXTURE_CUBE_MAP_ARRAY));
				break;

			default:
				THROW_EXCEPTION("outProjMode is not supported");
				break;
			}
			break;

		default:
			THROW_EXCEPTION("rigMode is not supported");
			break;
		}
	}

	void PanoRenderBase::AllocateTexture(const std::string& name, GLint f, GLint w, GLint h)
	{
		switch (rigMode)
		{
		case RigMode::MONO:
			switch (outProjMode)
			{
			case ProjectionMode::PERSPECTIVE:
			case ProjectionMode::EQUIRECTANGULAR:
			case ProjectionMode::MERCATOR:
				textures[name]->Storage2D(1, f, w, h);
				break;

			case ProjectionMode::MULTI_PERSPECTIVE:
			case ProjectionMode::JOSH1:
			case ProjectionMode::JOSH1_X:
				textures[name]->Storage3D(1, f, w, h, (GLsizei)outProjCamera.size());
				break;

			case ProjectionMode::JOSH2:
				textures[name]->Storage3D(1, f, w, h, 12);
				break;

			case ProjectionMode::JOSH3:
				textures[name]->Storage3D(1, f, w, h, 6);
				break;

			case ProjectionMode::CUBEMAP:
				textures[name]->Storage2D(1, f, w, h);
				break;

			default:
				THROW_EXCEPTION("outProjMode is not supported");
				break;
			}
			break;

		case RigMode::MULTI:
			switch (outProjMode)
			{
			case ProjectionMode::PERSPECTIVE:
			case ProjectionMode::EQUIRECTANGULAR:
			case ProjectionMode::MERCATOR:
				textures[name]->Storage3D(1, f, w, h, (GLsizei)(rigW2V.size()));
				break;

			case ProjectionMode::MULTI_PERSPECTIVE:
			case ProjectionMode::JOSH1:
			case ProjectionMode::JOSH1_X:
				textures[name]->Storage3D(1, f, w, h, (GLsizei)(outProjCamera.size() * rigW2V.size()));
				break;

			case ProjectionMode::JOSH2:
				textures[name]->Storage3D(1, f, w, h, (GLsizei)(rigW2V.size() * 12));
				break;

			case ProjectionMode::JOSH3:
				textures[name]->Storage3D(1, f, w, h, (GLsizei)(rigW2V.size() * 6));
				break;

			case ProjectionMode::CUBEMAP:
				textures[name]->Storage3D(1, f, w, h, (GLsizei)(rigW2V.size() * 6));
				break;

			default:
				THROW_EXCEPTION("outProjMode is not supported");
				break;
			}
			break;

		default:
			THROW_EXCEPTION("rigMode is not supported");
			break;
		}
	}

	void PanoRenderBase::Setup()
	{
		switch (rigMode)
		{
		case RigMode::MONO:
			(*(std::vector<Mat44>*)(&this->rigW2V)).clear();
			(*(std::vector<Mat44>*)(&this->rigV2W)).clear();
			break;

		case RigMode::MULTI:
			if (rigW2V.size() < 2)
				THROW_EXCEPTION("rigMode RigMode::MULTI but rigW2V.size() < 2");
			(*(std::vector<Mat44>*)(&this->rigV2W)).resize(rigW2V.size());
			for (std::size_t i = 0; i < rigW2V.size(); ++i)
				(*(Mat44*)(&this->rigV2W[i])) = glm::inverse(rigW2V[i]);
			break;

		default:
			THROW_EXCEPTION("rigMode is not supported");
			break;
		}

		//
		switch (inProjMode)
		{
		case ProjectionMode::PERSPECTIVE:
			if (inProjCamera.size() != 1)
			{
				THROW_EXCEPTION("inProjMode ProjectionMode::PERSPECTIVE but inProjCamera.size() != 1");
			}
			break;

		case ProjectionMode::MULTI_PERSPECTIVE:
			if (inProjCamera.size() < 2)
			{
				THROW_EXCEPTION("inProjMode ProjectionMode::MULTI_PERSPECTIVE but inProjCamera.size() < 2");
			}
			break;

		case ProjectionMode::EQUIRECTANGULAR:
		case ProjectionMode::MERCATOR:
		case ProjectionMode::CUBEMAP:
			(*(std::vector<Camera>*)(&this->inProjCamera)).clear();
			(*((std::vector<Mat44>*) & inProjW2V)).clear();
			(*((std::vector<Mat44>*) & inProjW2C)).clear();
			(*((std::vector<Mat44>*) & inProjV2W)).clear();
			(*((std::vector<Mat44>*) & inProjC2W)).clear();
			(*((std::vector<GLfloat>*) & inProjCameraWeight)).clear();
			break;

		case ProjectionMode::JOSH1:
		case ProjectionMode::JOSH1_X:
			(*(std::vector<Camera>*)(&this->inProjCamera)).resize(6);
			(*((std::vector<Mat44>*) & inProjW2V)).resize(6);
			(*((std::vector<Mat44>*) & inProjW2C)).resize(6);
			(*((std::vector<Mat44>*) & inProjV2W)).resize(6);
			(*((std::vector<Mat44>*) & inProjC2W)).resize(6);
			(*((std::vector<GLfloat>*) & inProjCameraWeight)).resize(6);
			InitCamera_JOSH1(inProjCamera, JOSH1_fovY);
			break;

		case ProjectionMode::JOSH2:
			(*(std::vector<Camera>*)(&this->inProjCamera)).resize(8);
			(*((std::vector<Mat44>*) & inProjW2V)).resize(8);
			(*((std::vector<Mat44>*) & inProjW2C)).resize(8);
			(*((std::vector<Mat44>*) & inProjV2W)).resize(8);
			(*((std::vector<Mat44>*) & inProjC2W)).resize(8);
			(*((std::vector<GLfloat>*) & inProjCameraWeight)).resize(8);
			InitCamera_JOSH2(inProjCamera);
			break;

		case ProjectionMode::JOSH3:
			(*(std::vector<Camera>*)(&this->inProjCamera)).resize(2);
			(*((std::vector<Mat44>*) & inProjW2V)).resize(2);
			(*((std::vector<Mat44>*) & inProjW2C)).resize(2);
			(*((std::vector<Mat44>*) & inProjV2W)).resize(2);
			(*((std::vector<Mat44>*) & inProjC2W)).resize(2);
			(*((std::vector<GLfloat>*) & inProjCameraWeight)).resize(2);
			InitCamera_JOSH3(inProjCamera);
			break;

		default:
			THROW_EXCEPTION("inProjMode is not supported");
			break;
		}

		//
		switch (outProjMode)
		{
		case ProjectionMode::PERSPECTIVE:
			if (outProjCamera.size() != 1)
			{
				THROW_EXCEPTION("outProjMode ProjectionMode::PERSPECTIVE but outProjCamera.size() != 1");
			}
			break;

		case ProjectionMode::MULTI_PERSPECTIVE:
			if (outProjCamera.size() < 2)
			{
				THROW_EXCEPTION("outProjMode ProjectionMode::MULTI_PERSPECTIVE but outProjCamera.size() < 2");
			}
			break;

		case ProjectionMode::EQUIRECTANGULAR:
			(*(std::vector<Camera>*)(&this->outProjCamera)).clear();
			(*((std::vector<Mat44>*) & outProjW2V)).clear();
			(*((std::vector<Mat44>*) & outProjW2C)).clear();
			(*((std::vector<Mat44>*) & outProjC2W)).clear();
			(*((std::vector<Mat44>*) & outProjV2W)).clear();
			if (canvasWidth != canvasHeight * 2)
			{
				THROW_EXCEPTION("outProjMode ProjectionMode::EQUIRECTANGULAR but canvasWidth != canvasHeight * 2");
			}
			break;

		case ProjectionMode::MERCATOR:
			(*(std::vector<Camera>*)(&this->outProjCamera)).clear();
			(*((std::vector<Mat44>*) & outProjW2V)).clear();
			(*((std::vector<Mat44>*) & outProjW2C)).clear();
			(*((std::vector<Mat44>*) & outProjC2W)).clear();
			(*((std::vector<Mat44>*) & outProjV2W)).clear();
			if (canvasWidth != canvasHeight)
			{
				THROW_EXCEPTION("outProjMode ProjectionMode::MERCATOR but canvasWidth != canvasHeight");
			}
			break;

		case ProjectionMode::CUBEMAP:
			(*(std::vector<Camera>*)(&this->outProjCamera)).resize(6);
			(*((std::vector<Mat44>*) & outProjW2V)).resize(6);
			(*((std::vector<Mat44>*) & outProjW2C)).resize(6);
			(*((std::vector<Mat44>*) & outProjC2W)).resize(6);
			(*((std::vector<Mat44>*) & outProjV2W)).resize(6);
			InitCamera_CUBEMAP(outProjCamera);
			if (canvasWidth != canvasHeight)
			{
				THROW_EXCEPTION("outProjMode ProjectionMode::CUBEMAP but canvasWidth != canvasHeight");
			}
			break;

		case ProjectionMode::JOSH1:
		case ProjectionMode::JOSH1_X:
			(*(std::vector<Camera>*)(&this->outProjCamera)).resize(6);
			(*((std::vector<Mat44>*) & outProjW2V)).resize(6);
			(*((std::vector<Mat44>*) & outProjW2C)).resize(6);
			(*((std::vector<Mat44>*) & outProjC2W)).resize(6);
			(*((std::vector<Mat44>*) & outProjV2W)).resize(6);
			InitCamera_JOSH1(outProjCamera, JOSH1_fovY);
			break;

		case ProjectionMode::JOSH2:
			(*(std::vector<Camera>*)(&this->outProjCamera)).resize(8);
			(*((std::vector<Mat44>*) & outProjW2V)).resize(8);
			(*((std::vector<Mat44>*) & outProjW2C)).resize(8);
			(*((std::vector<Mat44>*) & outProjC2W)).resize(8);
			(*((std::vector<Mat44>*) & outProjV2W)).resize(8);
			InitCamera_JOSH2(outProjCamera);
			break;

		case ProjectionMode::JOSH3:
			(*(std::vector<Camera>*)(&this->outProjCamera)).resize(2);
			(*((std::vector<Mat44>*) & outProjW2V)).resize(2);
			(*((std::vector<Mat44>*) & outProjW2C)).resize(2);
			(*((std::vector<Mat44>*) & outProjC2W)).resize(2);
			(*((std::vector<Mat44>*) & outProjV2W)).resize(2);
			InitCamera_JOSH3(outProjCamera);
			if (canvasWidth != canvasHeight)
			{
				THROW_EXCEPTION("outProjMode ProjectionMode::JOSH3 but canvasWidth != canvasHeight");
			}
			break;

		default:
			THROW_EXCEPTION("outProjMode is not supported");
			break;
		}

		//
		switch (rigMode)
		{
		case RigMode::MONO:
			switch (inProjMode)
			{
			case ProjectionMode::PERSPECTIVE:
				PanoRender_Setup__rigMode_MONO__inProjMode_PERSPECTIVE();
				break;

			case ProjectionMode::EQUIRECTANGULAR:
				PanoRender_Setup__rigMode_MONO__inProjMode_EQUIRECTANGULAR();
				break;

			case ProjectionMode::MERCATOR:
				PanoRender_Setup__rigMode_MONO__inProjMode_MERCATOR();
				break;

			case ProjectionMode::MULTI_PERSPECTIVE:
				PanoRender_Setup__rigMode_MONO__inProjMode_MULTI_PERSPECTIVE();
				break;

			case ProjectionMode::CUBEMAP:
				PanoRender_Setup__rigMode_MONO__inProjMode_CUBEMAP();
				break;

			case ProjectionMode::JOSH1:
				PanoRender_Setup__rigMode_MONO__inProjMode_JOSH1();
				break;

			case ProjectionMode::JOSH2:
				PanoRender_Setup__rigMode_MONO__inProjMode_JOSH2();
				break;

			case ProjectionMode::JOSH3:
				PanoRender_Setup__rigMode_MONO__inProjMode_JOSH3();
				break;

			case ProjectionMode::JOSH1_X:
				PanoRender_Setup__rigMode_MONO__inProjMode_JOSH1_X();
				break;

			default:
				THROW_EXCEPTION("inProjMode is not supported");
				break;
			}
			break;

		case RigMode::MULTI:
			switch (inProjMode)
			{
			case ProjectionMode::PERSPECTIVE:
				PanoRender_Setup__rigMode_MULTI__inProjMode_PERSPECTIVE();
				break;

			case ProjectionMode::EQUIRECTANGULAR:
				PanoRender_Setup__rigMode_MULTI__inProjMode_EQUIRECTANGULAR();
				break;

			case ProjectionMode::MERCATOR:
				PanoRender_Setup__rigMode_MULTI__inProjMode_MERCATOR();
				break;

			case ProjectionMode::MULTI_PERSPECTIVE:
				PanoRender_Setup__rigMode_MULTI__inProjMode_MULTI_PERSPECTIVE();
				break;

			case ProjectionMode::CUBEMAP:
				PanoRender_Setup__rigMode_MULTI__inProjMode_CUBEMAP();
				break;

			case ProjectionMode::JOSH1:
				PanoRender_Setup__rigMode_MULTI__inProjMode_JOSH1();
				break;

			case ProjectionMode::JOSH2:
				PanoRender_Setup__rigMode_MULTI__inProjMode_JOSH2();
				break;

			case ProjectionMode::JOSH3:
				PanoRender_Setup__rigMode_MULTI__inProjMode_JOSH3();
				break;

			case ProjectionMode::JOSH1_X:
				PanoRender_Setup__rigMode_MULTI__inProjMode_JOSH1_X();
				break;

			default:
				THROW_EXCEPTION("inProjMode is not supported");
				break;
			}
			break;

		default:
			THROW_EXCEPTION("rigMode is not supported");
			break;
		}

		//
		switch (rigMode)
		{
		case RigMode::MONO:
			switch (outProjMode)
			{
			case ProjectionMode::MULTI_PERSPECTIVE:
			case ProjectionMode::CUBEMAP:
			case ProjectionMode::JOSH1:
			case ProjectionMode::JOSH1_X:
				(*(std::size_t*)(&layers)) = outProjCamera.size();
				break;

			case ProjectionMode::JOSH2:
				(*(std::size_t*)(&layers)) = 12;
				break;

			case ProjectionMode::JOSH3:
				(*(std::size_t*)(&layers)) = 6;
				break;

			}
			break;

		case RigMode::MULTI:
			switch (outProjMode)
			{
			case ProjectionMode::PERSPECTIVE:
			case ProjectionMode::EQUIRECTANGULAR:
			case ProjectionMode::MERCATOR:
				(*(std::size_t*)(&layers)) = rigW2V.size();
				break;

			case ProjectionMode::MULTI_PERSPECTIVE:
			case ProjectionMode::CUBEMAP:
			case ProjectionMode::JOSH1:
			case ProjectionMode::JOSH1_X:
				(*(std::size_t*)(&layers)) = outProjCamera.size() * rigW2V.size();
				break;

			case ProjectionMode::JOSH2:
				(*(std::size_t*)(&layers)) = 12 * rigW2V.size();
				break;

			case ProjectionMode::JOSH3:
				(*(std::size_t*)(&layers)) = 6 * rigW2V.size();
				break;

			default:
				THROW_EXCEPTION("outProjMode is not supported");
				break;
			}
			break;

		default:
			THROW_EXCEPTION("rigMode is not supported");
			break;
		}

		//
		switch (rigMode)
		{
		case RigMode::MONO:
			((std::vector<Mat44>*) & inProjTransform)->resize(1);
			((std::vector<Mat44>*) & outProjTransform)->resize(1);
			*((Mat44*)&inProjTransform[0]) = glm::identity<Mat44>();
			*((Mat44*)&outProjTransform[0]) = glm::identity<Mat44>();
			break;

		case RigMode::MULTI:
			((std::vector<Mat44>*) & inProjTransform)->resize(rigW2V.size());
			((std::vector<Mat44>*) & outProjTransform)->resize(rigW2V.size());
			for (std::size_t i = 0; i < rigW2V.size(); ++i)
			{
				*((Mat44*)&inProjTransform[i]) = glm::identity<Mat44>();
				*((Mat44*)&outProjTransform[i]) = glm::identity<Mat44>();
			}
			break;

		default:
			THROW_EXCEPTION("rigMode is not supported");
			break;
		}

		for (std::size_t i = 0; i < rigW2V.size(); ++i)
			(*(Mat44*)(&this->rigV2W[i])) = glm::inverse(rigW2V[i]);

		for (std::size_t i = 0; i < inProjCamera.size(); ++i)
		{
			Vec3 eye = inProjCamera[i].transform * Vec4(0.0f, 0.0f, 0.0f, 1.0f);
			Vec3 viewDir = inProjCamera[i].transform * Vec4(1.0f, 0.0f, 0.0f, 0.0f);
			Vec3 up = inProjCamera[i].transform * Vec4(0.0f, 0.0f, 1.0f, 0.0f);

			(*((Mat44*)&inProjW2V[i])) = glm::lookAt(eye, eye + viewDir, up);
			(*((Mat44*)&inProjW2C[i])) = inProjCamera[i].projection * inProjW2V[i];
			(*((Mat44*)&inProjV2W[i])) = glm::inverse(inProjW2V[i]);
			(*((Mat44*)&inProjC2W[i])) = glm::inverse(inProjW2C[i]);
			(*((GLfloat*)&inProjCameraWeight[i])) = 1.0f;
		}

		for (std::size_t i = 0; i < outProjCamera.size(); ++i)
		{
			Vec3 eye = outProjCamera[i].transform * Vec4(0.0f, 0.0f, 0.0f, 1.0f);
			Vec3 viewDir = outProjCamera[i].transform * Vec4(1.0f, 0.0f, 0.0f, 0.0f);
			Vec3 up = outProjCamera[i].transform * Vec4(0.0f, 0.0f, 1.0f, 0.0f);

			(*((Mat44*)&outProjW2V[i])) = glm::lookAt(eye, eye + viewDir, up);
			(*((Mat44*)&outProjW2C[i])) = outProjCamera[i].projection * outProjW2V[i];
			(*((Mat44*)&outProjV2W[i])) = glm::inverse(outProjW2V[i]);
			(*((Mat44*)&outProjC2W[i])) = glm::inverse(outProjW2C[i]);
		}
	}

	void PanoRenderBase::PanoRender_Setup__rigMode_MONO__inProjMode_PERSPECTIVE()
	{
		if (panoFieldTexture->Target() != GL_TEXTURE_2D)
			THROW_EXCEPTION("pano Field targets is not correct");
		if (enableDepth)
		{
			if (panoDepthTexture->Target() != GL_TEXTURE_2D)
				THROW_EXCEPTION("pano Depth targets is not correct");
		}
		if (enableMask)
		{
			if (panoMaskTexture->Target() != GL_TEXTURE_2D)
				THROW_EXCEPTION("pano Mask targets is not correct");
		}

		panoFieldSampler = samplers.at("plane_bilinear");
		if (enableDepth)
			panoDepthSampler = samplers.at("plane_bilinear");
		if (enableMask)
			panoMaskSampler = samplers.at("plane_bilinear");
	}

	void PanoRenderBase::PanoRender_Setup__rigMode_MONO__inProjMode_EQUIRECTANGULAR()
	{
		if (panoFieldTexture->Target() != GL_TEXTURE_2D)
			THROW_EXCEPTION("pano Field targets is not correct");
		if (enableDepth)
		{
			if (panoDepthTexture->Target() != GL_TEXTURE_2D)
				THROW_EXCEPTION("pano Depth targets is not correct");
		}
		if (enableMask)
		{
			if (panoMaskTexture->Target() != GL_TEXTURE_2D)
				THROW_EXCEPTION("pano Mask targets is not correct");
		}

		panoFieldSampler = samplers.at("equirectangular_bilinear");
		if (enableDepth)
			panoDepthSampler = samplers.at("equirectangular_bilinear");
		if (enableMask)
			panoMaskSampler = samplers.at("equirectangular_bilinear");
	}

	void PanoRenderBase::PanoRender_Setup__rigMode_MONO__inProjMode_MERCATOR()
	{
		if (panoFieldTexture->Target() != GL_TEXTURE_2D)
			THROW_EXCEPTION("pano Field targets is not correct");
		if (enableDepth)
		{
			if (panoDepthTexture->Target() != GL_TEXTURE_2D)
				THROW_EXCEPTION("pano Depth targets is not correct");
		}
		if (enableMask)
		{
			if (panoMaskTexture->Target() != GL_TEXTURE_2D)
				THROW_EXCEPTION("pano Mask targets is not correct");
		}

		panoFieldSampler = samplers.at("mercator_bilinear");
		if (enableDepth)
			panoDepthSampler = samplers.at("mercator_bilinear");
		if (enableMask)
			panoMaskSampler = samplers.at("mercator_bilinear");
	}

	void PanoRenderBase::PanoRender_Setup__rigMode_MONO__inProjMode_MULTI_PERSPECTIVE()
	{
		if (panoFieldTexture->Target() != GL_TEXTURE_2D_ARRAY)
			THROW_EXCEPTION("pano Field targets is not correct");
		if (enableDepth)
		{
			if (panoDepthTexture->Target() != GL_TEXTURE_2D_ARRAY)
				THROW_EXCEPTION("pano Depth targets is not correct");
		}
		if (enableMask)
		{
			if (panoMaskTexture->Target() != GL_TEXTURE_2D_ARRAY)
				THROW_EXCEPTION("pano Mask targets is not correct");
		}

		/*if (panoFieldTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != inProjCamera.size())
			THROW_EXCEPTION("panoFieldTexture depth is not correct");*/
		panoFieldSampler = samplers.at("plane_bilinear");
		if (enableDepth)
		{
			/*if (panoDepthTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != inProjCamera.size())
				THROW_EXCEPTION("panoDepthTexture depth is not correct");*/
			panoDepthSampler = samplers.at("plane_bilinear");
		}
		if (enableMask)
		{
			/*if (panoMaskTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != inProjCamera.size())
				THROW_EXCEPTION("panoMaskTexture depth is not correct");*/
			panoMaskSampler = samplers.at("plane_bilinear");
		}
	}

	void PanoRenderBase::PanoRender_Setup__rigMode_MONO__inProjMode_CUBEMAP()
	{
		if (panoFieldTexture->Target() != GL_TEXTURE_CUBE_MAP)
			THROW_EXCEPTION("pano Field targets is not correct");
		if (enableDepth)
		{
			if (panoDepthTexture->Target() != GL_TEXTURE_CUBE_MAP)
				THROW_EXCEPTION("pano Depth targets is not correct");
		}
		if (enableMask)
		{
			if (panoMaskTexture->Target() != GL_TEXTURE_CUBE_MAP)
				THROW_EXCEPTION("pano Mask targets is not correct");
		}

		panoFieldSampler = samplers.at("cube_bilinear");
		if (enableDepth)
			panoDepthSampler = samplers.at("cube_bilinear");
		if (enableMask)
			panoMaskSampler = samplers.at("cube_bilinear");
	}

	void PanoRenderBase::PanoRender_Setup__rigMode_MONO__inProjMode_JOSH1()
	{
		PanoRender_Setup__rigMode_MONO__inProjMode_MULTI_PERSPECTIVE();
		InitCamera_JOSH1(inProjCamera, JOSH1_fovY);
	}

	void PanoRenderBase::PanoRender_Setup__rigMode_MONO__inProjMode_JOSH2()
	{
		if (panoFieldTexture->Target() != GL_TEXTURE_2D_ARRAY)
			THROW_EXCEPTION("pano Field targets is not correct");
		if (enableDepth)
		{
			if (panoDepthTexture->Target() != GL_TEXTURE_2D_ARRAY)
				THROW_EXCEPTION("pano Depth targets is not correct");
		}
		if (enableMask)
		{
			if (panoMaskTexture->Target() != GL_TEXTURE_2D_ARRAY)
				THROW_EXCEPTION("pano Mask targets is not correct");
		}

		/*if (panoFieldTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != 12)
			THROW_EXCEPTION("panoFieldTexture depth is not correct");*/
		panoFieldSampler = samplers.at("plane_bilinear");
		if (enableDepth)
		{
			/*if (panoDepthTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != 12)
				THROW_EXCEPTION("panoDepthTexture depth is not correct");*/
			panoDepthSampler = samplers.at("plane_bilinear");
		}
		if (enableMask)
		{
			/*if (panoMaskTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != 12)
				THROW_EXCEPTION("panoMaskTexture depth is not correct");*/
			panoMaskSampler = samplers.at("plane_bilinear");
		}

		InitCamera_JOSH2(inProjCamera);
	}

	void PanoRenderBase::PanoRender_Setup__rigMode_MONO__inProjMode_JOSH3()
	{
		if (panoFieldTexture->Target() != GL_TEXTURE_2D_ARRAY)
			THROW_EXCEPTION("pano Field targets is not correct");
		if (enableDepth)
		{
			if (panoDepthTexture->Target() != GL_TEXTURE_2D_ARRAY)
				THROW_EXCEPTION("pano Depth targets is not correct");
		}
		if (enableMask)
		{
			if (panoMaskTexture->Target() != GL_TEXTURE_2D_ARRAY)
				THROW_EXCEPTION("pano Mask targets is not correct");
		}

		/*if (panoFieldTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != 6)
			THROW_EXCEPTION("panoFieldTexture depth is not correct");*/
		panoFieldSampler = samplers.at("plane_bilinear");
		if (enableDepth)
		{
			/*if (panoDepthTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != 6)
				THROW_EXCEPTION("panoDepthTexture depth is not correct");*/
			panoDepthSampler = samplers.at("plane_bilinear");
		}
		if (enableMask)
		{
			/*if (panoMaskTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != 6)
				THROW_EXCEPTION("panoMaskTexture depth is not correct");*/
			panoMaskSampler = samplers.at("plane_bilinear");
		}

		InitCamera_JOSH3(inProjCamera);
	}

	void PanoRenderBase::PanoRender_Setup__rigMode_MONO__inProjMode_JOSH1_X()
	{
		PanoRender_Setup__rigMode_MONO__inProjMode_MULTI_PERSPECTIVE();
		InitCamera_JOSH1(inProjCamera, JOSH1_fovY);
	}

	void PanoRenderBase::PanoRender_Setup__rigMode_MULTI__inProjMode_PERSPECTIVE()
	{
		if (panoFieldTexture->Target() != GL_TEXTURE_2D_ARRAY)
			THROW_EXCEPTION("pano Field targets is not correct");
		if (enableDepth)
		{
			if (panoDepthTexture->Target() != GL_TEXTURE_2D_ARRAY)
				THROW_EXCEPTION("pano Depth targets is not correct");
		}
		if (enableMask)
		{
			if (panoMaskTexture->Target() != GL_TEXTURE_2D_ARRAY)
				THROW_EXCEPTION("pano Mask targets is not correct");
		}

		/*if (panoFieldTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != rigW2V.size())
			THROW_EXCEPTION("panoFieldTexture depth is not correct");*/
		panoFieldSampler = samplers.at("plane_bilinear");
		if (enableDepth)
		{
			/*if (panoDepthTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != rigW2V.size())
				THROW_EXCEPTION("panoDepthTexture depth is not correct");*/
			panoDepthSampler = samplers.at("plane_bilinear");
		}
		if (enableMask)
		{
			/*if (panoMaskTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != rigW2V.size())
				THROW_EXCEPTION("panoMaskTexture depth is not correct");*/
			panoMaskSampler = samplers.at("plane_bilinear");
		}
	}

	void PanoRenderBase::PanoRender_Setup__rigMode_MULTI__inProjMode_EQUIRECTANGULAR()
	{
		if (panoFieldTexture->Target() != GL_TEXTURE_2D_ARRAY)
			THROW_EXCEPTION("pano Field targets is not correct");
		if (enableDepth)
		{
			if (panoDepthTexture->Target() != GL_TEXTURE_2D_ARRAY)
				THROW_EXCEPTION("pano Depth targets is not correct");
		}
		if (enableMask)
		{
			if (panoMaskTexture->Target() != GL_TEXTURE_2D_ARRAY)
				THROW_EXCEPTION("pano Mask targets is not correct");
		}

		/*if (panoFieldTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != rigW2V.size())
			THROW_EXCEPTION("panoFieldTexture depth is not correct");*/
		panoFieldSampler = samplers.at("equirectangular_bilinear");
		if (enableDepth)
		{
			/*if (panoDepthTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != rigW2V.size())
				THROW_EXCEPTION("panoDepthTexture depth is not correct");*/
			panoDepthSampler = samplers.at("equirectangular_bilinear");
		}
		if (enableMask)
		{
			/*if (panoMaskTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != rigW2V.size())
				THROW_EXCEPTION("panoMaskTexture depth is not correct");*/
			panoMaskSampler = samplers.at("equirectangular_bilinear");
		}
	}

	void PanoRenderBase::PanoRender_Setup__rigMode_MULTI__inProjMode_MERCATOR()
	{
		if (panoFieldTexture->Target() != GL_TEXTURE_2D_ARRAY)
			THROW_EXCEPTION("pano Field targets is not correct");
		if (enableDepth)
		{
			if (panoDepthTexture->Target() != GL_TEXTURE_2D_ARRAY)
				THROW_EXCEPTION("pano Depth targets is not correct");
		}
		if (enableMask)
		{
			if (panoMaskTexture->Target() != GL_TEXTURE_2D_ARRAY)
				THROW_EXCEPTION("pano Mask targets is not correct");
		}

		/*if (panoFieldTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != rigW2V.size())
			THROW_EXCEPTION("panoFieldTexture depth is not correct");*/
		panoFieldSampler = samplers.at("mercator_bilinear");
		if (enableDepth)
		{
			/*if (panoDepthTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != rigW2V.size())
				THROW_EXCEPTION("panoDepthTexture depth is not correct");*/
			panoDepthSampler = samplers.at("mercator_bilinear");
		}
		if (enableMask)
		{
			/*if (panoMaskTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != rigW2V.size())
				THROW_EXCEPTION("panoMaskTexture depth is not correct");*/
			panoMaskSampler = samplers.at("mercator_bilinear");
		}
	}

	void PanoRenderBase::PanoRender_Setup__rigMode_MULTI__inProjMode_MULTI_PERSPECTIVE()
	{
		if (panoFieldTexture->Target() != GL_TEXTURE_2D_ARRAY)
			THROW_EXCEPTION("pano Field targets is not correct");
		if (enableDepth)
		{
			if (panoDepthTexture->Target() != GL_TEXTURE_2D_ARRAY)
				THROW_EXCEPTION("pano Depth targets is not correct");
		}
		if (enableMask)
		{
			if (panoMaskTexture->Target() != GL_TEXTURE_2D_ARRAY)
				THROW_EXCEPTION("pano Mask targets is not correct");
		}

		/*if (panoFieldTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != inProjCamera.size() * rigW2V.size())
			THROW_EXCEPTION("panoFieldTexture depth is not correct");*/
		panoFieldSampler = samplers.at("plane_bilinear");
		if (enableDepth)
		{
			/*if (panoDepthTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != inProjCamera.size() * rigW2V.size())
				THROW_EXCEPTION("panoDepthTexture depth is not correct");*/
			panoDepthSampler = samplers.at("plane_bilinear");
		}
		if (enableMask)
		{
			/*if (panoMaskTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != inProjCamera.size() * rigW2V.size())
				THROW_EXCEPTION("panoMaskTexture depth is not correct");*/
			panoMaskSampler = samplers.at("plane_bilinear");
		}
	}

	void PanoRenderBase::PanoRender_Setup__rigMode_MULTI__inProjMode_CUBEMAP()
	{
		if (panoFieldTexture->Target() != GL_TEXTURE_CUBE_MAP_ARRAY)
			THROW_EXCEPTION("pano Field targets is not correct");
		if (enableDepth)
		{
			if (panoDepthTexture->Target() != GL_TEXTURE_CUBE_MAP_ARRAY)
				THROW_EXCEPTION("pano Depth targets is not correct");
		}
		if (enableMask)
		{
			if (panoMaskTexture->Target() != GL_TEXTURE_CUBE_MAP_ARRAY)
				THROW_EXCEPTION("pano Mask targets is not correct");
		}

		/*if (panoFieldTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != rigW2V.size() * 6)
			THROW_EXCEPTION("panoFieldTexture depth is not correct");*/
		panoFieldSampler = samplers.at("cube_bilinear");
		if (enableDepth)
		{
			/*if (panoDepthTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != rigW2V.size() * 6)
				THROW_EXCEPTION("panoDepthTexture depth is not correct");*/
			panoDepthSampler = samplers.at("cube_bilinear");
		}
		if (enableMask)
		{
			/*if (panoMaskTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != rigW2V.size() * 6)
				THROW_EXCEPTION("panoMaskTexture depth is not correct");*/
			panoMaskSampler = samplers.at("cube_bilinear");
		}
	}

	void PanoRenderBase::PanoRender_Setup__rigMode_MULTI__inProjMode_JOSH1()
	{
		PanoRender_Setup__rigMode_MULTI__inProjMode_MULTI_PERSPECTIVE();
		InitCamera_JOSH1(inProjCamera, JOSH1_fovY);
	}

	void PanoRenderBase::PanoRender_Setup__rigMode_MULTI__inProjMode_JOSH2()
	{
		if (panoFieldTexture->Target() != GL_TEXTURE_2D_ARRAY)
			THROW_EXCEPTION("pano Field targets is not correct");
		if (enableDepth)
		{
			if (panoDepthTexture->Target() != GL_TEXTURE_2D_ARRAY)
				THROW_EXCEPTION("pano Depth targets is not correct");
		}
		if (enableMask)
		{
			if (panoMaskTexture->Target() != GL_TEXTURE_2D_ARRAY)
				THROW_EXCEPTION("pano Mask targets is not correct");
		}

		/*if (panoFieldTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != 12 * rigW2V.size())
			THROW_EXCEPTION("panoFieldTexture depth is not correct");*/
		panoFieldSampler = samplers.at("plane_bilinear");
		if (enableDepth)
		{
			/*if (panoDepthTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != 12 * rigW2V.size())
				THROW_EXCEPTION("panoDepthTexture depth is not correct");*/
			panoDepthSampler = samplers.at("plane_bilinear");
		}
		if (enableMask)
		{
			/*if (panoMaskTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != 12 * rigW2V.size())
				THROW_EXCEPTION("panoMaskTexture depth is not correct");*/
			panoMaskSampler = samplers.at("plane_bilinear");
		}

		InitCamera_JOSH2(inProjCamera);
	}

	void PanoRenderBase::PanoRender_Setup__rigMode_MULTI__inProjMode_JOSH3()
	{
		if (panoFieldTexture->Target() != GL_TEXTURE_2D_ARRAY)
			THROW_EXCEPTION("pano Field targets is not correct");
		if (enableDepth)
		{
			if (panoDepthTexture->Target() != GL_TEXTURE_2D_ARRAY)
				THROW_EXCEPTION("pano Depth targets is not correct");
		}
		if (enableMask)
		{
			if (panoMaskTexture->Target() != GL_TEXTURE_2D_ARRAY)
				THROW_EXCEPTION("pano Mask targets is not correct");
		}

		/*if (panoFieldTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != 6 * rigW2V.size())
			THROW_EXCEPTION("panoFieldTexture depth is not correct");*/
		panoFieldSampler = samplers.at("plane_bilinear");
		if (enableDepth)
		{
			/*if (panoDepthTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != 6 * rigW2V.size())
				THROW_EXCEPTION("panoDepthTexture depth is not correct");*/
			panoDepthSampler = samplers.at("plane_bilinear");
		}
		if (enableMask)
		{
			/*if (panoMaskTexture->GetInfo<GLint>(0, GL_TEXTURE_DEPTH) != 6 * rigW2V.size())
				THROW_EXCEPTION("panoMaskTexture depth is not correct");*/
			panoMaskSampler = samplers.at("plane_bilinear");
		}

		InitCamera_JOSH3(inProjCamera);
	}

	void PanoRenderBase::PanoRender_Setup__rigMode_MULTI__inProjMode_JOSH1_X()
	{
		PanoRender_Setup__rigMode_MULTI__inProjMode_MULTI_PERSPECTIVE();
		InitCamera_JOSH1(inProjCamera, JOSH1_fovY);
	}

	//
	void PanoConverterRender::InitTexturesEvent()
	{
		PanoRenderBase::InitTexturesEvent();

		//
		{
			GLint tf = panoFieldTexture->GetInfo<GLint>(0, GL_TEXTURE_INTERNAL_FORMAT);
			GLint tw = CanvasWidth();
			GLint th = CanvasHeight();

			GLint cf = textures["canvas_field"]->GetInfo<GLint>(0, GL_TEXTURE_INTERNAL_FORMAT);
			GLint cw = textures["canvas_field"]->GetInfo<GLint>(0, GL_TEXTURE_WIDTH);
			GLint ch = textures["canvas_field"]->GetInfo<GLint>(0, GL_TEXTURE_HEIGHT);

			if ((tf != cf) || (tw != cw) || (th != ch))
				AllocateTexture("canvas_field", tf, tw, th);
		}

		if (enableDepth)
		{
			GLint tf = panoDepthTexture->GetInfo<GLint>(0, GL_TEXTURE_INTERNAL_FORMAT);
			GLint tw = CanvasWidth();
			GLint th = CanvasHeight();

			GLint cf = textures["canvas_depth"]->GetInfo<GLint>(0, GL_TEXTURE_INTERNAL_FORMAT);
			GLint cw = textures["canvas_depth"]->GetInfo<GLint>(0, GL_TEXTURE_WIDTH);
			GLint ch = textures["canvas_depth"]->GetInfo<GLint>(0, GL_TEXTURE_HEIGHT);

			if ((tf != cf) || (tw != cw) || (th != ch))
				AllocateTexture("canvas_depth", tf, tw, th);
		}

		if (enableMask)
		{
			GLint tf = panoMaskTexture->GetInfo<GLint>(0, GL_TEXTURE_INTERNAL_FORMAT);
			GLint tw = CanvasWidth();
			GLint th = CanvasHeight();

			GLint cf = textures["canvas_mask"]->GetInfo<GLint>(0, GL_TEXTURE_INTERNAL_FORMAT);
			GLint cw = textures["canvas_mask"]->GetInfo<GLint>(0, GL_TEXTURE_WIDTH);
			GLint ch = textures["canvas_mask"]->GetInfo<GLint>(0, GL_TEXTURE_HEIGHT);

			if ((tf != cf) || (tw != cw) || (th != ch))
				AllocateTexture("canvas_mask", tf, tw, th);
		}
	}

	void PanoConverterRender::InitFragmentShaderHeadersEvent()
	{
		PanoRenderBase::InitFragmentShaderHeadersEvent();

		//
		{
			shaderSources["canvas_frag"]->push_back(R"(
layout(location = 0) out vec4 f_field;
				)");
		}

		if (enableDepth && enableMask)
		{
			shaderSources["canvas_frag"]->push_back(R"(
layout(location = 1) out vec4 f_depth;
layout(location = 2) out vec4 f_mask;
				)");
		}
		else
		{
			if (enableDepth)
			{
				shaderSources["canvas_frag"]->push_back(R"(
layout(location = 1) out vec4 f_depth;
					)");
			}

			if (enableMask)
			{
				shaderSources["canvas_frag"]->push_back(R"(
layout(location = 1) out vec4 f_mask;
					)");
			}
		}
	}

	void PanoConverterRender::InitFragmentShaderMainsEvent()
	{
		if (enableDepth && enableMask)
		{
			shaderSources["canvas_frag"]->push_back(R"(
void main(void)
{
	vec3 viewDir = GetFragViewRay(gl_FragCoord.xy / vec2(u_canvasWidth, u_canvasHeight)).d;
	f_field = PanoField(viewDir);
	f_depth = vec4(PanoDepth(viewDir), 0.0f, 0.0f, 1.0f);
	f_mask = vec4(PanoMask(viewDir), 0.0f, 0.0f, 1.0f);
}
				)");
		}
		else if (enableDepth)
		{
			shaderSources["canvas_frag"]->push_back(R"(
void main(void)
{
	vec3 viewDir = GetFragViewRay(gl_FragCoord.xy / vec2(u_canvasWidth, u_canvasHeight)).d;
	f_field = PanoField(viewDir);
	f_depth = vec4(PanoDepth(viewDir), 0.0f, 0.0f, 1.0f);
}
				)");
		}
		else if (enableMask)
		{
			shaderSources["canvas_frag"]->push_back(R"(
void main(void)
{
	vec3 viewDir = GetFragViewRay(gl_FragCoord.xy / vec2(u_canvasWidth, u_canvasHeight)).d;
	f_field = PanoField(viewDir);
	f_mask = vec4(PanoMask(viewDir), 0.0f, 0.0f, 1.0f);
}
				)");
		}
		else
		{
			shaderSources["canvas_frag"]->push_back(R"(
void main(void)
{
	vec3 viewDir = GetFragViewRay(gl_FragCoord.xy / vec2(u_canvasWidth, u_canvasHeight)).d;
	f_field = PanoField(viewDir);
}
				)");
		}
	}

	void PanoConverterRender::InitFrameBuffersEvent()
	{
		PanoRenderBase::InitFrameBuffersEvent();

		//
		if (enableDepth && enableMask)
		{
			frameBuffers["canvas"]->Attach(GL_COLOR_ATTACHMENT0, *textures["canvas_field"], 0);
			frameBuffers["canvas"]->Attach(GL_COLOR_ATTACHMENT1, *textures["canvas_depth"], 0);
			frameBuffers["canvas"]->Attach(GL_COLOR_ATTACHMENT2, *textures["canvas_mask"], 0);

			std::vector<GLenum> attachments{ GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
			frameBuffers["canvas"]->DrawBuffer(attachments);
		}
		else if (enableDepth)
		{
			frameBuffers["canvas"]->Attach(GL_COLOR_ATTACHMENT0, *textures["canvas_field"], 0);
			frameBuffers["canvas"]->Attach(GL_COLOR_ATTACHMENT1, *textures["canvas_depth"], 0);

			std::vector<GLenum> attachments{ GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
			frameBuffers["canvas"]->DrawBuffer(attachments);
		}
		else if (enableMask)
		{
			frameBuffers["canvas"]->Attach(GL_COLOR_ATTACHMENT0, *textures["canvas_field"], 0);
			frameBuffers["canvas"]->Attach(GL_COLOR_ATTACHMENT1, *textures["canvas_mask"], 0);

			std::vector<GLenum> attachments{ GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
			frameBuffers["canvas"]->DrawBuffer(attachments);
		}
		else
		{
			frameBuffers["canvas"]->Attach(GL_COLOR_ATTACHMENT0, *textures["canvas_field"], 0);

			std::vector<GLenum> attachments{ GL_COLOR_ATTACHMENT0 };
			frameBuffers["canvas"]->DrawBuffer(attachments);
		}
	}

	void PanoConverterRender::PostDrawEvent() const
	{
		if (enableMask)
			textures.at("canvas_mask")->GenMipmaps();
		if (enableDepth)
			textures.at("canvas_depth")->GenMipmaps();
		textures.at("canvas_field")->GenMipmaps();

		//
		PanoRenderBase::PostDrawEvent();
	}

	void PanoConverterRender::Setup()
	{
		if (enableDepth && enableMask)
		{
			GLint n = 0;
			glGetIntegerv(GL_MAX_DRAW_BUFFERS, &n);
			if (n < 3)
				THROW_EXCEPTION("GL_MAX_DRAW_BUFFERS must at least 3");
		}
		else if (enableDepth || enableMask)
		{
			GLint n = 0;
			glGetIntegerv(GL_MAX_DRAW_BUFFERS, &n);
			if (n < 2)
				THROW_EXCEPTION("GL_MAX_DRAW_BUFFERS must at least 2");
		}

		CreateTexture("canvas_field");
		if (enableDepth)
			CreateTexture("canvas_depth");
		if (enableMask)
			CreateTexture("canvas_mask");
	}
};