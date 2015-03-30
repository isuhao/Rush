#include "RushPieceBase.h"
#include "RushGame.h"
#include "C4Packing.h"

using namespace C4;
using namespace Rush;

/*--------------------------------- CONSTRUCTORS AND DESTRUCTORS --------------------------------*/
RushPieceController::RushPieceController() : Controller(kControllerQueen), 
											 selected(false),
											 matObject(nullptr),
											 diffuse(nullptr),
											 emission(nullptr),
											 curRotation(0),
											 reqRotation(0),
											 playerControlled(false),
											 wayPoint(0.0F,0.0F,0.0F)
{
}

RushPieceController::RushPieceController(const RushPieceController &pieceController) : Controller(pieceController)
{
}

Controller *RushPieceController::Replicate(void) const
{
	return (new RushPieceController(*this));
}

RushPieceController::~RushPieceController()
{
	if (matObject)
	{
		matObject->Release();
	}
}

/*--------------------------------- USED FOR UNIT SELECTION -------------------------------------*/
void RushPieceController::SetSelected(bool select)
{
	TheEngine->Report("SetSelected() is called");
	if (selected != select)
	{
		selected = select;

		if (emission)
		{
			if (selected)
			{
				TheEngine->Report("SetSelected() is true");
				emission->SetEmissionColor(ColorRGB(1.0F, 1.0F, 0.5F));
			}
			else
			{
				emission->SetEmissionColor(ColorRGB(0.0F, 0.0F, 0.0F));
			}
		}
	}
}

bool RushPieceController::IsSelected()
{
	TheEngine->Report("IsSelected() is called");
	return selected;
}

/*------------------------ CHECKS THAT CONTROLLER IS ATTACHED TO A MODEL ------------------------*/
bool RushPieceController::ValidNode(const Node *node)
{
	if (node && node->GetNodeType() == kNodeModel)
	{
		return (true);
	}
	return (false);
}

/*--------------------------- CHECKS THAT WAYPOINT IS VALID FOR MODEL ---------------------------*/
bool RushPieceController::IsValidWayPoint()
{

}

/*-------------------------------- MODIFIES CONTROLLER SETTINGS ---------------------------------*/
int32 RushPieceController::GetSettingCount(void) const
{
	return (1);
}

Setting* RushPieceController::GetSetting(int32 index) const
{
	if (index == 0)
	{
		return (new BooleanSetting('pctl', playerControlled, "Player Controlled"));
	}
	return (nullptr);
}

void RushPieceController::SetSetting(const Setting *setting)
{
	if (setting->GetSettingIdentifier() == 'pctl')
	{
		playerControlled = (static_cast<const BooleanSetting *>(setting))->GetBooleanValue();
	}
}

/*------------------------------------- USED FOR NETWORKING -------------------------------------*/
	/*------------------------------------- SERIALIZATION -----------------------------------*/
void RushPieceController::Pack(Packer &data, unsigned_int32 packFlags) const
{
	Controller::Pack(data, packFlags);

	data << ChunkHeader('pctl', 4);
	data << playerControlled;
	data << TerminatorChunk;
}

void RushPieceController::Unpack(Unpacker &data, unsigned_int32 unpackFlags)
{
	Controller::Unpack(data, unpackFlags);

	UnpackChunkList<RushPieceController>(data, unpackFlags);
}

bool RushPieceController::UnpackChunk(const ChunkHeader *chunkHeader, Unpacker &data, unsigned_int32 unpackFlags)
{
	switch (chunkHeader->chunkType)
	{
		case 'pctl':
			data >> playerControlled;
			return true;
	}

	return false;
}



void RushPieceController::Preprocess(void)
{
	Controller::Preprocess();

	Node *node = this->GetTargetNode();
	Model *model = static_cast<Model *>(node);
	if (model)
	{
		wayPoint = model->GetNodePosition();
		
		matObject = new MaterialObject();
		diffuse = new DiffuseAttribute();
		emission = new EmissionAttribute(kAttributeMutable);

		if(playerControlled)
		{
			diffuse->SetAttributeColor(ColorRGB(0.5F, 0.5F, 1.0F));
		}
		else
		{
			diffuse->SetAttributeColor(ColorRGB(1.0F, 0.5F, 0.5F));
		}
		
		emission->SetEmissionColor(ColorRGB(0.0F, 0.0F, 0.0F));

		matObject->AddAttribute(diffuse);
		matObject->AddAttribute(emission);

		Geometry *modelGeometry = static_cast<Geometry *>(model->GetFirstSubnode());
		if (modelGeometry)
		{
			modelGeometry->SetMaterialObject(0, matObject);
		}
	}
}

void RushPieceController::Move(void)
{
	float dt = TheTimeMgr->GetFloatDeltaTime()*0.001F;
	
	Node *node = this->GetTargetNode();
	if (node)
	{
		Model *model = static_cast<Model *>(node);
		if (model)
		{
			MovePiece(model, dt);
			model->Invalidate();
		}
	}

}

void RushPieceController::Travel(void)
{
}

void RushPieceController::MovePiece(Model *model, float dt)
{
	if (!model || (model->GetModelType() != kModelQueen))
	{
		return;
	}

	//Get the direction that the piece should be facing
	//Difference between current location and desired location
	Vector3D reqDirVector = wayPoint - model->GetNodePosition(); 

	//Get distance to the waypoint
	float travelDistance = Magnitude(reqDirVector);

	reqDirVector.Normalize();

	reqRotation = Atan(reqDirVector.y, reqDirVector.x);

	float deltaRotation = reqRotation - curRotation;

	while (deltaRotation > K::pi)
	{
		deltaRotation += K::two_pi;
	}

	while (deltaRotation > K::pi)
	{
		deltaRotation -= K::two_pi;
	}

	bool rotationArrived = true;

	//Check if delta rotation is larger than threshold
	if (Fabs(deltaRotation) > 1.0F)
	{
		rotationArrived = false;

		if (deltaRotation < 0)
		{
			curRotation -= 1.0F*dt;
		}
		else if (deltaRotation > 0)
		{
			curRotation += 1.0F*dt;
		}
	}

	//Start with the current position
	Point3D newPosition = model->GetNodePosition();
	if (travelDistance > 1.0F && rotationArrived)
	{
		//Advance the position
		newPosition += reqDirVector * 0.5F * dt;
	}

	//Start with a transform about the pivot
	Transform4D transform;
	transform.SetRotationAboutZ(curRotation);
	model->SetNodeTransform(transform);

	//Then move the node to the new position
	model->SetNodePosition(newPosition);
}