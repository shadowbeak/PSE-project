#include "PrintSystem.h"
#include <iostream>



int main() {
    PrintSystem system;
    system.Readfile("xmlTest/vbPDF.xml");
    std::cout << system.printReport() << std::endl;

    return 0;
}