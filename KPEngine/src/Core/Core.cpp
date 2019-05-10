#include "../../include/Core/Core.h"
#include "../../include/Scripting/Lua/LuaSystem.h"


namespace KPEngine
{
	namespace Core
	{
		StrongPointer<GameObject> Core::InstantiateGameObject(const char* i_pScriptFileName)
		{
			return Scripting::Lua::LuaSystem::CreateGameObject(i_pScriptFileName, false, KPVector3SSE::Zero());
		}

		StrongPointer<GameObject> Core::InstantiateGameObject(const char* i_pScriptFileName, KPVector3SSE i_StartPosition)
		{
			return Scripting::Lua::LuaSystem::CreateGameObject(i_pScriptFileName, true, i_StartPosition);
		}

		void Core::DestroyGameObject(StrongPointer<GameObject> i_ObjectToDestroy)
		{
		}
	}
}

