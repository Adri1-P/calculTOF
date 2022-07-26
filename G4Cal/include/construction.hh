#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4GenericMessenger.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"

#include "detector.hh"


class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public :
	MyDetectorConstruction();
	~MyDetectorConstruction();

	virtual G4VPhysicalVolume *Construct();

	G4LogicalVolume *GetScoringVolume() const {return fScoringVolume;} //utilisé pour les cuts.
	void SetScoringVolume ( G4LogicalVolume * lV)  {fScoringVolume = lV;}
	G4int GetCristalWidth() const {return e;}
	void GenerateCastorOptionFile(G4float scanner_radius, // radius in mm (from isocenter to cry
//stal surface)
													 //nb scanner elements
													 G4int nb_rsectors,
													 G4int nb_trans_mod,
													 G4int nb_axial_mod,
													 G4int nb_trans_submod,
													 G4int nb_axial_submod,
													 G4int nb_trans_crystal,
													 G4int nb_axial_crystal,
													 // Gaps between scanner elements
													 G4float gap_trans_mod,
													 G4float gap_axial_mod,
													 G4float gap_trans_submod,
													 G4float gap_axial_submod,
													 G4float gap_trans_crystal,
													 G4float gap_axial_crystal,
													 // crystal dimensions (mm)
													 G4float crystal_size_depth,
													 G4float crystal_size_trans,
													 G4float crystal_size_axial);

private :

	//pour le world : don't remove
	G4Box *solidWorld;
	G4LogicalVolume *logicWorld;
	G4VPhysicalVolume *physWorld;

	//pour les cuts
	G4LogicalVolume *fScoringVolume;

	//matériaux
	G4Material *SiO2, *H2O, *Aerogel, *worldMat, *LYSO_GE,*LSO;
	G4Element *C;

	//messengers
	G4double xWorld, yWorld, zWorld,e,ly;
	G4int nCols,nRows;
	G4GenericMessenger *fMessenger;

	virtual void ConstructSDandField();
	void DefineMaterials();
	void ConstructScintillator();
	void ConstructScanGE_OnlyCrystals();
	void ConstructScanGE();
	void ConstructTOFTestStructure();
	void ConstructDebugGeom();

};

#endif
