#ifndef PSE_PROJECT_PRINTSYSTEM_H
#define PSE_PROJECT_PRINTSYSTEM_H

#include <vector>
#include <string>
#include <algorithm>
#include "tinyxml.h"
using namespace std;

static const std::string reportExtension = ".txt";
static const std::string reportDirectory = "reports/";
static const std::string reportFileName = "report_";


static const std::string processExtension = ".txt";
static const std::string processDirectory = "procescases/";
static const std::string processFileName = "proces_";


class Device;
class Job;

/**
 * \brief Een klasse die het afdruksysteem vertegenwoordigt
 * 
 * Dit systeem beheert afdrukapparaten en printtaken.
 */
class PrintSystem{
private:
    std::vector<Device *> devices; /**< Een vector met afdrukapparaten */
    std::vector<Job *> jobs; /**< Een vector met printtaken */

public:
    // Constructors en destructor

    PrintSystem(); 
    /**< Standaardconstructor */

    virtual ~PrintSystem(); 
    /**< Destructor */

    // Methoden voor het lezen van gegevens
    void ReadJob(TiXmlElement *jobElement); 
    /**< Leest een printtaak uit een XML-element */

    void ReadDevice(TiXmlElement *deviceElement); 
    /**< Leest een afdrukapparaat uit een XML-element */

    void Readfile(const string &filename); 
    /**< Leest gegevens uit een bestand */

    // Methoden voor het afdrukken en verwerken van taken
    std::string printReport() const; 
    /**< Geeft een rapport terug over het systeem */

    Device* getLeastBurdened() const; 
    /**< Geeft het minst belaste apparaat terug */

    Device* deviceAssignment(Job *job) const; 
    /**< Wijs een taak toe aan een apparaat */

    void assignALL() const;
    /**< Wijs alle taken toe */

    void processFirstJob() const; 
    /**< Verwerk de eerste taak */

    Job *getNextPendingJob() const;
    /**< Geeft de eerste onverwerkte taak terug */

    // Methoden voor het controleren van de consistentie van het systeem
    bool checkJobs()const; 
    /**< Controleert de printtaken */

    bool checkDevices()const; 
    /**< Controleert de afdrukapparaten */

    bool checkSystem()const; 
    /**< Controleert het gehele systeem */

    const vector<Device *> &getDevices() const;

    const vector<Job *> &getJobs() const;

};






#endif //PSE_PROJECT_PRINTSYSTEM_H
