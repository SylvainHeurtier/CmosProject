//
// ********************************************************************
// *                      Detector Construction                       *
// ********************************************************************
// 
// $Id$
//
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class

#include "DetectorConstruction.hh"
//#include "ChipSD.hh"
#include "Pixel.hh"
#include "Constants.hh"

#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
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

//-------------------------------------------//


  void ConstructChip (
                      const char* chipName,  // Chip name
                      const int& station,        // Chip station
                      G4double shape_dz,         // width of the layer
                      G4double pos_z,            // position of the layer
                      const G4String & Material, // material of the layer
                      G4RotationMatrix* pRot,    // angle of the plan
                      G4LogicalVolume* logicEnv,
                      bool full)      // if full==True we build the chip with pixels
  {
    //Just build the chip

    // Creation of the chip
    G4Material* shape_plastic = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
    G4Material* shape = nist->FindOrBuildMaterial(Material);

    // Hole for the chip
    G4VSolid* shapeIN      = new G4Box("shapeIN",6.912*mm,14.848*mm,shape_dz);  // half the size of the chips
    G4VSolid* shapeOUT     = new G4Box("shapeOUT",30*mm,30*mm,shape_dz);     // half the size of plastic plans
    G4VSolid* shapePh      = new G4SubtractionSolid("shapePhantom", shapeOUT, shapeIN,0, G4ThreeVector(0,0,pos_z));
    G4LogicalVolume* logicshapePh = new G4LogicalVolume(shapePh, shape_plastic,"shapePh");
    new G4PVPlacement(pRot,                          //no rotation
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

    G4VSolid* shapeChip            = new G4Box("shapeChip", 6.912*mm,14.848*mm,shape_dz);
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

//**************Construction of pixels if full==True**********************

    if (full){
      // if full==True we build the chip with pixels

      char pxl_name_lv[100];
      char pxl_name_pvp[100];
      int countLV;
      int countPVP;

      //Create a solid and declaration
      G4VSolid* shapePix= new G4Box("shapePix", 0.5*Xpix, 0.5*Ypix, shape_dz);
      G4LogicalVolume* logicshape_Pix;

      //CopyNumber of pixel =compteur - initialisation
      int compteur=0;

      //Limits of parameters for nx and ny depend of npxl_row and npxl_col
      int nx_max;
      int ny_max;
      int nx_min;
      int ny_min;
      
      //Limit for nx
      if(npxl_col%2==0){ //even number of columns
        nx_max = npxl_col/2 -1;
        nx_min = npxl_col/2;
      }
      else{
        nx_max = (npxl_col-1)/2;
        nx_min = nx_max;
      }

      //Limit for ny
      if(npxl_row%2==0){ //even number of rows
        ny_max = npxl_row/2 -1;
        ny_min = npxl_row/2;
      }
      else{
        ny_max = (npxl_row-1)/2;
        ny_min = ny_max;
      }

      //Double loop to build pixel one by one in the chip
      for( int nx = -nx_min; nx <= nx_max; nx++){
        for( int ny = -ny_min; ny <= ny_max; ny++){

          //Create name of pixel
          countLV = sprintf(pxl_name_lv, "PixelLV%d",compteur);
          countPVP = sprintf(pxl_name_pvp, "PixelPVP%d",compteur);

          //Create a logical volume
          logicshape_Pix = new G4LogicalVolume(shapePix,  //its solid
                                  shape,                  //its material
                                  pxl_name_lv);           //its name

          new G4PVPlacement(pRot,              //rotation
                    G4ThreeVector((0.5+nx)*Xpix,(0.5+ny)*Ypix, pos_z),//coordinates
                    logicshape_Pix,           //its logical volume
                    pxl_name_pvp,            //its name
                    logicshape_Si,           //its mother volume = logical volume of the chip
                    false,                   //no boolean operation
                    compteur,                //copy number
                    checkOverlaps);          //overlaps checking
          
          //Pixel = a sensitive detector
          Pixel* pixelSD = new Pixel(pxl_name_lv, 0);//Pixel(pxl_name_lv, compteur)
          G4SDManager::GetSDMpointer()->AddNewDetector(pixelSD);
          logicshape_Pix->SetSensitiveDetector(pixelSD);
          
          compteur+=1;
        }
      }
    }
    
//***********************************************************************

  }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ConstructPlan (G4double shape_dz,         // width of the layer
                    const int& station,        // Chip station
                    G4double pos_y,            // position of the layer
                    G4double pos_z,
                    const G4String & Material, // material of the layer
                    G4RotationMatrix* pRot,    // angle of the plan
                    G4LogicalVolume* logicEnv) // blabla
{
  // Creation of the chip
  G4Material* shape_plastic = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
  G4Material* shape = nist->FindOrBuildMaterial(Material);

  G4VSolid* shapeIN      = new G4Box("shapeIN",7.5*mm,15*mm,0.0025*mm);
  G4VSolid* shapeOUT     = new G4Box("shapeOUT",30*mm,30*mm,0.0025*mm);
  G4VSolid* shapePh      = new G4SubtractionSolid("shapePhantom", shapeOUT, shapeIN,0, G4ThreeVector(0,pos_y,pos_z));
  G4LogicalVolume* logicshapePh = new G4LogicalVolume(shapePh,shape_plastic,"shapePh");

  new G4PVPlacement(pRot,                          //no rotation
                  G4ThreeVector(0,pos_y,pos_z),     //at (0,0,pos_z)
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
                  G4ThreeVector(0,pos_y,pos_z),//at (0,0,pos_z)
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
  Z[0] =-103.2*mm; // chip 
  Z[1] =-83.6*mm;  // chip
  Z[2] =-64*mm;    // chip 
  Z[3] =69*mm;     // chip
  Z[4] =88.6*mm;   // chip
  Z[5] =108.2*mm;  // chip
  Z[6] =-50*mm;    // plan of aluminium
  Z[7] =-4*std::cos(angle*deg)*mm;     // plan of aluminium
  Z[8] =8*std::cos(angle*deg)*mm;      // plan of aluminium
  Z[9] =57*mm;     // plan of aluminium

  G4RotationMatrix* rotationMatrix = new G4RotationMatrix();
  rotationMatrix->rotateX(angle*deg);
  G4double yn = -4*std::sin(angle*deg)*mm;
  G4double yp = 8*std::sin(angle*deg)*mm;


  int i = 0;
  while(i<10) {
    // chips in the planes
    char chip_name_sv[100];
    sprintf(chip_name_sv, "Chip%d",i+1);
    if(i<6) ConstructChip(chip_name_sv,i+1,shape_dz_IB, Z[i], "G4_Si", nullptr, logicEnv, false); 
    i=i+1;
    }
  
  // build the aluminium planes
  ConstructPlan( shape_dz_Al, 10, 0., Z[6], "G4_ALUMINUM_OXIDE", nullptr, logicEnv);
  ConstructPlan( shape_dz_Al, 8, yn, Z[7], "G4_ALUMINUM_OXIDE", rotationMatrix, logicEnv);
  ConstructPlan( shape_dz_Al, 9, yp, Z[8], "G4_ALUMINUM_OXIDE", rotationMatrix, logicEnv);
  ConstructPlan( shape_dz_Al, 10, 0., Z[9], "G4_ALUMINUM_OXIDE", nullptr, logicEnv);
  

  // the sensitive chip
  char chip_name_sv[100];
  sprintf(chip_name_sv, "Chip%d",0);
  ConstructChip(chip_name_sv, 0, epaisseur, 0, "G4_Si", rotationMatrix, logicEnv, true);

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
