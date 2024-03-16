//============================================================================
// Source      : https://github.com/sergedemeyer/TicTacToe_Git/blob/master/TicTacToeUtils.h
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#ifndef PSE_PROJECT_PRINTSYSTEMUTILS_H
#define PSE_PROJECT_PRINTSYSTEMUTILS_H


#include <iostream>

bool DirectoryExists(const std::string dirname);

bool FileExists(const std::string dirname);

bool FileIsEmpty(const std::string filename);

bool FileCompare(const std::string leftFileName, const std::string rightFileName);

#endif //PSE_PROJECT_PRINTSYSTEMUTILS_H
