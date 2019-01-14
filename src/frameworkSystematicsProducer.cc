#ifndef utilitysystematics
#define utilitysystematics
/*
 *
 *
 *
 * This is where the functions used to produce the plots for the systematic 
 *      uncertainty on the photon energy scale are defined.
 *
 *
 */

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TTree.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGaxis.h>
#include <TLegend.h>
#include <TCollection.h>
#include <TKey.h>
#include <TPave.h>
#include <TLatex.h>
#include <TPaletteAxis.h>
#include <TStyle.h>
#include <TTree.h>
#include "../interface/frameworkSystematicsProducer.h"

//#define ETA_VETO

extern std::string DIRECTORY_NAME;

/// Produce FNUF Histograms only analyzes two files at a time

void mySystematicsProducer::produce_LookUpTables(std::string fileName){

    std::cout << "begin producing look-up tables... " << std::endl;

	int numR9bins = 5;
	double r9Bins[6] = {0, 0.8, 0.9, 0.92, 0.96, 1.00}; 

	int numEtaBins = 8;
	double etaBins [9] = {0, 0.3, 0.7, 1.1, 1.4442, 1.566, 1.8, 2.1, 2.5};
	TFile* myHistograms = new TFile(fileName.c_str(), "READ");

    std::cout << "initializing histograms ... " << std::endl;
    
	TH2F * mean_0 = new TH2F("mean_0", "Photon Systematics [%], 0 < R9 < 0.8", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean_1 = new TH2F("mean_1", "Photon Systematics [%], 0.8 < R9 < 0.9", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean_2 = new TH2F("mean_2", "Photon Systematics [%], 0.9 < R9 < 0.92", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean_3 = new TH2F("mean_3", "Photon Systematics [%], 0.92 < R9 < 0.96", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean_4 = new TH2F("mean_4", "Photon Systematics [%], 0.96 < R9 < 1.0", numEtaBins, etaBins, 100, 0.005, 1.005);

	std::vector< std::vector<TH1F*> > e_0_hists;
	std::vector< std::vector<TH1F*> > e_1_hists;
	std::vector< std::vector<TH1F*> > e_2_hists;
	std::vector< std::vector<TH1F*> > e_3_hists;
	std::vector< std::vector<TH1F*> > e_4_hists;
	std::vector< std::vector<TH1F*> > g_0_hists;
	std::vector< std::vector<TH1F*> > g_1_hists;
	std::vector< std::vector<TH1F*> > g_2_hists;
	std::vector< std::vector<TH1F*> > g_3_hists;
	std::vector< std::vector<TH1F*> > g_4_hists;

	std::vector<TH1F*> e_0;
	std::vector<TH1F*> e_1;
	std::vector<TH1F*> e_2;
	std::vector<TH1F*> e_3;
	std::vector<TH1F*> e_4;
	std::vector<TH1F*> g_0;
	std::vector<TH1F*> g_1;
	std::vector<TH1F*> g_2;
	std::vector<TH1F*> g_3;
	std::vector<TH1F*> g_4;

	char title [50];
	for(int i = 0; i < numEtaBins; i++){
		for(int j = 0; j < 100; j++){
			sprintf( title, "e_0_%i_%i_%i", i, i+1, j);
			e_0.push_back((TH1F*)myHistograms->Get(title));
			sprintf( title, "e_1_%i_%i_%i", i, i+1, j);
			e_1.push_back((TH1F*)myHistograms->Get(title));
			sprintf( title, "e_2_%i_%i_%i", i, i+1, j);
			e_2.push_back((TH1F*)myHistograms->Get(title));
			sprintf( title, "e_3_%i_%i_%i", i, i+1, j);
			e_3.push_back((TH1F*)myHistograms->Get(title));
			sprintf( title, "e_4_%i_%i_%i", i, i+1, j);
			e_4.push_back((TH1F*)myHistograms->Get(title));
			sprintf( title, "g_0_%i_%i_%i", i, i+1, j);
			g_0.push_back((TH1F*)myHistograms->Get(title));
			sprintf( title, "g_1_%i_%i_%i", i, i+1, j);
			g_1.push_back((TH1F*)myHistograms->Get(title));
			sprintf( title, "g_2_%i_%i_%i", i, i+1, j);
			g_2.push_back((TH1F*)myHistograms->Get(title));
			sprintf( title, "g_3_%i_%i_%i", i, i+1, j);
			g_3.push_back((TH1F*)myHistograms->Get(title));
			sprintf( title, "g_4_%i_%i_%i", i, i+1, j);
			g_4.push_back((TH1F*)myHistograms->Get(title));
      	}
		e_0_hists.push_back(e_0);
		e_1_hists.push_back(e_1);
		e_2_hists.push_back(e_2);
		e_3_hists.push_back(e_3);
		e_4_hists.push_back(e_4);
		g_0_hists.push_back(g_0);
		g_1_hists.push_back(g_1);
		g_2_hists.push_back(g_2);
		g_3_hists.push_back(g_3);
		g_4_hists.push_back(g_4);
		e_0.clear();
		e_1.clear();
		e_2.clear();
		e_3.clear();
		e_4.clear();
		g_0.clear();
		g_1.clear();
		g_2.clear();
		g_3.clear();
		g_4.clear();
	}

    std::cout << "evaluating systematics ... " << std::endl;

    std::string uncertainty_low = "rootFiles/uncertainty_hists_low.root";
    std::string uncertainty_high = "rootFiles/uncertainty_hists_high.root";
    std::string uncertainty_frontDown = "rootFiles/uncertainty_hists_frontFlat.root";


    if(fileName.find("030") != std::string::npos){
        uncertainty_low = "rootFiles/uncertainty_hists_low_030.root";
        uncertainty_high = "rootFiles/uncertainty_hists_high_030.root";
        uncertainty_frontDown = "rootFiles/uncertainty_hists_frontFlat_030.root";
    }
    if(fileName.find("045") != std::string::npos){
        uncertainty_low = "rootFiles/uncertainty_hists_low_045.root";
        uncertainty_high = "rootFiles/uncertainty_hists_high_045.root";
        uncertainty_frontDown = "rootFiles/uncertainty_hists_frontFlat_045.root";
    }
    if(fileName.find("120") != std::string::npos){
        uncertainty_low = "rootFiles/uncertainty_hists_low_120.root";
        uncertainty_high = "rootFiles/uncertainty_hists_high_120.root";
        uncertainty_frontDown = "rootFiles/uncertainty_hists_frontFlat_120.root";
    }

    TFile * correction_low = new TFile(uncertainty_low.c_str(), "READ");
    TFile * correction_high = new TFile(uncertainty_high.c_str(), "READ");
    TFile * correction_front = new TFile(uncertainty_frontDown.c_str(), "READ");

    TH2F * low_ratio_0 = (TH2F*)correction_low->Get("ratio_0");
    TH2F * low_ratio_1 = (TH2F*)correction_low->Get("ratio_1");
    TH2F * low_ratio_2 = (TH2F*)correction_low->Get("ratio_2");
    TH2F * low_ratio_3 = (TH2F*)correction_low->Get("ratio_3");
    TH2F * low_ratio_4 = (TH2F*)correction_low->Get("ratio_4");

    TH2F * high_ratio_0 = (TH2F*)correction_high->Get("ratio_0");
    TH2F * high_ratio_1 = (TH2F*)correction_high->Get("ratio_1");
    TH2F * high_ratio_2 = (TH2F*)correction_high->Get("ratio_2");
    TH2F * high_ratio_3 = (TH2F*)correction_high->Get("ratio_3");
    TH2F * high_ratio_4 = (TH2F*)correction_high->Get("ratio_4");

    TH2F * front_ratio_0 = (TH2F*)correction_front->Get("ratio_0");
    TH2F * front_ratio_1 = (TH2F*)correction_front->Get("ratio_1");
    TH2F * front_ratio_2 = (TH2F*)correction_front->Get("ratio_2");
    TH2F * front_ratio_3 = (TH2F*)correction_front->Get("ratio_3");
    TH2F * front_ratio_4 = (TH2F*)correction_front->Get("ratio_4");

	double mean1, mean2;
	double err1, err2;
	double ratio;
	double quantile;
	for(int eta = 0; eta < numEtaBins; eta++){
        if(etaBins[eta] != 1.4442 && etaBins[eta+1] != 1.566){
            for(int apd = 0; apd < 100; apd++){
                double correction_0 = 1 + std::max(fabs(high_ratio_0->GetBinContent(eta+1, apd+1)), fabs(low_ratio_0->GetBinContent(eta+1,apd+1)))/100. + fabs(front_ratio_0->GetBinContent(eta+1,apd+1)/100.);
                double correction_1 = 1 + std::max(fabs(high_ratio_1->GetBinContent(eta+1, apd+1)), fabs(low_ratio_1->GetBinContent(eta+1,apd+1)))/100. + fabs(front_ratio_1->GetBinContent(eta+1,apd+1)/100.);
                double correction_2 = 1 + std::max(fabs(high_ratio_2->GetBinContent(eta+1, apd+1)), fabs(low_ratio_2->GetBinContent(eta+1,apd+1)))/100. + fabs(front_ratio_2->GetBinContent(eta+1,apd+1)/100.);
                double correction_3 = 1 + std::max(fabs(high_ratio_3->GetBinContent(eta+1, apd+1)), fabs(low_ratio_3->GetBinContent(eta+1,apd+1)))/100. + fabs(front_ratio_3->GetBinContent(eta+1,apd+1)/100.);
                double correction_4 = 1 + std::max(fabs(high_ratio_4->GetBinContent(eta+1, apd+1)), fabs(low_ratio_4->GetBinContent(eta+1,apd+1)))/100. + fabs(front_ratio_4->GetBinContent(eta+1,apd+1)/100.);
                
                mean1 = e_0_hists[eta][99-apd]->GetMean();
                mean2 = g_0_hists[eta][99-apd]->GetMean();
                mean_0->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1)*correction_0);

                mean1 = e_1_hists[eta][99-apd]->GetMean();
                mean2 = g_1_hists[eta][99-apd]->GetMean();
                mean_1->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1)*correction_1);

                mean1 = e_2_hists[eta][99-apd]->GetMean();
                mean2 = g_2_hists[eta][99-apd]->GetMean();
                mean_2->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1)*correction_2);

                mean1 = e_3_hists[eta][99-apd]->GetMean();
                mean2 = g_3_hists[eta][99-apd]->GetMean();
                mean_3->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1)*correction_3);

                mean1 = e_4_hists[eta][99-apd]->GetMean();
                mean2 = g_4_hists[eta][99-apd]->GetMean();
                mean_4->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1)*correction_4);

                delete e_0_hists[eta][99-apd];
                delete g_0_hists[eta][99-apd];
                delete e_1_hists[eta][99-apd];
                delete g_1_hists[eta][99-apd];
                delete e_2_hists[eta][99-apd];
                delete g_2_hists[eta][99-apd];
                delete e_3_hists[eta][99-apd];
                delete g_3_hists[eta][99-apd];
                delete e_4_hists[eta][99-apd];
                delete g_4_hists[eta][99-apd];
            }
        }
    }

    TH2F * mean_EE_0 = (TH2F*)mean_0->Clone();
    TH2F * mean_EE_1 = (TH2F*)mean_1->Clone();
    TH2F * mean_EE_2 = (TH2F*)mean_2->Clone();
    TH2F * mean_EE_3 = (TH2F*)mean_3->Clone();
    TH2F * mean_EE_4 = (TH2F*)mean_4->Clone();

    mySystematicsProducer::plot_LookUpTable( mean_0, "lookUpTable_EB_R9_0", 0., 1.44419, -0.7, 0.7);
    mySystematicsProducer::plot_LookUpTable( mean_1, "lookUpTable_EB_R9_1", 0., 1.44419, -0.7, 0.7);
    mySystematicsProducer::plot_LookUpTable( mean_2, "lookUpTable_EB_R9_2", 0., 1.44419, -0.7, 0.7);
    mySystematicsProducer::plot_LookUpTable( mean_3, "lookUpTable_EB_R9_3", 0., 1.44419, -0.7, 0.7);
    mySystematicsProducer::plot_LookUpTable( mean_4, "lookUpTable_EB_R9_4", 0., 1.44419, -0.7, 0.7);

    mySystematicsProducer::plot_LookUpTable( mean_EE_0, "lookUpTable_EE_R9_0", 1.566, 2.499, -0.7, 0.7);
    mySystematicsProducer::plot_LookUpTable( mean_EE_1, "lookUpTable_EE_R9_1", 1.566, 2.499, -0.7, 0.7);
    mySystematicsProducer::plot_LookUpTable( mean_EE_2, "lookUpTable_EE_R9_2", 1.566, 2.499, -0.7, 0.7);
    mySystematicsProducer::plot_LookUpTable( mean_EE_3, "lookUpTable_EE_R9_3", 1.566, 2.499, -0.7, 0.7);
    mySystematicsProducer::plot_LookUpTable( mean_EE_4, "lookUpTable_EE_R9_4", 1.566, 2.499, -0.7, 0.7);

    std::cout << std::endl << "look-up tables have been produced ... " << std::endl;

    return;
};

