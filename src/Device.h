#ifndef PSE_PROJECT_DEVICE_H
#define PSE_PROJECT_DEVICE_H

#include <iostream>
#include <vector>
#include "Job.h"
#include <deque>
using namespace std;

// Een klasse die een apparaat voorstelt in het printsysteem

class Device {
private:
    string name; // Naam van het apparaat
    int emission; // Uitstoot van het apparaat
    int speed; // Snelheid van het apparaat
    std::deque<Job *> jobs; // De lijst met taken die momenteel worden verwerkt door het apparaat

public:
    // Constructoren
    Device(const string &name, int emission, int speed, const std::deque<Job *>  &jobs);
    explicit Device(TiXmlElement *device_node);
    virtual ~Device();

    // Getters en setters voor de private leden van de klasse

    
	/**
	 * Constructor voor apparaat
	 * @param naam
	 * @param emissie
	 * @param snelheid
	 */
    const string &getName() const;

    
	/**
	 * Haalt de naam van het apparaat op.
	 * @return
	 */
    void setName(const string &name);

     /**
	 * Geeft de emissie van het apparaat
	 * @return
	 */
    int getEmission() const;

    /**
     * \brief Stelt de emissie van het apparaat in
     * Stelt de emissie van het apparaat in op de opgegeven waarde.
     */
    void setEmission(int emission);

    /**
	 * Geeft de snelheid van het apparaat.
	 * @return
	 */
    int getSpeed() const;

    /**
     * \brief Stelt de snelheid van het apparaat in
     * Stelt de snelheid van het apparaat in op de opgegeven waarde.
     */
    void setSpeed(int speed);

    /**
     * \brief Geeft de taken van het apparaat terug
     * Geeft de taken van het apparaat terug als een const referentie naar een deque van Job-pointers.
     */
    const deque<Job *>  &getJobs() const ;

    /**
     * \brief Stelt de taken van het apparaat in
     * Stelt de taken van het apparaat in op de opgegeven waarde.
     */
    void setJobs(const deque<Job *>  &jobs);

    	/**
	 * Voegt een taak toe aan het apparaat
	 * @require
	    - REQUIRE(properlyInitialized(), "Klasse is niet correct geïnitialiseerd.");
		- REQUIRE(job != NULL, "Job is leeg.");
	 * @ensure
		- ENSURE(jobs.back() == job, "Job is niet toegevoegd aan het apparaat.");
	 */
    void addJob(Job *job); 

    /**
	 * Print een rapport van het apparaat
	 * @require
		- REQUIRE(properlyInitialized(), "Klasse is niet goed geïnitialiseerd.");
		- REQUIRE(emissie >= 0, "Emissie is negatief.");
		- REQUIRE(speed >= 0, "Snelheid is negatief.");
	 * @ensure
		- ENSURE(result != "", "Rapport is leeg.");
	 */
    string printReport() const; 

    /**
     * \brief Verwerkt een taak
     * Verwerkt de eerste taak van het apparaat en retourneert een bericht met het resultaat van de verwerking.
     */
    string processJob(); 

    /**
     * \brief Geeft de belasting van het apparaat terug
     * Geeft de belasting van het apparaat terug als een integer.
     */
    int getJobBurden() const; // Geeft de belasting van het apparaat terug (aantal taken)
};

#endif //PSE_PROJECT_DEVICE_H
