#include "PrintSystem.h"
#include <iostream>
#include "Device.h"



int main() {
    PrintSystem system;
    system.Readfile("xmlTests/EmissionIsNeg.xml");
    //system.assignALL();
    //std::cout << system.printReport() << std::endl;

    return 0;
}