#include "RushSelectPanel.h"
#include "RushPieceBase.h"
#include "RushTestWorld.h"
#include "C4String.h"

using namespace C4;
using namespace Rush;

GridWindow *Rush::TheGridWindow = nullptr;

GridWindow::GridWindow() :
/*--------------------------- JOINING PANEL PATH, NEED TO MAKE IN C4 ENGINE ------------------------------*/
Window("panels/SelectGridPanel"),
Singleton<GridWindow>(TheGridWindow),
gridButtonObserver(this, &GridWindow::HandleGridButtonEvent)
{
}

GridWindow::~GridWindow()
{
}

void GridWindow::Preprocess(void)
{
	Window::Preprocess();

	//Map every button
	Widget *A1Button = FindWidget("0000");
	Widget *A2Button = FindWidget("0001");
	Widget *A3Button = FindWidget("0002");
	Widget *A4Button = FindWidget("0003");
	Widget *A5Button = FindWidget("0004");
	Widget *A6Button = FindWidget("0005");
	Widget *A7Button = FindWidget("0006");
	Widget *A8Button = FindWidget("0007");
	Widget *A9Button = FindWidget("0008");
	Widget *A10Button = FindWidget("0009");
	Widget *A11Button = FindWidget("0010");
	Widget *B1Button = FindWidget("0100");
	Widget *B2Button = FindWidget("0101");
	Widget *B3Button = FindWidget("0102");
	Widget *B4Button = FindWidget("0103");
	Widget *B5Button = FindWidget("0104");
	Widget *B6Button = FindWidget("0105");
	Widget *B7Button = FindWidget("0106");
	Widget *B8Button = FindWidget("0107");
	Widget *B9Button = FindWidget("0108");
	Widget *B10Button = FindWidget("0109");
	Widget *B11Button = FindWidget("0110");
	Widget *C1Button = FindWidget("0200");
	Widget *C2Button = FindWidget("0201");
	Widget *C3Button = FindWidget("0202");
	Widget *C4Button = FindWidget("0203");
	Widget *C5Button = FindWidget("0204");
	Widget *C6Button = FindWidget("0205");
	Widget *C7Button = FindWidget("0206");
	Widget *C8Button = FindWidget("0207");
	Widget *C9Button = FindWidget("0208");
	Widget *C10Button = FindWidget("0209");
	Widget *C11Button = FindWidget("0210");
	Widget *D1Button = FindWidget("0300");
	Widget *D2Button = FindWidget("0301");
	Widget *D3Button = FindWidget("0302");
	Widget *D4Button = FindWidget("0303");
	Widget *D5Button = FindWidget("0304");
	Widget *D6Button = FindWidget("0305");
	Widget *D7Button = FindWidget("0306");
	Widget *D8Button = FindWidget("0307");
	Widget *D9Button = FindWidget("0308");
	Widget *D10Button = FindWidget("0309");
	Widget *D11Button = FindWidget("0310");
	Widget *E1Button = FindWidget("0400");
	Widget *E2Button = FindWidget("0401");
	Widget *E3Button = FindWidget("0402");
	Widget *E4Button = FindWidget("0403");
	Widget *E5Button = FindWidget("0404");
	Widget *E6Button = FindWidget("0405");
	Widget *E7Button = FindWidget("0406");
	Widget *E8Button = FindWidget("0407");
	Widget *E9Button = FindWidget("0408");
	Widget *E10Button = FindWidget("0409");
	Widget *E11Button = FindWidget("0410");
	Widget *F1Button = FindWidget("0500");
	Widget *F2Button = FindWidget("0501");
	Widget *F3Button = FindWidget("0502");
	Widget *F4Button = FindWidget("0503");
	Widget *F5Button = FindWidget("0504");
	Widget *F6Button = FindWidget("0505");
	Widget *F7Button = FindWidget("0506");
	Widget *F8Button = FindWidget("0507");
	Widget *F9Button = FindWidget("0508");
	Widget *F10Button = FindWidget("0509");
	Widget *F11Button = FindWidget("0510");
	Widget *G1Button = FindWidget("0600");
	Widget *G2Button = FindWidget("0601");
	Widget *G3Button = FindWidget("0602");
	Widget *G4Button = FindWidget("0603");
	Widget *G5Button = FindWidget("0604");
	Widget *G6Button = FindWidget("0605");
	Widget *G7Button = FindWidget("0606");
	Widget *G8Button = FindWidget("0607");
	Widget *G9Button = FindWidget("0608");
	Widget *G10Button = FindWidget("0609");
	Widget *G11Button = FindWidget("0610");
	Widget *H1Button = FindWidget("0700");
	Widget *H2Button = FindWidget("0701");
	Widget *H3Button = FindWidget("0702");
	Widget *H4Button = FindWidget("0703");
	Widget *H5Button = FindWidget("0704");
	Widget *H6Button = FindWidget("0705");
	Widget *H7Button = FindWidget("0706");
	Widget *H8Button = FindWidget("0707");
	Widget *H9Button = FindWidget("0708");
	Widget *H10Button = FindWidget("0709");
	Widget *H11Button = FindWidget("0710");
	Widget *I1Button = FindWidget("0800");
	Widget *I2Button = FindWidget("0801");
	Widget *I3Button = FindWidget("0802");
	Widget *I4Button = FindWidget("0803");
	Widget *I5Button = FindWidget("0804");
	Widget *I6Button = FindWidget("0805");
	Widget *I7Button = FindWidget("0806");
	Widget *I8Button = FindWidget("0807");
	Widget *I9Button = FindWidget("0808");
	Widget *I10Button = FindWidget("0809");
	Widget *I11Button = FindWidget("0810");

	A1Button->SetObserver(&gridButtonObserver);
	A2Button->SetObserver(&gridButtonObserver);
	A3Button->SetObserver(&gridButtonObserver);
	A4Button->SetObserver(&gridButtonObserver);
	A5Button->SetObserver(&gridButtonObserver);
	A6Button->SetObserver(&gridButtonObserver);
	A7Button->SetObserver(&gridButtonObserver);
	A8Button->SetObserver(&gridButtonObserver);
	A9Button->SetObserver(&gridButtonObserver);
	A10Button->SetObserver(&gridButtonObserver);
	A11Button->SetObserver(&gridButtonObserver);
	B1Button->SetObserver(&gridButtonObserver);
	B2Button->SetObserver(&gridButtonObserver);
	B3Button->SetObserver(&gridButtonObserver);
	B4Button->SetObserver(&gridButtonObserver);
	B5Button->SetObserver(&gridButtonObserver);
	B6Button->SetObserver(&gridButtonObserver);
	B7Button->SetObserver(&gridButtonObserver);
	B8Button->SetObserver(&gridButtonObserver);
	B9Button->SetObserver(&gridButtonObserver);
	B10Button->SetObserver(&gridButtonObserver);
	B11Button->SetObserver(&gridButtonObserver);
	C1Button->SetObserver(&gridButtonObserver);
	C2Button->SetObserver(&gridButtonObserver);
	C3Button->SetObserver(&gridButtonObserver);
	C4Button->SetObserver(&gridButtonObserver);
	C5Button->SetObserver(&gridButtonObserver);
	C6Button->SetObserver(&gridButtonObserver);
	C7Button->SetObserver(&gridButtonObserver);
	C8Button->SetObserver(&gridButtonObserver);
	C9Button->SetObserver(&gridButtonObserver);
	C10Button->SetObserver(&gridButtonObserver);
	C11Button->SetObserver(&gridButtonObserver);
	D1Button->SetObserver(&gridButtonObserver);
	D2Button->SetObserver(&gridButtonObserver);
	D3Button->SetObserver(&gridButtonObserver);
	D4Button->SetObserver(&gridButtonObserver);
	D5Button->SetObserver(&gridButtonObserver);
	D6Button->SetObserver(&gridButtonObserver);
	D7Button->SetObserver(&gridButtonObserver);
	D8Button->SetObserver(&gridButtonObserver);
	D9Button->SetObserver(&gridButtonObserver);
	D10Button->SetObserver(&gridButtonObserver);
	D11Button->SetObserver(&gridButtonObserver);
	E1Button->SetObserver(&gridButtonObserver);
	E2Button->SetObserver(&gridButtonObserver);
	E3Button->SetObserver(&gridButtonObserver);
	E4Button->SetObserver(&gridButtonObserver);
	E5Button->SetObserver(&gridButtonObserver);
	E6Button->SetObserver(&gridButtonObserver);
	E7Button->SetObserver(&gridButtonObserver);
	E8Button->SetObserver(&gridButtonObserver);
	E9Button->SetObserver(&gridButtonObserver);
	E10Button->SetObserver(&gridButtonObserver);
	E11Button->SetObserver(&gridButtonObserver);
	F1Button->SetObserver(&gridButtonObserver);
	F2Button->SetObserver(&gridButtonObserver);
	F3Button->SetObserver(&gridButtonObserver);
	F4Button->SetObserver(&gridButtonObserver);
	F5Button->SetObserver(&gridButtonObserver);
	F6Button->SetObserver(&gridButtonObserver);
	F7Button->SetObserver(&gridButtonObserver);
	F8Button->SetObserver(&gridButtonObserver);
	F9Button->SetObserver(&gridButtonObserver);
	F10Button->SetObserver(&gridButtonObserver);
	F11Button->SetObserver(&gridButtonObserver);
	G1Button->SetObserver(&gridButtonObserver);
	G2Button->SetObserver(&gridButtonObserver);
	G3Button->SetObserver(&gridButtonObserver);
	G4Button->SetObserver(&gridButtonObserver);
	G5Button->SetObserver(&gridButtonObserver);
	G6Button->SetObserver(&gridButtonObserver);
	G7Button->SetObserver(&gridButtonObserver);
	G8Button->SetObserver(&gridButtonObserver);
	G9Button->SetObserver(&gridButtonObserver);
	G10Button->SetObserver(&gridButtonObserver);
	G11Button->SetObserver(&gridButtonObserver);
	H1Button->SetObserver(&gridButtonObserver);
	H2Button->SetObserver(&gridButtonObserver);
	H3Button->SetObserver(&gridButtonObserver);
	H4Button->SetObserver(&gridButtonObserver);
	H5Button->SetObserver(&gridButtonObserver);
	H6Button->SetObserver(&gridButtonObserver);
	H7Button->SetObserver(&gridButtonObserver);
	H8Button->SetObserver(&gridButtonObserver);
	H9Button->SetObserver(&gridButtonObserver);
	H10Button->SetObserver(&gridButtonObserver);
	H11Button->SetObserver(&gridButtonObserver);
	I1Button->SetObserver(&gridButtonObserver);
	I2Button->SetObserver(&gridButtonObserver);
	I3Button->SetObserver(&gridButtonObserver);
	I4Button->SetObserver(&gridButtonObserver);
	I5Button->SetObserver(&gridButtonObserver);
	I6Button->SetObserver(&gridButtonObserver);
	I7Button->SetObserver(&gridButtonObserver);
	I8Button->SetObserver(&gridButtonObserver);
	I9Button->SetObserver(&gridButtonObserver);
	I10Button->SetObserver(&gridButtonObserver);
	I11Button->SetObserver(&gridButtonObserver);
}

