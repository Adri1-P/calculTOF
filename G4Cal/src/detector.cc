#include "detector.hh"
#include "construction.hh"
#include "myHit.hh"

#include "G4SDManager.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ios.hh"
#include "g4analysis.hh"
#include "G4EventManager.hh"
#include "G4RunManager.hh"
#include "G4GDMLParser.hh"
#include "G4GeneralParticleSourceData.hh"

#include <math.h>

//******************************************************************************
//******************************************************************************

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name) ,HitsCollection(nullptr), ID(-1)
{
	collectionName.insert("myCollection");
}

//******************************************************************************

MySensitiveDetector::~MySensitiveDetector(){}

//******************************************************************************

void MySensitiveDetector::Initialize(G4HCofThisEvent* hce)
{
	//Cette méthode est appelée au début de l'event.
	//On crée une nouvelle collection associée au détecteur "sensitive detector" défini dans la classe construction
	HitsCollection = new myHitsCollection(SensitiveDetectorName,collectionName[0]);

	if (ID <0) //s'il n'y a pas déjà d'ID, on prend celui courant
	{ID = G4SDManager::GetSDMpointer()->GetCollectionID(HitsCollection); }

	hce->AddHitsCollection(ID,HitsCollection);
}

//******************************************************************************

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *R0hist)
{
	//cette méthode est appelée à chaque hit.
	//Plus il y a de code dedans, plus la simulation sera lente.
	//Elle permet d'accéder aux propriétés des hits.

	//event
	const G4Event * event = G4RunManager::GetRunManager()->GetCurrentEvent();
	G4int evt = event->GetEventID();
	G4GeneralParticleSourceData* G4GPSData = G4GeneralParticleSourceData::Instance();
	G4int sourceID = G4GPSData->GetCurrentSourceIdx();

	//step
	G4Track* track = aStep->GetTrack();
	G4double edep = aStep->GetTotalEnergyDeposit();

	//Track
	G4int trackID = track->GetTrackID();
	G4int stepNumber = track->GetCurrentStepNumber();
	G4int parentID = track->GetParentID();
	G4ParticleDefinition* particle = track->GetDefinition();
	G4String particleName  = particle->GetParticleName();

	//stepPoint
	G4StepPoint* preStepPoint = aStep->GetPreStepPoint(); //arrivée dans le détecteur du photon
	G4StepPoint* postStepPoint = aStep->GetPostStepPoint(); //sortie du détecteur
	G4double localTime = postStepPoint->GetLocalTime();
	G4double properTime = postStepPoint->GetProperTime();
	G4double globalTime = postStepPoint->GetGlobalTime();
	G4double totalEnergy = postStepPoint->GetTotalEnergy();
	G4double kEnergy = postStepPoint->GetKineticEnergy();
	G4ThreeVector posPhoton = postStepPoint->GetPosition();

	//nom du process
	const G4VProcess* PreProcess = preStepPoint->GetProcessDefinedStep();
	G4String prepname = "";
	if (PreProcess) prepname = PreProcess->GetProcessName();
	const G4VProcess* PostProcess = postStepPoint->GetProcessDefinedStep();
	G4String postpname = "";
	if (PostProcess) postpname = PostProcess->GetProcessName(); //utilisé dans Gate


  //  For all processes except transportation, we select the PostStepPoint volume
  //  For the transportation, we select the PreStepPoint volume
  const G4VTouchable* touchable;
   if ( postpname == "Transportation" )
      {touchable = (const G4TouchableHistory*)(preStepPoint->GetTouchable() );}
  else
      {touchable = (const G4TouchableHistory*)(postStepPoint->GetTouchable() );}

	G4VPhysicalVolume* physVol = touchable->GetVolume();
	G4String volName = physVol->GetName();
	//attention, si la structure défini dans construction.cc n'a pas autant d'étage,
	//il va y avoir une seg fault.
	// Pour y remédier, il suffit de mettre à 0 les étages qui n'existent pas.
	G4int layerID = touchable->GetReplicaNumber(0);
	G4int crystalID = touchable->GetReplicaNumber(0);
	G4int submoduleID = touchable->GetReplicaNumber(0);
	G4int moduleID = touchable->GetReplicaNumber(0);
	G4int rsectorID = touchable->GetReplicaNumber(0);



	if (edep <= 0) {return{true};}


	//On a détecté un hit, on lui assigne ses propriétés.
	if (HitsCollection != NULL)
	{
		myHit* hit = new myHit();

		hitNumber++;
	  if (trackID==1) {hitNumberTrack1++;}
	  else if (trackID==2) {hitNumberTrack2++;}

		hit->fillHitInfo(hitNumber,hitNumberTrack1, hitNumberTrack2, trackID, evt,parentID,
		posPhoton,
		edep,globalTime,
		layerID,
		crystalID,
		submoduleID,
		moduleID,
		rsectorID,
	  particleName,
		sourceID);

		//cette fonction s'occupe de remplir le NTuple pour le hits. S'il y a un champ à rajouter, c'est ici.
		//Mais il faut aussi modifier le hit.
		hit->FillNTuple();

		HitsCollection->insert(hit);
	}
	else {	G4cout<< "pbm" << G4endl;}

	return true;
}

