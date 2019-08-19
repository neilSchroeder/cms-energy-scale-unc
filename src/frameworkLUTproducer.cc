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
#include "../interface/frameworkLUTproducer.h"

//#define ETA_VETO
//#define ALT_R9
//#define ALT_ETA
//#define check

extern std::string DIRECTORY_NAME;
extern bool _flag_median;
/// Produce FNUF Histograms only analyzes two files at a time

void myLookUpTableProducer::produce_LookUpTables(std::string fileName, bool corrections){

    std::cout << "[STATUS] begin producing look-up tables... " << std::endl;
#ifdef ALT_R9
	int numR9bins = 6;
	double r9Bins[7] = {0, 0.8, 0.9, 0.92, 0.94, 0.96, 1.00}; 
#else 
    int numR9bins = 5;
    double r9Bins[6] = {0, 0.8, 0.9, 0.92, 0.96, 1.00};
#endif

#ifdef ALT_ETA
	int numEtaBins = 9;
	double etaBins [10] = {0, 0.3, 0.7, 1.1, 1.4442, 1.57, 1.8, 2.1, 2.3, 2.5};
#else
    int numEtaBins = 8;
    double etaBins [9] = {0, 0.3, 0.7, 1.1, 1.4442, 1.57, 1.8, 2.1, 2.5};
#endif


	TFile* myHistograms = new TFile(fileName.c_str(), "READ");

    std::cout << "[STATUS] initializing histograms ... " << std::endl;
    
	TH2F * mean_0 = new TH2F("mean_0", "r90", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean_1 = new TH2F("mean_1", "r91", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean_2 = new TH2F("mean_2", "r92", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean_3 = new TH2F("mean_3", "r93", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean_4 = new TH2F("mean_4", "r94", numEtaBins, etaBins, 100, 0.005, 1.005);
#ifdef ALT_R9
	TH2F * mean_5 = new TH2F("mean_5", "r95", numEtaBins, etaBins, 100, 0.005, 1.005);
#endif

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
#ifdef ALT_R9
	std::vector< std::vector<TH1F*> > e_5_hists;
	std::vector< std::vector<TH1F*> > g_5_hists;
#endif

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
#ifdef ALT_R9
	std::vector<TH1F*> e_5;
	std::vector<TH1F*> g_5;
#endif


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
#ifdef ALT_R9
			sprintf( title, "e_5_%i_%i_%i", i, i+1, j);
			e_5.push_back((TH1F*)myHistograms->Get(title));
			sprintf( title, "g_5_%i_%i_%i", i, i+1, j);
			g_5.push_back((TH1F*)myHistograms->Get(title));
#endif
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
#ifdef ALT_R9
		e_5_hists.push_back(e_5);
		g_5_hists.push_back(g_5);
#endif
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
#ifdef ALT_R9
		e_5.clear();
		g_5.clear();
#endif
	}

    std::cout << "[INFO] evaluating systematics ... " << std::endl;
#ifndef ALT_R9
    std::string uncertainty_low = "rootFiles/uncertainty_hists_low_060.root";
    std::string uncertainty_high = "rootFiles/uncertainty_hists_high_060.root";
    std::string uncertainty_frontDown = "rootFiles/uncertainty_hists_frontDown_060.root";


    if(fileName.find("030") != std::string::npos){
        uncertainty_low = "rootFiles/uncertainty_hists_low_030.root";
        uncertainty_high = "rootFiles/uncertainty_hists_high_030.root";
        uncertainty_frontDown = "rootFiles/uncertainty_hists_frontDown_030.root";
    }
    if(fileName.find("045") != std::string::npos){
        uncertainty_low = "rootFiles/uncertainty_hists_low_045.root";
        uncertainty_high = "rootFiles/uncertainty_hists_high_045.root";
        uncertainty_frontDown = "rootFiles/uncertainty_hists_frontDown_045.root";
    }
    if(fileName.find("120") != std::string::npos){
        uncertainty_low = "rootFiles/uncertainty_hists_low_120.root";
        uncertainty_high = "rootFiles/uncertainty_hists_high_120.root";
        uncertainty_frontDown = "rootFiles/uncertainty_hists_frontDown_120.root";
    }

#else
    std::string uncertainty_low = "rootFiles/uncertainty_hists_low_060_altR9.root";
    std::string uncertainty_high = "rootFiles/uncertainty_hists_high_060_altR9.root";
    std::string uncertainty_frontDown = "rootFiles/uncertainty_hists_frontDown_060_altR9.root";


    if(fileName.find("030") != std::string::npos){
        uncertainty_low = "rootFiles/uncertainty_hists_low_030_altR9.root";
        uncertainty_high = "rootFiles/uncertainty_hists_high_030_altR9.root";
        uncertainty_frontDown = "rootFiles/uncertainty_hists_frontDown_030_altR9.root";
    }
    if(fileName.find("045") != std::string::npos){
        uncertainty_low = "rootFiles/uncertainty_hists_low_045_altR9.root";
        uncertainty_high = "rootFiles/uncertainty_hists_high_045_altR9.root";
        uncertainty_frontDown = "rootFiles/uncertainty_hists_frontDown_045_altR9.root";
    }
    if(fileName.find("120") != std::string::npos){
        uncertainty_low = "rootFiles/uncertainty_hists_low_120_altR9.root";
        uncertainty_high = "rootFiles/uncertainty_hists_high_120_altR9.root";
        uncertainty_frontDown = "rootFiles/uncertainty_hists_frontDown_120_altR9.root";
    }
#endif

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


#ifdef ALT_R9
    TH2F * low_ratio_5 = (TH2F*)correction_low->Get("ratio_5");
    TH2F * high_ratio_5 = (TH2F*)correction_high->Get("ratio_5");
    TH2F * front_ratio_5 = (TH2F*)correction_front->Get("ratio_5");
#endif

    std::cout<< low_ratio_4->GetEntries() << std::endl;
    std::cout<< high_ratio_4->GetEntries() << std::endl;
    std::cout<< front_ratio_4->GetEntries() << std::endl;

	double mean1, mean2;
	double err1, err2;
	double ratio;
	double quantile;
	for(int eta = 0; eta < numEtaBins; eta++){
        if(eta != 4){
            for(int apd = 0; apd < 100; apd++){
                double correction_0 = 1 + fabs(high_ratio_0->GetBinContent(eta+1, apd+1))/100. + fabs(front_ratio_0->GetBinContent(eta+1,apd+1))/100.;
                double correction_1 = 1 + fabs(high_ratio_1->GetBinContent(eta+1, apd+1))/100. + fabs(front_ratio_1->GetBinContent(eta+1,apd+1))/100.;
                double correction_2 = 1 + fabs(high_ratio_2->GetBinContent(eta+1, apd+1))/100. + fabs(front_ratio_2->GetBinContent(eta+1,apd+1))/100.;
                double correction_3 = 1 + fabs(high_ratio_3->GetBinContent(eta+1, apd+1))/100. + fabs(front_ratio_3->GetBinContent(eta+1,apd+1))/100.;
                double correction_4 = 1 + fabs(high_ratio_4->GetBinContent(eta+1, apd+1))/100. + fabs(front_ratio_4->GetBinContent(eta+1,apd+1))/100.;
#ifdef ALT_R9
                double correction_5 = 1 + fabs(high_ratio_5->GetBinContent(eta+1, apd+1))/100. + fabs(front_ratio_5->GetBinContent(eta+1,apd+1))/100.;
#endif
                if(!_flag_median){
                    mean1 = e_0_hists[eta][99-apd]->GetMean();
                    mean2 = g_0_hists[eta][99-apd]->GetMean();
                    if(corrections) mean_0->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1)*correction_0);
                    else mean_0->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1));

                    mean1 = e_1_hists[eta][99-apd]->GetMean();
                    mean2 = g_1_hists[eta][99-apd]->GetMean();
                    if(corrections) mean_1->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1)*correction_1);
                    else mean_1->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1));

                    mean1 = e_2_hists[eta][99-apd]->GetMean();
                    mean2 = g_2_hists[eta][99-apd]->GetMean();
                    if(corrections) mean_2->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1)*correction_2);
                    else mean_2->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1));

                    mean1 = e_3_hists[eta][99-apd]->GetMean();
                    mean2 = g_3_hists[eta][99-apd]->GetMean();
                    if(corrections) mean_3->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1)*correction_3);
                    else mean_3->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1));

                    mean1 = e_4_hists[eta][99-apd]->GetMean();
                    mean2 = g_4_hists[eta][99-apd]->GetMean();
                    if(corrections) mean_4->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1)*correction_4);
                    else mean_4->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1));

