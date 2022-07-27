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

	G4bool	straightToX = false; //straightToX à true implique que toutes les particules suivront l'axe des x.
	G4double pos1[3] = {10,0,0}; //si possible, remplacer par un G4ThreeVector un jour
	G4double pos2[3] = {-10,0,0};
	BToB->Shoot(anEvent,straightToX,pos1);
	BToB->Shoot(anEvent,straightToX,pos2);
}
//******************************************************************************
//******************************************************************************
