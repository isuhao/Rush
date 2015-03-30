#include "RushCameras.h"
#include "RushGame.h"
#include "MouseInterface.h"

using namespace C4;
using namespace Rush;

RushCamera::RushCamera() : 
	FrustumCamera(2.0F, 1.0F),
	movementFlags(0),
	curDirAngle(0.25F*K::pi),
	curDistance(10.0F),
	curTiltAngle(0.25F*K::pi),
	minDistance(1.0f),
	maxDistance(20.0f),
	curFocus(0.0F,0.0F,0.0F)
{
}

RushCamera::~RushCamera()
{
}

void RushCamera::GetWorldRayFromPoint(const Point2D &p, Ray *ray)
{
	const Rect &viewRect = this->GetObject()->GetViewRect();

	float x = p.x / (float) viewRect.Width();
	float y = p.y / (float) viewRect.Height();

	this->CastRay(x, y, ray);

	const Transform4D &cameraTransform = this->GetNodeTransform();
	ray->origin = cameraTransform * ray->origin;
	ray->direction = (cameraTransform * ray->direction).Normalize();

	ray->radius = 0.0F;
	ray->tmin = 0.0F;
	ray->tmax = 500.0F;
}

void RushCamera::Preprocess(void)
{
	FrustumCamera::Preprocess();
}

void RushCamera::Move(void)
{
	/*--------------------------------- VARIABLE DECLARATION ----------------------------------*/
	//Camera
	float dt = TheTimeMgr->GetFloatDeltaTime() * 0.0001F;

	float deltaFwd = 0.0F;
	float deltaRight = 0.0F;
	float deltaRot = 0.0F;

	//Mouse
	float sensitivity = 300.0f;

	float deltaX = -sensitivity * TheInputMgr->GetMouseDeltaX();
	float deltaY = -sensitivity * TheInputMgr->GetMouseDeltaY();

	Point2D cursorPos = Point2D(0.0f, 0.0f);

	if (TheGame)
	{
		MouseInterface	&mouseInterface = TheGame->GetMouseInterface();
		mouseInterface.ChangeCursorPosition(deltaX, deltaY);
		cursorPos = mouseInterface.GetCursorPosition();

		/*---------------------------------- AUTOSCROLLING ----------------------------------*/
		/*NOTE: As of right now (01:29 Friday March 27th 2015) this section of code does
				nothing that I can tell. The program will work the same without it. Hopefully
				it continues to do so in the future.								-Sasha	 */
		float autoScrollThreshold = 0.1f;

		float displayWidth = TheDisplayMgr->GetDisplayWidth();
		float displayHeight = TheDisplayMgr->GetDisplayHeight();

		if (cursorPos.x < autoScrollThreshold * displayWidth)
			deltaRight -= 1.0f * dt;

		if (cursorPos.x >= (1.0f - autoScrollThreshold) * displayWidth)
			deltaRight += 1.0f * dt;

		if (cursorPos.y < autoScrollThreshold * displayHeight)
			deltaFwd += 1.0f * dt;

		if (cursorPos.y >= (1.0f - autoScrollThreshold) * displayHeight)
			deltaFwd -= 1.0f * dt;
	}

	/*------------------------------------ CAMERA MOVEMENT ------------------------------------*/
	/*NOTE: The camera movement is working as of 01:28 Friday March 27th 2015. Mouse is still
			not completely functional. I am now going to try and implement scrolling zoom on
			the mouse.																-Sasha	   */
	/*NOTE: 12:52 Friday March 27th 2015. Camera is now completely controlled by keyboard and mouse.
			The camera can be zoomed in, out, and moved in all four directions.		-Sasha	   */

	//Position
	if ((movementFlags & kNavMoveLeft) != 0)
	{
		deltaRight -= 1.0f * dt;
	}
	if ((movementFlags & kNavMoveRight) != 0)
	{
		deltaRight += 1.0f * dt;
	}
	if ((movementFlags & kNavMoveForward) != 0)
	{
		deltaFwd += 1.0f * dt;
	}
	if ((movementFlags & kNavMoveBackward) != 0)
	{
		deltaFwd -= 1.0f * dt;
	}

	//Rotation
	if ((movementFlags & kNavMoveRotLeft) != 0)
	{
		deltaRot -= 1.0f * dt;
	}
	if ((movementFlags & kNavMoveRotRight) != 0)
	{
		deltaRot += 1.0f * dt;
	}

	//Update rotation
	curDirAngle += deltaRot;

	//Update Focus Point
	Vector3D dirVector = Vector3D(deltaRight, deltaFwd, 0.0F);

	Matrix3D dirMatrix;
	dirMatrix.SetIdentity();
	dirMatrix.SetRotationAboutZ(curDirAngle);
	dirVector = dirVector * dirMatrix;

	curFocus += dirVector;

	//Check for zoom
	if ((movementFlags & kNavMoveZoom) != 0)
	{
		curDistance -= 1.0F * TheInputMgr->GetMouseDeltaY();
		deltaRot -= 0.5F * TheInputMgr->GetMouseDeltaX();
	}
	
	if ((movementFlags & kNavMoveZoomIn) != 0)
	{
		curDistance -= 1.0F*dt;
	}

	if ((movementFlags & kNavMoveZoomOut) != 0)
	{
		curDistance += 1.0F*dt;
	}

	//Fix zoom boundaries
	if (curDistance < minDistance)
	{
		curDistance = minDistance;
	}

	if (curDistance > maxDistance)
	{
		curDistance = maxDistance;
	}

	//Update Camera Position
	Point3D camPosition;

	camPosition.Set(0.0F, -curDistance, 0.0F);

	Matrix3D tiltMatrix;
	tiltMatrix.SetIdentity();
	tiltMatrix.SetRotationAboutX(curTiltAngle);
	camPosition = camPosition*tiltMatrix;

	Transform4D tiltTransform;
	tiltTransform.SetIdentity();
	tiltTransform.SetMatrix3D(tiltMatrix);
	//camPosition = camPosition * tiltTransform;

	Matrix3D orbitMatrix;
	orbitMatrix.SetIdentity();
	orbitMatrix.SetRotationAboutZ(curDirAngle);

	Transform4D orbitTransform;
	orbitTransform.SetIdentity();
	orbitTransform.SetMatrix3D(orbitMatrix);
	
	//camPosition = camPosition * orbitTransform;
	camPosition = camPosition * orbitMatrix;
	camPosition += curFocus;

	this->SetNodePosition(camPosition);
	this->LookAtPoint(curFocus);

}