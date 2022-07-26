#include "event.hh"
#include  "myHit.hh"

#include "G4SDManager.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
//******************************************************************************
//classe utile si on veut faire quelque chose au niveau de l'event.
//à remplir.
//******************************************************************************
MyEventAction::MyEventAction(MyRunAction*)
{}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event* event)
{}

void MyEventAction::EndOfEventAction(const G4Event* event)
{}

//******************************************************************************
//******************************************************************************
