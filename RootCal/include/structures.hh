#ifndef STRUCTURES_HH
#define STRUCTURES_HH


typedef struct s_Hit  {
  Double_t X, Y, Z, time, edep; //edep : pondération (éventuelle) du centroïde
	Int_t eventID;
	Int_t trackID;
  Int_t rsectorID,moduleID,submoduleID,crystalID,layerID;
  Int_t hitNumberTrack1, hitNumberTrack2;
  Char_t particleName;
}s_Hit;
typedef struct s_Single {
  Double_t X, Y, Z, time, edep; //edep : pondération (éventuelle) du centroïde
	Int_t eventID;
	Int_t trackID;
  Int_t rsectorID,moduleID,submoduleID,crystalID,layerID;
  bool isInCoincidence;
}s_Single;

typedef struct s_Coincidence  {
  Double_t edep1, edep2, X1, X2, time1, time2, Y1, Y2, Z1, Z2, dt;
}s_Coincidence;

#endif
