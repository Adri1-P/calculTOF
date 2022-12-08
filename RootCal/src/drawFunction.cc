#include "drawFunction.hh"
#include <TROOT.h>
#include <TSystem.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TFile.h>
#include <TMath.h>
#include <TF1.h>
#include <TF2.h>
#include <TF3.h>
#include <TProfile.h>
#include <TKey.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TRandom.h>
#include <TPostScript.h>
#include <TNtuple.h>
#include <TChain.h>
#include <TCut.h>
#include <TCutG.h>
#include <TEventList.h>
#include <TBenchmark.h>
#include <TSystem.h>
#include <TApplication.h>
//#include <TClassTable.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TString.h>
#include <TView.h>
#include <TObject.h>
#include <TStyle.h>
#include <TFile.h>
#include <TSystemDirectory.h>
#include <TImageDump.h>
#include <TGraph2D.h>
#include <TMarker.h>

#include <math.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <limits.h>

#include <iostream>

//********************************************************************************
//********************************************************************************
void afficheCastorID(TString filenameRootGate)
{

	TFile* f = TFile::Open(filenameRootGate);
	TTree* Coincidences = (TTree*)f->Get("Coincidences");

	Int_t rsectorID1,moduleID1,submoduleID1,crystalID1,layerID1,CastorID1;
	Int_t rsectorID2,moduleID2,submoduleID2,crystalID2,layerID2,CastorID2;

	TBranch* brsectorID1;
	TBranch* bmoduleID1;
	TBranch* bsubmoduleID1;
	TBranch* bcrystalID1;
	TBranch* blayerID1;
	TBranch* bCastorID1;

	TBranch* brsectorID2;
	TBranch* bmoduleID2;
	TBranch* bsubmoduleID2;
	TBranch* bcrystalID2;
	TBranch* blayerID2;
	TBranch* bCastorID2;


	Coincidences->SetBranchAddress("rsectorID1", &rsectorID1, &brsectorID1);
	Coincidences->SetBranchAddress("moduleID1", &moduleID1, &bmoduleID1);
	Coincidences->SetBranchAddress("submoduleID1", &submoduleID1, &bsubmoduleID1);
	Coincidences->SetBranchAddress("crystalID1", &crystalID1, &bcrystalID1);
	Coincidences->SetBranchAddress("layerID1", &layerID1, &blayerID1);
	Coincidences->SetBranchAddress("CastorID1", &CastorID1, &bCastorID1);


	Coincidences->SetBranchAddress("rsectorID2", &rsectorID2, &brsectorID2);
	Coincidences->SetBranchAddress("moduleID2", &moduleID2, &bmoduleID2);
	Coincidences->SetBranchAddress("submoduleID2", &submoduleID2, &bsubmoduleID2);
	Coincidences->SetBranchAddress("crystalID2", &crystalID2, &bcrystalID2);
	Coincidences->SetBranchAddress("layerID2", &layerID2, &blayerID2);
	Coincidences->SetBranchAddress("CastorID2", &CastorID2, &bCastorID2);

	int nC = (int) Coincidences->GetEntries();

	for (int i = 0; i < nC;i++)
	{

    brsectorID1->GetEntry(i);
    bmoduleID1->GetEntry(i);
    bsubmoduleID1->GetEntry(i);
    bcrystalID1->GetEntry(i);
    blayerID1->GetEntry(i);
		bCastorID1->GetEntry(i);

		brsectorID2->GetEntry(i);
    bmoduleID2->GetEntry(i);
    bsubmoduleID2->GetEntry(i);
    bcrystalID2->GetEntry(i);
    blayerID2->GetEntry(i);
		bCastorID2->GetEntry(i);

		std::cout << " rsectorID1 : " << rsectorID1 << " " << " moduleID1 : " << moduleID1 << " " <<" submoduleID1 : " << submoduleID1 << " " <<" crystalID1 : " << crystalID1 << " " <<" layerID1 : " << layerID1 << " " <<" CastorID1 : " << CastorID1 <<  std::endl;


		std::cout << " rsectorID2 : " << rsectorID2 << " " << " moduleID2 : " << moduleID2 << " " <<" submoduleID2 : " << submoduleID2 << " " <<" crystalID2 : " << crystalID2 << " " <<" layerID2 : " << layerID2 << " " <<" CastorID2 : " << CastorID2 <<  std::endl;

	}

}
void drawgraphs() {

//fonction de base pour faire un plot. à améliorer. Ne donne pas toujours le même résultat que la fonction draw.

	std::cout << "drawgraphs" << std::endl;
	TFile* f = TFile::Open("outputs/Geant4_cut1mm.root");


	TTree* Hits = (TTree*)f->Get("Hits");
	//TTree* Events = (TTree*)f->Get("Event");

	// define the variable(s) of interest, type of variable must be respected
	Double_t X;
	Double_t Y;
	Double_t Z;
	Double_t time;
	Int_t eventID;
	Int_t trackID;
	Int_t stepNumber;
	Int_t parentID;

	Char_t preProcessName[40];
	Char_t postProcessName[40];

	Double_t edep;

	//variables interm�diaires et/ou finales
	Double_t x1, y1, z1;
	Double_t x2, y2, z2;
	Double_t time1;
	Double_t time2;
	Double_t deltaT;

	//branches d'int�r�t
	TBranch* bX;
	TBranch* bY;
	TBranch* bZ;
	TBranch* beventID;
	TBranch* btrackID;
	TBranch* btime;
	TBranch* bstepNumber;
	TBranch* bparentID;

	TBranch* bpreProcessName;
	TBranch* bpostProcessName;

	TBranch* bedep;


	// Set branch address
	Hits->SetBranchAddress("X", &X, &bX);
	Hits->SetBranchAddress("Y", &Y, &bY);
	Hits->SetBranchAddress("Z", &Z, &bZ);
	Hits->SetBranchAddress("EventID", &eventID, &beventID);
	Hits->SetBranchAddress("trackID", &trackID, &btrackID);
	Hits->SetBranchAddress("GlobalTime", &time, &btime);
	Hits->SetBranchAddress("stepNumber", &stepNumber, &bstepNumber);
	Hits->SetBranchAddress("parentID", &parentID, &bparentID);

	Hits->SetBranchAddress("PreProcessName", preProcessName, &bpreProcessName);
	Hits->SetBranchAddress("PostProcessName", postProcessName, &bpostProcessName);

	//Events->SetBranchAddress("fEdep", &edep, &bedep);

	TH3D* h = new TH3D("h", "positions des hits", 100, -800, 800, 100, -800, 800, 100, -800, 800);
	TH3D* hfirst = new TH3D("hfirst", "positions des premiers hits", 100, -800, 800, 100, -800, 800, 100, -800, 800);
	TH1D* ht = new TH1D("ht", "Delta t", 100, -220, 220);

	// Get number of hits in the TTree
	int nH = (int)Hits->GetEntries();

	TArrayD  *tabX = new TArrayD(nH);

	//initialisation
	x1 = 0;
	y1 = 0;
	z1 = 0;

	x2 = 0;
	y2 = 0;
	z2 = 0;

	// Loop over hits
	for (int i = 0; i < nH; i++)
	{
		//get event i
		bX->GetEntry(i);
		bY->GetEntry(i);
		bZ->GetEntry(i);
		btime->GetEntry(i);
		bparentID->GetEntry(i);
		beventID->GetEntry(i);

		btrackID->GetEntry(i);
		bstepNumber->GetEntry(i);

		bpreProcessName->GetEntry(i);
		bpostProcessName->GetEntry(i);


		if ((parentID == 0) & (trackID == 1) & (preProcessName[0] == 'T') & ((postProcessName[0] == 'c') || (postProcessName[0] == 'p') || (postProcessName[0] == 'R')))
		{
			x1 = X; y1 = Y; z1 = Z; time1 = time; // position du premier hit ?
			hfirst->Fill(x1, y1, z1);
		}

		if ((parentID == 0) & (trackID == 2) & (preProcessName[0] == 'T') & ((postProcessName[0] == 'c') || (postProcessName[0] == 'p') || (postProcessName[0] == 'R')))
		{
			x2 = X; y2 = Y; z2 = Z; time2 = time;
			hfirst->Fill(x2, y2, z2);
		}

		//fill histogram
		h->Fill(X, Y, Z); //mettre dans le bon ordre...

		deltaT = time1 - time2;
		ht->Fill(deltaT);

		tabX->AddAt(X,i);
	}


	//std::cout << *tabX << std::endl;


	TH1D* h2 = new TH1D("h2", "energie deposee par event", 100, 0, 1.2);
/*	// Get number of events in the TTree
	int nE = (int)Events->GetEntries();


	// Loop over events
	for (int i = 0; i < nE; i++)
	{
		//get event i
		bedep->GetEntry(i);
		//fill histogram
		h2->Fill(edep); //mettre dans le bon ordre...
	}

*/

	//remove the stat from upper right corner
	gStyle->SetOptStat(0);
	//remove the title
	gStyle->SetOptTitle(0);
	//define fonts sizes
	gStyle->SetPalette(1);
	gStyle->SetTextSize(0.16);
	gStyle->SetLabelSize(0.06, "x");
	gStyle->SetLabelSize(0.06, "y");
	gStyle->SetLabelSize(0.06, "z");
	gStyle->SetTitleSize(0.06, "x");
	gStyle->SetTitleSize(0.05, "y");
	gStyle->SetTitleSize(0.06, "z");
	gStyle->SetLineWidth(2);

	//Define canvas
	TCanvas* can = new TCanvas("can", "can", 1920, 1080);
	//Define paramters of the canvas
	can->SetFillColor(0);
	can->SetBorderMode(0);
	can->SetBorderSize(3);
	can->SetBottomMargin(0.14);
	can->SetLeftMargin(0.3);
	can->SetFrameBorderMode(2);
	can->SetFrameLineWidth(1);


	h->GetXaxis()->SetTitle("X");
	h->GetYaxis()->SetTitleOffset(0.7);
	h->GetYaxis()->SetTitle("Y");
	h->Draw();

	hfirst->SetMarkerStyle(2);

	hfirst->SetMarkerColor(2);
	hfirst->Draw("same");


	auto legend = new TLegend(0.01, 0.1, 0.2, 0.9);
	legend->SetHeader("position des preStepPoints"); // option "C" allows to center the header
	legend->AddEntry(h, "en rouge : position des preStepPoints verifiant la condition ");
	legend->Draw();


	//Define canvas
	TCanvas* can4 = new TCanvas("can4", "can4", 1920, 1080);
	//Define paramters of the canvas
	can4->SetFillColor(0);
	can4->SetBorderMode(0);
	can4->SetBorderSize(3);
	can4->SetBottomMargin(0.14);
	can4->SetLeftMargin(0.3);
	can4->SetFrameBorderMode(2);
	can4->SetFrameLineWidth(1);
	//can4->SaveAs("test.png");

	ht->GetXaxis()->SetTitle("dt");
	ht->Draw();

}

