#include "physics.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4SystemOfUnits.hh"
#include "construction.hh"
#include "G4Region.hh"
#include "G4ProductionCuts.hh"
#include "G4EmParameters.hh"
#include "G4RunManager.hh"

//******************************************************************************
//******************************************************************************

MyPhysicsList::MyPhysicsList(){RegisterPhysics (new G4EmStandardPhysics_option3()); /*le cut par défaut est de 1.0mm*/}
MyPhysicsList::~MyPhysicsList(){}

//******************************************************************************

void  MyPhysicsList::SetCuts()
{
	// permet d'appliquer les hits.
	// il y a sans doute des parties redondantes ou inutiles, mais je préfère
	// ne toucher à rien pour le moment.

	// Definition of  threshold of production of secondary particles
	G4Region *region = new G4Region("crystal"); //on crée une région dans laquelle s'appliquent les cuts
	G4ProductionCuts *  cuts(new G4ProductionCuts );
	G4double  defaultProductionCut( 1.0 * mm ); // !!on met une valeur ici mais elle est mise à jour ensuite!!

	const G4VUserPhysicsList *  physicsList(G4RunManager::GetRunManager()->GetUserPhysicsList());
	if ( physicsList ) {defaultProductionCut =physicsList->GetDefaultCutValue();} // on utilise le cut par défaut

	cuts->SetProductionCut(defaultProductionCut); // on donne la valeur du cut à appliquer

	//on applique le cut pour deux particules...
	SetCutValue(defaultProductionCut, "gamma");
	SetCutValue(defaultProductionCut, "e-");
	//...et pour la région
	region->SetProductionCuts( cuts );

	//ici, on dit que la région est en fait un volume logique
	//en l'occurence, ce volume logique est le sensitive detector
	//c'est pourquoi il y a une fonction setScoringVolume dans MetaDetector.hh
	const MyDetectorConstruction * detectorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();
	region->AddRootLogicalVolume( fScoringVolume );


	G4EmParameters *emPar;
	emPar= G4EmParameters::Instance();
	emPar->SetApplyCuts(true); //Pour effectivement appliquer les hits tout le temps : ils ne le sont pas par défaut. Utile ?

	DumpCutValuesTable(); //une simple sortie console des cuts appliqués
}

//******************************************************************************
//******************************************************************************
