#pragma once

//void * __cdecl malloc(size_t i_size);
//void __cdecl free(void * i_ptr);
void * operator new(size_t i_size);
void operator delete(void * i_ptr);
void * operator new[](size_t i_size);
void operator delete[](void * i_ptr);