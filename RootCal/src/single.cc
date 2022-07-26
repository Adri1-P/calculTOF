#include "single.hh"
#include "TTree.h"
#include "TRandom.h"
#include <TMath.h>
#include <iostream>
#include <math.h>
#include "structures.hh"

//********************************************************************************
//********************************************************************************

single::single(TTree* Hits){std::cout << "single::single" << std::endl;}
single::~single(){delete Single; std::cout << "single::~single" << std::endl;}

//********************************************************************************

void single::createTreeSingle(TTree* Hits, TFile* outputFile)
{
 //  entree : arbre de Hits de Geant4, nom du fichier de sortie voulu
 // sachant que le fichier de sortie contiendra des singles.
 //  effet : appelle une fonction de traitement des hits. Pour l'instant il n'y a
 // que des fonctions de triatement des backToBacks, mais le code commenté pourra
 // choisir la bonne fonction selon le nom de fichier de sortie voulu.
 // La fonction appelée écrit automatiquement le fichier de sortie.

  /*const TString pattern = "positron";
  if (filename.Contains(pattern)) {fillTreeSingle_positron(Hits,filename);}
  else if (filename.Contains("v2")) {fillTreeSingle_b2b_v2(Hits,filename);}*/
  fillTreeSingle_b2b(Hits,outputFile);


  std::cout << "single::createTreeSingle" << std:: endl;
}

//********************************************************************************

void single::fillTreeSingle_positron(TTree* Hits, TString filename)
{
//A remplir
std::cout << "single::fillTreeSingle_positron" << std:: endl;
}

//********************************************************************************

