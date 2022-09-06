#ifndef MYHIT_HH
#define MYHIT_HH

#include "G4VHit.hh"
#include "G4RunManager.hh"
#include "G4Allocator.hh"
#include "G4THitsCollection.hh"

//******************************************************************************
// adapté de basic/B5
//******************************************************************************

class myHit : public G4VHit
{
public:
	myHit();
	virtual ~myHit();

	//obligatoire
	inline void* operator new(size_t);
	inline void  operator delete(void*);
	//

//******************************************************************************
	void fillHitInfo(G4int myhitID,G4int myhitNumberTrack1, G4int myhitNumberTrack2, G4int myhitTrackID,G4int myhitEventID,G4int myhitParentID,
	G4ThreeVector myhitPos,G4ThreeVector myhitSourcePos,
	G4double myhitEdep, G4double myhitTime,
	G4int myhitLayerID,	G4int myhitCrystalID,	G4int myhitSubmoduleID,	G4int myhitModuleID,	G4int myhitRsectorID,
	G4String myhitParticleName);

	G4int gethitID() {return hitID;}
	G4int gethitNumberTrack1() {return hitNumberTrack1;}
	G4int gethitNumberTrack2() {return hitNumberTrack2;}
	G4int gethitTrackID() {return hitTrackID;}
	G4int gethitEventID() {return hitEventID;}
	G4int gethitParentID() {return hitParentID;}

	G4ThreeVector gethitPos() {return hitPos;}
	G4ThreeVector gethitSourcePos() {return hitSourcePos;}

	G4float gethitEdep() {return hitEdep;}
	G4double gethitTime() {return hitTime;}

	G4int gethitLayerID() {return hitLayerID;}
	G4int gethitCrystalID() {return hitCrystalID;}
	G4int gethitSubmoduleID() {return hitSubmoduleID;}
	G4int gethitModuleID() {return hitModuleID;}
	G4int gethitRsectorID() {return hitRsectorID;}

	G4String gethitParticleName() {return hitParticleName;}

	void Print();
	void FillNTuple(char listOfTypes[]= "",int NTupleID= 2,...); //Valeur par défaut à modifier ici si on veut changer le numéro du NTuple des hits dans run.cc
//******************************************************************************
private :

	G4int hitID;
	G4int hitNumberTrack1,hitNumberTrack2;
	G4int hitTrackID;
	G4int hitEventID;
	G4int hitParentID;

	G4ThreeVector hitPos,hitSourcePos;

	G4float hitEdep;
	G4double hitTime;

	G4int hitLayerID;
	G4int hitCrystalID;
	G4int hitSubmoduleID;
	G4int hitModuleID;
	G4int hitRsectorID;

	G4String hitParticleName;
};

//récupéré de https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Detector/hit.html?highlight=hit
// ne me demandez pas comment ça fonctionne.

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

using myHitsCollection = G4THitsCollection<myHit>; // = typedef G4THitsCollection<myHit> myHitsCollection; //alias
extern G4ThreadLocal G4Allocator<myHit>* myHitAllocator;//définition de variable globale dans plusieurs fichiers

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


inline void* myHit::operator new(size_t)
{
  if(!myHitAllocator)
      myHitAllocator = new G4Allocator<myHit>;
  return (void *) myHitAllocator->MallocSingle(); //allocation dynamique de mémoire, cf malloc du C
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void myHit::operator delete(void *hit)
{
  myHitAllocator->FreeSingle((myHit*) hit); //surcharge du destructeur pour libérer la mémoire qu'on a allouée "manuellement"
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
//******************************************************************************
//******************************************************************************
