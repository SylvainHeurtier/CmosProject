// ********************************************************************
// *                       EventAction.cc                             *
// ********************************************************************
//
/// \file B1/src/EventAction.cc
/// \brief Implementation of the B1::EventAction class

#include "EventAction.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

#include "G4UnitsTable.hh"
//#include "MyAnalysis.hh"
#include "G4CsvAnalysisManager.hh"

#include "G4AnalysisManager.hh"

namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction* runAction)
: fRunAction(runAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* event)
{
  // initialisation per event
  //fEdep = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{
  // accumulate statistics in run action
  //fRunAction->AddEdep(fEdep);

  // get analysis manager
  //G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Fill histograms
  //analysisManager->FillH1(0, fEdep);
  
  //G4int nofHits = fHitsCollection->entries();
  //for ( G4int i=0; i<nofHits; i++ ) {
  //  analysisManager->FillH1(0, (*fHitsCollection)[i]);
  //	}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