void single::fillTreeSingle_b2b(TTree* Hits, TFile* outputFile)
{
  // cette fonction traite les hits selon la policy voulue : winnerTakeAll,centroid ou
  // firstHit, appliquée avec une méthode setPolicyToCentroid, setPolicyToWinnerTakeAll
  // ou setPolicyToFirstHit (à écrire).
  // Elle écrit le fichier de sortie selon le nom passé en argument.
  // Les structures utilisées sont définies dans structure.hh.
  // Elle ne convient que pour des events lançant un backToBack à la fois, parce que
  // la logique n'est basée que sur les deux premiers tracks.


	//variables pour le single
	Double_t energie, energie1, energie2, globalPosX,temps,globalPosY, globalPosZ;
	Int_t STrackID;
	Int_t SeventID;
	Int_t SrsectorID,SmoduleID,SsubmoduleID,ScrystalID,SlayerID;
	Int_t SrsectorID1,SmoduleID1,SsubmoduleID1,ScrystalID1,SlayerID1;
	Int_t SrsectorID2,SmoduleID2,SsubmoduleID2,ScrystalID2,SlayerID2;
	Double_t x1, y1, z1, x2, y2, z2;
  Int_t Scoincidence;

	//define the variable(s) of interest, type of variable must be respected
	Double_t X, Y, Z, time, edep; //edep : pondération (éventuelle) du centroïde
	Int_t eventID;
	Int_t trackID;
  Int_t rsectorID,moduleID,submoduleID,crystalID,layerID;
  Int_t hitNumberTrack1, hitNumberTrack2;
  Char_t particleName; //Char_t* -> seg fault. string : pas le bon type...

	//branches d'intérêt
	TBranch* bX;
	TBranch* bY;
	TBranch* bZ;
	TBranch* beventID;
	TBranch* btrackID;
	TBranch* btime;
	TBranch* bedep;
	TBranch* brsectorID;
	TBranch* bmoduleID;
	TBranch* bsubmoduleID;
	TBranch* bcrystalID;
	TBranch* blayerID;
  TBranch* bhitNumberTrack1;
  TBranch* bhitNumberTrack2;
  TBranch* bparticleName;

	// Set branch address
	Hits->SetBranchAddress("posX", &X, &bX); //on pourrait utiliser les attributs d'un hit directement ? Pas sûr.
	Hits->SetBranchAddress("posY", &Y, &bY);
	Hits->SetBranchAddress("posZ", &Z, &bZ);
	Hits->SetBranchAddress("eventID", &eventID, &beventID);
	Hits->SetBranchAddress("trackID", &trackID, &btrackID);
	Hits->SetBranchAddress("time", &time, &btime);
	Hits->SetBranchAddress("edep", &edep, &bedep);
	Hits->SetBranchAddress("rsectorID", &rsectorID, &brsectorID);
	Hits->SetBranchAddress("moduleID", &moduleID, &bmoduleID);
	Hits->SetBranchAddress("submoduleID", &submoduleID, &bsubmoduleID);
	Hits->SetBranchAddress("crystalID", &crystalID, &bcrystalID);
	Hits->SetBranchAddress("layerID", &layerID, &blayerID);
  Hits->SetBranchAddress("hitNumberTrack1", &hitNumberTrack1, &bhitNumberTrack1);
  Hits->SetBranchAddress("hitNumberTrack2", &hitNumberTrack2, &bhitNumberTrack2);
  Hits->SetBranchAddress("particleName", &particleName, &bparticleName);

	// Get number of hits in the TTree
	int nH = (int)Hits->GetEntries();

	//initialisation
	 this->Single->Branch("globalPosX",&globalPosX,"globalPosX/D");
	 this->Single->Branch("globalPosY",&globalPosY,"globalPosY/D");
	 this->Single->Branch("globalPosZ",&globalPosZ,"globalPosZ/D");
	 this->Single->Branch("time",&temps,"time/D");
	 this->Single->Branch("energy",&energie,"energy/D");
	 this->Single->Branch("trackID",&STrackID,"trackID/I");
	 this->Single->Branch("eventID",&SeventID,"eventID/I");
	 this->Single->Branch("rsectorID",&SrsectorID,"rsectorID/I");
	 this->Single->Branch("moduleID",&SmoduleID,"moduleID/I");
	 this->Single->Branch("submoduleID",&SsubmoduleID,"submoduleID/I");
	 this->Single->Branch("crystalID",&ScrystalID,"crystalID/I");
	 this->Single->Branch("layerID",&SlayerID,"layerID/I");
   this->Single->Branch("coincidence",&Scoincidence,"coincidence/I");

	bool gamma1, gamma2;
	gamma1 = false;
	gamma2 = false;
	int i = 0;
	int currentEvent = 0;
	Double_t energieTot1;
	Double_t energieTot2;
	Double_t temps1;
	Double_t temps2;

	// Loop over hits
	while ( (i < nH) )
	{
		energie1 = 0;
		energie2 = 0;

    btrackID->GetEntry(i);
    beventID->GetEntry(i);
    bX->GetEntry(i);
    bY->GetEntry(i);
    bZ->GetEntry(i);
    bedep->GetEntry(i);
    btime->GetEntry(i);
    brsectorID->GetEntry(i);
    bmoduleID->GetEntry(i);
    bsubmoduleID->GetEntry(i);
    bcrystalID->GetEntry(i);
    blayerID->GetEntry(i);
    bparticleName->GetEntry(i);
    bhitNumberTrack1->GetEntry(i);
    bhitNumberTrack2->GetEntry(i);

    currentEvent = eventID;

    s_Single Single1,Single2; //maximum two singles per event
    Single1.edep = 0;
    Single1.time = time;
    Single1.X = 0;
    Single1.Y = 0;
    Single1.Z = 0;
    Single2.edep = 0;
    Single2.X = 0;
    Single2.Y = 0;
    Single2.Z = 0;
    Single2.time = time;


		while ((i < nH) && (eventID == currentEvent)) //loop over hits of the same event
		{
      s_Hit aHit;
      aHit.X = X;
      aHit.Y = Y;
      aHit.Z = Z;
      aHit.edep = edep;
      aHit.time = time;
      aHit.eventID = eventID;
      aHit.trackID = trackID;
      aHit.rsectorID = rsectorID;
      aHit.moduleID = moduleID;
      aHit.submoduleID = submoduleID;
      aHit.crystalID = crystalID;
      aHit.layerID = layerID;
      aHit.particleName = particleName;
      aHit.hitNumberTrack1 = hitNumberTrack1;
      aHit.hitNumberTrack2 = hitNumberTrack2;

      if(this->policy == "winnerTakeAll")
      {processOneHit_b2b_WTA(aHit,Single1,Single2,energie1,energie2,gamma1,gamma2);}
      else if (this->policy == "centroid")
      {processOneHit_b2b_EWC(aHit,Single1,Single2,gamma1,gamma2);}
      else if (this->policy == "firstHit")
      {processOneHit_b2b_FH(aHit,Single1,Single2,gamma1,gamma2);}

			i++;
      btrackID->GetEntry(i);
			beventID->GetEntry(i);
			bX->GetEntry(i);
			bY->GetEntry(i);
			bZ->GetEntry(i);
			bedep->GetEntry(i);
			btime->GetEntry(i);
			brsectorID->GetEntry(i);
			bmoduleID->GetEntry(i);
			bsubmoduleID->GetEntry(i);
			bcrystalID->GetEntry(i);
			blayerID->GetEntry(i);
      bparticleName->GetEntry(i);
      bhitNumberTrack1->GetEntry(i);
      bhitNumberTrack2->GetEntry(i);
		}

    if (gamma1 && Single1.edep>0)
    {
      globalPosX = Single1.X;
			globalPosY = Single1.Y;
			globalPosZ = Single1.Z;
			temps = Single1.time * 1000; //G4 est en ns par défaut, ici on passe en ps
			energie = Single1.edep;
			STrackID = 1;
			SeventID = eventID;
			SrsectorID = Single1.rsectorID;
			SmoduleID = Single1.moduleID;
			SsubmoduleID = Single1.submoduleID;
			ScrystalID = Single1.crystalID;
			SlayerID = Single1.layerID;
			this->Single->Fill();
    }

    if (gamma2 && Single2.edep>0)
    {
      globalPosX = Single2.X;
			globalPosY = Single2.Y;
			globalPosZ = Single2.Z;
			temps = Single2.time * 1000; //G4 est en ns par défaut, ici on passe en ps
			energie = Single2.edep;
			STrackID = 2;
			SeventID = eventID;
			SrsectorID = Single2.rsectorID;
			SmoduleID = Single2.moduleID;
			SsubmoduleID = Single2.submoduleID;
			ScrystalID = Single2.crystalID;
			SlayerID = Single2.layerID;
			this->Single->Fill();
    }
    gamma1 = false;
    gamma2 = false;
	}

  outputFile->WriteObject(this->Single, "Singles");
	Hits->ResetBranchAddresses();
	this->Single->ResetBranchAddresses();
}

