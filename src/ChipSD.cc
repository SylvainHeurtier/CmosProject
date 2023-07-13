//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id$
//
/// \file ChipSD.cc
/// \brief Implementation of the ChipSD class
//

#include "ChipSD.hh"

#include "G4AnalysisManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4VTouchable.hh"
#include "G4Step.hh"
#include "G4ios.hh"

namespace ED
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ChipSD::ChipSD(const G4String& name, G4int ntupleId)
 : G4VSensitiveDetector(name), fNtupleId(ntupleId)
{
  G4String hcName = SensitiveDetectorName + "HitsCollection";
  collectionName.insert(hcName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ChipSD::~ChipSD()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ChipSD::Initialize(G4HCofThisEvent* hce)
{
  G4String hcName = SensitiveDetectorName + "HitsCollection";

  fHitsCollection = new ChipHitsCollection(SensitiveDetectorName, hcName);

  G4int hcID
    = G4SDManager::GetSDMpointer()->GetCollectionID(hcName);
  hce->AddHitsCollection( hcID, fHitsCollection );

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool ChipSD::ProcessHits(G4Step* step,
                                    G4TouchableHistory* /*history*/)
{
  // Change the following lines to get the charge of the tracked particle
  G4double charge = step->GetTrack()->GetDefinition()->GetPDGCharge();
  if ( charge == 0. ) return false;

  // Create new hit
  ChipHit* newHit = new ChipHit();

  // Time
  G4StepPoint* preStepPoint = step->GetPreStepPoint();
  G4double time = preStepPoint->GetGlobalTime();
  newHit->SetTime(time);

  // Position
  G4ThreeVector position = preStepPoint->GetPosition();
  newHit->SetPosition(position);

  // Layer number
  // = copy number of mother volume
  const G4VTouchable* touchable = preStepPoint->GetTouchable();
  G4int copyNo = touchable->GetCopyNumber(1);
  newHit->SetLayerNumber(copyNo);

  // Add hit in the collection
  fHitsCollection->insert(newHit);

  // energy deposit
  G4double edep = step->GetTotalEnergyDeposit();

  // Name particle
  G4String NameParticle = step->GetTrack()->GetDefinition()->GetParticleName();
  std::cout << "Name Particle :" << NameParticle << std::endl;
  G4int NumParticle;
  if (NameParticle=="pi+")
    NumParticle=6;
  else if (NameParticle=="pi-")
    NumParticle=-6;
  else if (NameParticle=="e+")
    NumParticle=2;
  else if (NameParticle=="e-")
    NumParticle=-2;
  else if (NameParticle=="mu+")
    NumParticle=3;
  else if (NameParticle=="mu-")
    NumParticle=-3;
  else if (NameParticle=="kaon+")
    NumParticle=4;
  else if (NameParticle=="kaon-")
    NumParticle=-4;
  else if (NameParticle=="proton")
    NumParticle=1;
  else if (NameParticle=="anti_proton")
    NumParticle=-1;
  else
    NumParticle=0;

  //The GPD code
  G4int Nbcode = step->GetTrack()->GetDynamicParticle()->GetPDGcode();
  std::cout << "The PDG code :" << Nbcode << std::endl;

  //Charge
  G4double ChargeParticle = step->GetTrack()->GetDynamicParticle()->GetCharge();

  //
  //G4int copyNo_pixel = step->GetTrack()->GetVolume()->GetLogicalVolume()->GetDaughter()->GetCopyNo();
  G4int copyNo_pixel = step->GetTrack()->GetVolume()->GetCopyNo();

  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillNtupleIColumn(fNtupleId, 0, copyNo_pixel);
  analysisManager->FillNtupleDColumn(fNtupleId, 1, position.x());
  analysisManager->FillNtupleDColumn(fNtupleId, 2, position.y());
  analysisManager->FillNtupleDColumn(fNtupleId, 3, position.z());
  analysisManager->FillNtupleDColumn(fNtupleId, 4, edep);
  //analysisManager->FillNtupleSColumn(fNtupleId, 5, NameParticle);
  //analysisManager->FillNtupleIColumn(fNtupleId, 5, NumParticle);
  //analysisManager->FillNtupleIColumn(fNtupleId, 5, Nbcode);
  //analysisManager->FillNtupleDColumn(fNtupleId, 6, ChargeParticle);
  analysisManager->AddNtupleRow(fNtupleId);
  
  /*
  analysisManager->FillH1( 0, position.x());
  analysisManager->FillH1( 1, position.y());
  analysisManager->FillH1( 2, position.z());
  analysisManager->FillH1( 3, edep);
  analysisManager->FillH2( 0, position.x(), position.y());
  */


  return false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ChipSD::EndOfEvent(G4HCofThisEvent* /*hce*/)
{
  G4cout << "\n-------->" <<  fHitsCollection->GetName()
         << ": in this event: " << G4endl;

  G4int nofHits = fHitsCollection->entries();
  for ( G4int i=0; i<nofHits; i++ ) {
    (*fHitsCollection)[i]->Print();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
