#pragma once
#include "../../Core/Classes/GameObject.h"


namespace KPEngine
{
	namespace Core
	{
		namespace Interfaces
		{
			class IGameObjectController
			{
			public:
				IGameObjectController(){};
				virtual ~IGameObjectController(){};
				virtual void Initialize(GameObject * i_pObject) = 0;
				virtual void Update(float i_deltaTime) = 0;
				virtual void PrintInfo() const = 0;
				virtual char GetSymbol() const = 0;
				virtual KPVector2 GetPosition() const = 0;
			};
		}
	}
}
