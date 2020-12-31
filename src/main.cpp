#include "JHNet.h"
#include <iostream>

int main(void){
    CJHNet::GetInstance()->Start();

    std::cout << "Main is ended.";
    return 0;
}