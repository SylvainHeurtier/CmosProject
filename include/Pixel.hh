#ifndef Pixel_h
#define Pixel_h 1


#include "G4VSensitiveDetector.hh"
#include "PixelHit.hh"

//Creation of a sensitive detector (SD)

//(different logical volumes can share one SD object)


class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

namespace B1
{
class Pixel : public G4VSensitiveDetector
{
public:
	//Constructor
	Pixel(const G4String& SDname,G4int ntupleID);
	//Destructor
	~Pixel() override;

public:
	void   Initialize(G4HCofThisEvent* hce) override;
	G4bool ProcessHits(G4Step *step, G4TouchableHistory *ROhist) override; 
	//called for each GStep in sensitive volume
	void   EndOfEvent(G4HCofThisEvent* hce) override;

private:
	HitCollection* fHitsCollection = nullptr;
	//PixelHitsCollection* fHitsCollection = nullptr;
	G4int fNtupleId = 0;
};
}

#endif