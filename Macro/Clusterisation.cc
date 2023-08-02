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
const int npxl_row = 50; //rows
const int npxl_col = 100; //columns







////////////////////////////////////////////////////////////////////
// Fonction tri d'une liste dans l'ordre croissant
////////////////////////////////////////////////////////////////////

/**
 * @brief      { La fonction SortPixels() prend en argument une liste 
 * (et sa taille) et permet de trier ses éléments dans l'ordre croissant }
 *
 * @param      t       { liste d'entier à trier}
 * @param[in]  length  {dimension de la liste t}
 */
void SortPixels(int *t, int length){
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

int ShapeCluster1(int* List, int length){
	SortPixels(List, length);
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

int ShapeCluster1bis(int* List, int length){
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

int ShapeCluster2(std::vector<int> V){
	int length = V.size();
	TriVector(V);
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

int ShapeCluster2bis(std::vector<int> V){
	int length = V.size();
	TriVector(V);
	switch(length){
		case 1:
			return 0;
		case 2:
			if(V[1]==V[0]+npxl_row)
				return 1;
			if(V[1]==V[0]+1)
				return 2;
		case 3:
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
		case 4:
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
// Differentiate Shape - version avec des VECTEURS
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
std::vector<int> DifferentiateShape_version1(std::vector<int> V){
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
 		switch (Couronne) {
	 		case 0:
 				if (taille==1){
 					VectorClusterID.push_back(0);
 					return VectorClusterID;
 				}

	 			if (V.at(1)==N+npxl_row-1 && 2<taille && V.at(2)==N+npxl_row+1){
 					// On ajoute l'identifiant correspondant à 1 pixel touché = 0
 					VectorClusterID.push_back(0);
 					// On supprime le pixel déjà répertorié dans VectorClusterID
 					V.erase(V.begin());
 					taille = V.size();
 				}
	 			if (V.at(1)==N+npxl_row-1 && 2<taille && V.at(2)!=N+npxl_row && V.at(2)!=N+npxl_row+1){
 					VectorClusterID.push_back(0);
 					V.erase(V.begin());
 					taille = V.size();
 				}
	 			if (V.at(1)==N+npxl_row+1){
 					VectorClusterID.push_back(0);
 					V.erase(V.begin());
 					taille = V.size();
 				}

	 			else{
 					Couronne+=1;
 				}

 		//********************* COURONNE 1 ***************************
	 		case 1:
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

 		//********************* COURONNE 2 ***************************
 			case 2:
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
					VectorClusterID.push_back(ShapeCluster2bis(VectorVar));
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
 		//********************* COURONNE 3 ***************************
 			case 3:
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
					VectorClusterID.push_back(ShapeCluster2bis(VectorVar));
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

 		//********************* COURONNE 4 ***************************
 			case 4:
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
				VectorClusterID.push_back(ShapeCluster2bis(VectorVar));
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
// Differentiate Shape - version avec des LISTES
////////////////////////////////////////////////////////////////////

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

int* DifferentiateShape(int* L, //list of 0 and 1
						int NumHits, // number of hits = number of 1 in L
						int* NumCluster) //number of Cluster identify at the end
	{ 

	//******* Declaration des variables **********
	
	int n_pixels_tot = npxl_row * npxl_col;
	int Couronne = 0;
	int Test_fin;
	int i_ClustID = 0;
	int i_Clust;
	int NumClusterMax=41;
	// Liste dans laquelle on répertorie les identifiants (entiers) des clusters
	int* ListClusterID = (int*)malloc(n_pixels_tot*sizeof(int)); 

	// Liste dans laquelle on répertorie les numéros des pixels touchés formant un cluster
	int* ListCluster = (int*)malloc(NumClusterMax*sizeof(int)); //on ne considère pas de cluster supérieur à 41 pixels d'où la limite en taille

	//*********************************************

	for(int i=0;i<n_pixels_tot;i++){
		if(L[i]==1){//numéro du pixel touché le plus petit de la liste L

			for(int i=0;i<NumClusterMax;i++) ListCluster[i] = n_pixels_tot+1;

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
					}
					else{
						cout<<"***** ERROR ******"<<endl;
						cout<<"i_ClustID = "<<i_ClustID<< " et n_pixels_tot = "<< n_pixels_tot <<endl;
					}
				}
				else
					Couronne+=1;
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
				//
				for(int k=-1; k<=1; k++){ //on étudie les 3 pixels adjacents placés sur la colonne de droite
					if(i+npxl_row+k>n_pixels_tot){
						cout<<"***** ERROR ******"<<endl;
						cout<<"i+npxl_row+k = "<<i+npxl_row+k<< " et n_pixels_tot = "<< n_pixels_tot <<endl;
						}
					if(i+npxl_row+k<=n_pixels_tot && L[i+k+npxl_row]==1){
						// On ajoute le numéro du pixel dans le vecteur ListCluster
						ListCluster[i_Clust]=i+k+npxl_row;
						i_Clust+=1;
						// On "supprime" le pixel qui vient d'être répertorié dans ListCluster
						L[i+k+npxl_row]=0;
						NumHits -= 1;
					}
				}
				if(i+1>n_pixels_tot){
						cout<<"***** ERROR ******"<<endl;
						cout<<"i+1 = "<<i+1<< " et n_pixels_tot = "<< n_pixels_tot <<endl;
						}
				if(i+1<=n_pixels_tot && L[i+1]==1){

					// On ajoute le numéro du pixel dans le vecteur ListCluster
					ListCluster[i_Clust]=i+1;
					i_Clust+=1;
					// On "supprime" le pixel qui vient d'être répertorié dans ListCluster
					L[i+1]=0;
					NumHits -= 1;
				}
				Couronne+=1;
				Test_fin = i_Clust;

			}//fin boucle if couronne 1
			//********************* COURONNE 2 ***************************
			if(Couronne==2){
				//
				if(i+2<=n_pixels_tot && L[i+2]==1){
					ListCluster[i_Clust]=i+2;
					i_Clust+=1;
					// On supprime le pixel qui vient d'être répertorié dans ListCluster
					L[i+2]=0;
					NumHits -= 1;
				}
				if(i+npxl_row-2<=n_pixels_tot && L[i+npxl_row-2]==1){
					ListCluster[i_Clust]=i+npxl_row-2;
					i_Clust+=1;
					// On supprime le pixel qui vient d'être répertorié dans ListCluster
					L[i+npxl_row-2]=0;
					NumHits -= 1;
				}
				if(i+npxl_row+2<=n_pixels_tot && L[i+npxl_row+2]==1){
					ListCluster[i_Clust]=i+npxl_row+2;
					i_Clust+=1;
					// On supprime le pixel qui vient d'être répertorié dans ListCluster
					L[i+npxl_row+2]=0;
					NumHits -= 1;
				}
				for(int k=-2; k<=2; k++){ //on étudie les 5 pixels adjacents placés sur la colonne de droite
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
						ListClusterID[i_ClustID]=ShapeCluster1bis(ListCluster,i_Clust);
						i_ClustID+= 1;
					}
					else{
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
						ListClusterID[i_ClustID]=ShapeCluster1bis(ListCluster,i_Clust);
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
						ListClusterID[i_ClustID]=ShapeCluster1bis(ListCluster,i_Clust);
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


////////////////////////////////////////////////////////////////////
// Function which convert vector in list of 0 and 1
////////////////////////////////////////////////////////////////////

int* Convert_1ereVersion(std::vector<int> V){
	int s=V.size();
	int N = npxl_row * npxl_col;
	int p=0;
	int* L = (int*)malloc(N*sizeof(int));
	for(int j=0;j<N;j++){
		if(p<s && j==V.at(p)){
			L[j]=1;
			p+=1;
		}
		else
			L[j]=0;
	}
	return L;
}

int* Convert(int* V, int s){
	int N = npxl_row * npxl_col;
	int p=0;
	int* L = (int*)malloc(N*sizeof(int));
	for(int j=0;j<N;j++){
		if(p<s && j==V[p]){
			L[j]=1;
			p+=1;
		}
		else
			L[j]=0;
	}
	return L;
}


////////////////////////////////////////////////////////////////////
// MACRO
////////////////////////////////////////////////////////////////////


void Clusterisation2(const char* filename, 
					 const char* treename,
					 const int theta, //angle of the chip
					 const int NumberOfEvents, 
					 const int NumberOfParticles){

	char Angle[100];
 	sprintf(Angle, "Angle: %d deg", theta);

 	char NumParticles[100];
 	sprintf(NumParticles, "Number of particles by bunch: %d", NumberOfParticles);

 	char NumBunch[100];
 	sprintf(NumBunch, "Number of bunch: %d", NumberOfEvents);

	//************************************************//

	TFile* f= new TFile(filename,"read");
	TTree* tree = (TTree*) f-> Get(treename);

////////////////////////////////////////////////////////////////////
//                 Graph 1 - Position pixel hit
////////////////////////////////////////////////////////////////////

	TCanvas* c1 = new TCanvas;
	c1->SetGrid();
	c1->Divide(2,1);
	c1->cd(1);

	//*********** Histo 2D : Column vs Row ****************

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
   	legend->AddEntry((TObject*)0, NumBunch, "");
   	legend->AddEntry((TObject*)0, NumParticles, "");
   	legend->Draw();
	gStyle->SetPalette(1);
   	c1->SaveAs("PixelLigneColonne.pdf");

////////////////////////////////////////////////////////////////////
//                 Graph 2 - Cluster Shape IDs
////////////////////////////////////////////////////////////////////
   	
	//TCanvas* c = new TCanvas;
	//c->SetGrid();
   	c1->cd(2);

	int n_entries = tree->GetEntries();
	cout<<"****** n_entries = " << n_entries <<" *******"<<endl;
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

	int n_pixels_tot = npxl_row*npxl_col;
	int NumHits;
	int* ListClusterID;
	int NumCluster;
	int num_pix;

/*
	int** pixels_hit = (int**)malloc(npxl_row*sizeof(int*));
	for (int r = 0; r < npxl_row; ++r){
		int* pixels_hit[r] = (int*)malloc(npxl_col*sizeof(int));
		for (int c = 0; c < npxl_col; ++c){
			pixels_hit[r][c]=0;
		}
	}
*/
	int* pixels_hit = (int*)malloc(n_pixels_tot*sizeof(int));
	for (int i = 0; i < n_pixels_tot; ++i)pixels_hit[i]=0;

	//Initialisation
	tree->GetEntry(0);
	int eID = numEvent;
	NumHits = 0;

	for(int i=0; i<n_entries; i++){
		tree->GetEntry(i);
		if(eID==numEvent){

			//pixels_hit[row][col] = 1;

			//Division euclidienne pour récupérer le numéro des pixels à partir des coordonnées:
		  	//num_pix = npxl_row*C + (npxl_row - L) avec C le numéro de colonne et L de la ligne
			num_pix = npxl_row * col + (npxl_row - row);
			pixels_hit[num_pix] = 1;

			NumHits+=1;
			
			// last entries
			if(i==n_entries-1){
				
				ListClusterID = DifferentiateShape(pixels_hit, NumHits, &NumCluster);
				for(int j=0;j<NumCluster;j++){
					NumShape=ListClusterID[j];
					tCluster.Fill();
				}
			}

		// all pixels in same events are stored		
		} else {
			ListClusterID = DifferentiateShape(pixels_hit, NumHits, &NumCluster);
			for(int j=0;j<NumCluster;j++){
				NumShape=ListClusterID[j];
				tCluster.Fill();
			}
			
			// reset pixel_hits and add new elements
			eID=numEvent;
			/*
			for (int r = 0; r < npxl_row; ++r){
				for (int c = 0; c < npxl_col; ++c){
					pixels_hit[r][c]=0;
				}
			}			
			pixels_hit[row][col] = 1;
			*/
			for (int i = 0; i < n_pixels_tot; ++i) pixels_hit[i]=0;
			num_pix = npxl_row * col + (npxl_row - row);
			pixels_hit[num_pix] = 1;

			NumHits=1;
		}
	}
	tCluster.Write();

	tCluster.Draw("NumShape>>Clusterisation(28, 0, 29)", "","");
	auto histoCluster = (TH1D*)gPad->GetPrimitive("Clusterisation");
	histoCluster->SetTitle("#font[12]{Cluster hit};#font[12]{Cluster ID }");
	histoCluster->GetYaxis()->SetTitle("#font[12]{N count }");
	histoCluster->SetLineColor(kCyan+2);
	histoCluster->SetFillStyle(3003);
    histoCluster->SetFillColor(kCyan+2);

	auto legend1 = new TLegend(0.9,0.7,0.4,0.9);
   	legend1->SetHeader("Legend of the graph:","C"); // option "C" allows to center the header
   	legend1->AddEntry((TObject*)0, Angle, "");
   	legend1->AddEntry((TObject*)0, NumBunch, " ");
   	legend1->AddEntry((TObject*)0, NumParticles, " ");
	gStyle->SetStatFont(12);
	gStyle->SetLegendFont(12);
	gStyle->SetOptStat("e");
	//gStyle->SetLegendTextSize(0.03);

	histoCluster->DrawCopy();
	legend1->Draw();
	c1->SaveAs("Clusterisation.pdf");

//**********************************************************//

}









/*

void PixelAdvanced(char* filename){


   	TFile* f_init= new TFile(filename,"read");
	TTree* InitTree = (TTree*) f_init-> Get("Chip0");

	int n_entries = InitTree->GetEntries();

 	int n, row, col, numEvent;
	InitTree->SetBranchAddress("EventID", &numEvent);
	InitTree->SetBranchAddress("Ligne", &row);
	InitTree->SetBranchAddress("Colonne", &col);
	InitTree->SetBranchAddress("Colonne", &col);
	InitTree->SetBranchAddress("Edep", &EnergyDeposit);
	InitTree->SetBranchAddress("TrackID", &traID);
	InitTree->SetBranchAddress("NumParticle", &numPart);

	//create a Tree file tree1.root
   	//create the file, the Tree and a few branches
   	TFile f_final("PixelAdvanced.root","recreate");
   	TTree FinalTree("FinalTree","name");

	Int_t Ligne, Colonne, EventID, Edep, Enoise, Eleak, Eshared, EventID, TrackID, NumParticle;
	
	FinalTree.Branch("Ligne",&Ligne,"Ligne/I");
	FinalTree.Branch("Colonne",&Colonne,"Colonne/I");
	FinalTree.Branch("EventID",&EventID,"EventID/I");
	FinalTree.Branch("Edep",&Edep,"Edep/I");
	FinalTree.Branch("Enoise",&Enoise,"Enoise/I");
	FinalTree.Branch("Eleak",&Eleak,"Eleak/I");
	FinalTree.Branch("Eshared",&Eshared,"Eshared/I");
	FinalTree.Branch("EventID",&EventID,"EventID/I");
	FinalTree.Branch("TrackID",&TrackID,"TrackID/I");
	FinalTree.Branch("NumParticle",&NumParticle,"NumParticle/I");

	int n_pixels_tot = npxl_row*npxl_col;

	//Initialisation
	TreeInit->GetEntry(0);

	for(int i=0; i<n_entries; i++){
		TreeInit->GetEntry(i);

		if(row>0 && row<npxl_row-1 && col>0 && col<npxl_col-1 ){

		}

		if(row==0){
			Ligne=row+1;
			Colonne=col+1;
			EventID=numEvent;
			Eshared==
			Enoise=TRandom::Gauss(0,0.01); 
			//TRandom::Gaus(Double_t mean=0, Double_t sigma=1)
		}

		if(col==0){
			Enoise=TRandom::Gauss(0,0.01); 
		}

		if(row==npxl_row-1){
			Enoise=TRandom::Gauss(0,0.01); 
		}

		if(col==npxl_col-1){
			Enoise=TRandom::Gauss(0,0.01); 
		}

	}


}
*/




















void Clusterisation(){

/*
	const char* filename0 = "~/bin/CmosProject/build/ED_0deg_1000Evt_1000part.root";
	const char* filename2 = "~/bin/CmosProject/build/ED_2deg_1000Evt_1000part.root";
	const char* filename5 = "~/bin/CmosProject/build/ED_5deg_1000Evt_1000part.root";
	const char* filename10 = "~/bin/CmosProject/build/ED_10deg_1000Evt_1000part.root";
	const char* filename15 = "~/bin/CmosProject/build/ED_15deg_1000Evt_1000part.root";
	const char* filename20 = "~/bin/CmosProject/build/ED_20deg_1000Evt_1000part.root";
	const char* filename30 = "~/bin/CmosProject/build/ED_30deg_1000Evt_1000part.root";
	const char* filename40 = "~/bin/CmosProject/build/ED_40deg_1000Evt_1000part.root";
	const char* filename50 = "~/bin/CmosProject/build/ED_50deg_1000Evt_1000part.root";
	const char* filename60 = "~/bin/CmosProject/build/ED_60deg_1000Evt_1000part.root";
*/
	const char* filename0 = "~/bin/CmosProject/build/ED_0deg_100Evt_10000part_radius30um.root";
	const char* filename10 = "~/bin/CmosProject/build/ED_10deg_100Evt_10000part_radius30um.root";
	const char* filename20 = "~/bin/CmosProject/build/ED_20deg_100Evt_10000part_radius30um.root";
	const char* filename30 = "~/bin/CmosProject/build/ED_30deg_100Evt_10000part_radius30um.root";
	const char* filename40 = "~/bin/CmosProject/build/ED_40deg_100Evt_10000part_radius30um.root";
	const char* filename50 = "~/bin/CmosProject/build/ED_50deg_100Evt_10000part_radius30um.root";
	const char* filename60 = "~/bin/CmosProject/build/ED_60deg_100Evt_10000part_radius30um.root";

	//************************************************//

	TCanvas* c = new TCanvas;
	c->SetGrid();

////////////////////////////////////////////////////////////////////
//                 Histo 0 deg
////////////////////////////////////////////////////////////////////
   	
   	TFile* f0= new TFile(filename0,"read");
	TTree* tree0 = (TTree*) f0-> Get("Chip0");

	int n_entries = tree0->GetEntries();
 	int n, row, col, numEvent;
	tree0->SetBranchAddress("EventID", &numEvent);
	tree0->SetBranchAddress("Ligne", &row);
	tree0->SetBranchAddress("Colonne", &col);

	//create a Tree file tree1.root
   	//create the file, the Tree and a few branches
   	TFile fCluster0("tCluster0.root","recreate");
   	TTree tCluster0("tCluster0","name40");

	Int_t NumShape;
	tCluster0.Branch("NumShape",&NumShape,"NumShape/I");

	int n_pixels_tot = npxl_row*npxl_col;
	int NumHits;
	int* ListClusterID;
	int NumCluster;
	int num_pix;

	int* pixels_hit = (int*)malloc(n_pixels_tot*sizeof(int));
	for (int i = 0; i < n_pixels_tot; ++i)pixels_hit[i]=0;

	//Initialisation
	tree0->GetEntry(0);
	int eID = numEvent;
	NumHits = 0;

	for(int i=0; i<n_entries; i++){
		tree0->GetEntry(i);
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
					NumShape=ListClusterID[j];
					tCluster0.Fill();
				}
			}

		// all pixels in same events are stored		
		} else {
			ListClusterID = DifferentiateShape(pixels_hit, NumHits, &NumCluster);
			for(int j=0;j<NumCluster;j++){
				NumShape=ListClusterID[j];
				tCluster0.Fill();
			}
			
			// reset pixel_hits and add new elements
			eID=numEvent;
			for (int i = 0; i < n_pixels_tot; ++i) pixels_hit[i]=0;
			num_pix = npxl_row * col + (npxl_row - row);
			pixels_hit[num_pix] = 1;

			NumHits=1;
		}
	}
	tCluster0.Write();

	tCluster0.Draw("NumShape>>Clusterisation40(29, 0, 29)", "","");
	auto histoCluster0 = (TH1D*)gPad->GetPrimitive("Clusterisation40");
	histoCluster0->SetLineColor(kOrange);
	//histoCluster0->SetFillStyle(3004);
    histoCluster0->SetFillColor(kOrange);
    histoCluster0->Scale(1./histoCluster0->Integral(), "width");

////////////////////////////////////////////////////////////////////
//                 Histo 10deg
////////////////////////////////////////////////////////////////////


	TFile* f10= new TFile(filename10,"read");
	TTree* tree10 = (TTree*) f10-> Get("Chip0");

	tree10->SetBranchAddress("EventID", &numEvent);
	tree10->SetBranchAddress("Ligne", &row);
	tree10->SetBranchAddress("Colonne", &col);

	//create a Tree file tree1.root
   	//create the file, the Tree and a few branches
   	TFile fCluster10("tCluster10.root","recreate");
   	TTree tCluster10("tCluster10","name10");

	tCluster10.Branch("NumShape",&NumShape,"NumShape/I");

	for (int i = 0; i < n_pixels_tot; ++i)pixels_hit[i]=0;

	//Initialisation
	tree10->GetEntry(0);
	NumHits = 0;

	for(int i=0; i<n_entries; i++){
		tree10->GetEntry(i);
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
					NumShape=ListClusterID[j];
					tCluster10.Fill();
				}
			}

		// all pixels in same events are stored		
		} else {
			ListClusterID = DifferentiateShape(pixels_hit, NumHits, &NumCluster);
			for(int j=0;j<NumCluster;j++){
				NumShape=ListClusterID[j];
				tCluster10.Fill();
			}
			
			// reset pixel_hits and add new elements
			eID=numEvent;
			for (int i = 0; i < n_pixels_tot; ++i) pixels_hit[i]=0;
			num_pix = npxl_row * col + (npxl_row - row);
			pixels_hit[num_pix] = 1;

			NumHits=1;
		}
	}
	tCluster10.Write();

	tCluster10.Draw("NumShape>>Clusterisation10(29, 0, 29)", "","");
	auto histoCluster10 = (TH1D*)gPad->GetPrimitive("Clusterisation10");
	histoCluster10->SetLineColor(kOrange+2);
	//histoCluster10->SetFillStyle(3004);
    histoCluster10->SetFillColor(kOrange+2);
    histoCluster10->Scale(1./histoCluster10->Integral(), "width");


////////////////////////////////////////////////////////////////////
//                 Histo 20deg
////////////////////////////////////////////////////////////////////


	TFile* f20= new TFile(filename20,"read");
	TTree* tree20 = (TTree*) f20-> Get("Chip0");

	tree20->SetBranchAddress("EventID", &numEvent);
	tree20->SetBranchAddress("Ligne", &row);
	tree20->SetBranchAddress("Colonne", &col);

	//create a Tree file tree1.root
   	//create the file, the Tree and a few branches
   	TFile fCluster20("tCluster20.root","recreate");
   	TTree tCluster20("tCluster20","name20");

	tCluster20.Branch("NumShape",&NumShape,"NumShape/I");

	for (int i = 0; i < n_pixels_tot; ++i)pixels_hit[i]=0;

	//Initialisation
	tree20->GetEntry(0);
	NumHits = 0;

	for(int i=0; i<n_entries; i++){
		tree20->GetEntry(i);
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
					NumShape=ListClusterID[j];
					tCluster20.Fill();
				}
			}

		// all pixels in same events are stored		
		} else {
			ListClusterID = DifferentiateShape(pixels_hit, NumHits, &NumCluster);
			for(int j=0;j<NumCluster;j++){
				NumShape=ListClusterID[j];
				tCluster20.Fill();
			}
			
			// reset pixel_hits and add new elements
			eID=numEvent;
			for (int i = 0; i < n_pixels_tot; ++i) pixels_hit[i]=0;
			num_pix = npxl_row * col + (npxl_row - row);
			pixels_hit[num_pix] = 1;

			NumHits=1;
		}
	}
	tCluster20.Write();

	tCluster20.Draw("NumShape>>Clusterisation20(29, 0, 29)", "","");
	auto histoCluster20 = (TH1D*)gPad->GetPrimitive("Clusterisation20");
	histoCluster20->SetLineColor(kRed);
	//histoCluster20->SetFillStyle(3004);
    histoCluster20->SetFillColor(kRed);
    histoCluster20->Scale(1./histoCluster20->Integral(), "width");


////////////////////////////////////////////////////////////////////
//                 Histo 30deg
////////////////////////////////////////////////////////////////////


	TFile* f30= new TFile(filename30,"read");
	TTree* tree30 = (TTree*) f30-> Get("Chip0");

	tree30->SetBranchAddress("EventID", &numEvent);
	tree30->SetBranchAddress("Ligne", &row);
	tree30->SetBranchAddress("Colonne", &col);

	//create a Tree file tree1.root
   	//create the file, the Tree and a few branches
   	TFile fCluster30("tCluster30.root","recreate");
   	TTree tCluster30("tCluster30","name30");

	tCluster30.Branch("NumShape",&NumShape,"NumShape/I");

	for (int i = 0; i < n_pixels_tot; ++i)pixels_hit[i]=0;

	//Initialisation
	tree30->GetEntry(0);
	NumHits = 0;

	for(int i=0; i<n_entries; i++){
		tree30->GetEntry(i);
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
					NumShape=ListClusterID[j];
					tCluster30.Fill();
				}
			}

		// all pixels in same events are stored		
		} else {
			ListClusterID = DifferentiateShape(pixels_hit, NumHits, &NumCluster);
			for(int j=0;j<NumCluster;j++){
				NumShape=ListClusterID[j];
				tCluster30.Fill();
			}
			
			// reset pixel_hits and add new elements
			eID=numEvent;
			for (int i = 0; i < n_pixels_tot; ++i) pixels_hit[i]=0;
			num_pix = npxl_row * col + (npxl_row - row);
			pixels_hit[num_pix] = 1;

			NumHits=1;
		}
	}
	tCluster30.Write();

	tCluster30.Draw("NumShape>>Clusterisation30(29, 0, 29)", "","");
	auto histoCluster30 = (TH1D*)gPad->GetPrimitive("Clusterisation30");
	histoCluster30->SetLineColor(kViolet);
	//histoCluster30->SetFillStyle(3004);
    histoCluster30->SetFillColor(kViolet);
    histoCluster30->Scale(1./histoCluster30->Integral(), "width");