#ifdef ALT_R9
                    mean1 = e_5_hists[eta][99-apd]->GetMean();
                    mean2 = g_5_hists[eta][99-apd]->GetMean();
                    if(corrections) mean_5->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1)*correction_5);
                    else mean_5->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1));
#endif
                }
                else{
                    double median = 0.5;
                    double thisMedian1, thisMedian2;

                    e_0_hists[eta][99-apd]->GetQuantiles(1, &thisMedian1, &median);
                    g_0_hists[eta][99-apd]->GetQuantiles(1, &thisMedian2, &median);
                    if(corrections) mean_0->SetBinContent(eta+1, apd+1, 100*((thisMedian2/thisMedian1) - 1)*correction_0);
                    else mean_0->SetBinContent(eta+1, apd+1, 100*((thisMedian2/thisMedian1) - 1));

                    e_1_hists[eta][99-apd]->GetQuantiles(1, &thisMedian1, &median);
                    g_1_hists[eta][99-apd]->GetQuantiles(1, &thisMedian2, &median);
                    if(corrections) mean_1->SetBinContent(eta+1, apd+1, 100*((thisMedian2/thisMedian1) - 1)*correction_1);
                    else mean_1->SetBinContent(eta+1, apd+1, 100*((thisMedian2/thisMedian1) - 1));

                    e_2_hists[eta][99-apd]->GetQuantiles(1, &thisMedian1, &median);
                    g_2_hists[eta][99-apd]->GetQuantiles(1, &thisMedian2, &median);
                    if(corrections) mean_2->SetBinContent(eta+1, apd+1, 100*((thisMedian2/thisMedian1) - 1)*correction_2);
                    else mean_2->SetBinContent(eta+1, apd+1, 100*((thisMedian2/thisMedian1) - 1));

                    e_3_hists[eta][99-apd]->GetQuantiles(1, &thisMedian1, &median);
                    g_3_hists[eta][99-apd]->GetQuantiles(1, &thisMedian2, &median);
                    if(corrections) mean_3->SetBinContent(eta+1, apd+1, 100*((thisMedian2/thisMedian1) - 1)*correction_3);
                    else mean_3->SetBinContent(eta+1, apd+1, 100*((thisMedian2/thisMedian1) - 1));

                    e_4_hists[eta][99-apd]->GetQuantiles(1, &thisMedian1, &median);
                    g_4_hists[eta][99-apd]->GetQuantiles(1, &thisMedian2, &median);
                    if(corrections) mean_4->SetBinContent(eta+1, apd+1, 100*((thisMedian2/thisMedian1) - 1)*correction_4);
                    else mean_4->SetBinContent(eta+1, apd+1, 100*((thisMedian2/thisMedian1) - 1));
                }   

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
#ifdef ALT_R9
                delete e_5_hists[eta][99-apd];
                delete g_5_hists[eta][99-apd];