void mySystematicsProducer::plot_LookUpTable( TH2F* thisHist, std::string title, double xMin, double xMax, double zMin, double zMax){
    TCanvas * a = new TCanvas("a", "", 900, 900);
    a->cd();
    gStyle->SetPalette(kBird);
    gStyle->SetOptStat(0);
    gStyle->SetPaintTextFormat("0.2f");
    gStyle->SetOptTitle(0);

    TLatex* pave = new TLatex(0.100, 0.91, "#font[42]{#bf{CMS} #it{Simulation Preliminary}}");
    TLatex* lumi_label = new TLatex(0.75, 0.91, "#font[42]{13 TeV}");
    thisHist->SetXTitle("|#eta|");
    thisHist->SetYTitle("Laser Response");
    thisHist->SetZTitle("Systematics [%]");
    thisHist->Draw("colztext");
    thisHist->SetContour(99);
    thisHist->SetAxisRange(xMin, xMax, "X");
    if(title.find("EB") != std::string::npos) thisHist->SetAxisRange(0.8, 0.9999999, "Y");
    if(title.find("EE") != std::string::npos) thisHist->SetAxisRange(0.6, 0.8999999, "Y");
    thisHist->SetAxisRange(zMin, zMax, "Z");
    thisHist->SetLabelSize(0.03, "Y");
    thisHist->SetLabelSize(0.02, "Z");
    thisHist->SetTitleSize(0.03, "Z");
    thisHist->SetTitleOffset(1.25, "Y");
    pave->SetNDC();
    pave->Draw();
    lumi_label->SetNDC();
    lumi_label->Draw();
    gPad->Update();	
    TPaletteAxis * palette =(TPaletteAxis*)thisHist->GetListOfFunctions()->FindObject("palette");
    palette->SetX2NDC(0.92);
    a->Modified();
    std::string saveName = DIRECTORY_NAME+"/"+title+".pdf";
    a->SaveAs(saveName.c_str());
    saveName = DIRECTORY_NAME+"/"+title+".C";
    a->SaveAs(saveName.c_str());
    saveName = DIRECTORY_NAME+"/"+title+".png";
    a->SaveAs(saveName.c_str());
    delete a;
    return;
};

#endif
