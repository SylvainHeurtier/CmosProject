#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TTree.h"
#include "TLatex.h"
#include "TAttMarker.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "THStack.h"
#include "TRandom.h"
#include "TString.h"
#include "TNtuple.h"

#include "TObjString.h"
#include <iostream>
#include <vector>
using namespace std;

////////////////////////////////////////////////////////////////////
/*
           /\
          /  \
         /    \
        /  ||  \
       /   ..   \
      /_ _ _ _ _ \
*/

//Constants of the simulation on Geant4 - DON'T FORGET TO UPDATE THEM !
const int npxl_row = 100; //rows
const int npxl_col = 50; //columns
const int n_pixels_tot = npxl_row*npxl_col;



void ApplyPixelCrossTalk(const char* filename, double Fleak, const char* new_filename)
{

    TFile f_init(filename,"read");
    TTree* InitTree = (TTree*) f_init. Get("Chip0");

    int n_entries = InitTree->GetEntries();

    int n, row, col, numEvent;
    double EnergyDeposit;
    InitTree->SetBranchAddress("EventID", &numEvent);
    InitTree->SetBranchAddress("Ligne", &row);
    InitTree->SetBranchAddress("Colonne", &col);
    InitTree->SetBranchAddress("Edep", &EnergyDeposit);

    //create a Tree file tree1.root
    //create the file, the Tree and a few branches
    TNtuple tuple("tuple","pixel processed with pixel", "EventID:Ligne:Colonne:Edep:Enoise:Eleak:Ecrosstalk");

    double TabEdep[npxl_row][npxl_col];
    double TabEleak[npxl_row][npxl_col];
    double TabEcrosstalk[npxl_row][npxl_col];
    double TabEnoise[npxl_row][npxl_col];

    int Ligne, Colonne, EventID;
    double Edep, Enoise, Eleak, Ecrosstalk;

    //Initialisation
    InitTree->GetEntry(0);
    int eID = numEvent;

    for (int r=0; r<npxl_row; r++){
        for (int c=0; c<npxl_col; c++){
            TabEdep[r][c]       = 0;
            TabEleak[r][c]      = 0;
            TabEcrosstalk[r][c] = 0;
            TabEnoise[r][c]     = 0;
        }
    }
    TRandom *Random = new TRandom();

    //Loop on all events
    for(int i=0; i<n_entries; i++){
        InitTree->GetEntry(i);

        if(eID==numEvent){

            TabEdep[row][col] += EnergyDeposit;
            TabEnoise[row][col] = Random->Gaus(0,0.01);

            if(row>0 && row<npxl_row-1 && col>0 && col<npxl_col-1 ){
                //cout<<" COUCOU 1 "<<endl;
                //Pixel au dessus
                TabEleak[row][col]        -= Fleak*EnergyDeposit;
                TabEcrosstalk[row+1][col] += Fleak*EnergyDeposit;
                TabEnoise[row+1][col]     = Random->Gaus(0,0.01); //Random->Gaus(Double_t mean=0, Double_t sigma=1)
                
                //Pixel à droite
                TabEleak[row][col]        -= Fleak*EnergyDeposit;
                TabEcrosstalk[row][col+1] += Fleak*EnergyDeposit;
                TabEnoise[row][col+1]     = Random->Gaus(0,0.01);
                
                //Pixel en dessous
                TabEleak[row][col]        -= Fleak*EnergyDeposit;
                TabEcrosstalk[row][col+1] += Fleak*EnergyDeposit;
                TabEnoise[row][col+1]     = Random->Gaus(0,0.01);
                
                //Pixel à gauche
                TabEleak[row][col]        -= Fleak*EnergyDeposit;
                TabEcrosstalk[row][col-1] += Fleak*EnergyDeposit;
                TabEnoise[row][col-1]     = Random->Gaus(0,0.01);
            }

            if(row==0){
                //cout<<" COUCOU 2 "<<endl;
                //Pixel au dessus
                TabEleak[row][col]        -= Fleak*EnergyDeposit;
                TabEcrosstalk[row+1][col] += Fleak*EnergyDeposit;
                TabEnoise[row+1][col]     = Random->Gaus(0,0.01);
            }

            if(col==0){
                //cout<<" COUCOU 3"<<endl;
                //Pixel à droite
                TabEleak[row][col]        -= Fleak*EnergyDeposit;
                TabEcrosstalk[row][col+1] += Fleak*EnergyDeposit;
                TabEnoise[row][col+1]     = Random->Gaus(0,0.01);
            }

            if(row==npxl_row-1){
                //cout<<" COUCOU 4"<<endl;
                //Pixel en dessous
                TabEleak[row][col]        -= Fleak*EnergyDeposit;
                TabEcrosstalk[row-1][col] += Fleak*EnergyDeposit;
                TabEnoise[row-1][col]     = Random->Gaus(0,0.01);
            }

            if(col==npxl_col-1){
                //cout<<" COUCOU 5"<<endl;
                //Pixel à gauche
                TabEleak[row][col]        -= Fleak*EnergyDeposit;
                TabEcrosstalk[row][col-1] += Fleak;
                TabEnoise[row][col-1]     = Random->Gaus(0,0.01);
            }

            // last entries
            if(i==n_entries-1){
                //cout<<" last entries"<<endl;
                for (int r=0; r<npxl_row; r++){
                    for (int c=0; c<npxl_col; c++){
                        if(TabEdep[r][c] >0 || TabEleak[r][c] <0 || TabEcrosstalk[r][c] >0 || TabEnoise[r][c]<0){
                            Ligne      =r;
                            Colonne    =c;

                            InitTree->GetEntry(i-1);
                            EventID    =numEvent;
                            InitTree->GetEntry(i);

                            Edep       = TabEdep[r][c];
                            Enoise     = TabEnoise[r][c];
                            Eleak      = TabEleak[r][c];
                            Ecrosstalk = TabEcrosstalk[r][c];
                        }
                    }
                }

                // EventID:Ligne:Colonne:Edep:Enoise:Eleak:Ecrosstalk
                tuple.Fill(eID,Ligne,Colonne,Edep,Enoise,Eleak,Ecrosstalk);
            }
        } else {
            
            //cout<<"******** i = "<< i << "********" <<endl;
            for (int r=0; r<npxl_row; r++){
                for (int c=0; c<npxl_col; c++){
                    if(TabEdep[r][c]>0 || TabEleak[r][c]<0 || TabEcrosstalk[r][c]>0 || TabEnoise[r][c]<0){
                        
                        Ligne      =r;
                        Colonne    =c;

                        InitTree->GetEntry(i-1);
                        EventID    =numEvent;
                        InitTree->GetEntry(i);

                        Edep       = TabEdep[r][c];
                        Eleak      = TabEleak[r][c];
                        Enoise     = TabEnoise[r][c];
                        Ecrosstalk = TabEcrosstalk[r][c];
                    }
                }
            }

            // EventID:Ligne:Colonne:Edep:Enoise:Eleak:Ecrosstalk
            tuple.Fill(EventID,Ligne,Colonne,Edep,Enoise,Eleak,Ecrosstalk);

            eID=numEvent;
            for (int r=0; r<npxl_row; r++){
                for (int c=0; c<npxl_col; c++){
                    TabEdep[r][c]       = 0;
                    TabEleak[r][c]      = 0;
                    TabEcrosstalk[r][c] = 0;
                    TabEnoise[r][c]     = 0;
                }
            }

            TabEdep[row][col] += EnergyDeposit;
            TabEnoise[row][col] = Random->Gaus(0,0.01);

            if(row>0 && row<npxl_row-1 && col>0 && col<npxl_col-1 ){
                //Pixel au dessus
                TabEleak[row][col]        -= Fleak*EnergyDeposit;
                TabEcrosstalk[row+1][col] += Fleak*EnergyDeposit;
                TabEnoise[row+1][col]     = Random->Gaus(0,0.01); //Random->Gaus(Double_t mean=0, Double_t sigma=1)
                //Pixel à droite
                TabEleak[row][col]        -= Fleak*EnergyDeposit;
                TabEcrosstalk[row][col+1] += Fleak*EnergyDeposit;
                TabEnoise[row][col+1]     = Random->Gaus(0,0.01);
                //Pixel en dessous
                TabEleak[row][col]        -= Fleak*EnergyDeposit;
                TabEcrosstalk[row][col+1] += Fleak*EnergyDeposit;
                TabEnoise[row][col+1]     = Random->Gaus(0,0.01);
                //Pixel à gauche
                TabEleak[row][col]        -= Fleak*EnergyDeposit;
                TabEcrosstalk[row][col-1] += Fleak*EnergyDeposit;
                TabEnoise[row][col-1]     = Random->Gaus(0,0.01);
            }

            if(row==0){ 
                //Pixel au dessus
                TabEleak[row][col]        -= Fleak*EnergyDeposit;
                TabEcrosstalk[row+1][col] += Fleak*EnergyDeposit;
                TabEnoise[row+1][col]     = Random->Gaus(0,0.01);
            }

            if(col==0){
                //Pixel à droite
                TabEleak[row][col]        -= Fleak*EnergyDeposit;
                TabEcrosstalk[row][col+1] += Fleak*EnergyDeposit;
                TabEnoise[row][col+1]     = Random->Gaus(0,0.01);               
            }

            if(row==npxl_row-1){
                //Pixel en dessous
                TabEleak[row][col]        -= Fleak*EnergyDeposit;
                TabEcrosstalk[row-1][col] += Fleak*EnergyDeposit;
                TabEnoise[row-1][col]     = Random->Gaus(0,0.01);
            }

            if(col==npxl_col-1){
                //Pixel à gauche
                TabEleak[row][col]        -= Fleak*EnergyDeposit;
                TabEcrosstalk[row][col-1] += Fleak;
                TabEnoise[row][col-1]     = Random->Gaus(0,0.01);
            }
        }
    }
    cout<<"--------------------------------"<<endl;

    f_init.Close();

    cout<< "f_init Close OK"<<endl;

    TFile f_final(new_filename,"recreate");
    tuple.Write();
    f_final.Close();

    cout<<"Write ok"<<endl;
}


void ComputeChipResponse(){

    double Ethreshold = 0.01; // MeV
    double Fleak = 5./100.; // MeV
    int n_files = 2;
    auto filenames = new TObjArray(n_files);
    filenames->Add((TObject*) new TString("/Users/ba272880/bin/CmosProject/build/sim_0deg_1000Evt_10000part_radius30um.root"));
    filenames->Add((TObject*) new TString("/Users/ba272880/bin/CmosProject/build/sim_20deg_1000Evt_10000part_radius30um.root"));

    //************************************************//
    
    for (int i = 0; i < filenames->GetEntriesFast(); ++i){
        const char* filename = ((TString*) filenames->At(i))->Data();
        TString new_filename(filename);
        new_filename.ReplaceAll(".root","_with_crosstalk.root");
        new_filename.ReplaceAll("build","Macro");

        ApplyPixelCrossTalk(filename, Fleak, new_filename.Data());
        cout<<"ApplyPixelCrossTalk "<< new_filename.Data() << " deg - OK"<<endl;
    }
    cout<<"--------------------------------"<<endl;
}