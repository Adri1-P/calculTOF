#include "generator.hh"

#include "G4SPSRandomGenerator.hh"
#include "G4SPSPosDistribution.hh"

//******************************************************************************
//classe appelée pour générer des particules.
//Pour changer de source, créer une classe à part
//en suivant le modèle de BackToBackGenerator.
//******************************************************************************

MyPrimaryGenerator::MyPrimaryGenerator()
{
BToB->Prepare();
}
//******************************************************************************
MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fSource;
	delete angGenerator;
	delete biasRndm;
	delete posGenerator;
}
//******************************************************************************
void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	//Quand on demande un /run/BeamOn c'est cette méthode qui génére les particules.
	//Sa définition a été déportée dans une autre clase pour faciliter le changement de source.
	G4cout << "test" << G4endl;
	G4ThreeVector pos;
	pos.set(0,0,0);
	G4cout << "test" << G4endl;
  fSource->SetParticlePosition(pos); //pbm d'accès au pointeur ici
	G4cout << "test" << G4endl;
  G4ThreeVector mom;
  mom.set(1,0,0);
	fSource->SetParticleMomentumDirection(mom);
	fSource->GeneratePrimaryVertex(anEvent);

  int i = 0;
  G4AnalysisManager* man = G4AnalysisManager::Instance();
  man->FillNtupleDColumn(0, i, pos[0]);
  i++;
  man->FillNtupleDColumn(0, i, pos[1]);
  i++;
  man->FillNtupleDColumn(0, i, pos[2]);
  i++;
  man->AddNtupleRow(0);
	G4cout << "test" << G4endl;
	// G4double pos1[3] = {10,0,0}; //si possible, remplacer par un G4ThreeVector un jour
	// G4double pos2[3] = {-10,0,0};
	// BToB->Shoot(anEvent,straightToX,pos1);
	// BToB->Shoot(anEvent,straightToX,pos2);
}
//******************************************************************************
//******************************************************************************