#endif
            }
        }
    }

    TH2F * mean_EE_0 = (TH2F*)mean_0->Clone();
    TH2F * mean_EE_1 = (TH2F*)mean_1->Clone();
    TH2F * mean_EE_2 = (TH2F*)mean_2->Clone();
    TH2F * mean_EE_3 = (TH2F*)mean_3->Clone();
    TH2F * mean_EE_4 = (TH2F*)mean_4->Clone();
#ifdef ALT_R9
    TH2F * mean_EE_5 = (TH2F*)mean_5->Clone();
#endif


    myLookUpTableProducer::plot_LookUpTable( mean_0, "lookUpTable_EB_R9_0", 0., 2.49999, -999, -999);
    myLookUpTableProducer::plot_LookUpTable( mean_1, "lookUpTable_EB_R9_1", 0., 2.49999, -999, -999);
    myLookUpTableProducer::plot_LookUpTable( mean_2, "lookUpTable_EB_R9_2", 0., 2.49999, -999, -999);
    myLookUpTableProducer::plot_LookUpTable( mean_3, "lookUpTable_EB_R9_3", 0., 2.49999, -999, -999);
    myLookUpTableProducer::plot_LookUpTable( mean_4, "lookUpTable_EB_R9_4", 0., 2.49999, -999, -999);
#ifdef ALT_R9
    myLookUpTableProducer::plot_LookUpTable( mean_5, "lookUpTable_EB_R9_4", 0., 2.49999, -999, -999);
#endif

    std::cout << std::endl << "[INFO] look-up tables have been produced ... " << std::endl;

    return;
};