//
void GridWindow::HandleGridButtonEvent(Widget *widget, const WidgetEventData *eventData)
{
	if (eventData->eventType == kEventWidgetActivate)
	{
		WidgetKey widgetID = static_cast<WidgetKey>(widget->GetWidgetKey());
		Engine::Report(widgetID);

		if (widgetID == "0000")
		{
			//Move model to position x = 0, y = 0
			Point3D waypoint = Point3D(-8.0F, -8.0F, 0.0F);
			TheEngine->Report("WidgetID 0000 is clicked");
			TheEngine->Report("The model should begin to move to location 0,0");
			TestWorld *world = static_cast<TestWorld *>(TheWorldMgr->GetWorld());
			if (world)
			{
				Array<Model *> *models = world->GetModels();
				for (int i = 0; i < models->GetElementCount(); i++)
				{
					Model *model = static_cast<Model *>((*models)[i]);
					if (model)
					{
						RushPieceController *pieceController = static_cast<RushPieceController *>(model->GetController());
						if (pieceController && pieceController->IsPlayerControlled())
						{
							pieceController->SetWayPoint(waypoint);
						}
					}
				}
			}
		}
		else if (widgetID == "0001")
		{
		
		}
		else if (widgetID == "0002")
		{

		}
		else if (widgetID == "0003")
		{

		}
		else if (widgetID == "0004")
		{

		}
		else if (widgetID == "0005")
		{

		}
		else if (widgetID == "0006")
		{

		}
		else if (widgetID == "0007")
		{

		}
		//Add more

		
	}
}



