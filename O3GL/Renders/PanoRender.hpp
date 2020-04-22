#pragma once

// O3GL
#include "O3GL/Renders/CanvasRender.hpp"

// 
namespace O3GL
{
	//
	enum class ProjectionMode
	{
		PERSPECTIVE,
		EQUIRECTANGULAR,
		MERCATOR,
		MULTI_PERSPECTIVE,
		CUBEMAP,
		JOSH1,
		JOSH2,
		JOSH3,
		JOSH1_X
	};

	enum class RigMode
	{
		MONO,
		MULTI,
	};

	//
	class PanoRenderBase : public CanvasRender
	{
	protected:
		virtual void InitGeometryShaderHeadersEvent();
		virtual void InitGeometryShaderMainsEvent();
		virtual void InitFragmentShaderHeadersEvent();
		virtual void InitProgramParametersEvent() const;

	protected:
		virtual void PreDrawEvent() const;
		virtual void PostDrawEvent() const;

	public:
		static void InitCamera_CUBEMAP(const std::vector<Camera>& cameras);
		static void InitCamera_JOSH1(const std::vector<Camera>& cameras, GLfloat fovY);
		static void InitCamera_JOSH2(const std::vector<Camera>& cameras);
		static void InitCamera_JOSH3(const std::vector<Camera>& cameras);

	protected:
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_PERSPECTIVE();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_EQUIRECTANGULAR();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_MERCATOR();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_MULTI_PERSPECTIVE();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_CUBEMAP();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_JOSH1();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_JOSH2();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_JOSH3();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_JOSH1_X();

		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_PERSPECTIVE();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_EQUIRECTANGULAR();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_MERCATOR();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_MULTI_PERSPECTIVE();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_CUBEMAP();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_JOSH1();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_JOSH2();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_JOSH3();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_JOSH1_X();

		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_PERSPECTIVE();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_EQUIRECTANGULAR();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_MERCATOR();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_MULTI_PERSPECTIVE();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_CUBEMAP();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_JOSH1();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_JOSH2();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_JOSH3();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_JOSH1_X();

		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_PERSPECTIVE();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_EQUIRECTANGULAR();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_MERCATOR();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_MULTI_PERSPECTIVE();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_CUBEMAP();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_JOSH1();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_JOSH2();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_JOSH3();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_JOSH1_X();

		void CreateTexture(const std::string& name);
		void AllocateTexture(const std::string& name, GLint f, GLint w, GLint h);

	public:
		PanoRenderBase(
			GLint canvasWidth, GLint canvasHeight,
			RigMode rigMode, const std::vector<Mat44>& rigW2V,
			ProjectionMode inProjMode, const std::vector<Camera>& inProjCamera,
			ProjectionMode outProjMode, const std::vector<Camera>& outProjCamera,
			const CONST_PTR<Texture>& panoFieldTexture) :
			CanvasRender(canvasWidth, canvasHeight),
			rigMode(rigMode), rigW2V(rigW2V), rigV2W(),
			inProjMode(inProjMode), inProjTransform(), inProjCamera(inProjCamera),
			outProjMode(outProjMode), outProjTransform(), outProjCamera(outProjCamera),
			panoFieldSampler(), panoFieldTexture(panoFieldTexture),
			enableField(true), enableDepth(false), enableMask(false),
			JOSH1_fovY(90.0f),
			inProjW2V(inProjCamera.size()), inProjW2C(inProjCamera.size()), inProjC2W(inProjCamera.size()), inProjV2W(inProjCamera.size()), inProjCameraWeight(),
			outProjW2V(outProjCamera.size()), outProjW2C(outProjCamera.size()), outProjV2W(outProjCamera.size()), outProjC2W(outProjCamera.size()),
			layers(1), JOSH3_useCenterOnly(0)
		{
			Setup();
		}

