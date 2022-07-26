#include "BackToBackGenerator.hh"
#include "G4SPSRandomGenerator.hh"
#include "G4SPSPosDistribution.hh"
#include "G4RandomDirection.hh"

#include "generator.hh"

#include <math.h>

//******************************************************************************
//Cette classe définit une source de BackToBacks.
//Pour d'autres sources, s'en inspirer
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
	// G4ParticleDefinition *particle = particleTable->FindParticle("proton");
  // fSource->SetParticleMomentum(100.*GeV); //default is meV
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

  //Représente le calcul des seuils pour choisir la source aléatoirement, tout en tenant compte des activités de chacune
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

void BackToBackGenerator::ShootOne(G4Event *anEvent,G4ThreeVector *posXYZ,G4ThreeVector *momXYZ)
{
  //fonction de base qui tire deux backToBack par event.

  G4ThreeVector pos;
  if (posXYZ != NULL) {pos = (*posXYZ);}
  else                {G4double rdmPos = (2*G4UniformRand() -1) *20;pos.set(rdmPos,rdmPos,rdmPos);}
  fSource->SetParticlePosition(pos);

  G4ParticleMomentum mom; //G4ParticleMomentum est un typedef de G4ThreeVector
  if (momXYZ != NULL)  {mom = (*momXYZ);}
	else                 //{mom = G4RandomDirection();}
	{G4double rdmMom_y = (2*G4UniformRand() - 1) * 0.18; G4double rdmMom_z = (2*G4UniformRand() - 1) * 0.18;mom.set(1,rdmMom_y,rdmMom_z);}

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
  man->AddNtupleRow(0);
}

void BackToBackGenerator::ShootMultiple(G4Event *anEvent,G4ThreeVector listePos[],char listOfShape[], G4double listOfRadius[], G4double listOfz[])
{
  G4int id = findIndex(fListeSeuils,listePos,0,fTotalSourceNumber-1);
  G4ThreeVector* pos = &listePos[id];
  char shape = listOfShape[id];
  G4double radius = listOfRadius[id];

  if (shape == 'c') //si c'est un cylindre
  {
    G4double z = listOfz[id];
    ShootFromACylinder(anEvent,pos,radius,z);
  }
  else //seules deux formes possibles
  {
    ShootFromASphere(anEvent,pos,radius);
  }
}

void BackToBackGenerator::ShootFromASphere(G4Event* anEvent,G4ThreeVector* centerCoord, G4double radius)
{
	const G4double r = radius*pow(G4UniformRand(),1/3.)*mm; // rayon. Racine cubique pour la dimension trois, je ne sais plus pourquoi

  //vertex 1 uniform on
  G4double alpha = CLHEP::twopi*G4UniformRand();
  G4double beta = 2 * asin(sqrt(2*G4UniformRand() -1)); //inverse de la CDF venant du déterminant d'une jacobienne utilisée pour le passage cartésiennes vers sphérique : https://en.wikibooks.org/wiki/Mathematica/Uniform_Spherical_Distribution
  G4double ux = std::cos(alpha)*std::sin(beta);
  G4double uy = std::sin(alpha)*std::sin(beta);
  G4double uz = std::cos(beta);

  G4ThreeVector pos(r*ux,r*uy,r*uz);
  pos = pos + (*centerCoord);
  ShootOne(anEvent, &pos);
}

void BackToBackGenerator::ShootFromACylinder(G4Event* anEvent, G4ThreeVector* centerCoord, G4double radius,G4double halfz)
{
  //adapted from https://gitlab.cern.ch/geant4/geant4/-/blob/master/examples/extended/eventgenerator/particleGun/src/PrimaryGeneratorAction1.cc
	const G4double r = radius*sqrt(G4UniformRand())*mm; // rayon du cylindre

  //vertex 1 uniform on cylinder
  G4double alpha = CLHEP::twopi*G4UniformRand();  //alpha uniform in (0, 2*pi)
  G4double ux = std::cos(alpha);
  G4double uy = std::sin(alpha);
  G4double z = halfz*(2*G4UniformRand() - 1);

  G4ThreeVector pos(r*ux,r*uy,z);
  pos = pos + (*centerCoord);
  ShootOne(anEvent, &pos);
}

G4int BackToBackGenerator::findIndex(G4double listeSeuils[],G4ThreeVector listePos[], G4int a, G4int b)
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
    if ((a+b)%2) //longueur de l'intervalle impaire
    {
      milieu = (a+b-1)/2;
      seuil = listeSeuils[milieu];

      if (k<seuil) {b = milieu;}
      else     {a = milieu; if (l ==1) {a = b;}}
    }
    else //longueur de l'intervalle paire
    {
      milieu = (a+b)/2;
      seuil = listeSeuils[milieu];

      if (k<seuil) {b = milieu;}
      else     {a = milieu; if (l ==1) {a = b;}}
    }
    l = b-a;
  }

  return a;
}
//******************************************************************************
//******************************************************************************