//********************************************************************************

void DrawDirectory() {

// intéressant si on veut utiliser tous les fichiers roots d'un répertoire

	Int_t i = 0;
	TString ext = ".root";
	TString dirname = "outputs";
	TSystemDirectory dir(dirname, dirname);
	TList* files = dir.GetListOfFiles();
	if (files) {
		TSystemFile* file;
		TString fname;
		TIter next(files);
		while ((file = (TSystemFile*)next())) {
			fname = file->GetName();
			if (!file->IsDirectory() && fname.EndsWith(ext)) {
				TString absoluteName = dirname +'/'+ fname;
				//std::cout << fname.Length() << std::endl;
				TFile* f = TFile::Open(absoluteName);



				TTree* Hits = (TTree*)f->Get("TousSTEP");
				TTree* Events = (TTree*)f->Get("Event");

				// define the variable(s) of interest, type of variable must be respected
				Double_t X;
				Double_t Y;
				Double_t Z;
				Double_t time;
				Int_t eventID;
				Int_t trackID;
				Int_t stepNumber;
				Int_t parentID;

				Char_t preProcessName[40];
				Char_t postProcessName[40];

				Double_t edep;

				//variables interm�diaires et/ou finales
				Double_t x1, y1, z1;
				Double_t x2, y2, z2;
				Double_t time1;
				Double_t time2;
				Double_t deltaT;

				//branches d'int�r�t
				TBranch* bX;
				TBranch* bY;
				TBranch* bZ;
				TBranch* beventID;
				TBranch* btrackID;
				TBranch* btime;
				TBranch* bstepNumber;
				TBranch* bparentID;

				TBranch* bpreProcessName;
				TBranch* bpostProcessName;

				TBranch* bedep;


				// Set branch address
				Hits->SetBranchAddress("X", &X, &bX);
				Hits->SetBranchAddress("Y", &Y, &bY);
				Hits->SetBranchAddress("Z", &Z, &bZ);
				Hits->SetBranchAddress("EventID", &eventID, &beventID);
				Hits->SetBranchAddress("trackID", &trackID, &btrackID);
				Hits->SetBranchAddress("GlobalTime", &time, &btime);
				Hits->SetBranchAddress("stepNumber", &stepNumber, &bstepNumber);
				Hits->SetBranchAddress("parentID", &parentID, &bparentID);

				Hits->SetBranchAddress("PreProcessName", preProcessName, &bpreProcessName);
				Hits->SetBranchAddress("PostProcessName", postProcessName, &bpostProcessName);

				Events->SetBranchAddress("fEdep", &edep, &bedep);

				TH3D* h = new TH3D("h", "positions des hits", 100, -800, 800, 100, -800, 800, 100, -800, 800);
				TH3D* hfirst = new TH3D("hfirst", "positions des premiers hits", 100, -800, 800, 100, -800, 800, 100, -800, 800);
				TH1D* ht = new TH1D("ht", "Delta t", 100, -200, 200);

				// Get number of hits in the TTree
				int nH = (int)Hits->GetEntries();

				//initialisation
				x1 = 0;
				y1 = 0;
				z1 = 0;

				x2 = 0;
				y2 = 0;
				z2 = 0;

				// Loop over hits
				for (int i = 0; i < nH; i++)
				{
					//get event i
					bX->GetEntry(i);
					bY->GetEntry(i);
					bZ->GetEntry(i);
					btime->GetEntry(i);
					bparentID->GetEntry(i);
					beventID->GetEntry(i);

					btrackID->GetEntry(i);
					bstepNumber->GetEntry(i);

					bpreProcessName->GetEntry(i);
					bpostProcessName->GetEntry(i);


					if ((parentID == 0) & (trackID == 1) & (preProcessName[0] == 'T') & ((postProcessName[0] == 'c') || (postProcessName[0] == 'p') || (postProcessName[0] == 'R')))
					{
						x1 = X; y1 = Y; z1 = Z; time1 = time; // position du premier hit ?
						hfirst->Fill(x1, y1, z1);
					}

					if ((parentID == 0) & (trackID == 2) & (preProcessName[0] == 'T') & ((postProcessName[0] == 'c') || (postProcessName[0] == 'p') || (postProcessName[0] == 'R')))
					{
						x2 = X; y2 = Y; z2 = Z; time2 = time;
						hfirst->Fill(x2, y2, z2);
					}
					//fill histogram
					h->Fill(X, Y, Z); //mettre dans le bon ordre...

					deltaT = time1 - time2;
					ht->Fill(deltaT);
				}

				TH1D* h2 = new TH1D("h2", "energie deposee par event", 100, 0, 1.2);
				// Get number of events in the TTree
				int nE = (int)Events->GetEntries();

				// Loop over events
				for (int i = 0; i < nE; i++)
				{
					//get event i
					bedep->GetEntry(i);
					//fill histogram
					h2->Fill(edep); //mettre dans le bon ordre...
				}



				//remove the stat from upper right corner
				gStyle->SetOptStat(0);
				//remove the title
				gStyle->SetOptTitle(0);
				//define fonts sizes
				gStyle->SetPalette(1);
				gStyle->SetTextSize(0.16);
				gStyle->SetLabelSize(0.06, "x");
				gStyle->SetLabelSize(0.06, "y");
				gStyle->SetLabelSize(0.06, "z");
				gStyle->SetTitleSize(0.06, "x");
				gStyle->SetTitleSize(0.05, "y");
				gStyle->SetTitleSize(0.06, "z");
				gStyle->SetLineWidth(2);

				//Define canvas
				TString *name = new TString(fname, fname.Length() - 5);
				TCanvas* can = new TCanvas(name->Data(), name->Data(), 1920, 1080); //nom titre taille taille
				//Define paramters of the canvas
				can->SetFillColor(0);
				can->SetBorderMode(0);
				can->SetBorderSize(3);
				can->SetBottomMargin(0.14);
				can->SetLeftMargin(0.3);
				can->SetFrameBorderMode(2);
				can->SetFrameLineWidth(1);


				h->GetXaxis()->SetTitle("X");
				h->GetYaxis()->SetTitleOffset(0.7);
				h->GetYaxis()->SetTitle("Y");
				h->Draw();

				hfirst->SetMarkerStyle(2);

				hfirst->SetMarkerColor(2);
				hfirst->Draw("same");


				auto legend = new TLegend(0.01, 0.1, 0.2, 0.9);
				legend->SetHeader("position des preStepPoints"); // option "C" allows to center the header
				legend->AddEntry(h, "en rouge : position des preStepPoints verifiant la condition ");
				legend->Draw();




				//Define canvas
				TString suffixe = "_dt";
				TString canvasName = *name + suffixe;
				TCanvas* can4 = new TCanvas(canvasName, canvasName, 1920, 1080);
				//Define paramters of the canvas
				can4->SetFillColor(0);
				can4->SetBorderMode(0);
				can4->SetBorderSize(3);
				can4->SetBottomMargin(0.14);
				can4->SetLeftMargin(0.3);
				can4->SetFrameBorderMode(2);
				can4->SetFrameLineWidth(1);

				ht->GetXaxis()->SetTitle("dt");
				ht->Draw();

				TString prefixe = "graphs/";
				TString ext2 = ".png";
				TString filename = prefixe + *name + ext2;
				TImageDump* imgdump = new TImageDump(filename.Data());
				can->Paint();
				imgdump->Close();

				filename = prefixe + *name + suffixe + ext2;
				imgdump = new TImageDump(filename.Data());
				can4->Paint();
				imgdump->Close();


				i++;
				//f->Close();

			}
		}
	}
}

