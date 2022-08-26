#include "myHit.hh"

#include <iostream>
#include <cstdarg> //fonctions variadiques

#include "g4analysis.hh"

//******************************************************************************
// Définition de la classe hit, qui provient d'un template situé dans le book
// for application developers de Geant4.
// il a été suivi à la lettre avec quelques ajouts.
//******************************************************************************

G4ThreadLocal G4Allocator<myHit>* myHitAllocator = 0; //? dans le template.

myHit::myHit(){}
myHit::~myHit(){}

//******************************************************************************

void myHit::fillHitInfo(G4int myhitID,G4int myhitNumberTrack1, G4int myhitNumberTrack2, G4int myhitTrackID,G4int myhitEventID,G4int myhitParentID,
												G4ThreeVector myhitPos,
												G4double myhitEdep, G4double myhitTime,
												G4int myhitLayerID, G4int myhitCrystalID,	G4int myhitSubmoduleID, G4int myhitModuleID, G4int myhitRsectorID,
												G4String myhitParticleName,
												G4int myhitSourceID)
{
	//comme son nom l'indique, cette fonction se contente de recopier les propriétés du hit passées en argument dans le hit lui-même.
	hitID = myhitID;
	hitNumberTrack1 = myhitNumberTrack1;
	hitNumberTrack2 = hitNumberTrack2;
	hitTrackID = myhitTrackID;
	hitEventID = myhitEventID;
	hitParentID = myhitParentID;

	hitPos = myhitPos;

	hitEdep = myhitEdep;
	hitTime = myhitTime;

	hitLayerID = myhitLayerID;
	hitCrystalID = myhitCrystalID;
	hitSubmoduleID = myhitSubmoduleID;
	hitModuleID = myhitModuleID;
	hitRsectorID = myhitRsectorID;

	hitParticleName = myhitParticleName;
	hitSourceID = myhitSourceID;
}

//******************************************************************************

void myHit::Print()
{
	//si on veut afficher les propriétés du hit. à remplir.
  G4cout << "test" << G4endl;
}

//******************************************************************************

void myHit::FillNTuple(char listOfTypes[],int NTupleID ,...) //variadic function, see https://en.cppreference.com/w/cpp/utility/variadic for more
{
		//cette méthode rempli le NTuple associé aux hits.
		//Elle n'attend pas d'arguments
		//si on veut ajouter des valeurs qui ne sont pas déjà dans le hit,
		//il faut donner la liste des types des valeurs dans une chaîne de caractères :

		//Exemple :
		// char* listOfTypes = "ds"; //d pour double, s pour string, i pour int. Rien d'autre. Mettre les args dans l'ordre.
		// hit->FillNTuple(listOfTypes,2,kEnergy,postpname);
		//dans l'exemple, il y aura en plus les champs kEnergy et postpname dans le Ntuple
		//du moins si on les a rajoutés dans run.cc

		//N.B. : j'en suis assez fier.

		G4AnalysisManager* man = G4AnalysisManager::Instance();
		int i =0;

		man->FillNtupleIColumn(NTupleID, i, this->gethitID());
		i++;
		man->FillNtupleIColumn(NTupleID, i, this->gethitNumberTrack1());
		i++;
		man->FillNtupleIColumn(NTupleID, i, this->gethitNumberTrack2());
		i++;
		man->FillNtupleIColumn(NTupleID, i, this->gethitTrackID());
		i++;
		man->FillNtupleIColumn(NTupleID, i, this->gethitEventID());
		i++;
		man->FillNtupleIColumn(NTupleID, i, this->gethitParentID());
		i++;
		man->FillNtupleDColumn(NTupleID, i, this->gethitPos()[0]);
		i++;
		man->FillNtupleDColumn(NTupleID, i, this->gethitPos()[1]);
		i++;
		man->FillNtupleDColumn(NTupleID, i, this->gethitPos()[2]);
		i++;
		man->FillNtupleDColumn(NTupleID, i, this->gethitTime());
		i++;
		man->FillNtupleDColumn(NTupleID, i, this->gethitEdep());
		i++;
		man->FillNtupleIColumn(NTupleID, i, this->gethitLayerID());
		i++;
		man->FillNtupleIColumn(NTupleID, i, this->gethitCrystalID());
		i++;
		man->FillNtupleIColumn(NTupleID, i, this->gethitSubmoduleID());
		i++;
		man->FillNtupleIColumn(NTupleID, i, this->gethitModuleID());
		i++;
		man->FillNtupleIColumn(NTupleID, i, this->gethitRsectorID());
		i++;
		man->FillNtupleSColumn(NTupleID, i, this->gethitParticleName());
		i++;
		man->FillNtupleIColumn(NTupleID, i, this->gethitSourceID());
		i++;

		int j=0;
		int vali;
		double vald;
		G4String vals;

		if (listOfTypes[j] != '\0')
		{
			va_list args;  // 	holds the information needed by va_start, va_arg, va_end, and va_copy
			va_start(args, listOfTypes);  //enables access to variadic function arguments
			char currentType;
			currentType = listOfTypes[j];
			while(currentType != '\0')
			{
				switch (currentType)
				{
					case 'i' :
					vali = va_arg(args, int);
					man->FillNtupleIColumn(NTupleID, i, vali);
						break;
					case 'd' :
					vald = va_arg(args, double);
					man->FillNtupleDColumn(NTupleID, i, vald);
						break;
					case 's' :
					vals = va_arg(args, G4String);
					man->FillNtupleSColumn(NTupleID, i, vals);
						break;
				}
				 i++;  //compteur de NTuple
				 j++;  //compteur de type
				 currentType = listOfTypes[j];
			 }
			 va_end(args); //ends traversal of the variadic function arguments
	 	}
		man->AddNtupleRow(NTupleID);
}

//******************************************************************************
//******************************************************************************
