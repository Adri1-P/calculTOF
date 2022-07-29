#include "construction.hh"
#include "DebugDetector.hh"
#include "TOFDebugDetector.hh"
#include "TOFDebugDetector2.hh"
#include "TOFDebugDetector50.hh"
#include "ScanGE.hh"

#include "G4SDManager.hh"

//******************************************************************************
//******************************************************************************

MyDetectorConstruction::MyDetectorConstruction()
{
//méthode dans laquelle on définit tous les matériaux qu'on veut utiliser à travers la méhode DefineMaterials.
//il y a aussi un passage avec des messengers qu'on peut réutiliser.

	//Ces lignes ajoutent des commandes utilisables dans l'interface graphique...
	fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");

	fMessenger->DeclareProperty("nCols", nCols, "Number of columns");
	fMessenger->DeclareProperty("nRows", nRows, "Number of rows");
	fMessenger->DeclareProperty("eCristal",e, "épaisseur (1e dim) des cristaux");
	fMessenger->DeclareProperty("eCristal",ly, "largeur (2e dim) des cristaux");

	nCols = 100;
	nRows = 100;

	e = 5*mm;
	ly = 5*mm;
	//...elles sont pour le moment inutiles

	DefineMaterials();

	 xWorld = 2*m;
	 yWorld = 2*m;
	 zWorld = 2*m;
}

//******************************************************************************

MyDetectorConstruction::~MyDetectorConstruction(){}

//******************************************************************************

void MyDetectorConstruction::DefineMaterials()
{
//c'est ici qu'on donne toutes les propriétés de tous les matériaux qu'on veut utiliser.

	G4NistManager *nist = G4NistManager::Instance();

	//world = air
	G4double energy[2] = {1.239841939*eV/0.2, 1.239841939*eV/0.9}; //conversion moment du photon -> 0.2 : blue light, 0.9 : red light?
	G4double rindexWorld[2] = {1.0, 1.0};
	G4MaterialPropertiesTable * mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
	worldMat = nist->FindOrBuildMaterial("G4_AIR");
	worldMat->SetMaterialPropertiesTable(mptWorld);

	//cristaux
	G4double fractionmass;
	LYSO_GE = new G4Material("LYSO_GE", 7.21*g/cm3, 4);
	LYSO_GE->AddElement(nist-> FindOrBuildElement("Lu"),fractionmass= 72.99*perCent);
	LYSO_GE->AddElement(nist-> FindOrBuildElement("Y"),fractionmass= 2.79*perCent);
	LYSO_GE->AddElement(nist-> FindOrBuildElement("Si"),fractionmass= 6.28*perCent);
	LYSO_GE->AddElement(nist-> FindOrBuildElement("O"),fractionmass= 17.94*perCent);

	LSO = new G4Material("LSO", 7.4*g/cm3, 3);
	LSO->AddElement(nist-> FindOrBuildElement("Lu"),2);
	LSO->AddElement(nist-> FindOrBuildElement("Si"),1);
	LSO->AddElement(nist-> FindOrBuildElement("O"),5);
}

//******************************************************************************

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	//ici on instantie la géométrie complète.
	//voir dans les classes d'en-tête quelles structures sont disponibles
	//Il suffit d'instancier la classe
	//et éventuellement changer les arguments de la méthode Construct
	//si on veut changer de setup.

	solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);// x/2,y/2,z/2, en mètres
	logicWorld = new G4LogicalVolume(solidWorld, worldMat,"logicWorld");
	physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);

	DebugDetector *scanner = new DebugDetector();
	scanner->Construct(logicWorld,LSO);
	this->SetScoringVolume(scanner->GetScoringVolume());

	return physWorld;
}

//******************************************************************************

void MyDetectorConstruction::ConstructSDandField()
{
//Ici, on définit ce que doit être le sensitive detector, c'est à dire le volume qui va
//être utilisé pour compter les hits dans detector.cc
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

  	G4SDManager::GetSDMpointer()->AddNewDetector(sensDet); //sinon initialize de detector.cc refuse de coopérer

	if (fScoringVolume != NULL)
	{
		fScoringVolume->SetSensitiveDetector(sensDet);
	}
}

//******************************************************************************

void MyDetectorConstruction::GenerateCastorOptionFile(G4float scanner_radius, // radius in mm (from isocenter to crystal surface)
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
                           G4float crystal_size_axial)
{
  G4cout<<"!!!!!!!! it  works!!!!! "<<G4endl;
  G4cout<< "scanner_radius "  << scanner_radius<<G4endl;
  G4cout<< "nb_rsectors "  << nb_rsectors<<G4endl;
  G4cout<< "nb_trans_mod " << nb_trans_mod<<G4endl;
  G4cout<< "nb_axial_mod " << nb_axial_mod<<G4endl;
  G4cout<< "nb_trans_submod " << nb_trans_submod<<G4endl;
  G4cout<< "nb_axial_submod " << nb_axial_submod<<G4endl;
  G4cout<< "nb_trans_crystal " << nb_trans_crystal<<G4endl;
  G4cout<< "nb_axial_crystal " << nb_axial_crystal<<G4endl;
  // Gaps between scanner elements
  G4cout<< "gap_trans_mod " << gap_trans_mod<<G4endl;
  G4cout<< "gap_axial_mod " << gap_axial_mod<<G4endl;
  G4cout<< "gap_trans_submod " << gap_trans_submod<<G4endl;
  G4cout<< "gap_axial_submod " << gap_axial_submod<<G4endl;
  G4cout<< "gap_trans_crystal " << gap_trans_crystal<<G4endl;
  G4cout<< "gap_axial_crystal " << gap_axial_crystal<<G4endl;
  // crystal dimensions (mm)
  G4cout<< "crystal_size_depth " << crystal_size_depth<<G4endl;
  G4cout<< "crystal_size_trans " << crystal_size_trans<<G4endl;
  G4cout<< "crystal_size_axial " << crystal_size_axial<<G4endl;


  std::ofstream myfile;
  myfile.open ("G4toCastorOptFile.txt");
  myfile << scanner_radius<<'\n';
  myfile << nb_rsectors<<'\n';
  myfile << nb_trans_mod<<'\n';
  myfile << nb_axial_mod<<'\n';
  myfile << nb_trans_submod<<'\n';
  myfile << nb_axial_submod<<'\n';
  myfile << nb_trans_crystal<<'\n';
  myfile << nb_axial_crystal<<'\n';
  // Gaps between scanner elements
  myfile << gap_trans_mod<<'\n';
  myfile << gap_axial_mod<<'\n';
  myfile << gap_trans_submod<<'\n';
  myfile << gap_axial_submod<<'\n';
  myfile << gap_trans_crystal<<'\n';
  myfile << gap_axial_crystal<<'\n';
  // crystal dimensions (mm)
  myfile << crystal_size_depth<<'\n';
  myfile << crystal_size_trans<<'\n';
  myfile << crystal_size_axial<<'\n';
  myfile.close();
}
//******************************************************************************
//******************************************************************************
