#include <iostream>
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4ProductionCutsTable.hh"
#include "CLHEP/Random/RandomEngine.h"
#include "CLHEP/Random/Random.h"
#include "G4OpticalPhysics.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "FTFP_BERT.hh"


#include "G4RunManagerFactory.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"
#include "detector.hh"
//******************************************************************************
//Fonction principale (main) qui appelle toutes les autres
//décrit la façon dont on lance la simu en ligne de commande
//******************************************************************************

namespace
{
  void PrintUsage()
  {
    G4cerr << " Usage: " << G4endl;
    G4cerr << " sim [-m macro ] [-p physList ] [-u UIsession] [-g GDMLfile] [-t nThreads] [-n nbOfEvents]" << G4endl;
    G4cerr << " note: -t option is used only in multi-threaded mode." << G4endl;
    G4cerr << G4endl;
  }
}

//******************************************************************************

int main(int argc, char** argv)
{

  // Evaluate arguments
  if ( argc > 9 )
  {
    PrintUsage();
    return 1;
  }

  G4String macro;
  G4String session;
  G4String physicsListName;
  G4String gdmlFileName;
  G4int nofThreads = 0;
  G4bool noUI = false;
  int numberOfEvent = 1000;


  for ( G4int i=1; i<argc; i=i+2 )
  {
    if      ( G4String(argv[i]) == "-m" ) macro = argv[i+1];
    else if ( G4String(argv[i]) == "-u" ) session = argv[i+1];
    else if ( G4String(argv[i]) == "-p" ) physicsListName = argv[i+1];
    else if ( G4String(argv[i]) == "-g" ) gdmlFileName = argv[i+1];
    else if ( G4String(argv[i]) == "-t" ) nofThreads = G4UIcommand::ConvertToInt(argv[i+1]);
    else if ( G4String(argv[i]) == "-n" ) noUI = true, numberOfEvent = atoi(argv[i+1]);
    else
    {
      PrintUsage();
      return 1;
    }
  }

  // Construct the default run manager
  auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

  if ( nofThreads > 0 ) {runManager->SetNumberOfThreads(nofThreads);}

  runManager->SetUserInitialization(new MyDetectorConstruction());
  runManager->SetUserInitialization(new MyPhysicsList());
  runManager->SetUserInitialization(new MyActionInitialization());
  runManager->Initialize();

  if (noUI)
  {
    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    // UImanager->ApplyCommand("/tracking/verbose 1");
    runManager->BeamOn(numberOfEvent);
    delete runManager;
  }

  else
  {
  // Detect interactive mode (if no arguments) and define UI session
  G4UIExecutive* ui = nullptr;
  G4VisManager *visManager = new G4VisExecutive();
  visManager->Initialize();
  G4UImanager *UImanager = G4UImanager::GetUIpointer();

  if ( ! macro.size() )
  {
    ui = new G4UIExecutive(argc, argv, session);
  }

  if ( macro.size() )// batch mode
  {
    G4String command = "/control/execute ";
    UImanager->ApplyCommand(command+macro);
  }
  else // interactive mode : define UI session
  {
    //UImanager->ApplyCommand("/run/verbose 1");
    //UImanager->ApplyCommand("/event/verbose 1");
    //UImanager->ApplyCommand("/tracking/verbose 1");
    UImanager->ApplyCommand("/control/execute ../macros/vis.mac");
    ui->SessionStart();
    delete ui;
  }

  delete visManager;
  delete runManager;
}


  return 0;
}

//******************************************************************************
//******************************************************************************
