#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TTree.h"
#include "TLatex.h"
#include "TAttMarker.h"


////////////////////////////////////////////////////////////////////
//                       Definitions
////////////////////////////////////////////////////////////////////

// Name file
const char* filename1 = "ED_epaisseur25um.root"; //width of chips = 50*um
const char* filename2 = "ED_epaisseur50um.root"; //width of chips = 100*um

const char* filename3 = "ED_10deg.root";
const char* filename4 = "ED_20deg.root";
const char* filename5 = "ED_30deg.root";
const char* filename6 = "ED_40deg.root";
const char* filename7 = "ED_50deg.root";
const char* filename8 = "ED_60deg.root";

const char* filename9 = "ED_epaisseur100um.root"; //width of chips = 200*um
const char* filename10 = "ED_epaisseur500um.root"; //width of chips = 1000*um
const char* filename11 = "ED_epaisseur700um.root"; //width of chips = 1400*um
const char* filename12 = "ED_epaisseur600um.root"; //width of chips = 1200*um
const char* filename13 = "ED_epaisseur525um.root"; //width of chips = 1050*um

const char* ED_e50um = "ED_e50um.root"; //width of the chip = 50*um
const char* ED_e100um = "ED_e100um.root"; //width of the chip = 100*um
const char* ED_e300um = "ED_e300um.root"; //width of the chip = 300*um
const char* ED_e500um = "ED_e500um.root"; //width of the chip = 500*um
const char* ED_e600um = "ED_e600um.root"; //width of the chip = 600*um
const char* ED_e700um = "ED_e700um.root"; //width of the chip = 700*um
const char* ED_e800um = "ED_e800um.root"; //width of the chip = 800*um

const char* ED_e50um_1GeV = "ED_e50um_1Gev.root"; //width of the chip = 50*um
const char* ED_e50um_9GeV = "ED_e50um_9Gev.root"; //width of the chip = 50*um
const char* ED_e50um_12GeV = "ED_e50um_12Gev.root"; //width of the chip = 50*um
const char* ED_e50um_20GeV = "ED_e50um_20Gev.root"; //width of the chip = 50*um
const char* ED_e50um_30GeV = "ED_e50um_30Gev.root"; //width of the chip = 50*um


// Name Tree
const char* treename = "Chip0";


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