//********************************************************************************

TCanvas* showGate_dt(TString  filename)
{
	//mini fonction pour afficher le dt depuis un fichier Gate
	TFile* f = TFile::Open(filename);
	TTree* Coincidences;
	f->GetObject("Coincidences", Coincidences);

	TCanvas *can = new TCanvas("can_fillDtGate_rand","can",1920,1080);
	Coincidences->Draw("time1-time2");
	return can;
}




void GateScanHits(TString  filename)
{
//une fonction qui a servi à voir que des hits se baladaient dans plusieurs cristaux

	TFile* f = TFile::Open(filename);
	TTree* Hits;
	f->GetObject("Hits", Hits);

	TTree* Singles;
	f->GetObject("Singles", Singles);

	Int_t eventID;
	Int_t trackID;

	Int_t gantryID; // ?
	Int_t rsectorID; //1
	Int_t moduleID; //2
	Int_t submoduleID; //3
	Int_t crystalID; //4
	Int_t layerID;  //5

	Float_t edep;


	//branches d'int�r�t
	TBranch* beventID;
	TBranch* btrackID;

	TBranch* bgantryID;
	TBranch* brsectorID;
	TBranch* bmoduleID;
	TBranch* bsubmoduleID;
	TBranch* bcrystalID;
	TBranch* blayerID;

	TBranch* bedep;


	// Set branch address
	Hits->SetBranchAddress("eventID", &eventID, &beventID);
	Hits->SetBranchAddress("trackID", &trackID, &btrackID);

	Hits->SetBranchAddress("gantryID", &gantryID, &bgantryID);
	Hits->SetBranchAddress("rsectorID", &rsectorID, &brsectorID);
	Hits->SetBranchAddress("moduleID", &moduleID, &bmoduleID);
	Hits->SetBranchAddress("submoduleID", &submoduleID, &bsubmoduleID);
	Hits->SetBranchAddress("crystalID", &crystalID, &bcrystalID);
	Hits->SetBranchAddress("layerID", &layerID, &blayerID);

	Hits->SetBranchAddress("edep", &edep, &bedep);


	// Get number of hits in the TTree
	int nH = (int)Hits->GetEntries();
	//nH = 1000;

	//variables boucle
	int i = 0;
	int c1 = 0;
	int c2 = 0;
	int j = 0;
	int ps = 0;
	int deuxGammasCount = 0;

	bool gamma1 = false;
	bool gamma2 = false;

	bool touriste1Repere; //y a t-il un touriste dans cet event pour ce track  ?
	bool touriste2Repere;

	bool premierModule1;
	bool premierModule2;

	int currentEvent;
	int currentModule1;
	int currentModule2;




	//initialisation
	int touriste1 = 0; //nombre d'events o� le track1 parcourt plusieurs module
	int touriste2 = 0;

	// Loop over hits
	while ( (i < nH) )
	{

		//d�but event

		beventID->GetEntry(i);
		currentEvent = eventID;
		bedep->GetEntry(i);
		btrackID->GetEntry(i);

		touriste1Repere = false;
		touriste2Repere = false;

		premierModule1 = true;
		premierModule2 = true;

		//std ::cout <<"debut event : " <<  eventID << "currentEvent : " << currentEvent << std :: endl;

		if (((trackID == 1) || (trackID == 2)) && edep >0)
		{
			do
			{
				beventID->GetEntry(i);
				btrackID->GetEntry(i);
				bedep->GetEntry(i);

				if(eventID == currentEvent)
				{
					if (trackID == 1 && edep > 0)
					{
						brsectorID->GetEntry(i); // [A MODIFIER SI DEPTH CHANGE ]
						if(premierModule1) {currentModule1 = rsectorID; premierModule1 = false;} //premier module rencontr�. Doit �tre le seul dans l'event pour un track donn�. // [A MODIFIER SI DEPTH CHANGE ]
						else
						{
							//std ::cout <<"moduleID track1 : " << moduleID <<  "moduleCourant1 : " << currentModule1<< std :: endl;
							if ((rsectorID != currentModule1) && !touriste1Repere ) // [A MODIFIER SI DEPTH CHANGE ]
							{touriste1++;touriste1Repere = true;}//std ::cout <<"touriste1Repere"<< std :: endl;} //un seul touriste par event
						}
						gamma1 = true;
						c1++;
					}
					else if (trackID == 2 && edep > 0)
					{
						brsectorID->GetEntry(i); // [A MODIFIER SI DEPTH CHANGE ]

						if(premierModule2) {currentModule2 = rsectorID; premierModule2 = false;} // [A MODIFIER SI DEPTH CHANGE ]
						else
						{
							//std ::cout <<"moduleID track2 : " << moduleID <<  "moduleCourant2 : " << currentModule2<< std :: endl;
							if ((rsectorID != currentModule2) && !touriste2Repere)  // [A MODIFIER SI DEPTH CHANGE ]
							{touriste2++;touriste2Repere = true;}//std ::cout <<"touriste2Repere"<< std :: endl;}
						}

						gamma2 = true;
						c2++;
					}
					else   {ps++;}
					i++;
				}
			}
			while ((i < nH) && (eventID == currentEvent));
		}
		else   {ps++; i++;}
		//std ::cout <<"finEvent  " << "eventID : " <<  eventID << "currentEvent : " << currentEvent << std :: endl;

		if (gamma1 && gamma2) {deuxGammasCount++;}
		gamma1 = false;
		gamma2 = false;
		j++;
	}

	Hits->ResetBranchAddresses();
	Double_t nS = Singles->GetEntries();

	std::cout << ps << " hits de particules secondaires pour ce run" << std:: endl;
	std::cout << j << " nombre d'events trait�s : " <<  std:: endl;
	std::cout << deuxGammasCount << " nombre d'events ayant deux gammas" << std:: endl;
	std::cout <<  " nombre de hits dans le track 1 : " << c1 << std:: endl;
	std::cout <<  " nombre de hits dans le track 2 : " << c2 << std:: endl;
	std::cout << "nombre d'events o� le track1 parcourt plusieurs cristaux : " << touriste1 << std:: endl; // [A MODIFIER SI DEPTH CHANGE ]
	std::cout << "nombre d'events o� le track2 parcourt plusieurs cristaux : " << touriste2 << std:: endl; // [A MODIFIER SI DEPTH CHANGE ]
	std::cout << nH << " nombre de hits : " << "nombre de singles (Gate) : " << nS << std:: endl;
	printf("�cart relatif : %f \n" ,(double) ((1 - (nS -touriste1 -touriste2) / nS)) * 100);
}

