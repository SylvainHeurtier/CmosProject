#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TTree.h"
#include "TLatex.h"
#include "TAttMarker.h"
#include "TStyle.h"
#include "TCanvas.h"

#include <iostream>
#include <vector>
using namespace std;

////////////////////////////////////////////////////////////////////

//Constants of the simulation on Geant4 - DON'T FORGET TO UPDATE THEM !
const int npxl_row = 50; //rows
const int npxl_col = 100; //columns

////////////////////////////////////////////////////////////////////
// Fonction tri d'une liste dans l'ordre croissant
////////////////////////////////////////////////////////////////////

/**
 * @brief      { La fonction Tri() prend en argument une liste 
 * (et sa taille) et permet de trier ses éléments dans l'ordre croissant }
 *
 * @param      t       { liste d'entier à trier}
 * @param[in]  length  {dimension de la liste t}
 */
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

void TriVector(std::vector<int> v){
    int i, mini, j, x;
    int length = v.size();
    for (i = 0; i < length - 1; i++){
        mini = i;
        for (j = i + 1; j < length; j++){
            if (v.at(j)< v.at(mini))
                mini = j;
        	}
        x = v.at(i);
        v.at(i) = v.at(mini);
        v.at(mini) = x;
    }
}

////////////////////////////////////////////////////////////////////
// Function which identify shape of cluster
////////////////////////////////////////////////////////////////////

/**
 * @brief      { Function which identify shape of cluster }
 *
 * @param      List    { Liste des numéros des pixels touchés 
 * classés dans l'ordre croissant }
 * @param[in]  length  { Nombre de pixels dans le cluster }
 *
 * @return     { Cette fonction renvoie l'identifiant associé à la 
 * forme du cluster selon la classification de l'article du Summer 
 * Student Project de Natalia Emriskova - 2017 }
 */

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
	if(length==4){
		if(List[1]==List[0]+npxl_row-1 && List[3]==List[0]+npxl_row+1)
			return 9;
		if(List[2]==List[0]+npxl_row+1 && List[3]==List[0]+npxl_row*2)
			return 10;
		if(List[2]==List[0]+npxl_row*2 && List[3]==List[0]+npxl_row*2+1)
			return 11;
		if(List[1]==List[0]+1 && List[2]==List[0]+npxl_row && List[3]==List[0]+npxl_row-1)
			return 12;
		if(List[1]==List[0]+1 && List[2]==List[0]+npxl_row && List[3]==List[0]+npxl_row+1)
			return 13;
		if(List[1]==List[0]+npxl_row && List[3]==List[0]+npxl_row+2)
			return 14;
		if(List[1]==List[0]+npxl_row && List[2]==List[0]+npxl_row+1 && List[3]==List[0]+npxl_row*2+1)
			return 15;
		if(List[1]==List[0]+npxl_row-1 && List[3]==List[0]+npxl_row+2)
			return 16;
		if(List[1]==List[0]+npxl_row*2-1 && List[3]==List[0]+npxl_row*2)
			return 17;
		if(List[1]==List[0]+1 && List[2]==List[0]+npxl_row-1)
			return 18;
		if(List[1]==List[0]+npxl_row-2)
			return 19;
		if(List[1]==List[0]+npxl_row-1 && List[2]==List[0]+npxl_row*2)
			return 20;
		if(List[3]==List[0]+npxl_row*3)
			return 21;
		if(List[1]==List[0]+1 && List[3]==List[0]+npxl_row*2)
			return 22;
		if(List[1]==List[0]+1 && List[3]==List[0]+npxl_row*2+1)
			return 23;
		if(List[1]==List[0]+npxl_row-1 && List[3]==List[0]+npxl_row+1)
			return 24;
		if(List[1]==List[0]+2 && List[3]==List[0]+npxl_row)
			return 25;
		if(List[1]==List[0]+2 && List[3]==List[0]+npxl_row+2)
			return 26;
		if(List[3]==List[0]+3)
			return 27;
	}
	else
		return 28;
}

