#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TTree.h"
#include "TObjArray.h"
#include "TString.h"
#include "TLatex.h"
#include "TAttMarker.h"
#include "TStyle.h"
#include "TObjString.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "THStack.h"

using namespace std;
#include <iostream>
#include <vector>
#include <stdio.h>
#include <typeinfo>



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
const int n_pixels_tot = npxl_row * npxl_col;

void SortPixels(int *t, int length)
{
	/**
	 * @brief      { La fonction SortPixels() prend en argument une liste 
	 * (et sa taille) et permet de trier ses éléments dans l'ordre croissant }
	 *
	 * @param      t       { liste d'entier à trier}
	 * @param[in]  length  {dimension de la liste t}
	 */
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

int ShapeCluster(int* List, int length)
{
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
	SortPixels(List, length);
	switch(length){
		case 1:
			return 0;
		case 2:
			if(List[1]==List[0]+npxl_row)
				return 1;
			if(List[1]==List[0]+1)
				return 2;
		case 3:
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
		case 4:
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
	return 30+length;
}


int* DifferentiateShape(int* L, int NumHits, int* NumCluster) 
{ 
	/**
	 * @brief      { Differentiate Shape in all pixels it in one event }
	 *
	 * @param      L    { Liste de zéro et de un: si L[i]==1 cela signifie 
	 * que le pixel de numéro i a été touché, si L[i]==0 cela signifie que
	 * le pixel de numéro i n'a pas été touché}
	 *
	 * @return     { Liste des identifiants associés à la 
	 * forme du cluster selon la classification de l'article du Summer 
	 * Student Project de Natalia Emriskova - 2017 }
	 */

	int Couronne      = 0;
	int Test_fin      = 0;
	int i_ClustID     = 0;
	int i_Clust       = 0;
	int NumClusterMax = 41;

	// Liste dans laquelle on répertorie les identifiants (entiers) des clusters
	int* ListClusterID = (int*)malloc(n_pixels_tot*sizeof(int)); 

	// Liste dans laquelle on répertorie les numéros des pixels touchés formant un cluster
	// on ne considère pas de cluster supérieur à 41 pixels d'où la limite en taille
	int* ListCluster = (int*)malloc(NumClusterMax*sizeof(int)); 

	for(int i=0;i<n_pixels_tot;i++){

		// pixel touché
		if(L[i]==1){

			for( int i=0; i<NumClusterMax; i++) ListCluster[i] = n_pixels_tot+1;

			if(Couronne==0){

				if (NumHits==1){
					ListClusterID[i_ClustID]=0;
					return ListClusterID;
				}

	 			if (i+npxl_row+1<=n_pixels_tot && L[i+1]==0 && L[i+npxl_row-1]==1 && L[i+npxl_row]==0 && L[i+npxl_row+1]==1){
					// On ajoute l'identifiant correspondant à 1 pixel touché = 0
					if(i_ClustID<=n_pixels_tot){
						ListClusterID[i_ClustID]=0;
						i_ClustID+= 1;
						// On "supprime" le pixel déjà répertorié dans ListClusterID
						L[i]=0;
						NumHits -= 1;
					}
					else{
						cout<<"***** ERROR ******"<<endl;
						cout<<"i_ClustID = "<<i_ClustID<< " et n_pixels_tot = "<< n_pixels_tot <<endl;
					}
				}
	 			else if (i+npxl_row+1<=n_pixels_tot && L[i+1]==0 && L[i+npxl_row-1]==0 && L[i+npxl_row]==0 && L[i+npxl_row+1]==1){
					// On ajoute l'identifiant correspondant à 1 pixel touché = 0
					if(i_ClustID<=n_pixels_tot){
						ListClusterID[i_ClustID]=0;
						i_ClustID+= 1;
						// On "supprime" le pixel déjà répertorié dans ListClusterID
						L[i]=0;
						NumHits -= 1;
					}
					else{
						cout<<"***** ERROR ******"<<endl;
						cout<<"i_ClustID = "<<i_ClustID<< " et n_pixels_tot = "<< n_pixels_tot <<endl;
					}
				}
	 			else if (i+npxl_row+1<=n_pixels_tot && L[i+1]==0 && L[i+npxl_row-1]==1 && L[i+npxl_row]==0 && L[i+npxl_row+1]==0){
					// On ajoute l'identifiant correspondant à 1 pixel touché = 0
					if(i_ClustID<=n_pixels_tot){
						ListClusterID[i_ClustID]=0;
						i_ClustID+= 1;
						// On "supprime" le pixel déjà répertorié dans ListClusterID
						L[i]=0;
						NumHits -= 1;
					}
					else{
						cout<<"***** ERROR ******"<<endl;
						cout<<"i_ClustID = "<<i_ClustID<< " et n_pixels_tot = "<< n_pixels_tot <<endl;
					}
				}
				else if (i+npxl_row+1<=n_pixels_tot && L[i+1]==0 && L[i+npxl_row-1]==0 && L[i+npxl_row]==0 && L[i+npxl_row+1]==0){
					// On ajoute l'identifiant correspondant à 1 pixel touché = 0
					if(i_ClustID<=n_pixels_tot){
						ListClusterID[i_ClustID]=0;
						i_ClustID+= 1;
						// On "supprime" le pixel déjà répertorié dans ListClusterID
						L[i]=0;
						NumHits -= 1;
					} else {
						cout<<"***** ERROR ******"<<endl;
						cout<<"i_ClustID = "<<i_ClustID<< " et n_pixels_tot = "<< n_pixels_tot <<endl;
					}
				}
				else Couronne += 1;
			}

			//********************* COURONNE 1 ***************************
			if(Couronne==1){
				//
				// Le pixel numéro i est le pixel de départ autour duquel on va regarder 
				// successivement si les pixels voisins sont touchés
				// 
				// On ajoute le numéro du pixel dans le vecteur ListCluster
				ListCluster[0]=i;
				i_Clust=1;
				
				//on étudie les 3 pixels adjacents placés sur la colonne de droite
				for(int k=-1; k<=1; k++){ 

					if(i+npxl_row+k<=n_pixels_tot && L[i+k+npxl_row]==1)
					{
						// On ajoute le numéro du pixel dans le vecteur ListCluster
						ListCluster[i_Clust]=i+k+npxl_row;
						i_Clust+=1;
						// On "supprime" le pixel qui vient d'être répertorié dans ListCluster
						L[i+k+npxl_row]=0;
						NumHits -= 1;
					}
				}
								
				if(i+1<=n_pixels_tot && L[i+1]==1)
				{

					// On ajoute le numéro du pixel dans le vecteur ListCluster
					ListCluster[i_Clust]=i+1;
					i_Clust+=1;
					// On "supprime" le pixel qui vient d'être répertorié dans ListCluster
					L[i+1]=0;
					NumHits -= 1;
				}
				
				Couronne +=1 ;
				Test_fin = i_Clust;

			} //fin boucle if couronne 1

			//********************* COURONNE 2 ***************************
			if(Couronne==2){
				//
				if(i+2<=n_pixels_tot && L[i+2]==1) {
					ListCluster[i_Clust]=i+2;
					i_Clust+=1;
					// On supprime le pixel qui vient d'être répertorié dans ListCluster
					L[i+2]=0;
					NumHits -= 1;
				} else if(i+npxl_row-2<=n_pixels_tot && L[i+npxl_row-2]==1) {
					ListCluster[i_Clust]=i+npxl_row-2;
					i_Clust+=1;
					// On supprime le pixel qui vient d'être répertorié dans ListCluster
					L[i+npxl_row-2]=0;
					NumHits -= 1;
				} else if(i+npxl_row+2<=n_pixels_tot && L[i+npxl_row+2]==1) {
					ListCluster[i_Clust]=i+npxl_row+2;
					i_Clust+=1;
					// On supprime le pixel qui vient d'être répertorié dans ListCluster
					L[i+npxl_row+2]=0;
					NumHits -= 1;
				}

				//on étudie les 5 pixels adjacents placés sur la colonne de droite
				for(int k=-2; k<=2; k++){ 
					if(i+k+2*npxl_row<=n_pixels_tot && L[i+k+2*npxl_row]==1){
						ListCluster[i_Clust]=i+k+2*npxl_row;
						i_Clust+=1;
						// On supprime le pixel qui vient d'être répertorié dans ListCluster
						L[i+k+2*npxl_row]=0;
						NumHits -= 1;
					}
				}

				// TESTS POUR PASSAGE A LA COURONNE SUIVANTE
				if(Test_fin == i_Clust){ 
					//
					// Aucun pixel voisin de la deuxième couronne de N a été touché
					// On identifie la forme obtenue de l'ensemble des pixels touchés
					// puis on supprime ces pixels du vecteur V pour ne pas les 
					// compter plusieurs fois
					//
					if(i_ClustID<=n_pixels_tot){
						SortPixels(ListCluster,NumClusterMax);
						ListClusterID[i_ClustID]=ShapeCluster(ListCluster,i_Clust);
						i_ClustID+= 1;
					} else {
						cout<<"***** ERROR ******"<<endl;
						cout<<"i_ClustID = "<<i_ClustID<< " et n_pixels_tot = " << n_pixels_tot << endl;
					}
					// On réinitialise Couronne pour recommencer la même
					// logique à partir d'un nouveau pixel
					Couronne=0; 
				}
				if(Test_fin != i_Clust){
					Couronne+=1;
					Test_fin = i_Clust;
				}
			}//fin boucle if couronne 2


			//********************* COURONNE 3 ***************************
			if(Couronne==3){
				if(i+3<=n_pixels_tot && L[i+3]==1){
					ListCluster[i_Clust]=i+3;
					i_Clust+=1;
					L[i+3]=0;
					NumHits -= 1;
				}
				for(int k=1;k<=2;k++){
					if(i+k*npxl_row-3<=n_pixels_tot && L[i+k*npxl_row-3]==1){
						ListCluster[i_Clust]=i+k*npxl_row-3;
						i_Clust+=1;
						L[i+k*npxl_row-3]=0;
						NumHits -= 1;
					}
					if(i+k*npxl_row+3<=n_pixels_tot && L[i+k*npxl_row+3]==1){
						ListCluster[i_Clust]=i+k*npxl_row+3;
						i_Clust+=1;
						L[i+k*npxl_row+3]=0;
						NumHits -= 1;
					}
				}
				for(int k=-3; k<=3; k++){ //on étudie les 7 pixels adjacents placés sur la colonne de droite
					if(i+k+3*npxl_row<=n_pixels_tot && L[i+k+3*npxl_row]==1){
						ListCluster[i_Clust]=i+k+3*npxl_row;
						i_Clust+=1;
						L[i+k+3*npxl_row]=0;
						NumHits -= 1;
					}
				}
				// TESTS POUR PASSAGE A LA COURONNE SUIVANTE
				if(Test_fin == i_Clust){
					//
					// Aucun pixel voisin de la troisième couronne de N a été touché
					// On identifie la forme obtenue de l'ensemble des pixels touchés
					// puis on supprime ces pixels du vecteur V pour ne pas les 
					// compter plusieurs fois
					// 
					if(i_ClustID<=n_pixels_tot){
						SortPixels(ListCluster,NumClusterMax);
						ListClusterID[i_ClustID]=ShapeCluster(ListCluster,i_Clust);
						i_ClustID+= 1;
					}
					else{
						cout<<"***** ERROR ******"<<endl;
						cout<<"i_ClustID = "<<i_ClustID<< " et n_pixels_tot = " << n_pixels_tot << endl;
					}
					//
					// On réinitialise Couronne pour recommencer la même
					// logique à partir d'un nouveau pixel
					Couronne=0; 
				}
				if(Test_fin != i_Clust){
					Couronne+=1;
					Test_fin = i_Clust;
				}
			}//fin boucle if couronne 3

			//********************* COURONNE 4 ***************************
			if(Couronne==4){
				if(i+4<=n_pixels_tot && L[i+4]==1){
					ListCluster[i_Clust]=i+4;
					i_Clust+=1;
					L[i+4]=0;
					NumHits -= 1;
				}
				for(int k=1;k<=3;k++){
					if(i+k*npxl_row-3<=n_pixels_tot && L[i+k*npxl_row-3]==1){
						ListCluster[i_Clust]=i+k*npxl_row-3;
						i_Clust+=1;
						L[i+k*npxl_row-3]=0;
						NumHits -= 1;
					}
					if(i+k*npxl_row+3<=n_pixels_tot && L[i+k*npxl_row+3]==1){
						ListCluster[i_Clust]=i+k*npxl_row+3;
						i_Clust+=1;
						L[i+k*npxl_row+3]=0;
						NumHits -= 1;
					}
				}
				for(int k=-4; k<=4; k++){ //on étudie les 7 pixels adjacents placés sur la colonne de droite
					if(i+k+4*npxl_row<=n_pixels_tot && L[i+k+4*npxl_row]==1){
						ListCluster[i_Clust]=i+k+4*npxl_row;
						i_Clust+=1;
						L[i+k+4*npxl_row]=0;
						NumHits -= 1;
					}
				}
				// MAXIMUM 41 PIXELS PAR ENSEMBLE
			
				if(i_ClustID<=n_pixels_tot){
						SortPixels(ListCluster,NumClusterMax);
						ListClusterID[i_ClustID]=ShapeCluster(ListCluster,i_Clust);
						i_ClustID+= 1;
				}
				else{
					cout<<"***** ERROR ******"<<endl;
					cout<<"i_ClustID = "<<i_ClustID<< " et n_pixels_tot = " << n_pixels_tot << endl;
				}

				// On réinitialise Couronne pour recommencer la même
				// logique à partir d'un nouveau pixel
				Couronne=0;
			}//fin boucle if couronne 4
		}//fin boucle if
	}//fin boucle for

	for(int p = i_ClustID; p<n_pixels_tot; p++) ListClusterID[p]=-1;

	*NumCluster=i_ClustID;
	return ListClusterID;
}

void Clusterisation()
{
	int n_files = 2;
	auto filenames = new TObjArray(n_files);
	filenames->Add((TObject*) new TString("/Users/ba272880/bin/CmosProject/build/sim_0deg_1000Evt_10000part_radius30um.root"));
	filenames->Add((TObject*) new TString("/Users/ba272880/bin/CmosProject/build/sim_20deg_1000Evt_10000part_radius30um.root"));
	// filenames->Add((TObject*) new TString("~/bin/CmosProject/build/ED_20deg_100Evt_10000part_radius30um.root"));
	// filenames->Add((TObject*) new TString("~/bin/CmosProject/build/ED_30deg_100Evt_10000part_radius30um.root"));
	// filenames->Add((TObject*) new TString("~/bin/CmosProject/build/ED_40deg_100Evt_10000part_radius30um.root"));
	// filenames->Add((TObject*) new TString("~/bin/CmosProject/build/ED_50deg_100Evt_10000part_radius30um.root"));
	// filenames->Add((TObject*) new TString("~/bin/CmosProject/build/ED_60deg_100Evt_10000part_radius30um.root"));

	//************************************************//
		
	auto hs1 = new THStack("hs1","");
    TText T1; T1.SetTextFont(12); T1.SetTextAlign(21);

	for (int i = 0; i < filenames->GetEntriesFast(); ++i)
	{

		// the TH1 we gonna fill
		auto s_filename = (TString*) filenames->At(i);
		auto s_obj_array  = s_filename->Tokenize("/");
		auto s_obj_string = (TObjString*) s_obj_array->Last();
		auto s_hist_title = s_obj_string->String();
		s_hist_title.ReplaceAll(".root","");

		const char* hist_name = s_hist_title.Data();		
		const char* hist_title = s_hist_title.Data();

		auto histoCluster = new TH1F(hist_name,hist_title,29,0,29);
	    histoCluster->SetFillColor(40+i);

		//  get the TTree and set addresses
		const char* filename = ((TString*) filenames->At(i))->Data();
	   	TFile file(filename,"read");
		TTree* tree = (TTree*) file.Get("Chip0");

		int n_entries = tree->GetEntries();
	 	int n, row, col, numEvent;
		tree->SetBranchAddress("EventID", &numEvent);
		tree->SetBranchAddress("Ligne", &row);
		tree->SetBranchAddress("Colonne", &col);

		// some pointers
		int NumHits;
		int* ListClusterID;
		int NumCluster;
		int num_pix;

		// matrix of hitted pixels 
		int* pixels_hit = (int*)malloc(n_pixels_tot*sizeof(int));
		for (int i = 0; i < n_pixels_tot; ++i)pixels_hit[i]=0;

		//Initialisation
		tree->GetEntry(0);
		int eID = numEvent;
		NumHits = 0;

		//  loop over entries
		for(int i=0; i<n_entries; i++){
			
			tree->GetEntry(i);
			
			if(eID==numEvent){
				//Division euclidienne pour récupérer le numéro des pixels à partir des coordonnées:
			  	//num_pix = npxl_row*C + (npxl_row - L) avec C le numéro de colonne et L de la ligne
				num_pix = npxl_row * col + (npxl_row - row);
				pixels_hit[num_pix] = 1;
				NumHits+=1;
				
				// last entries
				if(i==n_entries-1){
					
					ListClusterID = DifferentiateShape(pixels_hit, NumHits, &NumCluster);
					for(int j=0;j<NumCluster;j++){
						int NumShape=ListClusterID[j];
						histoCluster->Fill(NumShape);
					}
				}

			// all pixels in same events are stored		
			} else {
				ListClusterID = DifferentiateShape(pixels_hit, NumHits, &NumCluster);
				for(int j=0;j<NumCluster;j++){
					int NumShape=ListClusterID[j];
					histoCluster->Fill(NumShape);
				}
				
				// reset pixel_hits and add new elements
				eID = numEvent;
				for (int i = 0; i < n_pixels_tot; ++i) pixels_hit[i]=0;
				num_pix = npxl_row * col + (npxl_row - row);
				pixels_hit[num_pix] = 1;
				NumHits=1;
			}
		}
		file.Close();
	    histoCluster->Scale(1./histoCluster->Integral(), "width");
    	hs1->Add(histoCluster);
	}
   	
	////////////////////////////////////////////////////////////////////
	//                 Histo stack
	////////////////////////////////////////////////////////////////////

	TCanvas* c1 = new TCanvas;
	c1->SetGrid();
    hs1->Draw("HIST, nostackb");
    hs1->GetXaxis()->SetNdivisions(29);
    hs1->GetXaxis()->SetTitle("#font[12]{Cluster Shape ID}");
    hs1->GetYaxis()->SetTitle("#font[12]{Likelihood}");

    T1.DrawTextNDC(.5,.95,"Likelihood of different cluster shapes for different angle of incidence");

    c1->Modified();
    gPad->BuildLegend(0.9,0.7,0.7,0.9);
	gPad->SetLogy(kTRUE);
	c1->SaveAs("plots/LikelihoodClusterShapes_nostackb_log.pdf");
}