//********************************************************************************

TCanvas* fillDtGate_rand(TString filename)
{
//affiche le dt depuis un fichier Gate mais avec un signe aléatoire pour le résultat de la différence

  // open the file
TFile *f = TFile::Open(filename);
// get the TTree
TTree *Tree = (TTree*)f->Get("Coincidences");
//cout<< Tree->GetEntries()<<endl;
// define the variable(s) of interest, type of variable must be respected
Double_t time1;
Double_t time2;
TBranch * btime1;
TBranch * btime2;
Float_t dt;
Int_t eventID1, eventID2;
TBranch *  beventID1,* beventID2;

//Tree->SetBranchStatus("*",0);
Tree->SetBranchStatus("time1",1);
Tree->SetBranchStatus("time2",1);
Tree->SetBranchStatus("eventID1",1);
Tree->SetBranchStatus("eventID2",1);

// Set branch address
Tree->SetBranchAddress("time1",&time1,&btime1);
Tree->SetBranchAddress("time2",&time2,&btime2);
Tree->SetBranchAddress("eventID1",&eventID1,&beventID1);
Tree->SetBranchAddress("eventID2",&eventID2,&beventID2);
// Get number of events in the TTree
int n=(int)Tree->GetEntries();

// Define a histogram with 100 bins, on x from 0 to 1
 TH1F* h = new TH1F("h","Gate TOF measure (GE)",100,-3 *pow(10,-10)  ,3 * pow(10,-10) );//* pow(10,-10));
 //TH1F* h = new TH1F("h","h",100,-10000,10000);
// Loop over events
TRandom r;
unsigned int ntot = 1;
double prob = 0.5;
for(int i=0;i<n;i++)
{
	beventID1 -> GetEntry(i);
	beventID2 -> GetEntry(i);
			if (eventID1 == eventID2)
			{
			//get event i
			btime1 -> GetEntry(i);
			btime2 -> GetEntry(i);

			dt = (time2 - time1) * (r.Binomial(ntot,prob) * 2 -1); // (a - b) * ({0;1} * 2 -1 = {-1;1})   ;
			//dt = dt * pow(10,12); // pour mettre en ps

			//fill histogram
			 h->Fill(dt);
			}
 }
	TCanvas *can = new TCanvas("can_fillDtGate_rand","can",1920,1080);

	Int_t ci;      // for color index setting
	TColor *color; // for color definition with alpha
	ci = TColor::GetColor("#000099");
	h->SetLineColor(ci);
	h->GetXaxis()->SetTitle("TOF (s)");
	h->GetXaxis()->SetLabelFont(42);
	h->GetXaxis()->SetTitleOffset(1);
	h->GetXaxis()->SetTitleFont(42);
	h->GetYaxis()->SetTitle("# of coincidences");
	h->GetYaxis()->SetLabelFont(42);
	h->GetYaxis()->SetTitleFont(42);
	h->GetZaxis()->SetLabelFont(42);
	h->GetZaxis()->SetTitleOffset(1);
	h->GetZaxis()->SetTitleFont(42);
	h->Draw("");
	h->Fit("gaus");

	TF1 * fitFun = h->GetFunction("gaus");
	double sigma = fitFun->	GetParameter("Sigma");
	gStyle->SetOptFit(1011);
	std::cout << "FWHM = " << sigma*pow(10,12)*2.35 << "ps" << std::endl;
	return can;
}