////////////////////////////////////////////////////////////////////
//                 Histo 40deg
////////////////////////////////////////////////////////////////////


	TFile* f40= new TFile(filename40,"read");
	TTree* tree40 = (TTree*) f40-> Get("Chip0");

	tree40->SetBranchAddress("EventID", &numEvent);
	tree40->SetBranchAddress("Ligne", &row);
	tree40->SetBranchAddress("Colonne", &col);

	//create a Tree file tree1.root
   	//create the file, the Tree and a few branches
   	TFile fCluster40("tCluster40.root","recreate");
   	TTree tCluster40("tCluster40","name40");

	tCluster40.Branch("NumShape",&NumShape,"NumShape/I");

	for (int i = 0; i < n_pixels_tot; ++i)pixels_hit[i]=0;

	//Initialisation
	tree40->GetEntry(0);
	NumHits = 0;

	for(int i=0; i<n_entries; i++){
		tree40->GetEntry(i);
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
					NumShape=ListClusterID[j];
					tCluster40.Fill();
				}
			}

		// all pixels in same events are stored		
		} else {
			ListClusterID = DifferentiateShape(pixels_hit, NumHits, &NumCluster);
			for(int j=0;j<NumCluster;j++){
				NumShape=ListClusterID[j];
				tCluster40.Fill();
			}
			
			// reset pixel_hits and add new elements
			eID=numEvent;
			for (int i = 0; i < n_pixels_tot; ++i) pixels_hit[i]=0;
			num_pix = npxl_row * col + (npxl_row - row);
			pixels_hit[num_pix] = 1;

			NumHits=1;
		}
	}
	tCluster40.Write();

	tCluster40.Draw("NumShape>>Clusterisation40(29, 0, 29)", "","");
	auto histoCluster40 = (TH1D*)gPad->GetPrimitive("Clusterisation40");
	histoCluster40->SetLineColor(kMagenta+2);
	//histoCluster40->SetFillStyle(3004);
    histoCluster40->SetFillColor(kMagenta+2);
    histoCluster40->Scale(1./histoCluster40->Integral(), "width");


