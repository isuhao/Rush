#include "RushTestWorld.h"
#include "RushPieceBase.h"
#include "GroundProperty.h"

using namespace C4;
using namespace Rush;

TestWorld::TestWorld(const char *name) : World(name)
{
}

TestWorld::~TestWorld()
{
}

WorldResult TestWorld::Preprocess()
{
	WorldResult result = World::Preprocess();
	if (result != kWorldOkay)
	{
		return (result);
	}
	/*----------------------------------- SET GROUND PROPERTY -------------------------------------*/
	//This seems to break the unit selection for some reason. Let's see if removing it fixes the
	//issue
	/*Node *root = this->GetRootNode();
	Node *node = root;
	unsigned int nodeType = 0;
	do
	{
		nodeType = node->GetNodeType();
		if (nodeType == kNodeGeometry)
		{
			Geometry *geo = static_cast<Geometry *>(node);
			if (geo)
			{
				Property *prop = geo->GetProperty(kPropertyGround);
				if (!prop)
				{
					GeometryObject *geoObj = static_cast<GeometryObject *>(geo->GetObject());
					if (geoObj)
					{
						geoObj->SetCollisionExclusionMask(kCollisionSightPath);
					}
				}
			}
		}
		node = root->GetNextNode(node);
	} while (node);
	*/
	/*----------------------------------- SET WORLD CAMERA ----------------------------------------*/
	SetCamera(&navCamera);
	return (kWorldOkay);
}

void TestWorld::Render(void)
{
	World::Render();
}

//Will likely need to be edited when we have lots of nodes on the screen
Array<Model *> *TestWorld::GetModels()
{
	models.Purge();

	Node *root = this->GetRootNode();
	Node *node = root;
	unsigned int nodeType = 0;
	do
	{
		nodeType = node->GetNodeType();
		if (nodeType == kNodeModel)
		{
			Model *model = static_cast<Model *>(node);
			if (model)
			{
				if (model->GetModelType() == kModelQueen);
				{
					TheEngine->Report("Queen model added to model array");
					models.AddElement(model);
				}
				//Add the rest of the pieces here
			}
		}
		node = root->GetNextNode(node);
	} while (node);
	TheEngine->Report("Model array completed");
	return &models;
}