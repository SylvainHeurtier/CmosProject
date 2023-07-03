//We need to write our own Hit class: inherits from G4VHit

//Hits must be stored in a collection of hits instantiated from
//G4THitsCollection template class
#ifndef Hit_h
#define Hit_h 1

#include "G4VHit.hh"
#include "G4Allocator.hh"
#include "G4THitsCollection.hh"

class Hit : public G4VHit 
{
	public:
		Hit(); //create a new Hit: the ID is the layer index
		~Hit() override;
		const Hit& operator=(const Hit& right);

		int operator==(const Hit &right) const;

    	inline void* operator new(size_t);
    	inline void  operator delete(void* hit);

		void Print() override;  //Hit interface: print on screen
		
		//-----------------------------------------------
		//Our specific hit interface:
		void AddEdep(const double e) {eDep += e;}
		void SetCopyNo(const int N) {CopyNo = N;}

		G4double GetEdep() const {return eDep;}
		G4int GetCopyNo() const {return CopyNo;}
		//-----------------------------------------------

private:
	//const G4int layerNumber;
	G4double eDep;
	G4int CopyNo;
};

// Define the "hit collection" using the template class G4THitsCollection:
typedef G4THitsCollection<Hit> HitCollection;


extern G4Allocator<Hit>* HitAllocator;

inline void* Hit::operator new(size_t)
{
  if (! HitAllocator)
        HitAllocator = new G4Allocator<Hit>;
  return (void*)HitAllocator->MallocSingle();
}

inline void Hit::operator delete(void* hit)
{
  HitAllocator->FreeSingle((Hit*) hit);
}

#endif