////////////////////////////////////////////////////////////////////
//                 Histo 50deg
////////////////////////////////////////////////////////////////////


	TFile* f50= new TFile(filename50,"read");
	TTree* tree50 = (TTree*) f50-> Get("Chip0");

	tree50->SetBranchAddress("EventID", &numEvent);
	tree50->SetBranchAddress("Ligne", &row);
	tree50->SetBranchAddress("Colonne", &col);

	//create a Tree file tree1.root
   	//create the file, the Tree and a few branches
   	TFile fCluster50("tCluster50.root","recreate");
   	TTree tCluster50("tCluster50","name50");

	tCluster50.Branch("NumShape",&NumShape,"NumShape/I");

	for (int i = 0; i < n_pixels_tot; ++i)pixels_hit[i]=0;

	//Initialisation
	tree50->GetEntry(0);
	NumHits = 0;

	for(int i=0; i<n_entries; i++){
		tree50->GetEntry(i);
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
					NumShape=ListClusterID[j];
					tCluster50.Fill();
				}
			}

		// all pixels in same events are stored		
		} else {
			ListClusterID = DifferentiateShape(pixels_hit, NumHits, &NumCluster);
			for(int j=0;j<NumCluster;j++){
				NumShape=ListClusterID[j];
				tCluster50.Fill();
			}
			
			// reset pixel_hits and add new elements
			eID=numEvent;
			for (int i = 0; i < n_pixels_tot; ++i) pixels_hit[i]=0;
			num_pix = npxl_row * col + (npxl_row - row);
			pixels_hit[num_pix] = 1;

			NumHits=1;
		}
	}
	tCluster50.Write();

	tCluster50.Draw("NumShape>>Clusterisation50(29, 0, 29)", "","");
	auto histoCluster50 = (TH1D*)gPad->GetPrimitive("Clusterisation50");
	histoCluster50->SetLineColor(kBlue);
	//histoCluster50->SetFillStyle(3004);
    histoCluster50->SetFillColor(kBlue);
    histoCluster50->Scale(1./histoCluster50->Integral(), "width");

