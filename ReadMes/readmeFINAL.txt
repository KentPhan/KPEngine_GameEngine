Final Testing and Important Notes:
- In integrating your unit test and final project into my own. I moved it to my Unit 
Testing Project. TO RUN THE UNIT TEST: THE START UP PROJECT MUST BE SET TO "KPEngine_Test" 
in the solution settings.

- Most of the Heap Allocator Logic can be found in the following folders: 
Assignment\u0734504\KPEngine\include\Core\HeapManager
Assignment\u0734504\KPEngine\src\Core\HeapManager

- All of my debug logs show in output using the log class we made in one of the assignments

- I Integrated your MemorySystem into my project, which can be found in those folders.

- I Still have my old allocator logic in there, but it's commented out to accomidate
for the new logic.

- I did my best to seperate my Dynamic Allocation System and my Fixed Allocation System

- I made SLIGHT modifications to your unit test, but didn't change the underlying
test, I only added additional information to help me debug, and I added some of 
my own tests.

- My Dynamic Allocation system was based upon putting the descriptor right before
the block.

- I wouldn't be surprised if I didn't get some of the Final Specs somehow

-------------------------------------------------------------------------------------
Things I did that stand out:
- I did my best to organize my codebase into structured namespaces and classes
- I added my own BitArray unit tests, which can be found in BitArray_UnitTest
- I added various byte configurations for my Fixed Allocator, found in "KPFixedHeapManager.cpp",
Create function, and a bit into that.
- I added additional BitArray functions to help me found in BitArray.cpp outside of
the spec.
- I added Guard Banding to my Fixed Heap Allocator. Code can be found in "KPFixedHeapManager.cpp"(Like line 81) and "KPFixedHeapManager.h"

-------------------------------------------------------------------------------------
Flaws :
- I Regret this, but I based my original Dynamic Heap Allocator off of using a key value
to try and identify where descriptors were due to alignment. I thought this was optimal. 
This would come back to bite me back in the butt, for there was a chance where 
that key value could actually exist in the data. (How can I improve this? Or do I just have
to loop through the whole list)

- Documentation on BitScanArray was fairly weak. Does BitScanArray always scan 32 bits?
Does BitScanArray64 always scan 64 bits? The documentation made it sound like it did,
but other classmates said otherwise.

- In terms of optimizing my BitArray for 32 bit vs 64 bit. I was a bit unsure of how to
do this. Any tips?

-------------------------------------------------------------------------------------
I would greatly appreciate feedback on how to improve my c++ coding/style/organization
with the current state of the project. Thank You!
(I still am unsure when it comes to identifying speed versus cleanliness)


