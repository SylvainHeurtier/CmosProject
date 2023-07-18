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
/// \file ChipHit.hh
/// \brief Definition of the ChipHit class
//

#ifndef ChipHit_h
#define ChipHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

namespace ED
{

class ChipHit : public G4VHit
{
  public:
    ChipHit();
    ~ChipHit() override;
    ChipHit(const ChipHit& right);
    const ChipHit& operator=(const ChipHit& right);
    int operator==(const ChipHit &right) const;

    inline void* operator new(size_t);
    inline void  operator delete(void* hit);

    void Print() override;
    void Draw() override;

    // setter methods
    void SetLayerNumber(G4int number) { fLayerNumber = number; }
    void SetTime(G4double time)       { fTime = time; }
    void SetPosition(G4ThreeVector position) { fPosition = position; }

    // getter methods
    G4int          GetLayerNumber() const { return fLayerNumber;}
    G4double       GetTime() const        { return fTime; }
    G4ThreeVector  GetPosition() const    { return fPosition; }

  private:
    // data members
    G4int          fLayerNumber = -1;
    G4double       fTime = 0.;
    G4ThreeVector  fPosition;
};

typedef G4THitsCollection<ChipHit> ChipHitsCollection;

extern G4Allocator<ChipHit>* ChipHitAllocator;

inline void* ChipHit::operator new(size_t)
{
  if (! ChipHitAllocator)
        ChipHitAllocator = new G4Allocator<ChipHit>;
  return (void*)ChipHitAllocator->MallocSingle();
}

inline void ChipHit::operator delete(void* hit)
{
  ChipHitAllocator->FreeSingle((ChipHit*) hit);
}

}

#endif


