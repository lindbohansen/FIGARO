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

#ifndef figaroDetectorConstruction_h
#define figaroDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

class G4Region;
class G4LogicalVolume;
class G4PhysicalVolume;

class G4VPhysicalVolume; // in B4d..

class G4Material;
class G4UserLimits;
class G4ProductionCuts;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class figaroDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
    figaroDetectorConstruction();
    virtual ~figaroDetectorConstruction();

  public:
	
  // G4Region* sourceRegion;
  //G4Region* roomRegion;

  public:

     virtual G4VPhysicalVolume* Construct();
     virtual void ConstructSDandField();
     
  private:
    
     void DefineMaterials();
     G4VPhysicalVolume* DefineVolumes();

     G4bool fCheckOverlaps;     
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

