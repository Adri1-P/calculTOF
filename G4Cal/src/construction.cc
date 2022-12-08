#include "construction.hh"
#include "DebugDetector.hh"
#include "TOFDebugDetector.hh"
#include "TOFDebugDetector2.hh"
#include "TOFDebugDetector50.hh"
#include "ScanGE.hh"
#include "ClearMindDetector.hh"

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

	//construction aerogel

	G4Material *SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2); //nom, densité, nombre éléments
	SiO2->AddElement(nist->FindOrBuildElement("Si"),1); // élément, quantité
	SiO2->AddElement(nist->FindOrBuildElement("O"),2);

	G4Material *H2O = new G4Material("H2O", 1.000*g/cm3, 2);
	H2O->AddElement(nist->FindOrBuildElement("O"),1);
	H2O->AddElement(nist->FindOrBuildElement("H"),2);

	C = nist->FindOrBuildElement("C");

	Aerogel = new G4Material ("Aerogel", 0.200*g/cm3, 3);
	Aerogel->AddMaterial(SiO2, 62.5*perCent);
	Aerogel->AddMaterial(H2O, 37.4*perCent);
	Aerogel->AddElement(C, 0.1*perCent);

	G4double rindexAerogel[2] = {1.1, 1.1};
	G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
	mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2); //2 valeurs d'indice

	Aerogel->SetMaterialPropertiesTable(mptAerogel);

	PbW04_Black = new G4Material("PbW04_Black", 8.28*g/cm3, 3);
	PbW04_Black-> AddElement(nist-> FindOrBuildElement("Pb"),1);
	PbW04_Black-> AddElement(nist-> FindOrBuildElement("W"),1);
	PbW04_Black-> AddElement(nist-> FindOrBuildElement("O"),4);

	// Pour vérifier le PbWO4 :
	// G4NistManager* man = G4NistManager::Instance();
	// G4Material* PbWO4  = man->FindOrBuildMaterial("G4_PbWO4");

	PbW04_Y = new G4Material("PbW04_Y", 8.28*g/cm3, 3); //pas de différence avec le précédent ?
	PbW04_Y-> AddElement(nist-> FindOrBuildElement("Pb"),1);
	PbW04_Y-> AddElement(nist-> FindOrBuildElement("W"),1);
	PbW04_Y-> AddElement(nist-> FindOrBuildElement("O"),4);

	Bialkali_Bleu = new G4Material("Bialkali_Bleu", 2.*g/cm3, 3);
	Bialkali_Bleu-> AddElement(nist-> FindOrBuildElement("K"),2);
	Bialkali_Bleu-> AddElement(nist-> FindOrBuildElement("Cs"),1);
	Bialkali_Bleu-> AddElement(nist-> FindOrBuildElement("Sb"),1);


	G4double PbW04Y_energy_RINDEX[2] = {300000.*eV,3.*eV};
	G4double PbW04Y_value_RINDEX[2] = {1.4,1.4};
	G4double PbW04Y_energy_FASTCOMPONENT = 2.95167*eV;
	G4double PbW04Y_value_FASTCOMPONENT = 1;
	G4double PbW04Y_energy_ABSLENGTH[2] = {1.84*eV, 4.08*eV};
	G4double PbW04Y_value_ABSLENGTH[2] = {50.*nm,50.*nm};
	G4MaterialPropertiesTable *mptPbW04_Y = new G4MaterialPropertiesTable();
	mptPbW04_Y->AddProperty("RINDEX", PbW04Y_energy_RINDEX, PbW04Y_value_RINDEX,2);
	mptPbW04_Y->AddConstProperty("SCINTILLATIONYIELD", 26000.*MeV); //Note : même valeur que pour le LSO ?
	mptPbW04_Y->AddConstProperty("RESOLUTIONSCALE", 4.41);
	mptPbW04_Y->AddConstProperty("FASTTIMECONSTANT", 40.*ns);
	mptPbW04_Y->AddConstProperty("YIELDRATIO", 1.);
	mptPbW04_Y->AddProperty("FASTCOMPONENT", &PbW04Y_energy_FASTCOMPONENT,&PbW04Y_value_FASTCOMPONENT,1); //un tableau à une case, c'est l'adresse d'une variable
	mptPbW04_Y->AddProperty("ABSLENGTH", PbW04Y_energy_ABSLENGTH,PbW04Y_value_ABSLENGTH,2);
	PbW04_Y->SetMaterialPropertiesTable(mptPbW04_Y);


	G4double PbW04Black_value_RINDEX[17] = {2.196275,  2.198392,  2.201643,  2.206028,  2.211547,  2.2182,  2.225987,  2.234908,  2.244963,  2.256152,  2.268475,  2.281932,  2.296523,  2.312248,  2.329107,  2.3471,  2.6};
	G4double *PbW04Black_energy_RINDEX = new G4double[17];
	int i = 0;
	for (i = 0; i<16;i++)
	{
		 PbW04Black_energy_RINDEX[i] = (1.5 + double(i)/10.) *eV ;
  }
	PbW04Black_energy_RINDEX[i] = 4.0 *eV;
	G4double PbW04Black_energy_ABSLENGTH[2] = {1.50*eV, 4.0*eV};
	G4double PbW04Black_value_ABSLENGTH[2] = {5.*nm,10.*nm};
	G4MaterialPropertiesTable *mptPbW04_Black = new G4MaterialPropertiesTable();
	mptPbW04_Black->AddProperty("RINDEX", PbW04Black_energy_RINDEX, PbW04Black_value_RINDEX,17);
	mptPbW04_Black->AddProperty("ABSLENGTH", PbW04Black_energy_ABSLENGTH,PbW04Black_value_ABSLENGTH,2);
	PbW04_Black->SetMaterialPropertiesTable(mptPbW04_Black);