////////////////////////////////////////////////////////////////////
//                 Histo 60deg
////////////////////////////////////////////////////////////////////


	TFile* f60= new TFile(filename60,"read");
	TTree* tree60 = (TTree*) f60-> Get("Chip0");

	tree60->SetBranchAddress("EventID", &numEvent);
	tree60->SetBranchAddress("Ligne", &row);
	tree60->SetBranchAddress("Colonne", &col);

	//create a Tree file tree1.root
   	//create the file, the Tree and a few branches
   	TFile fCluster60("tCluster60.root","recreate");
   	TTree tCluster60("tCluster60","name60");

	tCluster60.Branch("NumShape",&NumShape,"NumShape/I");

	for (int i = 0; i < n_pixels_tot; ++i)pixels_hit[i]=0;

	//Initialisation
	tree60->GetEntry(0);
	NumHits = 0;

	for(int i=0; i<n_entries; i++){
		tree60->GetEntry(i);
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
					NumShape=ListClusterID[j];
					tCluster60.Fill();
				}
			}

		// all pixels in same events are stored		
		} else {
			ListClusterID = DifferentiateShape(pixels_hit, NumHits, &NumCluster);
			for(int j=0;j<NumCluster;j++){
				NumShape=ListClusterID[j];
				tCluster60.Fill();
			}
			
			// reset pixel_hits and add new elements
			eID=numEvent;
			for (int i = 0; i < n_pixels_tot; ++i) pixels_hit[i]=0;
			num_pix = npxl_row * col + (npxl_row - row);
			pixels_hit[num_pix] = 1;

			NumHits=1;
		}
	}
	tCluster60.Write();

	tCluster60.Draw("NumShape>>Clusterisation60(29, 0, 29)", "","");
	auto histoCluster60 = (TH1D*)gPad->GetPrimitive("Clusterisation60");
	histoCluster60->SetLineColor(kGreen+2);
	//histoCluster60->SetFillStyle(3004);
    histoCluster60->SetFillColor(kGreen+2);
    histoCluster60->Scale(1./histoCluster60->Integral(), "width");

