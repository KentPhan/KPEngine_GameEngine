#include "../../include/GameObjects/GameObject.h"

#include <iostream>
#include <cassert>

using namespace  KPEngine::Utils;

namespace MonsterChaseGame
{
	namespace GameObjects
	{
		GameObject::GameObject()
		{
			this->Position = KPVector2(0, 0);
		}

		char* GameObject::GetName() const
		{
			return name_->Get();
		}

		void GameObject::SetName(const char* name)
		{
			assert(name);

			delete name_;
			name_ = new KPString(name);
		}

		void GameObject::PrintInfo() const
		{
			std::cout << "Name: " << name_->Get() << "\n";
		}

		char GameObject::GetSymbol()
		{
			return 'U';
		}

		void GameObject::SetPosition(int i_x, int i_y)
		{
			this->Position.X(i_x);
			this->Position.Y(i_y);
		}


		GameObject::~GameObject()
		{
			delete name_;
		}
	}
}


