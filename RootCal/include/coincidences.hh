#ifndef COINCIDENCES_HH
#define COINCIDENCES_HH

#include "TTree.h"
#include "TString.h"
#include "TFile.h"

#include "structures.hh"


class coincidences{
private:
TTree * Coincidences = new TTree("coincidences","coincidences");

void processTwoSingles(s_Single &Single1,s_Single &Single2,s_Coincidence &c);




public:

coincidences();
~coincidences();

void fillTreeCoincidences (TTree * Singles,TFile* outputFile);

TTree * getTreeCoincidences() {return Coincidences;}

// void writeTree(TTree* treeToWrite,TString filename);
// Double_t distance(Double_t x1,Double_t x2,Double_t y1,Double_t y2,Double_t z1,Double_t z2);


};
#endif
