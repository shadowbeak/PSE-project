#include "PrintSystem.h"
#include <iostream>
#include "Device.h"



int main() {
    PrintSystem system;
    system.Readfile("xmlTests/NoJobNumber.xml");
    system.assignALL();
    system.processFirstJob();
    std::cout << system.printReport() << std::endl;

    return 0;
}