#pragma once
#include "../../Core/GameObject/GameObject.h"


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
				
				virtual void Initialize(WeakPointer<GameObject> i_pObject) = 0;
				virtual void Destroy() = 0;
				virtual void Update(float i_deltaTime) = 0;
				virtual void PrintInfo() const = 0;
				virtual char GetSymbol() const = 0;
				virtual KPVector3SSE GetPosition() const = 0;
			protected:
				virtual ~IGameObjectController() {};
			};
		}
	}
}
