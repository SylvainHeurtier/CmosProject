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
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class

#include "DetectorConstruction.hh"
#include "ChipSD.hh"
#include "Constants.hh"

#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SubtractionSolid.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "stdlib.h"

namespace ED
{

  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = false;

  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();


  void ConstructChip (
                      const char* chipName,  // Chip name
                      const int& station,        // Chip station
                      G4double shape_dz,         // width of the layer
                      G4double pos_z,            // position of the layer
                      const G4String & Material, // material of the layer
                      G4RotationMatrix* pRot,    // angle of the plan
                      G4LogicalVolume* logicEnv,
                      bool sensitive)
  {

    //Just build the chip

    // Creation of the chip
    G4Material* shape_plastic = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
    G4Material* shape = nist->FindOrBuildMaterial(Material);

    // Hole for the chip
    G4VSolid* shapeIN      = new G4Box("shapeIN",6.912*mm,14.848*mm,25*um);  // half the size of the chips
    G4VSolid* shapeOUT     = new G4Box("shapeOUT",30*mm,30*mm,0.025*mm);     // half the size of plastic plans
    G4VSolid* shapePh      = new G4SubtractionSolid("shapePhantom", shapeOUT, shapeIN,0, G4ThreeVector(0,0,pos_z));
    G4LogicalVolume* logicshapePh = new G4LogicalVolume(shapePh, shape_plastic,"shapePh");
    new G4PVPlacement(0,                          //no rotation
                    G4ThreeVector(0,0,pos_z),     //at (0,0,pos_z)
                    logicshapePh,                 //its logical volume
                    "shapePh",                    //its name
                    logicEnv,                     //its mother  volume
                    true,                         //no boolean operation
                    station,                      //copy number
                    checkOverlaps);               //overlaps checking
    G4VisAttributes* shapePhVisAtt = new G4VisAttributes(G4Colour(1.0,0.0,0.0));
    logicshapePh->SetVisAttributes(shapePhVisAtt);
      


    char chip_name_sv[100];
    char chip_name_lv[100];
    char chip_name_pv[100];
    sprintf(chip_name_sv, "%sSV",chipName);
    sprintf(chip_name_lv, "%sLV",chipName);
    sprintf(chip_name_pv, "%sPV",chipName);

    G4VSolid* shapeChip            = new G4Box("shapeChip", 6.912*mm,14.848*mm,25*um);
    G4LogicalVolume* logicshape_Si = new G4LogicalVolume(
                                shapeChip,        //its solid
                                shape,            //its material
                                chip_name_lv);    //its name
    
    new G4PVPlacement(pRot,               //rotation
            G4ThreeVector(0,0,pos_z),     //at (0,0,pos_z)
            logicshape_Si,                //its logical volume
            chip_name_pv,                 //its name
            logicEnv,                     //its mother  volume
            false,                        //no boolean operation
            station,                      //copy number
            checkOverlaps);               //overlaps checking

    if (sensitive){
      auto chipSD = new ChipSD(chip_name_sv, station);
      G4SDManager::GetSDMpointer()->AddNewDetector(chipSD);
      logicshape_Si->SetSensitiveDetector(chipSD);
    }

  }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ConstructPlan (G4double shape_dz,         // width of the layer
                    const int& station,        // Chip station
                    G4double pos_z,            // position of the layer
                    const G4String & Material, // material of the layer
                    G4RotationMatrix* pRot,    // angle of the plan
                    G4LogicalVolume* logicEnv) // blabla
{
  // Creation of the chip
  G4Material* shape_plastic = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
  G4Material* shape = nist->FindOrBuildMaterial(Material);

  G4VSolid* shapeIN      = new G4Box("shapeIN",7.5*mm,15*mm,0.0025*mm);
  G4VSolid* shapeOUT     = new G4Box("shapeOUT",30*mm,30*mm,0.0025*mm);
  G4VSolid* shapePh      = new G4SubtractionSolid("shapePhantom", shapeOUT, shapeIN,0, G4ThreeVector(0,0,pos_z));
  G4LogicalVolume* logicshapePh = new G4LogicalVolume(shapePh,shape_plastic,"shapePh");

  new G4PVPlacement(0,                          //no rotation
                  G4ThreeVector(0,0,pos_z),     //at (0,0,pos_z)
                  logicshapePh,                 //its logical volume
                  "shapePh_alu",                //its name
                  logicEnv,                     //its mother  volume
                  true,                         //no boolean operation
                  station,                      //copy number
                  checkOverlaps);               //overlaps checking
  G4VisAttributes* shapePhVisAtt= new G4VisAttributes(G4Colour(1.0,0.0,0.0));
  logicshapePh->SetVisAttributes(shapePhVisAtt); 
       
  G4LogicalVolume* logicshape_Mat = new G4LogicalVolume( shapeIN,    //its solid
                                        shape,      //its material
                                        Material);  //its name

  new G4PVPlacement(pRot,                  //rotation
                  G4ThreeVector(0,0,pos_z),//at (0,0,pos_z)
                  logicshape_Mat,           //its logical volume
                  Material,                //its name
                  logicEnv,                //its mother  volume
                  false,                   //no boolean operation
                  0,                       //copy number
                  checkOverlaps);          //overlaps checking     
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4NistManager* nist = G4NistManager::Instance();

  // Envelope parameters
  //
  G4double env_sizeX=  60*mm, env_sizeY = 60*mm, env_sizeZ = 240*mm;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");

  ////////////////////////////////////////////////////////////////////////
  // World
  G4double world_sizeX = 1.2*env_sizeX;
  G4double world_sizeY = 1.2*env_sizeY;
  G4double world_sizeZ = 1.2*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  auto solidWorld = new G4Box("World",                         // its name
  0.5 * world_sizeX, 0.5 * world_sizeY, 0.5 * world_sizeZ);  // its size

  auto logicWorld = new G4LogicalVolume(solidWorld,  // its solid
  world_mat,                                       // its material
  "World");                                        // its name

  auto physWorld = new G4PVPlacement(nullptr,    // no rotation
  G4ThreeVector(),                           // at (0,0,0)
  logicWorld,                                // its logical volume
  "World",                                   // its name
  nullptr,                                   // its mother  volume
  false,                                     // no boolean operation
  0,                                         // copy number
  checkOverlaps);                            // overlaps checking

  /////////////////////////////////////////////////////////////////////////
  // Envelope
  auto solidEnv = new G4Box("Envelope",                  // its name
  0.5 * env_sizeX, 0.5 * env_sizeY, 0.5 * env_sizeZ);  // its size

  auto logicEnv = new G4LogicalVolume(solidEnv,// its solid
  env_mat,                                   // its material
  "Envelope");                               // its name

  new G4PVPlacement(nullptr,    // no rotation
  G4ThreeVector(),          // at (0,0,0)
  logicEnv,                 // its logical volume
  "Envelope",               // its name
  logicWorld,               // its mother  volume
  false,                    // no boolean operation
  0,                        // copy number
  checkOverlaps);           // overlaps checking
  //


  ///////////////////////////////////////////////////////////////////////////
  // ALPIDE chip
  ///////////////////////////////////////////////////////////////////////////
  G4double* Z; // list of positions along the z-axis of the layers
  int n = 10; 
  Z=(G4double*)malloc(n*sizeof(G4double));
  Z[0]=-103.2*mm; // chip 
  Z[1]=-83.6*mm;  // chip
  Z[2]=-64*mm;    // chip 
  Z[3]=69*mm;     // chip
  Z[4]=88.6*mm;   // chip
  Z[5]=108.2*mm;  // chip
  Z[6]=-50*mm;    // plan of aluminium
  Z[7]=-4*mm;     // plan of aluminium
  Z[8]=8*mm;      // plan of aluminium
  Z[9]=57*mm;     // plan of aluminium

  int i = 0;
  while(i<10) {


    // chips in the planes
    char chip_name_sv[100];
    sprintf(chip_name_sv, "Chip%d",i);
    if(i<6) ConstructChip(chip_name_sv,i+1,shape_dz_IB, Z[i], "G4_Si", nullptr, logicEnv, false); //Test=0
    
    // build the aluminium planes
    else    ConstructPlan( shape_dz_Al, i+1, Z[i], "G4_ALUMINUM_OXIDE", nullptr, logicEnv);
    i=i+1;
  }

  // the sensitive chip
  char chip_name_sv[100];
  sprintf(chip_name_sv, "Chip%d",0);
  ConstructChip(chip_name_sv, 0, shape_dz_IB, 0, "G4_Si", nullptr, logicEnv, true); //Test=1

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
