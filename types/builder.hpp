
/**
*
*   A template builder for implementing a builder pattern on a hierarchy of
*   classes.
*
*   Use to create a hierarchy of builders mirroring the class tree, such that
*   the subclass builders extend the behaviour and code base of the superclass
*   builders, while constructing, amending and validating an instance of the
*   correct subclass on the heap. See example below for an example of use.
*
**/

#pragma once
#if !defined(AAB_TYPES_BUILDER_CLASS)
#define AAB_TYPES_BUILDER_CLASS
#include<exception>
namespace aab	{
namespace types	{

template<typename T>
class Builder
{
    protected:
    
        T * instance;
    
    public:
    
        Builder ()
        {
            instance = new T();
        }
        
        explicit Builder (Builder &other): instance(other.instance)
        {
            other.instance = 0; //copied others instance: it is now invalid
        }
        
        bool hasInstance () const
        {
            return instance != 0;
        }
        
        T * try_release()// throw (std::exception &)
        {
            if (! instance)
            {
                return 0;
            }
            
            if(//!pre_validate() ||
               !instance->validate()// || !post_validate()
               )
            {
                return 0;
            }
            T * releasedInstance = instance;
            instance = 0;
            return releasedInstance;
        }
        
        virtual ~Builder()
        {
            if (instance)
            {
                delete instance;
            }
        }
        
        virtual bool pre_validate() { return true; }
        virtual bool post_validate() { return true; }
};

}		//	types
}		//	aab
#endif	//	AAB_TYPES_BUILDER_CLASS


//example:


/*




*/

/*

// In this example, we have a class A, and a subclass B.
// A has a field a, which must be set up before it is ready for work.
// B has a field b which must also be set up. B also extends A, and so it has a value a as well.
// We want to have builders for A and B, whcih set them up for us.
// In this small example, chaining constructors would be perfect, but in other
// situations where the list of variables to setup is large and unweidly, this
// builder pattern could do much better.

// To use, implement a builder subclass in advance of the class to be built
// Parameterise the builder subclass by a template parameter as below.
// The builder creates an instance of the class on the heap.
//  The builder can have methods to set values of the instance by setting the
//  private fields of the instance.
//  To do this it needs to be a friend of the class (See class A one below)

template<typename T>
class A_builder_T:public aab::types::Builder<T>
{
    public: void setup_a ()
        { this->instance->a = 5; } // must qualify instance with "this"
};




class A
{
    int a;
    
    protected:
    
        A() { };                                // constructor must be protected for B(){} to call
        friend class aab::types::Builder<A>;    // must declare builder as a friend class
        template <typename T> friend class A_builder_T; // must declare this subclasses builder as a friend.
    
        // validate must be implemented - return or throw - user choice
        // It can be protected (recommended)
        virtual bool validate() 
        {
            return 5 == a; // validate can also just throw an excepition.
        }
        
    public:
        
        int get_a()const{ return a; }
        

};

// To invoke a builder of class A:
//      A_builder_T<A> aBuilder;
//      aBuilder.setup_a();
//      A* newA = aBuilder.release();
//      if (! newA)
//      {       // not validated properly
//      ... etc



// Subclasses
// 
// B requires its own builder; to do this, extend the builder of A, and parameterise
// by the same template parameter.
// B then only has to worry about setting up the fields which are unique to B.

template<typename T>
class B_builder_T:public A_builder_T<T>
{
    public: void setup_b ()
        { this->instance->b = 10; } // must qualify instance with "this"
};



class B : public A
{
    int b;
    protected:
    
        B() { };
        friend class aab::types::Builder<B>;
        template <typename T> friend class B_builder_T;
        
        virtual bool validate()
        {
            return 10 == b && A::validate();
        }
    
    public:
        
        int get_b()const{ return b; }

};



int main()
{
    using std::cout;
    using std::endl;
    using std::cin;
    
    B_builder_T<B> b_build;
    
    b_build.setup_b();
    b_build.setup_a();
    
    B* b = b_build.release();
    
    if (b)
    {
        cout << "b is valid" << endl;
    }
    else
    {
        cout << "b is null" << endl;
    }
    
    cin.get();
    
    return 0;
}

*/

