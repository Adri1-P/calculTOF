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
	fTotalSourceNumber = 2;
	fActivities = new G4double[fTotalSourceNumber] {250000, 250000};// dans le run BeamOn mettre la somme des activités
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
	bool straightToX = false;
	G4int evtID = anEvent->GetEventID();
	G4ThreeVector *pos = new G4ThreeVector(0,0,0);
  if (evtID > fActivities[fSourceID]) {fSourceID++;}; //on peut mettre un tirage aléatoire en remplacement

	switch (fSourceID)
	{
		case 0 :
		pos->set(10,0,0);
		break;

		case 1 :
		pos->set(-10,0,0);
		break;
	}
	BToB->Shoot(anEvent,straightToX,pos);


	int i = 0;
  G4AnalysisManager* man = G4AnalysisManager::Instance();

  man->FillNtupleDColumn(0, i, pos->x());
  i++;
  man->FillNtupleDColumn(0, i, pos->y());
  i++;
  man->FillNtupleDColumn(0, i, pos->z());
  i++;
  man->FillNtupleIColumn(0, i, evtID);
  i++;
  man->FillNtupleIColumn(0, i, fTotalSourceNumber);
  i++;
  man->FillNtupleIColumn(0, i, fSourceID+1);
  i++;
  man->AddNtupleRow(0);

}
//******************************************************************************
//******************************************************************************
