#include "RushLoad.h"
#include "C4World.h"
#include "RushSelectPanel.h"

using namespace C4;
using namespace Rush;


JoinWindow::JoinWindow() :
/*--------------------------- JOINING PANEL PATH, NEED TO MAKE IN C4 ENGINE ------------------------------*/
Window("panels/RushJoin"),
Singleton<JoinWindow>(TheJoinWindow),
backButtonObserver(this, &JoinWindow::HandleBackButtonEvent),
joinButtonObserver(this, &JoinWindow::HandleJoinButtonEvent)
{
}

JoinWindow::~JoinWindow()
{
}

void JoinWindow::Preprocess(void)
{
	Window::Preprocess();

	//Look for widgets in the panel and give them observers
	Widget *backButton = FindWidget("Back");
	backButton->SetObserver(&backButtonObserver);

	Widget *joinButton = FindWidget("Join");
	joinButton->SetObserver(&joinButtonObserver);
}

//Back button clicked from join window, go back to start window
void JoinWindow::HandleBackButtonEvent(Widget *widget, const WidgetEventData *eventData)
{
	if (eventData->eventType == kEventWidgetActivate)
	{
		delete this;

		TheInterfaceMgr->AddWidget(new StartWindow);
	}
}

//Join button clicked from join window, load world with IP
void JoinWindow::HandleJoinButtonEvent(Widget *widget, const WidgetEventData *eventData)
{
	if (eventData->eventType == kEventWidgetActivate)
	{
		EditTextWidget *IPEntry = static_cast<EditTextWidget*> (this->FindWidget("IP"));
		const char *IP = IPEntry->GetText();

		Engine::Report(IP); //we can get the IP this way

		delete this;

		/*-------------------- CODE TO JOIN A GAME SHOULD GO HERE --------------------------*/
		TheWorldMgr->LoadWorld("world/rushTest");
	}
}


StartWindow::StartWindow() :
/*--------------------------- START PANEL PATH, NEED TO MAKE IN C4 ENGINE ------------------------------*/
Window("panels/RushStart"),
Singleton<StartWindow>(TheStartWindow),
hostButtonObserver(this, &StartWindow::HandleHostButtonEvent),
joinButtonObserver(this, &StartWindow::HandleJoinButtonEvent)
{
}

StartWindow::~StartWindow()
{
}

void StartWindow::Preprocess(void)
{
	Window::Preprocess();

	//Look for widgets in the panel and give them observers
	Widget *hostButton = FindWidget("Host");
	hostButton->SetObserver(&hostButtonObserver);

	Widget *joinButton = FindWidget("Join");
	joinButton->SetObserver(&joinButtonObserver);
}

//Host button was clicked in the start window
void StartWindow::HandleHostButtonEvent(Widget *widget, const WidgetEventData *eventData)
{
	if (eventData->eventType == kEventWidgetActivate)
	{
		delete this;
		/*-------------------- CODE TO HOST A GAME SHOULD GO HERE --------------------------*/
		TheWorldMgr->LoadWorld("world/rushTest");
		TheInterfaceMgr->AddWidget(new GridWindow);

	}
}

//Join button was clicked from the start window, go to the join window interface
void StartWindow::HandleJoinButtonEvent(Widget *widget, const WidgetEventData *eventData)
{
	if (eventData->eventType == kEventWidgetActivate)
	{
		delete this;

		TheInterfaceMgr->AddWidget(new JoinWindow);
	}
}