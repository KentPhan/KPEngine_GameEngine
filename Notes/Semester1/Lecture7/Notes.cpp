
Look at virtual function example
setting function to 0 makes the function abstract


By having a inheritance with virtual function:
1. For virtual based properties, a pointer is made to a virtual function table where virtual properties are defined
2. If implementations are overrided, from VFT you then go to the individual implementations


Go into settings optimization: Whole program optimization - links files first before compiling


Virtual Functions result in extra cachemisses



Abstract class:
// An abstract class 
class Test 
{    
    // Data members of class 
public: 
    // Pure Virtual Function. Ho

    virtual void show() = 0; 
    
   /* Other members */
}; 


Automatic destructor generated calls destructor for members

virtual destructor problem:
in inheritance, derived class destructors dont get called from base definition unless parent class defines destructor as virtual

if you ever derive from a class, probably should make destructor virtual 

Code is in repository in virtua

