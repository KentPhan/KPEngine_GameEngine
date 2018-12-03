#pragma once
#include "Core/Classes/KPGameObject.h"


namespace KPEngine
{
	namespace Core
	{
		namespace Interfaces
		{
			class IKPGameObjectController
			{
			public:
				virtual void Initialize() = 0;
				virtual void SetGameObject(KPGameObject * i_pObject) = 0;
				virtual void SetMap(KPGameObject* i_Map) = 0;
				virtual void UpdateGameObject() = 0;
				virtual void PrintInfo() const = 0;
				virtual char GetSymbol() const = 0;
				virtual KPVector2 GetPosition() const = 0;
			};
		}
	}
}
