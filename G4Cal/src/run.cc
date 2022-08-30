#include "run.hh"
#include "construction.hh"
#include "G4RunManager.hh"
#include "G4AccumulableManager.hh"


//******************************************************************************
//******************************************************************************

MyRunAction::MyRunAction()
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->SetNtupleMerging(true);

	man->CreateNtuple("Source","Source");
	man->CreateNtupleDColumn("SposX");
	man->CreateNtupleDColumn("SposY");
	man->CreateNtupleDColumn("SposZ");
	man->CreateNtupleIColumn("evtID");
	// man->CreateNtupleIColumn("totalSourceNumber");
	// man->CreateNtupleIColumn("sourceID");
	man->FinishNtuple(0); //numéro du Ntuple

	//prendre le temps de virer ce NTuple et renuméroter les autres.
	man->CreateNtuple("Steps","Steps");
	man->CreateNtupleIColumn("EventID"); //I pour integer
	man->CreateNtupleDColumn("X");
	man->CreateNtupleDColumn("Y");
	man->CreateNtupleDColumn("Z");
	man->CreateNtupleDColumn("GlobalTime");
	man->CreateNtupleSColumn("PreProcessName");
	man->CreateNtupleSColumn("PostProcessName");
	man->CreateNtupleIColumn("trackID");
	man->CreateNtupleDColumn("totalEnergy");
	man->CreateNtupleIColumn("stepNumber");
	man->CreateNtupleIColumn("parentID");
	man->CreateNtupleSColumn("volName");
	man->CreateNtupleIColumn("crystalID");
	man->CreateNtupleDColumn("edep");
	man->FinishNtuple(1);

	//NB : ce NTuple est lié à la classe "Hits"
	//si on change le numéro, il faut aller le changer quand
	//on appelle la méthode fillNTuple avec des arguments
	//et dans tous les cas dans valeur par défaut
	//dans le header myHit.hh
	man->CreateNtuple("Hits", "Hits"); //noms vérifiés comme Gate
	man->CreateNtupleIColumn("hitNumber"); //pas dans Gate
	man->CreateNtupleIColumn("hitNumberTrack1"); //pas dans Gate
	man->CreateNtupleIColumn("hitNumberTrack2"); //pas dans Gate
	man->CreateNtupleIColumn("trackID");
	man->CreateNtupleIColumn("eventID"); //I pour integer
	man->CreateNtupleIColumn("parentID");
	man->CreateNtupleDColumn("posX");
	man->CreateNtupleDColumn("posY");
	man->CreateNtupleDColumn("posZ");
	man->CreateNtupleDColumn("SposX");
	man->CreateNtupleDColumn("SposY");
	man->CreateNtupleDColumn("SposZ");
	man->CreateNtupleDColumn("time");
	man->CreateNtupleDColumn("edep");
	man->CreateNtupleIColumn("layerID");
	man->CreateNtupleIColumn("crystalID");
	man->CreateNtupleIColumn("submoduleID");
	man->CreateNtupleIColumn("moduleID");
	man->CreateNtupleIColumn("rsectorID");
	man->CreateNtupleSColumn("particleName");//pas dans Gate
	man->FinishNtuple(2);

	man->CreateNtuple("Singles", "Singles"); //noms vérifiés comme Gate
	man->CreateNtupleIColumn("eventID"); //I pour integer
	man->CreateNtupleDColumn("globalPosX");
	man->CreateNtupleDColumn("globalPosY");
	man->CreateNtupleDColumn("globalPosZ");
	man->CreateNtupleDColumn("time");
	man->CreateNtupleIColumn("layerID");
	man->CreateNtupleIColumn("crystalID");
	man->CreateNtupleIColumn("submoduleID");
	man->CreateNtupleIColumn("moduleID");
	man->CreateNtupleIColumn("rsectorID");
	man->CreateNtupleDColumn("edep");
	man->FinishNtuple(3);

	man->CreateNtuple("Coincidences", "Coincidences"); //noms vérifiés comme Gate
	man->CreateNtupleIColumn("eventID"); //I pour integer

	man->CreateNtupleDColumn("posX1");
	man->CreateNtupleDColumn("posY1");
	man->CreateNtupleDColumn("posZ1");

	man->CreateNtupleDColumn("posX2");
	man->CreateNtupleDColumn("posY2");
	man->CreateNtupleDColumn("posZ2");

	man->CreateNtupleDColumn("time1");
	man->CreateNtupleDColumn("time2");

	man->CreateNtupleIColumn("layerID1");
	man->CreateNtupleIColumn("crystalID1");
	man->CreateNtupleIColumn("submoduleID1");
	man->CreateNtupleIColumn("moduleID1");
	man->CreateNtupleIColumn("rsectorID1");
	man->CreateNtupleDColumn("edep1");

	man->CreateNtupleIColumn("layerID2");
	man->CreateNtupleIColumn("crystalID2");
	man->CreateNtupleIColumn("submoduleID2");
	man->CreateNtupleIColumn("moduleID2");
	man->CreateNtupleIColumn("rsectorID2");
	man->CreateNtupleDColumn("edep2");

	man->CreateNtupleDColumn("dt");
	man->CreateNtupleDColumn("d");

	man->FinishNtuple(4);
	//cf https://geant4-forum.web.cern.ch/t/usage-of-accumulables/8256 et exemple B3a
	// G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  // accumulableManager->CreateAccumulable<G4int>("fParticleCount", 0);
	// accumulableManager->RegisterAccumulable(fParticleCount);
}

//******************************************************************************

MyRunAction::~MyRunAction(){}

//******************************************************************************

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
	//ici, on ouvre le fichier de sortie

	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->OpenFile("../../../calculTOF_outputs/G4Outputs/test.root");

	// G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
	// accumulableManager->Reset();

}

//******************************************************************************

void MyRunAction::EndOfRunAction(const G4Run*)
{
	//ici, on écrit les NTuples et on ferme le fichier
	G4AnalysisManager *man = G4AnalysisManager::Instance();
// 	G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
// auto particleCount = accumulableManager->GetAccumulable<int>("fParticleCount");
// 	accumulableManager->Merge();
// 	G4cout << "last merge done" << G4endl;
// 		G4cout << "ParticleCount : " << particleCount->GetValue() << G4endl;

	man->Write();
	man->CloseFile();
}
//******************************************************************************
//******************************************************************************
