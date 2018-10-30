#include "pch.h"
#include "MakeSentence.h"
#include <cstdio>
#include <iostream>

namespace InterviewProblems
{	
	void RunMakeSentence(int i_argc, char ** i_argl)
	{
	
		const char * strings[5] = {
			"This",
			"is",
			"a",
			"test",
			NULL
		};

		char * pSentence = MakeSentence(strings);

		printf("The Sentence is: %s", pSentence);

		free(pSentence);

#if defined(_DEBUG)
		_CrtDumpMemoryLeaks();
#endif // _DEBUG
		
	}

	char* MakeSentence(const char* strings[])
	{
		int l_return_string_length = 0;

		// Loop through all possible strings
		int l_string_count = 0;
		while (strings[l_string_count] != nullptr)
		{
			
			// Loop through each string and count characters
			const char*  l_string = strings[l_string_count];
			while(*l_string != '\0')
			{
				l_return_string_length++;// count
				l_string++;// increment loop
			}

			l_return_string_length++;// Account for space character count
			
			l_string_count++;// increment loop
		}

		l_return_string_length++;// Account for terminating string
		char* l_return_string = reinterpret_cast<char*>(malloc(l_return_string_length)); // Allocate exact
		char* l_position_in_return_string = l_return_string;

		// Loop through all possible strings
		l_string_count = 0;
		while (strings[l_string_count] != nullptr)
		{

			// Loop through each string and add characters to return string
			const char*  l_string = strings[l_string_count];
			while (*l_string != '\0')
			{
				*(l_position_in_return_string) = *l_string; // set char
				l_position_in_return_string++; // increment return position

				l_string++; // increment loop
			}

			*(l_position_in_return_string) = ' ';// add space character
			l_position_in_return_string++; // increment return position
				

			l_string_count++;// increment loop
		}

		

		*(l_position_in_return_string) = '\0';
		
		return l_return_string;
	}
}
