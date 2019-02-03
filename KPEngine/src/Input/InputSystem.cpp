
#include "../../include/Input/InputSystem.h"
#include "GLib.h"
#include <stdio.h>
#include "../../include/Utils/KP_Log.h"

namespace KPEngine
{
	namespace Input
	{
		// TODO Having a hard time understanding why I have to do this
		std::unordered_set<KeyCode>* InputSystem::m_pInputHashKeyDown;
		std::unordered_set<KeyCode>* InputSystem::m_pInputHashKeyUp;


		bool InputSystem::GetInputDown(KeyCode i_Key)
		{
			return m_pInputHashKeyDown->count(i_Key);
		}

		bool InputSystem::GetInputUp(KeyCode i_Key)
		{
			return m_pInputHashKeyUp->count(i_Key);
		}

		bool InputSystem::QuitRequested()
		{
			return m_pInputHashKeyUp->count(Q);
		}

		// Core Functions
		bool InputSystem::Initialize()
		{
			GLib::SetKeyStateChangeCallback(InputWindowCallBack);

			m_pInputHashKeyDown = new std::unordered_set<KeyCode>();
			m_pInputHashKeyUp = new std::unordered_set<KeyCode>();

			return true;
		}

		void InputSystem::ReadInput()
		{
			bool bQuit = false;
			GLib::Service(bQuit);
		}

		void InputSystem::ClearInput()
		{
			m_pInputHashKeyDown->clear();
			m_pInputHashKeyUp->clear();
		}

		void InputSystem::Shutdown()
		{
			m_pInputHashKeyDown->clear();
			m_pInputHashKeyUp->clear();

			delete m_pInputHashKeyDown;
			delete m_pInputHashKeyUp;
		}

		void InputSystem::InputWindowCallBack(unsigned i_KeyID, bool i_bWentDown)
		{
//#ifdef _DEBUG
//			const size_t	lenBuffer = 65;
//			char			Buffer[lenBuffer];
//
//			sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_KeyID, i_bWentDown ? "down" : "up");
//			OutputDebugStringA(Buffer);
//#endif // __DEBUG

			// TODO Check for if key is not mapped
			if (i_bWentDown)
				m_pInputHashKeyDown->insert(static_cast<KeyCode>(i_KeyID));
			else
				m_pInputHashKeyUp->insert(static_cast<KeyCode>(i_KeyID));

			//KeyCode l_Key = static_cast<KeyCode>(i_KeyID);
			//DEBUG_PRINT(Utils::Verbose, "Input Code: %i %i", InputSystem::inputCount++,  i_KeyID);

		}
	}
}
