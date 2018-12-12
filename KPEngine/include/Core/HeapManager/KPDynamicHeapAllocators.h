//// To Swap between Dynamic and Static Heap Allocators. These have to be commented out and in according to what you want to use
//
//#pragma once
//
//enum dummy_parameter {};
//
//enum KP_Alignment
//{
//	Alignment_4,
//	Alignment_8,
//	Alignment_16,
//	Alignment_32,
//	Alignment_64,a
//};
//
//void * operator new(size_t i_size); // New
//void operator delete(void* i_ptr); // Delete
//void * operator new[](size_t i_size); // New []
//void operator delete[](void* i_ptr); // Delete []
//void * operator new(size_t i_size, dummy_parameter, void * i_ptr); // Placement New
//void * operator new(size_t i_size, KP_Alignment i_alignment); // New Extension
//void operator delete(void* i_ptr, KP_Alignment i_alignment); // Delete Extension
//
