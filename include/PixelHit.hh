//We need to write our own Hit class: inherits from G4VHit

//Hits must be stored in a collection of hits instantiated from
//G4THitsCollection template class
#ifndef PixelHit_h
#define PixelHit_h 1
 
#include "G4VHit.hh"
#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"


namespace ED
{

class PixelHit : public G4VHit 
{
	public:
		PixelHit(); //create a new Hit: the ID is the layer index
		~PixelHit() override;
		PixelHit(const PixelHit& right);
		const PixelHit& operator=(const PixelHit& right);
		int operator==(const PixelHit &right) const;

    	inline void* operator new(size_t);
    	inline void  operator delete(void* hit);

		void Print() override;  //Hit interface: print on screen

		// setter methods
    	void SetLayerNumber(G4int number) { fLayerNumber = number; }
    	void SetTime(G4double time)       { fTime = time; }
    	void SetPosition(G4ThreeVector position) { fPosition = position; }

    	// getter methods
    	G4int          GetLayerNumber() const { return fLayerNumber;}
    	G4double       GetTime() const        { return fTime; }
    	G4ThreeVector  GetPosition() const    { return fPosition; }
    
    /*
		//-----------------------------------------------
		//Our specific hit interface:
		void AddEdep(const double e) {eDep += e;}
		void SetCopyNo(const int N) {CopyNo = N;}

		G4double GetEdep() const {return eDep;}
		G4int GetCopyNo() const {return CopyNo;}
		//-----------------------------------------------
	*/
private:
	//const G4int layerNumber;
	//G4double eDep;
	//G4int CopyNo;
	// data members
    G4int          fLayerNumber = -1;
    G4double       fTime = 0.;
    G4ThreeVector  fPosition;
};

// Define the "hit collection" using the template class G4THitsCollection:
typedef G4THitsCollection<PixelHit> HitCollection;


extern G4Allocator<PixelHit>* PixelHitAllocator;

inline void* PixelHit::operator new(size_t)
{
  if (! PixelHitAllocator)
        PixelHitAllocator = new G4Allocator<PixelHit>;
  return (void*)PixelHitAllocator->MallocSingle();
}

inline void PixelHit::operator delete(void* hit)
{
  PixelHitAllocator->FreeSingle((PixelHit*) hit);
}

}

#endif