//********************************************************************************

void single::processOneHit_b2b_WTA(s_Hit &aHit, s_Single &Single1,s_Single &Single2, Double_t &energieMax1, Double_t &energieMax2, bool &gamma1, bool &gamma2)
{
  //WTA : WinnerTakeAll : l'énergie du single est la somme de celles des hits.
  //  Sa position est celle du hit ayant déposé le plus d'énergie, idem pour le temps.

  if (aHit.particleName == 'g')
  {
    if (aHit.trackID == 1)
    {
      Single1.edep = Single1.edep + aHit.edep;

      if (energieMax1 < aHit.edep)
      {
        Single1.X = aHit.X;
        Single1.Y = aHit.Y;
        Single1.Z = aHit.Z;
        Single1.rsectorID = aHit.rsectorID;
        Single1.moduleID = aHit.moduleID;
        Single1.submoduleID = aHit.submoduleID;
        Single1.crystalID = aHit.crystalID;
        Single1.layerID = aHit.layerID;
        energieMax1 = aHit.edep;
        Single1.time = aHit.time; //comme dans Gate
      }
      gamma1 = true;
    }

      else if (aHit.trackID == 2)
      {
          Single2.edep = Single2.edep + aHit.edep;

          if (energieMax2 < aHit.edep)
          {
            Single2.X = aHit.X;
            Single2.Y = aHit.Y;
            Single2.Z = aHit.Z;
            Single2.rsectorID = aHit.rsectorID;
            Single2.moduleID = aHit.moduleID;
            Single2.submoduleID = aHit.submoduleID;
            Single2.crystalID = aHit.crystalID;
            Single2.layerID = aHit.layerID;
            energieMax2 = aHit.edep;
            Single2.time = aHit.time; //comme dans Gate
          }
          gamma2 = true;
        }
    }
}

