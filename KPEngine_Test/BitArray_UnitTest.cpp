#include <cassert>
#include <Windows.h>
#include <iostream>
#include "Core/HeapManager/BitArray.h"

using KPEngine::Core::HeapManager::Fixed::BitArray;

bool BitArray_UnitTest()
{
	std::cout << "BIT ARRAY TEST:" << std::endl;

	const size_t 		sizeHeap = 1024 * 1024;

	// Allocate memory for my test heap.
	void * pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
	assert(pHeapMemory);

	BitArray* test = BitArray::Create(pHeapMemory, sizeHeap, 52, true);


	std::cout << "Initial State" << std::endl;
	test->PrintBitArray();

	test->SetAll();
	std::cout << "Set All" << std::endl;
	test->PrintBitArray();
	assert(test->AreAllSet());

	test->ClearAll();
	std::cout << "Clear All" << std::endl;
	test->PrintBitArray();
	assert(test->AreAllClear());

	test->SetBit(6);
	test->SetBit(63);
	test->SetBit(1);
	std::cout << "Set Bit 1, 6, 63" << std::endl;
	test->PrintBitArray();
	assert(test->IsBitSet(6));

	test->ClearBit(5);
	test->ClearBit(63);
	test->ClearBit(1);
	std::cout << "Clear Bit 1, 5, 63" << std::endl;
	test->PrintBitArray();
	assert(test->IsBitClear(63));


	size_t l_testNumber = 0;
	assert(test->GetFirstSetBit(l_testNumber));
	assert(l_testNumber == 6);
	std::cout << "Get First Set Bit: "<< l_testNumber << std::endl;
	test->PrintBitArray();

	test->ClearAll();
	assert(test->AreAllClear ());
	test->SetBit(53);
	std::cout << "Clear All with set bit 53" << std::endl;
	test->PrintBitArray();

	size_t l_testNumber3 = 0;
	assert(test->GetFirstSetBit(l_testNumber3));
	assert(l_testNumber3 == 53);
	std::cout << "Get First Set Bit: " << l_testNumber3 << std::endl;
	test->PrintBitArray();

	test->SetAll();
	std::cout << "Set All with clear bit 32" << std::endl;
	assert(test->AreAllSet());
	test->ClearBit(32);
	test->PrintBitArray();
	
	size_t l_testNumber2 = 0;
	assert(test->GetFirstClearBit(l_testNumber2));
	assert(l_testNumber2 == 32);
	std::cout << "Get First Clear Bit: " << l_testNumber2 << std::endl;

	test->SetAll();
	std::cout << "Set All with clear bit 33" << std::endl;
	assert(test->AreAllSet());
	test->ClearBit(33);
	test->PrintBitArray();

	size_t l_testNumber4 = 0;
	assert(test->GetFirstClearBit(l_testNumber4));
	assert(l_testNumber4 == 33);
	std::cout << "Get First Clear Bit: " << l_testNumber4 << std::endl;





	
	

	return true;
}
