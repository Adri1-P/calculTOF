#include "generator.hh"

#include "G4AccumulableManager.hh"
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
	for (int i = 0; i < fTotalSourceNumber; i++)
	{
		fTotalActivity = fTotalActivity + fActivities[i]; //activitées cumulées nécessaire pour le calcul des seuils si
																										  //plus de deux sources
	}

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
	//Sa définition a été déportée dans une autre classe pour faciliter le changement de source.
	G4int evtID = anEvent->GetEventID();
	bool straightToX = false;
	G4ThreeVector *pos = new G4ThreeVector(0,0,0);
	// G4double seuil = fActivities[fSourceID];
	//
	// G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
	// auto particleCount = accumulableManager->GetAccumulable<int>("fParticleCount");

  //if (particleCount->GetValue() > seuil) {fSourceID++; seuil = seuil + fActivities[fSourceID];}; //on peut mettre un tirage aléatoire en remplacement
	G4double seuil = fActivities[0] / fTotalActivity;
	fSourceID = G4int(G4UniformRand() < seuil);

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

	// anEvent->getRunAction()->CountParticle();
	// fparticleCount = anEvent->getRunAction()->getCount;
	// G4cout << "ParticleCount : " << particleCount->GetValue() << " " << "fActivities[fSourceID] : " << fActivities[fSourceID] << " " <<"fSourceID : " << fSourceID << G4endl;
	// G4cout << "seuil : " << seuil << G4endl;

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
