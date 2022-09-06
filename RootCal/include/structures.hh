#ifndef STRUCTURES_HH
#define STRUCTURES_HH


typedef struct s_Hit  {
  Float_t X, Y, Z,edep;
  Double_t time; //edep : pondération (éventuelle) du centroïde
  Double_t sourcePosX,sourcePosY,sourcePosZ;
	Int_t eventID;
	Int_t trackID;
  Int_t rsectorID,moduleID,submoduleID,crystalID,layerID;
  Int_t hitNumberTrack1, hitNumberTrack2;
  Char_t particleName;
}s_Hit;
typedef struct s_Single {
  Float_t X, Y, Z, edep;
  Double_t time; //edep : pondération (éventuelle) du centroïde
  Double_t sourcePosX,sourcePosY,sourcePosZ;
  Int_t eventID;
	Int_t trackID;
  Int_t rsectorID,moduleID,submoduleID,crystalID,layerID;
  bool isInCoincidence;
}s_Single;

typedef struct s_Coincidence  {
  Double_t time1, time2, dt;
  Float_t X1, X2, Y1, Y2, Z1, Z2,edep1, edep2;
  Int_t rsectorID1,moduleID1,submoduleID1,crystalID1,layerID1;
  Int_t rsectorID2,moduleID2,submoduleID2,crystalID2,layerID2;
  Double_t sourcePosX1,sourcePosY1,sourcePosZ1,sourcePosX2,sourcePosY2,sourcePosZ2;
}s_Coincidence;

#endif
