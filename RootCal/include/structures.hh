#ifndef STRUCTURES_HH
#define STRUCTURES_HH


typedef struct s_Hit  {
  Double_t X, Y, Z, time, edep; //edep : pondération (éventuelle) du centroïde
	Int_t eventID;
	Int_t trackID;
  Int_t rsectorID,moduleID,submoduleID,crystalID,layerID;
  Char_t particleName;
}s_Hit;
typedef struct s_Single {
  Double_t X, Y, Z, time, edep; //edep : pondération (éventuelle) du centroïde
	Int_t eventID;
	Int_t trackID;
  Int_t rsectorID,moduleID,submoduleID,crystalID,layerID;
}s_Single;

typedef struct s_Coincidence  {
  Double_t energie, energie1, energie2, globalPosX1,globalPosX2, temps1,temps2, globalPosY1,globalPosY2, globalPosZ1, globalPosZ2, dt;
	Double_t x1, y1, z1, x2, y2, z2;
}s_Coincidence;

#endif
