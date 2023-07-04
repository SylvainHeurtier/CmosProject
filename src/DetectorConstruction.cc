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
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  //Declaration
  G4double shape_dx;
  G4double shape_dy;

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

  G4double Xpix=27*um;
  G4double Ypix=29*um; // size of one pixel
  int nx, ny; // half the number of pixels along the x-axis and y-axis

///////////////////////////////////////////////////////////////////////////
//............................oooOO0OOooo..................................
///////////////////////////////////////////////////////////////////////////

  //La fonction ConstructChip créer un support plastique carré avec à l'interieur 
  //le chip formé des pixels à l'intérieur placé à la coordonnée pos_z selon z.

  void ConstructChip (G4double shape_dz,         // width of the layer
                      G4double pos_z,            // position of the layer
                      const G4String & Material, // material of the layer
                      G4RotationMatrix* pRot,    // angle of the plan
                      G4LogicalVolume* logicEnv,
                      int Test)
    {
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
      
    shapePix= new G4Box("shapePix", 0.5*Xpix, 0.5*Ypix,25*um);
    logicshape_Si = new G4LogicalVolume(shapePix,  //its solid
                              shape,             //its material
                              Material);         //its name
    G4String nameLV;
    G4String namePVP;
    char bufferLV[100];
    char bufferPVP[100];
    int countLV;
    int countPVP;

    int compteur=0;
    for(nx=0;nx<=50;nx=nx+1){ // 0<=nx<=255
      for(ny=0;ny<=50;ny=ny+1){ // 0<=ny<=511
        //std::cout << "===========================================================" << std::endl;
        //std::cout << "       nx = " << nx << "  et  ny = " << ny <<   "          " << std::endl;
        //std::cout << "===========================================================" << std::endl;

        //Construction de la partie haut droite du chip
        countLV =sprintf(bufferLV, "PixelLV%d",compteur);
        countPVP =sprintf(bufferPVP, "PixelPVP%d",compteur);

        if(Test==1){
          nameLV=bufferLV;
          namePVP=bufferPVP;}
        else{
          nameLV="NameLV";
          namePVP="NamePVP";}
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

        
        countLV =sprintf(bufferLV, "PixelLV%d",compteur);
        countPVP =sprintf(bufferPVP, "PixelPVP%d",compteur);
        //Construction de la partie haut gauche du chip
        if(Test==1){
          nameLV=bufferLV;
          namePVP=bufferPVP;}
        else{
          nameLV="NameLV";
          namePVP="NamePVP";}
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

        countLV =sprintf(bufferLV, "PixelLV%d",compteur);
        countPVP =sprintf(bufferPVP, "PixelPVP%d",compteur);
        //Construction de la partie basse droite du chip
        if(Test==1){
          nameLV=bufferLV;
          namePVP=bufferPVP;}
        else{
          nameLV="NameLV";
          namePVP="NamePVP";}
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

        countLV =sprintf(bufferLV, "PixelLV%d",compteur);
        countPVP =sprintf(bufferPVP, "PixelPVP%d",compteur);
        //Construction de la partie basse gauche du chip
        if(Test==1){
          nameLV=bufferLV;
          namePVP=bufferPVP;}
        else{
          nameLV="NameLV";
          namePVP="NamePVP";}
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

///////////////////////////////////////////////////////////////////////////
//............................oooOO0OOooo..................................
///////////////////////////////////////////////////////////////////////////

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


///////////////////////////////////////////////////////////////////////////
//............................oooOO0OOooo..................................
///////////////////////////////////////////////////////////////////////////

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4NistManager* nist = G4NistManager::Instance();

  // Envelope parameters
  //
      G4double env_sizeX=  60*mm, env_sizeY = 60*mm, env_sizeZ = 240*mm;
      G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");

      // Option to switch on/off checking of volumes overlaps
      G4bool checkOverlaps = true;
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

  // ALPIDE Chips
  shape_dx = 15*mm;
  shape_dy = 30*mm;
  G4double shape_dz_IB = 0.05*mm;  // thick: 50µm
  //G4double shape_dz_OB = 0.1*mm;   // thick: 100µm
  G4double shape_dz_Al = 0.01*mm; // thick: ??

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
  while(i<10)
  {
    if(i<6)
      ConstructChip( shape_dz_IB, Z[i], "G4_Si", nullptr, logicEnv, 0); //Test=0
    else
      ConstructPlan( shape_dz_Al, Z[i], "G4_ALUMINUM_OXIDE", nullptr, logicEnv);
    i=i+1;
  }

  ConstructChip(shape_dz_IB, 0, "G4_Si", nullptr, logicEnv, 1); //Test=1

  // G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
  //
  // Sensitive detectors
  //

  int count, count1;
  char buffer[100];
  char buffer1[100];
  G4String pixelname;
  G4String mySensitive;
  int j;

  for(j=0;j<=10403;j=j+1){ //1024*512 = 524288 pixels au total 
    //mais le compteur commence à 0 dans la fonction ConstructChip => 0<=j<=524287
    count =sprintf(buffer, "PixelLV%d",j);
    count1 =sprintf(buffer1, "mySensitive%d",j);
    pixelname = buffer;
    mySensitive = buffer1;
    Pixel* PixelSensitive = new Pixel(mySensitive, j);
    G4SDManager::GetSDMpointer()->AddNewDetector(PixelSensitive);
    SetSensitiveDetector(pixelname, PixelSensitive);
  }
  // Set ShapeDUT as scoring volume
  //fScoringVolume = logicshape_Si;

  ////////////////////////////////////////////////////////////////////////
  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
}













  //
  // Shape DUT //////////////////////////////////////////////////////////////
  // DUT = Device Under Test
  
  //G4Material* shape_plastic = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
  //G4Material* shape_Si = nist->FindOrBuildMaterial("G4_Si");

  //G4VSolid* shapeIN= new G4Box("shapeIN",7.5*mm,15*mm,0.0025*mm);
  //G4VSolid* shapeOUT = new G4Box("shapeOUT",30*mm,30*mm,0.0025*mm);
  //G4VSolid* shapePh= new G4SubtractionSolid("shapePhantom", shapeOUT, shapeIN,
//0, G4ThreeVector(0,0,0));

  //G4LogicalVolume* logicshapePh =
  //new G4LogicalVolume(shapePh,            //its solid
  //                    shape_plastic,      //its material
  //                    "shapePh");         //its name

  //new G4PVPlacement(0,                            //no rotation
  //                  G4ThreeVector(0,0,0),         //at (0,0,0)
  //                  logicshapePh,                 //its logical volume
  //                  "shapePh",                    //its name
  //                  logicEnv,                     //its mother  volume
  //                  true,                         //no boolean operation
  //                  0,                            //copy number
  //                  checkOverlaps);               //overlaps checking
  
  //G4VisAttributes* shapePhVisAtt= new G4VisAttributes(G4Colour(1.0,0.0,0.0));
  //logicshapePh->SetVisAttributes(shapePhVisAtt); 
         
  //G4LogicalVolume* logicshape_Si =
  //  new G4LogicalVolume(shapeIN,            //its solid
  //                      shape_Si,           //its material
  //                      "Si");              //its name

  //new G4PVPlacement(0,                       //no rotation
  //                  G4ThreeVector(0,0,0),    //at (0,0,0)
  //                  logicshape_Si,           //its logical volume
  //                  "Si",                    //its name
  //                  logicEnv,                //its mother  volume
  //                  false,                   //no boolean operation
  //                  0,                       //copy number
  //                  checkOverlaps);          //overlaps checking     

  //////////////////////////////////////////