int ShapeCluster2(std::vector<int> V){
	int length = V.size();
	TriVector(V);
	int p;
	if(length==1)
		return 0;
	if(length==2){
		if(V[1]==V[0]+npxl_row)
			return 1;
		if(V[1]==V[0]+1)
			return 2;
	}
	if(length==3){
		if(V[1]==V[0]+npxl_row && V[2]==V[0]+npxl_row+1)
			return 3;
		if(V[2]==V[0]+npxl_row-1)
			return 4;
		if(V[2]==V[0]+npxl_row*2)
			return 5;
		if(V[2]==V[0]+npxl_row)
			return 6;
		if(V[1]==V[0]+1 && V[2]==V[0]+npxl_row+1)
			return 7;
		if(V[2]==V[0]+2)
			return 8;
	}
	if(length==4){
		if(V[1]==V[0]+npxl_row-1 && V[3]==V[0]+npxl_row+1)
			return 9;
		if(V[2]==V[0]+npxl_row+1 && V[3]==V[0]+npxl_row*2)
			return 10;
		if(V[2]==V[0]+npxl_row*2 && V[3]==V[0]+npxl_row*2+1)
			return 11;
		if(V[1]==V[0]+1 && V[2]==V[0]+npxl_row && V[3]==V[0]+npxl_row-1)
			return 12;
		if(V[1]==V[0]+1 && V[2]==V[0]+npxl_row && V[3]==V[0]+npxl_row+1)
			return 13;
		if(V[1]==V[0]+npxl_row && V[3]==V[0]+npxl_row+2)
			return 14;
		if(V[1]==V[0]+npxl_row && V[2]==V[0]+npxl_row+1 && V[3]==V[0]+npxl_row*2+1)
			return 15;
		if(V[1]==V[0]+npxl_row-1 && V[3]==V[0]+npxl_row+2)
			return 16;
		if(V[1]==V[0]+npxl_row*2-1 && V[3]==V[0]+npxl_row*2)
			return 17;
		if(V[1]==V[0]+1 && V[2]==V[0]+npxl_row-1)
			return 18;
		if(V[1]==V[0]+npxl_row-2)
			return 19;
		if(V[1]==V[0]+npxl_row-1 && V[2]==V[0]+npxl_row*2)
			return 20;
		if(V[3]==V[0]+npxl_row*3)
			return 21;
		if(V[1]==V[0]+1 && V[3]==V[0]+npxl_row*2)
			return 22;
		if(V[1]==V[0]+1 && V[3]==V[0]+npxl_row*2+1)
			return 23;
		if(V[1]==V[0]+npxl_row-1 && V[3]==V[0]+npxl_row+1)
			return 24;
		if(V[1]==V[0]+2 && V[3]==V[0]+npxl_row)
			return 25;
		if(V[1]==V[0]+2 && V[3]==V[0]+npxl_row+2)
			return 26;
		if(V[3]==V[0]+3)
			return 27;
	}

	return 28;
}


////////////////////////////////////////////////////////////////////
// Differentiate Shape in all pixels it in one event
////////////////////////////////////////////////////////////////////

/**
 * @brief      { Differentiate Shape in all pixels it in one event }
 *
 * @param      Vector    { Vecteur avec les numéros des pixels touchés 
 * rangés dans l'ordre croissant}
 *
 * @return     { Liste des identifiants associés à la 
 * forme du cluster selon la classification de l'article du Summer 
 * Student Project de Natalia Emriskova - 2017 }
 */
