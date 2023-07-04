//*******************************************//
//                  Pixel.cc                 //
//*******************************************//

#include "Pixel.hh"
#include "PixelHit.hh"

#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4VTouchable.hh"
#include "G4Step.hh"
#include "G4ios.hh"

#include "G4CsvAnalysisManager.hh"
#include "G4AnalysisManager.hh"

namespace B1
{
Pixel::Pixel(const G4String& SDname, G4int ntupleID)
 : G4VSensitiveDetector(SDname),
   fNtupleId(ntupleID)
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

  fHitsCollection = new HitCollection(SensitiveDetectorName, hcName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//G4Step can be interrogated to get information about physics process and volumes
G4bool Pixel::ProcessHits(G4Step *step, G4TouchableHistory*)
{
	// Change the following lines to get the charge of the tracked particle
	G4double charge = step->GetTrack()->GetDefinition()->GetPDGCharge();
  	if ( charge == 0. ) return false;

	PixelHit* newHit = new PixelHit();

	// Get some properties from G4Step and set them to the hit
	G4double edep = step->GetTotalEnergyDeposit();
	newHit->AddEdep(edep);

	std::cout <<  "------------------------------------" << std::endl;
	std::cout <<  "----------"<< edep <<"--------------" << std::endl;
	std::cout <<  "------------------------------------" << std::endl;
	//
	//G4StepPoint* preStepPoint = step->GetPreStepPoint();
	//G4TouchableHistory* theTouchable = (G4TouchableHistory*)(preStepPoint->GetTouchable());
	//G4int copyNo = theTouchable->GetVolume()->GetCopyNo();
	//G4int motherCopyNo = theTouchable->GetVolume(1)->GetCopyNo();
	//G4int grandMotherCopyNo = theTouchable->GetVolume(2)->GetCopyNo();
	//G4ThreeVector worldPos = preStepPoint->GetPosition();
	//G4ThreeVector localPos = theTouchable->GetHistory()
	//				->GetTopTransform().TransformPoint(worldPos);
	//newHit->SetCopyNo(copyNo);

	// Position
  	//G4ThreeVector position = preStepPoint->GetPosition();
  	//newHit->SetPosition(position);

	// Add hit in the collection
  	fHitsCollection->insert(newHit);

  	// Add hits properties in the ntuple
  	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  	G4String name = this->GetName(); // name = PixelLV%d with 0<=d<=10403
  	int n = name.size();
  	int i = 7; // variables de la boucle while: 
  			   //on commence à i=7 car les 6 premiers termes = PixelLV
  	int p = 0; // initialisation du numéro du pixel
  	while (i<n){
  		p = p + name[i]*pow(10,i-7);
  		i=i+1;
  	}
  	// p = numéro du pixel
  	std::cout<<"---------------------------------"<<std::endl;
   	std::cout<<"------------ "<<p<<" ------------"<<std::endl;
  	std::cout<<"---------------------------------"<<std::endl;

  	//analysisManager->FillNtupleIColumn(fNtupleId, 0, p );
  	//analysisManager->FillNtupleDColumn(fNtupleId, 1, newHit->GetEdep());
  	//analysisManager->AddNtupleRow(fNtupleId);

	
	return false;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Pixel::EndOfEvent(G4HCofThisEvent* /*hce*/)
{
  //G4cout << "\n-------->" <<  fHitsCollection->GetName() << ": in this event: " << G4endl;

  //G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  //G4int nofHits = fHitsCollection->entries();
  //for ( G4int i=0; i<nofHits; i++ ) {
  	//G4cout <<  "--------------coucou----------------" << G4endl;
  	//PixelHit* hit = static_cast<PixelHit*>(fHitsCollection->GetHit(i));
    //analysisManager->FillH1(0, hit->GetEdep());
    //analysisManager->FillH1(0, hit->GetEdep());
  //}
}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
