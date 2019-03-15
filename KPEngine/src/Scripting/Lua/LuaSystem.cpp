#include "../../../include/Scripting/Lua/LuaSystem.h"
#include <cassert>

namespace KPEngine
{
	namespace Scripting
	{
		namespace Lua
		{
			lua_State* LuaSystem::g_pLuaState;
			void LuaSystem::Initialize()
			{
				g_pLuaState = luaL_newstate();
				assert(g_pLuaState);
				luaL_openlibs(g_pLuaState);

				//// Call the Lua C API function lua_type
				//// to get the type of the top item on stack   
				//int type = lua_type(pLuaState, -1);
				// lua_tointeger
				// lua_pop
				// lua_len
				// lua_tostring
				// lua_tonumber
				// lua_loadbuffer Returning not 0 means error in lua code?
				// lua_pcall
			}

			void LuaSystem::Shutdown()
			{
				lua_close(g_pLuaState);
			}
		}
	}
}