//********************************************************************************

void single::processOneHit_b2b_EWC(s_Hit &aHit, s_Single &Single1,s_Single &Single2,bool &gamma1, bool &gamma2)
{
  //EWC : Energy Weighted Centroid : la position est un barycentre de la position des hits pondéré à leur énergie déposé.
  // le temps est pour l'instant celui du dernier hit.
  // l'énergie est celle de la somme des hits.

   //adapté de GatePulse.cc  méthode CentroidMerge
  Double_t totalEnergy1 = 0;
  Double_t totalEnergy2 = 0;

  if (aHit.particleName == 'g')
  {
    if (aHit.trackID == 1)
    {
      totalEnergy1 = Single1.edep + aHit.edep; //TotalEnergy1 : rang n, Single1.edep : rang n-1

      Single1.X = (Single1.X * Single1.edep + aHit.X * aHit.edep)/ totalEnergy1; // aHit.edep > 0
      Single1.Y = (Single1.Y * Single1.edep + aHit.Y * aHit.edep)/ totalEnergy1;
      Single1.Z = (Single1.Z * Single1.edep + aHit.Z * aHit.edep)/ totalEnergy1;
      Single1.rsectorID = (Single1.rsectorID * Single1.edep + aHit.rsectorID * aHit.edep)/ totalEnergy1;
      Single1.moduleID = (Single1.moduleID * Single1.edep + aHit.moduleID * aHit.edep)/ totalEnergy1;
      Single1.submoduleID = (Single1.submoduleID * Single1.edep + aHit.submoduleID * aHit.edep)/ totalEnergy1;
      Single1.crystalID = (Single1.crystalID * Single1.edep + aHit.crystalID * aHit.edep)/ totalEnergy1;
      Single1.layerID = (Single1.layerID * Single1.edep + aHit.layerID * aHit.edep)/ totalEnergy1;
      Single1.time = aHit.time; //comme dans Gate ?
      Single1.edep = totalEnergy1;
      gamma1 = true;
    }

      else if (aHit.trackID == 2)
      {
          totalEnergy2 = Single2.edep + aHit.edep;

          Single2.X = (Single2.X * Single2.edep + aHit.X * aHit.edep)/ totalEnergy2;
          Single2.Y = (Single2.Y * Single2.edep + aHit.Y * aHit.edep)/ totalEnergy2;
          Single2.Z = (Single2.Z * Single2.edep + aHit.Z * aHit.edep)/ totalEnergy2;
          Single2.rsectorID = (Single2.rsectorID * Single2.edep + aHit.rsectorID * aHit.edep)/ totalEnergy2;
          Single2.moduleID = (Single2.moduleID * Single2.edep + aHit.moduleID * aHit.edep)/ totalEnergy2;
          Single2.submoduleID = (Single2.submoduleID * Single2.edep + aHit.submoduleID * aHit.edep)/ totalEnergy2;
          Single2.crystalID = (Single2.crystalID * Single2.edep + aHit.crystalID * aHit.edep)/ totalEnergy2;
          Single2.layerID = (Single2.layerID * Single2.edep + aHit.layerID * aHit.edep)/ totalEnergy2;
          Single2.time = aHit.time; //comme dans Gate ?
          Single2.edep = totalEnergy2;
          gamma2 = true;
        }
    }
}

//********************************************************************************