void myLookUpTableProducer::plot_LookUpTable( TH2F* thisHist, std::string title, double xMin, double xMax, double zMin, double zMax){
#ifdef ALT_R9
	int numR9bins = 6;
	double r9Bins[7] = {0, 0.8, 0.9, 0.92, 0.94, 0.96, 1.00}; 
#else 
    int numR9bins = 5;
    double r9Bins[6] = {0, 0.8, 0.9, 0.92, 0.96, 1.00};
#endif

#ifdef ALT_ETA
	int numEtaBins = 9;
	double etaBins [10] = {0, 0.3, 0.7, 1.1, 1.4442, 1.57, 1.8, 2.1, 2.3, 2.5};
#else
    int numEtaBins = 9;
    double etaBins[9] = {0, 0.3, 0.7, 1.1, 1.4442, 1.57, 1.8, 2.1, 2.5};
#endif
    TCanvas * a = new TCanvas("a", "", 1600, 1200);
    if( !(thisHist) ) std::cout << "[ERROR] could not open historgram: " << thisHist->GetName() << std::endl;
    a->cd();
    gStyle->SetPalette(kBird);
    gStyle->SetOptStat(0);
    gStyle->SetPaintTextFormat("0.2f");
    gStyle->SetOptTitle(0);

    TLatex* pave = new TLatex(0.100, 0.91, "#font[42]{#bf{CMS} #it{Simulation Preliminary}}");
    TLatex* lumi_label = new TLatex(0.9, 0.91, "#font[42]{13 TeV}");
    lumi_label->SetTextAlign(31);
    thisHist->SetXTitle("|#eta|");
    thisHist->SetYTitle("Laser Response");
    thisHist->SetZTitle("Systematics [%]");
    thisHist->Draw("colztext");
    thisHist->SetContour(99);
    thisHist->SetAxisRange(xMin, xMax, "X");
    thisHist->SetAxisRange(0.5, 1., "Y");
    if(zMin == -999 && zMax == -999){
        zMin = thisHist->GetMinimum();
        zMax = thisHist->GetMaximum();
        std::cout << zMin << " " << zMax << std::endl;
        zMax = 1.1*std::max(fabs(zMin), fabs(zMax));
        zMin = -1*zMax;
        std::cout << zMin << " " << zMax << std::endl;
    }
    thisHist->SetAxisRange(zMin, zMax, "Z");
    thisHist->SetLabelSize(0.03, "Y");
    thisHist->SetLabelSize(0.02, "Z");
    thisHist->SetTitleSize(0.03, "Z");
    thisHist->SetTitleOffset(1.25, "Y");
    TBox * myBox = new TBox(1.4442, 0.495, 1.57, 1.005);
    myBox->SetFillStyle(3002);
    myBox->SetFillColor(kBlack);
    myBox->SetLineColor(kBlack);
    pave->SetNDC();
    pave->Draw();
    lumi_label->SetNDC();
    lumi_label->Draw();
    myBox->Draw();
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

void myLookUpTableProducer::produce_RatioLookUpTables(std::string fileName1, std::string fileName2){
#ifdef ALT_R9
	int numR9bins = 6;
	double r9Bins[7] = {0, 0.8, 0.9, 0.92, 0.94, 0.96, 1.00}; 
#else 
    int numR9bins = 5;
    double r9Bins[6] = {0, 0.8, 0.9, 0.92, 0.96, 1.00};
#endif

#ifdef ALT_Eta
	int numEtaBins = 9;
	double etaBins [10] = {0, 0.3, 0.7, 1.1, 1.4442, 1.57, 1.8, 2.1, 2.3, 2.5};
#else
    int numEtaBins = 8;
    double etaBins [9] = {0, 0.3, 0.7, 1.1, 1.4442, 1.57, 1.8, 2.1, 2.5};
#endif

    std::cout << "begin producing ratio look-up tables... " << std::endl;

    std::cout << "initializing histograms ... " << std::endl;

    std::vector< std::vector<TH1F*> > ratio;
    std::vector< std::vector<TH1F*> > systematics1;
    std::vector< std::vector<TH1F*> > systematics2;
    std::vector< TH1F* > temp1_;
    std::vector< TH1F* > temp2_;
    std::vector< TH1F* > temp3_;
    char title [50];
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < numR9bins; j++){
            sprintf(title, "ratio_%i_%i", i, j);
            temp3_.push_back(new TH1F(title, title, numEtaBins, etaBins));
            sprintf(title, "systematics1_%i_%i", i, j);
            temp1_.push_back(new TH1F(title, title, numEtaBins, etaBins));
            sprintf(title, "systematics2_%i_%i", i, j);
            temp2_.push_back(new TH1F(title, title, numEtaBins, etaBins));
        }
        ratio.push_back(temp3_);
        systematics1.push_back(temp1_);
        systematics2.push_back(temp2_);
        temp1_.clear();
        temp2_.clear();
        temp3_.clear();
    }
    
	TH2F * mean1_0 = new TH2F("mean1_0", "", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean1_1 = new TH2F("mean1_1", "", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean1_2 = new TH2F("mean1_2", "", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean1_3 = new TH2F("mean1_3", "", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean1_4 = new TH2F("mean1_4", "", numEtaBins, etaBins, 100, 0.005, 1.005);

	TH2F * mean2_0 = new TH2F("mean2_0", "", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean2_1 = new TH2F("mean2_1", "", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean2_2 = new TH2F("mean2_2", "", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean2_3 = new TH2F("mean2_3", "", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean2_4 = new TH2F("mean2_4", "", numEtaBins, etaBins, 100, 0.005, 1.005);

    TH2F * ratio_0 = new TH2F("ratio_0", "", numEtaBins, etaBins, 100, 0.005, 1.005);
    TH2F * ratio_1 = new TH2F("ratio_1", "", numEtaBins, etaBins, 100, 0.005, 1.005);
    TH2F * ratio_2 = new TH2F("ratio_2", "", numEtaBins, etaBins, 100, 0.005, 1.005);
    TH2F * ratio_3 = new TH2F("ratio_3", "", numEtaBins, etaBins, 100, 0.005, 1.005);
    TH2F * ratio_4 = new TH2F("ratio_4", "", numEtaBins, etaBins, 100, 0.005, 1.005);
#ifdef ALT_R9
	TH2F * mean1_5 = new TH2F("mean1_5", "", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * mean2_5 = new TH2F("mean2_5", "", numEtaBins, etaBins, 100, 0.005, 1.005);
	TH2F * ratio_5 = new TH2F("ratio_5", "", numEtaBins, etaBins, 100, 0.005, 1.005);
#endif


    std::vector< std::vector<TH1F*> > e1_0_hists;
	std::vector< std::vector<TH1F*> > e1_1_hists;
	std::vector< std::vector<TH1F*> > e1_2_hists;
	std::vector< std::vector<TH1F*> > e1_3_hists;
	std::vector< std::vector<TH1F*> > e1_4_hists;
	std::vector< std::vector<TH1F*> > g1_0_hists;
	std::vector< std::vector<TH1F*> > g1_1_hists;
	std::vector< std::vector<TH1F*> > g1_2_hists;
	std::vector< std::vector<TH1F*> > g1_3_hists;
	std::vector< std::vector<TH1F*> > g1_4_hists;

	std::vector< std::vector<TH1F*> > e2_0_hists;
	std::vector< std::vector<TH1F*> > e2_1_hists;
	std::vector< std::vector<TH1F*> > e2_2_hists;
	std::vector< std::vector<TH1F*> > e2_3_hists;
	std::vector< std::vector<TH1F*> > e2_4_hists;
	std::vector< std::vector<TH1F*> > g2_0_hists;
	std::vector< std::vector<TH1F*> > g2_1_hists;
	std::vector< std::vector<TH1F*> > g2_2_hists;
	std::vector< std::vector<TH1F*> > g2_3_hists;
	std::vector< std::vector<TH1F*> > g2_4_hists;

    std::vector<TH1F*> e1_0;
	std::vector<TH1F*> e1_1;
	std::vector<TH1F*> e1_2;
	std::vector<TH1F*> e1_3;
	std::vector<TH1F*> e1_4;
	std::vector<TH1F*> g1_0;
	std::vector<TH1F*> g1_1;
	std::vector<TH1F*> g1_2;
	std::vector<TH1F*> g1_3;
	std::vector<TH1F*> g1_4;

	std::vector<TH1F*> e2_0;
	std::vector<TH1F*> e2_1;
	std::vector<TH1F*> e2_2;
	std::vector<TH1F*> e2_3;
	std::vector<TH1F*> e2_4;
	std::vector<TH1F*> g2_0;
	std::vector<TH1F*> g2_1;
	std::vector<TH1F*> g2_2;
	std::vector<TH1F*> g2_3;
	std::vector<TH1F*> g2_4;

#ifdef ALT_R9
	std::vector< std::vector<TH1F*> > e1_5_hists;
	std::vector< std::vector<TH1F*> > g1_5_hists;
	std::vector< std::vector<TH1F*> > e2_5_hists;
	std::vector< std::vector<TH1F*> > g2_5_hists;
	std::vector<TH1F*> e1_5;
	std::vector<TH1F*> e2_5;
	std::vector<TH1F*> g1_5;
	std::vector<TH1F*> g2_5;
#endif

    for(int i = 0; i < numEtaBins; i++){
        for(int j = 0; j < 100; j++){
            e1_0.push_back(new TH1F());
            e1_1.push_back(new TH1F());
            e1_2.push_back(new TH1F());
            e1_3.push_back(new TH1F());
            e1_4.push_back(new TH1F());
            g1_0.push_back(new TH1F());
            g1_1.push_back(new TH1F());
            g1_2.push_back(new TH1F());
            g1_3.push_back(new TH1F());
            g1_4.push_back(new TH1F());
            e2_0.push_back(new TH1F());
            e2_1.push_back(new TH1F());
            e2_2.push_back(new TH1F());
            e2_3.push_back(new TH1F());
            e2_4.push_back(new TH1F());
            g2_0.push_back(new TH1F());
            g2_1.push_back(new TH1F());
            g2_2.push_back(new TH1F());
            g2_3.push_back(new TH1F());
            g2_4.push_back(new TH1F());
#ifdef ALT_R9
            e1_5.push_back(new TH1F());
            e2_5.push_back(new TH1F());
            g1_5.push_back(new TH1F());
            g2_5.push_back(new TH1F());
#endif
        }
		e1_0_hists.push_back(e1_0);
		e1_1_hists.push_back(e1_1);
		e1_2_hists.push_back(e1_2);
		e1_3_hists.push_back(e1_3);
		e1_4_hists.push_back(e1_4);
		g1_0_hists.push_back(g1_0);
		g1_1_hists.push_back(g1_1);
		g1_2_hists.push_back(g1_2);
		g1_3_hists.push_back(g1_3);
		g1_4_hists.push_back(g1_4);
		e2_0_hists.push_back(e2_0);
		e2_1_hists.push_back(e2_1);
		e2_2_hists.push_back(e2_2);
		e2_3_hists.push_back(e2_3);
		e2_4_hists.push_back(e2_4);
		g2_0_hists.push_back(g2_0);
		g2_1_hists.push_back(g2_1);
		g2_2_hists.push_back(g2_2);
		g2_3_hists.push_back(g2_3);
		g2_4_hists.push_back(g2_4);
#ifdef ALT_R9
        e1_5_hists.push_back(e1_5);
        e2_5_hists.push_back(e2_5);
        g1_5_hists.push_back(g1_5);
        g2_5_hists.push_back(g2_5);
        e1_5.clear();
        e2_5.clear();
        g1_5.clear();
        g2_5.clear();
#endif
		e1_0.clear();
		e1_1.clear();
		e1_2.clear();
		e1_3.clear();
		e1_4.clear();
		g1_0.clear();
		g1_1.clear();
		g1_2.clear();
		g1_3.clear();
		g1_4.clear();
		e2_0.clear();
		e2_1.clear();
		e2_2.clear();
		e2_3.clear();
		e2_4.clear();
		g2_0.clear();
		g2_1.clear();
		g2_2.clear();
		g2_3.clear();
		g2_4.clear();
    }

	TFile* myHistograms1 = new TFile(fileName1.c_str(), "READ");
    if(!myHistograms1 || myHistograms1->IsZombie()){
        std::cout << "The file '" << fileName1 <<"` did not successfully open." << std::endl;
        return;
    }
    TFile* myHistograms2 = new TFile(fileName2.c_str(), "READ");
    if(!myHistograms2 || myHistograms2->IsZombie()){
        std::cout << "The file '" << fileName1 <<"` did not successfully open." << std::endl;
        return;
    }

    myHistograms1->cd();
	for(int i = 0; i < numEtaBins; i++){
		for(int j = 0; j < 100; j++){
			sprintf( title, "e_0_%i_%i_%i", i, i+1, j);
			e1_0_hists[i][j] = (TH1F*)gDirectory->Get(title);
            e1_0_hists[i][j]->GetMean();
			sprintf( title, "e_1_%i_%i_%i", i, i+1, j);
			e1_1_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "e_2_%i_%i_%i", i, i+1, j);
			e1_2_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "e_3_%i_%i_%i", i, i+1, j);
			e1_3_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "e_4_%i_%i_%i", i, i+1, j);
			e1_4_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "g_0_%i_%i_%i", i, i+1, j);
			g1_0_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "g_1_%i_%i_%i", i, i+1, j);
			g1_1_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "g_2_%i_%i_%i", i, i+1, j);
			g1_2_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "g_3_%i_%i_%i", i, i+1, j);
			g1_3_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "g_4_%i_%i_%i", i, i+1, j);
			g1_4_hists[i][j] = (TH1F*)gDirectory->Get(title);
#ifdef ALT_R9
			sprintf( title, "e_5_%i_%i_%i", i, i+1, j);
			e1_5_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "g_5_%i_%i_%i", i, i+1, j);
			g1_5_hists[i][j] = (TH1F*)gDirectory->Get(title);
#endif
      	}
	}

    myHistograms2->cd();
	for(int i = 0; i < numEtaBins; i++){
		for(int j = 0; j < 100; j++){
			sprintf( title, "e_0_%i_%i_%i", i, i+1, j);
			e2_0_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "e_1_%i_%i_%i", i, i+1, j);
			e2_1_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "e_2_%i_%i_%i", i, i+1, j);
			e2_2_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "e_3_%i_%i_%i", i, i+1, j);
			e2_3_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "e_4_%i_%i_%i", i, i+1, j);
			e2_4_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "g_0_%i_%i_%i", i, i+1, j);
			g2_0_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "g_1_%i_%i_%i", i, i+1, j);
			g2_1_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "g_2_%i_%i_%i", i, i+1, j);
			g2_2_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "g_3_%i_%i_%i", i, i+1, j);
			g2_3_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "g_4_%i_%i_%i", i, i+1, j);
			g2_4_hists[i][j] = (TH1F*)gDirectory->Get(title);