void Macro1(){

	//*********************************************//

	TFile* f1= new TFile(filename1,"read");
	TTree* tree1 = (TTree*) f1-> Get(treename);

	TFile* f2= new TFile(filename2,"read");
	TTree* tree2 = (TTree*) f2-> Get(treename);

/* ANGLE
	TFile* f3= new TFile(filename3,"read");
	TTree* tree3 = (TTree*) f3-> Get(treename);

	TFile* f4= new TFile(filename4,"read");
	TTree* tree4 = (TTree*) f4-> Get(treename);

	TFile* f5= new TFile(filename5,"read");
	TTree* tree5 = (TTree*) f5-> Get(treename);

	TFile* f6= new TFile(filename6,"read");
	TTree* tree6 = (TTree*) f6-> Get(treename);

	TFile* f7= new TFile(filename7,"read");
	TTree* tree7 = (TTree*) f7-> Get(treename);
*/

////////////////////////////////////////////////////////////////////
//                         Graph 1
////////////////////////////////////////////////////////////////////

/*
	TCanvas* c = new TCanvas;
	c->Divide(2,1);
	c->SetFillStyle(3001);
	c->SetFillColor(kGray);
*/
	//Color
	//c->SetFillColor(410);
    //c->GetFrame()->SetFillColor(1);
    //c->GetFrame()->SetBorderSize(700);
    //c->GetFrame()->SetBorderMode(-1);

	//******** Histo 1D : variable thickness ***********//



////////////////////////////////////////////////////////////////////
//                         Graph 2
////////////////////////////////////////////////////////////////////

	TCanvas* c2 = new TCanvas;
	//c2->SetFillStyle(3001);
	//c2->SetFillColor(kGray);
	c2->SetGrid();
	
	//*********** Histo 2D : Y vs X ****************//

	tree1->Draw("Xposition:Yposition>>Position of hits(100,-3,3,100,-3,3)", "","col");
	auto histoXY = (TH2D*)gPad->GetPrimitive("Position of hits");
	histoXY->GetXaxis()->SetTitle("X axis (mm)  ");
	histoXY->SetTitle("Position of hits on the chip");
	histoXY->GetYaxis()->SetTitle("Y axis (mm)  ");
	histoXY->SetFillColor(kRed);
	histoXY->Draw("LEGO2Z");
	//histoXY->Draw("surf1Z");

	gStyle->SetOptStat("nem");


////////////////////////////////////////////////////////////////////
//                         Graph 3
////////////////////////////////////////////////////////////////////

	TCanvas* c1 = new TCanvas;
	c1->Divide(2,2);
	//c1->SetFillStyle(3001);
	c1->SetFillColor(kGray);

	//*********** Histo 1D : X position*************//

	c1->cd(1);
	c1->SetGrid();
	tree1->Draw("Xposition>>Xposition(500,-3,3)");
	auto histoX = (TH1D*)gPad->GetPrimitive("Xposition");
	histoX->SetTitle("Distribution of hit along the x axis ;X axis (mm) ");
	histoX->GetYaxis()->SetTitle("N count");
	histoX->SetLineColor(kViolet+7);
	histoX->Draw("bar");
	gStyle->SetOptStat("nem");

	//*************** Histo text *******************//
	c1->cd(2);
	TLatex t;
   	t.SetTextFont(132);
   	t.SetTextSize(0.07);
   	t.SetTextAlign(12);
   	t.SetTextAlign(21);
   	t.DrawLatex(0.5,0.6,"Spatial distribution");
   	t.DrawLatex(0.5,0.5,"of hits on the chip");

	//*********** Histo 2D : Y vs X ****************//
 	
 	c1->cd(3);
	c1->SetGrid();
	tree1->Draw("Xposition:Yposition>>HistogramXY(100,-5,5,100,-5,5)", "","col");
	auto histoXY2 = (TH2D*)gPad->GetPrimitive("HistogramXY");
	histoXY2->SetTitle("Distribution of hit along x and y axis;X axis (mm) ");
	histoXY2->GetYaxis()->SetTitle("Y axis (mm) ");
	gStyle->SetPalette(1);
	histoXY2->Draw("COLZ");
	gPad->Update();
	auto palette = (TPaletteAxis*)histoXY2->GetListOfFunctions()->FindObject("palette");
   	palette->SetY2NDC(0.7);
   	//gStyle->SetOptStat(0);

	//*********** Histo 1D : Y position*************//

	c1->cd(4);
	c1->SetGrid();
	tree1->Draw("Yposition>>Yposition(500,-3,3)");
	auto histoY = (TH1D*)gPad->GetPrimitive("Yposition");
	histoY->SetTitle("Distribution of hit along the y axis ;Y axis (mm) ");
	histoY->GetYaxis()->SetTitle("N count");
	histoY->SetLineColor(kViolet+7);
	histoY->Draw("hbar");
	gStyle->SetOptStat("nem");

	//**********************************************//

	f1->Close();

////////////////////////////////////////////////////////////////////
//                         Graph 4
////////////////////////////////////////////////////////////////////
	TFile* f= new TFile(filename1,"read");
	TTree* tree = (TTree*) f-> Get(treename);

	TCanvas* c3 = new TCanvas;
	//c3->SetFillStyle(3001);
	//c3->SetFillColor(kGray);

	//********* Histo 3D : X - Y - Edep ************//
 	
 	c3->cd();
	c3->SetGrid();
	tree->Draw("Edep:Yposition:Xposition>>Title(25,-5,5,25,-5,5,10,0,10)", "","box");
	auto histoXYE = (TH3D*)gPad->GetPrimitive("Title");
	histoXYE->SetTitle("Distribution of hit;X axis (mm) ");
	histoXYE->GetYaxis()->SetTitle("Y axis (mm) ");
	histoXYE->GetZaxis()->SetTitle("Energy (MeV) ");
	//histoXYE->SetMarkerColorAlpha(kBlue, 0.35);
	histoXYE->Draw("COLZ BOX");
	histoXYE->SetFillColor(kRed);

////////////////////////////////////////////////////////////////////

	//c->SaveAs("Graph.pdf");
	//f->Close();
}



	//histo->GetXAxis()->SetTitle("Coordonnée x");
	//histo->GetYAxis()->SetTitle("Fréquence");

/*
write formulas
	TCanvas *c1 = new TCanvas("c1","test",600,700);
	TLatex l;
	l.SetTextAlign(12);
	l.SetTextSize(0.04);
	l.DrawLatex(0.1,0.9,"iruiuiuqlhgiuqir");
	c1->Print("latex.ps");
*/

/*
	*********************************************

	TCanvas* c2 = new TCanvas;

	c2->SetGrid();

	tree->Draw("Xposition>>Position of hits(100,-10,10)");

	c2->cd();
	c2->SaveAs("GraphXpos.pdf");

	*********************************************

	TCanvas* c3 = new TCanvas;

	c3->SetGrid();

	tree->Draw("Yposition>>Position of hits(100,-10,10)");

	c3->cd();
	c3->SaveAs("GraphYpos.pdf");
*/