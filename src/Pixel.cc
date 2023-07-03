//*******************************************//
//                  Pixel.cc                 //
//*******************************************//

#include "Pixel.hh"


#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4VTouchable.hh"
#include "G4Step.hh"
#include "G4ios.hh"
#include "PixelHit.hh"

#include "G4CsvAnalysisManager.hh"
#include "G4AnalysisManager.hh"


namespace B1
{
Pixel::Pixel(const G4String& SDname)
 : G4VSensitiveDetector(SDname)
{
	//'collectionName is a protected dat member of base class G4SensitiveDetector'
	//Here we declare the name of the collection we will be using.
	G4String hcName = SensitiveDetectorName + "HitsCollection";
	collectionName.insert("HitCollection"); //"HitCollection" = our hits collection name
}

Pixel::~Pixel()
{}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Pixel::Initialize(G4HCofThisEvent* /*hce*/)
{
  G4String hcName = SensitiveDetectorName + "HitsCollection";

  fHitsCollection
    = new HitCollection(SensitiveDetectorName, hcName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//G4Step can be interrogated to get information about physics process and volumes
G4bool Pixel::ProcessHits(G4Step *step, G4TouchableHistory*)
{
	PixelHit* newHit = new PixelHit();

	// Get some properties from G4Step and set them to the hit
	G4double edep = step->GetTotalEnergyDeposit();
	newHit->AddEdep(edep);


	//
	G4StepPoint* preStepPoint = step->GetPreStepPoint();
	G4TouchableHistory* theTouchable = (G4TouchableHistory*)(preStepPoint->GetTouchable());
	G4int copyNo = theTouchable->GetVolume()->GetCopyNo();
	//G4int motherCopyNo = theTouchable->GetVolume(1)->GetCopyNo();
	//G4int grandMotherCopyNo = theTouchable->GetVolume(2)->GetCopyNo();
	//G4ThreeVector worldPos = preStepPoint->GetPosition();
	//G4ThreeVector localPos = theTouchable->GetHistory()
	//				->GetTopTransform().TransformPoint(worldPos);
	newHit->SetCopyNo(copyNo);

	// Add hit in the collection
  	fHitsCollection->insert(newHit);

	//Position
	//G4ThreeVector position = step->GetPreStepPoint()->GetPosition();

	return false;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Pixel::EndOfEvent(G4HCofThisEvent* /*hce*/)
{
  G4cout << "\n-------->" <<  fHitsCollection->GetName()
         << ": in this event: " << G4endl;


  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  G4int nofHits = fHitsCollection->entries();
  for ( G4int i=0; i<nofHits; i++ ) {
  	PixelHit* hit = static_cast<PixelHit*>(fHitsCollection->GetHit(i));
    analysisManager->FillH1(0, hit->GetEdep());
    //analysisManager->FillH1(0, hit->GetEdep());
  }
}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
