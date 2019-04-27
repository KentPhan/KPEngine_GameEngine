#include "../../../include/Scripting/Lua/LuaSystem.h"
#include <cassert>
#include "../../../include/Utils/FileIO.h"
#include "../../../include/Graphics/RendererSystem.h"
#include "../../../include/Physics/PhysicsComponent.h"
#include "../../../include/Physics/PhysicsSystem.h"
#include "../../../include/Collision/CollisionSystem.h"
#include "../../../include/Core/GameObject/GameObjectSystem.h"
#


// TODO strcmp is bad possibly in here
namespace KPEngine
{
	using namespace KPEngine::Core;

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

			StrongPointer<Core::GameObject> LuaSystem::CreateGameObject(const char* i_pScriptFileName)
			{
				size_t l_SizeFile;
				StrongPointer<GameObject> l_NewStrongPointer = nullptr;

				// TODO need to adapt pathing
				char * l_pFileContents = static_cast<char*>(FileIO::LoadFile(i_pScriptFileName, l_SizeFile));

				// TODO File Error Handling
				//// exit if something didn't work
				//	// probably need some debug logging in here!!!!
				//if (l_pFileContents)
				//	delete[] l_pFileContents;

				//if (l_pFileContents == nullptr)
				//	return NULL;

				if (l_pFileContents && l_SizeFile)
				{
					int result = 0;
					result = luaL_loadbuffer(g_pLuaState, l_pFileContents, l_SizeFile, nullptr);
					assert(result == 0);
					result = lua_pcall(g_pLuaState, 0, 0, 0);
					assert(result == 0);

					
					// Getting number of items in table
					/*int l_type1 = lua_getglobal(g_pLuaState, "GameObject");
					assert(l_type1 == LUA_TTABLE);


					lua_len(g_pLuaState, -1);
					assert(lua_type(g_pLuaState, -1) == LUA_TNUMBER);

					lua_Integer table_entries = lua_tointeger(g_pLuaState, -1);
					int l_table_Entries = table_entries < INT_MAX ? int(table_entries) : INT_MAX;

					lua_pop(g_pLuaState, 1);
*/

					// Getting a specific key
					int l_GameObjectTable = lua_getglobal(g_pLuaState, "GameObject");
					assert(l_GameObjectTable == LUA_TTABLE);

					// Get Name
					lua_pushstring(g_pLuaState, "name");
					// Using stack field 1 as the key, get it's value from the table (in
					// stack field 2) replacing the key in field 1 by the associated value
					int l_nameType = lua_gettable(g_pLuaState, -2); // Player[top of stack after popping] =  Does Player(-2)["name"(Top of Stack)]
					// It should be a string
					assert(l_nameType == LUA_TSTRING);
					// Retrieve the value associated with key "name" as a string, assuming it�s a string
					const char * l_pName = lua_tostring(g_pLuaState, -1);
					// Pop it off the stack now we're done
					lua_pop(g_pLuaState, 1);

					// Get Position
					lua_pushstring(g_pLuaState, "position");
					int l_positionType = lua_gettable(g_pLuaState, -2);
					assert(l_positionType == LUA_TTABLE);
					int l_xType = lua_rawgeti(g_pLuaState, -1, 1);
					int l_yType = lua_rawgeti(g_pLuaState, -2, 2);
					int l_zType = lua_rawgeti(g_pLuaState, -3, 3);
					assert(l_xType == LUA_TNUMBER);
					assert(l_yType == LUA_TNUMBER);
					assert(l_zType == LUA_TNUMBER);
					float l_xValue = static_cast<float>(lua_tonumber(g_pLuaState, -3));
					float l_yValue =static_cast<float>(lua_tonumber(g_pLuaState, -2));
					float l_zValue = static_cast<float>(lua_tonumber(g_pLuaState, -1));
					lua_pop(g_pLuaState, 4);

					// Create Player Game Object and register components with engine
					KPVector3 l_startPosition = KPVector3(l_xValue, l_yValue, 0.0f);
					StrongPointer<GameObject> l_playerObject = new GameObject(l_pName, l_startPosition, 1);
					GameObjectSystem::RegisterGameObject(l_playerObject);


					// Loop through components
					lua_pushstring(g_pLuaState, "components");
					int l_componentsType = lua_gettable(g_pLuaState, -2);
					assert(l_componentsType == LUA_TTABLE);
					lua_pushnil(g_pLuaState);
					while(lua_next(g_pLuaState, -2) != 0)
					{
						assert(lua_type(g_pLuaState, -2) == LUA_TSTRING);
						assert(lua_type(g_pLuaState, -1) == LUA_TTABLE);

						const char* l_key = lua_tostring(g_pLuaState, -2);


						if(strcmp(l_key,"KPRender2DComponent") == 0)
						{
							// Registering Renderer Component
							KPEngine::Graphics::RendererSystem::RegisterSprite(l_playerObject, "Assets\\girl.dds");
						}
						else if (strcmp(l_key,"KPPhysics2DComponent") == 0 )
						{
							// Register Physics Component and passing to controller
							KPEngine::Physics::PhysicsSystem::RegisterPhysicsComponent(l_playerObject);
						}
						else
						{
							assert(false && "UnIdentified Component");
						}

						

						lua_pop(g_pLuaState, 1);
					}

					// TODO For now. Add a Box collision to everything for testing purposes
					Collision::CollisionSystem::RegisterBoxComponent(l_playerObject);

					l_NewStrongPointer = l_playerObject;
				}
				// Determine Game Object, Components, Properties, and stuff from Lua code, and return game object after adding it to the list
				delete[] l_pFileContents;

				return l_NewStrongPointer;
			}

		}
	}

	
}