////////////////////////////////////////////////////////////////////
//                 Histo stack
////////////////////////////////////////////////////////////////////

/*
	c->cd(1);
	c->SetWindowSize(5000,5000);
    auto hs = new THStack("hs","");
    TText T; T.SetTextFont(12); T.SetTextAlign(21);
    hs->Add(histoCluster0);
    hs->Add(histoCluster10);
    hs->Add(histoCluster20);
    hs->Add(histoCluster30);
    hs->Add(histoCluster40);
    hs->Add(histoCluster50);
    hs->Add(histoCluster60);
    hs->Draw("HIST,nostack");

    hs->GetXaxis()->SetTitle("#font[12]{Cluster Shape ID}");
    hs->GetYaxis()->SetTitle("#font[12]{Likelihood}");

    T.DrawTextNDC(.5,.95,"Likelihood of different cluster shapes for different angle of incidence");

    auto legend1 = new TLegend(0.9,0.7,0.7,0.9);
   	legend1->SetHeader("Legend of the graph:","C"); // option "C" allows to center the header
   	legend1->AddEntry(histoCluster0, "Angle : 0 deg", "f");
   	legend1->AddEntry(histoCluster10, "Angle : 10 deg", "f");
   	legend1->AddEntry(histoCluster20, "Angle : 20 deg", "f");
   	legend1->AddEntry(histoCluster30, "Angle : 30 deg", "f");
   	legend1->AddEntry(histoCluster40, "Angle : 40 deg", "f");
   	legend1->AddEntry(histoCluster50, "Angle : 50 deg", "f");
   	legend1->AddEntry(histoCluster60, "Angle : 60 deg", "f");
	gStyle->SetStatFont(12);
	gStyle->SetLegendFont(12);
	gStyle->SetOptStat("e");

	legend1->Draw();

	//c->SaveAs("LikelihoodClusterShapes_nostack.pdf");

	gPad->SetLogy(kTRUE);
	c->SaveAs("LikelihoodClusterShapes_nostack_log.pdf");
*/
	TCanvas* c1 = new TCanvas;
	c1->SetGrid();

	c1->SetWindowSize(5000,5000);
	auto hs1 = new THStack("hs1","");
    TText T1; T1.SetTextFont(12); T1.SetTextAlign(21);
    hs1->Add(histoCluster0);
    hs1->Add(histoCluster10);
    hs1->Add(histoCluster20);
    hs1->Add(histoCluster30);
    hs1->Add(histoCluster40);
    hs1->Add(histoCluster50);
    hs1->Add(histoCluster60);
    hs1->Draw("HIST,nostackb");

    hs1->GetXaxis()->SetNdivisions(29);
    hs1->GetXaxis()->SetTitle("#font[12]{Cluster Shape ID}");
    hs1->GetYaxis()->SetTitle("#font[12]{Likelihood}");

    T1.DrawTextNDC(.5,.95,"Likelihood of different cluster shapes for different angle of incidence");

    auto legend2 = new TLegend(0.9,0.7,0.7,0.9);
   	legend2->SetHeader("Legend of the graph:","C"); // option "C" allows to center the header
   	legend2->AddEntry(histoCluster0, "Angle : 0 deg", "f");
   	legend2->AddEntry(histoCluster10, "Angle : 10 deg", "f");
   	legend2->AddEntry(histoCluster20, "Angle : 20 deg", "f");
   	legend2->AddEntry(histoCluster30, "Angle : 30 deg", "f");
   	legend2->AddEntry(histoCluster40, "Angle : 40 deg", "f");
   	legend2->AddEntry(histoCluster50, "Angle : 50 deg", "f");
   	legend2->AddEntry(histoCluster60, "Angle : 60 deg", "f");
	gStyle->SetStatFont(12);
	gStyle->SetLegendFont(12);
	gStyle->SetOptStat("e");

	legend2->Draw();

	//c1->SaveAs("LikelihoodClusterShapes_nostackb.pdf");

	gPad->SetLogy(kTRUE);
	c1->SaveAs("LikelihoodClusterShapes_nostackb_log.pdf");
}











