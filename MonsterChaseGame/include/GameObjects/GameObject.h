#pragma once

#include "GameObjectType.h"
#include "Utils/KPString.h"
#include "Utils/KPVector2.h"
#include <cassert>
#include <iostream>

using namespace KPEngine::Utils;

namespace MonsterChaseGame
{
	namespace GameObjects
	{
		class GameObject
		{

		protected:
			KPString * name_;


		public:
			inline char* GetName() const
			{
				return name_->Get();
			}
			inline void SetName(const char* name)
			{
				assert(name);

				delete name_;
				name_ = new KPString(name);
			}
			inline virtual void PrintInfo() const
			{
				std::cout << "Name: " << name_->Get() << "\n";
			}
			inline virtual char GetSymbol()
			{
				return 'U';
			}
			inline void SetPosition(int i_x, int i_y)
			{
				this->Position.X(i_x);
				this->Position.Y(i_y);
			}

			KPVector2 Position;
			GameObjectType Type;

			bool empty = true;
			inline GameObject()
			{
				this->Position = KPVector2(0, 0);
			}
			inline ~GameObject()
			{
				delete name_;
			}
		};
	}
}


