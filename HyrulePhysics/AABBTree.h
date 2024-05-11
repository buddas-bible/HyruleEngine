#pragma once

namespace hyrule
{
	namespace Physics
	{
		struct AABBnode
		{
			AABBnode* parent;
			AABBnode* left;
			AABBnode* right;

			bool isLeaf();
		};


		class AABBTree
		{
		public:


			void Rotate();

			void Insert();
			void Remove();
			void Query();
		};
	}
}

