#include "coincidences.hh"
#include <iostream>
#include "TFile.h"
#include <math.h> //pow,acos,sqrt
#include <stdlib.h> //abs

#include "structures.hh"

//********************************************************************************
//********************************************************************************

coincidences::coincidences() {};
coincidences::~coincidences() {delete Coincidences;};

//********************************************************************************

void coincidences::fillTreeCoincidences (TTree * Singles, TFile* outputFile)
{
	//prend un arbre de singles provenant de la fonction fillTreeSingle_b2b (non validé avec d'autres arbres)
	// et écrit automatiquement un fichier de coïncidences.
	// il est possible de changer la fonction d'analyse, mais dans la mesure où elle traite uniquement deux singles.
	// sinon autant faire un copier-coller de cette fonction.


	//variables pour les coincidences
	Double_t time1,time2, dt;
	Float_t energy, energy1, energy2, globalPosX1, globalPosX2, globalPosY1, globalPosY2, globalPosZ1, globalPosZ2;
	Float_t x1, y1, z1, x2, y2, z2;
	Int_t rsectorID1,moduleID1,submoduleID1,crystalID1,layerID1;
	Int_t rsectorID2,moduleID2,submoduleID2,crystalID2,layerID2;
	Double_t sourcePosX1,sourcePosX2,sourcePosY1,sourcePosY2,sourcePosZ1,sourcePosZ2;

	// variables pour les singles
	Float_t globalPosX, globalPosY, globalPosZ,edep;
	Double_t time ;
	Int_t eventID;
	Int_t trackID;
	Int_t coincidence;
  Int_t rsectorID,moduleID,submoduleID,crystalID,layerID;
	Double_t sourcePosX,sourcePosY,sourcePosZ;

	//branches d'intérêt
	TBranch* bglobalPosX;
	TBranch* bglobalPosY;
	TBranch* bglobalPosZ;
	TBranch* beventID;
	TBranch* btrackID;
	TBranch* btime;
	TBranch* bedep;
	TBranch* bcoincidence;
	TBranch* brsectorID;
	TBranch* bmoduleID;
	TBranch* bsubmoduleID;
	TBranch* bcrystalID;
	TBranch* blayerID;
	TBranch* bsourcePosX;
  TBranch* bsourcePosY;
  TBranch* bsourcePosZ;

	// Set branch address
	Singles->SetBranchAddress("globalPosX", &globalPosX, &bglobalPosX); //mm
	Singles->SetBranchAddress("globalPosY", &globalPosY, &bglobalPosY);
	Singles->SetBranchAddress("globalPosZ", &globalPosZ, &bglobalPosZ);
	Singles->SetBranchAddress("trackID", &trackID, &btrackID);
	Singles->SetBranchAddress("eventID", &eventID, &beventID);
	Singles->SetBranchAddress("time", &time, &btime);  //secondes
	Singles->SetBranchAddress("energy", &edep, &bedep); //MeV
	Singles->SetBranchAddress("coincidence", &coincidence, &bcoincidence);
	Singles->SetBranchAddress("rsectorID", &rsectorID, &brsectorID);
	Singles->SetBranchAddress("moduleID", &moduleID, &bmoduleID);
	Singles->SetBranchAddress("submoduleID", &submoduleID, &bsubmoduleID);
	Singles->SetBranchAddress("crystalID", &crystalID, &bcrystalID);
	Singles->SetBranchAddress("layerID", &layerID, &blayerID);
	Singles->SetBranchAddress("sourcePosX", &sourcePosX, &bsourcePosX);
	Singles->SetBranchAddress("sourcePosY", &sourcePosY, &bsourcePosY);
	Singles->SetBranchAddress("sourcePosZ", &sourcePosZ, &bsourcePosZ);
	//initialisation

	this->Coincidences->Branch("globalPosX1",&globalPosX1,"globalPosX/F");
	this->Coincidences->Branch("globalPosY1",&globalPosY1,"globalPosY/F");
	this->Coincidences->Branch("globalPosZ1",&globalPosZ1,"globalPosZ/F");
	this->Coincidences->Branch("time1",&time1,"time/D");
	this->Coincidences->Branch("energy1",&energy1,"energy/F");
	this->Coincidences->Branch("globalPosX2",&globalPosX2,"globalPosX/F");
	this->Coincidences->Branch("globalPosY2",&globalPosY2,"globalPosY/F");
	this->Coincidences->Branch("globalPosZ2",&globalPosZ2,"globalPosZ/F");
	this->Coincidences->Branch("time2",&time2,"time/D");
	this->Coincidences->Branch("energy2",&energy2,"energy/D");
	this->Coincidences->Branch("dt",&dt,"dt/D");
	this->Coincidences->Branch("rsectorID1", &rsectorID1, "rsectorID1/I");
	this->Coincidences->Branch("moduleID1", &moduleID1, "moduleID1/I");
	this->Coincidences->Branch("submoduleID1", &submoduleID1, "submoduleID1/I");
	this->Coincidences->Branch("crystalID1", &crystalID1, "crystalID1/I");
	this->Coincidences->Branch("layerID1", &layerID1, "layerID1/I");
	this->Coincidences->Branch("rsectorID2", &rsectorID2, "rsectorID2/I");
	this->Coincidences->Branch("moduleID2", &moduleID2, "moduleID2/I");
	this->Coincidences->Branch("submoduleID2", &submoduleID2, "submoduleID2/I");
	this->Coincidences->Branch("crystalID2", &crystalID2, "crystalID2/I");
	this->Coincidences->Branch("layerID2", &layerID2, "layerID2/I");
	this->Coincidences->Branch("sourcePosX1", &sourcePosX1, "sourcePosX1/D");
	this->Coincidences->Branch("sourcePosX2", &sourcePosX2, "sourcePosX2/D");
	this->Coincidences->Branch("sourcePosY1", &sourcePosY1, "sourcePosY1/D");
	this->Coincidences->Branch("sourcePosY2", &sourcePosY2, "sourcePosY2/D");
	this->Coincidences->Branch("sourcePosZ1", &sourcePosZ1, "sourcePosZ1/D");
	this->Coincidences->Branch("sourcePosZ2", &sourcePosZ2, "sourcePosZ2/D");
  // Get number of hits in the TTree
  int nS = (int)Singles->GetEntries();
	int i = 0;
	int j = 0;

	// Loop over singles
	while ( i < nS-1 )
	{
		s_Single Single1,Single2;
		s_Coincidence c;
		j = i+1;
		btrackID->GetEntry(i);
		Single1.trackID = trackID; //Single1 n'est pas forcément du track1
		btrackID->GetEntry(j);
		Single2.trackID = trackID;
		beventID->GetEntry(i);
		Single1.eventID = eventID;
		beventID->GetEntry(j);
		Single2.eventID = eventID;
		btime->GetEntry(i);
		Single1.time = time;
		btime->GetEntry(j);
		Single2.time = time;
		bglobalPosY->GetEntry(i);
		Single1.Y = globalPosY;
		bglobalPosY->GetEntry(j);
		Single2.Y = globalPosY;
		bglobalPosX->GetEntry(i);
		Single1.X = globalPosX;
		bglobalPosX->GetEntry(j);
		Single2.X = globalPosX;
		bglobalPosZ->GetEntry(i);
		Single1.Z = globalPosZ;
		bglobalPosZ->GetEntry(j);
		Single2.Z = globalPosZ;
		bedep->GetEntry(i);
		Single1.edep = edep;
		bedep->GetEntry(j);
		Single2.edep = edep;
		brsectorID->GetEntry(i);
		Single1.rsectorID = rsectorID;
		brsectorID->GetEntry(j);
		Single2.rsectorID = rsectorID;
		bmoduleID->GetEntry(i);
		Single1.moduleID = moduleID;
		bmoduleID->GetEntry(j);
		Single2.moduleID = moduleID;
		bsubmoduleID->GetEntry(i);
		Single1.submoduleID = submoduleID;
		bsubmoduleID->GetEntry(j);
		Single2.submoduleID = submoduleID;
		bcrystalID->GetEntry(i);
		Single1.crystalID = crystalID;
		bcrystalID->GetEntry(j);
		Single2.crystalID = crystalID;
		blayerID->GetEntry(i);
		Single1.layerID = layerID;
		blayerID->GetEntry(j);
		Single2.layerID = layerID;
		bsourcePosX->GetEntry(i);
		Single1.sourcePosX = sourcePosX;
		bsourcePosX->GetEntry(j);
		Single2.sourcePosX = sourcePosX;
		bsourcePosY->GetEntry(i);
		Single1.sourcePosY = sourcePosY;
		bsourcePosY->GetEntry(j);
		Single2.sourcePosY = sourcePosY;
		bsourcePosZ->GetEntry(i);
		Single1.sourcePosZ = sourcePosZ;
		bsourcePosZ->GetEntry(j);
		Single2.sourcePosZ = sourcePosZ;


		processTwoSingles(Single1,Single2,c);

		globalPosX1 = c.X1;
		globalPosY1 = c.Y1;
		globalPosZ1 = c.Z1;
		globalPosX2 = c.X2;
		globalPosY2 = c.Y2;
		globalPosZ2 = c.Z2;
		energy1 = c.edep1;
		energy2 = c.edep2;
		time1 = c.time1;
		time2 = c.time2;
		dt = c.dt;
		rsectorID1 = c.rsectorID1;
		moduleID1 = c.moduleID1;
		submoduleID1 = c.submoduleID1;
		crystalID1 = c.crystalID1;
		layerID1 = c.layerID1;
		rsectorID2 = c.rsectorID2;
		moduleID2 = c.moduleID2;
		submoduleID2 = c.submoduleID2;
		crystalID2 = c.crystalID2;
		layerID2 = c.layerID2;
		sourcePosX1 = c.sourcePosX1;
		sourcePosY1 = c.sourcePosY1;
		sourcePosZ1 = c.sourcePosZ1;
		sourcePosX2 = c.sourcePosX2;
		sourcePosY2 = c.sourcePosY2;
		sourcePosZ2 = c.sourcePosZ2;

		if (Single1.isInCoincidence && Single2.isInCoincidence)
		{
			this->Coincidences->Fill();
			i = i + 2;
		}
		else {i++;}
	}

	outputFile->WriteObject(this->Coincidences, "Coincidences");
	Singles->ResetBranchAddresses();
	this->Coincidences->ResetBranchAddresses();
}