#ifdef ALT_R9
			sprintf( title, "e_5_%i_%i_%i", i, i+1, j);
			e2_5_hists[i][j] = (TH1F*)gDirectory->Get(title);
			sprintf( title, "g_5_%i_%i_%i", i, i+1, j);
			g2_5_hists[i][j] = (TH1F*)gDirectory->Get(title);
#endif
      	}
	}

    std::cout << "evaluating systematics ... " << std::endl;

	double mean11, mean12, mean21, mean22;
	double err11, err12, err21, err22;
	double ratio1, ratio2;
    double err1, err2;
	double quantile;

	for(int eta = 0; eta < numEtaBins; eta++){
        if(eta != 4){
            for(int apd = 0; apd < 100; apd++){
                
                mean11 = e1_0_hists[eta][99-apd]->GetMean();
                mean12 = g1_0_hists[eta][99-apd]->GetMean();
                mean1_0->SetBinContent(eta + 1, apd + 1, ((mean12/mean11) ));
                systematics1[apd][0]->SetBinContent(eta+1, mean12/mean11);

                mean11 = e1_1_hists[eta][99-apd]->GetMean();
                mean12 = g1_1_hists[eta][99-apd]->GetMean();
                mean1_1->SetBinContent(eta + 1, apd + 1, ((mean12/mean11) ));
                systematics1[apd][1]->SetBinContent(eta+1, mean12/mean11);

                mean11 = e1_2_hists[eta][99-apd]->GetMean();
                mean12 = g1_2_hists[eta][99-apd]->GetMean();
                mean1_2->SetBinContent(eta + 1, apd + 1, ((mean12/mean11) ));
                systematics1[apd][2]->SetBinContent(eta+1, mean12/mean11);

                mean11 = e1_3_hists[eta][99-apd]->GetMean();
                mean12 = g1_3_hists[eta][99-apd]->GetMean();
                mean1_3->SetBinContent(eta + 1, apd + 1, ((mean12/mean11) ));
                systematics1[apd][3]->SetBinContent(eta+1, mean12/mean11);

                mean11 = e1_4_hists[eta][99-apd]->GetMean();
                mean12 = g1_4_hists[eta][99-apd]->GetMean();
                mean1_4->SetBinContent(eta + 1, apd + 1, ((mean12/mean11) ));
                systematics1[apd][4]->SetBinContent(eta+1, mean12/mean11);
#ifdef ALT_R9
                mean11 = e1_5_hists[eta][99-apd]->GetMean();
                mean12 = g1_5_hists[eta][99-apd]->GetMean();
                mean1_5->SetBinContent(eta + 1, apd + 1, ((mean12/mean11) ));
                systematics1[apd][5]->SetBinContent(eta+1, mean12/mean11);
#endif

                mean21 = e2_0_hists[eta][99-apd]->GetMean();
                mean22 = g2_0_hists[eta][99-apd]->GetMean();
                mean2_0->SetBinContent(eta + 1, apd + 1, ((mean22/mean21) ));
                std::cout << mean21 << " " << mean22 << std::endl;

                mean21 = e2_1_hists[eta][99-apd]->GetMean();
                mean22 = g2_1_hists[eta][99-apd]->GetMean();
                mean2_1->SetBinContent(eta + 1, apd + 1, ((mean22/mean21) ));
                systematics2[apd][1]->SetBinContent(eta+1, mean22/mean21);

                mean21 = e2_2_hists[eta][99-apd]->GetMean();
                mean22 = g2_2_hists[eta][99-apd]->GetMean();
                mean2_2->SetBinContent(eta + 1, apd + 1, ((mean22/mean21) ));
                systematics2[apd][2]->SetBinContent(eta+1, mean22/mean21);

                mean21 = e2_3_hists[eta][99-apd]->GetMean();
                mean22 = g2_3_hists[eta][99-apd]->GetMean();
                mean2_3->SetBinContent(eta + 1, apd + 1, ((mean22/mean21) ));
                systematics2[apd][3]->SetBinContent(eta+1, mean22/mean21);

                mean21 = e2_4_hists[eta][99-apd]->GetMean();
                mean22 = g2_4_hists[eta][99-apd]->GetMean();
                mean2_4->SetBinContent(eta + 1, apd + 1, ((mean22/mean21) ));
                systematics2[apd][4]->SetBinContent(eta+1, mean22/mean21);
#ifdef ALT_R9
                mean21 = e2_5_hists[eta][99-apd]->GetMean();
                mean22 = g2_5_hists[eta][99-apd]->GetMean();
                mean2_5->SetBinContent(eta + 1, apd + 1, ((mean22/mean21) ));
                systematics2[apd][5]->SetBinContent(eta+1, mean22/mean21);
#endif


                ratio[apd][0]->SetBinContent(eta+1, 100*((systematics1[apd][0]->GetBinContent(eta+1)/systematics2[apd][0]->GetBinContent(eta+1))- 1));
                ratio[apd][1]->SetBinContent(eta+1, 100*((systematics1[apd][1]->GetBinContent(eta+1)/systematics2[apd][1]->GetBinContent(eta+1))- 1));
                ratio[apd][2]->SetBinContent(eta+1, 100*((systematics1[apd][2]->GetBinContent(eta+1)/systematics2[apd][2]->GetBinContent(eta+1))- 1));
                ratio[apd][3]->SetBinContent(eta+1, 100*((systematics1[apd][3]->GetBinContent(eta+1)/systematics2[apd][3]->GetBinContent(eta+1))- 1));
                ratio[apd][4]->SetBinContent(eta+1, 100*((systematics1[apd][4]->GetBinContent(eta+1)/systematics2[apd][4]->GetBinContent(eta+1))- 1));
#ifdef ALT_R9
                ratio[apd][5]->SetBinContent(eta+1, 100*((systematics1[apd][5]->GetBinContent(eta+1)/systematics2[apd][5]->GetBinContent(eta+1))- 1));
#endif

                ratio_0->SetBinContent(eta + 1, apd + 1, 100*(mean1_0->GetBinContent(eta+1, apd+1) / mean2_0->GetBinContent(eta+1, apd+1) - 1));
                ratio_1->SetBinContent(eta + 1, apd + 1, 100*(mean1_1->GetBinContent(eta+1, apd+1) / mean2_1->GetBinContent(eta+1, apd+1) - 1));
                ratio_2->SetBinContent(eta + 1, apd + 1, 100*(mean1_2->GetBinContent(eta+1, apd+1) / mean2_2->GetBinContent(eta+1, apd+1) - 1));
                ratio_3->SetBinContent(eta + 1, apd + 1, 100*(mean1_3->GetBinContent(eta+1, apd+1) / mean2_3->GetBinContent(eta+1, apd+1) - 1));
                ratio_4->SetBinContent(eta + 1, apd + 1, 100*(mean1_4->GetBinContent(eta+1, apd+1) / mean2_4->GetBinContent(eta+1, apd+1) - 1));
#ifdef ALT_R9
                ratio_5->SetBinContent(eta + 1, apd + 1, 100*(mean1_5->GetBinContent(eta+1, apd+1) / mean2_5->GetBinContent(eta+1, apd+1) - 1));
#endif

#ifdef check
                std::cout << systematics1[apd][0]->GetBinContent(eta+1) << std::endl;
                std::cout << systematics1[apd][1]->GetBinContent(eta+1) << std::endl;
                std::cout << systematics1[apd][2]->GetBinContent(eta+1) << std::endl;
                std::cout << systematics1[apd][3]->GetBinContent(eta+1) << std::endl;
                std::cout << systematics1[apd][4]->GetBinContent(eta+1) << std::endl << std::endl;
                std::cout << systematics2[apd][0]->GetBinContent(eta+1) << std::endl;
                std::cout << systematics2[apd][1]->GetBinContent(eta+1) << std::endl;
                std::cout << systematics2[apd][2]->GetBinContent(eta+1) << std::endl;
                std::cout << systematics2[apd][3]->GetBinContent(eta+1) << std::endl;
                std::cout << systematics2[apd][4]->GetBinContent(eta+1) << std::endl << std::endl;
                std::cout << ratio_0->GetBinContent(eta+1, apd + 1) << std::endl;
                std::cout << ratio_1->GetBinContent(eta+1, apd + 1) << std::endl;
                std::cout << ratio_2->GetBinContent(eta+1, apd + 1) << std::endl;
                std::cout << ratio_3->GetBinContent(eta+1, apd + 1) << std::endl;
                std::cout << ratio_4->GetBinContent(eta+1, apd + 1) << std::endl << std::endl;
#endif
            }
        }
    }

    TH2F * ratio_EE_0 = (TH2F*)ratio_0->Clone();
    TH2F * ratio_EE_1 = (TH2F*)ratio_1->Clone();
    TH2F * ratio_EE_2 = (TH2F*)ratio_2->Clone();
    TH2F * ratio_EE_3 = (TH2F*)ratio_3->Clone();
    TH2F * ratio_EE_4 = (TH2F*)ratio_4->Clone();
