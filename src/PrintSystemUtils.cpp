//============================================================================
// Source      : https://github.com/sergedemeyer/TicTacToe_Git/blob/master/TicTacToeUtils.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include <fstream>
#include <sys/stat.h>


#include "PrintSystemUtils.h"
#include <ctime>
#include <iomanip>
#include <sstream>


/**
Auxiliary functions for file manipulation.
*/
bool DirectoryExists(const std::string dirname) {
    struct stat st;
    return stat(dirname.c_str(), &st) == 0;
}

bool FileExists(const std::string filename) {
    struct stat st;
    if (stat(filename.c_str(), &st) != 0) return false;
    std::ifstream f(filename);
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }
}

bool FileIsEmpty(const std::string filename) {
    struct stat st;
    if (stat(filename.c_str(), &st) != 0) return true; // File does not exist; thus it is empty
    return st.st_size == 0;
}

bool FileCompare(const std::string leftFileName, const std::string rightFileName) {
    std::ifstream leftFile, rightFile;
    char leftRead, rightRead;
    bool result;

    // Open the two files.
    leftFile.open(leftFileName);
    if (!leftFile.is_open()) {
        return false;
    };
    rightFile.open(rightFileName);
    if (!rightFile.is_open()) {
        leftFile.close();
        return false;
    };

    result = true; // files exist and are open; assume equality unless a counterexamples shows up.
    while (result && leftFile.good() && rightFile.good()) {
        leftFile.get(leftRead);
        rightFile.get(rightRead);
        result = (leftRead == rightRead);
    };
    if (result) {
        // last read was still equal; are we at the end of both files ?
        result = (!leftFile.good()) && (!rightFile.good());
    };

    leftFile.close();
    rightFile.close();
    return result;
}

bool isInt(const std::string& str) {
    if (str.empty()) {
        return false;
    }

    size_t start = 0;

    if (str[0] == '-') {
        if (str.size() == 1)
            return false;
        start = 1;
    }

    for (size_t i = start; i < str.size(); ++i) {
        if (!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool isNegativeInt(const std::string& str) {


    // Controleer of het eerste teken een min-teken is en de rest cijfers zijn
    if (str[0] == '-') {
        for (size_t i = 1; i < str.size(); ++i) {
            if (!std::isdigit(str[i])) {
                return false;
            }
        }
        // Als er minstens één cijfer na het min-teken is, is het een negatieve integer
        return str.size() > 1;
    }

    return false; // Geen min-teken aan het begin
}


bool isNotInDevice(Job *job, std::deque<Job *>& jobs){
    int job1n = job->getJobNumber();
    for(Job* j: jobs){
        int job2n = j->getJobNumber();
        if(job1n == job2n){
            return false;
        }
    }
    return true;
}

bool isNegative(int value) {
    return value < 0;
}

std::string constructFilename(const std::string& storageDirectory, const std::string& reportExtension, const std::string& name){
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    std::ostringstream oss;
    oss << std::put_time(localTime, "%Y%m%d_%H%M%S");
    std::string datetimeStr = oss.str();

    std::string filename = storageDirectory + name + datetimeStr + reportExtension;
    return filename;

}
