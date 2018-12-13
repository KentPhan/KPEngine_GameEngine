// To Swap between Dynamic and Static Heap Allocators. These have to be commented out and in according to what you want to use

#pragma once

void * __cdecl _malloc(size_t i_size);
void __cdecl _free(void * i_ptr);
void * operator new(size_t i_size);
void operator delete(void * i_ptr);
void * operator new[](size_t i_size);
void operator delete[](void * i_ptr);