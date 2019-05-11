#pragma once
#include "../Lua/export/lua.hpp"
#include "../../Core/GameObject/GameObject.h"
#include "../../Utils/SmartPointers.h"


// Documentation to help understand Lua
//http://www.lua.org/manual/5.2/manual.html#4.8
//http://dev.oz-apps.com/?p=331
//https://szpg1108.wordpress.com/2013/08/07/understanding-the-lua-stack-pt-1-the-basics/
//https://stackoverflow.com/questions/23429173/simple-lua-example-of-passing-a-table-to-c-c
namespace KPEngine
{
	namespace Scripting
	{
		namespace Lua
		{
			enum BuiltInComponents
			{
				RENDER_COMPONENT,
				PHYSICS_COMPONENT
			};

			class LuaSystem
			{
			public:
				static void Initialize();
				static void Shutdown();
				static StrongPointer<Core::GameObject> CreateGameObject(const char* i_pScriptFileName, bool i_OverridePosition, KPVector3SSE i_Position);
			private:

				static lua_State* g_pLuaState;
			};


		}
	}

	
}

