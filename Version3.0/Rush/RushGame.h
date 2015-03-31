#pragma once

#include "C4Application.h"
#include "C4Interface.h"
#include "C4Engine.h"
#include "RushTestWorld.h"
#include "RushCameraNavigation.h"
#include "MouseInterface.h"
#include "RushPieceBase.h"
#include "RushCommandAction.h"
#include "GroundProperty.h"
#include "RushLoad.h"

extern "C"
{
	C4MODULEEXPORT C4::Application* ConstructApplication();
}

using namespace C4;

namespace Rush
{
	class RushGame : public Singleton<RushGame>, public Application
	{
		private:
			DisplayEventHandler						displayEventHandler;

			CameraNavigationAction					*moveForwardAction;
			CameraNavigationAction					*moveBackwardAction;
			CameraNavigationAction					*moveLeftAction;
			CameraNavigationAction					*moveRightAction;
			CameraNavigationAction					*rotLeftAction;
			CameraNavigationAction					*rotRightAction;
			CameraNavigationAction					*zoomInAction;
			CameraNavigationAction					*zoomOutAction;
			CameraNavigationAction					*zoomAction;
			CameraNavigationAction					*zoomWheelAction;

			RushCommandAction						*selectAction;
			RushCommandAction						*moveAction;

			//ModelRegistration						pawnModelReg;
			//ModelRegistration						knightModelReg;
			//ModelRegistration						bishopModelReg;
			//ModelRegistration						rookModelReg;
			ModelRegistration						queenModelReg;
			//ModelRegistration						kingModelReg;
			ModelRegistration						battleshipModelReg;
			ModelRegistration						torpedoModelReg;
			ModelRegistration						salvageModelReg;
			ModelRegistration						carrierModelReg;
			ModelRegistration						destroyerModelReg;

			ControllerReg<RushPieceController>		pawnControllerReg;
			ControllerReg<RushPieceController>		knightControllerReg;
			ControllerReg<RushPieceController>		bishopControllerReg;
			ControllerReg<RushPieceController>		rookControllerReg;
			ControllerReg<RushPieceController>		queenControllerReg;
			ControllerReg<RushPieceController>		kingControllerReg;
			ControllerReg<RushPieceController>		battleshipControllerReg;
			ControllerReg<RushPieceController>		torpedoControllerReg;
			ControllerReg<RushPieceController>		salvageControllerReg;
			ControllerReg<RushPieceController>		carrierControllerReg;
			ControllerReg<RushPieceController>		destroyerControllerReg;

			//Entering PropertyReg seems to break selection
			//PropertyReg<GroundProperty>				groundPropertyReg;

			MouseInterface							*mouseInterface;

			InputMgr::KeyProc						*prevEscapeProc;
			void									*prevEscapeCookie;
			
		public:
			RushGame();
			~RushGame();

			static World *CreateWorld(const char *name, void *data);
			static void HandleDisplayEvent(const DisplayEventData *eventData, void *cookie);
			static void EscapeProc(void *cookie);
			MouseInterface GetMouseInterface()
			{
				return *mouseInterface;
			}

	};

	extern RushGame* TheGame;

}