G4double BialkaliBleu_energy_RINDEX[23] = {1.5*eV,  1.823203819*eV,  1.864328717*eV,  1.907351688*eV,  1.952407239*eV,  1.999642898*eV,  2.049220822*eV,  2.101319656*eV,  2.156136691*eV,  2.213890352*eV,  2.274823114*eV,  2.3392049*eV,  2.407337082*eV,  2.479557194*eV,  2.55624453*eV,  2.637826802*eV,  2.724788125*eV,  2.81767863*eV,  2.917126111*eV,  3.023850237*eV,  3.138679993*eV,  3.262575255*eV,  4.0*eV};
G4double BialkaliBleu_value_RINDEX[23] = {2.96,  2.96,  2.95,  2.95,  2.95,  2.96,  2.98,  3.01,  3.06,  3.12,  3.2,  3.26,  3.09,  3,  3,  3,  2.87,  2.7,  2.61,  2.38,  2.18,  1.92,  1.92};
G4double BialkaliBleu_energy_ABSLENGTH[23] = {1.5*eV,  1.823203819*eV,  1.864328717*eV,  1.907351688*eV,  1.952407239*eV,  1.999642898*eV,  2.049220822*eV,  2.101319656*eV,  2.156136691*eV,  2.213890352*eV,  2.274823114*eV,  2.3392049*eV,  2.407337082*eV,  2.479557194*eV,  2.55624453*eV,  2.637826802*eV,  2.724788125*eV,  2.81767863*eV,  2.917126111*eV,  3.023850237*eV,  3.138679993*eV,  3.262575255*eV,  4.0*eV};
G4double BialkaliBleu_value_ABSLENGTH[23] = {200.0*nm,  163.9774367*nm,  155.6438083*nm,  152.1330457*nm,  144.3759322*nm,  133.3457216*nm,  126.695415*nm,  111.7871391*nm,  99.47160682*nm,  84.08166011*nm,  68.84066758*nm,  49.04181546*nm,  39.03076382*nm,  37.53645541*nm,  34.77025536*nm,  27.91143594*nm,  25.14421173*nm,  23.3426704*nm,  22.10480152*nm,  19.07993394*nm,  18.59942471*nm,  17.89311744*nm,  14.12614535*nm};
G4MaterialPropertiesTable *mptBialkali_bleu = new G4MaterialPropertiesTable();
mptBialkali_bleu->AddProperty("RINDEX", BialkaliBleu_energy_RINDEX, BialkaliBleu_value_RINDEX,23);
mptBialkali_bleu->AddProperty("ABSLENGTH", BialkaliBleu_energy_ABSLENGTH,BialkaliBleu_value_ABSLENGTH,23);
Bialkali_Bleu->SetMaterialPropertiesTable(mptBialkali_bleu);
}

//******************************************************************************

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	//ici on instancie la géométrie complète.
	//voir dans les classes d'en-tête quelles structures sont disponibles
	//Il suffit d'instancier la classe
	//et éventuellement changer les arguments de la méthode Construct
	//si on veut changer de setup.

	solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);// x/2,y/2,z/2, en mètres
	logicWorld = new G4LogicalVolume(solidWorld, worldMat,"logicWorld");
	physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);

	CMdetector *scanner = new CMdetector();
	scanner->Construct(logicWorld,PbW04_Black,PbW04_Y,Bialkali_Bleu); //pas le material
	// scanner->Construct(logicWorld,Aerogel,Aerogel,Aerogel);

	this->SetScoringVolumes(scanner->getTheScoringVolumes());
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

	int i = 0;
	while (fScoringVolumes[i] != NULL)
	{
		fScoringVolumes[i]->SetSensitiveDetector(sensDet);
		i++;
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
