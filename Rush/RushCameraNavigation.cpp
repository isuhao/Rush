#include "RushCameraNavigation.h"
#include "C4Engine.h"
#include "RushGame.h"


using namespace C4;

namespace Rush
{
	CameraNavigationAction::CameraNavigationAction(unsigned_int32 type, unsigned_int32 flag) : Action(type)
	{
		cameraMovementFlag = flag;
	}

	CameraNavigationAction::~CameraNavigationAction()
	{
	}

	void CameraNavigationAction::Begin(void)
	{
		TestWorld *world = static_cast<TestWorld *>(TheWorldMgr->GetWorld());
		RushCamera *camera = world->GetNavCamera();
		camera->SetNavFlags(camera->GetNavFlags() | cameraMovementFlag);
	}

	void CameraNavigationAction::End(void)
	{
		TestWorld *world = static_cast<TestWorld *>(TheWorldMgr->GetWorld());
		RushCamera *camera = world->GetNavCamera();
		camera->SetNavFlags(camera->GetNavFlags() & ~cameraMovementFlag);
	}

	void CameraNavigationAction::Update(float value)
	{
		ActionType type = GetActionType();
		if (type != kActionCameraZoomWheel)
		{
			return;
		}

		TestWorld	*world = static_cast<TestWorld *>(TheWorldMgr->GetWorld());
		RushCamera	*camera = world->GetNavCamera();
		camera->SetCurrentDistance(camera->GetCurrentDistance() + (0.01f* -value));
	}
}