		PanoRenderBase(
			GLint canvasWidth, GLint canvasHeight,
			RigMode rigMode, const std::vector<Mat44>& rigW2V,
			ProjectionMode inProjMode, const std::vector<Camera>& inProjCamera,
			ProjectionMode outProjMode, const std::vector<Camera>& outProjCamera,
			const CONST_PTR<Texture>& panoFieldTexture, const CONST_PTR<Texture>& panoDepthTexture) :
			CanvasRender(canvasWidth, canvasHeight),
			rigMode(rigMode), rigW2V(rigW2V), rigV2W(),
			inProjMode(inProjMode), inProjTransform(), inProjCamera(inProjCamera),
			outProjMode(outProjMode), outProjTransform(), outProjCamera(outProjCamera),
			panoFieldSampler(), panoDepthSampler(), panoFieldTexture(panoFieldTexture), panoDepthTexture(panoDepthTexture),
			enableField(true), enableDepth(true), enableMask(false),
			JOSH1_fovY(90.0f),
			inProjW2V(inProjCamera.size()), inProjW2C(inProjCamera.size()), inProjC2W(inProjCamera.size()), inProjV2W(inProjCamera.size()), inProjCameraWeight(),
			outProjW2V(outProjCamera.size()), outProjW2C(outProjCamera.size()), outProjV2W(outProjCamera.size()), outProjC2W(outProjCamera.size()),
			layers(1), JOSH3_useCenterOnly(0)
		{
			Setup();
		}

		PanoRenderBase(
			GLint canvasWidth, GLint canvasHeight,
			RigMode rigMode, const std::vector<Mat44>& rigW2V,
			ProjectionMode inProjMode, const std::vector<Camera>& inProjCamera,
			ProjectionMode outProjMode, const std::vector<Camera>& outProjCamera,
			const CONST_PTR<Texture>& panoFieldTexture, const CONST_PTR<Texture>& panoDepthTexture, const CONST_PTR<Texture>& panoMaskTexture) :
			CanvasRender(canvasWidth, canvasHeight),
			rigMode(rigMode), rigW2V(rigW2V), rigV2W(),
			inProjMode(inProjMode), inProjTransform(), inProjCamera(inProjCamera),
			outProjMode(outProjMode), outProjTransform(), outProjCamera(outProjCamera),
			panoFieldSampler(), panoDepthSampler(), panoMaskSampler(), panoFieldTexture(panoFieldTexture), panoDepthTexture(panoDepthTexture), panoMaskTexture(panoMaskTexture),
			enableField(true), enableDepth(true), enableMask(true),
			JOSH1_fovY(90.0f),
			inProjW2V(inProjCamera.size()), inProjW2C(inProjCamera.size()), inProjC2W(inProjCamera.size()), inProjV2W(inProjCamera.size()), inProjCameraWeight(),
			outProjW2V(outProjCamera.size()), outProjW2C(outProjCamera.size()), outProjV2W(outProjCamera.size()), outProjC2W(outProjCamera.size()),
			layers(1), JOSH3_useCenterOnly(0)
		{
			Setup();
		}

		void SetInProjTransform(Mat44 inProjTransform) const
		{
			for (const Mat44& m : this->inProjTransform)
				*((Mat44*)&m) = inProjTransform;
		}

		void SetOutProjTransform(Mat44 outProjTransform) const
		{
			for (const Mat44& m : this->outProjTransform)
				*((Mat44*)&m) = outProjTransform;
		}

		void SetInProjTransform(const std::vector<Mat44>& inProjTransform) const
		{
			*((std::vector<Mat44>*) & this->inProjTransform) = inProjTransform;
		}

		void SetOutProjTransform(const std::vector<Mat44>& outProjTransform) const
		{
			*((std::vector<Mat44>*) & this->outProjTransform) = outProjTransform;
		}

		void SetInProjCameraWeight(const std::vector<GLfloat>& inProjCameraWeight) const
		{
			*((std::vector<GLfloat>*) & this->inProjCameraWeight) = inProjCameraWeight;
		}

		void SetJOSH1_fovY(GLfloat JOSH1_fovY) const
		{
			*((GLfloat*)&this->JOSH1_fovY) = JOSH1_fovY;
		}

