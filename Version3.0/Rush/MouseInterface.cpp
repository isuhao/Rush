#include "MouseInterface.h"

using namespace C4;
using namespace Rush;

MouseInterface::MouseInterface()
{
	float halfDisplayWidth = 0.5F * TheDisplayMgr->GetDisplayWidth();
	float halfDisplayHeight = 0.5F * TheDisplayMgr->GetDisplayHeight();

	mousePosition = Point2D(halfDisplayWidth, halfDisplayHeight);

	mouseCursor = new BorderWidget(Vector2D(10.0F, 10.0F), kLineSolid, K::white);
	mouseCursor->SetWidgetPosition(Point3D(mousePosition.x, mousePosition.y, 0.0f));
	TheInterfaceMgr->AddWidget(mouseCursor);
}

MouseInterface::~MouseInterface()
{
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
The ChangeCursorPosition function is used in conjunction with the Camera::Move function to allow
for the camera to keep the mouse in focus at all times. Useful for MOBA style games with large
worlds and far traveling movement.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void MouseInterface::ChangeCursorPosition(const float deltaX, const float deltaY)
{
	mousePosition.x += deltaX;
	mousePosition.y += deltaY;

	float displayWidth = TheDisplayMgr->GetDisplayWidth();
	float displayHeight = TheDisplayMgr->GetDisplayHeight();

	if (mousePosition.x < 0.0F)
	{
		mousePosition.x = 0.0F;
	}

	if (mousePosition.y < 0.0F)
	{
		mousePosition.y = 0.0F;
	}
	
	if (mousePosition.x >= displayWidth)
	{
		mousePosition.x = displayWidth - 1;
	}

	if (mousePosition.y >= displayHeight)
	{
		mousePosition.y = displayHeight - 1;
	}

	if (mouseCursor)
	{
		Vector2D &cursorSize = mouseCursor->GetWidgetSize();
		float posX = mousePosition.x - 0.5*deltaX;
		float posY = mousePosition.y - 0.5*deltaY;

		mouseCursor->SetWidgetPosition(Point3D(posX, posY, 0.0F));
		mouseCursor->Invalidate();
	}
}