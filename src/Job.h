#ifndef PSE_PROJECT_JOB_H
#define PSE_PROJECT_JOB_H

#include <iostream>
#include "tinyxml.h"
using namespace std;

class Device;

/**
 * \brief Een klasse die een afdruktaak vertegenwoordigt
 * 
 * Deze klasse bevat informatie over een afdruktaak, zoals het taaknummer, het paginanummer, de gebruikersnaam, enz.
 */
class Job {
private:
    int jobNumber; /**< Het taaknummer */
    int pageCount; /**< Het aantal pagina's */
    string userName; /**< De gebruikersnaam */
    bool finished = false; /**< Geeft aan of de taak is voltooid */
    bool inProcess = false; /**< Geeft aan of de taak wordt verwerkt */
    Device* beingWorkedOnBy = NULL; /**< Het apparaat waaraan de taak wordt toegewezen */

public:
    //constructors en destructor
    Job(int jobNumber, int pageCount, const string &userName); /**< Constructor met parameters */
    explicit Job(TiXmlElement *jobElement); /**< Constructor op basis van XML-elementen */
    virtual ~Job(); /**< Destructor */

    //getters and setters
    int getJobNumber() const; /**< Geeft het taaknummer terug */
    void setJobNumber(int jobNumber); /**< Stelt het taaknummer in */
    int getPageCount() const; /**< Geeft het aantal pagina's terug */
    void setPageCount(int pageCount); /**< Stelt het aantal pagina's in */
    bool isFinished() const; /**< Controleert of de taak is voltooid */
    void setFinished(bool finished); /**< Stelt in of de taak is voltooid */
    bool isInProcess() const; /**< Controleert of de taak wordt verwerkt */
    void setInProcess(bool inProcess); /**< Stelt in of de taak wordt verwerkt */
    const string &getUserName() const; /**< Geeft de gebruikersnaam terug */
    void setUserName(const std::string &userName); /**< Stelt de gebruikersnaam in */
    string EndMessage() const; /**< Geeft een bericht terug dat de voltooiing van de taak aangeeft */

    Device *getBeingWorkedOnBy() const; /**< Geeft het apparaat terug waaraan de taak wordt toegewezen */
    void setBeingWorkedOnBy(Device *beingWorkedOnBy); /**< Stelt het apparaat in waaraan de taak wordt toegewezen */
};

#endif //PSE_PROJECT_JOB_H
