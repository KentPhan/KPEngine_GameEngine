#pragma once
#include <vector>
//#include "../../../../PlatformerGame/include/GameObjects/GameObjectType.h"
#include "../Utils/SmartPointers.h"
#include "GameObject/GameObject.h"
namespace KPEngine
{
	using Utils::StrongPointer;

	namespace Core
	{
		class Core
		{
		public:
			static StrongPointer<GameObject> InstantiateGameObject(const char* i_pScriptFileName);
			static StrongPointer<GameObject> InstantiateGameObject(const char* i_pScriptFileName, KPVector3SSE i_StartPosition);
		};


	}
}
