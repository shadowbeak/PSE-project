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
#include <cctype>
#include "Device.h"

/**
 * \brief Controleert of een directory bestaat
 * @param dirname De naam van de directory om te controleren
 * @return true als de directory bestaat
 */
bool DirectoryExists(const std::string dirname);

/**
 * \brief Controleert of een bestand bestaat
 * @param dirname De naam van het bestand om te controleren
 * @return true als het bestand bestaat
 */
bool FileExists(const std::string dirname);

/**
 * \brief Controleert of een bestand leeg is
 * @param filename De naam van het bestand om te controleren
 * @return true als het bestand leeg is
 */
bool FileIsEmpty(const std::string filename);

/**
 * \brief Vergelijkt twee bestanden
 * @param leftFileName De naam van het linkerbestand
 * @param rightFileName De naam van het rechterbestand
 * @return true als de bestanden identiek zijn
 */
bool FileCompare(const std::string leftFileName, const std::string rightFileName);

/**
 * \brief Controleert of een string een getal is
 * @param s De string om te controleren
 * @return true als de string een getal is
 */
bool is_number(const std::string& s);

/**
 * \brief Genereert een bestandsnaam
 * @param prefix Het voorvoegsel voor de bestandsnaam
 * @param extension De bestandsextensie
 * @return De gegenereerde bestandsnaam
 */
std::string constructFilename(const std::string& storageDirectory, const std::string& reportExtension, const std::string& name);

bool isInt(const std::string& str);
bool isNegativeInt(const std::string& str);


bool isNotInDevice(Job *job, std::deque<Job*>& jobs);

bool isNegative(int value);

#endif //PSE_PROJECT_PRINTSYSTEMUTILS_H