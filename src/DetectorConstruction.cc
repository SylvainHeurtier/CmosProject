/// \file B1/src/DetectorConstruction.cc
/// \brief Implementation of the B1::DetectorConstruction class
/// Lien matériaux: https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Appendix/materialNames.html


#include "DetectorConstruction.hh"
#include "Pixel.hh"

#include "G4SDManager.hh"
#include "G4SubtractionSolid.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "stdlib.h"

#include <cstdio>
#include <iostream>
using namespace std;


namespace B1
{


  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = false;


  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  //Declaration
  // ALPIDE Chips
  G4double shape_dx = 15*mm;;
  G4double shape_dy = 30*mm;;

  G4double shape_dz_IB = 0.05*mm;  // thick: 50µm
  //G4double shape_dz_OB = 0.1*mm;   // thick: 100µm
  G4double shape_dz_Al = 0.01*mm; // thick: ??

  // size of one pixel
  G4double Xpix=27*um;
  G4double Ypix=29*um; 

  // row and column for a chip
  const int npxl_row = 50;
  const int npxl_col = 50;

  G4ThreeVector pos;
  
  G4LogicalVolume* logicShape;

  G4Material* shape_mat;
  G4Material* shape_plastic;
  G4Material* shape;

  G4VSolid* solidShape;
  G4VSolid* shapeIN;
  G4VSolid* shapeOUT;
  G4VSolid* shapePh;
  G4VSolid* shapePix;

  G4LogicalVolume* logicshapePh;
  G4LogicalVolume* logicshape_Si;
  G4LogicalVolume* logicshape_Mat;
  G4VisAttributes* shapePhVisAtt;


