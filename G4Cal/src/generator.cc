#include "generator.hh"
#include "BackToBackGenerator.hh"

#include "G4RandomDirection.hh"
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
 // BToB->Prepare();
 // G4double listOfActivities[] = {10000, 10000,10000,10000,99999};
 G4double listOfActivities[] = {10000, 10000, 10000, 10000, 10000, 10000, 10000};


 BToB->PrepareMultipleSources(7,listOfActivities);
	// fTotalSourceNumber = 2;
	// fActivities = new G4double[fTotalSourceNumber] {250000, 250000};// dans le run BeamOn mettre la somme des activités
	// for (int i = 0; i < fTotalSourceNumber; i++)
	// {
	// 	fTotalActivity = fTotalActivity + fActivities[i]; //activitées cumulées nécessaire pour le calcul des seuils si
	// 																									  //plus de deux sources
	// }
}
//******************************************************************************
MyPrimaryGenerator::~MyPrimaryGenerator()
{}
//******************************************************************************
void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	//Quand on demande un /run/BeamOn c'est cette méthode qui génére les particules.
	//Sa définition a été déportée dans une autre classe pour faciliter le changement de source.
	// const G4Event * event = G4RunManager::GetRunManager()->GetCurrentEvent();
	// G4int evtID = anEvent->GetEventID();
	bool straightToX = false;
	// G4ThreeVector *pos = new G4ThreeVector(10,0,0);
	// G4double seuil = fActivities[fSourceID];
	//
	// G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
	// auto particleCount = accumulableManager->GetAccumulable<int>("fParticleCount");

  //if (particleCount->GetValue() > seuil) {fSourceID++; seuil = seuil + fActivities[fSourceID];}; //on peut mettre un tirage aléatoire en remplacement
	// G4double seuil = fActivities[0] / fTotalActivity;
	// fSourceID = G4int(G4UniformRand() < seuil);

	// switch (fSourceID)
	// {
	// 	case 0 :
	// 	pos->set(10,0,0);
	// 	break;
	//
	// 	case 1 :
	// 	pos->set(-10,0,0);
	// 	break;
	// }

	// G4ThreeVector pos(10. * mm,0.,0.);
	// BToB->ShootOne(anEvent,straightToX,&pos);
  G4ThreeVector pos1(-50,50,0);
	G4ThreeVector pos2(50,50,0);
	G4ThreeVector pos3(-50,0,0);
	G4ThreeVector pos4(-25,0,0);
  G4ThreeVector pos5(0,0,0);
  G4ThreeVector pos6(25,0,0);
  G4ThreeVector pos7(50,0,0);

	G4ThreeVector listOfPos[] = {pos1, pos2, pos3, pos4, pos5, pos6, pos7};
  char listOfShape[] = {'c','c','s','s','s','s','s'};
  G4double listOfRadius[] = {10,5,10,10,10,10,10};
  G4double listOfz[] = {10,10};
	BToB->ShootMultiple(anEvent, straightToX, listOfPos, listOfShape,  listOfRadius, listOfz);

	// anEvent->getRunAction()->CountParticle();
	// fparticleCount = anEvent->getRunAction()->getCount;
	// G4cout << "ParticleCount : " << particleCount->GetValue() << " " << "fActivities[fSourceID] : " << fActivities[fSourceID] << " " <<"fSourceID : " << fSourceID << G4endl;
	// G4cout << "seuil : " << seuil << G4endl;



}
//******************************************************************************
//******************************************************************************
