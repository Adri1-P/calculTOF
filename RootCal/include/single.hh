#include "TTree.h"
#include "TFile.h"
#include "structures.hh"



class single{

private:
	TTree* Single = new TTree("Singles","Singles");
	TString policy = "centroid";



void fillTreeSingle_b2b(TTree* Hits, TFile* outputFile);
void processOneHit_b2b_WTA(s_Hit &aHit, s_Single &Single1,s_Single &Single2, Float_t &energieMax1, Float_t &energieMax2, bool &gamma1, bool &gamma2);
void processOneHit_b2b_EWC(s_Hit &aHit, s_Single &Single1,s_Single &Single2,bool &gamma1, bool &gamma2);
void processOneHit_b2b_FH(s_Hit &aHit,s_Single &Single1,s_Single &Single2,bool &gamma1,bool &gamma2);

void fillTreeSingle_positron(TTree* Hits, TString filename);
// void fillTreeSingle_b2b_v2(TTree* Hits, TString filename);

//distance entre deux points
Double_t distance(Double_t x1,Double_t x2,Double_t y1,Double_t y2,Double_t z1,Double_t z2);




public:
	single(TTree* Hits);
	~single();


void createTreeSingle(TTree* Hits, TFile* outputFile);

void setPolicyToCentroid() {policy = "centroid"; printf("single policy set to centroid\n");}
void setPolicyToWinnerTakeAll() {policy = "winnerTakeAll"; printf("single policy set to winnerTakeAll\n");}
void setPolicyToFirstHit() {policy = "firstHit"; printf("single policy set to firstHit\n");}

TTree * getSingleTree() {return Single;}
TString getCurrentPolicy() {return policy;}

void PrintAvailablePolicies();

// void blurMyBranch(TTree* tree, Double_t sigma, TString branchName);
// void writeTree(TTree* arbreAEcrire,TString filename);
};
