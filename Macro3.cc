#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TLatex.h"
#include "TAttMarker.h"
#include "TAttLine.h"
#include "TH1F.h"
#include "TF1.h"
#include "TMath.h"


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

void Macro3(){

	//*********************************************//

	TFile* fe50= new TFile(ED_e50um,"read");  //width of chip = 50*um
	TTree* tree50= (TTree*) fe50-> Get(treename);

	TCanvas* c = new TCanvas;

	//Color
	c->SetGrid();
	c->SetFillColor(3001);
    c->GetFrame()->SetFillColor(1);
    c->GetFrame()->SetBorderSize(700);
    c->GetFrame()->SetBorderMode(-1);

	//******** Histo 1D : variable thickness ***********//

	tree50->Draw("Edep>>Parameters(1000,0.,0.07)");//0.05
	auto histoE50 = (TH1D*)gPad->GetPrimitive("Parameters");
	histoE50->GetYaxis()->SetTitle("N count");
	histoE50->SetTitle("Energy deposit on the chip;Energy deposit");
	histoE50->SetLineColor(kCyan+2);
	histoE50->SetLineWidth(1);
	histoE50->SetFillStyle(3003);
    histoE50->SetFillColor(kCyan+2);
	double integral = histoE50->Integral();
	std::cout << integral << std::endl;

//Fitting with Landau
	
	TF1 *f2 = new TF1("f2", "[0]*TMath::Gaus(x,[1],[2],0)*TMath::Landau(x,[3],[4],0)", 0, 0.09);
	f2->SetParameters(8804, 0.015,0.2,0.0118619,0.00150282);
	//f2->SetParameters(1, 0, 0.07);
	//
	histoE50->Fit(f2,"MRI","",0.003,0.07);
	histoE50->GetFunction("f2")->SetLineColor(kOrange+1);
	gStyle->SetOptFit(1101);
	gStyle->SetOptStat("ime");


	auto legend = new TLegend(0.9,0.8,0.7,0.9);
   	legend->SetHeader("Legend of the graph:","C"); // option "C" allows to center the header
   	legend->AddEntry(histoE50,"Histogram","L");
   	legend->AddEntry("landau","fit","L");
   	legend->Draw();

}