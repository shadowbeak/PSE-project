#ifndef PSE_PROJECT_PRINTSYSTEM_H
#define PSE_PROJECT_PRINTSYSTEM_H

#include <vector>
#include <string>
#include <algorithm>
#include "tinyxml.h"
using namespace std;


static const string reportExtension = ".txt";
static const string storageDirectory = "reports/";

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
    std::string log_file_name; /**< De naam van het logbestand */
    bool log = false; /**< Geeft aan of loggen is ingeschakeld */

public:
    // Constructors en destructor
    PrintSystem(const vector<Device *> &devices, const vector<Job *> &jobs); 
    /**< Constructor met parameters */

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

    void assignEverything() const; 
    /**< Wijs alle taken toe */

    void processFirstJob() const; 
    /**< Verwerk de eerste taak */

    Job *getFirstUnprocessedJob() const; 
    /**< Geeft de eerste onverwerkte taak terug */

    // Methoden voor het controleren van de consistentie van het systeem
    bool checkJobs()const; 
    /**< Controleert de printtaken */

    bool checkDevices()const; 
    /**< Controleert de afdrukapparaten */

    bool checkSystem()const; 
    /**< Controleert het gehele systeem */
};










    //void clear();
    //void ReadJob(TiXmlElement *job_element);
    //bool Initialization() const { return _init == this; }
    //Device *getFirstDevice() const;
    //Job *getFirstJob() const;
    //Job *getFirstUnfinishedJob() const;
    //Job *getFirstUnprocessedJob() const;
    //const vector<Device *> &getDevices() const;
    //const vector<Job *> &getJobs() const;
    //vector<Job *> getUnfinishedJobs() const;
    //bool isLogErrors() const;
    //void setLogErrors(bool logErrors);
    //bool VerifyConsistency() const;
    //Device *getDeviceWithLeastLoad() const;
    //void processFirstJob() const;

    //atrribute:
    //static bool CheckNotNegative(int num);
    //PrintSystem* _init;




#endif //PSE_PROJECT_PRINTSYSTEM_H
