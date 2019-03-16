#pragma once
#include "../Lua/export/lua.hpp"
#include "../../Core/Classes/GameObject.h"
#include "../../Utils/SmartPointers.h"

namespace KPEngine
{
	namespace Scripting
	{
		namespace Lua
		{
			class LuaSystem
			{
			public:
				static void Initialize();
				static void Shutdown();
				static StrongPointer<Core::GameObject> CreateActor(const char* i_pScriptFileName);
			private:
				static lua_State* g_pLuaState;
			};


		}
	}

	
}