std::vector<int> DifferentiateShape(std::vector<int> V){
	// Le vecteur V est composé des numéros des pixels 
	// touchés triés dans l'ordre croissant.
	//
	// Si le premier élément de V est le numéro N, on va regarder si 
	// ces pixels voisins de numéro supérieur à N (car la liste est triée)
	// ont eux aussi été touchés.
	// 
	// Grille des numéros de pixels
	//  ...
	//   x | N+3 | N+npxl_row+2 | N+2*npxl_row+2 | ...
	//   x | N+2 | N+npxl_row+1 | N+2*npxl_row+1 | ...
	//   x | N+1 | N+npxl_row   | N+2*npxl_row   | ...
	//   x |  N  | N+npxl_row-1 | N+2*npxl_row-1 | ...
	//   x |  x  | N+npxl_row-2 | N+2*npxl_row-2 | ...
	//   x |  x  | N+npxl_row-3 | N+2*npxl_row-3 | ...
	//   x |  x  | N+npxl_row-4 | N+n2*pxl_row-4 | ...
	//  ...
	//  
 	std::vector<int> VectorClusterID;
 	std::vector<int> VectorVar;
 	int Couronne = 0;
 	int taille ;
 	taille = V.size();
 	while(V.size()!=0){
 		int i, j = 1;
 		int j_intermediaire;
 		int N = V.at(0); //numéro de pixel le plus petit du vecteur V
 		if(Couronne== 0){
 			if (taille==1){
 				VectorClusterID.push_back(0);
 				return VectorClusterID;
 			}
 			if (V.at(1)!=N+1 && V.at(1)!=N+npxl_row){
 				// On ajoute l'identifiant correspondant à 1 pixel touché = 0
 				VectorClusterID.push_back(0);
 				// On supprime le pixel déjà répertorié dans VectorClusterID
 				V.erase(V.begin());
 				taille = V.size();
 			}
 			else{
 				Couronne+=1;
 			}
 		}
 		//********************* COURONNE 1 ***************************
 		if(Couronne== 1){
			//
			// V.at(0) = N est le pixel de départ autour duquel on va regarder 
			// successivement si les pixels voisins sont touchés
			// 
			// On ajoute le numéro du pixel dans le vecteur VectorVar
			VectorVar.push_back(N);
			//
			for(i=-1; i<=1; i++){ //on étudie les 3 pixels adjacents placés sur la colonne de droite
				if(j<taille && V.at(j)==N+i+npxl_row){
					// On ajoute le numéro du pixel dans le vecteur VectorVar
					VectorVar.push_back(V.at(j));
					j+=1;
				}
			}
			if(j<taille && V.at(j)==N+1){
				VectorVar.push_back(V.at(j));
				j+=1;
			}
 			Couronne+=1;
 			j_intermediaire = j;
 		}
 		//********************* COURONNE 2 ***************************
 		if(Couronne== 2){
			//
			if(j<taille && V.at(j)==N+2){
				VectorVar.push_back(V.at(j));
				j+=1;
			}
			if(j<taille && V.at(j)==N+npxl_row-2){
				VectorVar.push_back(V.at(j));
				j+=1;
			}
			if(j<taille && V.at(j)==N+npxl_row+2){
				VectorVar.push_back(V.at(j));
				j+=1;
			}
			for(i=-2; i<=2; i++){ //on étudie les 5 pixels adjacents placés sur la colonne de droite
				if(j<taille && V.at(j)==N+i+2*npxl_row){
					VectorVar.push_back(V.at(j));
					j+=1;
				}
			}
			// TESTS POUR PASSAGE A LA COURONNE SUIVANTE
			if(j_intermediaire == j){ 
				//
				// Aucun pixel voisin de la deuxième couronne de N a été touché
				// On identifie la forme obtenue de l'ensemble des pixels touchés
				// puis on supprime ces pixels du vecteur V pour ne pas les 
				// compter plusieurs fois
				// 
				VectorClusterID.push_back(ShapeCluster2(VectorVar));
				//on supprime les pixels déjà étudiés
				V.erase(V.begin(),V.begin()+j-1);

				taille = V.size();
				// On réinitialise Couronne pour recommencer la même
				// logique à partir d'un nouveau pixel
				Couronne=0; 
			}
			if(j_intermediaire != j){
				Couronne+=1;
				j_intermediaire = j;
			}
 		}
 		//********************* COURONNE 3 ***************************
 		if(Couronne== 3){
 			if(j<taille && V.at(j)==N+3){
				VectorVar.push_back(V.at(j));
				j+=1;
			}
 			for(i=1;i<=2;i++){
 				if(j<taille && V.at(j)==N+i*npxl_row-3){
					VectorVar.push_back(V.at(j));
					j+=1;
				}
				if(j<taille && V.at(j)==N+i*npxl_row+3){
					VectorVar.push_back(V.at(j));
					j+=1;
				}
 			}
 			for(i=-3; i<=3; i++){ //on étudie les 7 pixels adjacents placés sur la colonne de droite
				if(j<taille && V.at(j)==N+i+3*npxl_row){
					VectorVar.push_back(V.at(j));
					j+=1;
				}
			}
			// TESTS POUR PASSAGE A LA COURONNE SUIVANTE
			if(j_intermediaire == j){
				//
				// Aucun pixel voisin de la troisième couronne de N a été touché
				// On identifie la forme obtenue de l'ensemble des pixels touchés
				// puis on supprime ces pixels du vecteur V pour ne pas les 
				// compter plusieurs fois
				// 
				VectorClusterID.push_back(ShapeCluster2(VectorVar));
				V.erase(V.begin(),V.begin()+j-1);
				taille = V.size();
				// On réinitialise Couronne pour recommencer la même
				// logique à partir d'un nouveau pixel
				Couronne=0; 
			}
			if(j_intermediaire != j){
				Couronne+=1;
				j_intermediaire = j;
			}
 		}
 		//********************* COURONNE 4 ***************************
 		if(Couronne== 4){
 			if(j<taille && V.at(j)==N+4){
				VectorVar.push_back(V.at(j));
				j+=1;
			}
 			for(i=1;i<=3;i++){
 				if(j<taille && V.at(j)==N+i*npxl_row-3){
					VectorVar.push_back(V.at(j));
					j+=1;
				}
				if(j<taille && V.at(j)==N+i*npxl_row+3){
					VectorVar.push_back(V.at(j));
					j+=1;
				}
 			}
 			for(i=-4; i<=4; i++){ //on étudie les 7 pixels adjacents placés sur la colonne de droite
				if(j<taille && V.at(j)==N+i+4*npxl_row){
					VectorVar.push_back(V.at(j));
					j+=1;
				}
			}
			// MAXIMUM 40 PIXELS PAR ENSEMBLE
			VectorClusterID.push_back(ShapeCluster2(VectorVar));
			V.erase(V.begin(),V.begin()+j-1);//on supprime les pixels déjà étudiés
			taille = V.size();
			// On réinitialise Couronne pour recommencer la même
			// logique à partir d'un nouveau pixel
			Couronne=0;
 		}
 	}
	return VectorClusterID;
}





