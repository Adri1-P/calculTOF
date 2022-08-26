#include "BackToBackGenerator.hh"
#include "G4SPSRandomGenerator.hh"
#include "G4SPSPosDistribution.hh"
#include "G4RandomDirection.hh"

#include "generator.hh"

#include <math.h>

//******************************************************************************
//Cette classe définit une source de BackToBacks.
//Pour d'autres sources, s'en inspirer
//Si possible, trouver un moyen pour que la méthode Shoot soit plus flexible.
//******************************************************************************

BackToBackGenerator::BackToBackGenerator(G4ParticleGun* Source)
{
   fSource = Source;
}

//******************************************************************************

BackToBackGenerator::~BackToBackGenerator(){}

//******************************************************************************

void BackToBackGenerator::Prepare()
{
	G4int n_particle = 1;
	fSource = new G4ParticleGun(n_particle);
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition *particle = particleTable->FindParticle("gamma");
  fSource->SetParticleMomentum(511.*keV); //default is meV
	fSource->SetParticleDefinition(particle);
}

//******************************************************************************

void BackToBackGenerator::PrepareMultipleSources(G4int TotalSourceNumber,G4double Activities[])
{
	this->Prepare();
  fTotalSourceNumber = TotalSourceNumber;
  fActivities = Activities;

  fCumulatedActivities = new G4double[fTotalSourceNumber];
  fListeSeuils = new G4double[fTotalSourceNumber];

  for (int i = 0; i <fTotalSourceNumber;i++)
  {
    fTotalActivity = fTotalActivity + fActivities[i];
    fCumulatedActivities[i] = fTotalActivity;
  }
  for (int i = 0; i <fTotalSourceNumber;i++)
  {
    fListeSeuils[i] = fCumulatedActivities[i]/fTotalActivity;
  }
}

void BackToBackGenerator::ShootOne(G4Event *anEvent, G4bool straightToX, G4ThreeVector *posXYZ)
{
	//adapted from https://gitlab.cern.ch/geant4/geant4/-/blob/master/examples/extended/eventgenerator/particleGun/src/PrimaryGeneratorAction1.cc
	const G4double r = 0.0*sqrt(G4UniformRand())*mm; // rayon du cylindre
  const G4double zmax = 0*mm; //0 source ponctuelle  135 source linéaire de 270mm

  //vertex 1 uniform on cylinder
  G4double alpha = CLHEP::twopi*G4UniformRand();  //alpha uniform in (0, 2*pi)
  G4double ux = std::cos(alpha);
  G4double uy = std::sin(alpha);
  G4double z = zmax*(2*G4UniformRand() - 1);  //z uniform in (-zmax, +zmax)

  G4ThreeVector pos; //initialisation obligatoire...
  if(straightToX)          {pos.set(0,0,0);}
  else if (posXYZ != NULL) {pos = (*posXYZ);}
  else                     {pos.set(r*ux,r*uy,z);}

  //end adapted from
  G4ParticleMomentum mom; //G4ParticleMomentum est un typedef de G4ThreeVector
  if (straightToX) {mom.set(1,0,0);}
	else{mom = G4RandomDirection();}

  fSource->SetParticleMomentumDirection(mom);
	fSource->GeneratePrimaryVertex(anEvent);

	fSource->SetParticleMomentumDirection(-mom);
  fSource->GeneratePrimaryVertex(anEvent);

  int i = 0;
  G4AnalysisManager* man = G4AnalysisManager::Instance();

  man->FillNtupleDColumn(0, i, pos.x());
  i++;
  man->FillNtupleDColumn(0, i, pos.y());
  i++;
  man->FillNtupleDColumn(0, i, pos.z());
  i++;
  // man->FillNtupleIColumn(0, i, evtID);
  // i++;
  // // man->FillNtupleIColumn(0, i, fTotalSourceNumber);
  // // i++;
  // // man->FillNtupleIColumn(0, i, fSourceID+1);
  // // i++;
  man->AddNtupleRow(0);
}

void BackToBackGenerator::ShootMultiple(G4Event *anEvent, G4bool straightToX,G4ThreeVector listePos[])
{
G4ThreeVector* fSourcePos = findPosition(fListeSeuils,listePos,0,fTotalSourceNumber-1);
ShootOne(anEvent, straightToX, fSourcePos);
}


G4ThreeVector* BackToBackGenerator::findPosition(G4double listeSeuils[],G4ThreeVector listePos[], G4int a, G4int b)
//une dichotomie (pas en récursif, C++ oblige)
//Trouve la position entre les deux seuils
//décidée par la valeur de k
{


  G4int l = b-a;
  G4int milieu;
  G4double k,seuil;
  k = G4UniformRand();
  while(l >0)
  {
    if (l%2) //longueur de l'intervalle impaire
    {
      milieu = (l-1)/2;
      seuil = listeSeuils[milieu];

      if (k<seuil) {b = milieu;}
      else     {a = milieu+1;}
    }
    else //longueur de l'intervalle paire
    {
      milieu = l/2;
      seuil = listeSeuils[milieu];

      if (k<seuil) {b = milieu;}
      else     {a = milieu+1;}
    }
    l = b-a;
  }
  return &listePos[a];

}
//******************************************************************************
//******************************************************************************
