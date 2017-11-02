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

#include "figaroEventAction.hh"
#include "figaroRunAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"

#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4THitsMap.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

figaroEventAction::figaroEventAction(figaroRunAction* runAction)
 : G4UserEventAction(), 
   fRunAction(runAction),
   fID_vol1(-1),
   fID_vol2(-1)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

figaroEventAction::~figaroEventAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void figaroEventAction::BeginOfEventAction(const G4Event* /*evt*/)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void figaroEventAction::EndOfEventAction(const G4Event* evt )
{
  //Hits collections  
  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
  if(!HCE) return;
               
   // Get hits collections IDs
  if (fID_vol1 < 0) {
    G4SDManager* SDMan = G4SDManager::GetSDMpointer();  
    fID_vol1 = SDMan->GetCollectionID("vol1/dose1");
    fID_vol2 = SDMan->GetCollectionID("vol2/dose2");    
  }
  
  //Dose deposit in volumes
  G4double dose1 = 0.;
  G4double dose2 = 0.;
  
  std::map<G4int,G4double*>::iterator itr;
   
  auto evtMap1 = (G4THitsMap<G4double>*)(HCE->GetHC(fID_vol1));
  auto evtMap2 = (G4THitsMap<G4double>*)(HCE->GetHC(fID_vol2));  
             
  for (itr = evtMap1->GetMap()->begin(); itr != evtMap1->GetMap()->end(); itr++) {
    dose1 = *(itr->second);
  }
  for (itr = evtMap2->GetMap()->begin(); itr != evtMap2->GetMap()->end(); itr++) {
    dose2 = *(itr->second);
  }

  if (dose1 > 0.) fRunAction->SumDose1(dose1);
  if (dose2 > 0.) fRunAction->SumDose2(dose2);
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
