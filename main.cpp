#include "dds.h"
#include <iostream>

// #define PUSH_DEMO    // Demos Push functionality
// #define POP_DEMO     //Demos POP functionaliyt define PUSH_DEMO or stk_overflow will be thrown

// #define SWAP_DEMO   //Demos Swap and Clear functionality
// #define EMP_DEMO     // Demos Empty function.

//#define GEN_DEMO       // General functionality Demo



int main()
{
    typedef int T;
    register int i;          //iterator
    int stk;                //which stack to use
    int test_size = 101;

    Dynamic_dual_stack<T> *dds;
    dds = new Dynamic_dual_stack<T>(20);

    #ifdef PUSH_DEMO        
    
    for(i=0; i<test_size ;i++){

        if(i%2)
            stk = 1;           //for odd i use stack 1
        else
            stk = 0;          //for even i use stack 0

        dds->push(stk,i*2);   //fill the stacks using even numbers alternating between the stacks 

        std::cout << "Capacity:   " << dds->capacity() << "  |  ";
        std::cout << "Size Total:   "<< dds->size(0) + dds->size(1) << "  |  ";
        std::cout << "Size 0:   " << dds->size(0) << "  |  ";
        std::cout << "Size 1:   " << dds->size(1) << "  |  ";
        std::cout << "Stack:   " << stk << "  |  ";
        std::cout << "Top:   " << dds->top(stk) << std::endl;
       

    }

    #ifdef POP_DEMO

    std::cout << std::endl;
    std::cout << std::endl;
    
    std::cout << "************************************************************************************************************" <<std::endl;
    std::cout << "Popping Stacks ... " << std::endl;
    std::cout << "************************************************************************************************************" <<std::endl;


    for(i=0; i < (test_size - 1) ;i++){

        if(i%2)
            stk = 1;           //for odd i use stack 1
        else
            stk = 0;          //for even i use stack 0

        dds->pop(stk);   //pop the stacks  alternating between the stacks 

        std::cout << "Capacity:   " << dds->capacity() << "  |  ";
        std::cout << "Size Total:   "<< dds->size(0) + dds->size(1) << "  |  ";
        std::cout << "Size 0:   " << dds->size(0) << "  |  ";
        std::cout << "Size 1:   " << dds->size(1) << "  |  ";
        std::cout << "Stack:   " << stk << "  |  ";
        std::cout << "Top:   " << dds->top(stk) << std::endl;
       


    }

    #endif
    #endif

    #ifdef EMP_DEMO

    Dynamic_dual_stack<T> temp(15);

    //operations
    temp.push(1,45);

    temp.push(0,66);
    temp.pop(0);

    bool emp_0 = temp.empty(0);
    bool emp_1 = temp.empty(1);

    if(!emp_0){
        std::cout << "Stack 0 is empty" << std::endl;
    }
    
    if(!emp_1){
        std::cout << "Stack 1 is empty" << std::endl;
    }

    #endif


    #ifdef SWAP_DEMO

    typedef double ty;

    Dynamic_dual_stack<ty> A(20);
    Dynamic_dual_stack<ty> B(30);

    std::cout << "Pushing Even values into A ... " << std::endl;

    for(int i = 0; i < 65 ; i++){
        if(i%2)
            stk = 0;
        else
            stk = 1;
        A.push(stk,i*2);
        
    }

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "==============================" << std::endl;
    std::cout << "A's Info before Swap" << std::endl;
    std::cout << "Total Capacity: " << A.capacity() << std::endl;
    std::cout << "Size 0: " << A.size(0) << std::endl;
    std::cout << "Size 1: " << A.size(1) << std::endl;
    std::cout << "Top 0: " << A.top(0) << std::endl;
    std::cout << "Top 1: " << A.top(1) << std::endl;
    std::cout << "==============================" << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Pushing Odd values into B ... " << std::endl;

      for(int i = 0; i < 80 ; i++){
        if(i%2)
            stk = 0;
        else
            stk = 1;
        B.push(stk,i*2 + 1);
        
    }

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "==============================" << std::endl;
    std::cout << "B's Info before Swap" << std::endl;
    std::cout << "Total Capacity: " << B.capacity() << std::endl;
    std::cout << "Size 0: " << B.size(0) << std::endl;
    std::cout << "Size 1: " << B.size(1) << std::endl;
    std::cout << "Top 0: " << B.top(0) << std::endl;
    std::cout << "Top 1: " << B.top(1) << std::endl;
    std::cout << "==============================" << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Swapping A and B ..." << std::endl;
    A.swap(B);
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "==============================" << std::endl;
    std::cout << "A's Info After Swap" << std::endl;
    std::cout << "Total Capacity: " << A.capacity() << std::endl;
    std::cout << "Size 0: " << A.size(0) << std::endl;
    std::cout << "Size 1: " << A.size(1) << std::endl;
    std::cout << "Top 0: " << A.top(0) << std::endl;
    std::cout << "Top 1: " << A.top(1) << std::endl;
    std::cout << "==============================" << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Popping A ...  " << std::endl;
    for(int i=0; i<79 ; i++){
        if(i%2)
            stk = 0;
        else
            stk = 1;
        std::cout << "Stack:  " << stk <<"|     Popped Val:  " <<A.pop(stk) << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Clearing B ..." << std::endl;

    B.clear();
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "==============================" << std::endl;
    std::cout << "B's Info after clear" << std::endl;
    std::cout << "Total Capacity: " << B.capacity() << std::endl;
    std::cout << "Size 0: " << B.size(0) << std::endl;
    std::cout << "Size 1: " << B.size(1) << std::endl;
    std::cout << "Top 0: " << B.top(0) << std::endl;
    std::cout << "Top 1: " << B.top(1) << std::endl;
    std::cout << "==============================" << std::endl;

    std::cout << "Attempting to Pop ... " << std::endl;
    B.pop(0);


    #endif

    #ifdef GEN_DEMO
    #undef SWAP_DEMO

    typedef double type;

    Dynamic_dual_stack<type> A;

    A.push(0,15.48454);
    std::cout << "Popped out stack 0 :  " << A.pop(0) << std::endl;


    #endif

    return 0;
}
