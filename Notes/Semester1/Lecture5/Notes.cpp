/*
Previous Questions:
My custom string class. Looking at how I make add operator overload, assignment, and copy constructor. I am trying to do something as simple as this x = a + b. I can't figure out how to not have a memory leak

Alignment with 1 byte primatives next to each other don't
break 4 byte alignment rule?

Data structures to use for memory allocator. Keeping track of descriptors and blocks

-----------------------------
Take Proxy Code and replace with your own calls to your own Heap Manager

Your heap manager will replace the one in HEapManagerProxy

neeed to combine abudding blocks back into

Assignemnt:

If you can't handle allocation. Handle gracefully and maybe
return null or something

Need to do block descriptors:
-either do block descriptors seperate
-or in front of allocation block



CPU Cache
- remember application lives in memmory. with stack, heap
program itself
- Main Memory address decompose into tag
- 


Desribe how memory gets into the cache:
Cacheing Algorithms:
-Fully Associative - Has to fully walk through
to find map between main memory and cache
-Direct Mapped - every line maps to a line of cache depending
on its address. address that map to the same point kick each other out
-N Way Set Associative - Lines are broken up into sets
Works better then Direct Mapped

What do I need to get from this:
Keeping data in cache as long as possible with
caching algorithms. Keep most recently used


Memory Characteristics
Triangle
Cheap, Plentiful, Fast


Byte Alignment:
Individual variables need to fall on 4 bye Alignment
(need to align variables in struct, and need to align)
To fix, need to sort 
This results in wasted memory
CANNOT cross byte boundary

Bitfields:
Bool takes 8 bits, you don't need all 8.
So specify 
Can specify bits in structure like so:

*/
unsigned short m_DayOfWeek :3// 3 bits
/*
_declspec lets you align data on lines like so:

*/
_declspec( align(N))// Whereas N can be 64 or however you want crap to align
/*
Prefetching: Allows you to prefetch a line of memory into the cache
based upon an address
Doesn't work as well as it use to, CPU memory controlls have gotten better
at doing this themselves
Like so:
*/
_mm_prefetch(pCurrent->m_pNext, )


// NEED TO UNDERSTAND THAT DATA DATA MOVES FROM
// MAIN MEMMORY INTO CACHE, depending on cache width(32 or 64)
// It grabs that line and puts it in the cache. 
// Kind of treats all memory as a (32 or 64) array
// important in how we design our data structures
// SPACIAL COHERENCE IS IMPORTANT. new and free aren't cheap
// Linked lists suck with spacial coherence
// our data structures should try to be spacially coherent

// ------------------
// Post Questions:
// How long does it take the cpu to check tag

// Go through every block and check if free or not