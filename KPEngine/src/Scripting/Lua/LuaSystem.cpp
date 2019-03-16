#include "../../../include/Scripting/Lua/LuaSystem.h"
#include <cassert>
#include "../../../include/Utils/FileIO.h"

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

			StrongPointer<Core::GameObject> LuaSystem::CreateActor(const char* i_pScriptFileName)
			{
				size_t l_SizeFile;
				// TODO need to adapt pathing
				void * l_pFileContents = FileIO::LoadFile(i_pScriptFileName, l_SizeFile);



				//// exit if something didn't work
				//	// probably need some debug logging in here!!!!
				//if (l_pFileContents)
				//	delete[] l_pFileContents;

				//if (l_pFileContents == nullptr)
				//	return NULL;

				if (l_pFileContents && l_SizeFile)
				{
					int result = 0;
					result = luaL_loadbuffer(g_pLuaState, reinterpret_cast<char*>(l_pFileContents), l_SizeFile, nullptr);

					assert(result == 0);

					result = lua_pcall(g_pLuaState, 0, 0, 0);

					assert(result == 0);

					// Getting number of items in table
					int l_type1 = lua_getglobal(g_pLuaState, "Player");
					assert(l_type1 == LUA_TTABLE);


					lua_len(g_pLuaState, -1);
					assert(lua_type(g_pLuaState, -1) == LUA_TNUMBER);

					lua_Integer table_entries = lua_tointeger(g_pLuaState, -1);
					lua_pop(g_pLuaState, 1);


					// Getting a specific key
					int l_type2 = lua_getglobal(g_pLuaState, "Player");
					assert(l_type2 == LUA_TTABLE);

					lua_pushstring(g_pLuaState, "name");

					// Using stack field 1 as the key, get it's value from the table (in
					// stack field 2) replacing the key in field 1 by the associated value
					int l_type3 = lua_gettable(g_pLuaState, -2); // Player[top of stack after popping] =  Does Player(-2)["name"(Top of Stack)]
					// It should be a string
					assert(l_type3 == LUA_TSTRING);

					// Retrieve the value associated with key "name" as a string, assuming it�s a string
					const char * pName = lua_tostring(g_pLuaState, -1);

					// Pop it off the stack now we're done
					lua_pop(g_pLuaState, 1);


				}


				





				return nullptr;
			}

		}
	}

	
}