TCanvas* DrawArray(Int_t n, Double_t x[], Double_t y[])
{
	TGraph * gr = new TGraph(n,x,y);
	TCanvas * can = new TCanvas("gr","MyGraph",1920,1080);
	/*
	for (Int_t i = 0; i < n; i++)
	{
		TMarker *m = new TMarker (x[i],y[i],0);
		m->Draw();
	}
	*/
	gr->Draw("AP*");
	
	return can;

}

TCanvas* Draw2Arrays(Int_t n, Double_t x1[], Double_t y1[],Double_t x2[], Double_t y2[])
{
	TGraph * gr1 = new TGraph(n,x1,y1);
	TGraph * gr2 = new TGraph(n,x2,y2);
	
	
	
	
	Double_t x_moyenne[4] = {5,8,11,14};
	Double_t y_moyenne_simu[4] = {(2.942 + 2.914)/2.0, (3.407 + 3.559)/2.0, (4.477 + 4.726) / 2.0, (4.869 + 5.755)/2.0};
	Double_t y_moyenne_exp[4] = {(2.874 + 2.579) / 2.0, (3.946 + 3.691) /2.0, (4.493 + 4.263)/2.0, (5.374 + 5.677)/2.0};
	
	Double_t ex[5] = {0,0,0,0,0};
	Double_t ey[5] = {0, abs((2.942-y_moyenne_simu[0])),abs((3.407 - y_moyenne_simu[1])), abs((4.477 - y_moyenne_simu[2])), abs((4.869 - y_moyenne_simu[3]))}; 
	
	Double_t ey_exp[5] = {0, abs((2.874-y_moyenne_exp[0])),abs((3.946 - y_moyenne_exp[1])), abs((4.493 - y_moyenne_exp[2])), abs((5.374 - y_moyenne_exp[3]))}; 
	
	
	/*
	for (int i = 0; i < 5; i++)
	{
	std::cout << ey[i] << std::endl;
	}
	*/
	
	Double_t x[5] = {1,5,8,11,14};
	Double_t y[5] = {y1[4],y_moyenne_simu[0],y_moyenne_simu[1],y_moyenne_simu[2],y_moyenne_simu[3]};
	
	Double_t y_simu[5] = {y2[4],y_moyenne_exp[0],y_moyenne_exp[1],y_moyenne_exp[2],y_moyenne_exp[3]};
	
	TGraphErrors* gr = new TGraphErrors(5,x,y,ex,ey);
	
	TGraphErrors* gr_exp = new TGraphErrors(5,x,y_simu,ex,ey_exp);
	
	
	Double_t xpubli[3] = {1,10,20};
	Double_t ypubli[3] = {3.55,3.98,4.58};
	Double_t ey_publi[3] = {0.61/2.0,0.28/2.0,0.61/2.0};
	
	TGraphErrors* gr_pub = new TGraphErrors(3,xpubli,ypubli,ex,ey_publi);
	
	
	TGraph * gr3 = new TGraph(3,xpubli,ypubli);
	TGraph * gr4 = new TGraph(4,x_moyenne,y_moyenne_simu);
	TGraph * gr5 = new TGraph(4,x_moyenne,y_moyenne_exp);
		
	TCanvas * can = new TCanvas("gr","MyGraph",1920,1080);
	gStyle->SetLegendFont(42);
	//gStyle->SetLegendTextSize(0.1);
	gr_pub->GetXaxis()->SetTitle("Distance of source from the center (cm)");
	gr_pub->GetXaxis()->CenterTitle(true);
	gr_pub->GetYaxis()->SetTitle("Spatial resolution FWHM (mm)");	
	gr_pub->GetYaxis()->CenterTitle(true);	
	gr_pub->GetYaxis()->SetRangeUser(2,6);
	//gr_pub->GetXaxis()->SetRangeUser(2,6);	
	
	gr_pub->SetTitle("");
	gr_pub->SetMarkerSize(2);	
	gr_exp->SetMarkerSize(2);
	gr->SetMarkerSize(2);				
	//gr1->Draw("A*");
			
	gr->SetMarkerStyle(3);	
	gr_exp->SetMarkerStyle(3);
	gr_pub->SetMarkerStyle(3);
	
	gr_exp->SetMarkerColor(2);
	gr_pub->SetMarkerColor(3);
	
	gr_exp->SetLineColor(2);
	gr_pub->SetLineColor(3);
	
	gr_pub->Draw("A*");	//formule magique
	gr->Draw("*");		
	gr_exp->Draw("P*");
	/*
	gr3->SetMarkerSize(2);
	gr3->SetMarkerColor(3);
	gr3->Draw("*");
	
	gr4->SetMarkerSize(2);
	gr4->SetMarkerColor(1); //simu c'est couleur 1
	gr4->Draw("*");
	
	gr5->SetMarkerSize(2);
	gr5->SetMarkerColor(2); //exp c'est couleur 2
	gr5->Draw("*");
	
	gr2->Draw("P*");
	*/
	
	
	TLegend *legend = new TLegend (0.1501043,0.6998106,0.4498957,0.8996212);
	legend->AddEntry(gr,"FWHM blurring 1mm simu");
	legend->AddEntry(gr_exp,"FWHM exp");
	legend->AddEntry(gr_pub,"FWHM  Medical Physics");
	legend->SetTextSize(0.03);
	legend->Draw();
	
	
	
	return can;

}

