#pragma once

#include "C4World.h"

using namespace C4;

namespace Rush
{
	enum
	{
		kPropertyGround = 'grnd'
	};

	class GroundProperty : public Property
	{
		private:

		public:
			GroundProperty();
			~GroundProperty();

			static bool ValidNode(const Node *node);

			void Pack(Packer &data, unsigned_int32 packFlags) const;
			void Unpack(Unpacker &data, unsigned_int32 unpackFlags);
	};
}