#ifndef __KX_RENDER_DATA_H__
#define __KX_RENDER_DATA_H__

#include "RAS_Rasterizer.h"

class KX_Scene;
class KX_Camera;

/** \brief This file contains all the data describing the rendering proceeded in a frame.
 * KX_RenderData is the main data which for each eye (in case of stereo) contains a frame
 * and each of these frame contains the scenes data and cameras data.
 */

struct KX_CameraRenderData
{
	KX_CameraRenderData(KX_Camera *rendercam, KX_Camera *cullingcam, const RAS_Rect& area, const RAS_Rect& viewport,
						RAS_Rasterizer::StereoMode stereoMode, RAS_Rasterizer::StereoEye eye, unsigned short index);
	KX_CameraRenderData(const KX_CameraRenderData& other);
	~KX_CameraRenderData();
	
	/// Rendered camera, could be a temporary camera in case of stereo.
	KX_Camera *m_renderCamera;
	KX_Camera *m_cullingCamera;
	RAS_Rect m_area;
	RAS_Rect m_viewport;
	RAS_Rasterizer::StereoMode m_stereoMode;
	RAS_Rasterizer::StereoEye m_eye;
	// Index of the camera in all the scene's cameras rendered.
	unsigned short m_index;
};

struct KX_SceneRenderData
{
	KX_SceneRenderData(KX_Scene *scene);
	
	KX_Scene *m_scene;
	// Use multiple list of cameras in case of per eye stereo.
	std::vector<KX_CameraRenderData> m_cameraDataList[RAS_Rasterizer::RAS_STEREO_MAXEYE];
};

/// Data used to render a frame.
struct KX_FrameRenderData
{
	KX_FrameRenderData(RAS_Rasterizer::OffScreenType ofsType, const std::vector<RAS_Rasterizer::StereoEye>& eyes);
	
	RAS_Rasterizer::OffScreenType m_ofsType;
	std::vector<RAS_Rasterizer::StereoEye> m_eyes;
};

struct KX_RenderData
{
	KX_RenderData(RAS_Rasterizer::StereoMode stereoMode, bool renderPerEye);
	
	RAS_Rasterizer::StereoMode m_stereoMode;
	bool m_renderPerEye;
	std::vector<KX_SceneRenderData> m_sceneDataList;
	std::vector<KX_FrameRenderData> m_frameDataList;
};

// Storing information for off screen rendering of shadow and texture map.
	struct TextureRenderData
	{
		enum {
			RENDER_WORLD,
			UPDATE_LOD
		} m_mode;

		mt::mat4 m_viewMatrix;
		mt::mat4 m_progMatrix;
		mt::mat3x4 m_camTrans;
		mt::vec3 m_position;

		SG_Frustum m_frustum;

		float m_lodFactor;

		std::function<void (unsigned short)> m_bind;
		std::function<void (unsigned short)> m_unbind;
	};

	struct CameraRenderData
	{
		CameraRenderData(KX_Camera *rendercam, KX_Camera *cullingcam, const RAS_Rect& area, const RAS_Rect& viewport,
				RAS_Rasterizer::StereoMode stereoMode, RAS_Rasterizer::StereoEye eye);
		CameraRenderData(const CameraRenderData& other);
		~CameraRenderData();

		/// Rendered camera, could be a temporary camera in case of stereo.
		KX_Camera *m_renderCamera;
		KX_Camera *m_cullingCamera;
		RAS_Rect m_area;
		RAS_Rect m_viewport;
		RAS_Rasterizer::StereoMode m_stereoMode;
		RAS_Rasterizer::StereoEye m_eye;
	};

	struct SceneRenderData
	{
		SceneRenderData(KX_Scene *scene);

		KX_Scene *m_scene;
		std::vector<CameraRenderData> m_cameraDataList;
	};

	/// Data used to render a frame.
	struct FrameRenderData
	{
		FrameRenderData(RAS_Rasterizer::OffScreenType ofsType);

		RAS_Rasterizer::OffScreenType m_ofsType;
		std::vector<SceneRenderData> m_sceneDataList;
	};

	struct RenderData
	{
		RenderData(RAS_Rasterizer::StereoMode stereoMode, bool renderPerEye);

		RAS_Rasterizer::StereoMode m_stereoMode;
		bool m_renderPerEye;
		std::vector<FrameRenderData> m_frameDataList;
	};

#endif  // __KX_RENDER_DATA_H__
