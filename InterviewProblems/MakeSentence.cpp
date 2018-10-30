#include "pch.h"
#include "MakeSentence.h"
#include <cstdio>
#include <iostream>
#include <cassert>

namespace InterviewProblems
{	
	void RunMakeSentence(int i_argc, char ** i_argl)
	{
		// list of words
		char * strings[256]; // max 256 words
		int l_word_counts = 0;

		// Get input strings
		printf("Input words to make sentence with. End by just pressing Enter.\n");
		
		// get input until an empty enter is inputed
		char i_name_input[1000];
		while(true)
		{
			char* i_name_input_position = i_name_input; // for storing
			int i_word_length = 0;
			
			// get word input
			while (true)
			{
				const char i_character = std::cin.get();

				if (i_character == '\n') // if encountering end line. end of word
				{
					*(i_name_input_position) = '\0';
					i_word_length++;
					break;
				}

				// store character
				*(i_name_input_position) = i_character;
				i_word_length++;
				i_name_input_position++;
			}

			// if pointer position did not move at all. break;
			if (i_name_input_position == i_name_input)
				break;


			i_name_input_position = i_name_input;
			char* i_word = reinterpret_cast<char*>(malloc(sizeof(char) * i_word_length)); // malloc exact word size
			char* i_word_position = i_word;
			while((*i_name_input_position) != '\0') // loop through word and copy characters
			{
				*(i_word_position) = *i_name_input_position; // copy character

				i_name_input_position++;
				i_word_position++;
			}

			// copy end character
			*i_word_position = *i_name_input_position;
			strings[l_word_counts] = i_word;
			l_word_counts++;
		}
		

		// mark last word as a nullptr
		strings[l_word_counts] = nullptr;

		char * pSentence = MakeSentence(strings);

		printf("The Sentence is: %s", pSentence);

		free(pSentence);

		for(int i = 0; i < l_word_counts; i++)
		{
			free(strings[i]);
		}

#if defined(_DEBUG)
		_CrtDumpMemoryLeaks();
#endif // _DEBUG
		
	}

	char* MakeSentence(char** strings)
	{
		int l_return_string_length = 0;

		// Loop through all possible strings
		int l_string_count = 0;
		while (strings[l_string_count] != nullptr)
		{
			l_return_string_length++;// Account for space character count
			
			// Loop through each string and count characters
			const char*  l_string = strings[l_string_count];
			while(*l_string != '\0')
			{
				l_return_string_length++;// count
				l_string++;// increment loop
			}

			l_string_count++;// increment loop
		}


		l_return_string_length += 2 ;// Account for period and terminating string
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
				
				assert(l_position_in_return_string != nullptr);

				*(l_position_in_return_string) = *l_string; // set char
				l_position_in_return_string++; // increment return position

				l_string++; // increment loop
			}

			*(l_position_in_return_string) = ' ';// add space character
			l_position_in_return_string++; // increment return position
				

			l_string_count++;// increment loop
		}

		

		*(l_position_in_return_string - 1) = '.'; // Replace that last space with a period instead
		*(l_position_in_return_string) = '\0'; // Slap on that terminating string
		
		return l_return_string;
	}
}
