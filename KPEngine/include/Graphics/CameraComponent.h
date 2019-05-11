#pragma once
#include "../Utils/SmartPointers.h"
#include "../Core/GameObject/GameObject.h"
#include "../Utils/KPMatrix4x4SSE.h"

namespace KPEngine
{
	namespace Graphics
	{
		class CameraComponent
		{
		public:
			CameraComponent(WeakPointer<Core::GameObject> i_GameObject);
			~CameraComponent();

			inline KPMatrix4x4SSE GetCameraTransform() const
			{
				KPMatrix4x4SSE o_TransformationMatrix =  KPMatrix4x4SSE::CreateTranslationMatrix(m_pGameObject.GetStrongPointer()->GetPosition());

				return o_TransformationMatrix;
			}
		private:
			Utils::WeakPointer<Core::GameObject>m_pGameObject;
		};
	}
}
