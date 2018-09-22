#pragma once

namespace KPEngine
{
	namespace Utils
	{
		class KPString
		{
		public:
			KPString();
			KPString(const char * i_str);
			~KPString();
			char* Get();
			int length();
		private:
			char* m_str;
			int m_length;
		};
	}
}


