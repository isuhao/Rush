#pragma once

#include "C4Engine.h"
#include "C4Input.h"
#include "RushTestWorld.h"

using namespace C4;
namespace Rush
{
	enum
	{
		kActionCameraForward				= 'cfwd',
		kActionCameraBackward				= 'cbwd',
		kActionCameraLeft					= 'clft',
		kActionCameraRight					= 'crgt',
		kActionCameraRotateLeft				= 'crlt',
		kActionCameraRotateRight			= 'crrt',
		kActionCameraZoom					= 'zoom',
		kActionCameraZoomIn					= 'zmin',
		kActionCameraZoomOut				= 'zout',
		kActionCameraZoomWheel				= 'next'
	};

	class CameraNavigationAction : public Action
	{
		private:
			unsigned long cameraMovementFlag;

		public:
			CameraNavigationAction(unsigned_int32 type, unsigned_int32 flag);
			~CameraNavigationAction();

			void Begin(void);
			void End(void);
			void Update(float value);
	};
}