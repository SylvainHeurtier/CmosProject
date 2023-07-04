// ********************************************************************
// *                           RunAction.cc                           *
// ********************************************************************
/// \file B1/src/RunAction.cc
/// \brief Implementation of the B1::RunAction class

#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"

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
  //analysisManager->SetNtupleMerging(true);

  // Creating histograms

  // histogram 1
  analysisManager->CreateH1("Edep", "Energy deposit", 100, 0., 10*GeV);

  // Creating ntuples
  //
  // ntuple id = 0
  //analysisManager->CreateNtuple("HitPixel", "Pixel 1 hits");
  //analysisManager->CreateNtupleIColumn("Pixel");   // column id = 0
  //analysisManager->CreateNtupleDColumn("Edep");    // column id = 1
  //analysisManager->FinishNtuple();

  }

  //RunAction::~RunAction()
  //{}

  ////////////////////////////////////////////////////////////////////////////////
  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  ////////////////////////////////////////////////////////////////////////////////

  void RunAction::BeginOfRunAction(const G4Run*)
  {
  // Create analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);

  // Create directories 
  //analysisManager->SetHistoDirectoryName("histograms");
  //analysisManager->SetNtupleDirectoryName("ntuple");

  // Open an output file
  G4String fileName = "Output.csv";
  analysisManager->OpenFile(fileName);

  // Creating histograms
  //analysisManager->CreateH1("Edep","Energy deposit", 10, 0., 10*GeV);
  // inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  }

  ////////////////////////////////////////////////////////////////////////////////
  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  ////////////////////////////////////////////////////////////////////////////////


  void RunAction::EndOfRunAction(const G4Run* run)
  {

  // print histogram statistics
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  if ( analysisManager->GetH1(0) ) {
    G4cout <<"-------------> print histograms statistic \n"<< G4endl << "------------------------------------------------------------"<< G4endl << G4endl;
    
    G4cout << " Edep : mean = " << G4BestUnit(analysisManager->GetH1(0)->mean(), "Energy") 
               << " rms = " << G4BestUnit(analysisManager->GetH1(0)->rms(),  "Energy") << G4endl;
    G4cout <<"\n"<< G4endl << "------------------------------------------------------------"<< G4endl<< G4endl;
  }
  // save histograms 
  //
  analysisManager->Write();
  analysisManager->CloseFile();
  // complete cleanup
  //
  delete G4AnalysisManager::Instance(); 

  }

}




















  // Book histograms, ntuple
  //
  
  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in MyAnalysis.hh
//G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
//analysisManager->SetVerboseLevel(1);

  // Create directories 
  //analysisManager->SetHistoDirectoryName("histograms");
  //analysisManager->SetNtupleDirectoryName("ntuple");
  
  // Open an output file
//G4String fileName = "output.root";
//analysisManager->OpenFile(fileName);

  // Creating histograms
//analysisManager->CreateH1("Edep","Energy deposit", 100, 0., 800*MeV);
//analysisManager->CreateH1("Tlen","Track length", 100, 0., 100*mm);

  // inform the runManager to save random number seed
//G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // reset accumulables to their initial values
//G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
//accumulableManager->Reset();








//void RunAction::EndOfRunAction(const G4Run* run)
//  {
//  G4int nofEvents = run->GetNumberOfEvent();
//  if (nofEvents == 0) return;
//
//  // Merge accumulables
//  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
//  accumulableManager->Merge();
//
//  // Compute dose = total energy deposit in a run and its variance
//  //
//  G4double edep  = fEdep.GetValue();
//  G4double edep2 = fEdep2.GetValue();
//
//  G4double rms = edep2 - edep*edep/nofEvents;
//  if (rms > 0.) rms = std::sqrt(rms); else rms = 0.;
//
//  const auto detConstruction = static_cast<const DetectorConstruction*>(
//    G4RunManager::GetRunManager()->GetUserDetectorConstruction());
//  G4double mass = detConstruction->GetScoringVolume()->GetMass();
//  G4double dose = edep/mass;
//  G4double rmsDose = rms/mass;
//
//  // Run conditions
//  //  note: There is no primary generator action object for "master"
//  //        run manager for multi-threaded mode.
//  const auto generatorAction = static_cast<const PrimaryGeneratorAction*>(
//          G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
//  
//  G4String runCondition;
//  if (generatorAction)
//  {
//    const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
//    runCondition += particleGun->GetParticleDefinition()->GetParticleName();
//    runCondition += " of ";
//    G4double particleEnergy = particleGun->GetParticleEnergy();
//    runCondition += G4BestUnit(particleEnergy,"Energy");
//  }
//
//  // Print
//  //
//  if (IsMaster()) {
//    G4cout
//     << G4endl
//     << "--------------------End of Global Run-----------------------";
//  }
//  else {
//    G4cout
//     << G4endl
//     << "--------------------End of Local Run------------------------";
//  }
//
//  G4cout
//     << G4endl
//     << " The run consists of " << nofEvents << " "<< runCondition
//     << G4endl
//     << " Cumulated dose per run, in scoring volume : "
//     << G4BestUnit(dose,"Dose") << " rms = " << G4BestUnit(rmsDose,"Dose")
//     << G4endl
//     << "------------------------------------------------------------"
//     << G4endl
//     << G4endl;
//
//  // print histogram statistics
//  //
//  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
//
//  if ( analysisManager->GetH1(0) ) {
//    G4cout << "\n ----> print histograms statistic \n"<< G4endl
//    << "------------------------------------------------------------"<< G4endl
//    << G4endl;
//    
//    G4cout 
//       << " Edep : mean = " << G4BestUnit(analysisManager->GetH1(0)->mean(), "Energy") 
//               << " rms = " << G4BestUnit(analysisManager->GetH1(0)->rms(),  "Energy") 
//               << G4endl;
//  }
//  // save histograms 
//  //
//  analysisManager->Write();
//  analysisManager->CloseFile();
//  // complete cleanup
//  //
//  delete G4AnalysisManager::Instance(); 
//
//  }