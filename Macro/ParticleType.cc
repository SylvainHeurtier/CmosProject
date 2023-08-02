#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TAttMarker.h"
#include "TAttLine.h"
#include "TH1F.h"
#include "TF1.h"
#include "TMath.h"


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

void ParticleType(){


////////////////////////////////////////////////////////////////////
//                            Graph 1 
////////////////////////////////////////////////////////////////////

	//*********************************************//

	TFile* fetest= new TFile(ED_test,"read");  //width of chip = 50*um
	TTree* treetest= (TTree*) fetest-> Get(treename);

	TCanvas* c1 = new TCanvas;
	//Color
	c1->Divide(2,2);
	c1->SetGrid();
	c1->SetFillColor(3001);
    c1->GetFrame()->SetFillColor(1);
    c1->GetFrame()->SetBorderSize(700);
    c1->GetFrame()->SetBorderMode(-1);

	//*************** Histo 2D ********************//

/*
	treetest->Draw("Edep>>EneregyDepositTest()","NameParticle==char(pi+)","");
	auto histoTest = (TH1D*)gPad->GetPrimitive("EneregyDepositTest");
	//histoTest->GetYaxis()->SetTitle("#font[12]{Z axis (mm)}");
	//histoTest->SetTitle("#font[12]{Energy deposit in the chip - Width d = 50#mum}");
	//histoTest->GetXaxis()->SetTitle("#font[12]{Energy deposit (MeV)}");
	gStyle->SetStatFont(12);
	histoTest->Draw();
*/

/*
	// column of strings
	char* label;
	TLeafC* leafLabel = (TLeafC*)treetest->GetLeaf("NameParticle");
	leafLabel->SetAddress(label);

	// Get number of entries (events)
	int num = treetest->GetEntries();
	std::cout << "number of events = " << num << std::endl;

	// Read events in a loop
	for(int i=0;i<num;i++) {
		treetest->GetEntry(i);
   		std::cout << i << "th entry: " << std::endl;
   		// print label
    	if(leafLabel) {
      		char* labelChar = leafLabel->GetValueString();
      		std::cout << "label: " << std::string(labelChar) << std::endl;
    	}
    }
*/
/*
    c1->cd(1);
    treetest->Draw("Edep:PDGcode>>EneregyDepositTest()","","col");
	auto histoTest = (TH2D*)gPad->GetPrimitive("EneregyDepositTest");
	//histoTest->GetYaxis()->SetTitle("#font[12]{Z axis (mm)}");
	//histoTest->SetTitle("#font[12]{Energy deposit in the chip - Width d = 50#mum}");
	//histoTest->GetXaxis()->SetTitle("#font[12]{Energy deposit (MeV)}");
	gStyle->SetStatFont(12);
	histoTest->Draw();

    c1->cd(2);
	treetest->Draw("PDGcode>>EneregyDepositTest()","","col");
	auto histoTest3 = (TH1I*)gPad->GetPrimitive("EneregyDepositTest");
	//histoTest3->GetYaxis()->SetTitle("#font[12]{Z axis (mm)}");
	//histoTest3->SetTitle("#font[12]{Energy deposit in the chip - Width d = 50#mum}");
	//histoTest3->GetXaxis()->SetTitle("#font[12]{Energy deposit (MeV)}");
	gStyle->SetStatFont(12);
	histoTest3->Draw();
*/
    c1->cd(1);
	treetest->Draw("NumParticle>>NumParticle(50, -6.5, 5.9)","","");
	auto histoTest4 = (TH1I*)gPad->GetPrimitive("NumParticle");
	histoTest4->GetYaxis()->SetTitle("#font[12]{N count}");
	histoTest4->SetTitle("#font[12]{Number code of the particule}");
	histoTest4->GetXaxis()->SetTitle("#font[12]{Number}");
	histoTest4->SetLineColor(kCyan+2);
	histoTest4->SetFillStyle(3003);
    histoTest4->SetFillColor(kCyan+2);
	gStyle->SetStatFont(12);
	histoTest4->Draw();

	auto legend3 = new TLegend(0.9,0.3,0.6,0.9);
	gStyle->SetLegendFont(12);
   	legend3->SetHeader("Legend of the graph:","C"); // option "C" allows to center the header
   	//legend3->SetNColumns(2);
   	legend3->AddEntry((TObject*)0, " Proton : -1", "");
   	legend3->AddEntry((TObject*)0, " Anti-proton : -1", "");
   	legend3->AddEntry((TObject*)0, " Electron : -2", "");
   	legend3->AddEntry((TObject*)0, " Positron : -2", "");
   	legend3->AddEntry((TObject*)0, " Muon- : -3", "");
   	legend3->AddEntry((TObject*)0, " Muon+ : 3", "");
   	legend3->AddEntry((TObject*)0, " Kaon- : -4", "");
   	legend3->AddEntry((TObject*)0, " Kaon+ : 4", "");
   	legend3->AddEntry((TObject*)0, " Pion- : -6", "");
   	legend3->AddEntry((TObject*)0, " Pion+ : 6", "");
   	legend3->AddEntry((TObject*)0, " Other particles : 0", "");
   	legend3->Draw();

    c1->cd(2);
	treetest->Draw("NumParticle>>NumParticle2(50, -7, 7)","","");
	auto histoTest6 = (TH1I*)gPad->GetPrimitive("NumParticle2");
	histoTest6->GetYaxis()->SetTitle("#font[12]{N count}");
	histoTest6->SetTitle("#font[12]{Number code of the particule}");
	histoTest6->GetXaxis()->SetTitle("#font[12]{Number}");
	histoTest6->SetLineColor(kCyan+2);
	histoTest6->SetFillStyle(3003);
    histoTest6->SetFillColor(kCyan+2);
	gStyle->SetStatFont(12);
	histoTest6->Draw();

	auto legend4 = new TLegend(0.2,0.3,0.5,0.9);
	gStyle->SetLegendFont(12);
   	legend4->SetHeader("Legend of the graph:","C"); // option "C" allows to center the header
   	//legend4->SetNColumns(2);
   	legend4->AddEntry((TObject*)0, " Proton : -1", "");
   	legend4->AddEntry((TObject*)0, " Anti-proton : -1", "");
   	legend4->AddEntry((TObject*)0, " Electron : -2", "");
   	legend4->AddEntry((TObject*)0, " Positron : -2", "");
   	legend4->AddEntry((TObject*)0, " Muon- : -3", "");
   	legend4->AddEntry((TObject*)0, " Muon+ : 3", "");
   	legend4->AddEntry((TObject*)0, " Kaon- : -4", "");
   	legend4->AddEntry((TObject*)0, " Kaon+ : 4", "");
   	legend4->AddEntry((TObject*)0, " Pion- : -6", "");
   	legend4->AddEntry((TObject*)0, " Pion+ : 6", "");
   	legend4->AddEntry((TObject*)0, " Other particles : 0", "");
   	legend4->Draw();


    c1->cd(3);
	treetest->Draw("charge>>charge(50)","","");
	auto histoTest5 = (TH1I*)gPad->GetPrimitive("charge");
	histoTest5->GetYaxis()->SetTitle("#font[12]{N count}");
	histoTest5->SetTitle("#font[12]{Charge of particle detected}");
	histoTest5->GetXaxis()->SetTitle("#font[12]{Charge}");
	histoTest5->SetLineColor(kCyan+2);
	histoTest5->SetFillStyle(3003);
    histoTest5->SetFillColor(kCyan+2);
	gStyle->SetStatFont(12);
	histoTest5->Draw();

	c1->SaveAs("TypeOfParticleDetected.pdf");

}