#ifdef ALT_R9
    TH2F * ratio_EE_5 = (TH2F*)ratio_5->Clone();
#endif

    std::string outName = DIRECTORY_NAME+"uncertainty_hists_";
    std::string type = "low_";
    std::string energy;
    if(fileName1.find("High") != std::string::npos || fileName2.find("High") != std::string::npos) type = "high_";
    if(fileName1.find("Flat") != std::string::npos || fileName2.find("Flat") != std::string::npos) type = "front_";
    if(fileName1.find("030") != std::string::npos || fileName2.find("030") != std::string::npos) energy = "030";
    if(fileName1.find("045") != std::string::npos || fileName2.find("045") != std::string::npos) energy = "045";
    if(fileName1.find("060") != std::string::npos || fileName2.find("060") != std::string::npos) energy = "060";
    if(fileName1.find("120") != std::string::npos || fileName2.find("120") != std::string::npos) energy = "120";
    outName = outName+type+energy;
#ifdef ALT_R9
    outName = outName+"_altR9";
#endif
    outName = outName+".root";
    std::cout << "[INFO] output file: " << outName << std::endl;


    // these ratios will be saved to a root file for later use
    TFile * outputRatioHists = new TFile(outName.c_str(), "RECREATE");
    outputRatioHists->cd();
    ratio_0->Write();
    ratio_1->Write();
    ratio_2->Write();
    ratio_3->Write();
    ratio_4->Write();
