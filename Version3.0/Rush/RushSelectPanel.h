#pragma once

#include "C4Input.h"
#include "C4Interface.h"
#include "C4Widgets.h"
#include "RushPieceBase.h"


using namespace C4;
namespace Rush
{
	const float Z_HEIGHT = 2.0F;
	class GridWindow : public Window, public Singleton<GridWindow>
	{
	private:
		WidgetObserver<GridWindow>		gridButtonObserver;
		WidgetObserver<GridWindow>		goButtonObserver;
		WidgetObserver<GridWindow>		actionButtonObserver;
		WidgetObserver<GridWindow>		pieceRadObserver;
		

		void HandleGridButtonEvent(Widget *widget, const WidgetEventData *eventData);
		void HandleGoButtonEvent(Widget *widget, const WidgetEventData *eventData);
		void HandlePieceRadioEvent(Widget *widget, const WidgetEventData *eventData);
		void HandleActionButtonEvent(Widget *widget, const WidgetEventData *eventData);
		void MovePiecesOnGrid(Point3D waypoint);
		bool IsPositionClear(Point3D waypoint);
		void AddPieceToGrid(ModelTypes type, Point3D waypoint);
		ModelTypes GetRadioButtonState();
	public:
		GridWindow();
		~GridWindow();

		void Preprocess(void) override;
	};

	extern GridWindow *TheGridWindow;
}