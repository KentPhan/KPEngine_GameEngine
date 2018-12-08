#pragma once
#include "../../Utils/KPString.h"
#include "../../Utils/KPVector2.h"
#include "../../Utils/KPVector3.h"

using namespace KPEngine::Utils;

class IKPGameObjectController;

namespace KPEngine
{
	namespace Core
	{
		class KPGameObject
		{
		public:

			KPGameObject(const char* i_Name, KPVector2 & i_Position, int tag)
			{
				SetName(i_Name);
				SetPosition(i_Position);
				SetTag(tag);
			}

			KPGameObject(KPString& i_Name, KPVector2 & i_Position, int tag)
			{
				SetName(i_Name);
				SetPosition(i_Position);
				SetTag(tag);
			}

			~KPGameObject() = default;


			// Accessors
			inline KPString GetName() const
			{
				return m_Name;
			}
			inline KPVector2 GetPosition() const
			{
				return m_Position;
			}
			inline void PrintInfo() const
			{
				std::cout << "Name: " << m_Name.Get() << "\n";
			}
			inline int GetTag() const
			{
				return m_Tag;
			}
			inline IKPGameObjectController* GetController() const
			{
				return m_pController;
			}
			

			// Setters
			inline KPVector2 SetPosition(KPVector2 & i_Position)
			{
				m_Position = i_Position;
				return m_Position;
			}
			inline KPString SetName(const char* i_Name)
			{
				m_Name = KPString(i_Name);
				return m_Name;
			}
			inline KPString SetName(KPString & i_Name)
			{
				m_Name = i_Name;
				return m_Name;
			}
			inline void SetTag(int tag)
			{
				m_Tag = tag;
			}
			inline void SetController(IKPGameObjectController* i_pController)
			{
				m_pController = i_pController;
			}
			
			
		private:
			KPVector2 m_Position;
			KPString m_Name;
			IKPGameObjectController* m_pController;
			int m_Tag;
		};
	}
}
