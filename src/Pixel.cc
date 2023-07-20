//*******************************************//
//                  Pixel.cc                 //
//*******************************************//
 
#include "Pixel.hh"
#include "Constants.hh"


#include "G4AnalysisManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4VTouchable.hh"
#include "G4Step.hh"
#include "G4ios.hh"
#include "G4EventManager.hh"
#include "G4RunManager.hh"

#include<iostream>
#include<string>
using namespace std;

namespace ED
{
Pixel::Pixel(const G4String& SDname, G4int ntupleID)
 : G4VSensitiveDetector(SDname),fNtupleId(ntupleID){
	//'collectionName is a protected dat member of base class G4SensitiveDetector'
	//Here we declare the name of the collection we will be using.
	G4String hcName = SensitiveDetectorName + "HitsCollection";
	collectionName.insert(hcName); //"HitCollection" = our hits collection name
  }

Pixel::~Pixel(){}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Pixel::Initialize(G4HCofThisEvent* hce)
  {
  G4String hcName = SensitiveDetectorName + "HitsCollection";


  G4int hcID
    = G4SDManager::GetSDMpointer()->GetCollectionID(hcName);
  }


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//G4Step can be interrogated to get information about physics process and volumes
G4bool Pixel::ProcessHits(G4Step *step, G4TouchableHistory*)
  {

	// Change the following lines to get the charge of the tracked particle
	G4double charge = step->GetTrack()->GetDefinition()->GetPDGCharge();
  	if ( charge == 0. ) return false;

	// Get some properties from G4Step and set them to the hit
  G4StepPoint* preStepPoint = step->GetPreStepPoint();
  // Time
  G4double time = preStepPoint->GetGlobalTime();
  // Position
  G4ThreeVector position = preStepPoint->GetPosition();
  // energy deposit
  G4double edep = step->GetTotalEnergyDeposit();
  /*
  // The GPD code
  G4int Nbcode = step->GetTrack()->GetDynamicParticle()->GetPDGcode();
  // Layer number
  const G4VTouchable* touchable = preStepPoint->GetTouchable();
  G4int copyNo = touchable->GetCopyNumber(1);
*/
  // Pixel hit collection used for printout
  PixelHit* newHit = new PixelHit();
  newHit->SetTime(time);
  newHit->SetPosition(position);
  //newHit->SetLayerNumber(copyNo);
  // Add hit in the collection

  // Name particle
  G4String NameParticle = step->GetTrack()->GetDefinition()->GetParticleName();
  G4int NumParticle;
  if (NameParticle=="pi+")
    NumParticle=5;
  else if (NameParticle=="pi-")
    NumParticle=-5;
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

  //Get current event
  //G4int EventID = G4EventManager::GetEventManager()->GetCurrentEvent()->GetEventID();
  G4int EventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  //Get Track
  G4int TrackID = step->GetTrack()->GetTrackID();

  // Add hits properties in the ntuple
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  G4String name = this->GetName(); // name = PixelLV%d with 0<=d<=(npxl_col*2+1)*(npxl_row*2+1)
  int n = name.size();
  int i = 7; // variables de la boucle while: 
  			       //on commence à i=7 car les 6 premiers termes = PixelLV
  int Npix = 0; // initialisation du numéro du pixel
  while (i<n){
    string a;
    a=name[i];
    int num = stoi(a);
    Npix = Npix + num*pow(10,n-i-1);
  	i=i+1;
  }

  //Division euclidienne pour récupérer les coordonnées du pixel:
  //Npix = (npxl_col*2+1)*C + L avec C le numéro de colonne et L de la ligne
  int L = Npix % (npxl_col*2+1);
  int C = (Npix-L) / (npxl_col*2+1);

	// Add hits properties in the ntuple
  analysisManager->FillNtupleIColumn(fNtupleId, 0, L);
  analysisManager->FillNtupleIColumn(fNtupleId, 1, C);
  analysisManager->FillNtupleDColumn(fNtupleId, 2, edep);
  analysisManager->FillNtupleIColumn(fNtupleId, 3, EventID);
  analysisManager->FillNtupleIColumn(fNtupleId, 4, TrackID);
  analysisManager->FillNtupleIColumn(fNtupleId, 4, NumParticle);
  analysisManager->AddNtupleRow(fNtupleId);
	
	return true;
  }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Pixel::EndOfEvent(G4HCofThisEvent* /*hce*/)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}