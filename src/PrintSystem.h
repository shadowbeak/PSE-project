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
static const std::string processDirectory = "procesCases/";
static const std::string processFileName = "case_";


class Device;
class Job;



class PrintSystem{
private:
    std::vector<Device *> devices;
    std::vector<Job *> jobs;

public:

    // Constructors en destructor

    /**
	 * \brief Standaardconstructor
	 * \return A new System object
	 */

    PrintSystem();

    /**
	 * \brief Destructor
	 */


    virtual ~PrintSystem();

    /**
     * \brief Leest een printtaak uit een XML-element
     * @param jobElement

     * @require
          - REQUIRE(jobElement != NULL, "JobElement is een null pointer")
     * @ensure
          - ENSURE(!jobs.empty(), "Er werden geen taken gelezen uit ons XML-bestand.")
     */

    // Methoden voor het lezen van gegevens
    void ReadJob(TiXmlElement *jobElement);

    /**
    * \brief Leest een afdrukapparaat uit een XML-element
    *  @param  deviceElement

    * @require
         - REQUIRE(deviceElement != NULL, "DeviceElement is een null pointer")
    * @ensure
         - ENSURE(!devices.empty(), "Er werden geen apparaten gelezen uit ons XML-bestand.")
    */

    void ReadDevice(TiXmlElement *deviceElement);

    /**
     * \brief Leest gegevens uit een bestand
     *  @param filename

     *  @require  REQUIRE(FileExists(filename), "Bestand bestaat niet.")

     */


    void Readfile(const string &filename);

    // Methoden voor het afdrukken en verwerken van taken

    /**
     * \brief Geeft een rapport terug over het systeem
     * \return string met rapport

     */

    std::string printReport() const;

    // getters

    /**
    * \brief Geeft het minst belaste apparaat terug
    * \return pointer naar device

    */

    Device* getLeastBurdened() const;

    /**
    * \brief Geeft het aantal apparaten terug
    * \return vector van pointers naar devices
    */


    const vector<Device *> &getDevices() const;


    /**
    * \brief Geeft het aantal jobs terug
    * \return vector van pointers naar jobs
    */


    const vector<Job *> &getJobs() const;

    /**
    * \brief Geeft de eerste onverwerkte taak terug
    * \return pointer naat job

    * @require
         - REQUIRE(!jobs.empty(), "Geen taken gevonden")

    */

    Job* getNextPendingJob() const;

    /**
     * \brief Wijs een taak toe aan een apparaat
     * @param job
     * \return pointer naar device

     * @require
          -  REQUIRE(!devices.empty(), "Er werden geen apparaten gevonden")
          -  REQUIRE(job->getBeingWorkedOnBy() == NULL, "Er wordt al aan deze taak gewerkt op een ander apparaat.")

     */

    Device* deviceAssignment(Job *job) const;

    /**
     * \brief Wijs alle taken toe

     * @require
          - REQUIRE(!devices.empty(), "Geen apparaten gevonden")
          - REQUIRE(!jobs.empty(), "Geen taken gevonden")

     */

    void assignALL() const;

    /**
    * \brief Verwerk de eerste taak

    * @require
         - REQUIRE(!jobs.empty(), "Geen taken gevonden")
         - REQUIRE(!devices.empty(), "Geen apparaten gevonden")
         - REQUIRE(getNextPendingJob() != NULL, "Alle taken zijn verwerkt")
         - REQUIRE(getNextPendingJob()->getBeingWorkedOnBy() != NULL, "Taak is niet toegewezen aan een apparaat")

    * @ensure
         -     ENSURE(job->isFinished(), "Taak is niet voltooid");
         -     ENSURE(job->getBeingWorkedOnBy()->getJobBurden() != initialBurden, "Apparaat heeft de taak niet verwerkt");


    */

    void processFirstJob() const;

    /**
    * \brief Controleert de printtaken
     * \return boolean
    */

    // Methoden voor het controleren van de consistentie van het systeem
    bool checkJobs()const;

    /**
     * \brief Controleert de afdrukapparaten
     * \return boolean
     */

    bool checkDevices()const;

    /**
     * \brief Controleert het gehele systeem
     * \return boolean
     */
    bool checkSystem()const; 



};






#endif //PSE_PROJECT_PRINTSYSTEM_H