//******************************************************************************

void MySensitiveDetector::EndOfEvent(G4HCofThisEvent* hce)
{
	//comme son nom l'indique, cete méthode est appelée à la fin de l'event.
	//c'est à ce moment qu'on accède à la collection de hits de l'event et qu'on la traite.
	G4VHitsCollection* hc = hce->GetHC(0);

	 //fait des coincidences comparables à celles de Gate avec la policy WinnerTakeAll
	ProcessCoincidencesTest("WinnerTakeAll",hc);

	hitNumber = 0;
	hitNumberTrack1 = 0;
	hitNumberTrack2 = 0;
}

//******************************************************************************

void MySensitiveDetector::ProcessCoincidencesTest(G4String policy, G4VHitsCollection* hc)
{
	//fait tous les calculs nécessaires à la formation des singles et coincidences à partir des hits de l'event et remplit les NTuples.
	//plus mis à jour : on fait ça dans un code root
	//si le code root ne marche pas, il faut par contre revenir à cette méthode.

	//declarations
	myHit* hit;
	G4int trackID,eventID;
	G4int layerID1,crystalID1,submoduleID1,moduleID1,rsectorID1,layerID2,crystalID2,submoduleID2,moduleID2,rsectorID2;
	G4double edep;
	G4double time;
	G4double edepMax1;
	G4double edepMax2;
	G4double timeMin1,timeMin2;
	G4double energieTot1, energieTot2;
	G4double X1,Y1,Z1,X2,Y2,Z2;
	G4ThreeVector pos;
	G4bool gamma1;
	G4bool gamma2;
	G4String particleName;

	//Initialisation
	G4int numberOfHits = hc->GetSize();

	edepMax1 = 0;
	edepMax2 = 0;

	energieTot1 = 0;
	energieTot2 = 0;
	X1 = 0;
	Y1 = 0;
	Z1 = 0;

	X2 = 0;
	Y2 = 0;
	Z2 = 0;
	gamma1 = false;
	gamma2 = false;

	//processing des hits, donne idéalement deux singles à la fin de la boucle for
	if (policy == "WinnerTakeAll")
	{
		for (unsigned int j = 0; j < numberOfHits; j++)
		{
			hit = static_cast<myHit*>(hc->GetHit(j));
			trackID = hit->gethitTrackID();
			edep = hit->gethitEdep();
			pos = hit->gethitPos();
			time = hit->gethitTime();
			hitNumberTrack1 = hit->gethitNumberTrack1();
			hitNumberTrack2 = hit->gethitNumberTrack2();
			particleName = hit->gethitParticleName();

			if (particleName == "gamma")
			{
				if (trackID == 1)
				{
					energieTot1 = energieTot1 + edep;

					if (edep > edepMax1) //and the winner is...
					{
						edepMax1 = edep;

						X1 =  pos[0];
						Y1 =  pos[1];
						Z1 =  pos[2];

						layerID1 = hit->gethitLayerID();
						crystalID1 = hit->gethitCrystalID();
						submoduleID1 = hit->gethitSubmoduleID();
						moduleID1 = hit->gethitModuleID();
						rsectorID1 = hit->gethitRsectorID();

						timeMin1 = time; //ce n'est pas vraiment le time min
					}
					gamma1 = true;
				}

				else if (trackID == 2)
				{
					energieTot2 = energieTot2 + edep;

					if (edep > edepMax2)
					{
						edepMax2 = edep;

						X2 =  pos[0];
						Y2 =  pos[1];
						Z2 =  pos[2];

						layerID2 = hit->gethitLayerID();
						crystalID2 = hit->gethitCrystalID();
						submoduleID2 = hit->gethitSubmoduleID();
						moduleID2 = hit->gethitModuleID();
						rsectorID2 = hit->gethitRsectorID();

						timeMin2 = time;
					}
					gamma2 = true;
				}
			}
		}
	}

	eventID = hit->gethitEventID();

	// remplissage singles //
	if(gamma1) //s'il y a un single dans le track 1
	{
	 int i = 0;
	 G4AnalysisManager* man = G4AnalysisManager::Instance();

	 man->FillNtupleIColumn(3, i, eventID);
	 i++;
	 man->FillNtupleDColumn(3, i, X1 / mm);
	 i++;
	 man->FillNtupleDColumn(3, i, Y1 / mm);
	 i++;
	 man->FillNtupleDColumn(3, i, Z1 / mm);
	 i++;
	 man->FillNtupleDColumn(3, i, timeMin1 /ps); //comme l'unité de base est la ns, /ps revient à multiplier par 1000
	 i++;
	 man->FillNtupleIColumn(3, i, layerID1);
	 i++;
	 man->FillNtupleIColumn(3, i, crystalID1);
	 i++;
	 man->FillNtupleIColumn(3, i, submoduleID1);
	 i++;
	 man->FillNtupleIColumn(3, i, moduleID1);
	 i++;
	 man->FillNtupleIColumn(3, i, rsectorID1);
	 i++;
	 man->FillNtupleDColumn(3, i, energieTot1 / MeV);
	 i++;
	 man->AddNtupleRow(3);
	}
	if(gamma2)
	{
	 int i = 0;
	 G4AnalysisManager* man = G4AnalysisManager::Instance();

	 man->FillNtupleIColumn(3, i, eventID);
	 i++;
	 man->FillNtupleDColumn(3, i, X2 / mm);
	 i++;
	 man->FillNtupleDColumn(3, i, Y2 / mm);
	 i++;
	 man->FillNtupleDColumn(3, i, Z2 / mm);
	 i++;
	 man->FillNtupleDColumn(3, i, timeMin2 /ps);
	 i++;
	 man->FillNtupleIColumn(3, i, layerID2);
	 i++;
	 man->FillNtupleIColumn(3, i, crystalID2);
	 i++;
	 man->FillNtupleIColumn(3, i, submoduleID2);
	 i++;
	 man->FillNtupleIColumn(3, i, moduleID2);
	 i++;
	 man->FillNtupleIColumn(3, i, rsectorID2);
	 i++;
	 man->FillNtupleDColumn(3, i, energieTot2 / MeV);
	 i++;
	 man->AddNtupleRow(3);
	}

	G4double dt,d;

	// remplissage coincidences //
	//ça consiste "essentiellement" à mettre deux singles sur une même ligne
	//avec un calcul de d et dt.
	if (gamma1 && gamma2)
	{
		dt = (timeMin1 - timeMin2);
		d = distance(X1,X2,Y1,Y2,Z1,Z2);

		int i = 0;
		G4AnalysisManager* man = G4AnalysisManager::Instance();

		man->FillNtupleIColumn(4, i, eventID);
		i++;

		man->FillNtupleDColumn(4, i, X1 / mm);
		i++;
		man->FillNtupleDColumn(4, i, Y1 / mm);
		i++;
		man->FillNtupleDColumn(4, i, Z1 / mm);
		i++;

		man->FillNtupleDColumn(4, i, X2 / mm);
		i++;
		man->FillNtupleDColumn(4, i, Y2 / mm);
		i++;
		man->FillNtupleDColumn(4, i, Z2 / mm);
		i++;


		man->FillNtupleDColumn(4, i, timeMin1 /ps);
		i++;
		man->FillNtupleDColumn(4, i, timeMin2 /ps);
		i++;

		man->FillNtupleIColumn(4, i, layerID1);
		i++;
		man->FillNtupleIColumn(4, i, crystalID1);
		i++;
		man->FillNtupleIColumn(4, i, submoduleID1);
		i++;
		man->FillNtupleIColumn(4, i, moduleID1);
		i++;
		man->FillNtupleIColumn(4, i, rsectorID1);
		i++;
		man->FillNtupleDColumn(4, i, energieTot1 / MeV);
		i++;

		man->FillNtupleIColumn(4, i, layerID2);
		i++;
		man->FillNtupleIColumn(4, i, crystalID2);
		i++;
		man->FillNtupleIColumn(4, i, submoduleID2);
		i++;
		man->FillNtupleIColumn(4, i, moduleID2);
		i++;
		man->FillNtupleIColumn(4, i, rsectorID2);
		i++;
	  man->FillNtupleDColumn(4, i, energieTot2 / MeV);
		i++;

		man->FillNtupleDColumn(4, i, dt / ps);
		i++;
		man->FillNtupleDColumn(4, i, d / mm);
		i++;

		man->AddNtupleRow(4);
	}
}

//******************************************************************************

G4double MySensitiveDetector::distance(G4double x1,G4double x2,G4double y1,G4double y2,G4double z1,G4double z2)
{
	// une simple distance euclidienne avec deux points en 3D.
	return sqrt(pow(x1-x2,2) + pow(y1-y2,2) + pow(z1-z2,2));
}

//******************************************************************************
//******************************************************************************
