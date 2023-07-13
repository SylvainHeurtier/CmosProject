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

namespace ED
{
Pixel::Pixel(const G4String& SDname, G4int ntupleID)
 : G4VSensitiveDetector(SDname),fNtupleId(ntupleID)
{
	//'collectionName is a protected dat member of base class G4SensitiveDetector'
	//Here we declare the name of the collection we will be using.
	G4String hcName = SensitiveDetectorName + "HitsCollection";
	collectionName.insert(hcName); //"HitCollection" = our hits collection name
}

Pixel::~Pixel()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Pixel::Initialize(G4HCofThisEvent* hce)
{
  G4String hcName = SensitiveDetectorName + "HitsCollection";

  fHitsCollection = new HitCollection(SensitiveDetectorName, hcName);

  G4int hcID
    = G4SDManager::GetSDMpointer()->GetCollectionID(hcName);
  hce->AddHitsCollection( hcID, fHitsCollection );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//G4Step can be interrogated to get information about physics process and volumes
G4bool Pixel::ProcessHits(G4Step *step, G4TouchableHistory*)
{

	// Change the following lines to get the charge of the tracked particle
	G4double charge = step->GetTrack()->GetDefinition()->GetPDGCharge();
  	if ( charge == 0. ) return false;

	PixelHit* newHit = new PixelHit();
/*
	// Get some properties from G4Step and set them to the hit
	G4double edep = step->GetTotalEnergyDeposit();
	newHit->AddEdep(edep);
*/
  // Time
  G4StepPoint* preStepPoint = step->GetPreStepPoint();
  G4double time = preStepPoint->GetGlobalTime();
  newHit->SetTime(time);

  // Position
  G4ThreeVector position = preStepPoint->GetPosition();
  newHit->SetPosition(position);
/*
  // Layer number
  // = copy number of mother volume
  const G4VTouchable* touchable = preStepPoint->GetTouchable();
  G4int copyNo = touchable->GetCopyNumber(1);
  newHit->SetLayerNumber(copyNo);
*/
  // Add hit in the collection
  fHitsCollection->insert(newHit);

  // energy deposit
  G4double edep = step->GetTotalEnergyDeposit();

  // Name particle
  G4String NameParticle = step->GetTrack()->GetDefinition()->GetParticleName();
  //std::cout<<"---------------------------------"<<std::endl; 
  //std::cout << "Name Particle: " << NameParticle << std::endl;
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
  //G4int Nbcode = step->GetTrack()->GetDynamicParticle()->GetPDGcode();
  //std::cout << "The PDG code: " << Nbcode << std::endl;

  //Charge
  //G4double ChargeParticle = step->GetTrack()->GetDynamicParticle()->GetCharge();

  //
  //G4int copyNo_pixel = step->GetTrack()->GetVolume()->GetCopyNo();



	// Add hit in the collection
  	fHitsCollection->insert(newHit);

  	// Add hits properties in the ntuple
  	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  	G4String name = this->GetName(); // name = PixelLV%d with 0<=d<=(npxl_col*2+1)*(npxl_row*2+1)
  	int n = name.size();
  	int i = 7; // variables de la boucle while: 
  			       //on commence à i=7 car les 6 premiers termes = PixelLV
  	int Npix = 0; // initialisation du numéro du pixel
  	while (i<n){
  		Npix = Npix + name[i]*pow(10,i-7);
  		i=i+1;
  	}

    //Division euclidienne pour récupérer les coordonnées du pixel:
    //Npix = (npxl_col*2+1)*C + L avec C le numéro de colonne et L de la ligne
    int L = Npix % (npxl_col*2+1);
    int C = Npix / (npxl_col*2+1);


  	// Npix = numéro du pixel
   	//std::cout<<"----"<< "Numéro du pixel: "<<Npix<<" ----"<<std::endl;
  	//std::cout<<"---------------------------------"<<std::endl;

	  // Add hits properties in the ntuple
  	analysisManager->FillNtupleIColumn(fNtupleId, 0, L);
    analysisManager->FillNtupleIColumn(fNtupleId, 1, C);
  	analysisManager->FillNtupleDColumn(fNtupleId, 2, time);
  	analysisManager->FillNtupleDColumn(fNtupleId, 3, edep);
    analysisManager->FillNtupleIColumn(fNtupleId, 4, NumParticle);
    //analysisManager->FillNtupleIColumn(fNtupleId, 5, Nbcode);
    //analysisManager->FillNtupleDColumn(fNtupleId, 6, ChargeParticle);
  	analysisManager->AddNtupleRow(fNtupleId);
	
	return true;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Pixel::EndOfEvent(G4HCofThisEvent* /*hce*/)
{
  //G4cout << "\n-------->" <<  fHitsCollection->GetName() << ": in this event: " << G4endl;

  //G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  G4int nofHits = fHitsCollection->entries();
  for ( G4int i=0; i<nofHits; i++ ) {
    (*fHitsCollection)[i]->Print();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
}