void Clusterisationbis(){
	const char* filename0 = "~/bin/CmosProject/build/ED_0deg_1000Evt_1000part.root";
	const char* filename2 = "~/bin/CmosProject/build/ED_2deg_1000Evt_1000part.root";
	const char* filename5 = "~/bin/CmosProject/build/ED_5deg_1000Evt_1000part.root";
	const char* filename10 = "~/bin/CmosProject/build/ED_10deg_1000Evt_1000part.root";
	const char* filename15 = "~/bin/CmosProject/build/ED_15deg_1000Evt_1000part.root";
	const char* filename20 = "~/bin/CmosProject/build/ED_20deg_1000Evt_1000part.root";
	const char* filename30 = "~/bin/CmosProject/build/ED_30deg_1000Evt_1000part.root";
	const char* filename40 = "~/bin/CmosProject/build/ED_40deg_1000Evt_1000part.root";
	const char* filename50 = "~/bin/CmosProject/build/ED_50deg_1000Evt_1000part.root";

	//const char* filenameTEST = "~/bin/CmosProject/build/ED_15deg_10Evt_100part.root";
	//Clusterisation2(filenameTEST, "Chip0", 15, 10, 100);

/*
	const char* filenameTEST1 = "~/bin/CmosProject/build/ED_0deg_10Evt_10part.root";
	Clusterisation2(filenameTEST1, "Chip0", 0, 10, 10);
	const char* filenameTEST = "~/bin/CmosProject/build/ED_5deg_10Evt_10part.root";
	Clusterisation2(filenameTEST, "Chip0", 5, 10, 10);
	const char* filenameTEST2 = "~/bin/CmosProject/build/ED_10deg_10Evt_10part.root";
	Clusterisation2(filenameTEST2, "Chip0", 10, 10, 10);


	const char* filenameTEST3 = "~/bin/CmosProject/build/ED_0deg_3Evt_1000part.root";
	Clusterisation2(filenameTEST3, "Chip0", 0, 3, 1000);

	const char* filenameTEST4 = "~/bin/CmosProject/build/ED_10deg_3Evt_1000part.root";
	Clusterisation2(filenameTEST4, "Chip0", 10, 3, 1000);

	const char* filenameTEST5 = "~/bin/CmosProject/build/ED_50deg_3Evt_1000part.root";
	Clusterisation2(filenameTEST5, "Chip0", 50, 3, 1000);
	const char* filenameTEST6 = "~/bin/CmosProject/build/ED_10deg_1Evt_10000part.root";
	Clusterisation2(filenameTEST6, "Chip0", 10, 1, 10000);

	Clusterisation2(filename5, "Chip0", 0, 1000, 1000);
	Clusterisation2(filename5, "Chip0", 2, 1000, 1000);
	Clusterisation2(filename5, "Chip0", 5, 1000, 1000);
	Clusterisation2(filename10, "Chip0", 10, 1000, 1000);
	Clusterisation2(filename15, "Chip0", 15, 1000, 1000);
	Clusterisation2(filename20, "Chip0", 20, 1000, 1000);
	Clusterisation2(filename30, "Chip0", 30, 1000, 1000);
	Clusterisation2(filename40, "Chip0", 40, 1000, 1000);
*/
	Clusterisation2(filename50, "Chip0", 50, 1000, 1000);
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
	histoCluster->SetFillStyle(300);
    histoCluster->SetFillColor(kCyan+2);
	histoCluster->DrawCopy();
	gStyle->SetStatFont(12);
	gStyle->SetOptStat("nem");
	c->SaveAs("Clusterisation.pdf");
}
*/