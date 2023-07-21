#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TTree.h"
#include "TLatex.h"
#include "TAttMarker.h"
#include "TStyle.h"

using namespace std;

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

//Constants of the simulation on Geant4
const int npxl_row = 50; //rows
const int npxl_col = 100; //columns

//Fonction tri d'une liste dans l'ordre croissant
void Tri(int *t, int length){
    int i, mini, j, x;
    for (i = 0; i < length - 1; i++){
        mini = i;
        for (j = i + 1; j < length; j++){
            if (t[j] < t[mini])
                mini = j;
        	}
        x = t[i];
        t[i] = t[mini];
        t[mini] = x;
    }
}

//Function identify shape of cluster
int ShapeCluster(int* List, int length){
	Tri(List, length);
	int p;
	if(length==1)
		return 0;
	if(length==2){
		if(List[1]==List[0]+npxl_row)
			return 1;
		if(List[1]==List[0]+1)
			return 2;
	}
	if(length==3){
		if(List[1]==List[0]+npxl_row && List[2]==List[0]+npxl_row+1)
			return 3;
		if(List[2]==List[0]+npxl_row-1)
			return 4;
		if(List[2]==List[0]+npxl_row*2)
			return 5;
		if(List[2]==List[0]+npxl_row)
			return 6;
		if(List[1]==List[0]+1 && List[2]==List[0]+npxl_row+1)
			return 7;
		if(List[2]==List[0]+2)
			return 8;
	}
	else
		return 9;
}


void Clusterisation(){
	//************************************************//

	TFile* f= new TFile(ED_TestBeam4,"read");
	TTree* tree = (TTree*) f-> Get(treename);

	TFile* f5= new TFile(ED_TestBeam5,"read");
	TTree* tree5 = (TTree*) f5-> Get(treename);

////////////////////////////////////////////////////////////////////
//                 Graph 1 - Position pixel hit
////////////////////////////////////////////////////////////////////

	TCanvas* c1 = new TCanvas;
	c1->SetGrid();

	//*********** Histo 2D : N vs Edep ****************//

	tree5->Draw("Ligne:Colonne>>GraphLC(35,5,40,95,5,100)", "","col");
	auto histoLC = (TH2D*)gPad->GetPrimitive("GraphLC");
	histoLC->SetTitle("#font[12]{Pixel hit}");
	histoLC->GetYaxis()->SetTitle("#font[12]{Row number }");
	histoLC->GetXaxis()->SetTitle("#font[12]{Column number }");
	histoLC->Draw("COLZ");
	gStyle->SetStatFont(12);
	gStyle->SetOptStat("e");

   	c1->SaveAs("PixelHitPosition.pdf");

////////////////////////////////////////////////////////////////////
//                 Graph 2 - Cluster Shape IDs
////////////////////////////////////////////////////////////////////

	TCanvas* c = new TCanvas;
	c->SetGrid();
	//c->Divide(2,1);

	int N = tree5->GetEntries();

	int n, row, col, numEvent;
	tree5->SetBranchAddress("EventID", &numEvent);
	tree5->SetBranchAddress("Ligne", &row);
	tree5->SetBranchAddress("Colonne", &col);

	//create a Tree file tree1.root
   	//create the file, the Tree and a few branches
   	TFile fCluster("tCluster.root","recreate");
   	TTree tCluster("tCluster","name");

//**********************************************************//

	Int_t NumShape;
	tCluster.Branch("NumShape",&NumShape,"NumShape/I");

	//Initialisation
	tree5->GetEntry(0);
	int eID=numEvent;
	int* List= (int*)malloc(4*sizeof(int));

	//Division euclidienne pour récupérer le numéro des pixels à partir des coordonnées:
  	//N = npxl_row*C + (npxl_row - L) avec C le numéro de colonne et L de la ligne
	List[0] = npxl_row * col + (npxl_row - row);

	int length=1; //1 elements

	//Loop
	for(int i=1; i<=N; i++){
		tree5->GetEntry(i);
		cout<<"Col = "<< col << endl;
		cout<<"Row = "<< row << endl;
		if(eID==numEvent){
			List[length] = npxl_row * col + (npxl_row - row);
			length+=1;
			cout<<"length = "<<	length << endl;
			cout<<"List[length] = "<<	List[length] << endl;
			cout<<"---------------------- "<< endl;
		}
		else{
			for(int j=length; j<=3; j++){
				List[j] = npxl_row * col + (npxl_row - row);
			}
			NumShape=ShapeCluster(List,length);
			tCluster.Fill();
			eID=numEvent;
			List[0] = npxl_row * col + (npxl_row - row);
			length=1;
		}
	}
	tCluster.Write();

//**********************************************************//
/*
	TFile fCluster1("tCluster1.root","recreate");
   	TTree tCluster1("tCluster1","name1");

	Int_t ClusterID;
	tCluster1.Branch("ClusterID",&ClusterID,"ClusterID/I");
	
	//Initialisation
	tree->GetEntry(0);
	eID=numEvent;
	int* List1= (int*)malloc(4*sizeof(int));
	List1[0] = npxl_row * col + row;
	length=1; //1 elements

	//Loop
	for(int i=1; i<=N; i++){
		tree->GetEntry(i);
		if(eID==numEvent){
			List1[length] = npxl_row * col + row;
			length=+1;			
		}
		else{
			for(int j=length; j<=3; j++){
				List1[j] = npxl_row * col + row;
			}
			ClusterID=ShapeCluster(List1,length);
			if(ClusterID!=0)
				tCluster.Fill();
			eID=numEvent;
			List1[0] = npxl_row * col + row;
			length=1;
		}
	}
	tCluster1.Write();
*/
//**********************************************************//

	//c->cd(1);
	tCluster.Draw("NumShape>>Clusterisation()", "","");
	auto histoCluster = (TH1D*)gPad->GetPrimitive("Clusterisation");
	histoCluster->SetTitle("#font[12]{Cluster hit};#font[12]{Cluster ID }");
	histoCluster->GetYaxis()->SetTitle("#font[12]{N count }");
	histoCluster->SetLineColor(kCyan+2);
	histoCluster->SetFillStyle(3003);
    histoCluster->SetFillColor(kCyan+2);
	histoCluster->DrawCopy();
	gStyle->SetStatFont(12);
	gStyle->SetOptStat("nem");
/*
	c->cd(2);
	tCluster1.Draw("ClusterID>>Clusterisation1()", "","");
	auto histoCluster1 = (TH1D*)gPad->GetPrimitive("Clusterisation1");
	histoCluster1->SetTitle("#font[12]{Cluster hit};#font[12]{Cluster ID }");
	histoCluster1->GetYaxis()->SetTitle("#font[12]{N count }");
	histoCluster1->SetLineColor(kOrange+1);
	histoCluster1->SetFillStyle(3003);
    histoCluster1->SetFillColor(kOrange+1);
	histoCluster1->DrawCopy();
*/
	c->SaveAs("Clusterisation.pdf");

//**********************************************************//

}