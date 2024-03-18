#include "PrintSystem.h"
#include <iostream>



int main() {
    PrintSystem system;
    system.Readfile("xmlTest/bigPrint.xml");
    system.assignEverything();
    std::cout << system.printReport() << std::endl;

    return 0;
}