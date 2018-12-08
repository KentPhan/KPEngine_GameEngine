#pragma once
namespace KPEngine
{
	namespace Utils
	{
		class KPString
		{
		public:

			// Constructors Destructors
			inline KPString()
			{
				m_str = new char[1];
				m_str[1] = '\0';
			}
			KPString(const char * i_str);
			KPString(const KPString &i_kp2);
			inline ~KPString()
			{
				delete m_str;
			}

			// Accessors
			inline char* Get() const
			{
				return m_str;
			}
			inline int length() const
			{
				return m_length;
			}

			//operators
			KPString operator+(const KPString & i_other) const;
			KPString& operator=(const KPString& i_other);


		private:
			char* m_str;
			int m_length;
		};
	}
}


