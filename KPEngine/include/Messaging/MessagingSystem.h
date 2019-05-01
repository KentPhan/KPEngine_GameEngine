#pragma once


namespace KPEngine {
	namespace Utils {
		class KPString;
	}
}

namespace KPEngine
{
	namespace Messaging
	{
		// Class that implements this implements the following method
		class IMessageHandler
		{
		public:
			virtual ~IMessageHandler(){}
			virtual void HandleMessage(const Utils::KPString& i_Message) = 0;
		};


		class MessagingSystem
		{
		public:
			MessagingSystem();
			~MessagingSystem();

		
		};
	}
}


