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
// $ 07/2017 lindbohansen@gmail.com $
//

#include "figaroDetectorConstruction.hh"

#include "G4AutoDelete.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4Trap.hh"
#include "G4EllipticalTube.hh"
#include "G4Region.hh"
#include "G4UserLimits.hh"
#include "G4ProductionCuts.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4UniformMagField.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RegionStore.hh"

#include "G4NistManager.hh"
#include "G4UnitsTable.hh"

#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4RunManager.hh" 

#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSDoseDeposit.hh"
#include "G4PSNofSecondary.hh"

//#include "figaroPSKerma.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4VisAttributes.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

figaroDetectorConstruction::figaroDetectorConstruction()
: G4VUserDetectorConstruction(),
	fCheckOverlaps(true)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

figaroDetectorConstruction::~figaroDetectorConstruction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* figaroDetectorConstruction::Construct()
{
	DefineMaterials();
  	return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void figaroDetectorConstruction::DefineMaterials()
{

  auto nistManager = G4NistManager::Instance();
  
  auto air_density = 0.001299*g/cm3;
  nistManager->BuildMaterialWithNewDensity("AIR_DEFAULT","G4_AIR",air_density); 

  auto steel_eff_density = 7.3*g/cm3;
  nistManager->BuildMaterialWithNewDensity("STEEL_DEFAULT","G4_STAINLESS-STEEL",steel_eff_density);

  nistManager->FindOrBuildMaterial("G4_CONCRETE");
  nistManager->FindOrBuildMaterial("G4_Pb");
  nistManager->FindOrBuildMaterial("G4_Co");
  //nistManager->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  nistManager->FindOrBuildMaterial("G4_WATER");
  nistManager->FindOrBuildMaterial("G4_PLEXIGLASS");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  
G4VPhysicalVolume* figaroDetectorConstruction::DefineVolumes()
{

  auto fWorldMaterial = G4Material::GetMaterial("AIR_DEFAULT");
  auto fConcrete = G4Material::GetMaterial("G4_CONCRETE");
  auto fLead = G4Material::GetMaterial("G4_Pb");
  auto fCobalt = G4Material::GetMaterial("G4_Co");
  auto fSteel = G4Material::GetMaterial("STEEL_DEFAULT");
  auto fWater = G4Material::GetMaterial("G4_WATER");
  auto fPlexiglass = G4Material::GetMaterial("G4_PLEXIGLASS");

  auto vWorldWidth     = 9.*m;
  auto vWorldHeight    = 4.*m;
  auto vWorldLength    = 22.*m;

  auto vRoomFrontWidth  = 5.2*m;
  auto vRoomFrontHeight = 2.940*m;
  auto vRoomFrontLength = 10.215*m;

  auto vRoomBackWidth  = 6.7*m;
  auto vRoomBackHeight = 2.940*m;
  auto vRoomBackLength = 10.3*m;

  auto vHousingWidth   = 80.*cm;
  auto vHousingHeight  = 91.7*cm;
  auto vHousingLength  = 80.*cm;

  auto vInnerWidth     = 6.9*cm;
  auto vInnerHeight    = 5.5*cm;

  auto vOuterWidth     = 11.4*cm; // was 11.6*cm
  auto vOuterHeight    = 9.5*cm;
  auto vOuterLength    = 21.*cm;

  auto vSourceChamberWidth  = 7.*cm; // was 10.*cm
  auto vSourceChamberHeight = 7.*cm; // was 10.*cm
  auto vSourceChamberLength = 7.*cm; // was 10.*cm

  auto vSteelSourceWidth  = 3.0*cm;
  auto vSteelSourceHeight = 6.9*cm;
  auto vSteelSourceLength = 3.0*cm; 

  auto vInnerSteelSourceWidth  = 1.0*cm;
  auto vInnerSteelSourceHeight = 6.9*cm;
  auto vInnerSteelSourceLength = 1.0*cm; 

  auto vThinWallThickness = 1.*cm; // was 10.*cm // was 5.*cm
  auto vThinWallWidth  = vRoomBackWidth-vRoomFrontWidth-vThinWallThickness;
  auto vThinWallHeight = vRoomFrontHeight;
  auto vThinWallLength = vRoomFrontLength-vThinWallThickness;

  auto vHousingDistanceFromSideWall = 1.085*m;
  auto vHousingDistanceFromFrontWall = 0.63*m;
  auto vOuterHeightAboveFloor = 71.*cm; // This means floor of collimator is 70 cm up from room floor
  auto vFocusDisplacement = 1.7*cm; // This means outer collimator opening is 41.7 cm from center of source

  auto vInnerLength    = vHousingLength/2-vSourceChamberLength/2-vOuterLength+vFocusDisplacement;
  auto vOuterAngle   = std::atan((vOuterHeight/2-vInnerHeight/2)/vOuterLength);
  auto vAdjustDisplacement = std::tan(vOuterAngle)*vOuterLength/2;


  G4Box* sWorld = new G4Box("World",vWorldWidth/2,vWorldHeight/2,vWorldLength/2);
  //G4LogicalVolume* lWorld = new G4LogicalVolume(sWorld,fWorldMaterial,"World");
  G4LogicalVolume* lWorld = new G4LogicalVolume(sWorld,fConcrete,"World"); // was G4_CONCRETE
  G4VPhysicalVolume* pWorld = new G4PVPlacement(0,G4ThreeVector(),lWorld,"World",0,false,0);

  G4Box* sRoomFront = new G4Box("RoomFront",vRoomFrontWidth/2,vRoomFrontHeight/2,vRoomFrontLength/2);   
  G4LogicalVolume* fLRoomFront = new G4LogicalVolume(sRoomFront,fWorldMaterial,"RoomFront");
  new G4PVPlacement(0,G4ThreeVector(0,0,-vRoomFrontLength/2),fLRoomFront,"RoomFront",lWorld,false,0);

  G4Box* sRoomBack = new G4Box("RoomBack",vRoomBackWidth/2,vRoomBackHeight/2,vRoomBackLength/2);
  G4LogicalVolume* fLRoomBack = new G4LogicalVolume(sRoomBack,fWorldMaterial,"RoomBack");
  new G4PVPlacement(0,G4ThreeVector(-(vRoomBackWidth-vRoomFrontWidth)/2,0,+vRoomBackLength/2),fLRoomBack,"RoomBack",lWorld,false,0);

  G4Box* sThinWall = new G4Box("ThinWall",vThinWallWidth/2,vThinWallHeight/2,vThinWallLength/2);
  G4LogicalVolume* fLThinWall = new G4LogicalVolume(sThinWall,fWorldMaterial,"ThinWall");
  new G4PVPlacement(0,G4ThreeVector(-vRoomFrontWidth/2-vThinWallWidth/2-vThinWallThickness,0,-vRoomFrontLength/2-vThinWallThickness/2),fLThinWall,"ThinWall",lWorld,false,0);


	G4Box* sHousing = new G4Box("Housing",vHousingWidth/2+vFocusDisplacement,vHousingHeight/2,vHousingLength/2+vFocusDisplacement);
	G4LogicalVolume* fLHousing = new G4LogicalVolume(sHousing,fLead,"Housing");
	//new G4PVPlacement(0,G4ThreeVector(0,0,0),fLHousing,"Housing",lWorld,false,0);
        new G4PVPlacement(0,G4ThreeVector(-vRoomFrontWidth/2+vHousingDistanceFromSideWall,-vRoomFrontHeight/2+vHousingHeight/2,-vRoomFrontLength/2+vHousingDistanceFromFrontWall),fLHousing,"Housing",fLRoomFront,false,0);
      
	G4Box* sInner = new G4Box("Inner",vInnerWidth/2,vInnerHeight/2,vInnerLength/2);
	G4LogicalVolume* fLInner = new G4LogicalVolume(sInner,fWorldMaterial,"Inner");
	//new G4PVPlacement(0,G4ThreeVector((17.5/2+2.)*cm,(-160./2+5.5/2+72.)*cm,0),fLInner,"Inner",fLHousing,false,0);
	new G4PVPlacement(0,G4ThreeVector(0,-vHousingHeight/2+vInnerHeight/2+vOuterHeightAboveFloor-vAdjustDisplacement,vInnerLength/2+vSourceChamberLength/2),fLInner,"Inner",fLHousing,false,0);

	G4RotationMatrix* rotOuter = new G4RotationMatrix();
        rotOuter->rotateY(-90*deg);
        //G4Trd* sOuter = new G4Trd("Outer",6.9/2*cm,12.6/2*cm,5.5/2*cm,9.5/2*cm,20.5/2*cm);
	//G4Trap* sOuter = new G4Trap("Outer",20.5/2*cm,5.6*deg,90*deg,5.5/2*cm,6.9/2*cm,6.9/2*cm,0*deg,9.5/2*cm,12.6/2*cm,12.6/2*cm,0*deg);
        G4Trap* sOuter = new G4Trap("Outer",vOuterLength/2,vOuterAngle,90*deg,vInnerHeight/2,vInnerWidth/2,vInnerWidth/2,0*deg,vOuterHeight/2,vOuterWidth/2,vOuterWidth/2,0*deg);
        G4LogicalVolume* fLOuter = new G4LogicalVolume(sOuter,fWorldMaterial,"Outer");
	//G4RotationMatrix* rotOuter = new G4RotationMatrix();
	//rotOuter->rotateY(-90*deg);
	//new G4PVPlacement(rotOuter,G4ThreeVector((17.5+2+20.5/2)*cm,1.0*cm,0),fLOuter,"Outer",fLHousing,false,0);
        //new G4PVPlacement(rotOuter,G4ThreeVector((17.5+2+20.5/2)*cm,(-160./2+5.5/2+72.+0.6093)*cm,0),fLOuter,"Outer",fLHousing,false,0);
        new G4PVPlacement(0,G4ThreeVector(0,-vHousingHeight/2+vInnerHeight/2+vOuterHeightAboveFloor,vOuterLength/2+vSourceChamberLength/2+vInnerLength),fLOuter,"Outer",fLHousing,false,0);

	G4Box* sSourceChamber = new G4Box("SourceChamber",vSourceChamberWidth/2,vSourceChamberHeight/2,vSourceChamberLength/2);
	G4LogicalVolume* fLSourceChamber = new G4LogicalVolume(sSourceChamber,fWorldMaterial,"SourceChamber");
	//new G4PVPlacement(0,G4ThreeVector(0,-vHousingHeight/2+vInnerHeight/2+vOuterHeightAboveFloor-vAdjustDisplacement,0),fLSourceChamber,"SourceChamber",fLHousing,false,0);
        new G4PVPlacement(0,G4ThreeVector(0,-vHousingHeight/2+vSourceChamberHeight/2+vOuterHeightAboveFloor-vAdjustDisplacement,0),fLSourceChamber,"SourceChamber",fLHousing,false,0);

        G4RotationMatrix* rotSteel = new G4RotationMatrix();
	rotSteel->rotateX(90*deg);

	G4EllipticalTube* sSteelSource = new G4EllipticalTube("SteelSource",vSteelSourceWidth/2,vSteelSourceLength/2,vSteelSourceHeight/2);
        G4LogicalVolume* fLSteelSource = new G4LogicalVolume(sSteelSource,fSteel,"SteelSource");
        new G4PVPlacement(rotSteel,G4ThreeVector(0,-vSourceChamberHeight/2+vSteelSourceHeight/2,0),fLSteelSource,"SteelSource",fLSourceChamber,false,0);
        //new G4PVPlacement(rotBottom,G4ThreeVector(0,-vSourceChamberHeight/2-((vSteelTopSourceHeight+vSteelBottomSourceHeight)/2)/2,0),fLSteelBottomSource,"SteelBottomSource",fLSourceChamber,false,0);

	G4EllipticalTube* sInnerSteelSource = new G4EllipticalTube("InnerSteelSource",vInnerSteelSourceWidth/2,vInnerSteelSourceLength/2,vInnerSteelSourceHeight/2);
        G4LogicalVolume* fLInnerSteelSource = new G4LogicalVolume(sInnerSteelSource,fSteel,"InnerSteelSource");
        new G4PVPlacement(0,G4ThreeVector(0,0,0),fLInnerSteelSource,"InnerSteelSource",fLSteelSource,false,0);
        //new G4PVPlacement(rotBottom,G4ThreeVector(0,-vSourceChamberHeight/2-((vSteelTopSourceHeight+vSteelBottomSourceHeight)/2)/2,0),fLSteelBottomSource,"SteelBottomSource",fLSourceChamber,false,0);
        
  return pWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void figaroDetectorConstruction::ConstructSDandField(){
	G4SDManager::GetSDMpointer()->SetVerboseLevel(3);

auto SD1 = new G4MultiFunctionalDetector("vol1");
G4SDManager::GetSDMpointer()->AddNewDetector(SD1);
G4VPrimitiveScorer* dose1 = new G4PSDoseDeposit("dose1");
SD1->RegisterPrimitive(dose1);
SetSensitiveDetector("RoomFront",SD1);

auto SD2 = new G4MultiFunctionalDetector("vol2");
G4SDManager::GetSDMpointer()->AddNewDetector(SD2);
G4VPrimitiveScorer* dose2 = new G4PSDoseDeposit("dose2");
SD2->RegisterPrimitive(dose2);
SetSensitiveDetector("RoomBack",SD2);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