#ifdef ALT_R9
    ratio_5->Write();
#endif
    outputRatioHists->Close();

    myLookUpTableProducer::plot_LookUpTable(ratio_0, "ratioLookUpTable_EB_R9_0", 0., 2.499, -0.3, 0.3);
    myLookUpTableProducer::plot_LookUpTable(ratio_1, "ratioLookUpTable_EB_R9_1", 0., 2.499, -0.3, 0.3);
    myLookUpTableProducer::plot_LookUpTable(ratio_2, "ratioLookUpTable_EB_R9_2", 0., 2.499, -0.3, 0.3);
    myLookUpTableProducer::plot_LookUpTable(ratio_3, "ratioLookUpTable_EB_R9_3", 0., 2.499, -0.3, 0.3);
    myLookUpTableProducer::plot_LookUpTable(ratio_4, "ratioLookUpTable_EB_R9_4", 0., 2.499, -0.3, 0.3);
#ifdef ALT_R9
    myLookUpTableProducer::plot_LookUpTable(ratio_5, "ratioLookUpTable_EB_R9_5", 0., 2.499, -0.3, 0.3);
#endif

    std::cout << std::endl << "[INFO] ratio look-up tables have been produced ... " << std::endl;
    delete myHistograms1;
    delete myHistograms2;
    return;
};

