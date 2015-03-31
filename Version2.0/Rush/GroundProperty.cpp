#include "GroundProperty.h"

using namespace C4;
using namespace Rush;

GroundProperty::GroundProperty() : Property(kPropertyGround)
{
}

GroundProperty::~GroundProperty()
{
}

bool GroundProperty::ValidNode(const Node *node)
{
	return (node->GetNodeType() == kNodeGeometry);
}

void GroundProperty::Pack(Packer &data, unsigned_int32 packFlags) const
{
	Property::Pack(data, packFlags);
}

void GroundProperty::Unpack(Unpacker &data, unsigned_int32 unpackFlags)
{
	Property::Unpack(data, unpackFlags);
}