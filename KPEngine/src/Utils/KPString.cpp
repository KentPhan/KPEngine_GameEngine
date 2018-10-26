#include "../../include/Utils/KPString.h"

#include <cstring>
#include <cassert>

namespace KPEngine
{
	namespace Utils
	{
		// Constructors Destructors
		KPString::KPString(const char* i_str)
		{
			assert(i_str);
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
		KPString::KPString(const KPString &i_kp2)
		{
			this->m_length = i_kp2.m_length;
			char * temp = new char[this->m_length + 1];
			strcpy_s(temp, (this->m_length + 1), i_kp2.m_str);
			this->m_str = temp;
		}

		// Operators
		KPString KPString::operator+(const KPString & i_other)
		{
			// new length
			int newLength = this->m_length + i_other.m_length; 

			// concat new string
			char* tempString = new char[newLength + 1];
			tempString[0] = '\0';
			strcat_s(tempString, (newLength + 1), this->m_str);
			strcat_s(tempString, (newLength + 1), i_other.m_str);

			// create new KPString on heap and return
			KPString tempValue = KPString(tempString);

			delete tempString;

			return tempValue;// Because returning by value, copy constructor will be called first before the destructor of tempValue
		}// destructor of copyConstructed item will be called here if the item has not been stored somewhere

		KPString& KPString::operator=(const KPString& i_other)
		{
			// free up old string
			delete this->m_str;


			this->m_length = i_other.m_length;
			char * temp = new char[this->m_length + 1];
			strcpy_s(temp, (this->m_length + 1), i_other.m_str);
			this->m_str = temp;

			return *this;
		}
	}
	
}