void single::processOneHit_b2b_FH(s_Hit &aHit,s_Single &Single1,s_Single &Single2,bool &gamma1,bool &gamma2)
{
  //FH : First Hit : toutes les infos sont celles du premier hit, sauf l'énergie qui est celle de la somme de tous les hits.

  if (aHit.particleName == 'g')
  {
    if (aHit.trackID == 1)
    {
      Single1.edep = Single1.edep + aHit.edep;

      if (aHit.hitNumberTrack1 == 1) //premier hit du track 1 ?
      {
        Single1.X = aHit.X;
        Single1.Y = aHit.Y;
        Single1.Z = aHit.Z;
        Single1.rsectorID = aHit.rsectorID;
        Single1.moduleID = aHit.moduleID;
        Single1.submoduleID = aHit.submoduleID;
        Single1.crystalID = aHit.crystalID;
        Single1.layerID = aHit.layerID;
        Single1.time = aHit.time; //comme dans Gate
      }
      gamma1 = true;
    }

      else if (aHit.trackID == 2)
      {
          Single2.edep = Single2.edep + aHit.edep;

          if (aHit.hitNumberTrack2 == 2)
          {
            Single2.X = aHit.X;
            Single2.Y = aHit.Y;
            Single2.Z = aHit.Z;
            Single2.rsectorID = aHit.rsectorID;
            Single2.moduleID = aHit.moduleID;
            Single2.submoduleID = aHit.submoduleID;
            Single2.crystalID = aHit.crystalID;
            Single2.layerID = aHit.layerID;
            Single2.time = aHit.time; //comme dans Gate
          }
          gamma2 = true;
        }
    }
}

//********************************************************************************

void single::PrintAvailablePolicies()
{
  printf("Pour des backToBacks : \n \
          centroid (non testé) \n \
          winnerTakeAll (testé) \n \
          firstHit (non testé) \n");
}

//********************************************************************************
//********************************************************************************

