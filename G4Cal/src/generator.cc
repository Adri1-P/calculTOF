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
 G4double listOfActivities[] = {100000, 100000, 100000, 500000};
 BToB->PrepareMultipleSources(4,listOfActivities);
 // BToB->Prepare();

}
//******************************************************************************
MyPrimaryGenerator::~MyPrimaryGenerator()
{}
//******************************************************************************
void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	//Quand on demande un /run/BeamOn c'est la méthode Shoot[...] qui génére les particules.
	//Sa définition a été déportée dans une autre classe pour faciliter le changement de source.
  G4ThreeVector pos1(0,0,0);
	G4ThreeVector pos2(50,0,0);
	G4ThreeVector pos3(61,0,0);
	G4ThreeVector pos4(0,0,0);
  // G4ThreeVector pos5(0,0,0);
  // G4ThreeVector pos6(25,0,0);
  // G4ThreeVector pos7(50,0,0);
  //
	G4ThreeVector listOfPos[] = {pos1, pos2, pos3, pos4};
  char listOfShape[] = {'c','s','s','s'};
  G4double listOfRadius[] = {10,5,5,2};
  G4double listOfz[] = {10};
	BToB->ShootMultiple(anEvent, listOfPos, listOfShape,  listOfRadius, listOfz);
  // G4ThreeVector pos(0,0,0);
  // BToB->ShootOne(anEvent,&pos);
}
//******************************************************************************
//******************************************************************************
