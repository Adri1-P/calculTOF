#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4Geantino.hh"
#include "G4Gamma.hh"
#include "G4IonTable.hh"

#include "g4root.hh"
#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4SPSAngDistribution.hh"
#include "G4GeneralParticleSource.hh"

#include "BackToBackGenerator.hh"
#include "G4Accumulable.hh"

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public :
	MyPrimaryGenerator();
	~MyPrimaryGenerator();

	virtual void GeneratePrimaries(G4Event*);
  // void setActivities(G4double someActivities[]) {activities = someActivities;}
	// void setSourceID (G4int anID) {sourceID = anID;}
	void setTotalSourceNumber(G4int number) {fTotalSourceNumber = number;}


private :
	G4ParticleGun* fSource;
	G4SPSAngDistribution* angGenerator;
	G4SPSRandomGenerator* biasRndm;
	G4SPSPosDistribution *posGenerator ;
	BackToBackGenerator * BToB = new BackToBackGenerator(fSource,angGenerator,biasRndm,posGenerator);

	G4int fSourceID = 0;
	G4int fTotalSourceNumber;
	G4double *fActivities;
	G4double fTotalActivity = 0;
	// G4ThreeVector position;
};


#endif
