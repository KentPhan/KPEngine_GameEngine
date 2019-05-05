#pragma once
#include <iostream>
using std::cout;
using std::endl;
void inline PrintTestStartLabel(const char* i_Title,const char* i_Label)
{
	printf("%s %s Test: \n", i_Title, i_Label);
}

void inline PrintTestEndLabel(const char* i_Title,const char* i_Label)
{
	printf("%s %s Test Passed \n", i_Title, i_Label);
}