  void ConstructChip (G4double shape_dz,         // width of the layer
                      G4double pos_z,            // position of the layer
                      const G4String & Material, // material of the layer
                      G4RotationMatrix* pRot,    // angle of the plan
                      G4LogicalVolume* logicEnv,
                      int Test)
    {

    //La fonction ConstructChip créer un support plastique carré avec à l'interieur 
    //le chip formé des pixels à l'intérieur placé à la coordonnée pos_z selon z.

    // Creation of the chip
    shape_plastic = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
    shape = nist->FindOrBuildMaterial(Material);

    shapeIN= new G4Box("shapeIN",6.912*mm,14.848*mm,25*um); // half the size of the chips
    shapeOUT = new G4Box("shapeOUT",30*mm,30*mm,0.025*mm); // half the size of plastic plans
    shapePh= new G4SubtractionSolid("shapePhantom", shapeOUT, 
                  shapeIN,0, G4ThreeVector(0,0,pos_z));

    logicshapePh = new G4LogicalVolume(shapePh,        //its solid
                                shape_plastic, //its material
                                "shapePh");    //its name


    new G4PVPlacement(0,                          //no rotation
                    G4ThreeVector(0,0,pos_z),     //at (0,0,pos_z)
                    logicshapePh,                 //its logical volume
                    "shapePh",                    //its name
                    logicEnv,                     //its mother  volume
                    true,                         //no boolean operation
                    0,                            //copy number
                    checkOverlaps);               //overlaps checking
  
    shapePhVisAtt= new G4VisAttributes(G4Colour(1.0,0.0,0.0));
    logicshapePh->SetVisAttributes(shapePhVisAtt);
      
    shapePix= new G4Box("shapePix", 0.5*Xpix, 0.5*Ypix,25*um);
    logicshape_Si = new G4LogicalVolume(shapePix,  //its solid
                              shape,             //its material
                              Material);         //its name
    G4String nameLV;
    G4String namePVP;


    char pxl_name_lv[100];
    char pxl_name_pvp[100];
    int countLV;
    int countPVP;

    int compteur=0;
    for( int nx=0;  nx<=npxl_row; nx++){ 
      for( int ny=0; ny<=npxl_col; ny++){ 
        //Construction de la partie haut droite du chip
        countLV = sprintf(pxl_name_lv, "PixelLV%d",compteur);
        countPVP = sprintf(pxl_name_pvp, "PixelPVP%d",compteur);

        if(Test==1){
          nameLV=pxl_name_lv;
          namePVP=pxl_name_pvp;
        } else {
          nameLV="NameLV";
          namePVP="NamePVP";
        }
        logicshape_Si = new G4LogicalVolume(shapePix,  //its solid
                              shape,             //its material
                              nameLV);         //its name
        new G4PVPlacement(pRot,              //rotation
                    G4ThreeVector((0.5+nx)*Xpix,(0.5+ny)*Ypix, pos_z),//coordinates
                    logicshape_Si,           //its logical volume
                    namePVP,                    //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    compteur,                //copy number
                    checkOverlaps);          //overlaps checking
        compteur+=1;

        
        countLV =sprintf(pxl_name_lv, "PixelLV%d",compteur);
        countPVP =sprintf(pxl_name_pvp, "PixelPVP%d",compteur);
        
        //Construction de la partie haut gauche du chip
        if(Test==1){
          nameLV=pxl_name_lv;
          namePVP=pxl_name_pvp;
        } else {
          nameLV="NameLV";
          namePVP="NamePVP";
        }
        
        logicshape_Si = new G4LogicalVolume(shapePix,  //its solid
                              shape,             //its material
                              nameLV);         //its name
        new G4PVPlacement(pRot,              //rotation
                    G4ThreeVector((-0.5-nx)*Xpix,(0.5+ny)*Ypix, pos_z),//coordinates
                    logicshape_Si,           //its logical volume
                    namePVP,                    //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    compteur,                //copy number
                    checkOverlaps);          //overlaps checking
        compteur+=1;

        countLV =sprintf(pxl_name_lv, "PixelLV%d",compteur);
        countPVP =sprintf(pxl_name_pvp, "PixelPVP%d",compteur);
        
        //Construction de la partie basse droite du chip
        if(Test==1){
          nameLV=pxl_name_lv;
          namePVP=pxl_name_pvp;
        } else {
          nameLV="NameLV";
          namePVP="NamePVP";
        }

        logicshape_Si = new G4LogicalVolume(shapePix,  //its solid
                              shape,             //its material
                              nameLV);         //its name
        new G4PVPlacement(pRot,             //rotation
                    G4ThreeVector((0.5+nx)*Xpix,(-0.5-ny)*Ypix, pos_z),//coordinates
                    logicshape_Si,          //its logical volume
                    namePVP,                   //its name
                    logicEnv,               //its mother  volume
                    false,                  //no boolean operation
                    compteur,               //copy number
                    checkOverlaps);         //overlaps checking
        compteur+=1;

        countLV =sprintf(pxl_name_lv, "PixelLV%d",compteur);
        countPVP =sprintf(pxl_name_pvp, "PixelPVP%d",compteur);

        //Construction de la partie basse gauche du chip
        if(Test==1){
          nameLV=pxl_name_lv;
          namePVP=pxl_name_pvp;
        } else {
          nameLV="NameLV";
          namePVP="NamePVP";
        }

        logicshape_Si = new G4LogicalVolume(shapePix,  //its solid
                              shape,             //its material
                              nameLV);         //its name
        new G4PVPlacement(pRot,             //rotation
                    G4ThreeVector((-0.5-nx)*Xpix,(-0.5-ny)*Ypix, pos_z),//coordinates
                    logicshape_Si,          //its logical volume
                    namePVP,                   //its name
                    logicEnv,               //its mother  volume
                    false,                  //no boolean operation
                    compteur,               //copy number
                    checkOverlaps);         //overlaps checking
        compteur+=1;
        }
      }
    }

  //La fonction ConstructPlan créer un support plastique carré avec à l'interieur 
  //une plaque en Silicium ou une plaque en aluminium en fonction du materiaux 
  //demandé placé à la coordonnée pos_z selon z.

