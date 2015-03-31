#pragma once

#include "C4Engine.h"
#include "C4Input.h"
#include "C4World.h"
#include "C4Cameras.h"

using namespace C4;

namespace Rush
{
/*----------------------------------------- COMMAND DEFINITIONS ----------------------------------------*/
	enum
	{
		kActionSelect		= 'slct',
		kActionCommandMove	= 'move'
	};

	class RushCommandAction : public Action
	{
		private:
			bool clicked;
			/*------------------------------ COMMAND FUNCTION DEFINITIONS ------------------------------*/
			void ModelSelect();
			void ModelMoveCommand();

			Model *IsOverModel();


		public:
			RushCommandAction(unsigned_int32 type);
			~RushCommandAction();

			void Begin();
			void End();

	};
}