////////////////////////////////////////////////////////////////////
// MACRO
////////////////////////////////////////////////////////////////////

void Clusterisation2(const char* filename, const char* treename, int theta){

	char Angle[100];
 	sprintf(Angle, "Angle: %d deg", theta);

	//************************************************//

	TFile* f= new TFile(filename,"read");
	TTree* tree = (TTree*) f-> Get(treename);

////////////////////////////////////////////////////////////////////
//                 Graph 1 - Position pixel hit
////////////////////////////////////////////////////////////////////

	TCanvas* c1 = new TCanvas;
	c1->SetGrid();

	//*********** Histo 2D : Column vs Row ****************//

	tree->Draw("Ligne:Colonne>>GraphLC()", "","col");
	auto histoLC = (TH2D*)gPad->GetPrimitive("GraphLC");
	histoLC->SetTitle("#font[12]{Pixel hit}");
	histoLC->GetYaxis()->SetTitle("#font[12]{Row number }");
	histoLC->GetXaxis()->SetTitle("#font[12]{Column number }");
	histoLC->Draw("COLZ");
	gStyle->SetStatFont(12);
	gStyle->SetLegendFont(12);
	gStyle->SetOptStat("e");
	//gStyle->SetPalette(kBlueRedYellow);
	//gStyle->SetPalette(kCool);
	auto legend = new TLegend();
	gStyle->SetLegendFont(12);
   	legend->SetHeader("Legend of the graph:","C"); // option "C" allows to center the header
   	legend->AddEntry((TObject*)0, Angle, "");
   	legend->AddEntry((TObject*)0, " Number of particles by bunch:", " 1000");
   	legend->AddEntry((TObject*)0, " Number of bunch:", " 1000");
   	legend->Draw();
	gStyle->SetPalette(1);
   	c1->SaveAs("PixelHitPosition.pdf");

////////////////////////////////////////////////////////////////////
//                 Graph 2 - Cluster Shape IDs
////////////////////////////////////////////////////////////////////
   	
	TCanvas* c = new TCanvas;
	c->SetGrid();

	int N = tree->GetEntries();
	cout<<"****** N = " << N <<" *******"<<endl;
	int n, row, col, numEvent;
	tree->SetBranchAddress("EventID", &numEvent);
	tree->SetBranchAddress("Ligne", &row);
	tree->SetBranchAddress("Colonne", &col);

	//create a Tree file tree1.root
   	//create the file, the Tree and a few branches
   	TFile fCluster("tCluster.root","recreate");
   	TTree tCluster("tCluster","name");

//**********************************************************//

	Int_t NumShape;
	tCluster.Branch("NumShape",&NumShape,"NumShape/I");

	//Initialisation
	tree->GetEntry(0);
	int eID=numEvent;
	std::vector<int> V;
	std::vector<int> VectorID;

	//Division euclidienne pour récupérer le numéro des pixels à partir des coordonnées:
  	//N = npxl_row*C + (npxl_row - L) avec C le numéro de colonne et L de la ligne
	V.push_back(npxl_row * col + (npxl_row - row));

	//Loop
	for(int i=1; i<N; i++){
		tree->GetEntry(i);
		if(eID==numEvent){
			V.push_back(npxl_row * col + (npxl_row - row));
			if(i==N-1){
				TriVector(V);
				VectorID = DifferentiateShape(V);
				for(long unsigned int j=0;j<VectorID.size();j++){
					NumShape=VectorID.at(j);
					tCluster.Fill();
				}
				V.erase(V.begin(),V.begin()+V.size()-1);
			}
		}
		else{
			TriVector(V);
			VectorID = DifferentiateShape(V);
			for(long unsigned int j=0;j<VectorID.size();j++){
				NumShape=VectorID.at(j);
				tCluster.Fill();
			}
			V.erase(V.begin(),V.begin()+V.size()-1);
			eID=numEvent;
			//cout<<"V.size() = " << V.size() <<endl;
			//cout<<"V.at(0) = " << V.at(0) <<endl;
			V.push_back(npxl_row * col + (npxl_row - row));
			//cout<<"V.at(0) = " << V.at(0) <<endl;
			//cout<<"V.at(1) = " << V.at(1) <<endl;
			V.erase(V.begin());
		}
	}
	tCluster.Write();

	tCluster.Draw("NumShape>>Clusterisation()", "","");
	auto histoCluster = (TH1D*)gPad->GetPrimitive("Clusterisation");
	histoCluster->SetTitle("#font[12]{Cluster hit};#font[12]{Cluster ID }");
	histoCluster->GetYaxis()->SetTitle("#font[12]{N count }");
	histoCluster->SetLineColor(kCyan+2);
	histoCluster->SetFillStyle(3003);
    histoCluster->SetFillColor(kCyan+2);

	auto legend1 = new TLegend();
	gStyle->SetLegendFont(12);
   	legend1->SetHeader("Legend of the graph:","C"); // option "C" allows to center the header
   	legend1->AddEntry((TObject*)0, Angle, "");
   	legend1->AddEntry((TObject*)0, " Number of particles by bunch:", " 1000");
   	legend1->AddEntry((TObject*)0, " Number of bunch:", " 1000");
   	legend1->Draw();
	gStyle->SetStatFont(12);
	gStyle->SetLegendFont(12);
	gStyle->SetOptStat("nem");

	histoCluster->DrawCopy();

	c->SaveAs("Clusterisation.pdf");

//**********************************************************//

}