  void ConstructPlan (G4double shape_dz,         // width of the layer
                      G4double pos_z,            // position of the layer
                      const G4String & Material, // material of the layer
                      G4RotationMatrix* pRot,    // angle of the plan
                      G4LogicalVolume* logicEnv)            // blabla
    {
    // Creation of the chip
    shape_plastic = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
    shape = nist->FindOrBuildMaterial(Material);

    shapeIN= new G4Box("shapeIN",7.5*mm,15*mm,0.0025*mm);
    shapeOUT = new G4Box("shapeOUT",30*mm,30*mm,0.0025*mm);
    shapePh= new G4SubtractionSolid("shapePhantom", shapeOUT, shapeIN,0, G4ThreeVector(0,0,pos_z));

    logicshapePh = new G4LogicalVolume(shapePh,        //its solid
                                shape_plastic, //its material
                                "shapePh");    //its name

    // Option to switch on/off checking of volumes overlaps
    G4bool checkOverlaps = false;

    new G4PVPlacement(0,                          //no rotation
                    G4ThreeVector(0,0,pos_z),     //at (0,0,pos_z)
                    logicshapePh,                 //its logical volume
                    "shapePh",                    //its name
                    logicEnv,                     //its mother  volume
                    true,                         //no boolean operation
                    0,                            //copy number
                    checkOverlaps);               //overlaps checking
  
    shapePhVisAtt= new G4VisAttributes(G4Colour(1.0,0.0,0.0));
    logicshapePh->SetVisAttributes(shapePhVisAtt); 
         
    logicshape_Mat = new G4LogicalVolume(shapeIN,  //its solid
                                shape,             //its material
                                Material);         //its name

    new G4PVPlacement(pRot,                  //rotation
                    G4ThreeVector(0,0,pos_z),//at (0,0,pos_z)
                    logicshape_Mat,           //its logical volume
                    Material,                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking     
  }


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
      if(i<6) ConstructChip( shape_dz_IB, Z[i], "G4_Si", nullptr, logicEnv, 0); //Test=0
      
      // build the aluminium planes
      else    ConstructPlan( shape_dz_Al, Z[i], "G4_ALUMINUM_OXIDE", nullptr, logicEnv);
      i=i+1;
    }

    ConstructChip(shape_dz_IB, 0, "G4_Si", nullptr, logicEnv, 1); //Test=1

    //
    // Sensitive detectors
    //
    int count, count1;
    char pxl_name[100];
    char pxl_name_stv[100];
    G4String pixelname;
    G4String mySensitive;

    // G4SDManager::GetSDMpointer()->SetVerboseLevel(3);
    for(int j=0;  j<= npxl_row*npxl_col; j++){ //1024*50 = 524288 pixels au total 
      //mais le compteur commence à 0 dans la fonction ConstructChip => 0<=j<=524287
      count                 = sprintf(pxl_name, "PixelLV%d",j);
      count1                = sprintf(pxl_name_stv, "mySensitive%d",j);
      pixelname             = pxl_name;
      mySensitive           = pxl_name_stv;
      Pixel* PixelSensitive = new Pixel(mySensitive, j);
      G4SDManager::GetSDMpointer()->AddNewDetector(PixelSensitive);
      SetSensitiveDetector(pixelname, PixelSensitive);
    }

    // test for sensitive detector
    
  G4VSensitiveDetector* test_pixel = G4SDManager::GetSDMpointer()->FindSensitiveDetector(mySensitive);
  
  std::cout << "ici !" << std::endl;
  std::cout << "test_pixel->isActive(): " << test_pixel->isActive() <<std::endl;
  std::cout << "test_pixel->GetName(): " << test_pixel->GetName() <<std::endl;

    //
    //always return the physical World
    //
    return physWorld;
  }
}