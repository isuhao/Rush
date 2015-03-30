#include "RushCommandAction.h"
#include "C4Engine.h"
#include "C4Interface.h"
#include "RushGame.h"

#include "RushPieceBase.h"

using namespace C4;
using namespace Rush;


/*--------------------------------- CONSTRUCTORS AND DESTRUCTORS --------------------------------*/
RushCommandAction::RushCommandAction(unsigned_int32 type) : Action(type), clicked(false)
{
}

RushCommandAction::~RushCommandAction()
{
}

void RushCommandAction::Begin(void)
{
	if (!clicked)
	{
		/*--------------------------------- COMMAND SELECTION -----------------------------------*/
		/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		NOTE: CURRENTLY THIS IS SET UP AS A BUNCH OF IF-ELSEIF-ELSE STATEMENTS, BUT IT WOULD BE
			  A LOT BETTER TO IMPLEMENT THIS AS A SWITCH-CASE STATEMENT. I REALLY JUST DON'T WANT
			  TO BE BOTHERED AT THE MOMENT AND THIS WORKS. MAYBE WE CAN CHANGE THIS LATER.
																						- SASHA
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		if (this->GetActionType() == kActionSelect)
		{
			TheEngine->Report("Select Action initiated");
			ModelSelect();
		}
		else if (this->GetActionType() == kActionCommandMove)
		{
			TheEngine->Report("Move Action initiated");
			ModelMoveCommand();
		}

		clicked = true;
	}
}

void RushCommandAction::End(void)
{
	clicked = false;
}


/*--------------------------------- FUNCTIONS FOR UNIT SELECTION --------------------------------*/
Model *RushCommandAction::IsOverModel()
{
	TheEngine->Report("IsOverModel() has been called");
	TestWorld *world = static_cast<TestWorld *>(TheWorldMgr->GetWorld());
	if (world)
	{
		TheEngine->Report("IsOverModel: World if statement has been triggered");
		RushCamera *cam = world->GetNavCamera();
		Point3D camPosition = cam->GetNodePosition();
		Point3D curFocus = cam->GetCurrentFocus();

		CollisionData data;
		CollisionState state = kCollisionStateNone;

		Ray ray;
		Point3D cursorPoint = TheInterfaceMgr->GetCursorPosition();
		cam->GetWorldRayFromPoint(Point2D(cursorPoint.x, cursorPoint.y), &ray);

		float distance = Magnitude(camPosition - curFocus);
		Point3D p1 = ray.origin;
		Point3D	p2 = ray.origin + ray.direction*ray.tmax;

		//Test against all geometry
		state = world->QueryCollision(p1, p2, 0.0F, 0, &data); //Was world->QueryWorld online

		if (state != kCollisionStateNone)
		{
			TheEngine->Report("IsOverModel: Collision with ray detected");
			Geometry *geo = data.geometry;
			Node *node = geo->GetSuperNode();
			bool overModel = false;
			while (node)
			{
				TheEngine->Report("IsOverModel: Node while loop is activated");
				if (node->GetNodeType() == kNodeModel)
				{
					TheEngine->Report("IsOverModel: Node found is model");
					Model *model = static_cast<Model *>(node);
					if (model && model->GetModelType() == kModelQueen)
					{
						TheEngine->Report("IsOverModel: Model has been identified as queen");
						return model;
					}
					//Add other model enums here
					else
					{
						TheEngine->Report("IsOverModel: Model is not identified");
						return nullptr;
					}
				}
				//Not a model, so keep looking to the super node
				TheEngine->Report("IsOverModel: Node found is not a model");
				node = node->GetSuperNode();
			}
		}
	}
	TheEngine->Report("No collision detected. Nullptr returned");
	return nullptr;
}

void RushCommandAction::ModelSelect()
{
	TheEngine->Report("ModelSelect() is called");
	//Reset all models
	TestWorld *world = static_cast<TestWorld *>(TheWorldMgr->GetWorld());
	Array<Model *> *models = world->GetModels();

	RushPieceController *pieceController = nullptr;
	Model *pieceModel = nullptr;
	for (int32 i = 0; i < models->GetElementCount(); i++)
	{
		pieceModel = static_cast<Model *>((*models)[i]);
		if (pieceModel)
		{
			pieceController = static_cast<RushPieceController *>(pieceModel->GetController());
			if (pieceController)
			{
				pieceController->SetSelected(false);
			}
		}
	}

	//Now see if any of them are clicked on
	TheEngine->Report("ModelSelect: Called IsOverModel()");
	pieceModel = IsOverModel();

	if (pieceModel)
	{
		TheEngine->Report("ModelSelect: pieceModel is not null");
		pieceController = static_cast<RushPieceController *>(pieceModel->GetController());
		if (!pieceController->IsSelected() &&pieceController->IsPlayerControlled())
		{
			pieceController->SetSelected(true);
		}
	}
	
}

/*--------------------------------- FUNCTIONS FOR UNIT MOVEMENT ---------------------------------*/
void RushCommandAction::ModelMoveCommand()
{
	TheEngine->Report("ModelMoveCommand is called");
	TestWorld*world = static_cast<TestWorld *>(TheWorldMgr->GetWorld());
	if (world)
	{
		TheEngine->Report("ModelMoveCommand: world statement entered");
		RushCamera *cam = world->GetNavCamera();
		Point3D camPosition = cam->GetNodePosition();
		Point3D camFocus = cam->GetCurrentFocus();

		CollisionData data;
		CollisionState state = kCollisionStateNone;

		Ray ray;
		Point3D cursorPoint = TheInterfaceMgr->GetCursorPosition();
		cam->GetWorldRayFromPoint(Point2D(cursorPoint.x, cursorPoint.y), &ray);

		float distance = Magnitude(camPosition - camFocus);
		Point3D p1 = ray.origin;
		Point3D p2 = ray.origin + ray.direction*ray.tmax;
		
		state = world->QueryCollision(p1, p2, 0.0F, 0, &data);

		if (state != kCollisionStateNone)
		{
			TheEngine->Report("ModelMoveCommand: collision has been detected");
			Geometry *geo = data.geometry;
			Node *node = geo->GetSuperNode();

			if (node)
			{
				TheEngine->Report("ModelMoveCommand: node statement entered");
				Array<Model *> *models = world->GetModels();
				for (int32 i = 0; i < models->GetElementCount(); i++)
				{
					Model *model = static_cast<Model *>((*models)[i]);
					if (model)
					{
						TheEngine->Report("ModelMoveCommand: model exists and model statement entered");
						RushPieceController *modelController = static_cast<RushPieceController *>(model->GetController());
						if (modelController && modelController->IsSelected() && cam)
						{
							TheEngine->Report("ModelMoveCommand: waypoint is set");
							modelController->SetWayPoint(data.position);
						}
					}
				}
			}
		}

	}
}
