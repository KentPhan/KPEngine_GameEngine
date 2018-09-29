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
		//KPString::KPString(const KPString &i_kp2)
		//{
		//	this = i_kp2;
		//	/*this->m_length = i_kp2.m_length;
		//	char * temp = new char[this->m_length + 1];
		//	strcpy_s(temp, (this->m_length + 1), i_kp2.m_str);
		//	this->m_str = temp;*/
		//}
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
		// TODO May need to handle private variables differently
		// TODO: This does not work and is still a work in progress
		KPString& KPString::operator+(const KPString & i_other)
		{
			// new length
			int newLength = this->m_length + i_other.m_length; 

			// concat new string
			char* newString = new char[newLength + 1];
			newString[0] = '\0';
			strcat_s(newString, (newLength + 1), this->m_str);
			strcat_s(newString, (newLength + 1), i_other.m_str);

			// create new KPString on heap and return
			KPString temp = KPString();
			temp.m_str = newString;
			temp.m_length = strlen(newString);

			//TO DO How do I handle this? Am I supposed to allocate on heap ????? If I do when do I delete????

			return temp;
		}

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