//********************************************************************************

void coincidences::processTwoSingles(s_Single &Single1,s_Single &Single2,s_Coincidence &c)
{
	// traite les singles deux par deux et s'ils sont du même event et du bon track considère qu'il y a coincidence.
	// pas de fenêtre ni de considération géométrique.


	Single1.isInCoincidence = false; //présomption de non-coincidence
	Single2.isInCoincidence = false;

	if (Single1.eventID == Single2.eventID)//les deux singles doivent être du même event
	{
		if ((Single1.trackID == 1 && Single2.trackID ==2) ) //deux singles qui se suivent = coincidence
		{
			Single1.isInCoincidence = true;
			Single2.isInCoincidence = true;

			c.time1 = Single1.time;
			c.time2 = Single2.time;
			c.dt = c.time1 - c.time2;
			c.Y1 = Single1.Y;
			c.Y2 = Single2.Y;
			c.X1 = Single1.X;
			c.X2 = Single2.X;
			c.Z1 = Single1.Z;
			c.Z2 = Single2.Z;
			c.edep1 = Single1.edep;
			c.edep2 = Single2.edep;
			c.rsectorID1 = Single1.rsectorID;
			c.moduleID1 = Single1.moduleID;
		  c.submoduleID1 = Single1.submoduleID;
			c.crystalID1 = Single1.crystalID;
			c.layerID1 = Single1.layerID;
			c.rsectorID2 = Single2.rsectorID;
			c.moduleID2 = Single2.moduleID;
			c.submoduleID2 = Single2.submoduleID;
			c.crystalID2 = Single2.crystalID;
			c.layerID2 = Single2.layerID;
			c.sourcePosX1 = Single1.sourcePosX;
			c.sourcePosX2 = Single2.sourcePosX;
			c.sourcePosY1 = Single1.sourcePosY;
			c.sourcePosY2 = Single2.sourcePosY;
			c.sourcePosZ1 = Single1.sourcePosZ;
			c.sourcePosZ2 = Single2.sourcePosZ;
		}
		else if (Single1.trackID == 2 && Single2.trackID == 1) //pareil mais dans l'autre sens. Utile?
		{
			Single1.isInCoincidence = true;
			Single2.isInCoincidence = true;

			c.time1 = Single2.time;
			c.time2 = Single1.time;
			c.dt = c.time1 - c.time2;
			c.Y1 = Single2.Y;
			c.Y2 = Single1.Y;
			c.X1 = Single2.X;
			c.X2 = Single1.X;
			c.Z1 = Single2.Z;
			c.Z2 = Single1.Z;
			c.edep1 = Single2.edep;
			c.edep2 = Single1.edep;
			c.rsectorID1 = Single2.rsectorID;
			c.moduleID1 = Single2.moduleID;
		  c.submoduleID1 = Single2.submoduleID;
			c.crystalID1 = Single2.crystalID;
			c.layerID1 = Single2.layerID;
			c.rsectorID2 = Single1.rsectorID;
			c.moduleID2 = Single1.moduleID;
			c.submoduleID2 = Single1.submoduleID;
			c.crystalID2 = Single1.crystalID;
			c.layerID2 = Single1.layerID;
			c.sourcePosX1 = Single2.sourcePosX;
			c.sourcePosX2 = Single1.sourcePosX;
			c.sourcePosY1 = Single2.sourcePosY;
			c.sourcePosY2 = Single1.sourcePosY;
			c.sourcePosZ1 = Single2.sourcePosZ;
			c.sourcePosZ2 = Single1.sourcePosZ;
		}
	}
}

//********************************************************************************
//********************************************************************************

// void coincidences::writeTree(TTree* treeToWrite,TString filename)
// {
//   TFile* target= new TFile(filename,"recreate");
//   target->WriteObject(treeToWrite, "Coincidences");
//   target->Close();
// }
// Double_t coincidences::distance(Double_t x1,Double_t x2,Double_t y1,Double_t y2,Double_t z1,Double_t z2) //distance entre deux points
// {
// return sqrt(pow(x1-x2,2) + pow(y1-y2,2) + pow(z1-z2,2));
// }
