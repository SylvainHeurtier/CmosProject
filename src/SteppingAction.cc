// ********************************************************************
// *                      SteppingAction.cc                           *
// ********************************************************************
//
/// \file B1/src/SteppingAction.cc
/// \brief Implementation of the B1::SteppingAction class

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction):G4UserSteppingAction(),
    fEventAction(eventAction)
    {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}






//********************************************************************************//
// Original du code de void SteppingAction::UserSteppingAction(const G4Step* step)
//********************************************************************************//
//  if (!fScoringVolume) {
//    const auto detConstruction = static_cast<const DetectorConstruction*>(
//      G4RunManager::GetRunManager()->GetUserDetectorConstruction());
//    fScoringVolume = detConstruction->GetScoringVolume();
//  }
//
//  // get volume of the current step
//  G4LogicalVolume* volume
//    = step->GetPreStepPoint()->GetTouchableHandle()
//      ->GetVolume()->GetLogicalVolume();
//
//  // check if we are in scoring volume
//  if (volume != fScoringVolume) return;
//
//  // collect energy deposited in this step
//  G4double edepStep = step->GetTotalEnergyDeposit();
//  fEventAction->AddEdep(edepStep);
//********************************************************************************//
