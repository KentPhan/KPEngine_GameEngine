#include "../../include/Utils/KPString.h"
#include <cstring>

namespace KPEngine
{
	namespace Utils
	{
		KPString::KPString()
		{
			m_str = nullptr;
		}

		KPString::KPString(const char* i_str)
		{

			// count size of string
			int length = 0;
			const char* start = i_str;
			while(*(i_str) != '\0')
			{
				length++;
				i_str++;
			}

			m_length = length;
			m_str = new char[m_length + 1];

			// copy string over
			for(int i =0; i < m_length; i++)
			{
				m_str[i] = *(start);
				start++;
			}
			m_str[m_length] = '\0';

		}


		KPString::~KPString()
		{
			delete m_str;
		}

		char* KPString::Get()
		{
			return m_str;
		}

		int KPString::length()
		{
			return m_length;
		}
	}
	
}
