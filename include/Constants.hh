#ifndef B1Constants_h
#define B1Constants_h 1

#include "globals.hh"
#include "G4SystemOfUnits.hh"


namespace ED
{

//Declaration
// ALPIDE Chips
const G4double shape_dx = 15*mm;
const G4double shape_dy = 30*mm;

const G4double shape_dz_IB = 0.05*mm;  // thick: 50µm
//G4double shape_dz_OB = 0.1*mm;   // thick: 100µm
const G4double shape_dz_Al = 0.01*mm; // thick: ??

// size of one pixel
const G4double Xpix=27*um;
const G4double Ypix=29*um; 

// row and column for a chip
const int npxl_row = 1;
const int npxl_col = 1;
}

#endif


