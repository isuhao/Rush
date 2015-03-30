#pragma once

#include "C4Interface.h"
#include "C4Engine.h"
#include "C4Widgets.h"

using namespace C4;

namespace Rush
{
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	The purpose of this MouseWrapper is to grab the mouse position and allow for the camera to track the mouse.

	Based off code by cjacket on the C4 Engine wiki forums
	http://www.terathon.com/forums/viewtopic.php?f=3&t=12436&p=112897&hilit=mouse+picking#p112897
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	class MouseInterface
	{
		private:
			BorderWidget		*mouseCursor;
			Point2D				mousePosition;
		public:
			MouseInterface(void);
			~MouseInterface();

			void ChangeCursorPosition(const float deltaX, const float deltaY);
			Point2D GetCursorPosition()
			{
				return (mousePosition);
			}
	};
}