#include "../../include/Utils/KPString.h"

#include <cstring>
#include <cassert>

namespace KPEngine
{
	namespace Utils
	{
		// Constructors Destructors
		KPString::KPString()
		{
			m_str = nullptr;
		}
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
		// TODO Define Copy Constructor
		KPString::~KPString()
		{
			delete m_str;
		}


		// Accessors
		char* KPString::Get()
		{
			return m_str;
		}

		int KPString::length()
		{
			return m_length;
		}


		// Operators
		// TODO: This does not work and is still a work in progress
		KPString& KPString::operator+(const KPString& i_other)
		{
			// new length
			int newLength = this->m_length + i_other.m_length;

			// concat new string
			char* newString = new char[newLength + 1];

			/*char* left = this->m_str;
			char* right = i_other.m_str;

			for (int i = 0; i < newLength; i++)
			{
				
				if(left )
				newString[i] = *(start);
				start++;
			}
			newString[newLength] = '\0';*/

			strcat_s(newString, (newLength + 1), this->m_str);
			strcat_s(newString, (newLength + 1), i_other.m_str);


			// remove old one
			delete this->m_str;

			// replace with new one
			this->m_str = newString;

			
			return *this;
		}
	}
	
}
