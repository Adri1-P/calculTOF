#include "ClearMindDetector.hh"
#include "MetaDetector.hh"
CMdetector::CMdetector()
{	G4cout<< "CMdetector" << G4endl;}
CMdetector::~CMdetector()
{	G4cout<< "~CMdetector" << G4endl;
}

void CMdetector::Construct(G4LogicalVolume*logicWorld, G4Material* PbW04_Black,G4Material* PbW04_Y,G4Material* Bialkali_Bleu)
{
	//a un équivalent dans Gate. C'est un simple cristal de PbWO4 à 30cm du centre sur l'axe x.
  G4double Rmin = 30.0*cm;

	G4double x = 20.0*0.5*mm;
	G4double y = 100.0*0.5*mm;
	G4double z = 100.0*0.5*mm;


	G4Box * sCrystal = new G4Box("sCrystal", x,y,z);
	G4LogicalVolume *lCrystal = new G4LogicalVolume(sCrystal,PbW04_Y,"lCrystal");

	G4VPhysicalVolume *pCrystal = new G4PVPlacement(0, G4ThreeVector(Rmin,0.,0.), lCrystal,"pCrystal",logicWorld,false,0,true);
  pCrystal = new G4PVPlacement(0, G4ThreeVector(-Rmin,0.,0.), lCrystal,"pCrystal",logicWorld,false,1,true);
	this->SetScoringVolume(lCrystal);



  G4double xCoating = 1000.0*0.5*nm;
  G4double dxC = -10.0005*mm;


	G4Box * sCoating = new G4Box("sCoating", xCoating,y,z);
	G4LogicalVolume *lCoating = new G4LogicalVolume(sCoating,PbW04_Black,"lCoating");

	G4VPhysicalVolume *pCoating = new G4PVPlacement(0, G4ThreeVector(Rmin + dxC,0.,0.), lCoating,"pCoating",logicWorld,false,0,true);
  pCoating = new G4PVPlacement(0, G4ThreeVector(-(Rmin + dxC),0.,0.), lCoating,"pCoating",logicWorld,false,1,true);



  G4double xPhotElec = 25.0*0.5*nm;
  G4double dxPE = 10.0000125*mm;


	G4Box * sPhotElec = new G4Box("sPhotElec", xPhotElec,y,z);
	G4LogicalVolume *lPhotElec = new G4LogicalVolume(sPhotElec,Bialkali_Bleu,"lPhotElec");

	G4VPhysicalVolume *pPhotElec = new G4PVPlacement(0, G4ThreeVector(Rmin + dxPE ,0.,0.), lPhotElec,"pPhotElec",logicWorld,false,0,true);
  pPhotElec = new G4PVPlacement(0, G4ThreeVector(-(Rmin + dxPE) ,0.,0.), lPhotElec,"pPhotElec",logicWorld,false,0,true);

  allScoringVolumes[0] = {lCoating};
  allScoringVolumes[1] = {lPhotElec};
  allScoringVolumes[2] = {lCrystal};



	G4cout<< "CMdetector::Construct" << G4endl;

}
