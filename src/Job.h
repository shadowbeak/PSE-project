#ifndef PSE_PROJECT_JOB_H
#define PSE_PROJECT_JOB_H

#include <iostream>
#include "tinyxml.h"
using namespace std;

class Device;


class Job {
private:
    int jobNumber;
    int pageCount;
    string userName;
    bool finished = false;
    bool inProcess = false;
    Device* beingWorkedOnBy = NULL;

public:

    /**
     * \Constructor met parameters
     */
    Job(int jobNumber, int pageCount, const string &userName);

    /**
     * \Constructor op basis van XML-elementen
     * @EXPECT
     *  -  EXPECT(!JN_temp.empty(), "Geen jobNumber opgegeven.");
        -  EXPECT(isInt(JN_temp), "JobNumber moet een integer zijn.");
        -  EXPECT(!isNegativeInt(JN_temp), "JobNumber mag niet negatief zijn.");

        -  EXPECT(!PC_temp.empty(), "Geen pageCount opgegeven.");
        -  EXPECT(isInt(PC_temp), "PageCount moet een integer zijn");
        -  EXPECT(!isNegativeInt(PC_temp), "PageCount mag niet negatief zijn.");

        -  EXPECT(!UN_temp.empty(), "Geen userName opgegeven.");
     */
    explicit Job(TiXmlElement *jobElement);

    /**
     * \Destructor
     */
    virtual ~Job();

    /**
     * \Geeft het taaknummer terug
     *  @return int jobnummer
     */
    int getJobNumber() const;

    /**
     * \Stelt het taaknummer in
     */
    void setJobNumber(int jobNumber);

    /**
     * \Geeft het aantal pagina's terug
     */
    int getPageCount() const;

    /**
     * \Stelt het aantal pagina's in
     */
    void setPageCount(int pageCount);

    /**
     * Controleert of de taak is voltooid
     * @require
     *  - Het Job-object moet goed zijn geïnitialiseerd
     * @ensure
     *  - True als de taak is voltooid, anders false
     */
    bool isFinished() const;

    /**
     * \Stelt in of de taak is voltooid
     */
    void setFinished(bool finished);

    /**
     * \Controleert of de taak wordt verwerkt

     */
    bool isInProcess() const;

    /**
     * \Stelt in of de taak wordt verwerkt
     */
    void setInProcess(bool inProcess);

    /**
     * \Geeft de gebruikersnaam terug
     */
    const string &getUserName() const;

    /**
     * \Geeft een bericht terug dat de voltooiing van de taak aangeeft
     * @require
     *    - REQUIRE(getBeingWorkedOnBy() != NULL, "Job is not assigned to a device");
     */
    string EndMessage() const;

    /**
     * \Geeft het apparaat terug waaraan de taak wordt toegewezen

     */
    Device *getBeingWorkedOnBy() const;

    /**
     * \Stelt het apparaat in waaraan de taak wordt toegewezen

     */
    void setBeingWorkedOnBy(Device *beingWorkedOnBy);

};

#endif //PSE_PROJECT_JOB_H
