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

const G4double shape_dz_IB = 25*um;  // width: 50µm
//G4double shape_dz_OB = 0.1*mm;   // width: 100µm
const G4double shape_dz_Al = 10*um; // width ??

// size of one pixel
const G4double Xpix=27*um;
const G4double Ypix=29*um;
const G4double epaisseur = 25*um; //25*um

// number of row and number of column for a chip 
const int npxl_row = 100; //more rows = more pixels along the y axis
const int npxl_col = 50; //more columns = more pixels along the x axis

// Angle of the chip with the vertical axis
const double angle = 70;

// Name of the ROOT file
const G4String fileName = "ED_TestBeam5.root";
}

#endif


