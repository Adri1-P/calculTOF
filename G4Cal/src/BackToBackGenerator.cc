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

BackToBackGenerator::BackToBackGenerator(G4ParticleGun* Source,
  G4SPSAngDistribution* angGen,
  G4SPSRandomGenerator* bias,
  G4SPSPosDistribution *posGen)
{
  //de ces arguments, seul fSource est utile ensuite
  //du moins pour le moment, je garde donc les autres.
   fSource = Source;
	 angGenerator = angGen;
	 biasRndm = bias;
	 posGenerator = posGen;
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

void BackToBackGenerator::Shoot(G4Event *anEvent, G4bool straightToX, G4ThreeVector *posXYZ)
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

  fSource->SetParticlePosition(pos);
  //end adapted from

  G4ThreeVector mom;
  if (straightToX) {mom.set(1,0,0);}
	else{mom = G4RandomDirection();}

	fSource->SetParticleMomentumDirection(mom);
	fSource->GeneratePrimaryVertex(anEvent);

	fSource->SetParticleMomentumDirection(-mom);
  fSource->GeneratePrimaryVertex(anEvent);


}

//******************************************************************************
//******************************************************************************