void Clusterisation(){
	const char* filename0 = "~/bin/CmosProject/build/ED_0deg_1000Evt_1000part.root";
	//const char* filename2 = "~/bin/CmosProject/build/ED_2deg_1000Evt_1000part.root";
	const char* filename5 = "~/bin/CmosProject/build/ED_5deg_1000Evt_1000part.root";
	const char* filename10 = "~/bin/CmosProject/build/ED_10deg_1000Evt_1000part.root";
	const char* filename15 = "~/bin/CmosProject/build/ED_15deg_1000Evt_1000part.root";
	const char* filename20 = "~/bin/CmosProject/build/ED_20deg_1000Evt_1000part.root";
	const char* filename30 = "~/bin/CmosProject/build/ED_30deg_1000Evt_1000part.root";
	const char* filename40 = "~/bin/CmosProject/build/ED_40deg_1000Evt_1000part.root";
	const char* filename50 = "~/bin/CmosProject/build/ED_50deg_1000Evt_1000part.root";

	//const char* filenameTEST = "~/bin/CmosProject/build/ED_15deg_10Evt_100part.root";
	//Clusterisation2(filenameTEST, "Chip0", 15);
	//
	Clusterisation2(filename5, "Chip0", 0);
	//Clusterisation2(filename5, "Chip0", 2);
	//Clusterisation2(filename5, "Chip0", 5);
	//Clusterisation2(filename10, "Chip0", 10);
	//Clusterisation2(filename15, "Chip0", 15);
	//Clusterisation2(filename20, "Chip0", 20);
	//Clusterisation2(filename30, "Chip0", 30);
	//Clusterisation2(filename40, "Chip0", 40);
	//Clusterisation2(filename50, "Chip0", 50);

}






/* ANCIEN CODE:
void Clusterisation(){

	TFile* f= new TFile(ED_TestBeam4,"read");
	TTree* tree = (TTree*) f-> Get(treename);

	TFile* f5= new TFile(ED_TestBeam5,"read");
	TTree* tree = (TTree*) f5-> Get(treename);

	TCanvas* c = new TCanvas;
	c->SetGrid();
	int N = tree5->GetEntries();
	int n, row, col, numEvent;
	tree5->SetBranchAddress("EventID", &numEvent);
	tree5->SetBranchAddress("Ligne", &row);
	tree5->SetBranchAddress("Colonne", &col);

   	TFile fCluster("tCluster.root","recreate");
   	TTree tCluster("tCluster","name");

	Int_t NumShape;
	tCluster.Branch("NumShape",&NumShape,"NumShape/I");
	tree5->GetEntry(0);
	int eID=numEvent;
	int* List= (int*)malloc(4*sizeof(int));
	List[0] = npxl_row * col + (npxl_row - row);
	int length=1;
	for(int i=1; i<=N; i++){
		tree5->GetEntry(i);
		if(eID==numEvent){
			List[length] = npxl_row * col + (npxl_row - row);
			length+=1;
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
	c->SaveAs("Clusterisation.pdf");
}
*/