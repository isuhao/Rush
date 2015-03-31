#pragma once

#include "C4Engine.h"
#include "C4World.h"
#include "RushCameras.h" //Needed to attach cameras to world

using namespace C4;
namespace Rush
{
	class TestWorld : public World
	{
		private:
			RushCamera		navCamera;
			Array<Model *>	models;
		public:
			TestWorld(const char *name);
			~TestWorld();

			WorldResult Preprocess(void);
			void Render(void);
			RushCamera *GetNavCamera(void)
			{
				return (&navCamera);
			}
			Array<Model *> *GetModels();
	};
}