//********************************************************************************
//********************************************************************************
// TCanvas* showHitProperty_CutOnAString(TString filename, TString property, TString  cut, TString booleanOperator, TString aString)
// {
// 	TFile* f = TFile::Open(filename);
// 	TTree* Hits;
// 	f->GetObject("Hits", Hits);
//
// 	Int_t hitNumber, hitNumberTrack1, hitNumberTrack2, trackID, eventID, parentID, layerID;
//   Float_t posX,posY,posZ,SposX,SposY,SposZ,time,edep;
// 	TString particleName,processName,volumeName;
//
// 	TBranch* bhitNumber, bhitNumberTrack1, bhitNumberTrack2, btrackID, beventID, bparentID, blayerID;
// 	TBranch* bposX, bposY, bposZ, bSposX, bSposY, bSposZ, btime, bedep;
// 	TBranch* bparticleName, bprocessName, bvolumeName;
//
// 	Hits->SetBranchAddress("hitNumber", &hitNumber, &bhitNumber);
// 	Hits->SetBranchAddress("hitNumberTrack1", &hitNumberTrack1, &bhitNumberTrack1);
// 	Hits->SetBranchAddress("hitNumberTrack2", &hitNumberTrack2, &bhitNumberTrack2);
// 	Hits->SetBranchAddress("trackID", &trackID, &btrackID);
// 	Hits->SetBranchAddress("eventID", &eventID, &beventID);
// 	Hits->SetBranchAddress("parentID", &parentID, &bparentID);
// 	Hits->SetBranchAddress("layerID", &layerID, &blayerID);
//
// 	Hits->SetBranchAddress("posX", &posX, &bposX);
// 	Hits->SetBranchAddress("posY", &posY, &bposY);
// 	Hits->SetBranchAddress("posZ", &posZ, &bposZ);
// 	Hits->SetBranchAddress("SposX", &SposX, &bSposX);
// 	Hits->SetBranchAddress("SposY", &SposY, &bSposY);
// 	Hits->SetBranchAddress("SposZ", &SposZ, &bSposZ);
// 	Hits->SetBranchAddress("time", &time, &btime);
// 	Hits->SetBranchAddress("edep", &edep, &bedep);
//
// 	Hits->SetBranchAddress("particleName", &particleName, &bparticleName);
// 	Hits->SetBranchAddress("processName", &processName, &bprocessName);
// 	Hits->SetBranchAddress("volumeName", &volumeName, &bvolumeName);
//
// 	int nH = (int)Hits->GetEntries();
//
// 	TH1F* h = new TH1F("h","h",100,-2 *pow(10,-10)  ,2 * pow(10,-10) );//* pow(10,-10));
//
//
// 	for(int i=0;i<n;i++)
// 	{
// 		bhitNumber -> GetEntry(i);
// 		bhitNumberTrack1 -> GetEntry(i);
// 		bhitNumberTrack2 -> GetEntry(i);
//
// 		bprocessName -> GetEntry(i);
// 		bvolumeName -> GetEntry(i);
// 		bparticleName -> GetEntry(i);
// 	}
//
// 	TCanvas *can = new TCanvas("myCanvas","can",1920,1080);
// 	return can;
// }