		void SetJOSH3_useCenterOnly(GLint JOSH3_useCenterOnly) const
		{
			*((GLint*)&this->JOSH3_useCenterOnly) = JOSH3_useCenterOnly;
		}

	protected:
		void Setup();

		void PanoRender_Setup__rigMode_MONO__inProjMode_PERSPECTIVE();
		void PanoRender_Setup__rigMode_MONO__inProjMode_EQUIRECTANGULAR();
		void PanoRender_Setup__rigMode_MONO__inProjMode_MERCATOR();
		void PanoRender_Setup__rigMode_MONO__inProjMode_MULTI_PERSPECTIVE();
		void PanoRender_Setup__rigMode_MONO__inProjMode_CUBEMAP();
		void PanoRender_Setup__rigMode_MONO__inProjMode_JOSH1();
		void PanoRender_Setup__rigMode_MONO__inProjMode_JOSH2();
		void PanoRender_Setup__rigMode_MONO__inProjMode_JOSH3();
		void PanoRender_Setup__rigMode_MONO__inProjMode_JOSH1_X();

		void PanoRender_Setup__rigMode_MULTI__inProjMode_PERSPECTIVE();
		void PanoRender_Setup__rigMode_MULTI__inProjMode_EQUIRECTANGULAR();
		void PanoRender_Setup__rigMode_MULTI__inProjMode_MERCATOR();
		void PanoRender_Setup__rigMode_MULTI__inProjMode_MULTI_PERSPECTIVE();
		void PanoRender_Setup__rigMode_MULTI__inProjMode_CUBEMAP();
		void PanoRender_Setup__rigMode_MULTI__inProjMode_JOSH1();
		void PanoRender_Setup__rigMode_MULTI__inProjMode_JOSH2();
		void PanoRender_Setup__rigMode_MULTI__inProjMode_JOSH3();
		void PanoRender_Setup__rigMode_MULTI__inProjMode_JOSH1_X();

	protected:
		const bool enableField;
		const bool enableDepth;
		const bool enableMask;

		CONST_PTR<Sampler> panoFieldSampler;
		CONST_PTR<Sampler> panoDepthSampler;
		CONST_PTR<Sampler> panoMaskSampler;

		CONST_PTR<Texture> panoFieldTexture;
		CONST_PTR<Texture> panoDepthTexture;
		CONST_PTR<Texture> panoMaskTexture;

		const std::size_t layers;

	protected:
		const ProjectionMode inProjMode;
		const std::vector<Mat44> inProjTransform;

		// for inProjMode: JOSH1_X
		const GLfloat JOSH1_fovY;

		// for inProjMode: MULTI_PERSPECTIVE, CUBEMAP, JOSH1, JOSH2, JOSH3, JOSH1_X
		const std::vector<Camera> inProjCamera;
		const std::vector<Mat44> inProjW2V;
		const std::vector<Mat44> inProjW2C;
		const std::vector<Mat44> inProjV2W;
		const std::vector<Mat44> inProjC2W;

		// for inProjMode: MULTI_PERSPECTIVE, JOSH1_X
		const std::vector<GLfloat> inProjCameraWeight;

		// for inProjMode: JOSH3
		const GLint JOSH3_useCenterOnly;

	protected:
		const ProjectionMode outProjMode;
		const std::vector<Mat44> outProjTransform;

		// for outProjMode: PERSPECTIVE, MULTI_PERSPECTIVE, CUBEMAP, JOSH1, JOSH2, JOSH3, JOSH1_X
		const std::vector<Camera> outProjCamera;
		const std::vector<Mat44> outProjW2V;
		const std::vector<Mat44> outProjW2C;
		const std::vector<Mat44> outProjV2W;
		const std::vector<Mat44> outProjC2W;

	protected:
		const RigMode rigMode;
		const std::vector<Mat44> rigW2V;
		const std::vector<Mat44> rigV2W;

