#pragma once
namespace KPEngine
{
	namespace Utils
	{
		class KPString
		{
		public:

			// Constructors Destructors
			KPString();
			KPString(const char * i_str);
			/*KPString(const KPString &i_kp2);*/
			~KPString();

			// Accessors
			char* Get();
			int length();

			//operators
			KPString& operator+(const KPString & i_other);
			KPString& operator=(const KPString& i_other);


		private:
			char* m_str;
			int m_length;
		};
	}
}


