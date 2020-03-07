#pragma once

// O3GL
#include "O3GL/CanvasRender.hpp"

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
		JOSH3
	};

	enum class RigMode
	{
		MONO,
		MULTI,
	};

	//
	class PanoRenderBase : public CanvasRender
	{
	public:
		virtual std::string Name() const { return "PanoRenderBase"; }

	protected:
		const bool enableField;
		const bool enableDepth;
		const bool enableMask;

		const Sampler panoFieldSampler;
		const Sampler panoDepthSampler;
		const Sampler panoMaskSampler;

		const Texture panoFieldTexture;
		const Texture panoDepthTexture;
		const Texture panoMaskTexture;

		const std::size_t layers;

	protected:
		const ProjectionMode inProjMode;
		const Mat44 inProjTransform;

		// for inProjMode: MULTI_PERSPECTIVE, CUBEMAP, JOSH1, JOSH2
		const std::vector<Camera> inProjCamera;
		const std::vector<Mat44> inProjW2V;
		const std::vector<Mat44> inProjW2C;
		const std::vector<Mat44> inProjV2W;
		const std::vector<Mat44> inProjC2W;

	protected:
		const ProjectionMode outProjMode;
		const Mat44 outProjTransform;

		// for outProjMode: PERSPECTIVE, MULTI_PERSPECTIVE, CUBEMAP, JOSH1, JOSH2
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
		virtual void InitSetupEvent();
		virtual void InitGeometryShaderHeadersEvent();
		virtual void InitGeometryShaderMainsEvent();
		virtual void InitFragmentShaderHeadersEvent();
		virtual void InitProgramParametersEvent() const;

		virtual void PreDrawEvent() const;
		virtual void PostDrawEvent() const;

		virtual void UpdateEvent();

	public:
		virtual void DrawInfo(float& wx, float& wy, float lineHeight = 0.06f) const;

	public:
		static void InitCamera_CUBEMAP(const std::vector<Camera>& cameras);
		static void InitCamera_JOSH1(const std::vector<Camera>& cameras);
		static void InitCamera_JOSH2(const std::vector<Camera>& cameras);
		static void InitCamera_JOSH3(const std::vector<Camera>& cameras);

	protected:
		void PanoRender_InitSetupEvent__rigMode_MONO__inProjMode_PERSPECTIVE();
		void PanoRender_InitSetupEvent__rigMode_MONO__inProjMode_EQUIRECTANGULAR();
		void PanoRender_InitSetupEvent__rigMode_MONO__inProjMode_MERCATOR();
		void PanoRender_InitSetupEvent__rigMode_MONO__inProjMode_MULTI_PERSPECTIVE();
		void PanoRender_InitSetupEvent__rigMode_MONO__inProjMode_CUBEMAP();
		void PanoRender_InitSetupEvent__rigMode_MONO__inProjMode_JOSH1();
		void PanoRender_InitSetupEvent__rigMode_MONO__inProjMode_JOSH2();
		void PanoRender_InitSetupEvent__rigMode_MONO__inProjMode_JOSH3();

		void PanoRender_InitSetupEvent__rigMode_MULTI__inProjMode_PERSPECTIVE();
		void PanoRender_InitSetupEvent__rigMode_MULTI__inProjMode_EQUIRECTANGULAR();
		void PanoRender_InitSetupEvent__rigMode_MULTI__inProjMode_MERCATOR();
		void PanoRender_InitSetupEvent__rigMode_MULTI__inProjMode_MULTI_PERSPECTIVE();
		void PanoRender_InitSetupEvent__rigMode_MULTI__inProjMode_CUBEMAP();
		void PanoRender_InitSetupEvent__rigMode_MULTI__inProjMode_JOSH1();
		void PanoRender_InitSetupEvent__rigMode_MULTI__inProjMode_JOSH2();
		void PanoRender_InitSetupEvent__rigMode_MULTI__inProjMode_JOSH3();

		//
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_PERSPECTIVE();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_EQUIRECTANGULAR();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_MERCATOR();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_MULTI_PERSPECTIVE();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_CUBEMAP();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_JOSH1();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_JOSH2();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__inProjMode_JOSH3();

		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_PERSPECTIVE();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_EQUIRECTANGULAR();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_MERCATOR();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_MULTI_PERSPECTIVE();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_CUBEMAP();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_JOSH1();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_JOSH2();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__inProjMode_JOSH3();

		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_PERSPECTIVE();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_EQUIRECTANGULAR();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_MERCATOR();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_MULTI_PERSPECTIVE();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_CUBEMAP();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_JOSH1();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_JOSH2();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MONO__outProjMode_JOSH3();

		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_PERSPECTIVE();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_EQUIRECTANGULAR();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_MERCATOR();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_MULTI_PERSPECTIVE();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_CUBEMAP();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_JOSH1();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_JOSH2();
		void PanoRender_InitFragmentShaderHeadersEvent__rigMode_MULTI__outProjMode_JOSH3();

	public:
		PanoRenderBase(
			GLint canvasWidth, GLint canvasHeight,
			RigMode rigMode, const std::vector<Mat44>& rigW2V,
			ProjectionMode inProjMode, const std::vector<Camera>& inProjCamera,
			ProjectionMode outProjMode, const std::vector<Camera>& outProjCamera,
			const Texture& panoFieldTexture) :
			CanvasRender(canvasWidth, canvasHeight),
			rigMode(rigMode), rigW2V(rigW2V), rigV2W(),
			inProjMode(inProjMode), inProjTransform(glm::identity<Mat44>()), inProjCamera(inProjCamera),
			outProjMode(outProjMode), outProjTransform(glm::identity<Mat44>()), outProjCamera(outProjCamera),
			panoFieldSampler(), panoFieldTexture(panoFieldTexture),
			enableField(true), enableDepth(false), enableMask(false),
			inProjW2V(inProjCamera.size()), inProjW2C(inProjCamera.size()), inProjC2W(inProjCamera.size()), inProjV2W(inProjCamera.size()),
			outProjW2V(outProjCamera.size()), outProjW2C(outProjCamera.size()), outProjV2W(outProjCamera.size()), outProjC2W(outProjCamera.size()),
			layers(1)
		{}

		PanoRenderBase(
			GLint canvasWidth, GLint canvasHeight,
			RigMode rigMode, const std::vector<Mat44>& rigW2V,
			ProjectionMode inProjMode, const std::vector<Camera>& inProjCamera,
			ProjectionMode outProjMode, const std::vector<Camera>& outProjCamera,
			const Texture& panoFieldTexture, const Texture& panoDepthTexture) :
			CanvasRender(canvasWidth, canvasHeight),
			rigMode(rigMode), rigW2V(rigW2V), rigV2W(),
			inProjMode(inProjMode), inProjTransform(glm::identity<Mat44>()), inProjCamera(inProjCamera),
			outProjMode(outProjMode), outProjTransform(glm::identity<Mat44>()), outProjCamera(outProjCamera),
			panoFieldSampler(), panoDepthSampler(), panoFieldTexture(panoFieldTexture), panoDepthTexture(panoDepthTexture),
			enableField(true), enableDepth(true), enableMask(false),
			inProjW2V(inProjCamera.size()), inProjW2C(inProjCamera.size()), inProjC2W(inProjCamera.size()), inProjV2W(inProjCamera.size()),
			outProjW2V(outProjCamera.size()), outProjW2C(outProjCamera.size()), outProjV2W(outProjCamera.size()), outProjC2W(outProjCamera.size()),
			layers(1)
		{}

		PanoRenderBase(
			GLint canvasWidth, GLint canvasHeight,
			RigMode rigMode, const std::vector<Mat44>& rigW2V,
			ProjectionMode inProjMode, const std::vector<Camera>& inProjCamera,
			ProjectionMode outProjMode, const std::vector<Camera>& outProjCamera,
			const Texture& panoFieldTexture, const Texture& panoDepthTexture, const Texture& panoMaskTexture) :
			CanvasRender(canvasWidth, canvasHeight),
			rigMode(rigMode), rigW2V(rigW2V), rigV2W(),
			inProjMode(inProjMode), inProjTransform(glm::identity<Mat44>()), inProjCamera(inProjCamera),
			outProjMode(outProjMode), outProjTransform(glm::identity<Mat44>()), outProjCamera(outProjCamera),
			panoFieldSampler(), panoDepthSampler(), panoMaskSampler(), panoFieldTexture(panoFieldTexture), panoDepthTexture(panoDepthTexture), panoMaskTexture(panoMaskTexture),
			enableField(true), enableDepth(true), enableMask(true),
			inProjW2V(inProjCamera.size()), inProjW2C(inProjCamera.size()), inProjC2W(inProjCamera.size()), inProjV2W(inProjCamera.size()),
			outProjW2V(outProjCamera.size()), outProjW2C(outProjCamera.size()), outProjV2W(outProjCamera.size()), outProjC2W(outProjCamera.size()),
			layers(1)
		{}

		void SetInProjTransform(Mat44 inProjTransform) const
		{
			*((Mat44*)&this->inProjTransform) = inProjTransform;
		}

		void SetOutProjTransform(Mat44 outProjTransform) const
		{
			*((Mat44*)&this->outProjTransform) = outProjTransform;
		}

	public:
		void CreateTexture(const std::string& name);
		void AllocateTexture(const std::string& name, GLint f, GLint w, GLint h);
	};

	//
	class PanoConverterRender : public PanoRenderBase
	{
	public:
		virtual std::string Name() const { return "PanoConverterRender"; }

	public:
		virtual void InitSetupEvent();
		virtual void InitTexturesEvent();
		virtual void InitFragmentShaderHeadersEvent();
		virtual void InitFragmentShaderMainsEvent();
		virtual void InitFrameBuffersEvent();

		virtual void PostDrawEvent() const;

	public:
		PanoConverterRender(
			GLint canvasWidth, GLint canvasHeight,
			RigMode rigMode, const std::vector<Mat44>& rigW2V,
			ProjectionMode inProjMode, const std::vector<Camera>& inProjCamera,
			ProjectionMode outProjMode, const std::vector<Camera>& outProjCamera,
			const Texture& panoFieldTexture) :
			PanoRenderBase(
				canvasWidth, canvasHeight,
				rigMode, rigW2V,
				inProjMode, inProjCamera,
				outProjMode, outProjCamera,
				panoFieldTexture)
		{}

		PanoConverterRender(
			GLint canvasWidth, GLint canvasHeight,
			RigMode rigMode, const std::vector<Mat44>& rigW2V,
			ProjectionMode inProjMode, const std::vector<Camera>& inProjCamera,
			ProjectionMode outProjMode, const std::vector<Camera>& outProjCamera,
			const Texture& panoFieldTexture, const Texture& panoDepthTexture) :
			PanoRenderBase(
				canvasWidth, canvasHeight,
				rigMode, rigW2V,
				inProjMode, inProjCamera,
				outProjMode, outProjCamera,
				panoFieldTexture, panoDepthTexture)
		{}

		PanoConverterRender(
			GLint canvasWidth, GLint canvasHeight,
			RigMode rigMode, const std::vector<Mat44>& rigW2V,
			ProjectionMode inProjMode, const std::vector<Camera>& inProjCamera,
			ProjectionMode outProjMode, const std::vector<Camera>& outProjCamera,
			const Texture& panoFieldTexture, const Texture& panoDepthTexture, const Texture& panoMaskTexture) :
			PanoRenderBase(
				canvasWidth, canvasHeight,
				rigMode, rigW2V,
				inProjMode, inProjCamera,
				outProjMode, outProjCamera,
				panoFieldTexture, panoDepthTexture, panoMaskTexture)
		{}
	};
};