void myLookUpTableProducer::produce_PionLookUpTables(std::string fileName, bool corrections){
#ifdef ALT_R9
	int numR9bins = 6;
	double r9Bins[7] = {0, 0.8, 0.9, 0.92, 0.94, 0.96, 1.00}; 
#else 
    int numR9bins = 5;
    double r9Bins[6] = {0, 0.8, 0.9, 0.92, 0.96, 1.00};
#endif

	int numEtaBins = 8;
	double etaBins [9] = {0, 0.3, 0.7, 1.1, 1.4442, 1.57, 1.8, 2.1, 2.5};

    std::cout << "[STATUS] begin producing look-up tables... " << std::endl;

	TFile* myHistograms = new TFile(fileName.c_str(), "READ");

    std::cout << "[STATUS] initializing histograms ... " << std::endl;
    
	TH2F * mean_0 = new TH2F("mean_0", "Photon Systematics [%], 0 < R9 < 0.8", numEtaBins, etaBins, 100, 0.005, 1.005);

	std::vector< std::vector<TH1F*> > e_0_hists;
	std::vector< std::vector<TH1F*> > g_0_hists;

	std::vector<TH1F*> e_0;
	std::vector<TH1F*> g_0;

	char title [50];
	for(int i = 0; i < numEtaBins; i++){
		for(int j = 0; j < 100; j++){
			sprintf( title, "e_0_%i_%i_%i", i, i+1, j);
			e_0.push_back((TH1F*)myHistograms->Get(title));
			sprintf( title, "g_0_%i_%i_%i", i, i+1, j);
			g_0.push_back((TH1F*)myHistograms->Get(title));
      	}
		e_0_hists.push_back(e_0);
		g_0_hists.push_back(g_0);
		e_0.clear();
		g_0.clear();
	}

    std::cout << "[STATUS] evaluating systematics ... " << std::endl;

	double mean1, mean2;
	double err1, err2;
	double ratio;
	double quantile;
	for(int eta = 0; eta < numEtaBins; eta++){
        if(etaBins[eta] != 1.4442 && etaBins[eta+1] != 1.566){
            for(int apd = 0; apd < 100; apd++){
                mean1 = e_0_hists[eta][99-apd]->GetMean();
                mean2 = g_0_hists[eta][99-apd]->GetMean();
                mean_0->SetBinContent(eta + 1, apd + 1, 100*((mean2/mean1) - 1));
                delete e_0_hists[eta][99-apd];
                delete g_0_hists[eta][99-apd];
            }
        }
    }

    TH2F * mean_EE_0 = (TH2F*)mean_0->Clone();

    myLookUpTableProducer::plot_LookUpTable( mean_0, "lookUpTable_EB_R9_0", 0., 1.44419, -0.1, 0.4);

    myLookUpTableProducer::plot_LookUpTable( mean_EE_0, "lookUpTable_EE_R9_0", 1.566, 2.499, -0.1, 0.45);

    std::cout << std::endl << "[INFO] look-up tables have been produced ... " << std::endl;

    return;
};

#endif
