#include "PrintSystem.h"
#include <iostream>
#include "Device.h"



int main() {
    PrintSystem system;
    system.Readfile("xmlTest/vbPDF.xml");
    system.assignEverything();
    system.processFirstJob();
    std::cout << system.printReport() << std::endl;

    return 0;
}