	public:
		const ProjectionMode& GetInProjMode() const { return inProjMode; }
		const std::vector<Mat44>& GetInProjTransform() const { return inProjTransform; }

		const std::vector<Camera>& GetInProjCamera() const { return inProjCamera; }
		const std::vector<Mat44>& GetInProjW2V() const { return inProjW2V; }
		const std::vector<Mat44>& GetInProjW2C() const { return inProjW2C; }
		const std::vector<Mat44>& GetInProjV2W() const { return inProjV2W; }
		const std::vector<Mat44>& GetInProjC2W() const { return inProjC2W; }
		const std::vector<GLfloat>& GetInProjCameraWeight() const { return inProjCameraWeight; }

		const ProjectionMode& GetOutProjMode() const { return outProjMode; }
		const std::vector<Mat44>& GetOutProjTransform() const { return outProjTransform; }

		const std::vector<Camera>& GetOutProjCamera() const { return outProjCamera; }
		const std::vector<Mat44>& GetOutProjW2V() const { return outProjW2V; }
		const std::vector<Mat44>& GetOutProjW2C() const { return outProjW2C; }
		const std::vector<Mat44>& GetOutProjV2W() const { return outProjV2W; }
		const std::vector<Mat44>& GetOutProjC2W() const { return outProjC2W; }

		const RigMode& GetRigMode() const { return rigMode; }
		const std::vector<Mat44>& GetRigW2V() const { return rigW2V; }
		const std::vector<Mat44>& GetRigV2W() const { return rigV2W; }
	};

	//
	class PanoConverterRender : public PanoRenderBase
	{
	protected:
		virtual void InitTexturesEvent();
		virtual void InitFragmentShaderHeadersEvent();
		virtual void InitFragmentShaderMainsEvent();
		virtual void InitFrameBuffersEvent();

	protected:
		virtual void PostDrawEvent() const;

	public:
		PanoConverterRender(
			GLint canvasWidth, GLint canvasHeight,
			RigMode rigMode, const std::vector<Mat44>& rigW2V,
			ProjectionMode inProjMode, const std::vector<Camera>& inProjCamera,
			ProjectionMode outProjMode, const std::vector<Camera>& outProjCamera,
			const CONST_PTR<Texture>& panoFieldTexture) :
			PanoRenderBase(
				canvasWidth, canvasHeight,
				rigMode, rigW2V,
				inProjMode, inProjCamera,
				outProjMode, outProjCamera,
				panoFieldTexture)
		{
			Setup();
		}

		PanoConverterRender(
			GLint canvasWidth, GLint canvasHeight,
			RigMode rigMode, const std::vector<Mat44>& rigW2V,
			ProjectionMode inProjMode, const std::vector<Camera>& inProjCamera,
			ProjectionMode outProjMode, const std::vector<Camera>& outProjCamera,
			const CONST_PTR<Texture>& panoFieldTexture, const CONST_PTR<Texture>& panoDepthTexture) :
			PanoRenderBase(
				canvasWidth, canvasHeight,
				rigMode, rigW2V,
				inProjMode, inProjCamera,
				outProjMode, outProjCamera,
				panoFieldTexture, panoDepthTexture)
		{
			Setup();
		}

		PanoConverterRender(
			GLint canvasWidth, GLint canvasHeight,
			RigMode rigMode, const std::vector<Mat44>& rigW2V,
			ProjectionMode inProjMode, const std::vector<Camera>& inProjCamera,
			ProjectionMode outProjMode, const std::vector<Camera>& outProjCamera,
			const CONST_PTR<Texture>& panoFieldTexture, const CONST_PTR<Texture>& panoDepthTexture, const CONST_PTR<Texture>& panoMaskTexture) :
			PanoRenderBase(
				canvasWidth, canvasHeight,
				rigMode, rigW2V,
				inProjMode, inProjCamera,
				outProjMode, outProjCamera,
				panoFieldTexture, panoDepthTexture, panoMaskTexture)
		{
			Setup();
		}

		void Setup();
	};
};