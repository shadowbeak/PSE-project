#include "PrintSystem.h"
#include <iostream>
#include "Device.h"



int main() {
    PrintSystem system;
    system.Readfile("xmlTests/ReportPrintTest.xml");
    system.assignALL();
    //system.processFirstJob();
    system.printReport();

    return 0;
}