// ********************************************************************
// *                           RunAction.cc                           *
// ********************************************************************
/// \file B1/src/RunAction.cc
/// \brief Implementation of the B1::RunAction class


#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
// #include "Run.hh"

//#include "MyAnalysis.hh"
#include "G4CsvAnalysisManager.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

namespace B1
{

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  RunAction::RunAction()
  {
 // Create analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);

  // Creating histograms
  // analysisManager->CreateH1("Edep","Energy deposit", 10, 0., 10*GeV);

  // Creating ntuples
  //
  // chip id = 0
  analysisManager->CreateNtuple("Chamber1", "Chamber 1 hits");
  analysisManager->CreateNtupleIColumn("Layer");   // column id = 0
  analysisManager->CreateNtupleDColumn("Xpos");    // column id = 1
  analysisManager->CreateNtupleDColumn("Ypos");    // column id = 2
  analysisManager->CreateNtupleDColumn("Zpos");    // column id = 3
  analysisManager->CreateNtupleDColumn("Edep");    // column id = 3
  analysisManager->FinishNtuple();
  
  }

  ////////////////////////////////////////////////////////////////////////////////
  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  ////////////////////////////////////////////////////////////////////////////////

  void RunAction::BeginOfRunAction(const G4Run*)
  {
    // Get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();

    // Open an output file
    G4String fileName = "output.root";
    analysisManager->OpenFile(fileName);
    G4cout << "Using " << analysisManager->GetType() << G4endl;
  }

  ////////////////////////////////////////////////////////////////////////////////
  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  ////////////////////////////////////////////////////////////////////////////////


  void RunAction::EndOfRunAction(const G4Run* run)
  {
  auto analysisManager = G4AnalysisManager::Instance();
  // save histograms
  analysisManager->Write();
  analysisManager->CloseFile();
  }
}
