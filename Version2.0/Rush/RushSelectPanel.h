#pragma once

#include "C4Input.h"
#include "C4Interface.h"
#include "C4Widgets.h"

using namespace C4;
namespace Rush
{
	class GridWindow : public Window, public Singleton<GridWindow>
	{
	private:
		WidgetObserver<GridWindow>		gridButtonObserver;
		//WidgetObserver<GridWindow>		goButtonObserver;
		

		void HandleGridButtonEvent(Widget *widget, const WidgetEventData *eventData);
		void HandleGoButtonEvent(Widget *widget, const WidgetEventData *eventData);

	public:
		GridWindow();
		~GridWindow();

		void Preprocess(void) override;
	};

	extern GridWindow *TheGridWindow;
}