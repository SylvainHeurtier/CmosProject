#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TLatex.h"
#include "TAttMarker.h"
#include "TAttLine.h"
 

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

void Macro2(){

	//*********************************************//

	TFile* f1= new TFile(filename1,"read");  //width of chip = 50*um
	TTree* tree1 = (TTree*) f1-> Get(treename);

	TFile* f2= new TFile(filename2,"read");  //width of chip = 100*um
	TTree* tree2 = (TTree*) f2-> Get(treename);

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

	TFile* f8= new TFile(filename8,"read");
	TTree* tree8 = (TTree*) f8-> Get(treename);

	TFile* f9= new TFile(filename9,"read");  //width of chip = 200*um
	TTree* tree9 = (TTree*) f9-> Get(treename);

	TFile* f10= new TFile(filename10,"read");  //width of chip = 1000*um
	TTree* tree10 = (TTree*) f10-> Get(treename);

	TFile* f11= new TFile(filename11,"read");  //width of chip = 1400*um
	TTree* tree11 = (TTree*) f11-> Get(treename);

	TFile* f12= new TFile(filename12,"read");  //width of chip = 1200*um
	TTree* tree12 = (TTree*) f12-> Get(treename);

	TFile* f13= new TFile(filename13,"read");  //width of chip = 1050*um
	TTree* tree13 = (TTree*) f13-> Get(treename);


////////////////////////////////////////////////////////////////////
//     Graph 1 - Variation de l'épaisseur de toutes les chips
////////////////////////////////////////////////////////////////////
	
	TCanvas* c = new TCanvas;
	//c->SetFillStyle(3001);
	//c->SetFillColor(kGray);
	//Color
	c->SetFillColor(3001);
    c->GetFrame()->SetFillColor(1);
    c->GetFrame()->SetBorderSize(700);
    c->GetFrame()->SetBorderMode(-1);
	c->SetGrid();
	c->cd();
	gStyle->SetOptStat(0);

	//******** Histo 1D : variable thickness ***********//

	tree1->Draw("Edep>>EneregyDeposit(300,0.,0.6)");
	auto histoE1 = (TH1D*)gPad->GetPrimitive("EneregyDeposit");
	histoE1->GetYaxis()->SetTitle("N count");
	histoE1->SetTitle("Energy deposit on the chip;Energy deposit (MeV)");
	histoE1->SetLineColor(kRed);
	histoE1->SetLineWidth(2);
	//Double_t* i = histoE1->GetIntegral();

	tree2->Draw("Edep>>EneregyDeposit2(300,0.,0.6)","","same");
	auto histoE2 = (TH1D*)gPad->GetPrimitive("EneregyDeposit2");
	histoE2->SetLineColor(kBlue);
	histoE2->SetLineWidth(2);

	tree9->Draw("Edep>>EneregyDeposit9(300,0.,0.6)","","same");
	auto histoE10 = (TH1D*)gPad->GetPrimitive("EneregyDeposit9");
	histoE10->SetLineColor(kViolet);
	histoE10->SetLineWidth(2);

	tree10->Draw("Edep>>EneregyDeposit10(300,0.,0.6)","","same");
	auto histoE11 = (TH1D*)gPad->GetPrimitive("EneregyDeposit10");
	histoE11->SetLineColor(kOrange);
	histoE11->SetLineWidth(2);

	tree11->Draw("Edep>>EneregyDeposit11(300,0.,0.6)","","same");
	auto histoE12 = (TH1D*)gPad->GetPrimitive("EneregyDeposit11");
	histoE12->SetLineColor(kGray);
	histoE12->SetLineWidth(2);

	tree12->Draw("Edep>>EneregyDeposit12(300,0.,0.6)","","same");
	auto histoE13 = (TH1D*)gPad->GetPrimitive("EneregyDeposit12");
	histoE13->SetLineColor(kBlack);
	histoE13->SetLineWidth(2);

	tree13->Draw("Edep>>EneregyDeposit13(300,0.,0.6)","","same");
	auto histoE14 = (TH1D*)gPad->GetPrimitive("EneregyDeposit13");
	histoE14->SetLineColor(kGreen);
	histoE14->SetLineWidth(2);

/*
	tree12->Draw("Edep>>EneregyDeposit12(300,0.,0.1)","","same");
	auto histoE13 = (TH1D*)gPad->GetPrimitive("EneregyDeposit12");
	histoE13->SetLineColor(kBlack);
	histoE13->SetLineWidth(2);
*/
	auto legend = new TLegend(0.9,0.6,0.5,0.9);
   	legend->SetHeader("Legend of the graph:","C"); // option "C" allows to center the header
   	legend->AddEntry(histoE1,"Width of chips: d = 50 #mum","L");
   	legend->AddEntry(histoE2,"Width of chips: d = 100 #mum","L");
   	legend->AddEntry(histoE10,"Width of chips: d = 200 #mum","L");
   	legend->AddEntry(histoE11,"Width of chips: d = 1000 #mum","L");
    legend->AddEntry(histoE14,"Width of chips: d = 1050 #mum","L");
   	legend->AddEntry(histoE13,"Width of chips: d = 1200 #mum","L");
    legend->AddEntry(histoE12,"Width of chips: d = 1400 #mum","L");
   	legend->Draw();

////////////////////////////////////////////////////////////////////
//           Graph 2 - variation de l'angle de la chip
////////////////////////////////////////////////////////////////////
	

	//******** Histo 1D : Variable angle ***********//

	TCanvas* c2 = new TCanvas;
	c2->SetFillColor(3001);
    c2->GetFrame()->SetFillColor(1);
    c2->GetFrame()->SetBorderSize(700);
    c2->GetFrame()->SetBorderMode(-1);
	c2->SetGrid();

	TFile* f1bis= new TFile(filename1,"read");
	TTree* tree1bis = (TTree*) f1bis-> Get(treename);

	tree1bis->Draw("Edep>>EneregyDeposit(200,0.,0.045)");
	auto histoE3 = (TH1D*)gPad->GetPrimitive("EneregyDeposit");
	histoE3->GetYaxis()->SetTitle("N count");
	histoE3->SetTitle("Energy deposit on the chip;Energy deposit (MeV)");
	histoE3->SetLineColor(kOrange+4);
	histoE3->SetLineWidth(2);

	tree3->Draw("Edep>>EneregyDeposit3(200,0.,0.045)","","same");
	auto histoE4 = (TH1D*)gPad->GetPrimitive("EneregyDeposit3");
	histoE4->SetLineColor(kRed);
	histoE4->SetLineWidth(2);

	tree4->Draw("Edep>>EneregyDeposit4(200,0.,0.045)","","same");
	auto histoE5 = (TH1D*)gPad->GetPrimitive("EneregyDeposit4");
	histoE5->SetLineColor(kGreen+2);
	histoE5->SetLineWidth(2);

	tree5->Draw("Edep>>EneregyDeposit5(200,0.,0.045)","","same");
	auto histoE6 = (TH1D*)gPad->GetPrimitive("EneregyDeposit5");
	histoE6->SetLineColor(kMagenta);
	histoE6->SetLineWidth(2);

	tree6->Draw("Edep>>EneregyDeposit6(200,0.,0.045)","","same");
	auto histoE7 = (TH1D*)gPad->GetPrimitive("EneregyDeposit6");
	histoE7->SetLineColor(kViolet+1);
	histoE7->SetLineWidth(2);

	tree7->Draw("Edep>>EneregyDeposit7(200,0.,0.045)","","same");
	auto histoE8 = (TH1D*)gPad->GetPrimitive("EneregyDeposit7");
	histoE8->SetLineColor(kBlue);
	histoE8->SetLineWidth(2);

	tree8->Draw("Edep>>EneregyDeposit8(200,0.,0.045)","","same");
	auto histoE9 = (TH1D*)gPad->GetPrimitive("EneregyDeposit8");
	histoE9->SetLineColor(kBlack);
	histoE9->SetLineWidth(2);

	auto legend2 = new TLegend(0.9,0.7,0.7,0.9);
   	legend2->SetHeader("Legend of the graph:","C"); // option "C" allows to center the header
   	legend2->AddEntry(histoE3,"Angle #theta = 0 deg","L");
   	legend2->AddEntry(histoE4,"Angle #theta = 10 deg","L");
   	legend2->AddEntry(histoE5,"Angle #theta = 20 deg","L");
   	legend2->AddEntry(histoE6,"Angle #theta = 30 deg","L");
   	legend2->AddEntry(histoE7,"Angle #theta = 40 deg","L");
   	legend2->AddEntry(histoE8,"Angle #theta = 50 deg","L");
   	legend2->AddEntry(histoE9,"Angle #theta = 60 deg","L");
   	legend2->Draw();

   	gStyle->SetOptStat(0);


////////////////////////////////////////////////////////////////////
//     Graph 3 - Variation de l'épaisseur de la chip centrale
////////////////////////////////////////////////////////////////////

	TFile* fe50= new TFile(ED_e50um,"read");  //width of chip = 50*um
	TTree* tree50= (TTree*) fe50-> Get(treename);

	TFile* fe100= new TFile(ED_e100um,"read");  //width of chip = 100*um
	TTree* tree100 = (TTree*) fe100-> Get(treename);

	TFile* fe300= new TFile(ED_e300um,"read");  //width of chip = 300*um
	TTree* tree300 = (TTree*) fe300-> Get(treename);

	TFile* fe500= new TFile(ED_e500um,"read");  //width of chip = 500*um
	TTree* tree500 = (TTree*) fe500-> Get(treename);

	TFile* fe600= new TFile(ED_e600um,"read");  //width of chip = 600*um
	TTree* tree600 = (TTree*) fe600-> Get(treename);

	TFile* fe700= new TFile(ED_e700um,"read");  //width of chip = 700*um
	TTree* tree700 = (TTree*) fe700-> Get(treename);

	TFile* fe800= new TFile(ED_e800um,"read");  //width of chip = 800*um
	TTree* tree800 = (TTree*) fe800-> Get(treename);

	TCanvas* c3 = new TCanvas;
	c3->SetFillStyle(3001);
	c3->SetFillColor(kWhite);

	//******** Histo 1D : variable thickness ***********//

	c3->SetGrid();

	tree50->Draw("Edep>>EneregyDeposit50(1000,0.,0.3)");
	auto histoE50 = (TH1D*)gPad->GetPrimitive("EneregyDeposit50");
	histoE50->GetYaxis()->SetTitle("N count");
	histoE50->SetTitle("Energy deposit on the chip;Energy deposit (MeV)");
	histoE50->SetLineColor(kRed);
	histoE50->SetLineWidth(2);

	tree100->Draw("Edep>>EneregyDeposit100(300,0.,0.3)","","same");
	auto histoE100 = (TH1D*)gPad->GetPrimitive("EneregyDeposit100");
	histoE100->SetLineColor(kBlue);
	histoE100->SetLineWidth(2);

	tree300->Draw("Edep>>EneregyDeposit300(300,0.,0.3)","","same");
	auto histoE300 = (TH1D*)gPad->GetPrimitive("EneregyDeposit300");
	histoE300->SetLineColor(kGray);
	histoE300->SetLineWidth(2);

	tree500->Draw("Edep>>EneregyDeposit500(300,0.,0.3)","","same");
	auto histoE500 = (TH1D*)gPad->GetPrimitive("EneregyDeposit500");
	histoE500->SetLineColor(kOrange);
	histoE500->SetLineWidth(2);

	tree600->Draw("Edep>>EneregyDeposit600(300,0.,0.3)","","same");
	auto histoE600 = (TH1D*)gPad->GetPrimitive("EneregyDeposit600");
	histoE600->SetLineColor(kBlack);
	histoE600->SetLineWidth(2);

	tree700->Draw("Edep>>EneregyDeposit700(300,0.,0.3)","","same");
	auto histoE700 = (TH1D*)gPad->GetPrimitive("EneregyDeposit700");
	histoE700->SetLineColor(kMagenta);
	histoE700->SetLineWidth(2);

	tree800->Draw("Edep>>EneregyDeposit800(300,0.,0.3)","","same");
	auto histoE800 = (TH1D*)gPad->GetPrimitive("EneregyDeposit800");
	histoE800->SetLineColor(kGreen);
	histoE800->SetLineWidth(2);

	auto legend3 = new TLegend(0.9,0.6,0.5,0.9);
   	legend3->SetHeader("Legend of the graph:","C"); // option "C" allows to center the header
   	legend3->AddEntry(histoE50,"Width of the chip: d = 50 #mum","L");
   	legend3->AddEntry(histoE100,"Width of the chip: d = 100 #mum","L");
   	legend3->AddEntry(histoE300,"Width of the chip: d = 300 #mum","L");
   	legend3->AddEntry(histoE500,"Width of the chip: d = 500 #mum","L");
   	legend3->AddEntry(histoE600,"Width of the chip: d = 600 #mum","L");
   	legend3->AddEntry(histoE700,"Width of the chip: d = 700 #mum","L");
   	legend3->AddEntry(histoE800,"Width of the chip: d = 800 #mum","L");
   	legend3->Draw();

   	gStyle->SetOptStat(0);

////////////////////////////////////////////////////////////////////
//            Graph 4 - Energie déposée en fonction de z
////////////////////////////////////////////////////////////////////
	
	TCanvas* c1 = new TCanvas;
	//c1->SetFillStyle(3001);
	//c1->SetFillColor(kGray);
	c1->SetGrid();
	c1->Divide(2,2);
	gStyle->SetOptStat("nem");


	//*********** Histo 2D : E vs Z ****************//
	c1->cd(1);
	tree50->Draw("Zposition:Edep>>EneregyDepositZE(85,-0.01,0.07,85,-0.023,0.024)","","col");
	//tree50->Draw("Zposition:Edep>>EneregyDepositZE(85,-0.01,0.07,85,-0.035,0.035)","","col");
	auto histoZE = (TH2D*)gPad->GetPrimitive("EneregyDepositZE");
	histoZE->GetYaxis()->SetTitle("Z axis (mm)");
	histoZE->SetTitle("Energy deposit in the chip - Width d = 50#mum");
	histoZE->GetXaxis()->SetTitle("Energy deposit (MeV)");
	histoZE->Draw("LEGO2Z");

	c1->cd(2);
	tree100->Draw("Zposition:Edep>>EneregyDepositZE1(85,-0.01,0.15,85,-0.098,0.099)","","col");
	//tree100->Draw("Zposition:Edep>>EneregyDepositZE1(85,-0.01,0.15,85,-0.15,0.15)","","col");
	auto histoZE1 = (TH1D*)gPad->GetPrimitive("EneregyDepositZE1");
	histoZE1->GetYaxis()->SetTitle("Z axis (mm)");
	histoZE1->SetTitle("Energy deposit in the chip - Width d = 200#mum");
	histoZE1->GetXaxis()->SetTitle("Energy deposit (MeV)");
	histoZE1->Draw("LEGO2Z");

	c1->cd(3);
	tree500->Draw("Zposition:Edep>>EneregyDepositZE2(85,-0.05,0.4,85,-0.248,0.248)","","col");
	//tree500->Draw("Zposition:Edep>>EneregyDepositZE2(85,-0.005,0.4,85,-0.35,0.35)","","col");
	auto histoZE2 = (TH1D*)gPad->GetPrimitive("EneregyDepositZE2");
	histoZE2->GetYaxis()->SetTitle("Z axis (mm)");
	histoZE2->SetTitle("Energy deposit in the chip - Width d = 500#mum");
	histoZE2->GetXaxis()->SetTitle("Energy deposit (MeV)");
	histoZE2->Draw("LEGO2Z");

	c1->cd(4);
	tree800->Draw("Zposition:Edep>>EneregyDepositZE3(85,-0.05,0.7,85,-0.399,0.39)","","col");
	//tree800->Draw("Zposition:Edep>>EneregyDepositZE3(85,-0.005,0.7,85,-0.5,0.5)","","col");
	auto histoZE3 = (TH1D*)gPad->GetPrimitive("EneregyDepositZE3");
	histoZE3->GetYaxis()->SetTitle("Z axis (mm)");
	histoZE3->SetTitle("Energy deposit in the chip - Width d = 800#mum");
	histoZE3->GetXaxis()->SetTitle("Energy deposit (MeV)");
	histoZE3->Draw("LEGO2Z");


////////////////////////////////////////////////////////////////////
//   Graph 5 - Energie déposée en fonction de l'énergie du beam
////////////////////////////////////////////////////////////////////

	TFile* fe1GeV= new TFile(ED_e50um_1GeV,"read");  //width of chip = 50*um
	TTree* tree1GeV = (TTree*) fe1GeV-> Get(treename);

	TFile* fe9GeV= new TFile(ED_e50um_9GeV,"read");  //width of chip = 50*um
	TTree* tree9GeV = (TTree*) fe9GeV-> Get(treename);

	TFile* fe12GeV= new TFile(ED_e50um_12GeV,"read");  //width of chip = 50*um
	TTree* tree12GeV = (TTree*) fe12GeV-> Get(treename);

	TFile* fe20GeV= new TFile(ED_e50um_20GeV,"read");  //width of chip = 50*um
	TTree* tree20GeV = (TTree*) fe20GeV-> Get(treename);

	TFile* fe30GeV= new TFile(ED_e50um_30GeV,"read");  //width of chip = 50*um
	TTree* tree30GeV = (TTree*) fe30GeV-> Get(treename);

	TCanvas* c4 = new TCanvas;
	c4->SetFillStyle(3001);
	c4->SetFillColor(kWhite);
	c4->SetGrid();
	gStyle->SetOptStat(0);

	//******** Histo 1D : variable thickness ***********//

	tree1GeV->Draw("Edep>>EneregyDeposit1GeV(200,0.,0.04)");
	auto histoE1GeV = (TH1D*)gPad->GetPrimitive("EneregyDeposit1GeV");
	histoE1GeV->GetYaxis()->SetTitle("N count");
	histoE1GeV->SetTitle("Energy deposit on the chip;Energy deposit (MeV)");
	histoE1GeV->SetLineColor(kRed);
	histoE1GeV->SetLineWidth(2);

	tree9GeV->Draw("Edep>>EneregyDeposit9GeV(300,0.,0.04)","","same");
	auto histoE9GeV = (TH1D*)gPad->GetPrimitive("EneregyDeposit9GeV");
	histoE9GeV->SetLineColor(kBlue);
	histoE9GeV->SetLineWidth(2);

	tree12GeV->Draw("Edep>>EneregyDeposit12GeV(300,0.,0.04)","","same");
	auto histoE12GeV = (TH1D*)gPad->GetPrimitive("EneregyDeposit12GeV");
	histoE12GeV->SetLineColor(kViolet);
	histoE12GeV->SetLineWidth(2);

	tree20GeV->Draw("Edep>>EneregyDeposit20GeV(300,0.,0.04)","","same");
	auto histoE20GeV = (TH1D*)gPad->GetPrimitive("EneregyDeposit20GeV");
	histoE20GeV->SetLineColor(kOrange);
	histoE20GeV->SetLineWidth(2);

	tree30GeV->Draw("Edep>>EneregyDeposit30GeV(300,0.,0.04)","","same");
	auto histoE30GeV = (TH1D*)gPad->GetPrimitive("EneregyDeposit30GeV");
	histoE30GeV->SetLineColor(kGreen+2);
	histoE30GeV->SetLineWidth(2);

	auto legend4 = new TLegend(0.9,0.6,0.5,0.9);
   	legend4->SetHeader("Legend of the graph:","C"); // option "C" allows to center the header
   	legend4->AddEntry(histoE1GeV,"Energy of the beam: E = 1 GeV","L");
   	legend4->AddEntry(histoE9GeV,"Energy of the beam: E = 9 GeV","L");
   	legend4->AddEntry(histoE12GeV,"Energy of the beam: E = 12 GeV","L");
   	legend4->AddEntry(histoE20GeV,"Energy of the beam: E = 20 GeV","L");
   	legend4->AddEntry(histoE30GeV,"Energy of the beam: E = 30 GeV","L");
   	legend4->Draw();
}