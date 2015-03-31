#pragma once

#include "RushPieceBase.h"
#include "C4Controller.h"
#include "C4World.h"
#include "C4Configuration.h"
#include "C4Physics.h"

using namespace C4;

namespace Rush
{
	class RushBattleshipController : public RushPieceController
	{
		private:
			unsigned_int32			*movementFlags;
			float					groundCosine;

			float					modelAzimuth;
			float					modelAltitude;

		public:
			RigidBodyStatus HandleNewGeometryContact(const GeometryContact *contact);

			bool					playerControlled;
	};
}

