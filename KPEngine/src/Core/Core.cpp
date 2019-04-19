#include "../../include/Core/Core.h"
#include "../../include/Scripting/Lua/LuaSystem.h"


namespace KPEngine
{
	namespace Core
	{
		StrongPointer<GameObject> Core::InstantiateGameObject(const char* i_pScriptFileName)
		{
			return Scripting::Lua::LuaSystem::CreateGameObject(i_pScriptFileName);
		}
	}
}

