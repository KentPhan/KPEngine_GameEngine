#pragma once


namespace KPEngine
{
	namespace Core
	{
		namespace Interfaces
		{
			class IGame
			{
			public:
				virtual void Init() = 0;
				virtual void Update(float i_deltaTime) = 0;
				virtual void Shutdown() = 0;
			};
		}
	}
}
