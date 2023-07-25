#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TTree.h"
#include "TLatex.h"
#include "TAttMarker.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPaletteAxis.h"


////////////////////////////////////////////////////////////////////
//                       Definitions
////////////////////////////////////////////////////////////////////

// Name file
const char* filename1 = "~/bin/CmosProject/build/ED_epaisseur25um.root"; //width of chips = 50*um
const char* filename2 = "~/bin/CmosProject/build/ED_epaisseur50um.root"; //width of chips = 100*um

const char* filename3 = "~/bin/CmosProject/build/ED_10deg.root";
const char* filename4 = "~/bin/CmosProject/build/ED_20deg.root";
const char* filename5 = "~/bin/CmosProject/build/ED_30deg.root";
const char* filename6 = "~/bin/CmosProject/build/ED_40deg.root";
const char* filename7 = "~/bin/CmosProject/build/ED_50deg.root";
const char* filename8 = "~/bin/CmosProject/build/ED_60deg.root";

const char* filename9 = "~/bin/CmosProject/build/ED_epaisseur100um.root"; //width of chips = 200*um
const char* filename10 = "~/bin/CmosProject/build/ED_epaisseur500um.root"; //width of chips = 1000*um
const char* filename11 = "~/bin/CmosProject/build/ED_epaisseur700um.root"; //width of chips = 1400*um
const char* filename12 = "~/bin/CmosProject/build/ED_epaisseur600um.root"; //width of chips = 1200*um
const char* filename13 = "~/bin/CmosProject/build/ED_epaisseur525um.root"; //width of chips = 1050*um

const char* ED_e50um = "~/bin/CmosProject/build/ED_e50um.root"; //width of the chip = 50*um
const char* ED_e100um = "~/bin/CmosProject/build/ED_e100um.root"; //width of the chip = 100*um
const char* ED_e300um = "~/bin/CmosProject/build/ED_e300um.root"; //width of the chip = 300*um
const char* ED_e500um = "~/bin/CmosProject/build/ED_e500um.root"; //width of the chip = 500*um
const char* ED_e600um = "~/bin/CmosProject/build/ED_e600um.root"; //width of the chip = 600*um
const char* ED_e700um = "~/bin/CmosProject/build/ED_e700um.root"; //width of the chip = 700*um
const char* ED_e800um = "~/bin/CmosProject/build/ED_e800um.root"; //width of the chip = 800*um

const char* ED_e50um_1GeV = "~/bin/CmosProject/build/ED_e50um_1Gev.root"; //width of the chip = 50*um
const char* ED_e50um_9GeV = "~/bin/CmosProject/build/ED_e50um_9Gev.root"; //width of the chip = 50*um
const char* ED_e50um_12GeV = "~/bin/CmosProject/build/ED_e50um_12Gev.root"; //width of the chip = 50*um
const char* ED_e50um_20GeV = "~/bin/CmosProject/build/ED_e50um_20Gev.root"; //width of the chip = 50*um
const char* ED_e50um_30GeV = "~/bin/CmosProject/build/ED_e50um_30Gev.root"; //width of the chip = 50*um

const char* ED_test = "~/bin/CmosProject/build/ED_test.root"; //width of the chip = 50*um
const char* ED_pixel3= "~/bin/CmosProject/build/ED_pixel3.root"; //width of the chip = 50*um
const char* ED_PixelTouched= "~/bin/CmosProject/build/ED_PixelTouched.root";   // 2 000 particles
const char* ED_ToMadeCluster= "~/bin/CmosProject/build/ED_ToMadeCluster.root";  // 20 000 particles
const char* ED_ToMadeCluster2= "~/bin/CmosProject/build/ED_ToMadeCluster2.root"; // 200 000 particles
const char* ED_ToMadeCluster3= "~/bin/CmosProject/build/ED_ToMadeCluster3.root"; // 600 000 particles

const char* ED_TestBeam1= "~/bin/CmosProject/build/ED_TestBeam1.root"; // 5000 particles with the beam
const char* ED_TestBeam2= "~/bin/CmosProject/build/ED_TestBeam2.root"; // 10 000 particles with the beam with angle = 50deg
const char* ED_TestBeam3= "~/bin/CmosProject/build/ED_TestBeam3.root"; // 10 000 particles with the beam with angle = 70deg
const char* ED_TestBeam4= "~/bin/CmosProject/build/ED_TestBeam4.root"; // 
const char* ED_TestBeam5= "~/bin/CmosProject/build/ED_TestBeam5.root"; // 

// Name Tree
const char* treename = "Chip0";


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

void SpatialDistrib(){

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
	histoXY->GetXaxis()->SetTitle("#font[12]{X axis (mm) }");
	histoXY->SetTitle("#font[12]{Position of hits on the chip}");
	histoXY->GetYaxis()->SetTitle("#font[12]{Y axis (mm) }");
	histoXY->SetFillColor(kRed);
	histoXY->Draw("LEGO2Z");
	//histoXY->Draw("surf1Z");
	gStyle->SetStatFont(12);
	gStyle->SetOptStat("nem");

	c2->SaveAs("PositionHitsXY.pdf");

////////////////////////////////////////////////////////////////////
//                         Graph 3
////////////////////////////////////////////////////////////////////

	TCanvas* c1 = new TCanvas;
	c1->Divide(2,2);
	//c1->SetFillStyle(3001);
	c1->SetFillColor(kWhite);

	//*********** Histo 1D : X position*************//

	c1->cd(1);
	c1->SetGrid();
	tree1->Draw("Xposition>>Xposition(500,-3,3)");
	auto histoX = (TH1D*)gPad->GetPrimitive("Xposition");
	histoX->SetTitle("#font[12]{Distribution of hit along the x axis} ;#font[12]{X axis (mm) }");
	histoX->GetYaxis()->SetTitle("#font[12]{N count}");
	histoX->SetLineColor(kViolet+7);
	histoX->Draw("bar");
	gStyle->SetStatFont(12);
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
	histoXY2->SetTitle("#font[12]{Distribution of hit along x and y axis};#font[12]{X axis (mm) }");
	histoXY2->GetYaxis()->SetTitle("#font[12]{Y axis (mm) }");
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
	histoY->SetTitle("#font[12]{Distribution of hit along the y axis };#font[12]{Y axis (mm) }");
	histoY->GetYaxis()->SetTitle("#font[12]{N count}");
	histoY->SetLineColor(kViolet+7);
	histoY->Draw("hbar");
	gStyle->SetStatFont(12);
	gStyle->SetOptStat("nem");

	//**********************************************//

	c1->SaveAs("3histo_X_XY_Y.pdf");
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
	tree->Draw("Edep:Yposition:Xposition>>Title(50,-5,5,50,-5,5,10,0,10)", "","box");
	auto histoXYE = (TH3D*)gPad->GetPrimitive("Title");
	histoXYE->SetTitle("#font[12]{Distribution of hit};#font[12]{X axis (mm) }");
	histoXYE->GetYaxis()->SetTitle("#font[12]{Y axis (mm) }");
	histoXYE->GetZaxis()->SetTitle("#font[12]{Energy (MeV) }");
	//histoXYE->SetMarkerColorAlpha(kBlue, 0.35);
	//histoXYE->Draw("COLZ BOX");
	histoXYE->Draw("BOX2");
	histoXYE->SetFillColor(kRed);

	c3->SaveAs("EnergyXY.pdf");
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