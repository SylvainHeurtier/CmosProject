#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TTree.h"
#include "TLatex.h"
#include "TAttMarker.h"
#include "TStyle.h"


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

void EdepInPixel(){

	//************************************************//
	const char* filename = "~/bin/CmosProject/build/ED_0deg_1000Evt_10000part_radius600um.root";
	const char* treename="Chip0";


	TFile* f1= new TFile(filename,"read");
	TTree* tree1 = (TTree*) f1-> Get(treename);

////////////////////////////////////////////////////////////////////
//                         Graph 1
////////////////////////////////////////////////////////////////////

	TCanvas* c = new TCanvas;
	c->SetGrid();
	
	//*********** Histo 3D ****************//

	tree1->Draw("Edep:Colonne:Ligne>>GraphECL()", "","box");
	auto histoLCE = (TH3D*)gPad->GetPrimitive("GraphECL");
	histoLCE->SetTitle("#font[12]{Number pixel}");

	histoLCE->GetXaxis()->SetTitle("#font[12]{Position X}");
	histoLCE->GetYaxis()->SetTitle("#font[12]{Position Y}");
	histoLCE->GetZaxis()->SetTitle("#font[12]{Energy (MeV)}");

	histoLCE->Draw("BOX2 Z");
	gStyle->SetStatFont(12);

   	c->SaveAs("NumberPixel.pdf");

////////////////////////////////////////////////////////////////////
//                         Graph 2
////////////////////////////////////////////////////////////////////

	TCanvas* c1 = new TCanvas;
	c1->SetGrid();

	//*********** Histo 2D  ****************//

	tree1->Draw("Ligne:Colonne>>GraphLC(61,-5,55,111,-5,105)", "","col");
	auto histoLC = (TH2D*)gPad->GetPrimitive("GraphLC");
	histoLC->SetTitle("#font[12]{Pixel hit}");
	histoLC->GetXaxis()->SetTitle("#font[12]{Column number }");
	histoLC->GetYaxis()->SetTitle("#font[12]{Row number}");
	histoLC->Draw("COLZ");
	gStyle->SetStatFont(12);
	gStyle->SetOptStat("e");
	gStyle->SetPalette(kCool);

   	c1->SaveAs("PixelHit.pdf");


}