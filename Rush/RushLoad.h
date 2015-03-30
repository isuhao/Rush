#pragma once

#include "C4Input.h"
#include "C4Interface.h"
#include "C4Widgets.h"

using namespace C4;
namespace Rush
{
	class JoinWindow : public Window, public Singleton<JoinWindow>
	{
	private:
		WidgetObserver<JoinWindow>		backButtonObserver;
		WidgetObserver<JoinWindow>		joinButtonObserver;

		void HandleBackButtonEvent(Widget *widget, const WidgetEventData *eventData);
		void HandleJoinButtonEvent(Widget *widget, const WidgetEventData *eventData);

	public:
		JoinWindow();
		~JoinWindow();

		void Preprocess(void) override;
	};


	class StartWindow : public Window, public Singleton<StartWindow>
	{
	private:
		WidgetObserver<StartWindow>		hostButtonObserver;
		WidgetObserver<StartWindow>		joinButtonObserver;

		void HandleHostButtonEvent(Widget *widget, const WidgetEventData *eventData);
		void HandleJoinButtonEvent(Widget *widget, const WidgetEventData *eventData);

	public:
		StartWindow();
		~StartWindow();

		void Preprocess(void) override;
	};

	extern StartWindow *TheStartWindow;
	extern JoinWindow *TheJoinWindow;
}