#include "JHNet.h"
#include <iostream>

int main(void){
    std::cout << "Application start!\n--------------\n";
    
    CJHNet::GetInstance()->Start();

    std::cout << "\n--------------\nApplication end!\n";
    return 0;
}