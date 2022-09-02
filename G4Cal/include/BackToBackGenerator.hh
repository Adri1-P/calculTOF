#ifndef BACKTOBACKGENERATOR_HH
#define BACKTOBACKGENERATOR_HH

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


class BackToBackGenerator
{
public :
BackToBackGenerator(G4ParticleGun* Source);
	~BackToBackGenerator();

	void Prepare();
	void PrepareMultipleSources(G4int TotalSourceNumber,G4double Activities[]);
	void ShootOne(G4Event *anEvent,G4ThreeVector *posXYZ = NULL,G4ThreeVector *momXYZ = NULL);
	void ShootMultiple(G4Event *anEvent,G4ThreeVector listePos[],char listOfShape[], G4double listOfRadius[], G4double listOfz[]);
	G4int findIndex(G4double listeSeuils[], G4ThreeVector listePos[], G4int a, G4int b);
	void ShootFromASphere(G4Event* anEvent, G4ThreeVector* centerCoord, G4double radius);
	void ShootFromACylinder(G4Event* anEvent, G4ThreeVector* centerCoord, G4double radius,G4double halfz);



	// G4ThreeVector* GetListOfPos() {return fPos;}

private :
	G4ParticleGun* fSource;
	G4int fSourceID = 0;
	G4int fTotalSourceNumber;
	G4double *fActivities;
	G4double *fCumulatedActivities;
	G4double *fListeSeuils;
	G4double fTotalActivity = 0;
	// G4ThreeVector* fPos;
};


#endif
