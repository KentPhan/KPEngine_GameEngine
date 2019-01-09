

//-Header files yes
//-Forward Declare in headers if only referenced by reference speeds up compile time. ()
//-Inputs before outputs in function parameters. Descriptive variable names in function
//-Plain Old Data - types can be optimally passed by value in most cases
//  -Take parameters approprioatly by value
//  -Pass inputs by const reference
//  -Return by value
//-Avoid default values where posible - does not promote readable code
//-Understand copy constructor and assignment operators
//-Explicity disabling copy and assignment by declaring privately/ Can set functions to delete to declare there should not be an implementation for it
//-Header file should bean outward definition
//-Consistent programming style
//  -Formatting
//  -TODO
//  -Exception - Follow any obvious existing programming styles
//  -Prefer spaces over tabs. Really???
//  -Prefer readable code over comments - reafactoring code doesn't always change comments
//  -Compile cleanly at high warning levels. Following them is a general good idea
// - Using const can reference values inst. local variables could be const is good
// - namespaces. google style gide. for new and delete - don't put it in namespace
//      -never ever ever put "using namespace" in header file, NEED TO FIX THIS
// - scoping variables and declaratiosn correctly. Dont' delcare it if you don't initialize it
// - do initializers
// - know your class types
//      -implementation
//      - base class
//      - pure virtual class
Compisition > Inheritance
PRefer writing small classes





Questions:
How about abstract classes?


