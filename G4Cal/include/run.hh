#ifndef RUN_HH
#define RUN_HH
#include "G4UserRunAction.hh"
#include "G4Run.hh"

#include "g4root.hh"

#include "G4Accumulable.hh"

class MyRunAction : public G4UserRunAction
{
public :
	MyRunAction();
	~MyRunAction();

	virtual void BeginOfRunAction(const G4Run*);
	virtual void EndOfRunAction(const G4Run*);

	// void CountParticle(){ fParticleCount += 1; };
	// G4int getCount() {return fParticleCount.GetValue();}
	//
	// private :
	// G4Accumulable<G4int>  fParticleCount;

};

#endif
