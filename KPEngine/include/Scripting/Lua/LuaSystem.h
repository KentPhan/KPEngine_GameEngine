#pragma once
#include "../Lua/export/lua.hpp"

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
			private:
				static lua_State* g_pLuaState;
			};


		}
	}
}


