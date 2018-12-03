#pragma once
#include "../../Utils/KPString.h"
#include "../../Utils/KPVector2.h"
#include "../../Utils/KPVector3.h"

using namespace KPEngine::Utils;

namespace KPEngine
{
	namespace Core
	{
		class KPGameObject
		{
		public:

			KPGameObject(){}

			~KPGameObject()
			{
				
			}


			// Accessors
			inline KPString GetName() const
			{
				return m_Name;
			}
			inline KPVector2 GetPosition() const
			{
				return m_Position;
			}
			inline virtual void PrintInfo() const
			{
				std::cout << "Name: " << m_Name.Get() << "\n";
			}
			inline virtual int GetTag() const
			{
				return m_Tag;
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
			inline virtual void SetTag(int tag)
			{
				m_Tag = tag;
			}
			
		private:
			KPVector2 m_Position;
			KPString m_Name;
			int m_Tag;
		};
	}
}
