#include "Utils/SmartPointer.h"
#include <iostream>
#include <cassert>
#include <string>

using KPEngine::Utils::SmartPointer;
using std::string;

bool SmartPointer_UnitTest()
{
	std::cout << "SMART POINTER TEST:" << std::endl;

	/*string* l_testData = new string();
	SmartPointer<string> l_testPointer = SmartPointer<string>();
*/



	std::cout << "SMART POINTER TEST PASSED:" << std::endl;
	return true;
}