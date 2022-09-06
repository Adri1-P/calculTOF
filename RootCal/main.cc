#include "compareFunction.hh"
#include "drawFunction.hh"
#include "single.hh"
#include "coincidences.hh"

#include <TApplication.h>
#include <TRootCanvas.h>
#include <TFile.h>
#include "TTree.h"


#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>


using namespace std;


int main(int argc, char** argv)
{

//some filenames
TString fileG4_s = "../../../calculTOF_outputs/G4Outputs/G4DebugTime0.root";//simple
TString fileG4_i = "../../../calculTOF_outputs/G4Outputs/G4DebugTimeTOF.root"; //intermediaire
TString fileG4_ib = "../../../calculTOF_outputs/G4Outputs/G4DebugTimeTOF_blocks_droits.root"; //intermediaire avec deux blocks de cristaux
TString fileG4_ib50 = "../../../calculTOF_outputs/G4Outputs/G4DebugTimeTOF_blocks_droits50.root"; //intermediaire avec deux blocks, grand nombre de cristaux
TString fileG4_ibd50Twta = "../../../calculTOF_outputs/G4Outputs/G4DebugTimeTOF_bd50_Twta.root"; //intermediaire avec deux blocks (bon sens), grand nombre de cristaux, TimeMin si edepMax
TString fileG4_ibd50iso = "../../../calculTOF_outputs/G4Outputs/G4DebugTimeTOF_bd50_iso.root"; //intermediaire avec deux blocks (bon sens), grand nombre de cristaux, source iso
TString fileG4_c = "../../../calculTOF_outputs/G4Outputs/G4ScanGERef.root";//complete
TString fileG4_cds = "../../../calculTOF_outputs/G4Outputs/G4ScanGERef_ds.root"; //ref avec deux sources
TString fileG4_csv = "../../../calculTOF_outputs/G4Outputs/sourcesVolumiques.root"; //ref avec quatre sources volumiques

//TString monSingleG4withGate = "../outputs/Single_GateHits.root";
TString fileGate_s = "../../../calculTOF_outputs/GateOutputs/GateCalDebugTime.root";//simple
TString fileGate_i = "../../../calculTOF_outputs/GateOutputs/GateCalDebugTimeTOF.root";//intermediaire
TString fileGate_ib_nR = "../../../calculTOF_outputs/GateOutputs/GateCalDebugTimeTOF_blocks_noReadout.root";//intermediaire avec deux blocks de cristaux
TString fileGate_ib_oR = "../../../calculTOF_outputs/GateOutputs/GateCalDebugTimeTOF_blocks_onlyReadout.root";//intermediaire avec deux blocks de cristaux
TString fileGate_ib = "../../../calculTOF_outputs/GateOutputs/GateCalDebugTimeTOF_blocks_droits.root";//intermediaire avec deux blocks de cristaux
TString fileGate_ib50 = "../../../calculTOF_outputs/GateOutputs/GateCalDebugTimeTOF_blocks_droits50.root";//intermediaire avec deux blocks, grand nombre de cristaux
TString fileGate_ibd50iso = "../../../calculTOF_outputs/GateOutputs/GateCalDebugTimeTOF_bd50iso.root";//intermediaire avec deux blocks (bon sens), grand nombre de cristaux, source iso
TString fileGate_c = "../../../calculTOF_outputs/GateOutputs/GateCalRef.root";//complete
TString fileGate_c_EWC = "../../../calculTOF_outputs/GateOutputs/GateCalRef_EWC.root";//complete

TString filenameSingle_c = "../../../calculTOF_outputs/RootOutputs/G4SingleTest_c.root";
TString filenameCoincidences_c = "../../../calculTOF_outputs/RootOutputs/G4CoincidencesTest_c.root";
TString filenameSingle_Twta = "../../../calculTOF_outputs/RootOutputs/G4SingleTest_Twta.root";
TString filenameCoincidences_Twta = "../../../calculTOF_outputs/RootOutputs/G4CoincidencesTest_Twta.root";
TString filenameSingle_EWC = "../../../calculTOF_outputs/RootOutputs/G4SingleTest_EWC.root";
TString filenameCoincidences_EWC = "../../../calculTOF_outputs/RootOutputs/G4CoincidencesTest_EWC.root";
TString filenameSingle_Debug = "../../../calculTOF_outputs/RootOutputs/SingleDebug.root";
TString filenameCoincidences_Debug = "../../../calculTOF_outputs/RootOutputs/CoincidencesDebug.root";
TString filenameSingle_sv = "../../../calculTOF_outputs/RootOutputs/Single_sv.root";
TString filenameCoincidences_sv = "../../../calculTOF_outputs/RootOutputs/Coincidences_sv.root";



TString currentG4File = fileG4_csv;
TString currentGateFile = fileGate_c_EWC;
TString currentSRootFile = filenameSingle_sv;
TString currentCRootFile = filenameCoincidences_sv;

//display
TFile* f = TFile::Open(currentG4File);
TTree* Hits;
f->GetObject("Hits", Hits); //nom du NTuple, nom de l'arbre

TFile* outputFileS= new TFile(currentSRootFile,"recreate");
single* monSingle = new single(Hits);
monSingle->PrintAvailablePolicies();
monSingle->setPolicyToWinnerTakeAll();
monSingle->createTreeSingle(Hits,outputFileS);
outputFileS->Close();

TFile * fSG4 = TFile::Open(currentSRootFile);
TTree* Singles;
fSG4->GetObject("Singles", Singles);

TFile* outputFileC= new TFile(currentCRootFile,"recreate");
coincidences * mesCoincidences = new coincidences();
mesCoincidences->fillTreeCoincidences(Singles,outputFileC);
outputFileC->Close();
//
TApplication app("app", &argc, argv);

TString champ1 = "time";
TString champ2 = "time";
TString file1 = currentGateFile ;
TString file2 = currentSRootFile;
TString datatype ="Singles";
Double_t xmin = -400;
Double_t xmax = 400;
Int_t nBins = 100;

// TCanvas *c = compareTwoTrees( champ1, champ2,  file1,  file2,  datatype, xmin, xmax, nBins );

	//c->Divide(2,1);
	//c->cd(1);


		 datatype = "Singles";
		 TCanvas*c = compareGateG4timeT0( currentGateFile, currentSRootFile, datatype );
		//
		// TString field = "posX";
		// TCanvas*c1 = compareTwoTrees(field, field, currentGateFile,currentG4File,"Hits" );
		// TCanvas *c2 = compareDt_rand( currentGateFile,  currentG4File);

		//TCanvas * compareTwoTrees(TString champ1,TString champ2, TString file1, TString file2, TString datatype, Double_t xmin,Double_t xmax, Int_t nBins);

   	c->Modified(); c->Update();
   	TRootCanvas*rc = (TRootCanvas *)c->GetCanvasImp();
   	rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
app.Run();

	return 0;
}
