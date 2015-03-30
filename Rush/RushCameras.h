#pragma once

#include "C4Cameras.h"
#include "C4CameraObjects.h"

using namespace C4;

namespace Rush
{
	enum
	{
		kNavMoveForward				= 1 << 0,
		kNavMoveBackward			= 1 << 1,
		kNavMoveLeft				= 1 << 2,
		kNavMoveRight				= 1 << 3,
		kNavMoveRotLeft				= 1 << 4,
		kNavMoveRotRight			= 1 << 5,
		kNavMoveZoomIn				= 1 << 6,
		kNavMoveZoomOut				= 1 << 7,
		kNavMoveZoom				= 1 << 8,
		kNavMoveZoomWheel			= 1 << 9,
		kNavMoveMask				= kNavMoveForward | 
									  kNavMoveBackward |
									  kNavMoveLeft |
									  kNavMoveRight |
									  kNavMoveRotLeft |
									  kNavMoveRotRight|
									  kNavMoveZoomIn|
									  kNavMoveZoomOut |
									  kNavMoveZoom|
									  kNavMoveZoomWheel
	};
	
	class RushCamera : public FrustumCamera
	{
		private:
			long			movementFlags;
			float			curDirAngle;
			float			curDistance;
			float			curTiltAngle;
			float			minDistance;
			float			maxDistance;
			Point3D			curFocus;
			
		public:
			RushCamera();
			~RushCamera();

/*------------------------------------- MODIFIER FUNCTIONS ---------------------------------------*/
			/*-------------------------------- GET FUNCTIONS -------------------------------------*/
			unsigned long GetNavFlags()
			{
				return (movementFlags);
			}
			float GetCurrentDistance()
			{
				return (curDistance);
			}
			float GetCurrentDirectionAngle()
			{
				return (curDirAngle);
			}
			float GetCurrentTiltAngle()
			{
				return (curTiltAngle);
			}
			Point3D GetCurrentFocus()
			{
				return (curFocus);
			}
			/*-------------------------------- SET FUNCTIONS -------------------------------------*/
			void SetNavFlags(unsigned long flags)
			{
				movementFlags = flags;
			}
			void SetCurrentDistance(float newDistance)
			{
				curDistance = newDistance;
			}
			void SetCurrentDirectionAngle(float newDirectionAngle)
			{
				curDirAngle = newDirectionAngle;
			}
			void SetCurrentTiltAngle(float newTiltAngle)
			{
				curTiltAngle = newTiltAngle;
			}
			void SetCurrentFocus(Point3D newFocus)
			{
				curFocus = newFocus;
			}

/*------------------------------- FUNCTIONS FOR UNIT SELECTION -----------------------------------*/
			void GetWorldRayFromPoint(const Point2D &p, Ray *ray);

			void Preprocess(void);
			void Move(void);
	};
}