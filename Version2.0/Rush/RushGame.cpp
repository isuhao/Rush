#include "RushGame.h"
#include "MouseInterface.h"
#include "RushLoad.h"

using namespace C4;
using namespace Rush;

RushGame* Rush::TheGame = nullptr;
StartWindow* Rush::TheStartWindow = nullptr;
JoinWindow* Rush::TheJoinWindow = nullptr;

Application* ConstructApplication()
{
	return (new RushGame);
}

void RushGame::HandleDisplayEvent(const DisplayEventData *eventData, void *cookie)
{
	if (eventData->eventType == kEventDisplayChange)
	{

	}
}

void RushGame::EscapeProc(void *cookie)
{

}

RushGame::RushGame() : Singleton<RushGame>(TheGame),
					   displayEventHandler(&HandleDisplayEvent),

/*-------------------------------- Controller Registrations -----------------------------------*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
The way that the controller registrations work is:

controllerReg(enumerationForController, textNameOfControllerInPanel)

This will work. Figured out 16:09 March 27th 2015.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
					   queenControllerReg(kControllerQueen, "Queen"), 

/*------------------------------------- Model Registrations -----------------------------------*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
The way that the model registration works is:

modelReg(modelEnum, whatYouCallItInPanel, pathToWhereItsStored, enumFlags, defaultController)

This will work. Figured out 16:09 March 27th 2015.
To make things simple, store all models in C4/Data/Rush/model and all textures in 
C4/Import/Rush/model
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
					   queenModelReg(kModelQueen, "queen", "model/whiteQueen", kModelPrecache, kControllerQueen)

/*------------------------------------ Property Registrations ---------------------------------*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
For some reason adding the groundPropertyReg seems to break the unit selection....I'm not sure
why...
																			-Sasha
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
					   //groundPropertyReg(kPropertyGround, "Ground Type")
{
	/*------------------------------- Set Display Event Handler -------------------------------*/
	TheDisplayMgr->InstallDisplayEventHandler(&displayEventHandler);

	/*---------------------------------- Escape Key Function ----------------------------------*/
	prevEscapeProc = TheInputMgr->GetEscapeProc();
	prevEscapeCookie = TheInputMgr->GetEscapeCookie();
	TheInputMgr->SetEscapeProc(&EscapeProc, this);

	/*--------------------------------- Set World Constructor ---------------------------------*/
	TheWorldMgr->SetWorldConstructor(&CreateWorld);

	/*------------------------------ Initialize camera movements ------------------------------*/
	moveLeftAction = new CameraNavigationAction(kActionCameraLeft, kNavMoveLeft);
	moveRightAction = new CameraNavigationAction(kActionCameraRight, kNavMoveRight);
	moveForwardAction = new CameraNavigationAction(kActionCameraForward, kNavMoveForward);
	moveBackwardAction = new CameraNavigationAction(kActionCameraBackward, kNavMoveBackward);
	rotLeftAction = new CameraNavigationAction(kActionCameraRotateLeft, kNavMoveRotLeft);
	rotRightAction = new CameraNavigationAction(kActionCameraRotateRight, kNavMoveRotRight);
	zoomInAction = new CameraNavigationAction(kActionCameraZoomIn, kNavMoveZoomIn);
	zoomOutAction = new CameraNavigationAction(kActionCameraZoomOut, kNavMoveZoomOut);
	zoomAction = new CameraNavigationAction(kActionCameraZoom, kNavMoveZoom);
	zoomWheelAction = new CameraNavigationAction(kActionCameraZoomWheel, kNavMoveZoomWheel);

	/*------------------------------ Initialize piece actions ---------------------------------*/
	selectAction = new RushCommandAction(kActionSelect);
	moveAction	 = new RushCommandAction(kActionCommandMove);

	/*------------------------------ Initialize mouse whatever --------------------------------*/
	mouseInterface = new MouseInterface();

	/*------------------------------- Register camera movements -------------------------------*/
	TheInputMgr->AddAction(moveLeftAction);
	TheInputMgr->AddAction(moveRightAction);
	TheInputMgr->AddAction(moveForwardAction);
	TheInputMgr->AddAction(moveBackwardAction);
	TheInputMgr->AddAction(rotLeftAction);
	TheInputMgr->AddAction(rotRightAction);
	TheInputMgr->AddAction(zoomInAction);
	TheInputMgr->AddAction(zoomOutAction);
	TheInputMgr->AddAction(zoomAction);
	TheInputMgr->AddAction(zoomWheelAction);

	/*------------------------------- Register piece actions ----------------------------------*/
	TheInputMgr->AddAction(selectAction);
	TheInputMgr->AddAction(moveAction);

	/*--------------------------------- Set Input Management ----------------------------------*/
	TheInputMgr->SetInputMode(kInputInactive);
	TheInterfaceMgr->SetInputManagementMode(kInputManagementAutomatic); 
	//kInputManagementManual shows the cursor but does not all for input
	TheInterfaceMgr->ShowCursor();

	/*-------------------------------------- Set Widgets --------------------------------------*/
	TheInterfaceMgr->AddWidget(new StartWindow);

	
	
}

RushGame::~RushGame()
{
	/*------------------------------ Unregister camera movements ------------------------------*/
	if (moveLeftAction)
	{	
		delete moveLeftAction;
	}

	if (moveRightAction)
	{
		delete moveRightAction;
	}

	if (moveForwardAction)
	{
		delete moveForwardAction;
	}

	if (moveBackwardAction)
	{
		delete moveBackwardAction;
	}

	if (rotLeftAction)
	{
		delete rotLeftAction;
	}

	if (rotRightAction)
	{
		delete rotRightAction;
	}

	if (zoomInAction)
	{
		delete zoomInAction;
	}

	if (zoomOutAction)
	{
		delete zoomOutAction;
	}

	if (zoomAction)
	{
		delete zoomAction;
	}

	if (zoomWheelAction)
	{
		delete zoomWheelAction;
	}

	/*------------------------------ Unregister piece actions --------------------------------*/
	if (selectAction)
	{
		delete selectAction;
	}
	if (moveAction)
	{
		delete moveAction;
	}

	/*------------------------------ Unregister mouse movements ------------------------------*/
	if (mouseInterface)
	{
		delete mouseInterface;
	}
	/*---------------------------------- Unregister widgets ----------------------------------*/
	delete TheStartWindow;
	delete TheJoinWindow;

}

World *RushGame::CreateWorld(const char *name, void *data)
{
	return (new TestWorld(name));
}

