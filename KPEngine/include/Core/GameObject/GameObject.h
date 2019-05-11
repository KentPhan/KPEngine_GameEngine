#pragma once
#include "../../Utils/KPString.h"
#include "../../Utils/KPVector2.h"
#include "../../Utils/KPVector3SSE.h"
#include "../../Utils/SmartPointers.h"
#include "../../Utils/KPMatrix4x4SSE.h"


using namespace KPEngine::Utils;

namespace KPEngine
{
	namespace Core
	{
		namespace Interfaces
		{
			class IGameObjectController;
		}
	}
	namespace Physics
	{
		class PhysicsComponent;
	}

	namespace Collision
	{
		class BoxCollisionComponent;
	}
}

namespace KPEngine
{
	namespace Core
	{
		class GameObject
		{
		public:

			GameObject(const char* i_Name, const KPVector3SSE i_Position, int tag)
			{
				SetName(i_Name);
				SetPosition(i_Position);
				SetTag(tag);
				m_LocalCS = KPMatrix4x4SSE();
			}

			GameObject(KPString& i_Name, const KPVector3SSE  i_Position, int tag)
			{

				SetName(i_Name);
				SetPosition(i_Position);
				SetTag(tag);
				m_LocalCS = KPMatrix4x4SSE();
			}

			inline void* operator new(size_t i_size)
			{
				return _mm_malloc(i_size, 16);
			}
			inline void operator delete(void * i_p)
			{
				_mm_free(i_p);
			}

			~GameObject() = default;


			// Accessors
			inline KPString GetName() const
			{
				return m_Name;
			}
			inline KPVector3SSE GetPosition() const
			{
				return m_Position;
			}
			inline float GetZRotation() const
			{
				return m_ZRotation;
			}
			inline void PrintInfo() const
			{
				std::cout << "Name: " << m_Name.Get() << "\n";
			}
			inline int GetTag() const
			{
				return m_Tag;
			}
			inline Interfaces::IGameObjectController* GetController() const
			{
				return m_pController;
			}

			StrongPointer<Physics::PhysicsComponent> GetPhysicsComponent() const;
			StrongPointer<Collision::BoxCollisionComponent> GetCollisionComponent() const;
			

			// Setters
			inline KPVector3SSE SetPosition(const KPVector3SSE i_Position)
			{
				m_Position = i_Position;
				return m_Position;
			}
			inline float SetZRotation(float i_ZRotation)
			{
				m_ZRotation = i_ZRotation;
				return m_ZRotation;
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
			void SetController(Interfaces::IGameObjectController* i_pController);
			
			
		private:
			Interfaces::IGameObjectController* m_pController;
			KPVector3SSE m_Position; // World space position
			float m_ZRotation; // Local Space Rotation
			KPString m_Name;
			KPMatrix4x4SSE m_LocalCS; // TODO Don't know what to do with this for now. Maybe store transformation data later on
			
			int m_Tag;
		};
	}
}