/*
void single::fillTreeSingle_b2b_v2(TTree* Hits, TString filename)
{
	//variables pour le single
	Double_t energie, energie1, energie2, globalPosX,temps,globalPosY, globalPosZ;
	Int_t STrackID,SlayerID;
	Double_t x1, y1, z1, x2, y2, z2;
	Double_t energieTot1;
	Double_t energieTot2;
	Double_t temps1;
	Double_t temps2;

	// define the variable(s) of interest, type of variable must be respected
	Double_t X, Y, Z, time, edep; //edep : pondération (éventuelle) du centroïde
	Int_t eventID;
	Int_t trackID;
	Int_t layerID;

	//branches d'intérêt
	TBranch* bX;
	TBranch* bY;
	TBranch* bZ;
	TBranch* beventID;
	TBranch* btrackID;
	TBranch* btime;
	TBranch* bedep;
	TBranch* blayerID;

	// Set branch address
	Hits->SetBranchAddress("posX", &X, &bX);
	Hits->SetBranchAddress("posY", &Y, &bY);
	Hits->SetBranchAddress("posZ", &Z, &bZ);
	Hits->SetBranchAddress("eventID", &eventID, &beventID);
	Hits->SetBranchAddress("trackID", &trackID, &btrackID);
	Hits->SetBranchAddress("layerID", &layerID, &blayerID);
	Hits->SetBranchAddress("globalTime", &time, &btime);
	//Hits->SetBranchAddress("GateTime", &time, &btime); //positron
	Hits->SetBranchAddress("edep", &edep, &bedep);

	// Get number of hits in the TTree
	int nH = (int)Hits->GetEntries();

	//initialisation

	 this->Single->Branch("globalPosX",&globalPosX,"globalPosX/D");
	 this->Single->Branch("globalPosY",&globalPosY,"globalPosY/D");
	 this->Single->Branch("globalPosZ",&globalPosZ,"globalPosZ/D");
	 this->Single->Branch("time",&temps,"time/D");
	 this->Single->Branch("energy",&energie,"energy/D");
	 //this->Single->Branch("trackID",&STrackID,"trackID/I");
	 this->Single->Branch("layerID",&SlayerID,"layerID/I");


	 int eventCourant, layerCourant;
	 int i = 0;
	 while(i < nH)
	 {
	 	beventID->GetEntry(i);
	 	eventCourant = eventID;

	 	btime->GetEntry(i);
		temps1 = time ;
		temps2 = time ;

		energie1 = 0;
		energie2 = 0;
		energieTot1 = 0;
	        energieTot2 = 0;


	        x1 = 0;
		y1 = 0;
		z1 = 0;
		x2 = 0;
		y2 = 0;
		z2 = 0;


	 	while ((i<nH) && (eventCourant == eventID))
	 	{
	 		blayerID->GetEntry(i);
	 		layerCourant = layerID;

	 		while ((i<nH) && (layerCourant == layerID) && (eventCourant == eventID))
	 		{
	 			bX->GetEntry(i);
				bY->GetEntry(i);
				bZ->GetEntry(i);
				bedep->GetEntry(i);
				btime->GetEntry(i);
				btrackID->GetEntry(i);
				if (trackID == 1)
				{
		 			energieTot1 = energieTot1 + edep;

					x1 = x1 + X * edep;
					y1 = y1 + Y * edep;
					z1 = z1 + Z * edep;

					if (time < temps1) {temps1 = time;}
				}
				if (trackID == 2)
				{
		 			energieTot2 = energieTot2 + edep;

					x2 = x2 + X * edep;
					y2 = y2 + Y * edep;
					z2 = z2 + Z * edep;

					if (time < temps2) {temps2 = time;}
				}
				i++;
				blayerID->GetEntry(i);
				beventID->GetEntry(i);
	 		}
	 		if (energieTot1 >0)
	 		{
		 		globalPosX = x1/energieTot1;
				globalPosY = y1/energieTot1;
				globalPosZ = z1/energieTot1;
				temps = temps1;
				SlayerID = layerID;
				energie = energieTot1;
				this->Single->Fill();
			}
			energieTot1 = 0;
			x1 = 0;
			y1 = 0;
			z1 = 0;
			btime->GetEntry(i);
			temps1 = time ;
			if (energieTot2 >0)
	 		{
		 		globalPosX = x2/energieTot2;
				globalPosY = y2/energieTot2;
				globalPosZ = z2/energieTot2;
				temps = temps2;
				SlayerID = layerID;
				energie = energieTot2;
				this->Single->Fill();
			}
			energieTot2 = 0;
			x2 = 0;
			y2 = 0;
			z2 = 0;
			btime->GetEntry(i);
			temps2 = time ;
	 	}

	 }



	writeTree(this->Single,filename);

	Hits->ResetBranchAddresses();
	this->Single->ResetBranchAddresses();

	std::cout << "single::fillTreeSingle_b2b_v2" << std:: endl;

}


void single::writeTree(TTree* arbreAEcrire,TString filename)
{
  TFile* target=new TFile(filename,"recreate");
  target->WriteObject(arbreAEcrire, "Singles");
  target->Close();
}

void single::blurMyBranch(TTree* tree, Double_t sigma, TString branchName)
{ //multiplication par une gaussienne de sigma donné et de moyenne la donnée dans l'arbre.
  //modifie l'arbre directement et crée un nouveau fichier

	Double_t blurredVar;
	Double_t branchVar;
	TBranch* bbranchVar;
	TString newBranchName = "blurred" + branchName;

	TBranch *toFill = tree->Branch(newBranchName,&blurredVar,"test/D");

	tree->SetBranchAddress(branchName, &branchVar, &bbranchVar);
	int nH = (int)tree->GetEntries();

	TRandom * r = new TRandom();
	for (int i = 0; i < nH; i++)
	{
		bbranchVar->GetEntry(i);
		blurredVar = r->Gaus(branchVar,sigma); //mean, variance
		std::cout << blurredVar << std:: endl;
		std::cout << i << std:: endl;
		toFill->Fill();
	}
	 std::cout <<(int)tree->GetEntries() << std::endl;

	tree->Scan();
	TString filename = "../outputs/Single_" + newBranchName + ".root";
	writeTree(tree,filename);
	tree->ResetBranchAddresses();
	std::cout << "single::blurMyBranch" << std:: endl;

}
*/
