#include "someprogram.h"
#include <iostream>

using ::tester;

int main()
{
    tester *temp = new tester();
    int hi = temp->addNum();
    delete temp;
    std::cout << hi << std::endl;

    return 0;
}