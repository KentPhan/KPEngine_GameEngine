#pragma once
#include "../../Core/Classes/KPGameObject.h"


namespace KPEngine
{
	namespace Core
	{
		namespace Interfaces
		{
			class IKPGameObjectController
			{
			public:
				IKPGameObjectController(){};
				virtual ~IKPGameObjectController(){};
				virtual void Initialize(KPGameObject * i_pObject, KPGameObject* (*i_Map)[20][20]) = 0;
				virtual void UpdateGameObject() = 0;
				virtual void PrintInfo() const = 0;
				virtual char GetSymbol() const = 0;
				virtual KPVector2 GetPosition() const = 0;
			};
		}
	}
}
